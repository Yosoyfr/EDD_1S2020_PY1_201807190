#ifndef QUEUE_H
#define QUEUE_H


#include<iostream>
#include <qdebug.h>
#include <fstream>
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
    int size;

public:
    //Constructor de la cola
    Queue(){
        this->first = this->last  = 0;
        this->size = 0;
    };

    //Verifica si la cola esta vacia
    bool isEmpty(){
        return first == 0;
    }

    //Inserta datos a la cola, por el final
    void enqueue(Game_Piece data){
        Node *n = new Node(data);
        if(isEmpty())
            first = n;
        else
            last->setNext(n);
        last = n;
        this->size++;
    }

    //Remueve el dato al frente de la cola
    Game_Piece dequeue(){
        Game_Piece aux;
        if(!isEmpty()){
            aux = first->getData();
            first = first->getNext();
            this->size--;
        }
        return aux;
    }

    //Obtiene la cima de la cola
    Game_Piece peek(){
        if(isEmpty()){}
        return first->getData();
    }

    //Obtiene el codigo DOT para formar el grafico
    void getDOT(){
        string graph = "digraph G{\n "
                       "labelloc = \"t\";\n"
                       "abc [shape=record, margin=0, label=<\n"
                       "<table width=\"150\" >";
        Node *aux = this->first;
        while (aux) {
            int score = aux->getData().getScore();
            graph += "<tr>\n"
                     "<td width=\"150\" height=\"75\"  BGCOLOR=\"" + aux->getData().getColor() + "\">" + aux->getData().getLetter() + " x" + to_string(score) + "pts</td>\n"
                     "</tr>\n";
            aux = aux->getNext();
        }

        graph += "</table>>];\n"
                 "graph[label=\"Fichas disponibles del juego.\"];\n"
                 "}";

        ofstream file("FichasJuego.dot", ios::out);;

        if(file.fail())
            cout << "Hubo un error (file.fail)";

        file << graph;
        file.close();

        system("dot -Tpng FichasJuego.dot -o FichasJuego.png");
    }
    ~Queue(){};

    int getSize(){return size;}

};

#endif // QUEUE_H
