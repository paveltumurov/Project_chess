#include <cmath>
bool FreeDiag(int x, int x_, int y, int y_);//проверка, есть ли внутри диагонали (x,y) - (x_, y_), включая последнюю клетку, другие фигуры и диагональ ли это
bool FreeVert(int x,int x_, int y, int y_);//проверка, есть ли внутри вертикали (x, y) - (x, y_), включая последнюю клетку, другие фигуры и вертикаль ли это
bool FreeHorizont(int x, int x_, int y, int y_);//проверка, есть ли внутри горизонтали (x,y) - (x_, y), включая последнюю клетку, другие фигуры и горизонталь ли это

//виртуальный класс фигуры
class Piece{
public:
    bool Life=true;
    int x, y;
    virtual void Move (int x_, int y_);
    virtual void Capture(Piece A, int x_, int y_);
};

bool Board[64] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,};
//у меня доска это а1=0, а2 =8, b1 = 1 и т.д.

class Bishop: public Piece{
    void Move(int x_, int y_){
        bool free_diag;
        free_diag = FreeDiag(x, x_, y, y_);
        if((free_diag==true))
        {
            Board[x+8*y]=0;
            x = x_;
            y = y_;
            Board[x+8*y]=1;
        }
    };
};
class Rook: public Piece{
    void Move(int x_, int y_){
        bool free_line;
        if((x_==x)&&(y_!=y)){
            free_line = FreeVert(x,x_, y,y_);
        }
        if((x_!=x)&&(y_==y)){
            free_line = FreeHorizont(x, x_, y,y_);
        }
        if(free_line == true){
            Board[x+8*y]=0;
            x = x_;
            y = y_;
            Board[x+8*y]=1;
        }
    }
};
class Knight: public Piece{
    void Move(int x_, int y_){
        if(((abs(x-x_)==2)&&(abs(y-y_==1)))||((abs(y-y_==2)&&(abs(x-x_)==1)))&&Board[x_+y_*8]==0){
            Board[x+8*y]=0;
            x=x_;
            y=y_;
            Board[x+8*y]=1;
        }
    }
};
class Pawn: public Piece{
    void Move (int x_, int y_){
        if((y_-y==1)&&(x_==x)&&(Board[x+y_*8] ==0)){
            Board[x+8*y]=0;
            x = x_;
            y = y_;
            Board[x+8*y]=1;
        }
        if((y_-y==2)&&(x_==x)&&(Board[x+y_*8]==0)&&(Board[x+y_*8-8]==0)){
            Board[x+8*y]=0;
            x = x_;
            y = y_;
            Board[x+8*y]=1;
        }
    }
};
class Queen: public Piece{
    int x;
    int y;
    void Move(int x_, int y_){
        if(abs(x-x_)==abs(y-y_)){
            bool free_diag = FreeDiag(x,x_,y,y_);
            if(free_diag == true){
                Board[x+8*y]=0;
                x = x_;
                y = y_;
                Board[x+8*y]=1;
            }
        }
        if((x==x_)&&(y!=y_)){
            bool free_line = FreeVert(x,x_,y,y_);
            if(free_line == true){
                Board[x+8*y]=0;
                x = x_;
                y = y_;
                Board[x+8*y]=1;
            }
        }
        if((x!=x_)&&(y==y_)){
            bool free_line = FreeHorizont(x, x_, y, y_);
            if(free_line ==true){
                Board[x+8*y]=0;
                x = x_;
                y = y_;
                Board[x+8*y]=1;
            }
        }
    }
};
class King: public Piece{

};
int main(){

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


