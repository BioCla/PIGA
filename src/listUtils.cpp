#include "../lib/listUtils.hpp"
#include <cstddef>

template <class T> List<T>::List(){
    head = NULL;
}

template <class T> bool List<T>::isEmpty(){
    return (head==NULL);
}

template <class T> int List<T>::listLenght(){
    Node<T> *tmp = head;
    int k=0;
    while (tmp!=NULL){
        tmp=tmp->next;
        k++;
    }
    return k;
}

template <class T> void List<T>::headInsert(T element){
    Node<T> *tmp = new Node<T>();
    tmp->data=element;
    tmp->next=head;
    head=tmp;
}

template <class T> void List<T>::tailInsert(T element){
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

template <class T> void List<T>::removeElement(T element){
    if (head==NULL){
        return;
    }
    else if(head->data==element){
        Node<T> *tmp=head->next;
        delete head;
        head = tmp;
    }
    else{
        bool flag = false;
        Node<T> *tmp = head;
        Node<T> *tmpafter = head->next;
        while((!flag)&&(tmpafter!=NULL)){
            if(tmpafter->data==element){
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



/*
ignorare tentativi passati

template <class T>
*Node Node<T>::removeFromList(Node *phead, T d){
    if (phead==NULL) return phead;
    else if (phead->data==d){
        Node *tmp=phead->next;
        delete phead;
        return tmp;
    }
    else{
        bool flag=false;
        Node *tmp = phead;
        Node *tmpafter = phead->next;
        while((!flag) && (tmpafter!=NULL)){
            if(tmpafter->data==d){
                tmp->next=tmpafter->next;
                flag = true;
                delete tmpafter;
            }
            else{
                tmp = tmpafter;
                tmpafter = tmpafter->next;
            }
        }
    }
    return (phead);
}
*/
