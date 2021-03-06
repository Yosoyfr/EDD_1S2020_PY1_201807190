#ifndef PIECESLIST_H
#define PIECESLIST_H

#include<iostream>
#include <qdebug.h>
#include <Objects.h>
using namespace  std;

class NodePiece{
private:
    //Atributos del nodo
    NodePiece *next;
    Game_Piece piece;
    SquaresXP square;

public:
    //Constructores del nodo para la pieza
    NodePiece(Game_Piece piece){
        this->next = 0;
        this->piece = piece;
    }

    //Constructores del nodo para la pieza
    NodePiece(SquaresXP square){
        this->next = 0;
        this->square = square;
    }

    //Constructor vacio del nodo
    NodePiece(){}

    //Accesores y modificadores de los atributos del nodo
    NodePiece *getNext(){return next;}
    void setNext(NodePiece *n) {this->next = n;}
    Game_Piece getPiece(){return piece;}
    void setPiece(Game_Piece n) {this->piece = n;}
    SquaresXP getSquare(){return square;}

    ~NodePiece(){}
};

class PiecesList{

private:
    NodePiece *first;
    NodePiece *last;
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
        NodePiece *n = new NodePiece(piece);
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
            NodePiece *aux = this->first;
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
            NodePiece *aux, *prev;
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
            NodePiece *aux, *prev;
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
        NodePiece *n = new NodePiece(square);
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
        NodePiece *aux = this->first;

        while (aux) {
            cout << aux->getPiece().getLetter() << endl;
            aux = aux->getNext();
        }
    }

    // Metodo que retorna el valor del multiplicador
    int multiplierXP(int x, int y){
        NodePiece *aux = this->first;
        int xp = 1;
        while (aux) {
            if (aux->getSquare().getX() == x && aux->getSquare().getY() == y) {
                xp = aux->getSquare().getMultiplier();
                break;
            }
            aux = aux->getNext();
        }
        return xp;
    }

    //Proceso de evaluar las casillas del jugador
    bool evaluateX(){
        bool perm = true;
        NodePiece *aux = this->first;
        int x = aux->getSquare().getX();
        while (aux) {
            if (aux->getSquare().getX() != x) {
                perm = false;
                break;
            }
            aux = aux->getNext();
        }

        return perm;
    }

    bool evaluateY(){
        bool perm = true;
        NodePiece *aux = this->first;
        int y = aux->getSquare().getY();
        while (aux) {
            if (aux->getSquare().getY() != y) {
                perm = false;
                break;
            }
            aux = aux->getNext();
        }

        return perm;
    }

    //Retorna el tamaño de la lista
    int getSize(){return size;}

    //Retorna la cabeza
    NodePiece *getFirst(){return first;}
    int getX1(){return first->getSquare().getX();}
    int getX2(){return last->getSquare().getX();}
    int getY1(){return first->getSquare().getY();}
    int getY2(){return last->getSquare().getY();}

    ~PiecesList(){};

};

#endif // PIECESLIST_H
