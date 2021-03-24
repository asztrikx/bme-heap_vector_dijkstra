#ifndef VECTOR_H
#define VECTOR_H
#include "container.h"
#include <initializer_list>
#include <cassert>
#include <iostream>

namespace Container {

template <typename T>
class Vector {
	/// Allocated memory's size
	int capacity;

	/// _length is the number of used elements in `data`
	int _length;

	/// T[capacity]
	T *data = nullptr;

	/// @brief Changes `data`-s *allocated* size
	/// @param capacityNew `data`'s new *allocated* size
	/// @exception Container::ExceptionDataLoose capacityNew < length
	void realloc(int capacityNew) {
		if (capacityNew < _length) {
			throw Exception::DataLoose();
		}

		capacity = capacityNew;
		T *dataNew = new T[capacity];
		for (int i = 0; i < _length; i++) {
			dataNew[i] = data[i];
		}
		delete[] data;
		data = dataNew;
	}
	void copy(Vector<T> const &vector) {
		delete[] data;
		_length = vector.length();
		capacity = vector.capacity;
		data = new T[vector.capacity];
		for (int i = 0; i < vector.length(); i++) {
			data[i] = vector.data[i];
		}
	}

  public:
	/// @brief Returns the number of stored data
	virtual int length() const {
		return _length;
	}

	/// @brief Clears then fills with `value`
	/// @param size number of elements to insert
	/// @param value value to be inserted
	virtual void resize(int size, T const &value) {
		clear();
		for (int i = 0; i < size; i++) {
			pushBack(value);
		}
	}

	/// @brief Deletes data, then recreates it with `capacity` = 1
	virtual void clear() {
		delete[] data;
		_length = 0;
		capacity = 1;
		data = new T[capacity];
	}

	/// @brief data[length] = value. Capacity is doubled if full
	/// @param size number of elements to insert
	/// @param value value to be inserted
	virtual void pushBack(T const &value) {
		if (capacity == _length) {
			realloc(2 * capacity);
		}

		_length++;
		data[_length - 1] = value;
	}

	/// @brief Marks last element as garbage. Decreases capacity if needed
	/// @param size number of elements to insert
	/// @param value value to be inserted
	/// @return last element
	virtual T popBack() {
		T result = data[_length - 1];
		_length--;

		if (capacity == 4 * _length) {
			realloc(capacity / 2);
		}
		return result;
	}

	//operator=
	virtual Vector<T> &operator=(Vector<T> const &vector) {
		copy(vector);
		return *this;
	}
	virtual Vector<T> &operator=(std::initializer_list<T> const &values) {
		clear();
		for (auto item = values.begin(); item != values.end(); item++) {
			pushBack(*item);
		}
		return *this;
	}

	//operator[]
	virtual T &operator[](int index) const {
		if (index >= _length || index < 0) {
			throw Exception::IndexOutofbounds();
		}
		return data[index];
	}

	//operator+
	virtual Vector<T> operator+(T const &value) const {
		Vector<T> vector;
		vector.copy(*this);
		vector.pushBack(value);
		return vector;
	}
	virtual Vector<T> operator+(Vector<T> const &vector) const {
		Vector<T> vectorNew;
		vectorNew.copy(*this);
		for (int i = 0; i < vector.length(); i++) {
			vectorNew.pushBack(vector[i]);
		}
		return vectorNew;
	}

	//operator+=
	virtual Vector<T> &operator+=(T const &value) {
		pushBack(value);
		return *this;
	}
	virtual Vector<T> &operator+=(Vector<T> const &vector) {
		for (int i = 0; i < vector.length(); i++) {
			pushBack(vector[i]);
		}
		return *this;
	}

	//ctor, dtor
	Vector() {
		clear();
	}
	Vector(int size, T def) {
		resize(size, def);
	}
	virtual ~Vector() {
		delete[] data;
	}

	//copy ctor
	Vector(Vector<T> const &vector) {
		copy(vector);
	}

	//init list ctor
	Vector(std::initializer_list<T> const &values) {
		clear();
		for (auto item = values.begin(); item != values.end(); item++) {
			pushBack(*item);
		}
	}

	//unit test
	static void Test() {
		//= test
		Vector<T> a;
		Vector<T> b;
		b = a;

		//copy ctor test
		Vector<T> c;
		Vector<T> d = c;

		//init list ctor test
		Vector<int> values({1, 2, 3, 4, 5, 6});
		for (int i = 0; i < 6; i++) {
			assert(values[i] == i + 1);
		}

		//= init list test
		Vector<int> e = {1, 2, 3, 5, 6};
		for (int i = 0; i < 6; i++) {
			assert(values[i] == i + 1);
		}

		//= misc test
		values = Vector({1, 2}) + 3 + 4 + Vector({5}) + Vector({6, 7, 8, 9, 10});
		values += {11, 12, 13};
		for (int i = 0; i < 13; i++) {
			assert(values[i] == i + 1);
		}
	}
};

template <typename T>
Vector<T> operator+(T const &value, Vector<T> const &vector) {
	return vector + value;
}

template <typename T>
std::ostream &operator<<(std::ostream &stream, Vector<T> const &vector) {
	stream << "[" << vector.length() << "]";
	stream << "(";
	for (int i = 0; i < vector.length(); i++) {
		stream << vector[i];
		if (i < vector.length() - 1) {
			stream << ", ";
		}
	}
	stream << ")";

	return stream;
}

} // namespace Container

#endif