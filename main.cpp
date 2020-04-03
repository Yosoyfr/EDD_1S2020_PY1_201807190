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

#include <unistd.h>

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

string modules(){
    //Bienvenida de la terminal
    string instructions[5] = {"Lectura de archivo JSON", "Registrar usuarios", "Jugar una partida", "Reportes", "Salir"};
    string select;
    for (int i = 0; i < 5; ++i) {
        cout << to_string(i) + " - " + instructions[i] << endl;
    }
    cout << "Opcion: ";
    cin >> select;
    return select;
}

string reports(){
    //Modulo de reportes
    cout << "\nModulo de reportes del juego." << endl;
    string instructions[7] = {"Diccionario de palabras", "ABB de usarios", "Recorrido PreOrden del ABB de usuarios",
                              "Recorrido InOrden del ABB de usuarios", "Recorrido PostOrden del ABB de usuarios",
                              "Historial de putanjes por un usario", "ScoreBoard"};
    string select;
    for (int i = 0; i < 7; ++i) {
        cout << to_string(i) + " - " + instructions[i] + " del juego." << endl;
    }
    cout << "7 - Salir del modulo de reportes." << endl;
    cout << "Opcion: ";
    cin >> select;
    return select;
}

User registerUser(string username){
    return  User(username);
}

void alert(string error){
    cout << "!! Alert: " + error + " !!" << endl;
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
    BinarySearchTree users;

    //Scoreboard del juego
    ScoreBoard scoreboard;

    //Inicializamos algunas cosas para poder jugar tranquilo
    dictionary.add("hola");
    dictionary.add("ñandu");
    dictionary.add("aux");
    dictionary.add("amar");
    dictionary.add("feca");

    users.insert(registerUser("Yosoyfr"));
    users.insert(registerUser("Mamba"));
    users.insert(registerUser("Tfue"));
    users.insert(registerUser("Ninja"));
    users.insert(registerUser("a"));
    users.insert(registerUser("b"));

    squaresXP.addLast(SquaresXP(1, 1, 2));
    squaresXP.addLast(SquaresXP(3, 2, 2));
    squaresXP.addLast(SquaresXP(0, 2, 2));
    squaresXP.addLast(SquaresXP(4, 0, 3));
    squaresXP.addLast(SquaresXP(1, 5, 3));

    dimension = 20;

    string c;
    while (c != "4") {
        cout << "Scrabble++\n" << endl;
        c = modules();
        if (c == "0") {
            cout << "\n##### Modulo de Lectura de archivo JSON #####" << endl;
            //Proceso de lectura del archivo JSON
            cout << "Si el archivo JSON se encuentra en la carpeta del proyecto, escribe solo el nombre del archivo, si no escribe la ruta completa." << endl;
            string route = "";
            cin >> route;
            QJsonObject jsonObject = jsonReading(route.c_str());

            dimension = jsonDimension(jsonObject);
            squaresXP = jsonSquares(jsonObject);
            dictionary = jsonDictionary(jsonObject);
            cout << "Dimension establecida: " + to_string(dimension) << endl;
        }
        else if (c == "1") {
            //Proceso para insertar usuarios
            while (1) {
                cout << "\n##### Modulo de registro de usuarios #####" << endl;
                cout << "Escriba el username del usuario: ";
                string username;
                cin >> username;
                users.insert(registerUser(username));

                cout << "\nDesea ingresar otro usuario?\n"
                        "No - 0\n"
                        "Si - cualquier cosa\n";

                string select;
                cout << "Opcion: ";
                cin >> select;
                if (select == "0") {
                    cout << "\n";
                    break;
                }
            }
        }
        else if (c == "2") {
            //Matriz: tablero del juego
            Matrix board;

            //Modulo de jugar
            cout << "\n##### Modulo de juego. Usuarios: " + to_string(users.getSize()) + " #####\n"<< endl;

            //El juego debe tener por lo menos dos jugadores
            if (users.getSize() >= 2 && dictionary.getSize() > 0 && dimension > 0) {

                //Vamos a inicializar la lista de fichas
                PiecesList pieces;
                for (int i = 0; i < 12; i++) {
                    pieces.addLast(Game_Piece("a", 1, "#2769AB"));
                    pieces.addLast(Game_Piece("e", 1, "#2FC25E"));
                }
                for (int i = 0; i < 9; i++) {
                    pieces.addLast(Game_Piece("o", 1, "#E4EE42"));
                }
                for (int i = 0; i < 6; i++) {
                    pieces.addLast(Game_Piece("i", 1, "#EEA242"));
                    pieces.addLast(Game_Piece("s", 1, "#EE6642"));
                }
                for (int i = 0; i < 5; i++) {
                    pieces.addLast(Game_Piece("n", 1, "#F91A1A"));
                    pieces.addLast(Game_Piece("r", 1, "#B9F91A"));
                    pieces.addLast(Game_Piece("u", 1, "#9CAD70"));
                    pieces.addLast(Game_Piece("d", 2, "#7083AD"));
                }
                for (int i = 0; i < 4; i++) {
                    pieces.addLast(Game_Piece("l", 1, "#AD70A1"));
                    pieces.addLast(Game_Piece("t", 1, "#F90505"));
                    pieces.addLast(Game_Piece("c", 3, "#05E3F9"));
                }
                for (int i = 0; i < 2; i++) {
                    pieces.addLast(Game_Piece("g", 2, "#1705F9"));
                    pieces.addLast(Game_Piece("b", 3, "#A005F9"));
                    pieces.addLast(Game_Piece("m", 3, "#F905BA"));
                    pieces.addLast(Game_Piece("p", 3, "#50994B"));
                    pieces.addLast(Game_Piece("h", 4, "#FFD500"));
                }
                pieces.addLast(Game_Piece("f", 4, "#FFD500"));
                pieces.addLast(Game_Piece("v", 4, "#FFD500"));
                pieces.addLast(Game_Piece("y", 4, "#FFD500"));
                pieces.addLast(Game_Piece("q", 5, "#FFD500"));
                pieces.addLast(Game_Piece("j", 8, "#FFD500"));
                pieces.addLast(Game_Piece("ñ", 8, "#FFD500"));
                pieces.addLast(Game_Piece("x", 8, "#FFD500"));
                pieces.addLast(Game_Piece("z", 10, "#FFD500"));

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

                //Proceso para solicitar los jugadores a jugar la partida
                cout << "Jugadores disponibles: ";
                users.inOrder();

                //Seleccion del jugador 1
                Node *player1 = 0;
                while (!player1) {
                    cout << endl << "Escriba el username del Jugador 1: ";
                    string j;
                    cin >> j;
                    player1 = users.search(users.getRoot(), j);
                    if (!player1) {
                        alert("El usuario no fue encontrado");
                    }
                }
                cout << "El usuario encontrado fue: " + player1->getData().getName() + " -> Jugador 1."<< endl;

                //Seleccion del jugador 2
                Node *player2 = 0;
                while (!player2 || player2 == player1) {
                    cout << endl << "Escriba el username del Jugador 2: ";
                    string j;
                    cin >> j;
                    player2 = users.search(users.getRoot(), j);
                    if (!player2) {
                        alert("El usuario no fue encontrado");
                    }
                    else if (player2 == player1) {
                        alert("El Jugador 2 no puede ser el mismo que le jugador 1");
                    }
                }
                cout << "El usuario encontrado fue: " + player2->getData().getName() + " -> Jugador 2.\n"<< endl;

                //Ya seleccionados los dos jugadores, se procede con el juego
                board.getDOT();
                system("xdg-open Matrix.png");
                sleep(1);

                //Se le daran fichas a los jugadores
                //Lista para el jugador 1
                DoubleList p1;
                for (int i = 0; i < 7; ++i) {
                    p1.addLast(pieces_in_game.dequeue());
                }

                //Lista para el jugador 2
                DoubleList p2;
                for (int i = 0; i < 7; ++i) {
                    p2.addLast(pieces_in_game.dequeue());
                }

                //Impresion de las fichas de los jugadores
                p1.getDOT(p1, p2, player1->getData().getName(), player2->getData().getName());
                system("xdg-open FichasJugador.png");
                sleep(1);

                //Impresion de las fichas que tiene el juego
                pieces_in_game.getDOT();
                system("xdg-open FichasJuego.png");

                //Seleccion del turno-----------------------------------------------------------------------------------------------------------------------
                int turn = 0;
                int pointsP1 = 0;
                int pointsP2 = 0;
                //Empezamos la partida
                while (pieces_in_game.getSize() > 0 && turn != 2) {
                    //Proceso de juego por turnos
                    PiecesList piecesEvaluate;
                    PiecesList squaresEvaluate;
                    if (turn == 0) {
                        //Primer turno
                        string instruction = "";
                        while (instruction != "0" && instruction != "1") {
                            cout << endl;
                            cout << "Que desea hacer en su turno " + player1->getData().getName() + "?" << endl;
                            cout << "0) Intercambiar fichas" << endl;
                            cout << "1) Insertar fichas" << endl;
                            cout << "Opcion: ";
                            cin >> instruction;
                            cout << endl;
                        }
                        if (instruction == "0") {
                            instruction = "0";
                            //Opcion: Intercambio de fichas
                            while (instruction == "0") {
                                Game_Piece piece = Game_Piece("a", 0, "0");
                                while (piece.getScore() == 0) {
                                    cin.get();
                                    cout << "Ingrese la letra a intercambiar: ";
                                    char letter = cin.get();;
                                    string auxL;
                                    auxL += letter;
                                    piece = p1.remove(auxL);
                                }
                                if (piece.getScore() > 0) {
                                    pieces_in_game.enqueue(piece);
                                    p1.addLast(pieces_in_game.dequeue());
                                }

                                //Preguntamos si desea finalizar el turno o intercambiar mas fichas
                                p1.getDOT(p1, p2, player1->getData().getName(), player2->getData().getName());
                                pieces_in_game.getDOT();
                                cout << endl;
                       del juego         cout << "0) Desea intercambar otra ficha?" << endl;
                                cout << "X) Finalizar turno?" << endl;
                                cout << "Opcion: ";
                                cin >> instruction;
                                cout << endl;
                            }
                        }
                        else{
                            //Opcion: jugar el turno
                            instruction = "1";
                            while (instruction == "1") {
                                SquaresXP squareAux = board.insertPiece(dimension, squaresXP);
                                Game_Piece piece = Game_Piece("a", 0, "0");
                                while (piece.getScore() == 0) {
                                    if (p1.getSize() == 0) {
                                        cout << "Ya no cuentas con fichas disponibles" << endl;
                                        break;
                                    }
                                    cin.get();
                                    cout << "Ingrese la letra a insertar: ";
                                    char letter = cin.get();;
                                    string auxL;
                                    auxL += letter;
                                    piece = p1.remove(auxL);
                                }
                                if (piece.getScore() > 0) {
                                    cout << "La letra ingresda es: " + piece.getLetter() << endl;
                                    piecesEvaluate.addLast(piece);
                                    squaresEvaluate.addLast(squareAux);
                                    board.insert(squareAux.getX(), squareAux.getY(), piece, squareAux.getMultiplier());
                                    board.getDOT();
                                }

                     del juego           //Preguntamos si desea validar o seguir insertando
                                p1.getDOT(p1, p2, player1->getData().getName(), player2->getData().getName());
                                cout << endl;
                                cout << "1) Desea insertar otra ficha?" << endl;
                                cout << "X) Desea validar las fichas insertadas?" << endl;
                                cout << "Opcion: ";
                                cin >> instruction;
                                cout << endl;
                            }
                            //Evaluacion de las letras insertadas
                            string word = "";
                            bool evaluateX = squaresEvaluate.evaluateX();
                            bool evaluateY = squaresEvaluate.evaluateY();
                            if (evaluateX) {
                                //Evaluacion por medio de busqueda en una columna
                                word = board.evaluateWordCol(squaresEvaluate.getX1(), squaresEvaluate.getY1(), squaresEvaluate.getY2());;
                                cout << "La palabra registrada fue: " + word << endl;
                            }
                            else if (evaluateY) {
                                //Evaluacion por medio de busqueda en una fila
                                word = board.evaluateWordRow(squaresEvaluate.getY1(), squaresEvaluate.getX1(), squaresEvaluate.getX2());
                                cout << "La palabra registrada fue: " + word << endl;
                            }
                            else{
                                alert("No se puede evaluar su registro ya que existe un error al insertar");
                                //Proceso de retornar las fichas insertadas
                                NodePiece *auxP = squaresEvaluate.getFirst();
                                while (auxP) {
                                    p1.addLast(board.remove(auxP->getSquare().getX(), auxP->getSquare().getY()));
                                    auxP = auxP->getNext();
                                }
                                board.getDOT();
                            }
                            //Ahora comparar la palabra registrada con el diccionario
                            int points = 0;
                            if (word != "") {
                                bool existWord = dictionary.searchWord(word);
                                if (existWord && evaluateX) {
                                    points = board.getPointsCol(squaresEvaluate.getX1(), squaresEvaluate.getY1(), squaresEvaluate.getY2());
                                }
                                else if (existWord && evaluateY) {
                                    points = board.getPointsRow(squaresEvaluate.getY1(), squaresEvaluate.getX1(), squaresEvaluate.getX2());

                                }
                                else {
                                    cout << "La palabra registrada no coincide con alguna del diccionario." << endl;
                                    NodePiece *auxP = squaresEvaluate.getFirst();
                                    while (auxP) {
                                        p1.addLast(board.remove(auxP->getSquare().getX(), auxP->getSquare().getY()));
                                        auxP = auxP->getNext();
                                    }
                                    board.getDOT();
                                }
                            }
                            pointsP1 += points;
                            cout << "Obtuviste los siguientes puntos en el turno: " + to_string(points) + "."<< endl;
                        }
                    }
                    else {
                        //Segundo turno
                        string instruction = "";
                        while (instruction != "0" && instruction != "1") {
                            cout << endl;
                            cout << "Que desea hacer en su turno " + player2->getData().getName() + "?" << endl;
                            cout << "0) Intercambiar fichas" << endl;
                            cout << "1) Insertar fichas" << endl;
                            cout << "Opcion: ";
                            cin >> instruction;
                            cout << endl;
                        }
                        if (instruction == "0") {
                            instruction = "0";
                            //Opcion: Intercambio de fichas
                            while (instruction == "0") {
                                Game_Piece piece = Game_Piece("a", 0, "0");
                                while (piece.getScore() == 0) {
                                    cin.get();
                                    cout << "Ingrese la letra a intercambiar: ";
                                    char letter = cin.get();;
                                    string auxL;
                                    auxL += letter;
                                    piece = p2.remove(auxL);
                                }
                                if (piece.getScore() > 0) {
                                    pieces_in_game.enqueue(piece);
                                    p2.addLast(pieces_in_game.dequeue());
                                }

                                //Preguntamos si desea finalizar el turno o intercambiar mas fichas
                                p1.getDOT(p1, p2, player1->getData().getName(), player2->getData().getName());
                                pieces_in_game.getDOT();
                                cout << endl;
                                cout << "0) Desea intercambar otra ficha?" << endl;
                                cout << "X) Finalizar turno?" << endl;
                                cout << "Opcion: ";
                                cin >> instruction;
                                cout << endl;
                            }
                        }
                        else{
                            //Opcion: jugar el turno
                            instruction = "1";
                            while (instruction == "1") {
                                SquaresXP squareAux = board.insertPiece(dimension, squaresXP);
                                Game_Piece piece = Game_Piece("a", 0, "0");
                                while (piece.getScore() == 0) {
                                    if (p2.getSize() == 0) {
                                        cout << "Ya no cuentas con fichas disponibles" << endl;
                                        break;
                                    }
                                    cin.get();
                                    cout << "Ingrese la letra a insertar: ";
                                    char letter = cin.get();;
                                    string auxL;
                                    auxL += letter;
                                    piece = p2.remove(auxL);
                                }
                                if (piece.getScore() > 0) {
                                    cout << "La letra ingresda es: " + piece.getLetter() << endl;
                                    piecesEvaluate.addLast(piece);
                                    squaresEvaluate.addLast(squareAux);
                                    board.insert(squareAux.getX(), squareAux.getY(), piece, squareAux.getMultiplier());
                                    board.getDOT();
                                }

                                //Preguntamos si desea validar o seguir insertando
                                p1.getDOT(p1, p2, player1->getData().getName(), player2->getData().getName());
                                cout << endl;
                                cout << "1) Desea insertar otra ficha?" << endl;
                                cout << "X) Desea validar las fichas insertadas?" << endl;
                                cout << "Opcion: ";
                                cin >> instruction;
                                cout << endl;
                            }
                            //Evaluacion de las letras insertadas
                            string word = "";
                            bool evaluateX = squaresEvaluate.evaluateX();
                            bool evaluateY = squaresEvaluate.evaluateY();
                            if (evaluateX) {
                                //Evaluacion por medio de busqueda en una columna
                                word = board.evaluateWordCol(squaresEvaluate.getX1(), squaresEvaluate.getY1(), squaresEvaluate.getY2());;
                                cout << "La palabra registrada fue: " + word << endl;
                            }
                            else if (evaluateY) {
                                //Evaluacion por medio de busqueda en una fila
                                word = board.evaluateWordRow(squaresEvaluate.getY1(), squaresEvaluate.getX1(), squaresEvaluate.getX2());
                                cout << "La palabra registrada fue: " + word << endl;
                            }
                            else{
                                alert("No se puede evaluar su registro ya que existe un error al insertar");
                                //Proceso de retornar las fichas insertadas
                                NodePiece *auxP = squaresEvaluate.getFirst();
                                while (auxP) {
                                    p2.addLast(board.remove(auxP->getSquare().getX(), auxP->getSquare().getY()));
                                    auxP = auxP->getNext();
                                }
                                board.getDOT();
                            }
                            //Ahora comparar la palabra registrada con el diccionario
                            int points = 0;
                            if (word != "") {
                                bool existWord = dictionary.searchWord(word);
                                if (existWord && evaluateX) {
                                    points = board.getPointsCol(squaresEvaluate.getX1(), squaresEvaluate.getY1(), squaresEvaluate.getY2());
                                }
                                else if (existWord && evaluateY) {
                                    points = board.getPointsRow(squaresEvaluate.getY1(), squaresEvaluate.getX1(), squaresEvaluate.getX2());

                                }
                                else {
                                    cout << "La palabra registrada no coincide con alguna del diccionario." << endl;
                                    NodePiece *auxP = squaresEvaluate.getFirst();
                                    while (auxP) {
                                        p2.addLast(board.remove(auxP->getSquare().getX(), auxP->getSquare().getY()));
                                        auxP = auxP->getNext();
                                    }
                                    board.getDOT();
                                }
                            }
                            pointsP2 += points;
                            cout << "Obtuviste los siguientes puntos en el turno: " + to_string(points) + "."<< endl;
                        }
                    }

                    //Se le vuelven a cargar 7 fichas
                    for (int i = p1.getSize(); i < 7; ++i) {
                        p1.addLast(pieces_in_game.dequeue());
                    }
                    for (int i = p2.getSize(); i < 7; ++i) {
                        p2.addLast(pieces_in_game.dequeue());
                    }
                    pieces_in_game.getDOT();
                    p1.getDOT(p1, p2, player1->getData().getName(), player2->getData().getName());


                    //Terminar juego o no
                    string temp = "";
                    while (temp != "0" && temp != "1") {
                        cout << endl;
                        cout << "1) Desea Terminar el juego? Si - 1 / No - 0" << endl;
                        cout << "Opcion: ";
                        cin >> temp;
                    }
                    if (temp == "1") {
                        turn = 2;
                    }
                    else if (turn == 0) {
                        turn = 1;
                    }
                    else{
                        turn = 0;
                    }
                }

                //Se acaba el juego
                cout << "S obtuvieron los siguientes resultados" << endl;
                cout << "J1: " + player1->getData().getName() + " obtuvo: " + to_string(pointsP1) + " pts." << endl;
                player1->getData().addScore(pointsP1);
                cout << "J2: " + player2->getData().getName() + " obtuvo: " + to_string(pointsP2) + " pts." << endl;
                player2->getData().addScore(pointsP2);
            }
            else if (dictionary.getSize() == 0) {
                alert("El juego no cuenta con un diccionario");
            }
            else if (dimension == 0) {
                alert("El tablero no contiene una dimension relativa");
            }
            else{
                alert("El juego no cuenta con los jugadores suficientes para poder iniciar una partida");
            }

            cout << "\n";
        }
        else if(c == "3"){
            //Reportes
            string select = "";

            while (select != "7") {
                select = reports();
                if (select == "0") {
                    //Mostrar el diccionario de palabras
                    dictionary.getDOT();
                    sleep(1);
                    system("xdg-open Diccionario.png");
                }
                else if (select == "1") {
                    //Mostrar ABB de usuarios
                    users.getDOT();
                    sleep(1);
                    system("xdg-open BinaryTree.png");
                }
                else if (select == "2") {
                    //Mostrar recorrido  Preorden
                    users.preOrderDOT();
                    sleep(1);
                    system("xdg-open Preorden.png");
                }
                else if (select == "3") {
                    //Mostrar el recorrido Inorden
                    users.inOrderDOT();
                    sleep(1);
                    system("xdg-open Inorden.png");
                }
                else if (select == "4") {
                    //Mostrar el recorrido Postorden
                    users.postOrderDOT();
                    sleep(1);
                    system("xdg-open Postorden.png");
                }
                else if (select == "5") {
                    //Mostrar historial de puntajes por un usuario
                    Node *player = 0;
                    while (!player) {
                        cout << "Inserte el username del jugador: ";
                        string j;
                        cin >> j;
                        player = users.search(users.getRoot(), j);
                        if (!player) {
                            alert("El usuario no fue encontrado");
                        }
                    }
                    player->getData().getScore();
                }
                else if (select == "6") {
                    //Mostrar el scoreboard
                    scoreboard.getDOT();
                    sleep(1);
                    system("xdg-open ScoreBoard.png");
                }
                else{
                    cout << "Ingrese una opcion valida" << endl;
                    select = reports();
                }
                cout << "\n";
            }
        }
    }

    return 0;
}










