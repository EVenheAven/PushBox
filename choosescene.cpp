#include "choosescene.h"
#include <QMenuBar>
#include "mypushbutton.h"
#include <qpainter.h>
#include <QPixmap>
#include <QTimer>
#include <QLabel>
ChooseScene::ChooseScene(QWidget *parent)
    : QMainWindow{parent}
{
    this->setFixedSize(800,800);
    this->setWindowTitle("选择关卡");
    this->setWindowIcon(QPixmap(":/res/icon.png"));
    backgroundMusic=new QSoundEffect();
    backgroundMusic->setSource(QUrl::fromLocalFile(":/res/chooseScene.wav"));
//    backgroundMusic->play();

    //返回按钮
    MPushButton *back = new MPushButton(":/res/backbtn.png",
                                        ":/res/backbtn1.png",
                                        ":/res/backbtn1.png");
    back->setParent(this);
    back->move(this->width() - back->width(),this->height() - back->height());

    connect(back,&MPushButton::clicked,[=](){
        back->zoom1();
        back->zoom2();

        QTimer::singleShot(250,this,[=]{
            emit this->Chooseback();
        });
    });

    pScene = NULL;


    //10个关卡按钮
    for(int i = 0;i<10;i++)
    {
        MPushButton *menuBtn = new MPushButton(":/res/guanqia.png",
                                               ":/res/guanqia1.png",
                                               ":/res/guanqia1.png");
        menuBtn->setParent(this);
        menuBtn->move(120+(i%5)*128,320+(i/5)*128);
        connect(menuBtn,&MPushButton::clicked,[=](){

            this->pScene = new PlayScene(i+1);
            this->pScene->show();
            this->hide();
            this->backgroundMusic->stop();

            //监听第三个场景的返回按钮信号
            connect(this->pScene,&PlayScene::Chooseback,[=](){
                this->show();
                this->backgroundMusic->play();
                this->pScene->hide();
                delete this->pScene;
                this->pScene = NULL;
            });
        });

        QLabel *label = new QLabel;
        label->setParent(this);
        label->move(120+(i%5)*128,320+(i/5)*128);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        QFont font = label->font(); // 获取当前字体
        font.setPointSize(20); // 设置字体大小为20
        label->setFont(font); // 应用新的字体

        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //设置鼠标穿透属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);//放置数字吸收点击事件

    }

    //EX关卡按钮
    MPushButton *exbtn = new MPushButton(":/res/guanqia.png",
                                         ":/res/guanqia1.png",
                                         ":/res/guanqia1.png");
    exbtn->setParent(this);
    exbtn->move(0,this->height() - back->height());
    connect(exbtn,&MPushButton::clicked,[=](){
        backgroundMusic->stop();
        this->exgame = new EX_Scene;
        this->exgame->show();
        this->exgame->backgroundMusic->play();
        this->exgame->startOneGame();

        //监听第三个场景的返回按钮信号
        connect(this->exgame,&EX_Scene::Chooseback,[=](){
            this->show();
            this->exgame->hide();
            this->exgame->backgroundMusic->stop();
            delete this->exgame;
            this->backgroundMusic->play();
            this->exgame = NULL;
        });
    });
    QLabel *label = new QLabel;
    label->setParent(this);
    label->move(0,this->height() - back->height());
    label->setFixedSize(exbtn->width(),exbtn->height());
    label->setText(QString("EX"));
    QFont font = label->font(); // 获取当前字体
    font.setPointSize(20); // 设置字体大小为20
    label->setFont(font); // 应用新的字体

    label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    //设置鼠标穿透属性
    label->setAttribute(Qt::WA_TransparentForMouseEvents);//放置数字吸收点击事件

}



void ChooseScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(QString(":/res/choose.png"));
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //修改大小
}
