
#include "../lib/entity.hpp"
#include "../lib/enemy.hpp"
#include <chrono>

template <typename T> Node<T>::Node(){
    this->next=NULL;
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

template <typename T> void List<T>::removeElement(T *element){
    if (head==NULL){
        return;
    }
    else if(&head->data==element){
        Node<T> *tmp=head->next;
        delete head;
        head = tmp;
    }
    else{
        bool flag = false;
        Node<T> *tmp = head;
        Node<T> *tmpafter = head->next;
        while((!flag)&&(tmpafter!=NULL)){
            if(&tmpafter->data==element){
                tmp->next = tmpafter->next;
                flag = true;
                delete tmpafter;
            }
            else{
                tmp = tmpafter;
                tmpafter=tmpafter->next;
            }
        }
    }

}

template <> void List<Enemy>::spawnEnemies(){
    Node<Enemy> *tmp = this->head;
    while (tmp!=NULL) {
        tmp->data.spawn(tmp->data.getCurrentPosition());
        tmp=tmp->next;
    }
}

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


