#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <Objects.h>
#include <fstream>
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

        string getDOTN()
        {
            string graph;
            int aux = this->next->getUser().getBestScore();
            graph += this->next->getUser().getName() + ", " + to_string(aux) +" pts.";
            return graph;
        }

        string getDOT(){
            string graph;
            int aux = getUser().getBestScore();
            if(this->next)
                graph += "\"" + getUser().getName() + ", " + to_string(aux) + " pts.\"->\"" + getDOTN() +"\";\n";
            else
                graph += "";
            return graph;
        }

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
            while (aux->getNext() && user.getBestScore() < aux->getUser().getBestScore()) {
                prev = aux;
                aux = aux->getNext();
            }
            if (user.getBestScore() < aux->getUser().getBestScore()){
                prev = aux;
            }
            n->setNext(prev->getNext());
            prev->setNext(n);
        }
        size++;
    }

    //Imprime en consola la scoreboard
    void printSB(){
        Node *aux = this->first;

        while (aux) {
            cout << aux->getUser().getName() << " ----- "<< aux->getUser().getBestScore() << endl;
            aux = aux->getNext();
        }
    }

    //Obtiene el codigo DOT para formar el grafico
    void getDOT(){
        string graph = "digraph G{\n "
                       "rankdir=LR;\n"
                       "labelloc = \"t\";\n"
                       "node [shape=record];\n";
        Node *aux = this->first;

        while (aux) {
            graph += aux->getDOT();
            aux = aux->getNext();
        }
        graph += "graph[label=\"Scoreboard del juego.\"];\n"
                 "}";

        ofstream file("ScoreBoard.dot", ios::out);;

        if(file.fail())
            cout << "Hubo un error (file.fail)";

        file << graph;
        file.close();

        system("dot -Tpng ScoreBoard.dot -o ScoreBoard.png");
    }

    //Retorna el tamaño de la lista
    int getSize(){return size;}

    ~ScoreBoard(){};

};
#endif // SCOREBOARD_H
