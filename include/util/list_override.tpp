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
		struct FindResult {
			int index;
			Node* node;
			FindResult(int index, Node* node) : index(index), node(node) {}
		};

		List() : head(nullptr) {}
		~List() { delete head; }
		int size();
		T front();
		bool empty();
		void clear();
		void reverse();
		T at(int index);
		void pop_back();
		void pop_front();
		void print() const;
		void print(std::function<void(const T&)> printFn) const;
		void remove(int index);
		void push_back(T data);
		void push_front(T data);
		FindResult find(T data);
		void insert(int index, T data);
};

#endif

#include "../../src/util/list_override.ipp"
