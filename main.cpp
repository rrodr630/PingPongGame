#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>

using namespace std;

enum eDir{STOP = 0, LEFT = 1, UP_LEFT = 2, DOWN_LEFT = 3, RIGHT = 4, UP_RIGHT = 5, DOWN_RIGHT = 6};

class cBall {
  
private:
    int x,y;
    int originalX, originalY;
    eDir direction;
public:
    cBall(int posX, int posY) 
    {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
        direction = STOP;
    }
    
    void Reset()
    {
        x = originalX;
        y = originalY;
        direction = STOP;
    }
    
    void changeDirection(eDir d)
    {
        direction = d;
    }
    
    void randomDirection() 
    {
        direction = (eDir)((rand() % 6) + 1);
    }
    
    inline int getX() {return x;}
    inline int getY() {return y;}
    inline eDir getDirection() {return direction;}
  
  
    void Move()
    {
        switch(direction)
        {
            case STOP:
                break;
            
            case LEFT:
                x--;
                break;
            
            case RIGHT:
                x++;
                break;
                
            case UP_LEFT:
                x--; y--;
                break;
                
            case DOWN_LEFT:
                x--; y++;
                break;
                
            case UP_RIGHT:
                x++; y--;
                break;
                
            case DOWN_RIGHT:
                x++; y++;
                break;
                
            default:
                break;
        }
    }
    
    friend ostream &operator<<(ostream &os, cBall c) 
    {
        os << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]";
        return os;
    }
    
};

class cPaddle 
{
private:
    int x;
    int y;
    int originalX;
    int originalY;
public:
    cPaddle()
    {
        x = y= 0;
    }
    cPaddle(int posX, int posY) : cPaddle() //calls other constructor
    {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
    }
    inline void Reset() {x = originalX; y = originalY;}
    inline int getX() {return x;}
    inline int getY() {return y;}
    inline void moveUp() { y--; }
    inline void moveDown() { y++; }
    
    friend ostream &operator<<(ostream &os, cPaddle c) 
    {
        os << "Paddle [" << c.x << "," << c.y << "]";
        return os;
    }
};

class Game
{
private:
    int width, hight;
    int score1, score2;
    char player1_up, player1_down, player2_up, player2_down; //players move up and down
    bool quit;
    cBall *ball;
    cPaddle *player1;
    cPaddle *player2;
    int speed;
public:
    
    Game(int w, int h)
    {
        srand(time(NULL)); //time(NULL) returns current time
        quit = false;
        speed = 0;
        player1_up = 'w'; player2_up = 'p';
        player1_down = 's'; player2_down = ';';
        score1 = score2 = 0;
        width = w; hight = h;
        ball = new cBall( w/2, h/2 ); //ball in the middle
        player1 = new cPaddle(1, h/2 -3);
        player2 = new cPaddle(w - 2, h/2 -3);
    }
    ~Game()
    {
        delete ball; 
        delete player1;
        delete player2; // important
    }
    
    void IncreaseScore(cPaddle *player)
    {
        if(player == player1)
            score1++;
        else if(player == player2)
            score2++;
            
        ball->Reset();
        player1->Reset();
        player2->Reset();
    }
    
    void Draw()
    {
        system("cls");
        
        //Draw cealling
        for(int i = 0; i < width +2; i++)
            cout << "\xB2";
        cout << endl;
            
        
        //Drawing board
        for(int i = 0; i < hight; i++)
        {
            for(int j = 0; j < width; j++)
            {
                int ballX = ball->getX();
                int ballY = ball->getY();
                int player1X = player1->getX();
                int player1Y = player1->getY();
                int player2X = player2->getX();
                int player2Y = player2->getY();
                
                //Left wall
                if(j == 0)
                    cout << "\xB2";
                

                //Drawing players (Paddles) and ball (this will be all the space btw walls and top/bot corners)
                if(ballX == j && ballY == i) //Ball
                    cout << "O";
                    
                else if(player1X == j && player1Y == i) //Player 1
                    cout << "\xDB";
                else if(player1X == j && player1Y + 1 == i) //Player 1 this is to make paddle bigger
                    cout << "\xDB";
                else if(player1X == j && player1Y + 2 == i) //Player 1
                    cout << "\xDB";
                
                else if(player2X == j && player2Y == i) //Player 2 
                    cout << "\xDB";
                else if(player2X == j && player2Y + 1== i) //Player 2 making paddle bigger
                    cout << "\xDB";
                else if(player2X == j && player2Y + 2== i) //Player 2
                    cout << "\xDB";
                else
                    cout << " "; //Empty space (space where ball and players can move)
                    
    
                
                //Right wall
                if(j == width -1)
                    cout << "\xB2" << endl;
                
            }
        }
        
        
        
            
        //Draw floor    
        for(int i = 0; i < width +2; i++)
            cout << "\xB2";
        cout << endl;
        
        cout << "Scores:" << endl;
        cout << "Player 1: " << score1 << endl;
        cout << "Player 2: " << score2 << endl;
        cout << "Speed is " << speed << endl;
    }
    
    
    void Input()
    {
        ball->Move();
        
        //int ballX = ball->getX();
        //int ballY = ball->getY();
        //int player1X = player1->getX();
        int player1Y = player1->getY();
        //int player2X = player2->getX();
        int player2Y = player2->getY();
        
        if(_kbhit())
        {
            char current = _getch();
            
            if(current == player1_up)
                if(player1Y > 0)
                    player1->moveUp();
                    
            if(current == player2_up)
                if(player2Y > 0)
                    player2->moveUp();
                    
                    
            if(current == player1_down)
                if(player1Y + 4 < hight)
                    player1->moveDown();
                    
                    
            if(current == player2_down)
                if(player2Y + 4 < hight)
                    player2->moveDown();
                    
            if(ball->getDirection() == STOP)
                ball->randomDirection();
                
            if(current == 'q') 
                quit = true;
            
        }
    }
    
    void Logic()
    {
        int ballX = ball->getX();
        int ballY = ball->getY();
        int player1X = player1->getX();
        int player1Y = player1->getY();
        int player2X = player2->getX();
        int player2Y = player2->getY();
        
        //Left paddle hit
        for(int i = 0; i < 4; i++)
            if(ballX == player1X + 1)
                if(ballY == player1Y || ballY == player1Y + 1 || ballY == player1Y + 2)
                {
                    ball->changeDirection((eDir)((rand() % 3) + 4)); 
                    speed += 1; //If left paddle is hit, the ball can only move to the right (check number values of direction in enum)
                }
        //right paddle hit
        for(int i = 0; i < 4; i++)
            if(ballX == player2X - 1)
                if(ballY == player2Y || ballY == player2Y + 1 || ballY == player2Y + 2)
                {
                    ball->changeDirection((eDir)((rand() % 3) + 1)); //If right paddle is hit, the ball can only move to the left (check number values of direction in enum)
                    speed++;
                }
    
        //If ball hits bot wall
        if(ballY == hight - 1)
            ball->changeDirection(ball->getDirection() == DOWN_RIGHT ? UP_RIGHT : UP_LEFT);
        
        // If ball hits top wall
        if(ballY == 0)
            ball->changeDirection(ball->getDirection() == UP_RIGHT ? DOWN_RIGHT : DOWN_LEFT);
            
        // If player1 misses the ball
        if(ballX == width -1)
        {
            IncreaseScore(player1);
            speed = 0;
        }
        
        // If player2 misses the ball
        if(ballX == 0)
        {
            IncreaseScore(player2);
            speed = 0;
        }
    }
    
    void Run()
    {
        //Game loop
        while(!quit)
        {
            //sleep is not working correctly
         //   Sleep(30 - speed);
            Draw();
            Input();
            Logic();
        }
    }
    
};

int main() {
    
    Game newGame(40,20);
    newGame.Run();
            
    return 0;
    }