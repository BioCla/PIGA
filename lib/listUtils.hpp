#ifndef LISTS
#define LISTS

#include "../lib/entity.hpp"

template <class T> struct Node{
    T data;
    Node *next;
};

template <class T> class List{
    protected:
        Node<T> *head; 
    public:
        List();     //crea lista vuota
        bool isEmpty();     //ritorna true se la lista è vuota, false altrimenti
        int listLenght();      //ritorna la lunghezza della lista
        void headInsert(T element);     //inserisce un elemento in testa
        void tailInsert(T element);     //inserisce un elemento in coda
        void removeElement(T element);      //rimuove un elemento
};
#endif
//typedef Node *pnode;
