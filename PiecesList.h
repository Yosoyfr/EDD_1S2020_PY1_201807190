#ifndef PIECESLIST_H
#define PIECESLIST_H

#include<iostream>
#include <qdebug.h>
#include <Objects.h>
using namespace  std;

class PiecesList{

    class Node{
    private:
        //Atributos del nodo
        Node *next;
        Game_Piece piece;
        SquaresXP square;

    public:
        //Constructores del nodo para la pieza
        Node(Game_Piece piece){
            this->next = 0;
            this->piece = piece;
        }

        //Constructores del nodo para la pieza
        Node(SquaresXP square){
            this->next = 0;
            this->square = square;
        }

        //Constructor vacio del nodo
        Node(){}

        //Accesores y modificadores de los atributos del nodo
        Node *getNext(){return next;}
        void setNext(Node *n) {this->next = n;}
        Game_Piece getPiece(){return piece;}
        void setPiece(Game_Piece n) {this->piece = n;}
        SquaresXP getSquare(){return square;}

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
    Game_Piece removeFirst(){
        Game_Piece piece;
        if(!isEmpty()){
            Node *aux = this->first;
            piece = aux->getPiece();
            this->first = this->first->getNext();
            delete aux;
            size--;
        }
        return piece;
    }

      //Remueve el ultimo elemento de la lista
    Game_Piece removeLast(){
        Game_Piece piece;
        if(!this->first->getNext())
            removeFirst();
        else if(!isEmpty()){
            Node *aux, *prev;
            aux = this->first;
            piece = this->last->getPiece();
            while (aux->getNext()) {
                prev = aux;
                aux = aux->getNext();
            }
            this->last = prev;
            prev->setNext(0);
            delete aux;
            size--;
        }
        return piece;
    }

    //Elimina de una pos
    Game_Piece remove(int pos){
        Game_Piece piece;
        if(pos > this->size - 1 || pos < 0){
        }
        else if (pos == 0)
            piece = removeFirst();
        else if (pos == this->size - 1)
            piece = removeLast();
        else if(!isEmpty()){
            Node *aux, *prev;
            aux = this->first;
            for(int i = 0; i < pos; i++){
                prev = aux;
                aux = aux->getNext();
            }
            piece = aux->getPiece();
            prev->setNext(aux->getNext());
            delete aux;
            size--;
        }
        return piece;
    }

    //Inserta datos a la lista, por el final
    void addLast(SquaresXP square){
        Node *n = new Node(square);
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
