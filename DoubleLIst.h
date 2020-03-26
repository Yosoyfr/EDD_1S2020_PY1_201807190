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
    int size = 0;

public:

    Node *getFirts(){return this->first;}
    Node *getLast(){return this->last;}
    int getSize(){return this->size;}

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

        if(this->isEmpty()){
            this->first = n;
            this->last = n;
        }
        else{
            this->last->setNext(n);
            n->setPrevious(last);
            this->last=n;
        }
        this->size++;
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

    void showData() {
        Node *aux = this->first;
        while(aux){
            cout << aux->getData().getLetter() << endl;
            aux = aux->getNext();
        }
    }

    //Obtiene el codigo DOT para formar el grafico
    void getDOT(DoubleList player1, DoubleList player2, string username1, string username2){
        string graph = "digraph G{\n "
                       "rankdir=LR;\n"
                       "labelloc = \"t\";\n";
        Node *aux1 = player1.getFirts();
        Node *aux2 = player2.getFirts();
        int x = 0;
        int y = 0;
        int yAUx = 0;

        //Fichas del jugador 1
        graph += "subgraph cluster_p {\n"
                 "node0[shape=record label =\"null\", fillcolor = yellow, style=filled]; \n";
        while(aux1){
            x++;
            graph += "node"+ to_string(x)+ "[shape=record label =\""+ aux1->getData().getLetter() + "\", fillcolor = yellow, style=filled];\n";
            aux1 = aux1->getNext();
        }

        y = x + 2;
        yAUx = x + 2;
        aux1 = player1.getFirts();
        x = 0;

        if (!isEmpty()){
            graph += "node0 -> node1 [color=white];\n";
            while(aux1!=player1.getLast()){
                x++;
                graph += "node" + to_string(x) + " -> node" + to_string(x+1) + ";\n";
                aux1 = aux1->getNext();
            }
            x = player1.getSize();
            graph += "node"+ to_string(x+1)+ "[shape=record label =\"null\", fillcolor = yellow, style=filled];\n";
            graph += "node" + to_string(x) + "-> node" + to_string(x+1) + ";\n";
            aux1=player1.getLast();
            while(aux1!=player1.getFirts()){
                x--;
                graph += "node"+to_string(x+1) + " -> node"+to_string(x) + ";\n";
                aux1 = aux1->getPrevios();
            }
            graph += "node1 -> node0;\n";
        }
        graph += "graph[label=\"Jugador 1: " + username2 +".\"];\n"
                 "}\n";


        //Fichas del jugador 2
        graph += "subgraph cluster_s {\n"
                 "node" + to_string(y) + "[shape=record label =\"null\", fillcolor = yellow, style=filled]; \n";
        while(aux2){
            y++;
            graph += "node" + to_string(y)+ "[shape=record label =\""+ aux2->getData().getLetter() + "\", fillcolor = yellow, style=filled];\n";
            aux2 = aux2->getNext();
        }

        aux2 = player2.getFirts();
        y = yAUx;

        if (!isEmpty()){
            graph += "node" + to_string(y) +  "-> node" + to_string(y + 1) + " [color=white];\n";
            while(aux2!=player2.getLast()){
                y++;
                graph += "node" + to_string(y) + " -> node" + to_string(y+1) + ";\n";
                aux2 = aux2->getNext();
            }
            y = player1.getSize() + player2.getSize() + 2;
            graph += "node"+ to_string(y+1)+ "[shape=record label =\"null\", fillcolor = yellow, style=filled];\n";
            graph += "node" + to_string(y) + "-> node" + to_string(y+1) + ";\n";
            aux2=player2.getLast();
            while(aux2!=player2.getFirts()){
                y--;
                graph += "node"+to_string(y+1) + " -> node"+to_string(y) + ";\n";
                aux2 = aux2->getPrevios();
            }
            graph += "node" + to_string(y) +  " -> node" + to_string(y - 1) +  ";\n";
        }
        graph += "graph[label=\"Jugador 2: " + username1 +".\"];\n"
                 "}\n";


        graph += "}";

        ofstream file("FichasJugador.dot", ios::out);;

        if(file.fail())
            cout << "Hubo un error (file.fail)";

        file << graph;
        file.close();

        system("dot -Tpng FichasJugador.dot -o FichasJugador.png");
    }
};

#endif // DOUBLELIST_H
