#include <chrono>
using namespace std::chrono;

template <typename T> Node<T>::Node(){
    this->next=NULL;
}

template <typename T> T* Node<T>::getData() {
    return &data;
}

template <typename T> Node<T>* Node<T>::getNext() {
    return next;
}

template <typename T> List<T>::List(){
    this->head = NULL;
}

template <typename T> bool List<T>::isEmpty(){
    return (this->head==NULL);
}

template <typename T> int List<T>::listLength() const{
    Node<T> *tmp = this->head;
    int k=0;
    while (tmp!=NULL){
        tmp=tmp->next;
        k++;
    }
    return k;
}

template <typename T> void List<T>::headInsert(T element){
    Node<T> *tmp = new Node<T>();
    tmp->data=element;
    tmp->next=head;
    head=tmp;
}

//Rimuove l'elemento selezionato dalla lista
template <typename T> void List<T>::removeElement(int &tracker) { 
	for (int i = 1; head != NULL; i++) {
		if (i == tracker - 1) {
			head->next = (head->next)->next;
		}
		headInsert(head->data);
		head = head->next;
	}
	tracker--;
}

template <typename T> Node<T> *List<T>::getHead() {
    return head;
}


template <typename T> void List<T>::spawnEntities(){
    Node<T> *tmp = this->head;
    while (tmp!=NULL) {
        tmp->data.spawn(tmp->data.getCurrentPosition());
        tmp=tmp->next;
    }    
}

template <typename T> void List<T>::moveEntities(system_clock::time_point time_now){
    Node<T> *tmp = this->head;
    while (tmp!=NULL) {
        tmp->data.checkIfTimeToMove(time_now);
        tmp=tmp->next;
    }    
}


template <typename T> void List<T>::removeDeadEntities(){
    if (head==NULL) return;
    else if((head->next==NULL)&&(!head->data.isAlive())){
        head->data.deleteIcon();
        delete head;
        head = NULL;
    }
    else{
        Node<T> *tmp = head;
        Node<T> *tmpafter = head->next;
        while(tmpafter!=NULL){
            if(!tmpafter->data.isAlive()){
                tmp->next = tmpafter->next;
                tmpafter->data.deleteIcon();
                delete tmpafter;
            }
            else{
                tmp = tmpafter;
            }
                tmpafter = tmp->next;
        }
        if (!head->data.isAlive()){
            Node<T> *tmp = head->next;
            head->data.deleteIcon();
            delete head;
            head=tmp;
        }

    }
}



// successive funzioni necessarie per i grafi
template <typename T>
void List<T>::remove(int index) {
	if (isEmpty() || index < 0 || index >= listLength()) return;
	Node<T>* current = head;
	if (index == 0) {
		head = current->next;
		delete current;
	} else {
		for (int i = 0; i < index - 1; i++)
			current = current->next; 
		Node<T>* temp = current->next;
		current->next = temp->next;
		delete temp;
	}
}

template <typename T>
void List<T>::push_back(T data) {
	Node<T>* newNode = new Node<T>();
    newNode->data = data;
	if (head == nullptr)
		head = newNode;
	else {
		Node<T>* current = head;
		while (current->next)
			current = current->next;
		current->next = newNode;
	}
}

template <typename T>
bool List<T>::contains(T data) const {
	Node<T>* current = head;
	while (current) {
		if (*(current->getData()) == data)
			return true;
		current = current->next;
	}
	return false;
}
