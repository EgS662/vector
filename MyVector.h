#pragma once
#include<iostream>
#include<initializer_list>
#include <algorithm>


template <typename T>
class MyVector {
	T* data{};
	size_t size{ 0 };
	size_t capacity{ 0 };
	void realocation(size_t cap);
public:
	MyVector();
	MyVector(T number);
	MyVector(const MyVector& rhs);
	MyVector(std::initializer_list<T> list);
	MyVector(MyVector&& rhs);
	~MyVector();
	void push_back(const T& d);
	void push_back(T&& d);
	template<typename ...Args>
	void emplace_back(Args&&... args);
	void pop_back();
	size_t Size();
	size_t Capacity();
	T& operator[](int e);
	T* begin();
	T* end();
	void erase();
	void reserve(size_t t);
	void insert(size_t index, T chislo);
	void swap(MyVector& y);
	void shrink_to_fit();
};


template <typename T>
void MyVector<T>::realocation(size_t cap) {
	capacity = cap;
	T* tmp = static_cast<T*>(malloc(sizeof(T)*cap));
	for (int i = 0; i < size; i++) {
		new(&tmp[i])T{ data[i] };
	}
	for (auto i{ 0 }; i < size; ++i) {
		data[i].~T();
	}
	free(data);
	data = tmp;

}

template <typename T>
MyVector<T>::MyVector() :data{ nullptr }, size{ 0 }, capacity{ 0 } {}

template <typename T>
MyVector<T>::MyVector(T number) :data{ static_cast<T*>(malloc(sizeof(T))) }, size{ 1 }, capacity{ 1 }{
	new(&data[0])T{ number };
}

template <typename T>
MyVector<T>::MyVector(const MyVector& rhs) : size{ rhs.size }, capacity{ rhs.capacity } {
	data = { static_cast<T*>(malloc(sizeof(T)*capacity)) };
	if (std::is_fundamental<T>::value) {
		memcpy(data, rhs.data, sizeof(T)*rhs.capacity);

	}
	else {
		for (int i{}; i < size; i++) {
			new(&data[i])T{ rhs.data[i] };
		}
	}

}

template <typename T>
MyVector<T>::MyVector(std::initializer_list<T> list) :data{ static_cast<T*>(malloc(sizeof(T)*list.size())) }, size{ list.size() }, capacity{ list.size() }{
	auto dataCopy{ data };
	auto begin{ list.begin() };
	if (std::is_fundamental<T>::value) {
		memcpy(dataCopy, list.begin(), sizeof(T)*size);
	}
	else {
		while (begin != list.end()) {
			new(&dataCopy)T{ *begin++ };
			dataCopy++;
		}
	}
}

template <typename T>
MyVector<T>::MyVector(MyVector&& rhs) :data{ rhs.data }, size{ rhs.size }, capacity{ rhs.capacity } {
	rhs.data = nullptr;
	rhs.size = 0;
	rhs.capacity = 0;
}

template <typename T>
MyVector<T>::~MyVector() {
	if (data != nullptr) {
		for (int i = 0; i < size; i++) {
			data[i].~T();
		}
	}
	free(data);
}

template <typename T>
void MyVector<T>::push_back(const T& d) {
	if (size == capacity) {
		realocation(capacity * 2);
	}
	new(&data[size++])T{ d };
}

template <typename T>
void MyVector<T>::push_back(T&& d) {
	if (size == capacity) {
		realocation(capacity * 2);
	}
	new(&data[size++])T{ std::move(d) };
}

template <typename T>
template<typename ...Args>
void MyVector<T>::emplace_back(Args&&... args) {
	if (size == capacity) {
		realocation(capacity * 2);
	}
	new(&data[size++])T{ std::forward<Args>(args)... };
}

template <typename T>
void MyVector<T>::pop_back() {
	data[size--].~T();
}

template <typename T>
size_t MyVector<T>::Size() {
	return size;
}

template <typename T>
T& MyVector<T>::operator[](int e) {
	return data[e];
}

template <typename T>
T* MyVector<T>::begin() {
	return data;
}

template <typename T>
T* MyVector<T>::end() {
	return data + size;
}

template <typename T>
void MyVector<T>::erase() {
	for (size_t i = 0; i < size; i++) {
		data[i].~T();
	}
	size = 0;
	capacity = 0;
	free(data);
}


template <typename T>
void MyVector<T>::reserve(size_t t) {
	if (t > capacity) {
		realocation(t);
	}
}

template <typename T>
void MyVector<T>::insert(size_t index, T chislo) {
	size_t indexFound{};
	for (size_t i = 0; i < size; i++) {
		if (index == i) {
			indexFound = i;
			break;
		}
	}
	if (size == capacity) {
		reserve(capacity * 2);
	}
	for (size_t i = size; i >= indexFound; i--) {
		data[i + 1] = data[i];

	}
	size++;
	data[indexFound].~T();
	new(&data[indexFound])T{ chislo };

}

template <typename T>
void MyVector<T>::swap(MyVector& y) {
	if (y.size == size) {
		for (size_t i = 0; i < size; i++) {
			std::swap(data[i], y[i]);
		}
		std::swap(size, y.size);
		return;
	}
	if (capacity != y.capacity) {
		if (capacity > y.capacity) {
			y.reserve(capacity);
		}
		if (capacity < y.capacity) {
			reserve(y.capacity);
		}
		for (size_t i = 0; i < size; i++) {
			std::swap(data[i], y[i]);
		}
	}
	std::swap(size, y.size);

}

template <typename T>
size_t MyVector<T>::Capacity() {
	return capacity;
}

template <typename T>
void MyVector<T>::shrink_to_fit() {
	if (capacity > size) {
		size_t t;
		t = capacity - size;
		realocation(capacity - t);
	}
}