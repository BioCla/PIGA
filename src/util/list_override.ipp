template <typename T>
T List<T>::front() const {
	if (head)
		return head->data;
	return T();
}

template <typename T>
int List<T>::size() const {
	int count = 0;
	Node* current = head;
	while (current) {
		count++;
		current = current->next;
	}
	return count;
}

template <typename T>
bool List<T>::empty() const {
	return head == nullptr;
}

template <typename T>
void List<T>::clear() {
	delete head;
	head = nullptr;
}

template <typename T>
void List<T>::reverse() {
	Node* prev = nullptr;
	Node* current = head;
	Node* next = nullptr;
	while (current) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	head = prev;
}

template <typename T>
T List<T>::at(int index) const {
	if (empty() || index < 0 || index >= size()) return T();
	Node* current = head;
	for (int i = 0; i < index; i++)
		current = current->next;
	return current->data;
}

template <typename T>
void List<T>::pop_back() {
	if (head == nullptr)
		return;
	else if (head->next == nullptr) {
		delete head;
		head = nullptr;
	}
	else {
		Node* current = head;
		while (current->next->next)
			current = current->next;
		delete current->next;
		current->next = nullptr;
	}
}

template <typename T>
void List<T>::pop_front() {
	if (head == nullptr)
		return;
	Node* temp = head;
	head = head->next;
	delete temp;
}

template <typename T>
bool List<T>::contains(T data) const {
	Node* current = head;
	while (current) {
		if (current->data == data)
			return true;
		current = current->next;
	}
	return false;
}

template <typename T>
void List<T>::remove(int index) {
	if (empty() || index < 0 || index >= size()) return;
	Node* current = head;
	if (index == 0) {
		head = current->next;
		delete current;
	} else {
		for (int i = 0; i < index - 1; i++)
			current = current->next; 
		Node* temp = current->next;
		current->next = temp->next;
		delete temp;
	}
}

template <typename T>
void List<T>::push_back(T data) {
	Node* newNode = new Node(data);
	if (head == nullptr)
		head = newNode;
	else {
		Node* current = head;
		while (current->next)
			current = current->next;
		current->next = newNode;
	}
}

template <typename T>
void List<T>::push_front(T data) {
	Node* newNode = new Node(data);
	newNode->next = head;
	head = newNode;
}

template <typename T>
void List<T>::insert(int index, T data) {
    if (index < 0)
        return;
    if (index == 0 || empty()) {
        push_front(data);
        return;
    }
    if (index >= size()) {
        push_back(data);
        return;
    }
    Node* newNode = new Node(data);
    Node* current = head;
    for (int i = 0; i < index - 1; i++)
        current = current->next;
    newNode->next = current->next;
    current->next = newNode;
}
