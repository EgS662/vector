#include<iostream>
#include<initializer_list>
#include <algorithm>
template <typename T>
class MyVector {
	T* data{};
	size_t size{ 0 };
	size_t capacity{ 0 };	
	void realocation(size_t cap) {
		std::cout << " realocation("<<cap<<")\n";
		capacity = cap;

		T* tmp = static_cast<T*>(malloc(sizeof(T)*cap));
		for (int i = 0; i < size; i++) {
			new(&tmp[i])T{ data[i] };
		}
		for (auto i{ 0 }; i < size; ++i) {
			data[i].~T();
		}
		//free(data);
		data = tmp;

	}
public:
	MyVector() :data{ nullptr }, size{ 0 }, capacity{ 0 } {

	}
	MyVector(T number) :data{ static_cast<T*>(malloc(sizeof(T))) }, size{ 1 }, capacity{ 1 }{
		new(&data[0])T{ number };
	}
	MyVector(const MyVector& rhs) : size{ rhs.size }, capacity{ rhs.capacity } {
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

	MyVector(std::initializer_list<T> list) :data{ static_cast<T*>(malloc(sizeof(T)*list.size())) }, size{ list.size() }, capacity{ list.size() }{
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

	MyVector(MyVector&& rhs) :data{ rhs.data }, size{ rhs.size }, capacity{ rhs.capacity } {
		rhs.data = nullptr;
		rhs.size = 0;
		rhs.capacity = 0;
	}
	~MyVector() {
		if (data != nullptr) {
			for (int i = 0; i < size; i++) {
				data[i].~T();
			}
		}
		free(data);
	}

	void push_back(const T& d) {
		if (size == capacity) {
			realocation(capacity * 2);
		}
		new(&data[size++])T{ d };//placement new
	}

	void push_back(T&& d) {
		if (size == capacity) {
			realocation(capacity * 2);
		}
		new(&data[size++])T{ std::move(d) };//placement new
	}
	template<typename ...Args>
	void emplace_back(Args&&... args) {
		if (size == capacity) {
			realocation(capacity * 2);
		}
		new(&data[size++])T{ std::forward<Args>(args)... };
	}


	void pop_back() {
		data[size--].~T();
	}

	void print() {
		for (int i = 0; i < size; i++) {
			std::cout << data[i] << " ";
		}
		std::cout << std::endl;
	}
	size_t Size() {
		return size;
	}
	T& operator[](int e) {
		return data[e];
	}
	T* begin() {
		return data;
	}
	T* end() {
		return data + size;
	}
	void erase() {
		for (size_t i = 0; i < size; i++) {
			data[i].~T();
		}
		size = 0;
		capacity = 0;
		free(data);
	}
	void reserve(size_t t) {
		if (t > capacity) {
			realocation(t);
		}
	}
	void insert(size_t index, T chislo) {
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
		for (size_t i =size; i >= indexFound; i--) {
			data[i+1] = data[i];

		}
		size++;
		data[indexFound].~T();
		new(&data[indexFound])T{ chislo };

	}
	void swap(MyVector& y) {
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
	void metod() {
		std::cout << capacity << std::endl;
	}
	void capacty() {
		capacity = 100;
	}
	void shrink_to_lift() {
		if (capacity > size) {
			size_t t;
			t = capacity - size;
			realocation(capacity-t);
		}
	}
};
class A
{
	int x{};
public:
	A() {
		std::cout << "A()\n";
	}
	A(int xx) :x{ xx } {
		std::cout << "A(int " << xx << ")\n";
	}
	A(double xx) :x{ static_cast<int>(xx) } {
		std::cout << "A(double " << xx << ")\n";
	}
	A(const A& rhs) :x{ rhs.x } {
		std::cout << "A(const A& rhs)\n";
	}
	A& operator=(const A& rhs) {
		x = rhs.x;
		std::cout << "A& operator=(const A& rhs)\n";
		return *this;
	}

	A(A&& rhs) {
		std::cout << "A(A&& rhs)\n";
	}

	~A() {
		std::cout << "~A\n";
	}

};



int main() {
	//MyVector<A> Vect{ A{23}, A{233} };
	//////Vect.push_back(25.5);
	////A a{ 55 };
	////Vect.push_back(std::move(a));
	MyVector<int> r{ 9,3,7,5 }; 
	MyVector<int> t{ 7 };
	//r.print();
	///*t.print();*/
	//r.insert(1, 0);
	//r.insert(1, 2);
	//r.insert(1, 4);
	//r.insert(1, 8);
	//std::cout << "-------------\n";
	//r.insert(1, 6);
	//std::sort(r.begin(), r.end(), [](int a, int b) {return a < b; });
	//r.print();
	/*r.swap(t);
	std::cout << "Swap\n";
	r.print();
	t.print();*/
	///*for (auto i = 0; i < r.Size();i++) {
	//	std::cout << r[i] << " ";
	//}*/
	r.insert(1, 4);
	r.push_back(5);
	r.push_back(9);
	r.emplace_back(9);
	r.push_back(6);
	r.print();
	/*r.print();*/
	/*r.swap(t, r);
	r.print();
	t.print();*/
	//r.capacty();
	r.metod();
	r.shrink_to_lift();
	r.metod();
	r.push_back(6);
	r.metod();
}