#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <Objects.h>
#include <Node.h>

#include<iostream>
#include <qdebug.h>
#include <fstream>

using namespace  std;

class BinarySearchTree{

protected:
    Node *root;
    Node *aux;
public:
    //Constructor vacio del arbol
    BinarySearchTree(){
        this->root = 0;
    }

    //Constructor del arbol, asignando el valor que recibira la raiz
    BinarySearchTree(Node *root){
        this->root = root;
    }

    bool isEmpty(){
        return root == 0;
    }

    static Node *newTree(Node *left, User data, Node *right){
        return  new Node(left, data, right);
    }

    void getDOT(){
        string graph = "digraph G{\n "
                       "rankdir=TB;\n"
                       "node [shape=record, style=filled, fillcolor=green];\n";
        graph += root->getDOT();
        graph += "}";

        ofstream file("BinaryTree.dot", ios::out);;

        if(file.fail())
            cout << "Hubo un error (file.fail)";

        file << graph;
        file.close();

        system("dot -Tpng BinaryTree.dot -o BinaryTree.png");
    }

    //Accesores y modificadores de los atributos del nodo
    Node *getRoot(){return root;}
    void setRoot(Node *n) {this->root = n;}
    Node *getAux(){return aux;}
    void setAux(Node *n) {this->aux = n;}
};

#endif // BINARYSEARCHTREE_H
