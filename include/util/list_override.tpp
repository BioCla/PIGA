#include "../assets/curses_lib_selector.hpp"

#ifndef LIST_HPP
#define LIST_HPP

template <typename T> 
class List {
	private:
		class Node {
			public:
				T data;
				Node* next;
				Node(T data) : data(data), next(nullptr) {}
				~Node() { delete next; }
		};
		Node* head;

	public:
		List() : head(nullptr) {}
		~List() { delete head; }
		T front();
		int size();
		bool empty();
		void clear();
		void reverse();
		T at(int index);
		void pop_back();
		void pop_front();
		void remove(int index);
		void push_back(T data);
		void push_front(T data);
		void insert(int index, T data);

		friend std::ostream& operator<<(std::ostream& out, const List<T>& list) {
			Node* current = list.head;
			while (current) {
				out << current->data << " ";
				current = current->next;
			}
			return out;
		}
};

#endif

#include "../../src/util/list_override.ipp"