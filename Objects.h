#ifndef OBJECTS_H
#define OBJECTS_H

#include<iostream>
#include <qdebug.h>
#include<SimpleList.h>

using namespace  std;

class User{
private:
    string name;
    SimpleList score;
public:
    //Constructor del objeto user
    User(string name){
        this->score = SimpleList();
        this->name = name;
    }
    //Constructor vacio del user
    User(){
    }

    //Accesores y modificadores del objeto
    string getName(){return name;}
    void setName(string newName){this->name = newName;}

    void addScore(int score){this->score.addOrder(score);}

    int getBestScore(){return score.getFirst()->getData();}

    ~User(){}
};

class Game_Piece{
private:
    string letter;
    int score;
public:
    //Constructor del objeto Game_Tab
    Game_Piece(string letter, int score){
        this->letter = letter;
        this->score = score;
    }
    //Constructor vacio del user
    Game_Piece(){}

    //Accesores y modificadores del objeto
    string getLetter(){return letter;}
    void setLetter(string newLetter){this->letter = newLetter;}
    int getScore(){return score;}
    void setScore(int newScore){this->score = newScore;}

    ~Game_Piece(){}
};

#endif // OBJECTS_H
