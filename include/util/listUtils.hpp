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

/**
 * @brief Template for a linked list of type `T`
*/
template <typename T> class List{
    protected:
        Node<T> *head; 
    public:
        List();     //crea lista vuota
        /*  scommentando questo distruttore, quando si esce dal gioco (premendo 'q' o morendo) dà questo errore
        free(): double free detected in tcache 2
        make: *** [Makefile:61: run] Aborted
        */
        /*~List() {
			Node<T>* current = head;
			while (current) {
				Node<T>* next = current->next;
				delete current;
				current = next;
			}
			head = nullptr;
		};*/
        bool isEmpty();     //ritorna true se la lista è vuota, false altrimenti
        int listLength() const;      //ritorna la lunghezza della lista
        void headInsert(T element);     //inserisce un elemento in testa

		void removeElement(int& tracker);	//rimuove un elemento dalla lista
				//void inline spawnEntities(); //spawna le entità

        //void inline spawnEnemies();
        void moveEntities(std::chrono::_V2::system_clock::time_point time_now);
        void spawnEntities();
        void removeDeadEntities();
        void inline refreshEnemyTarget(Position p1);
        void inline refreshEnemyProj(std::chrono::_V2::system_clock::time_point time_now);
		// void tailInsert(T element);     //inserisce un elemento in coda
            //Funzioni debug
        void inline killEnemy(int o);
        Node<T> *getHead();
        void remove(int index);
        void push_back(T data);
        bool contains(T data) const;
};


#include "../src/util/listUtils.tpp"

#endif
