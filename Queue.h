#ifndef QUEUE_H
#define QUEUE_H


#include<iostream>
#include <qdebug.h>

#include <Objects.h>

using namespace  std;

class Queue{

    class Node{
    private:
        //Atributos del nodo para una cola
        Node *next;
        Game_Piece data;

    public:
        //Constructores del nodo
        Node(Game_Piece data){
            this->next = 0;
            this->data = data;
        }

        //Constructor vacio del nodo
        Node(){}

        //Accesores y modificadores de los atributos del nodo
        Node *getNext(){return next;}
        void setNext(Node *n) {this->next = n;}
        Game_Piece getData(){return data;}
        void setData(Game_Piece n) {this->data = n;}

        ~Node(){}
    };

private:
    Node *first;
    Node *last;

public:
    //Constructor de la cola
    Queue(){
        this->first = this->last  = 0;
    };

    //Verifica si la cola esta vacia
    bool isEmpty(){
        return first == 0;
    }

    //Inserta datos a la cola, por el final
    void add(Game_Piece data){
        Node *n = new Node(data);
        if(isEmpty())
            first = n;
        else
            last->setNext(n);
        last = n;
    }

    //Remueve el dato al frente de la cola
    Game_Piece remove(){
        Game_Piece aux;
        if(!isEmpty()){
            aux = first->getData();
            first = first->getNext();
        }
        return aux;
    }

    //Obtiene la cima de la cola
    Game_Piece peek(){
        if(isEmpty()){}
        return first->getData();
    }

    ~Queue(){};

};

#endif // QUEUE_H
