#ifndef STACK_H
#define STACK_H

#include<iostream>
#include <qdebug.h>

#include<Node.h>

using namespace  std;


class Stack{

    class NodeStack{
    private:
        //Atributos del nodo para una pila
        NodeStack *next;
        Node *data;

    public:
        //Constructores del objeto nodo
        NodeStack(Node *data){
            this->next = 0;
            this->data = data;
        }

        NodeStack(Node *data, NodeStack *next){
            this->data = data;
            this->next = next;
        }
        //Constructor vacio del nodo
        NodeStack(){}

        //Accesores y modificadores de los atributos del nodo
        NodeStack *getNext(){return next;}
        void setNext(NodeStack *n) {this->next = n;}
        Node *getData(){return data;}
        void setData(Node *n) {this->data = n;}

        ~NodeStack(){}
    };

private:
    NodeStack *peek;

public:
    //Constructor de la pila
    Stack(){
        this->peek = 0;
    };

    //Verifica si la pila esta vacia
    bool isEmpty(){
        return peek == 0;
    }

    //Inserta datos a la pila
    void push(Node *data){
        NodeStack *n = new NodeStack(data);
        n->setNext(peek);
        peek = n;
    }

    //Desapila la cima de la pila
    Node *pop(){
        if(isEmpty())
            return 0;

        Node *aux = peek->getData();
        peek = peek->getNext();
        return aux;
    }

    //Obtiene la cima de la pila
    Node *top(){
        if(isEmpty())
            return 0;

        return peek->getData();
    }

    ~Stack(){};

};

#endif // STACK_H
