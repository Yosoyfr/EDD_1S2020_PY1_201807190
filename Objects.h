#ifndef OBJECTS_H
#define OBJECTS_H

#include<iostream>
#include <qdebug.h>
#include<SimpleList.h>

using namespace  std;

class User{
private:
    string name;
    SimpleList score = SimpleList();;
public:
    //Constructor del objeto user
    User(string name){
        this->name = name;
    }
    //Constructor vacio del user
    User(){
    }

    void getScore(){
        this->score.getDOT(this->name);
    }

    //Accesores y modificadores del objeto
    string getName(){return name;}

    void setName(string newName){this->name = newName;}

    void addScore(int score){
        this->score.addOrder(score);
    }

    int getBestScore(){
        if (score.getFirst()) {
            return score.getFirst()->getData();
        }
        else{
            return 0;
        }
    }

    ~User(){}
};

class Game_Piece{
private:
    string letter;
    int score;
    string color;
public:
    //Constructor del objeto Game_Piece
    Game_Piece(string letter, int score, string color){
        this->letter = letter;
        this->score = score;
        this->color = color;
    }
    //Constructor vacio del Game_Piece
    Game_Piece(){}

    //Accesores y modificadores del objeto
    string getLetter(){return letter;}
    void setLetter(string newLetter){this->letter = newLetter;}
    string getColor(){return color;}
    void setColor(string newColor){this->color = newColor;}
    int getScore(){return score;}
    void setScore(int newScore){this->score = newScore;}

    ~Game_Piece(){}
};

class SquaresXP{
private:
    int x;
    int y;
    int multiplier;
public:
    //Constructor del objeto SquaresXP
    SquaresXP(int x, int y, int multiplier){
        this->x = x;
        this->y = y;
        this->multiplier = multiplier;
    }
    //Constructor vacio del SquareXP
    SquaresXP(){}

    //Accesores  del objeto
    int getX(){return x;}
    int getY(){return y;}
    int getMultiplier(){return multiplier;}

    ~SquaresXP(){}
};

#endif // OBJECTS_H
