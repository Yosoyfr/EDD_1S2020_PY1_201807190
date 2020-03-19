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
        Game_Tab data;

    public:
        //Constructores del nodo
        Node(Game_Tab data){
            this->next = 0;
            this->data = data;
        }

        //Constructor vacio del nodo
        Node(){}

        //Accesores y modificadores de los atributos del nodo
        Node *getNext(){return next;}
        void setNext(Node *n) {this->next = n;}
        Game_Tab getData(){return data;}
        void setData(Game_Tab n) {this->data = n;}

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
    void add(Game_Tab data){
        Node *n = new Node(data);
        if(isEmpty())
            first = n;
        else
            last->setNext(n);
        last = n;
    }

    //Remueve el dato al frente de la cola
    Game_Tab remove(){
        Game_Tab aux;
        if(!isEmpty()){
            aux = first->getData();
            first = first->getNext();
        }
        return aux;
    }

    //Obtiene la cima de la cola
    Game_Tab peek(){
        if(isEmpty()){}
        return first->getData();
    }

    ~Queue(){};

};

#endif // QUEUE_H
