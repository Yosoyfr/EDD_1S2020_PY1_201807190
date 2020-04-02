#ifndef MATRIX_H
#define MATRIX_H

#include<QDebug>
#include<Objects.h>
#include<PiecesList.h>
#include<iostream>
#include<iomanip>

using namespace  std;

class Matrix
{
    class Node{
    private:
        //Atributos del Node para la matriz
        Node *up;
        Node *down;
        Node *next;
        Node *previous;
        Game_Piece data;
        int x;
        int y;
        int multiplierXP;

    public:
        //Constructores del Node
        Node(int x, int y, Game_Piece data, int multiplierXP){
            this->up = this->down= this->next = this->previous = 0;
            this->data = data;
            this->x = x;
            this->y = y;
            this->multiplierXP = multiplierXP;
        }

        //Constructor vacio del Node
        Node(){}


        //Obtiene los datos de cada cabecera por fila
        string getRowsDOT(){
            string graph;
            graph += "R" + to_string(this->y) + "[label=\"" + this->data.getLetter() + "_" + to_string(this->y) + "\", width=1.5, style=filled, fillcolor=blue4, fontcolor=white, group=1];\n";
            return graph;
        }

        string getPointR(){
            if(this->down != NULL){
                string rowC = "R" + to_string(this->y);
                string rowD = "R" + to_string(this->down->y);
                return rowC + " -> " + rowD + " -> " + rowC + ";\n";
            }
            return "";
        }


        //Obtiene los datos de cada cabecera por columna
        string getColumnsDOT(){
            string graph;
            graph += "C" + to_string(this->x) + "[label=\"" + this->data.getLetter() + "_" + to_string(this->x) + "\", width=1.5, style=filled, fillcolor=blue4, fontcolor=white, group=" + to_string(this->x + 2) + "];\n";
            return graph;
        }

        string getPointC(){
            if(this->next != NULL){
                string columnC = "C" + to_string(this->x);
                string columnD = "C" + to_string(this->next->x);
                return columnC + " -> " + columnD + " -> " + columnC + ";\n";
            }
            return "";
        }

        //Obtiene los nodos con datos de las piezas
        string getNodesDOT(){
            string graph;
            string color;
            int multi = this->multiplierXP;
            switch (multi) {
            case 2:
                color = "deepskyblue";
                break;
            case 3:
                color = "aquamarine2";
                break;
            default:
                color = "azure1";
                break;
            }
            graph += "N" + to_string(this->x) + to_string(this->y) + "[label=\"" + this->data.getLetter() + "\", width=1.5, style=filled, fillcolor=" + color + ", group=" + to_string(this->x + 2) + "];\n";
            return graph;
        }

        //Obtiene el rank de las columnas
        string getRankColumns(Node *root){
            string graph;
            Node *aux = root;
            graph += "{rank=same; Root ";

            while (aux != NULL) {
                graph += "C" + to_string(aux->x) + " ";
                aux = aux->getNext();
            }

            graph += "}\n";
            return graph;
        }

        string getPointX(){
            if(this->next != NULL){
                string columnC = "N" + to_string(this->x) + to_string(this->y);
                string columnD = "N" + to_string(this->next->x) + to_string(this->next->y);
                return columnC + " -> " + columnD + " -> " + columnC + ";\n";
            }
            return "";
        }

        string getPointY(){
            if(this->down != NULL){
                string rowC = "N" + to_string(this->x) + to_string(this->y);
                string rowD = "N" + to_string(this->down->x) + to_string(this->down->y);
                return rowC + " -> " + rowD + " -> " + rowC + ";\n";
            }
            return "";
        }

        string getRank(Node *row){
            string graph;
            string rowC = "R" + to_string(row->y);
            Node *aux = row->next;
            graph += "{rank=same; " + rowC + " ";
            while (aux != NULL) {
                graph += "N" + to_string(aux->x) + to_string(aux->y) + " ";
                aux = aux->getNext();
            }

            graph += "}\n";
            return graph;
        }

        //Accesores y modificadores de los atributos del Node
        Node *getNext(){return next;}
        void setNext(Node *n) {this->next = n;}
        Node *getPrevious(){return previous;}
        void setPrevious(Node *n) {this->previous = n;}
        Node *getUp(){return up;}
        void setUp(Node *n) {this->up = n;}
        Node *getDown(){return down;}
        void setDown(Node *n) {this->down = n;}
        Game_Piece getData(){return data;}
        void setData(Game_Piece n) {this->data = n;}
        int getY(){return y;}
        void setY(int n) {this->y = n;}
        int getX(){return x;}
        void setX(int n) {this->x = n;}
        int getMultiplierXP(){return multiplierXP;}
        void setMultiplierXP(int n) {this->multiplierXP = n;}

        ~Node(){}
    };

private:
    Node *root = new Node(-1, -1, Game_Piece("Root", 0, "0"), 0);
    int size = 0;

public:

    Node *search_Row(int y){
        Node *aux = this->root;
        while (aux) {
            if(aux->getY() == y){
                return aux;
            }
            aux = aux->getDown();
        }
        return 0;
    }

    Node *search_Column(int x){
        Node *aux = this->root;
        while (aux) {
            if(aux->getX() == x){
                return aux;
            }
            aux = aux->getNext();
        }
        return 0;
    }

    Node *insertOrderColumn(Node *n, Node *column){
        Node *aux = column;
        bool perm = false;
        while (true) {
            if (aux->getX() == n->getX()) {
                aux->setY(n->getY());
                aux->setData(n->getData());
                return aux;
            }
            else if (aux->getX() > n->getX()) {
                perm = true;
                break;
            }
            if (aux->getNext() != NULL) {
                aux = aux->getNext();
            }
            else
                break;
        }
        if (perm) {
            n->setNext(aux);
            aux->getPrevious()->setNext(n);
            n->setPrevious(aux->getPrevious());
            aux->setPrevious(n);
        }
        else{
            aux->setNext(n);
            n->setPrevious(aux);
        }
        return n;
    }

    Node *insertOrderRow(Node *n, Node *row){
        Node *aux = row;
        bool perm = false;

        while (true) {
            if (aux->getY() == n->getY()) {
                aux->setX(n->getX());
                aux->setData(n->getData());
                return aux;
            }
            else if (aux->getY() > n->getY()) {
                perm = true;
                break;
            }
            if (aux->getDown() != NULL) {
                aux = aux->getDown();
            }
            else
                break;
        }
        if (perm) {
            n->setDown(aux);
            aux->getUp()->setDown(n);
            n->setUp(aux->getUp());
            aux->setUp(n);
        }
        else{
            aux->setDown(n);
            n->setUp(aux);
        }
        return n;
    }

    Node *createColumn(int x){
        Node *auxColumn = this->root;
        Node *column = this->insertOrderColumn(new Node(x, -1, Game_Piece("Col", 0, "0"), 0), auxColumn);
        return column;
    }

    Node *createRow(int y){
        Node *auxRow = this->root;
        Node *row = this->insertOrderRow(new Node(-1, y, Game_Piece("Row", 0, "0"), 0), auxRow);
        return row;
    }


    //Proceso de insertar en la matriz
    void insert(int x, int y, Game_Piece data, int multiplier){
        Node *n = new Node(x, y, data, multiplier);
        Node *column = this->search_Column(x);
        Node *row = this->search_Row(y);

        if (!column && !row) {
            //Se crea columna
            column = this->createColumn(x);
            //Se crea fila
            row = this->createRow(y);
        }
        else if (!column && row) {
            //Se crea columnaNULL
            column = this->createColumn(x);
        }
        else if (column && !row) {
            //Se crea fila
            row = this->createRow(y);
        }
        //Insertamos en forma ordenada por columna
        n = this->insertOrderColumn(n, row);
        //Insertamos en forma ordenada por fila
        n = this->insertOrderRow(n, column);
        this->size++;
    }

    //Proceso de eliminar en la matriz

    Game_Piece remove(int x, int y){
        //Obtenemos las cabeceras
        Node *column = this->search_Column(x);
        Node *row = this->search_Row(y);
        Game_Piece piece;

        //Removemos de la columna
        piece = removeOrderColumn(row, x);
        //Removemos de la fila
        piece = removeOrderRow(column, y);


        //Si las cabeceras ya no tienen datos se eliminan
        if (!column->getDown()) {
            Node *prev = column->getPrevious();
            if (!column->getNext()) {
                prev->setNext(0);
            }
            else{
                prev->setNext(column->getNext());
                column->getNext()->setPrevious(prev);
            }
            delete column;
        }

        if (!row->getNext()) {
            Node *up = row->getUp();
            if (!column->getDown()) {
                up->setDown(0);
            }
            else{
                up->setDown(row->getDown());
                row->getDown()->setUp(up);
            }
            delete row;
        }
        return piece;
    }

    Game_Piece removeOrderColumn(Node *row, int x){
        Node *aux = row;
        Game_Piece piece;
        cout << to_string(x) << endl;
        while (aux != NULL) {
            if (aux->getX() == x) {
                Node *prev = aux->getPrevious();
                if(!aux->getNext()){
                    prev->setNext(0);
                }
                else{
                    prev->setNext(aux->getNext());
                    aux->getNext()->setPrevious(prev);
                }
                piece = aux->getData();
                break;
            }
            aux = aux->getNext();
        }
        return piece;
    }

    Game_Piece removeOrderRow(Node *column, int y){
        Node *aux = column;
        Game_Piece piece;

        while (aux != NULL) {
            if (aux->getY() == y) {
                Node *up = aux->getUp();
                if(!aux->getDown()){
                    up->setDown(0);
                }
                else{
                    up->setDown(aux->getDown());
                    aux->getDown()->setUp(up);
                }
                piece = aux->getData();
                break;
            }
            aux = aux->getDown();
        }
        return piece;
    }


    //Obtiene el codigo DOT para formar el grafico
    void getDOT(){
        string graph = "digraph Matrix{\n "
                       "labelloc = \"t\";\n"
                       "node [shape=box];\n"
                       "Root[label= \"Root\", width=1.5, style=filled, fillcolor = black, fontcolor=white, group = 1];\n";

        if (this->size > 0) {
            //Obtenemos las filas
            Node *aux = this->root->getDown();
            string firtsRow = "R" + to_string(aux->getY());
            if (aux) {
                while (aux) {
                    graph += aux->getRowsDOT();
                    aux = aux->getDown();
                }

                aux = this->root->getDown();
                graph += "Root -> " + firtsRow + " -> Root;\n";
                while (aux) {
                    graph += aux->getPointR();
                    aux = aux->getDown();
                }
            }

            //Obtenemos las columnas
            aux = this->root->getNext();
            string firtsColumn = "C" + to_string(aux->getX());
            if (aux) {
                while (aux) {
                    graph += aux->getColumnsDOT();
                    aux = aux->getNext();
                }

                aux = this->root->getNext();
                graph += "Root -> " + firtsColumn + " -> Root;\n";
                while (aux) {
                    graph += aux->getPointC();
                    aux = aux->getNext();
                }
            }

            //Rank de las columnas
            aux = this->root->getNext();
            graph += aux->getRankColumns(this->root->getNext());


            //Nodos con las piezas del juego
            aux = this->root->getDown();
            while (aux) {
                Node *temp = aux->getNext();
                while (temp) {
                    graph += temp->getNodesDOT();
                    temp = temp->getNext();
                }
                aux = aux->getDown();
            }

            //Union de los nodos por filas
            aux = this->root->getDown();
            while (aux) {
                string row = "R" + to_string(aux->getY());
                Node *temp = aux->getNext();
                string c = "N" + to_string(temp->getX()) + to_string(temp->getY());
                graph += row + " -> " + c + " -> " + row + ";\n";
                while (temp) {
                    graph += temp->getPointX();
                    temp = temp->getNext();
                }
                //Sacamos el Rank de estas
                graph += aux->getRank(aux);
                aux = aux->getDown();
            }

            //Union de los nodos por columnas
            aux = this->root->getNext();
            while (aux) {
                string column = "C" + to_string(aux->getX());
                Node *temp = aux->getDown();
                string c = "N" + to_string(temp->getX()) + to_string(temp->getY());
                graph += column + " -> " + c + " -> " + column + ";\n";
                while (temp) {
                    graph += temp->getPointY();
                    temp = temp->getDown();
                }
                aux = aux->getNext();
            }
        }

        graph += "graph[label=\"Tablero del juego. \n Multiplicadores de XP: x1 - Azure, x2 - Celeste, x3 - Menta.\"];\n"
                 "}";

        ofstream file("Matrix.dot", ios::out);;

        if(file.fail())
            cout << "Hubo un error (file.fail)";

        file << graph;
        file.close();

        system("dot -Tpng Matrix.dot -o Matrix.png");
    }

    void alert(string error){
        cout << "!! Alert: " + error + " !!" << endl;
    }

    SquaresXP insertPiece(int dimension, PiecesList squaresXP){
        int x = -1;
        while (x < 0 || x > dimension ) {
            cout << "Ingrese la coordenada en X: ";
            cin >> x;
            if (x < 0) {
                alert("No se permiten numeros menonres a 0");
            }
            else if (x > dimension) {
                alert("No se permiten numeros mayores a " + to_string(dimension));
            }
        }

        int y = -1;
        while (y < 0 || y > dimension ) {
            cout << "Ingrese la coordenada en Y: ";
            cin >> y;
            if (y < 0) {
                alert("No se permiten numeros menonres a 0");
            }
            else if (y > dimension) {
                alert("No se permiten numeros mayores a " + to_string(dimension));
            }
        }

        cout << "La coordenada en X es: " + to_string(x) << endl;
        cout << "La coordenada en Y es: " + to_string(x) << endl;

        SquaresXP piece;
        piece = SquaresXP(x, y, squaresXP.multiplierXP(x, y));

        return piece;
    }

    ~Matrix(){};
    int getSize(){return this->size;}
};
#endif // MATRIX_H
