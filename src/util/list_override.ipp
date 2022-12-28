template <typename T>
T List<T>::front() {
	if (head)
		return head->data;
	return T();
}

template <typename T>
int List<T>::size() {
	int count = 0;
	Node* current = head;
	while (current) {
		count++;
		current = current->next;
	}
	return count;
}

template <typename T>
bool List<T>::empty() {
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
T List<T>::at(int index) {
	if (index < 0 || index >= size())
		return T();

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
void List<T>::remove(int index) {
	if (index < 0 || index >= size())
		return;
	else if (index == 0)
		pop_front();
	else {
		Node* current = head;
		for (int i = 0; i < index - 1; i++)
			current = current->next;
		Node* temp = current->next;
		current->next = current->next->next;
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
	if (index < 0 || index > size())
		return;
	else if (index == 0)
		push_front(data);
	else {
		Node* newNode = new Node(data);
		Node* current = head;
		for (int i = 0; i < index - 1; i++)
			current = current->next;
		newNode->next = current->next;
		current->next = newNode;
	}
}