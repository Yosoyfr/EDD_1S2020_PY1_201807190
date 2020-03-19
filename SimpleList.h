#ifndef SIMPLELIST_H
#define SIMPLELIST_H


#include<iostream>
#include <qdebug.h>

using namespace  std;

class SimpleList{

    class Node{
    private:
        //Atributos del nodo para una lista simple para el puntaje por jugador
        Node *next;
        int data;

    public:
        //Constructores del nodo para el score
        Node(int data){
            this->next = 0;
            this->data = data;
        }

        //Constructor vacio del nodo
        Node(){}

        //Accesores y modificadores de los atributos del nodo
        Node *getNext(){return next;}
        void setNext(Node *n) {this->next = n;}
        int getData(){return data;}
        void setData(int n) {this->data = n;}

        ~Node(){}
    };

private:
    Node *first;
    Node *last;
    int size;

public:
    //Constructor de la lista simple
    SimpleList(){
        this->first = this->last = 0;
        this->size = 0;
    };

    //Verifica si la lista esta vacia
    bool isEmpty(){
        return first == 0;
    }

    //Inserta datos a la lista, por el final
    void addLast(int data){
        Node *n = new Node(data);
         if(isEmpty()){
             this->first = n;
             this->last = n;
         }
         else{
             this->last->setNext(n);
             this->last = n;
         }
         size++;
    }

    //Inserta datos a la lista, por la cabeza
    void addFirst(int data){
        Node *n = new Node(data);
        if(isEmpty()){
            this->first = n;
            this->last = n;
        }
        else{
            n->setNext(this->first);
            this->first = n;
        }
        size++;
    }

    //Inserta datos en orden para int
    void addOrder(int data){
        Node *n = new Node(data);
        if(isEmpty()){
            this->first = n;
        }
        else if (data > this->first->getData()){
            n->setNext(this->first);
            this->first = n;
        }
        else{
            Node *aux, *prev;
            aux = prev = this->first;

            while (aux->getNext() && data > aux->getData()) {
                prev = aux;
                aux = aux->getNext();
            }
            if (data > aux->getData()){
                prev = aux;
            }
            n->setNext(prev->getNext());
            prev->setNext(n);
        }
        size++;
    }

    //Busqueda en la lista por dato

    Node *search(int element){
        Node *index;
        for (index = this->first; !index; index = index->getNext())
            if(element == index->getData())
                return index;
        return 0;
    }

    int indexOf(int element){
        Node *aux = this->first;
        int index = 0;
        while (aux) {
            if(aux->getData() == element){
                return index;
            }
            index++;
            aux = aux->getNext();
        }

        return -1;
    }

    //Remueve el primer elemento de la lista
    void removeFirst(){
        if(!isEmpty()){
            Node *aux = this->first;
            this->first = this->first->getNext();
            delete aux;
            size--;
        }
    }

      //Remueve el ultimo elemento de la lista
    void removeLast(){
        if(!this->first->getNext())
            removeFirst();
        else if(!isEmpty()){
            Node *aux, *prev;
            aux = this->first;

            while (aux->getNext()) {
                prev = aux;
                aux = aux->getNext();
            }
            this->last = prev;
            prev->setNext(0);
            delete aux;
            size--;
        }
    }

    //
    void remove(int pos){
        if(pos > this->size - 1 || pos < 0)
            return;
        else if (pos == 0)
            removeFirst();
        else if (pos == this->size - 1)
            removeLast();
        else if(!isEmpty()){
            Node *aux, *prev;
            aux = this->first;

            for(int i = 0; i < pos; i++){
                prev = aux;
                aux = aux->getNext();
            }
            prev->setNext(aux->getNext());
            delete aux;
            size--;
        }
    }

    // Metodo para imprimir los nodos de la lista
    void print(){
        Node *aux = this->first;

        while (aux) {
            cout << aux->getData() << endl;
            aux = aux->getNext();
        }
    }

    void printSB(){
        Node *aux = this->first;

        while (aux) {
            cout << aux->getData() << endl;
            aux = aux->getNext();
        }
    }

    //Retorna el tamaño de la lista
    int getSize(){return size;}

    //Retorna la cabeza
    Node *getFirst(){return first;}

    ~SimpleList(){};

};

#endif // SIMPLELIST_H
