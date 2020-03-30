#include <QCoreApplication>
#include<QDebug>

#include <Objects.h>
#include <BinarySearchTree.h>
#include<Node.h>
#include<Stack.h>
#include<Queue.h>

#include<SimpleList.h>
#include<ScoreBoard.h>
#include<PiecesList.h>

#include<DoubleCircularLIst.h>
#include<DoubleLIst.h>

#include<Matrix.h>

#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Vamos a inicializar la lista de fichas
    PiecesList pieces;
    for (int i = 0; i < 12; i++) {
        pieces.addLast(Game_Piece("A", 1, "#2769AB"));
        pieces.addLast(Game_Piece("E", 1, "#2FC25E"));
    }
    for (int i = 0; i < 9; i++) {
        pieces.addLast(Game_Piece("O", 1, "#E4EE42"));
    }
    for (int i = 0; i < 6; i++) {
        pieces.addLast(Game_Piece("I", 1, "#EEA242"));
        pieces.addLast(Game_Piece("S", 1, "#EE6642"));
    }
    for (int i = 0; i < 5; i++) {
        pieces.addLast(Game_Piece("N", 1, "#F91A1A"));
        pieces.addLast(Game_Piece("R", 1, "#B9F91A"));
        pieces.addLast(Game_Piece("U", 1, "#9CAD70"));
        pieces.addLast(Game_Piece("D", 2, "#7083AD"));
    }
    for (int i = 0; i < 4; i++) {
        pieces.addLast(Game_Piece("L", 1, "#AD70A1"));
        pieces.addLast(Game_Piece("T", 1, "#F90505"));
        pieces.addLast(Game_Piece("C", 3, "#05E3F9"));
    }
    for (int i = 0; i < 2; i++) {
        pieces.addLast(Game_Piece("G", 2, "#1705F9"));
        pieces.addLast(Game_Piece("B", 3, "#A005F9"));
        pieces.addLast(Game_Piece("M", 3, "#F905BA"));
        pieces.addLast(Game_Piece("P", 3, "#50994B"));
        pieces.addLast(Game_Piece("H", 4, "#FFD500"));
    }
    pieces.addLast(Game_Piece("F", 4, "#FFD500"));
    pieces.addLast(Game_Piece("V", 4, "#FFD500"));
    pieces.addLast(Game_Piece("Y", 4, "#FFD500"));
    pieces.addLast(Game_Piece("Q", 5, "#FFD500"));
    pieces.addLast(Game_Piece("J", 8, "#FFD500"));
    pieces.addLast(Game_Piece("Ñ", 8, "#FFD500"));
    pieces.addLast(Game_Piece("X", 8, "#FFD500"));
    pieces.addLast(Game_Piece("Z", 10, "#FFD500"));

    cout << to_string(pieces.getSize()) << endl;
    /*
    int num;
    srand(time(NULL));
    int c = 10;
    for (int i = 0; i < 15; i++) {
        num = 1 + rand() %c;
        cout << to_string(num) << endl;
        if(c > 1)
            c--;
    }
    */

    return a.exec();
}
