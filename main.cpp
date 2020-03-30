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

#include<Matrix.h>

#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << "SCRABBLE++" << endl;

    Matrix matrix;


    matrix.insert(0, 0, Game_Piece("a", 1, "#FF5733"), 1);
    matrix.insert(2, 1, Game_Piece("b", 2, "#33F6FF"), 2);
    matrix.insert(1, 2, Game_Piece("c", 3, "#FF33FF"), 3);
    matrix.insert(0, 1, Game_Piece("d", 4, "#FF5733"), 2);
    matrix.insert(20, 1, Game_Piece("e", 5, "#33F6FF"), 1);
    matrix.insert(8, 8, Game_Piece("f", 8, "#33F6FF"), 3);
    matrix.insert(5, 15, Game_Piece("ñ", 10, "#33F6FF"), 1);

    /*
    matrix.remove(2, 1);
    matrix.remove(20, 1);
    matrix.remove(0, 1);
    */
    /*
    matrix.insert(1, 3, "dato5");
    matrix.insert(1, 2, "dato6");
    matrix.insert(10, 20, "dato7");
    matrix.insert(9, 19, "dato8");
    */


    matrix.print();
    matrix.getDOT();

    return a.exec();
}
