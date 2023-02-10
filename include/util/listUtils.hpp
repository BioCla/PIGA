#ifndef LISTS
#define LISTS
#include <cstddef>
#include <chrono>
#include "../assets/position.hpp"
#include "../assets/curses_lib_selector.hpp"

template <typename T> class Node{

    protected:
        T data;
        Node<T> *next;
        template <typename U> friend class List;
        
    public:
        Node();
        T* getData();
        Node<T>* getNext();
        ~Node() { next = nullptr; delete next; }
};

template <typename T> class List{
    protected:
        Node<T> *head; 
    public:
        List();     //crea lista vuota
        bool isEmpty();     //ritorna true se la lista è vuota, false altrimenti
        int listLength() const;      //ritorna la lunghezza della lista
        void headInsert(T element);     //inserisce un elemento in testa

		void removeElement(int& tracker);	//rimuove un elemento dalla lista

        void moveEntities(std::chrono::_V2::system_clock::time_point time_now);
        void spawnEntities();
        void removeDeadEntities();
        void inline refreshEnemyTarget(Position p1);
        Node<T> *getHead();
        void remove(int index);
        void push_back(T data);
        bool contains(T data) const;
};


#include "../src/util/listUtils.tpp"

#endif
