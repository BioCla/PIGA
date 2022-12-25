template <typename T> 
void List<T>::push_back(T data) {
	if (head == nullptr) {
		head = new Node(data);
		return;
	}

	Node *current = head;
	while (current->next != nullptr) {
		current = current->next;
	}
	current->next = new Node(data);
}

template <typename T> 
void List<T>::pop_front() {
	if (head == nullptr) {
		return;
	}

	Node* old_head = head;
	head = head->next;
	if (head != nullptr) {
		head->next = nullptr;
	}
	delete old_head;
}

template <typename T> 
int List<T>::size() {
	int count = 0;
	Node *current = head;
	while (current != nullptr) {
		count++;
		current = current->next;
	}
	return count;
}

template <typename T> 
bool List<T>::empty() {
	return (head == nullptr);
}

template <typename T> 
T List<T>::front() {
	if (head == nullptr) {
		return T();
	}
	return head->data;
}

template <typename T> 
void List<T>::push_front(T data) {
	Node* new_head = new Node(data);
	new_head->next = head;
	head = new_head;
}

template <typename T> 
void List<T>::pop_back() {
	if (head == nullptr) {
		return;
	}

	if (head->next == nullptr) {
		delete head;
		head = nullptr;
		return;
	}

	Node* current = head;
	while (current->next->next != nullptr) {
		current = current->next;
	}
	delete current->next;
	current->next = nullptr;
}

template <typename T> 
typename List<T>::FindResult List<T>::find(T data) {
	int index = 0;
	Node* current = head;
	while (current != nullptr) {
		if (current->data == data) {
			return FindResult(index, current);
		}
		index++;
		current = current->next;
	}
	return FindResult(-1, nullptr);
}

template <typename T> 
T List<T>::at(int index) {
	int current_index = 0;
	Node* current = head;
	while (current != nullptr) {
		if (current_index == index) {
			return current->data;
		}
		current_index++;
		current = current->next;
	}
	return T();
}

template <typename T> 
void List<T>::clear() {
    delete head;
    head = nullptr;
}

template <typename T>
void List<T>::insert(int index, T data) {
	if (index < 0 || index > size()) return;
		Node* newNode = new Node(data);
	if (empty() || index == 0) {
		newNode->next = head;
		head = newNode;
	} else {
		Node* current = head;
		for (int i = 0; i < index - 1; ++i) {
			current = current->next;
		}
		newNode->next = current->next;
		current->next = newNode;
	}
}

template <typename T>
	void List<T>::remove(int index) {
	if (index < 0 || index >= size()) return;
	if (index == 0) {
		Node* toDelete = head;
		head = head->next;
		delete toDelete;
	} else {
		Node* current = head;
		for (int i = 0; i < index - 1; ++i) {
			current = current->next;
		}
		Node* toDelete = current->next;
		current->next = toDelete->next;
		delete toDelete;
	}
}


template <typename T> 
void List<T>::reverse() {
    Node* prev = nullptr;
    Node* curr = head;
    Node* next = nullptr;
    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

template <typename T>
void List<T>::print() const {
	Node* current = head;
	while(current != nullptr) {
		std::cout << current->data;
		current = current->next;
		if (current != nullptr)
			std::cout << ", ";
	}
	std::cout << std::endl;
}

template <typename T>
void List<T>::print(std::function<void(const T&)> printFn) const {
	Node* current = head;
	while(current != nullptr) {
		printFn(current->data);
		current = current->next;
	}
}
