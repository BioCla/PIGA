#ifndef LISTS
#define LISTS
#include <cstddef>
#include <chrono>

template <typename T> class Node{

    protected:
        T data;
        Node<T> *next;
        template <typename U> friend class List;
    public:
        Node();
};

template <typename T> class List{
    protected:
        Node<T> *head; 
    public:
        List();     //crea lista vuota
        bool isEmpty();     //ritorna true se la lista è vuota, false altrimenti
        int listLenght();      //ritorna la lunghezza della lista
        void headInsert(T element);     //inserisce un elemento in testa
        void inline spawnEnemies();
        void moveEntities(std::chrono::_V2::system_clock::time_point time_now);
        void inline enemyShooting(std::chrono::_V2::system_clock::time_point time_now);
        void inline refreshEnemyProj(std::chrono::_V2::system_clock::time_point time_now);
//        void tailInsert(T element);     //inserisce un elemento in coda
        void removeDeadEntities();
            //Funzioni debug
        void inline killEnemy(int o);
};


#include "../src/listUtils.tpp"

#endif
