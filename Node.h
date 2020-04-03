#ifndef NODE_H
#define NODE_H

#include<Objects.h>
#include<ScoreBoard.h>


class Node{
private:
    //Atributos de un nodo para un arbol binario
    Node *left;
    Node *right;
    User *data;

public:
    //Constructores del objeto Node de un arbol binario
    Node(User *data){
        this->left = 0;
        this->right = 0;
        this->data = data;
    }

    Node(Node *left, User *data, Node *right){
        this->left = left;
        this->right = right;
        this->data = data;
    }

    //Constructor vacio del nodo
    Node(){}

    //Accesores y modificadores de los atributos del nodo
    Node *getLeft(){return left;}
    void setLeft(Node *n) {this->left = n;}
    Node *getRight(){return right;}
    void setRight(Node *n) {this->right = n;}
    User *getData(){return data;}
    void setData(User *n) {this->data = n;}

    //Obtiene el codigo DOT para formar el grafico
    string getDOT(){
        string graph;

        if(left == 0 && right == 0){
            graph = "\"" + getData()->getName() + "\" [label = \"" + getData()->getName() + "\"];\n";
        }
        else {
            graph = "\"" + getData()->getName() + "\" [label = \"<C0>|" + getData()->getName() + "|<C1>\"];\n";
        }

        if(left != 0)
            graph += left->getDOT() + "\"" + getData()->getName() + "\":C0->\"" + left->getData()->getName() + "\";\n";
        if(right != 0)
            graph += right->getDOT() + "\"" + getData()->getName() + "\":C1->\"" + right->getData()->getName() + "\";\n";

        return graph;
    }

    //Scoreboard del juego update
    void getScoreBoard(Node *r){
        //Scoreboard del juego
        scoreboard = ScoreBoard();
        getScore(r);
        scoreboard.getDOT();
    }

    ScoreBoard scoreboard;
    //Retorna del juego
    void getScore(Node *r){
        if (r) {
            scoreboard.addOrderSB(*r->getData());
            getScore(r->getLeft());
            getScore(r->getRight());
        }
    }

    //Recorrido del arbol en preorden
    static void preOrder(Node *r){
        if (r) {
            r->visit();
            preOrder(r->getLeft());
            preOrder(r->getRight());
        }
    }

    //Recorrido del arbol inorden
    static void inOrder(Node *r){
        if (r) {
            inOrder(r->getLeft());
            r->visit();
            inOrder(r->getRight());
        }
    }

    //Recorrido del arbol postorden
    static void postOrder(Node *r){
        if (r) {
            postOrder(r->getLeft());
            postOrder(r->getRight());
            r->visit();
        }
    }

    void visit(){
        cout << "<" + getData()->getName() + "> ";
    }

    //Los mismo metodos de arriba, solo que para obtener el dot
    string preOrderDOT(Node *r){
        string graph;
        if (r) {
            graph += "\"" + r->visitDOT() + "\"";
            if(r->getLeft())
                graph += "->" + preOrderDOT(r->getLeft());
            if(r->getRight())
                graph += "->" + preOrderDOT(r->getRight());
        }
        return graph;
    }

    string inOrderDOT(Node *r){
        string graph;
        if (r) {
            if(r->getLeft())
                graph += inOrderDOT(r->getLeft());
            graph += "\"" + r->visitDOT() + "\"->";
            if(r->getRight())
                graph += inOrderDOT(r->getRight());
        }
        return graph;
    }

    string postOrderDOT(Node *r){
        string graph;
        if (r) {
            if(r->getLeft())
                graph += postOrderDOT(r->getLeft());
            if(r->getRight())
                graph += postOrderDOT(r->getRight());
            graph += "\"" + r->visitDOT() + "\"->";
        }
        return graph;
    }

    string visitDOT(){
        return getData()->getName();
    }

    //~Node();
};


#endif // NODE_H
