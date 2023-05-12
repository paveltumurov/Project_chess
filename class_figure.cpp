#include <cmath>
#include <string>
#include <iostream>
bool FreeDiag(int x, int x_, int y, int y_);//проверка, есть ли внутри диагонали (x,y) - (x_, y_), включая последнюю клетку, другие фигуры и диагональ ли это
bool FreeVert(int x,int x_, int y, int y_);//проверка, есть ли внутри вертикали (x, y) - (x, y_), включая последнюю клетку, другие фигуры и вертикаль ли это
bool FreeHorizont(int x, int x_, int y, int y_);//проверка, есть ли внутри горизонтали (x,y) - (x_, y), включая последнюю клетку, другие фигуры и горизонталь ли это
bool IsItChecked(int x_, int y_);//проверка на "шаховость" поля
void Move_to_square(int x, int x_, int y, int y_,int p);//переместить фигуру на поле
void board();
//виртуальный класс фигуры
class Piece{
public:
    int x, y;
    virtual void Move (int x_, int y_);
    virtual void Capture(Piece A, int x_, int y_);
};
std::string WhatPiece(int x, int y);

int Board[64] = {4,2,3,5,6,3,2,4,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-4,-2,-3,-5,-6,-3,-2,-4};
//у меня доска это а1=0, а2 =8, b1 = 1 и т.д.
//1- pawn
//2 - Knight
//3 - Bishop
//4 - Rook
//5 - Queen
//6 - King

class WhiteBishop: public Piece{
    int p=3;
    void Move(int x_, int y_){
        bool free_diag;
        free_diag = FreeDiag(x, x_, y, y_);
        if((free_diag==true))
        {
            Move_to_square(x, x_, y, y_, p);
        }
        else std::cout<<"/n"<<"Invalid Move!";
    };
};
class BlackBishop: public Piece{
    int p=-3;
    void Move(int x_, int y_){
        bool free_diag;
        free_diag = FreeDiag(x, x_, y, y_);
        if((free_diag==true))
        {
            Move_to_square(x, x_, y, y_, p);
        }
        else std::cout<<"/n"<<"Invalid Move!";
    };
};

class WhiteRook: public Piece{
    int p =4;
    void Move(int x_, int y_){
        bool free_line;
        if((x_==x)&&(y_!=y)){
            free_line = FreeVert(x,x_, y,y_);
        }
        if((x_!=x)&&(y_==y)){
            free_line = FreeHorizont(x, x_, y,y_);
        }
        if(free_line == true){
            Move_to_square(x, x_, y, y_,p);
        }
        else std::cout<<"/n"<<"Invalid Move!";
    }
};
class BlackRook: public Piece{
    int p = -4;
    void Move(int x_, int y_){
        bool free_line;
        if((x_==x)&&(y_!=y)){
            free_line = FreeVert(x,x_, y,y_);
        }
        if((x_!=x)&&(y_==y)){
            free_line = FreeHorizont(x, x_, y,y_);
        }
        if(free_line == true){
            Move_to_square(x, x_, y, y_,p);
        }
        else std::cout<<"/n"<<"Invalid Move!";
    }
};
class WhiteKnight: public Piece{
    int p =2;
    void Move(int x_, int y_){
        if(((abs(x-x_)==2)&&(abs(y-y_==1)))||((abs(y-y_==2)&&(abs(x-x_)==1)))&&Board[x_+y_*8]*Board[x+8*y]<=0){
            Move_to_square(x, x_, y, y_,p);
        }
        else std::cout<<"/n"<<"Invalid Move!";
    }
};
class BlackKnight: public Piece{
    int p = -2;
    void Move(int x_, int y_){
        if(((abs(x-x_)==2)&&(abs(y-y_==1)))||((abs(y-y_==2)&&(abs(x-x_)==1)))&&Board[x_+y_*8]*Board[x+8*y]<=0){
            Move_to_square(x, x_, y, y_,p);
        }
        else std::cout<<"/n"<<"Invalid Move!";
    }
};
class WhitePawn: public Piece{
    int p =1;
    void Move (int x_, int y_){
        if((y_-y==1)&&(x_==x)&&(Board[x+y_*8] ==0)){
            Move_to_square(x, x_, y, y_,p);
        }
        if((y_-y==2)&&(x_==x)&&(Board[x+y_*8]==0)&&(Board[x+y_*8-8]==0)){
            Move_to_square(x, x_, y, y_,p);
        }
        else std::cout<<"/n"<<"Invalid Move!";
    }
};
class BlackPawn: public Piece{
    int p =-1;
    void Move (int x_, int y_){
        if((y_-y==1)&&(x_==x)&&(Board[x+y_*8] ==0)){
            Move_to_square(x, x_, y, y_,p);
        }
        if((y_-y==2)&&(x_==x)&&(Board[x+y_*8]==0)&&(Board[x+y_*8-8]==0)){
            Move_to_square(x, x_, y, y_,p);
        }
        else std::cout<<"/n"<<"Invalid Move!";
    }
};
class WhiteQueen: public Piece{
    int x;
    int y;
    int p = 5;
    void Move(int x_, int y_){
        if(abs(x-x_)==abs(y-y_)){
            bool free_diag = FreeDiag(x,x_,y,y_);
            if(free_diag == true){
                Move_to_square(x, x_, y, y_,p);
            }
            else std::cout<<"/n"<<"Invalid Move!";
        }
        if((x==x_)&&(y!=y_)){
            bool free_line = FreeVert(x,x_,y,y_);
            if(free_line == true){
                Move_to_square(x, x_, y, y_,p);
            }
            else std::cout<<"/n"<<"Invalid Move!";
        }
        if((x!=x_)&&(y==y_)){
            bool free_line = FreeHorizont(x, x_, y, y_);
            if(free_line ==true){
               Move_to_square(x, x_, y, y_,p);
            }
            else std::cout<<"/n"<<"Invalid Move!";
        }
    }
};
class BlackQueen: public Piece{
    int x;
    int y;
    int p = -5;
    void Move(int x_, int y_){
        if(abs(x-x_)==abs(y-y_)){
            bool free_diag = FreeDiag(x,x_,y,y_);
            if(free_diag == true){
                Move_to_square(x, x_, y, y_,p);
            }
            else std::cout<<"/n"<<"Invalid Move!";
        }
        if((x==x_)&&(y!=y_)){
            bool free_line = FreeVert(x,x_,y,y_);
            if(free_line == true){
                Move_to_square(x, x_, y, y_,p);
            }
            else std::cout<<"/n"<<"Invalid Move!";
        }
        if((x!=x_)&&(y==y_)){
            bool free_line = FreeHorizont(x, x_, y, y_);
            if(free_line ==true){
               Move_to_square(x, x_, y, y_,p);
            }
            else std::cout<<"/n"<<"Invalid Move!";
        }
    }
};

class WhiteKing: public Piece{
    int p =6;
    void Move(int x_, int y_){
        if ((abs(x-x_)<=1)&&(abs(y-y_)<=1)&&IsItChecked(x_,y_)){
            Move_to_square(x, x_, y, y_, p);
        }
        else std::cout<<"/n"<<"Invalid Move!";
    }
};
class BlackKing: public Piece{
    int p =-6;
    void Move(int x_, int y_){
        if ((abs(x-x_)<=1)&&(abs(y-y_)<=1)&&IsItChecked(x_,y_)){
            Move_to_square(x, x_, y, y_, p);
        }
        else std::cout<<"/n"<<"Invalid Move!";
    }
};
int main(){
    board();
}
bool FreeDiag(int x, int x_, int y, int y_){
        if(abs(x_-x)!=abs(y_-y)||(x_<0)||(x_>7)||(y_<0)||(y_>7)||(y_==y)){
            return false;
        }//проверка на корректность ввода

        if ((x_>x)&&(y_>y)){
            for (int i =1; i<=abs(x-x_);i++){
                if(Board[x+i+(y+i)*8]==1){
                    return false;
                }
            }
        }
        if ((x_<x)&&(y_>y)){
            for (int i =1; i<=abs(x-x_);i++){
                if(Board[x-i+(y+i)*8]==1){
                    return false;
                }
            }
        }if ((x_>x)&&(y_<y)){
            for (int i =1; i<=abs(x-x_);i++){
                if(Board[x+i-(y+i)*8]==1){
                    return false;
                }
            }
        }if ((x_<x)&&(y_<y)){
            for (int i =1; i<=abs(x-x_);i++){
                if(Board[x-i+(y-i)*8]==1){
                    return false;
                }
            }
        }
        return true;
}
bool FreeVert(int x, int x_, int y, int y_){
    if((x-x_!=0)||(x_<0)||(x_>7)||(y_<0)||(y_>7)||(y==y_)){
        return false;
    }
    if(y>y_){
        for(int i=1; i<=y-y_;i++){
            if(Board[x+(y-i)*8]==1){
                return false;
            }
        }
    }
    if(y<y_){
        for(int i=1; i<=y_-y;i++){
            if(Board[x+(y+i)*8]==1){
                return false;
            }
        }
    }
    return true;
}
bool FreeHorizont(int x, int x_, int y, int y_){
    if((y_-y!=0)||(x_<0)||(x_>7)||(y_<0)||(y_>7)||(x==x_)){
        return false;
    }
    if(x>x_){
        for(int i=1; i<=x-x_;i++){
            if(Board[x-i+y*8]==1){
                return false;
            }
        }
    }
    if(x<x_){
        for(int i=1;i<=x_-x;i++){
            if(Board[x+i+y*8]==1){
                return false;
            }
        }
    }
    return true;
}
void Move_to_square(int x, int x_, int y, int y_, int p){
    Board[x+8*y]=0;
    x = x_;
    y = y_;
    Board[x+8*y]=p;
}
std::string WhatPiece(int x, int y){
    if (Board[x+8*y]==0){
        return "  ";
    }
    if (Board[x+8*y]==1){
        return "wP";
    }
    if (Board[x+8*y]==-1){
        return "bP";
    }if (Board[x+8*y]==2){
        return "wN";
    }
    if (Board[x+8*y]==-2){
        return "bN";
    }
    if (Board[x+8*y]==3){
        return "wB";
    }
    if (Board[x+8*y]==-3){
        return "bB";
    }
    if (Board[x+8*y]==4){
        return "wR";
    }
    if (Board[x+8*y]==-4){
        return "bR";
    }
    if (Board[x+8*y]==5){
        return "wQ";
    }
    if (Board[x+8*y]==-5){
        return "bQ";
    }
    if (Board[x+8*y]==6){
        return "wK";
    }
    if (Board[x+8*y]==-6){
        return "bK";
    }
}
void board() {
    for (int row = 7; row >= 0; row--) {
        // Draws Horizontal Row Dividers
        std::cout << "   ";
        for (int col = 0; col < 8; col++) {
            std::cout << "-----";
        }
        std::cout << "-" << std::endl;
        // Draws Vertical Row Divider and Chess Piece
        std::cout << row + 1 << "  ";
        for (int col = 0; col < 8; col++) {
            std::cout << "| ";
            std::cout<<WhatPiece(col, row);
            std::cout << " ";
        }
        // Draws Divider for end of Row
        std::cout << "|" << std::endl;
    }
    // Draws Horitonal Divider for last Row
    std::cout << "   ";
    for (int col = 0; col < 8; col++) {
        std::cout << "-----";
    }
    std::cout << "-" << std::endl;

    // Draws Letters on botton of board
    std::cout << "   ";
    for (int col = 0; col < 8; col++) {
        std::cout << "  " << (char) (col + 97) << "  ";
    }
    std::cout << std::endl << std::endl;
}