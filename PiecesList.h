#ifndef PIECESLIST_H
#define PIECESLIST_H

#include<iostream>
#include <qdebug.h>
#include <Objects.h>
using namespace  std;

class PiecesList{

    class Node{
    private:
        //Atributos del nodo para una lista simple para el puntaje por jugador
        Node *next;
        Game_Piece piece;

    public:
        //Constructores del nodo para la pieza
        Node(Game_Piece piece){
            this->next = 0;
            this->piece = piece;
        }

        //Constructor vacio del nodo
        Node(){}

        //Accesores y modificadores de los atributos del nodo
        Node *getNext(){return next;}
        void setNext(Node *n) {this->next = n;}
        Game_Piece getPiece(){return piece;}
        void setPiece(Game_Piece n) {this->piece = n;}

        ~Node(){}
    };

private:
    Node *first;
    Node *last;
    int size;

public:
    //Constructor de la lista simple
    PiecesList(){
        this->first = this->last = 0;
        this->size = 0;
    };

    //Verifica si la lista esta vacia
    bool isEmpty(){
        return first == 0;
    }

    //Inserta datos a la lista, por el final
    void addLast(Game_Piece piece){
        Node *n = new Node(piece);
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

    //Elimina de una pos
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
            cout << aux->getPiece().getLetter() << endl;
            aux = aux->getNext();
        }
    }

    //Retorna el tamaño de la lista
    int getSize(){return size;}

    //Retorna la cabeza
    Node *getFirst(){return first;}

    ~PiecesList(){};

};

#endif // PIECESLIST_H
