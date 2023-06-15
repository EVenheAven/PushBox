#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qpainter.h>
#include <mypushbutton.h>
#include <qtimer.h>
#include <QSoundEffect>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    this->setFixedSize(500,500);
    this->setWindowTitle("星之卡比之恶魔城寻宝之旅");
    this->setWindowIcon(QPixmap(":/res/icon.png"));
    backgroundMusic=new QSoundEffect();
    backgroundMusic->setSource(QUrl::fromLocalFile(":/res/mainScene.wav"));
    backgroundMusic->play();

    //选关场景
    this->choosescene = new ChooseScene;

    MPushButton *StartBtn = new MPushButton(QString(":/res/normalbtn.png"),
                                            QString(":/res/pressbtn.png"),
                                            QString(":/res/pressbtn.png"));
    StartBtn->setParent(this);
    StartBtn->move(this->width()*0.5-StartBtn->width()*0.5,this->height()*0.7);

    connect(StartBtn,&MPushButton::clicked,[=](){
        StartBtn->zoom1();
        StartBtn->zoom2();

        QTimer::singleShot(150,this,[=](){

            this->choosescene->show();
            this->choosescene->backgroundMusic->play();
            this->hide();
            backgroundMusic->stop();
        });
    });

    //监听选关场景中的返回按钮信号
    connect(this->choosescene,&ChooseScene::Chooseback,[=](){

        this->show();
        this->choosescene->hide();
        this->choosescene->backgroundMusic->stop();
        backgroundMusic->play();
    });
}


void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(QString(":/res/back.png"));
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


}

MainWindow::~MainWindow()
{
    delete ui;
    delete backgroundMusic;
}

