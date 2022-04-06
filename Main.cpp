/*
    TOP TEXT
*/

#include <graphics.h>
#include<conio.h>
#include<dos.h>
#include <math.h>
#include <stdio.h>

#include <time.h>



struct Vector2{
    double x;
    double y;

    Vector2(){};

    Vector2 (double x, double y){
        this->x = x;
        this->y = y;
    };

    Vector2 (int x, int y){
        this->x = (double)x;
        this->y = (double)y;
    }

    Vector2 operator+(const Vector2& b){
        return Vector2(x + b.x, y + b.y);
    }
    Vector2 operator*(const float& b){
        return Vector2(x * b, y * b);
    }
    Vector2 operator/(const float& b){
        return Vector2(x/b, y/b);
    }
    Vector2 operator*(const double& b){
        return Vector2(x * b, y * b);
    }
    Vector2 operator/(const double& b){
        return Vector2(x/b, y/b);
    }
    Vector2 operator*(const int& b){
        return Vector2(x * b, y * b);
    }
    Vector2 operator/(const int& b){
        return Vector2(x/b, y/b);
    }
};

class Stopwatch{
    LARGE_INTEGER freq, start, end;
    public:
    Stopwatch(){
        ::QueryPerformanceFrequency(&freq);
    };

    void Start(){
        ::QueryPerformanceCounter(&start);
    };

    double Stop(){
        ::QueryPerformanceCounter(&end);

        return double(end.QuadPart - start.QuadPart) / double(freq.QuadPart);
    };

    double Restart(){

        ::QueryPerformanceCounter(&end);

        double t = double(end.QuadPart - start.QuadPart) / double(freq.QuadPart);
        ::QueryPerformanceCounter(&start);
        return t;
    }

};

Vector2 windowSize(700, 700);


class Bubble{
public :
    Vector2 position;
    Vector2 speed;
    double radius;
    int color;
    double bounciness=1;
    Bubble(){};
    Bubble(Vector2 pos, double rad){
        position = pos;
        radius = rad;
    };
    Bubble(Vector2 pos, int rad){
        position = pos;
        radius = (double)rad;
    };
    void Update(double dt){
        position = position + speed * dt;
        ScreenBoundBounce();
    };
    void ScreenBoundBounce(){
        bool needCheck = false;
        do{
            needCheck = false;
        double overRight = position.x + radius - windowSize.x;
        if (overRight >= 0){
            position.x -= 2*overRight;
            speed.x = -speed.x * bounciness;
            needCheck = true;
        }
        double overLeft = position.x - radius;
        if (overLeft <= 0){
            position.x -= 2*overLeft;
            speed.x = -speed.x* bounciness;
            needCheck = true;
        }
        double overTop = position.y - radius;
        if (overTop <= 0){
            position.y -= 2*overTop;
            speed.y = -speed.y* bounciness;
            needCheck = true;
        }
        double overBot = position.y + radius - windowSize.y;
        if (overBot >= 0){
            position.y -= 2*overBot;
            speed.y = -speed.y* bounciness;
            needCheck = true;
        }
        }while(needCheck);
    };

    void Draw(){
        setcolor(color);
        setfillstyle(9, color);
        //circle(position.x, position.y, radius);
        fillellipse(position.x, position.y, radius, radius);
    };
};

double targetFPS = 60;

void swapbuffers1(){
    int oldv = getvisualpage( );

    int olda = getactivepage( );

    setvisualpage(olda);

    setactivepage(oldv);
}

int main(){
    int gd=DETECT,gm;
    initgraph(&gd,&gm,"lib"); //Path where BGI folder appears

    Stopwatch sw;
    sw.Start();


    initwindow(windowSize.x, windowSize.y, "Bubbles", 0, 0, true, true);
    setactivepage(1);
    int bc = 0;
    int maxB = 50;
    Bubble bs[maxB];


    time_t t;
    srand((unsigned) time(&t));
    double spawnDelay = 0.05;
    int i;
    double spawnTime = spawnDelay + 0.01;
    double targetDt = 1 / targetFPS;
    double graphicTime = 0;
    while(1){
        double dt = sw.Restart();
        //graphicTime += dt;

        if (bc < maxB){
        spawnTime += dt;
        while(spawnTime > spawnDelay){

        bs[bc].radius = (double)(rand() % 30 + 10);
        bs[bc].position = Vector2(windowSize.x/2, windowSize.y - bs[bc].radius - 2);
        bs[bc].speed = Vector2(rand()%312 - 155, rand()%500 + 750);
        bs[bc].color = rand()%10 + 1;
        bs[bc].bounciness = (rand()%30 + 60) * 0.01;
        ++bc;
        spawnTime -= spawnDelay;
        }
        }

        for (i = 0; i < bc; i++){
            bs[i].Update(dt);
        }

        //if(graphicTime >= targetDt){
        swapbuffers1();
        cleardevice();
        for (i = 0; i < bc; i++){
            bs[i].Draw();
        }
        /*    while(graphicTime >= targetDt){
                graphicTime -= targetDt;
            }
        }*/

    }
   getch();
   closegraph();
    return 0;
}

/*
    BOTTOM KEK
*/
