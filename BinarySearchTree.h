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
    int size;
public:
    //Constructor vacio del arbol
    BinarySearchTree(){
        this->root = 0;
        this->size = 0;
    }

    //Constructor del arbol, asignando el valor que recibira la raiz
    BinarySearchTree(Node *root){
        this->root = root;
        this->size = 0;
    }

    bool isEmpty(){
        return root == 0;
    }

    static Node *newTree(Node *left, User *data, Node *right){
        return  new Node(left, data, right);
    }

    //Obtiene el codigo DOT para formar el grafico
    void getDOT(){
        string graph = "digraph G{\n "
                       "rankdir=TB;\n"
                       "labelloc = \"t\";\n"
                       "node [shape=record];\n";
        if (root) {
            graph += root->getDOT();
        }
        graph += "graph[label=\"Usuarios del juego.\"];\n"
                 "}";

        ofstream file("BinaryTree.dot", ios::out);;

        if(file.fail())
            cout << "Hubo un error (file.fail)";

        file << graph;
        file.close();
        system("dot -Tpng BinaryTree.dot -o BinaryTree.png");
    }

    //Metodo para buscar algun nodo del arbol
    Node *search(Node *rootAux, string dataSearch){
        if (rootAux == NULL)
            return 0;
        else if (dataSearch.compare(rootAux->getData()->getName()) == 0)
                 return rootAux;
        else if (dataSearch.compare(rootAux->getData()->getName()) == -1)
                 return search(rootAux->getLeft(), dataSearch);
        else
                 return search(rootAux->getRight(), dataSearch);
    }

    //Metodo para insertar datos al arbol
    void insert (User *data){
        this->root = insert(this->root, data);
    }

    Node *insert(Node *rootAux, User *data){
        if (rootAux == NULL){
            rootAux = new Node(data);
            cout << "Registro exitoso" << endl;
            this->size++;
        }
        else if (data->getName().compare(rootAux->getData()->getName()) < 0){
            Node *leftAux = insert(rootAux->getLeft(), data);
            rootAux->setLeft(leftAux);
        }
        else if (data->getName().compare(rootAux->getData()->getName()) > 0){
            Node *rightAux = insert(rootAux->getRight(), data);
            rootAux->setRight(rightAux);
        }
        else if (data->getName().compare(rootAux->getData()->getName()) == 0)
            cout << "Ya existe este username" << endl;
        return rootAux;
    }

    void preOrder(){
        this->root->preOrder(this->root);
    }

    void inOrder(){
        this->root->inOrder(this->root);
    }

    void postOrder(){
        this->root->postOrder(this->root);
    }

    void preOrderDOT(){
        string graph = "digraph G{\n "
                       "rankdir=LR;\n"
                       "labelloc = \"t\";\n"
                       "node [shape=record];\n";
        graph += this->root->preOrderDOT(this->root);
        graph += "\ngraph[label=\"Recorrido preorden del ABB.\"];\n"
                 "}";

        ofstream file("Preorden.dot", ios::out);;

        if(file.fail())
            cout << "Hubo un error (file.fail)";

        file << graph;
        file.close();

        system("dot -Tpng Preorden.dot -o Preorden.png");
    }

    void inOrderDOT(){
        string graph = "digraph G{\n "
                       "rankdir=LR;\n"
                       "labelloc = \"t\";\n"
                       "node [shape=record];\n";
        graph += this->root->inOrderDOT(this->root);
        graph.erase(graph.length()-1);
        graph.erase(graph.length()-1);
        graph += "\ngraph[label=\"Recorrido inorden del ABB.\"];\n"
                 "}";

        ofstream file("Inorden.dot", ios::out);;

        if(file.fail())
            cout << "Hubo un error (file.fail)";

        file << graph;
        file.close();

        system("dot -Tpng Inorden.dot -o Inorden.png");
    }

    void postOrderDOT(){
        string graph = "digraph G{\n "
                       "rankdir=LR;\n"
                       "labelloc = \"t\";\n"
                       "node [shape=record];\n";
        graph += this->root->postOrderDOT(this->root);
        graph.erase(graph.length()-1);
        graph.erase(graph.length()-1);
        graph += "\ngraph[label=\"Recorrido postorder del ABB.\"];\n"
                 "}";

        ofstream file("Postorden.dot", ios::out);;

        if(file.fail())
            cout << "Hubo un error (file.fail)";

        file << graph;
        file.close();

        system("dot -Tpng Postorden.dot -o Postorden.png");
    }

    void getScoreBoard(){this->root->getScoreBoard(this->root);}

    //Accesores y modificadores de los atributos del nodo
    Node *getRoot(){return root;}
    void setRoot(Node *n) {this->root = n;}
    int getSize(){return size;}

};

#endif // BINARYSEARCHTREE_H
