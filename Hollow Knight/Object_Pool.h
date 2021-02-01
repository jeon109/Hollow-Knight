#pragma once

#include <stack>
#include <mutex>

typedef std::lock_guard<std::recursive_mutex> MutexLocker;

template<typename T>
class objectPool
{
public:
	objectPool();
	~objectPool();
	T* PopObject();
	void SetSize(int size);
	void Expand();
	void ReturnObject(T* object);
	int ReturnSize();

private:
	std::recursive_mutex _mt;
	std::stack<T*> _objects;
	int _maxSize; // 최대 배열 크기
};
// 사이즈만큼 오브젝트를 만든다.
template<typename T>
objectPool<T>::objectPool() {}

// 오브젝트를 비운다.
template<typename T>
objectPool<T>::~objectPool()
{
	MutexLocker locker(_mt);
	while (!_objects.empty()) {
		T* object = _objects.top();
		_objects.pop();
		delete object;
	}

	_maxSize = 0;
}

template<typename T>
void objectPool<T>::SetSize(int size) {
	_maxSize = size;

	for (int i = 0; i < _maxSize; ++i) {
		T* newObject = new T();
		_objects.push(newObject);
	}
}

// 오브젝트를 꺼낸다.
template<typename T>
T* objectPool<T>::PopObject()
{
	MutexLocker locker(_mt);

	// 오브젝트가 없다면 확장한다.
	if (_objects.empty()) {
		Expand();
	}

	T* retVal = _objects.top();
	_objects.pop();
	return retVal;
}

// 현재 크기만큼 새로운 오브젝트를 넣어 확장한다.
template<typename T>
void objectPool<T>::Expand() {
	MutexLocker locker(_mt);

	for (int i = 0; i < _maxSize; ++i)
	{
		T* newObject = new T();
		_objects.push(newObject);
	}

	_maxSize += _maxSize;
}

// 오브젝트를 수거한다.
template<typename T>
void objectPool<T>::ReturnObject(T* object)
{
	MutexLocker locker(_mt);
	_objects.push(object);
}

template<typename T>
int objectPool<T>::ReturnSize()
{
	return _objects.size();
}