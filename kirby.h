#ifndef ROLE_H
#define ROLE_H

#include <QWidget>
#include <QTimer>
#include "ex_scene.h"
class Kirby : public QWidget
{
private:
    int hp;
    int hpMax;
    int x,y,width,height;
    int maxX,maxY;
    int score=0;
    double difficult=1;

    bool twiceJumpReady=false;
    bool onceJumpDone=false;
    bool isStanding=true;
    int jumpTime=400;
    double fallSpeed=0;
    double fallSpeedDt=0.5;
    int runSpeed=6;
    int jumpSpeed=20;
    int quickFallSpeed=20;

    EX_Scene *exgame;
    enum {FACE_LEFT,FACE_RIGHT}curFace;
    enum {STATE_RUN,STATE_JUMP}curState;
        //目前用途：冲刺时，冲刺结束还是dash状态   跳跃结束是设置为run,但并没有落地    图片更改目前未根据state(也就是说目前state没有用途)

    //RUN 图片    40*50
    int curRunImg=0;
    QPixmap runLeftImg;
    QPixmap runRightImg;
    //STAND 图片
    QPixmap standLeftImg;
    QPixmap standRightImg;
    //JUMP 图片   40*50
    QPixmap jumpLeftImg,jumpRightImg;
    
    
    QTimer runTimer,jumpTimer;
    Q_OBJECT

public:
    //    explicit Role(QWidget *parent = nullptr);
    Kirby(EX_Scene *g);
    void run();
    //HP相关
    void reduceHp();
    int getCurHp();
    int getCurHpPercent();

    QPixmap getImg();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void move(bool up,bool down,bool left,bool right);
    void addScore(int s);
    int getScore();
    void addDifficult();
    double getDifficult();
    void pauseGame();
    void continueGame();
signals:

};

#endif // ROLE_H
