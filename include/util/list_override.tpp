#ifndef LIST_HPP
#define LIST_HPP

template <typename T> 
class List {
	private:
		class Node {
			public:
				T data;
				Node* next;
				Node(T data) : data(data) { next = nullptr; }
				~Node() { next = nullptr; delete next; }
		};
		Node* head;

	public:
		List() : head(nullptr) {}
		~List() {
			Node* current = head;
			while (current) {
				Node* next = current->next;
				delete current;
				current = next;
			}
			head = nullptr;
		}
		T front() const;
		int size() const;
		bool empty() const;
		void clear();
		void reverse();
		T at(int index) const;
		void pop_back();
		void pop_front();
		bool contains(T data) const;
		void remove(int index);
		void push_back(T data);
		void push_front(T data);
		void insert(int index, T data);

		friend std::ostream& operator<<(std::ostream& out, const List<T>& list) {
			out << "[";
			if (list.empty()) {
				out << "N/D"; 
				return out << "]";
			}
			Node* current = list.head;
			while (current) {
				out << current->data;
				current = current->next;
				if (current) out << ", ";
			}
			return out << "]";
		}

		List(const List& other) {
			head = nullptr;
			Node* current = other.head;
			while (current) {
				push_back(current->data);
				current = current->next;
			}
		}

		List& operator=(const List& other) {
			if (this != &other) {
				clear();
				Node* current = other.head;
				while (current) {
					push_back(current->data);
					current = current->next;
				}
			}
			return *this;
		}

		T& operator[](int index) {
			if (index < 0 || index >= size()) {
				throw std::out_of_range("Index out of range");
			}
			Node* current = head;
			for (int i = 0; i < index; i++) {
				current = current->next;
			}
			return current->data;
		}

		const T& operator[](int index) const {
			if (index < 0 || index >= size()) {
				throw std::out_of_range("Index out of range");
			}
			Node* current = head;
			for (int i = 0; i < index; i++) {
				current = current->next;
			}
			return current->data;
		}
};

#include "../../src/util/list_override.ipp"

#endif