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

template <typename T> int List<T>::listLenght(){
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

//template class List<Item>;

/*
template <typename T> void List<T>::tailInsert(T element){
    if (head == NULL){
        head = new Node<T>();
        head->next=NULL;
        head->data=element;
    }
    else{
        Node<T> *tmp = head;
        while (tmp->next!=NULL) tmp=tmp->next;
        tmp->next = new Node<T>();
        tmp=tmp->next;
        tmp->next = NULL;
        tmp->data = element;
    }
}
*/

template <typename T> Node<T> *List<T>::getHead() {
    return head;
}
