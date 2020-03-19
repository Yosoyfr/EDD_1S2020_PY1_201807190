#include <QCoreApplication>
#include<QDebug>

#include <Objects.h>
#include <BinarySearchTree.h>
#include<Node.h>
#include<Stack.h>

#include<SimpleList.h>
#include<ScoreBoard.h>

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

    ScoreBoard board;

    User fran = User("Francisco");
    fran.addScore(20);
    fran.addScore(54);
    fran.addScore(28);
    fran.addScore(39);

    board.addOrderSB(fran);

    User maria = User("Maria");
    maria.addScore(48);
    maria.addScore(12);
    maria.addScore(56);

    board.addOrderSB(maria);

    User abel = User("Abel");
    abel.addScore(8);
    abel.addScore(98);
    abel.addScore(59);

    board.addOrderSB(abel);


    //board.printSB();


    //cout << arbol.getDOT()<<endl;

    return a.exec();
}
