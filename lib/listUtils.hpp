#ifndef LISTS
#define LISTS
#include <cstddef>
#include <chrono>
#include "../assets/position.hpp"

template <typename T> class Node{

    protected:
        T data;
        Node<T> *next;
        template <typename U> friend class List;
    public:
        Node();
        T* getData();
        Node<T>* getNext();
};

/**
 * @brief Template for a linked list of type `T`
*/
template <typename T> class List{
    protected:
        Node<T> *head; 
    public:
        List();     //crea lista vuota
        bool isEmpty();     //ritorna true se la lista è vuota, false altrimenti
        int listLength();      //ritorna la lunghezza della lista
        void headInsert(T element);     //inserisce un elemento in testa

				void removeElement(int& tracker);	//rimuove un elemento dalla lista
				void inline spawnEntities(); //spawna le entità

        void inline spawnEnemies();
        void moveEntities(std::chrono::_V2::system_clock::time_point time_now);
        void inline refreshEnemyTarget(Position p1);
        void inline refreshEnemyProj(std::chrono::_V2::system_clock::time_point time_now);
		// void tailInsert(T element);     //inserisce un elemento in coda
        void removeDeadEntities();
            //Funzioni debug
        void inline killEnemy(int o);
        Node<T> *getHead();
};


#include "../src/listUtils.tpp"

#endif
