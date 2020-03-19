#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include<Objects.h>

class DoubleList
{
    class Node{
    private:
        //Atributos del Node para una lista doble para las palabras del diccionario
        Node *next;
        Node *previos;
        Game_Piece data;

    public:
        //Constructores del Node para el Game_Piece
        Node(Game_Piece data){
            this->next = this->previos = 0;
            this->data = data;
        }

        //Constructor vacio del Node
        Node(){}

        //Accesores y modificadores de los atributos del Node
        Node *getNext(){return next;}
        void setNext(Node *n) {this->next = n;}
        Node *getPrevios(){return previos;}
        void setPrevious(Node *n) {this->previos = n;}
        Game_Piece getData(){return data;}
        void setData(Game_Piece n) {this->data = n;}

        ~Node(){}
    };

private:
    Node *first;
    Node *last;
    int size;

public:

    //Constructor del objeto Lista doble
    DoubleList(){
        this->first = this->last = 0;
    }

    //Verifica si la lista esta vacia
    bool isEmpty(){
        return first == 0;
    }

    //Inserta elementos a la lista
    void addLast(Game_Piece data){
        Node *n = new Node(data);

        if (!isEmpty()){
            this->last->setNext(n);
            n->setNext(0);
            n->setPrevious(0);
            this->last = n;
        }
        else{
            this->first = n;
            this->first->setNext(0);
            this->first->setPrevious(this->last);
            this->last = n;
        }
        size++;
    }

    //Metodo para buscar nodos, apartir de la letra a buscar
    Node *search(string letter){
        bool found = false;
        Node *aux = this->first;

        if (!isEmpty()){
            while(aux && !found){
                if (aux->getData().getLetter() == letter)
                {
                    found = true;
                    break;
                }
                aux = aux->getNext();
            };
        }
        if (!found){
            cout<<"La letra no fue encontrada"<<endl;
        }
        return aux;
    }


    //Metodo para eliminar datos de la lista
    void remove(string letter){
        Node *aux = search(letter);

        if (aux){
            if (aux == this->first){
                this->first = this->first->getNext();
                this->first->setPrevious(0);
            }
            else if (aux == this->last){
                this->last = this->last->getPrevios();
                this->last->setNext(0);
            }
            else{
                Node *prev = aux->getPrevios();
                prev->setNext(aux->getNext());
                aux->getNext()->setPrevious(prev);
            }
            delete aux;
        }
    }
};

#endif // DOUBLELIST_H
