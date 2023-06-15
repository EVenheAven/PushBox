#include "ex_scene.h"
#include "kirby.h"
#include <QDebug>
#include "choosescene.h"
#include <QSoundEffect>
EX_Scene::EX_Scene(){
    this->setFixedSize(960,960);
    this->setWindowTitle("最终试炼");
    this->setWindowIcon(QPixmap(":/res/icon.png"));
    backgroundMusic=new QSoundEffect();
    backgroundMusic->setSource(QUrl::fromLocalFile(":/res/ex.wav"));

    srand(time(NULL));
    gameIsRun=0;
    //地板高度
    this->groundY=this->height()-100;

    //加载该界面所有图像
    groundImg.load(":/res/ground.png");
    gameOverImg.load(":/res/gameover.png");
    pauseImg.load(":/res/pause.png");
    winImg.load(":/res/success.png");
//    loseImg.load(":/res/gameover.png");
    // 设置定时器，用于更新游戏画面
    fps.setInterval(17);

    this->grabKeyboard();//获取键盘事件
    connect(&fps,&QTimer::timeout,[=](){
        if(gameIsRun){
            r->addDifficult();//开始随时间增加难度
            r->move(upKey,downKey,leftKey,rightKey);

            // 处理障碍物的移动和碰撞检测
            for(auto i =curObstacle.begin();i!=curObstacle.end();)
            {
                if((*i)->done()) i=curObstacle.erase(i);//删除该障碍物
                else{
                    if((*i)->isCollision(r->getX(),r->getY(),r->getWidth(),r->getHeight())){
                        r->reduceHp();
                        curObstacle.clear();//清空障碍物
                        break;
                    }
                    (*i)->move();
                    i++;
                }
            }
            if(r->getCurHp()<=0)
                gameIsOver();
            if(!GameOver){
                addObstacles();
            }
        }
        update();
    });
}

void EX_Scene::paintEvent(QPaintEvent *){
    QPainter p(this);
    //背景绘制
    QPixmap pix;
    pix.load(QString(":/res/bloodmoon.png"));
    p.drawPixmap(0,0,this->width(),this->height(),pix);


    if(gameIsRun || GameOver)   //只是在开始第一局游戏前不走这个if
    {
        //人物绘制
        p.drawPixmap(QRect(r->getX(),r->getY(),r->getWidth(),r->getHeight()),r->getImg());

        //血量绘制
        p.drawRect(QRect(100,100,150,20));
        p.fillRect(QRect(100,100,r->getCurHpPercent()*150/100,20),Qt::red);
        p.drawLine(150,100,150,120);
        p.drawLine(200,100,200,120);
        QPen pen1(Qt::black);
        p.setFont(QFont("黑体",20));
        pen1.setColor(Qt::black);
        p.setPen(pen1);
        p.drawText(50,125,QString("HP"));

        //分数绘制
        p.drawText(500,100,QString("距离恶魔城:%1m").arg(r->getScore()));
        if(r->getScore()>1000){
            gameIsWin();
        }

        //障碍物绘制
        for(auto i=curObstacle.begin();i!=curObstacle.end();i++)
        {
            p.drawPixmap(QRect((*i)->getX(),(*i)->getY(),(*i)->getWidth(),(*i)->getHeight()),(*i)->getImg());
        }
    }

    //地图滚动
    p.drawPixmap(QRect(0,this->groundY,this->width(),this->height()-this->groundY)
                 ,groundImg
                 ,QRect(curgroundImgX,0,this->width(),this->height()-this->groundY));
    if(curgroundImgX>groundImg.width()-this->width())
        p.drawPixmap(QRect(groundImg.width()-curgroundImgX,this->groundY,this->width()-(groundImg.width()-curgroundImgX),groundImg.height())
                     ,groundImg
                     ,QRect(0,0,this->width()-(groundImg.width()-curgroundImgX),this->height()-this->groundY));

    if(curgroundImgX==groundImg.width())
            curgroundImgX=0;
    if(gameIsRun)
            curgroundImgX+=groundImgSpeed;

    //GameIsOver绘制
    if(GameOver){  
            fps.stop();
            p.drawPixmap((this->width()-gameOverImg.width())/2,(this->height()-gameOverImg.height())/2,gameOverImg);
//            QPainter painter(this);
//            painter.setRenderHint(QPainter::Antialiasing);
//            painter.setPen(Qt::NoPen);
//            painter.setBrush(Qt::black);
//            painter.drawRect(rect());

//            QFont font1("Arial", 64);
//            painter.setFont(font1);
//            painter.setPen(Qt::white);
//            int yOffset = -200; // 垂直偏移量
//            painter.drawText(rect().translated(0, yOffset), Qt::AlignCenter, "YOU LOSE");
//            yOffset += painter.fontMetrics().height(); // 在绘制完第一行后，增加偏移量
//            QFont font2("Arial", 32);
//            painter.setFont(font2);
//            painter.drawText(rect().translated(0, yOffset), Qt::AlignCenter, "按R重新开始");
//            yOffset += painter.fontMetrics().height(); // 在绘制完第二行后，增加偏移量
//            painter.drawText(rect().translated(0, yOffset), Qt::AlignCenter, "按Q返回选关");
    }

    if(GameWin){
            fps.stop();
            p.drawPixmap((this->width()-winImg.width())/2,(this->height()-winImg.height())/2,winImg);

    }
    //暂停绘制
    if(pauseState){
        p.drawPixmap((this->width()-pauseImg.width())/2,(this->height()-pauseImg.height())/2,pauseImg);
    }
}

void EX_Scene::startOneGame(){
    delete(r);
    curObstacle.clear();
    GameOver=false;
    GameWin=false;
    r=new Kirby(this);
    gameIsRun=true;

    r->run();
    fps.start();
    update();
}

void EX_Scene::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_W)
        this->upKey=true;
    else if(event->key()==Qt::Key_S)
        this->downKey=true;
    else if(event->key()==Qt::Key_A)
        this->leftKey=true;
    else if(event->key()==Qt::Key_D)
        this->rightKey=true;
    else if((GameOver||GameWin) && event->key()==Qt::Key_Q)
    {
        emit this->Chooseback();
    }
    else if(GameOver && event->key()==Qt::Key_R)
        startOneGame();

    else return QWidget::keyPressEvent(event);
}
void EX_Scene::keyReleaseEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_W)
        this->upKey=false;
    else if(event->key()==Qt::Key_S)
        this->downKey=false;
    else if(event->key()==Qt::Key_A)
        this->leftKey=false;
    else if(event->key()==Qt::Key_D)
        this->rightKey=false;
    else if(gameIsRun && event->key()==Qt::Key_Escape)
        if(pauseState==false)
            pauseGame();
        else
            continueGame();
    else return QWidget::keyPressEvent(event);
}

void EX_Scene::addObstacles(){
    static int afterLastWallTime;
    enum obstacleSort sort;
    sort=(enum obstacleSort)(rand()%3+1);       //这里改障碍物种类数目
    if(sort==SORT_WALL){
        if(rand()%600<=20*r->getDifficult() && afterLastWallTime>=90){//生成间隔
            int x=this->width()+20;
            int y=rand()%(int)(this->groundY*0.3)+this->groundY*0.7;
            curObstacle.push_back((Obstacle*)new Wall(x,y,80,this->groundY-y));
            afterLastWallTime=0;
        }
    }else if(sort==SORT_CIRCLE){
        if(rand()%600<=5*r->getDifficult()){
            int x=this->width()+150;
            int y=rand()%(int)250 + 0.5*this->height();
            int r=rand()%100+50;
            curObstacle.push_back((Obstacle*)new Circle(x,y,r,r));
        }
    }else if(sort==SORT_FIRE){
        if(rand()%600<=5*r->getDifficult()){
            int x=0;
            int y=rand()%this->groundY*0.6+this->groundY*0.3;
            curObstacle.push_back((Obstacle*)new Fire(x,y,400,100));
        }
    }
    afterLastWallTime++;
}


void EX_Scene::gameIsOver(){
    gameIsRun=false;
    GameOver=true;
}
void EX_Scene::gameIsWin(){
    gameIsRun=false;
    GameWin=true;
}

int EX_Scene::getGroundY(){
    return this->groundY;
}

void EX_Scene::pauseGame(){
    fps.stop();
    r->pauseGame();
    pauseState=true;
    update();
}

void EX_Scene::continueGame(){
    fps.start();
    r->continueGame();
    pauseState=false;
    update();
}

EX_Scene::~EX_Scene(){
    delete backgroundMusic;
}
