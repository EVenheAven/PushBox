#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <QPixmap>
#include <QString>

class Obstacle
{
public:
    Obstacle(int x,int y,int width,int height);
    virtual bool isCollision(int px,int py,int pwidth,int pheight);
    virtual void move();
    void executeMove(int dx,int dy);
    virtual QPixmap getImg();
    int getX();
    void setX(int x);
    int getY();
    void setY(int y);
    int getWidth();
    int getHeight();
    virtual bool done();


private:
    int x,y;
    int width,height;
};


class Wall:public Obstacle
{
private:
    QPixmap img;
public:
    Wall(int x,int y,int width,int height);
    virtual QPixmap getImg();
    virtual bool isCollision(int px,int py,int pwidth,int pheight);
    virtual void move();
    virtual bool done();
};

class Circle:public Obstacle
{
private:
    QPixmap img;
    int r;
    int CollisionDX,CollisionWidth; //碰撞检测
    bool degreeUP=true;             //旋转角度及顺逆时针
    int degree=0;
public:
    Circle(int x,int y,int width,int height);
    virtual QPixmap getImg();
    virtual bool isCollision(int px,int py,int pwidth,int pheight);
    virtual void move();
    virtual bool done();
};

class Fire:public Obstacle
{
private:
    QPixmap warningImg;
    QPixmap fireImg;
    int r;//半径
    int CollisionDX,CollisionWidth; //碰撞检测
    int CollisionDY,CollisionHeight; //碰撞检测
    int liveFrame=0,occurFrame=60;//警告与实际射击
public:
    Fire(int x,int y,int width,int height);
    virtual QPixmap getImg();
    virtual bool isCollision(int px,int py,int pwidth,int pheight);
    virtual void move();
    virtual bool done();
};
#endif // OBSTACLE_H
