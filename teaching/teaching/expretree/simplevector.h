#pragma once
#include <initializer_list>
#include <utility>

template<typename T>
class SimpleVector {
public:
	SimpleVector() {
		reserve(16);
	}

	SimpleVector(const SimpleVector<T>& other) {
		reserve(other._capacity);
		for (int i = 0; i < other._size; i++) {
			_array[i] = other._array[i];
		}
		_size = other._size;
	}

	SimpleVector<T>& operator = (const SimpleVector<T>& other) {
		reserve(other._capacity);
		for (int i = 0; i < other._size; i++) {
			_array[i] = other._array[i];
		}
		_size = other._size;
		return *this;
	}

	SimpleVector(std::initializer_list<T> objects) {
		reserve(16 > objects.size() ? 16 : objects.size());
		for (const T& obj : objects) {
			push_back(obj);
		}
	}

	int size() const {
		return _size;
	}

	bool empty() const {
		return _size == 0;
	}

	T& operator[] (int index) const {
		return _array[index];
	}

	T& back() const {
		return _array[_size - 1];
	}

	void clear() {
		_size = 0;
	}

	void push_back(const T& obj) {
		if (_size == _capacity) {
			reserve(_capacity * 2 + 1);
		}

		_array[_size++] = obj;
	}

	void pop_back() {
		_size--;
	}

	void reserve(int capacity) {
		if (capacity <= _capacity) {
			return;
		}

		T* new_array = new T[capacity];
		for (int i = 0; i < _size; i++) {
			new_array[i] = std::move(_array[i]);
		}

		_capacity = capacity;
		std::swap(_array, new_array);
		if (new_array) {
			delete[] new_array;
		}
	}

	T* begin() const {
		return _array;
	}

	T* end() const {
		return _array + _size;
	}

	~SimpleVector() {
		if (_array) {
			delete[] _array;
			_array = nullptr;
		}
	}

private:
	T* _array = nullptr;
	int _size = 0;
	int _capacity = 0;
};
