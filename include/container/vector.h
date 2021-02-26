#ifndef VECTOR_H
#define VECTOR_H
#include <initializer_list>

namespace Container {

template <typename T>
class Vector {
	int capacity;
	T *data = nullptr;

	void realloc(int length, int capacityNew) {
		if (capacityNew < length) {
			throw "Vector realloc loosing data";
		}

		T *dataNew = new T[capacityNew];
		for (int i = 0; i < length; i++) {
			dataNew[i] = data[i];
		}
		delete[] data;
		data = dataNew;
	}

  public:
	int length;
	Vector() {
		clear();
	}
	Vector(T def, int size) {
		clear();
		for (int i = 0; i < size; i++) {
			pushBack(def);
		}
	}
	Vector(std::initializer_list<T> values) {
		clear();
		for (auto item = values.begin(); item != values.end(); item++) {
			pushBack(*item);
		}
	}
	~Vector() {
		delete[] data;
	}
	void clear() {
		delete[] data;
		length = 0;
		capacity = 1;
		data = new T[1];
	}
	T &operator[](int index) {
		if (index >= length) {
			throw "Vector[] out of bounds";
		}
		return data[index];
	}
	void pushBack(T value) {
		if (capacity == length) {
			capacity *= 2;
			realloc(length, capacity);
		}

		data[length] = value;
		length++;
	}
	T popBack() {
		T result = data[length - 1];
		length--;

		if (length * 4 == capacity) {
			capacity /= 2;
			realloc(length, capacity);
		}
		return result;
	}
};

} // namespace Container

#endif