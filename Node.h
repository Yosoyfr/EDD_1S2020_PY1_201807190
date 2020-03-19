#ifndef NODE_H
#define NODE_H

#include<Objects.h>

class Compare{
public:
    bool igualQUe(User q);
    bool menorQue(User q);
    bool menorIgualQUe(User q);
    bool mayorQue(User q);
    bool mayorIgualQUe(User q);
};

class Node: public Compare{
private:
    //Atributos de un nodo para un arbol binario
    Node *left;
    Node *right;
    User data;

public:
    //Constructores del objeto Node de un arbol binario
    Node(User data){
        this->left = 0;
        this->right = 0;
        this->data = data;
    }

    Node(Node *left, User data, Node *right){
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
    User getData(){return data;}
    void setData(User n) {this->data = n;}

    string getDOT(){
        string graph;

        if(left == 0 && right == 0){
            graph = "\"" + getData().getName() + "\" [label = \"" + getData().getName() + "\"];\n";
        }
        else {
            graph = "\"" + getData().getName() + "\" [label = \"<C0>|" + getData().getName() + "|<C1>\"];\n";
        }

        if(left != 0)
            graph += left->getDOT() + "\"" + getData().getName() + "\":C0->\"" + left->getData().getName() + "\";\n";
        if(right != 0)
            graph += right->getDOT() + "\"" + getData().getName() + "\":C1->\"" + right->getData().getName() + "\";\n";

        return graph;
    }

    ~Node();
};


#endif // NODE_H
