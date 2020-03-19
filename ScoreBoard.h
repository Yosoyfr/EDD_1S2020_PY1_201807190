#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <Objects.h>

#include <iostream>
using namespace std;

class ScoreBoard{

    class Node{
    private:
        //Atributo del nodo para una lista simple para el scoreboard
        Node *next;
        User user;

    public:
        //Constructores del nodo para el score
        Node(User user){
            this->next = 0;
            this->user = user;
        }

        //Constructor vacio del nodo
        Node(){}

        //Accesores y modificadores de los atributos del nodo
        Node *getNext(){return next;}
        void setNext(Node *n) {this->next = n;}
        User getUser(){return user;}
        void setUser(User u) {this->user = u;}

        ~Node(){}
    };

private:
    Node *first;
    int size;

public:
    //Constructor de la lista simple
    ScoreBoard(){
        this->first = 0;
        this->size = 0;
    };

    //Verifica si la lista esta vacia
    bool isEmpty(){
        return first == 0;
    }

    //Inserta datos en orden para user por su score

    void addOrderSB(User user){
        Node *n = new Node(user);
        if(isEmpty()){
            this->first = n;
        }
        else if (user.getBestScore() > this->first->getUser().getBestScore()){
            n->setNext(this->first);
            this->first = n;
        }
        else{
            Node *aux, *prev;
            aux = prev = this->first;

            while (aux->getNext() && user.getBestScore() > aux->getUser().getBestScore()) {
                prev = aux;
                aux = aux->getNext();
            }
            if (user.getBestScore() > aux->getUser().getBestScore()){
                prev = aux;
            }
            n->setNext(prev->getNext());
            prev->setNext(n);
        }
        size++;
    }

    void printSB(){
        Node *aux = this->first;

        while (aux) {
            cout << aux->getUser().getName() << " ----- "<< aux->getUser().getBestScore() << endl;
            aux = aux->getNext();
        }
    }

    //Retorna el tamaño de la lista
    int getSize(){return size;}

    ~ScoreBoard(){};

};
#endif // SCOREBOARD_H
