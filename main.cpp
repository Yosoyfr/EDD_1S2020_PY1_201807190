#include <QCoreApplication>
#include<QDebug>

#include <Objects.h>
#include <BinarySearchTree.h>
#include<Node.h>
#include<Stack.h>
#include<Queue.h>

#include<SimpleList.h>
#include<ScoreBoard.h>

#include<DoubleCircularLIst.h>
#include<DoubleLIst.h>

#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << "SCRABBLE++" << endl;

    BinarySearchTree arbol;
    arbol.insert(User("Heydi"));
    arbol.insert(User("Carlos"));
    arbol.insert(User("Antonio"));
    arbol.insert(User("Eduardo"));
    arbol.insert(User("Rodrigo"));
    /*
    arbol.insert(User("Jesus"));
    arbol.insert(User("Francisco"));
    arbol.insert(User("Zoila"));
    */
    arbol.getDOT();
    arbol.preOrderDOT();
    arbol.postOrderDOT();
    arbol.inOrderDOT();

    //cout << arbol.getRoot()->getData().getName()<< endl;

    DoubleCircularList listaC;
    listaC.add("Hola");
    listaC.add("Mundo");
    listaC.add("Prueba");
    listaC.add("Diccionario");
    listaC.add("Feca");
    listaC.add("Sexo");
    listaC.add("ALV");
    listaC.remove("Prueba");
    listaC.getDOT();

    Queue cola;
    cola.enqueue(Game_Piece("D", 2, "#FF5733"));
    cola.enqueue(Game_Piece("H", 3, "#33F6FF"));
    cola.enqueue(Game_Piece("K", 1, "#FF33FF"));
    cola.getDOT();


    ScoreBoard board;

    User fran = User("Francisco");
    fran.addScore(20);
    fran.addScore(54);
    fran.addScore(28);
    fran.addScore(39);
    fran.getScore();

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

    board.getDOT();

    DoubleList listaD;
    listaD.addLast(Game_Piece("D", 2, "#FF5733"));
    listaD.addLast(Game_Piece("H", 3, "#33F6FF"));
    listaD.addLast(Game_Piece("H", 3, "#33F6FF"));
    listaD.addLast(Game_Piece("K", 1, "#FF33FF"));
    listaD.addLast(Game_Piece("D", 2, "#FF5733"));
    listaD.addLast(Game_Piece("A", 2, "#FF5733"));

    DoubleList listaH;
    listaH.addLast(Game_Piece("J", 2, "#FF5733"));
    listaH.addLast(Game_Piece("J", 3, "#33F6FF"));
    listaH.addLast(Game_Piece("P", 3, "#33F6FF"));
    listaH.addLast(Game_Piece("A", 2, "#FF5733"));

    listaH.getDOT(listaD, listaH, abel.getName(), fran.getName());

    return a.exec();
}
