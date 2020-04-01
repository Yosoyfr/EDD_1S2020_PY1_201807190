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

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include <iostream>
using namespace std;

QJsonObject jsonReading(QString filename){
    QFile file;
    QString values;
    file.setFileName(filename);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    values = file.readAll();
    if(file.error())
        cout << "Hubo un error (file.fail)\n" << endl;
    else
        cout << "Lectura de archivo exitosa\n" << endl;
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(values.toUtf8());
    return doc.object();
}

DoubleCircularList jsonDictionary(QJsonObject jsonObject){

    DoubleCircularList dictionary;
    QJsonArray dictionaryAux = jsonObject["diccionario"].toArray();
    foreach (const QJsonValue & value, dictionaryAux) {
        QJsonObject obj = value.toObject();
        QString aux = obj.value(QStringLiteral("palabra")).toString();
        string word = aux.toStdString();
        dictionary.add(word);
    }
    return dictionary;
}

PiecesList jsonSquares(QJsonObject jsonObject){
    PiecesList squaresXP;
    QJsonObject squares = jsonObject["casillas"].toObject();
    QJsonArray double_squares = squares["dobles"].toArray();
    QJsonArray triple_squares = squares["triples"].toArray();

    foreach (const QJsonValue & value, double_squares) {
        QJsonObject obj = value.toObject();
        int x = obj.value(QStringLiteral("x")).toInt();
        int y = obj.value(QStringLiteral("y")).toInt();
        squaresXP.addLast(SquaresXP(x, y, 2));
    }

    foreach (const QJsonValue & value, triple_squares) {
        QJsonObject obj = value.toObject();
        int x = obj.value(QStringLiteral("x")).toInt();
        int y = obj.value(QStringLiteral("y")).toInt();
        squaresXP.addLast(SquaresXP(x, y, 3));
    }
    return squaresXP;
}

int jsonDimension(QJsonObject jsonObject){
    return jsonObject.value(QStringLiteral("dimension")).toInt();
}

int modules(){
    //Bienvenida de la terminal
    string instructions[5] = {"Lectura de archivo JSON", "Registrar usuarios", "Jugar una partida", "Reportes", "Salir"};
    int select = 0;
    for (int i = 0; i < 5; ++i) {
        cout << to_string(i) + " - " + instructions[i] << endl;
    }
    cin >> select;
    return select;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Estructuras a utilizar a lo largo de las partidas
    //Estructuras utilizadas en la lectura de JSON
    PiecesList squaresXP;
    DoubleCircularList dictionary;
    int dimension = 0;

    //Arbol de usuarios
    BinarySearchTree user;

    int c = 0;
    while (c != 4) {
        cout << "Scrabble++\n" << endl;
        c = modules();
        if (c == 0) {
            //Proceso de lectura del archivo JSON
            cout << "\nSi el archivo JSON se encuentra en la carpeta del proyecto, escribe solo el nombre del archivo, si no escribe la ruta completa." << endl;
            string route = "";
            cin >> route;
            QJsonObject jsonObject = jsonReading(route.c_str());

            dimension = jsonDimension(jsonObject);
            squaresXP = jsonSquares(jsonObject);
            dictionary = jsonDictionary(jsonObject);
            //cout << "Dimension: " + to_string(dimension) << endl;
        }
        else if (c == 1) {
            //Proceso para insertar usuarios

        }
        else if (c == 2) {
            //Modulo de jugar
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

            //Proceso para almacenar en la cola las letras al azar
            Queue pieces_in_game;

            while (pieces.getSize() > 0) {
                int num;
                srand(time(NULL));
                num = rand() %pieces.getSize();
                Game_Piece pieza =  pieces.remove(num);
                pieces_in_game.enqueue(pieza);
            }
            pieces_in_game.getDOT();
            dictionary.getDOT();
        }
    }

    return 0;
}










