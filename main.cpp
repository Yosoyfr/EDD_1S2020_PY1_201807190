#include <QCoreApplication>
#include<QDebug>

#include <Objects.h>
#include <BinarySearchTree.h>
#include<Node.h>
#include<Stack.h>

#include<SimpleList.h>

#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << "SCRABBLE++" << endl;

    BinarySearchTree arbol;
    Node *a1, *a2, *ar;
    Stack pila = Stack();

    a1 = arbol.newTree(0,User("Maria"),0);
    a2 = arbol.newTree(0,User("Rodrigo"),0);
    ar = arbol.newTree(a1,User("Esperanza"),a2);
    pila.push(ar);
    a1 = arbol.newTree(0,User("Anyora"),0);
    a2 = arbol.newTree(0,User("Abel"),0);
    ar = arbol.newTree(a1,User("M Jesus"),a2);
    pila.push(ar);
    a2 = pila.pop();
    a1 = pila.pop();
    ar = arbol.newTree(a1,User("Francisco"),a2);
    arbol = ar;

    arbol.getDOT();

    SimpleList list;

    list.addOrder(20);
    list.addOrder(54);
    list.addOrder(28);
    list.addOrder(39);
    list.addOrder(48);
    list.addOrder(56);

    list.print();

    cout << endl << list.indexOf(48) << endl;
    cout << endl;

    list.remove(list.indexOf(48));
    list.print();


    //cout << arbol.getDOT()<<endl;

    return a.exec();
}
