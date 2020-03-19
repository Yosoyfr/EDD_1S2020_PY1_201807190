#ifndef DOUBLECIRCULARLIST_H
#define DOUBLECIRCULARLIST_H

#include<Objects.h>

class DoubleCircularList
{
    class Node{
    private:
        //Atributos del Node para una lista circular doble para las palabras del diccionario
        Node *next;
        Node *previos;
        string word;

    public:
        //Constructores del Node para el score
        Node(string word){
            this->next = this->previos = 0;
            this->word = word;
        }

        //Constructor vacio del Node
        Node(){}

        //Accesores y modificadores de los atributos del Node
        Node *getNext(){return next;}
        void setNext(Node *n) {this->next = n;}
        Node *getPrevios(){return previos;}
        void setPrevious(Node *n) {this->previos = n;}
        string getData(){return word;}
        void setData(string n) {this->word = n;}

        ~Node(){}
    };

private:
    Node *first;
    Node *last;
    int size;

public:

    //Constructor del objeto Lista doble circular
    DoubleCircularList(){
        this->first = this->last = 0;
    }

    //Verifica si la lista esta vacia
    bool isEmpty(){
        return first == 0;
    }

    //Inserta elementos a la lista
    void add(string word){
        Node *n = new Node(word);

        if (!isEmpty()){
            this->last->setNext(n);
            n->setNext(this->first);
            n->setPrevious(this->last);
            this->last = n;
            this->first->setPrevious(this->last);
        }
        else{
            this->first = n;
            this->first->setNext(this->first);
            this->first->setPrevious(this->last);
            this->last = this->first;
        }
        size++;
    }

    Node *search(string word){
        bool found = false;
        Node *aux = this->first;

        if (!isEmpty()){
            do{
                if (aux->getData() == word){
                    found = true;
                    break;
                }
                aux = aux->getNext();
            } while (aux != this->first && !found);
        }
        if (!found){
            cout<<"La palabra no fue encontrada"<<endl;
        }
        return aux;
    }

    void remove(string word){
        Node *aux = search(word);

        if (aux){
            if (aux == this->first){
                this->first = this->first->getNext();
                this->first->setPrevious(this->last);
                this->last->setNext(this->first);
            }
            else if (aux == this->last){
                this->last = this->last->getPrevios();
                this->last->setNext(this->first);
                this->first->setPrevious(this->last);
            }
            else{
                Node* prev = aux->getPrevios();
                prev->setNext(aux->getNext());
                aux->getNext()->setPrevious(prev);
            }
            delete aux;
        }
    }
};

#endif // DOUBLECIRCULARLIST_H
