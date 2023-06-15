#include "kirby.h"
#include <QString>
#include <QDebug>
#include <QSoundEffect>
Kirby::Kirby(EX_Scene *g){
    this->exgame=g;
    //人物血量设置
    this->hp=3600;
    this->hpMax=3600;
    //初始位置
    this->x=100;
    this->y=exgame->getGroundY()-this->height;
    //人物大小
    this->width=50;
    this->height=50;
    this->curFace=FACE_RIGHT;//初始面向右边
    //最大移动范围
    this->maxX=exgame->width()-this->width;
    this->maxY=exgame->getGroundY()-this->height;

    //RUN 图片
    runLeftImg.load(QString(":/res/left1.png"));
    runRightImg.load(QString(":/res/right1.png"));
    //STAND 图片
    standLeftImg.load(":/res/left1.png");
    standRightImg.load(":/res/right1.png");
    //JUMP 图片
    jumpLeftImg.load(":/res/left2.png");
    jumpRightImg.load(":/res/right2.png");
    //图片设置
    curState=STATE_RUN;
    //时钟设置
    //run时每帧时长
    runTimer.setInterval(100);

    //jump时长
    jumpTimer.setInterval(jumpTime);
    jumpTimer.setSingleShot(true);
    connect(&jumpTimer,&QTimer::timeout,[=](){
        this->curState=STATE_RUN;
        //如果改这里，下方直接stop也要改的
    });

}

void Kirby::run(){
    runTimer.start();
}

//根据面向方向判断左右图片
QPixmap Kirby::getImg(){
    QPixmap img;
    if(curFace==FACE_LEFT)
        img=runLeftImg;
    else img=runRightImg;
    return img;
}


void Kirby::move(bool up,bool down,bool left,bool right){
    if(this->y==maxY){
        fallSpeed=0;
        twiceJumpReady=true;
    }
    if(up){
        //在地上则可以进行一段跳
        if(this->y==maxY){
            jumpTimer.start();
            onceJumpDone=false;
        }
        //在空中，且一段跳结束，则可以进行二段跳
        if(this->y<maxY && twiceJumpReady && onceJumpDone){
            jumpTimer.start();
            twiceJumpReady=false;
            fallSpeed=0;
        }
        if(jumpTimer.isActive())
            this->y-=jumpSpeed*jumpTimer.remainingTime()/jumpTime;//跳跃计时器剩余时间除以跳跃时间,实现跳跃高度变缓
    }
    else{
        jumpTimer.stop();
        onceJumpDone=true;
    }
    if(down){
        this->y+=quickFallSpeed;
    }
    if(left){
        this->x-=runSpeed;
        this->curFace=FACE_LEFT;
    }
    if(right){
        this->x+=runSpeed;
        this->curFace=FACE_RIGHT;
    }

    //自然掉落
    this->y+=fallSpeed;

    //范围限制
    if(this->x>=maxX) this->x=maxX;
    if(this->x<0) this->x=0;
    if(this->y>=maxY) this->y=maxY;
    if(this->y<0) this->y=0;

    //不按上了就不跳了，所以掉落速度就开始递增了
    if(!jumpTimer.isActive())
        fallSpeed+=fallSpeedDt;
    else
        fallSpeed=0;

    //判断是否在站立不动中
    if(this->y==maxY && !left && !right)
        isStanding=true;
    else
        isStanding=false;
    //时间加分
    this->score++;
}

//扣血
void Kirby::reduceHp(){
    this->hp-=1200;
    if(this->hp<=0)
        this->hp=0;
}

int Kirby::getCurHp(){
    return this->hp;
}

int Kirby::getCurHpPercent(){
    return this->hp*100/this->hpMax;
}

int Kirby::getX(){
    return this->x;
}

int Kirby::getY(){
    return this->y;
}
int Kirby::getWidth(){
    return this->width;
}
int Kirby::getHeight(){
    return this->height;
}
void Kirby::addScore(int s){
    this->score+=s;
}
int Kirby::getScore(){
    return this->score;
}
void Kirby::addDifficult(){
    this->difficult+=0.0015;
}
double Kirby::getDifficult(){
    return this->difficult;
}
void Kirby::pauseGame(){
    runTimer.stop();
    jumpTimer.stop();
}
void Kirby::continueGame(){

    runTimer.start();
}
