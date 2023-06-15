#include "playscene.h"
#include<QMenuBar>
#include<QPainter>
#include "mypushbutton.h"
#include <choosescene.h>
#include <QTimer>
#include "rule.h"
#include <QSoundEffect>
#include <QDebug>
#include <QSqlDatabase>
#include <QtSql>
#include <QMessageBox>

PlayScene::PlayScene(int index)
{
    level=index;
    loseMusic=new QSoundEffect();
    loseMusic->setSource(QUrl::fromLocalFile(":res/lose.wav"));
    backgroundMusic=new QSoundEffect();
    backgroundMusic->setSource(QUrl::fromLocalFile(":res/gameScene.wav"));
    qDebug()<<backgroundMusic->source();
    backgroundMusic->play();
    this->levelIndex = index;
    //设置固定大小
    this->setFixedSize(960,960);
    //设置标题
    this->setWindowTitle(QString("星之卡比之恶魔城寻宝之旅"));
    //设置图片
    this->setWindowIcon(QIcon(":/res/icon.png"));
    //创建菜单栏
    mrule = new Rule(index);
    painter = new QPainter(this);
    MPushButton *back = new MPushButton(":/res/backbtn.png",
                                        ":/res/backbtn1.png",
                                        ":/res/backbtn1.png");
    back->setParent(this);
    back->move(0,0);

    connect(back,&MPushButton::clicked,[=](){
//        back->zoom1();
//        back->zoom2();

        QTimer::singleShot(250,this,[=]{
            this->close();
            emit this->Chooseback();
        });
    });
    //    QMenuBar *bar = menuBar();
    //    this->setMenuBar(bar);
    //创建开始菜单
//    QMenu * startmenu = bar->addMenu("开始");
    //创建菜单项
//    QAction * QuitAction = startmenu->addAction("返回选择关卡");
//    connect(QuitAction,&QAction::triggered,[=]()
//        {
//            this->close();
//            emit this->Chooseback();
//        });
}




void PlayScene::keyPressEvent(QKeyEvent *e)
{
    if(mrule->keyboard(e))
        mrule->step--;
//    if(mrule->step<=0&&!mrule->gameover()){
//        soundEffect(LOSE);
//    }
}

void PlayScene::paintEvent(QPaintEvent *)
{
    painter->begin(this);
    mrule->drawmap(painter);
    if(mrule->gameover()==1){
        backgroundMusic->stop();
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::black);
        painter.drawRect(rect());

        QFont font("Arial", 64);
        painter.setFont(font);
        painter.setPen(Qt::white);
        painter.drawText(rect(), Qt::AlignCenter, "YOU WIN");
//        mrule->step = 100;
        QTimer::singleShot(2000,this,[=](){

            emit this->Chooseback();
        });
    }
    else if(mrule->step <= 0){
        backgroundMusic->stop();
        if(!loseMusic->isPlaying())
            loseMusic->play();
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::black);
        painter.drawRect(rect());

        QFont font("Arial", 64);
        painter.setFont(font);
        painter.setPen(Qt::white);
        painter.drawText(rect(), Qt::AlignCenter, "YOU LOSE");

        QTimer::singleShot(5000,this,[=](){
            emit this->Chooseback();
        });
    }
    painter->end();
    update();
}

PlayScene::~PlayScene(){
    saveGameData(mrule->step);
    delete backgroundMusic;
}




void PlayScene::saveGameData(int remainStep)
{
    // 建立数据库连接
    QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("121.4.74.215");
    database.setPort(3306);
    database.setDatabaseName("game");
    database.setUserName("root");
    database.setPassword("jbsxl0814");

    if (!database.open()) {
//        qDebug() << "Failed to connect to database:"<<database.lastError();

        QMessageBox::warning(this,"连接数据库失败",database.lastError().text());
        return;
    }

    // 数据库连接成功，执行保存游戏数据的操作
    QSqlQuery query;

    // 创建游戏数据表（如果不存在）
    query.exec("CREATE TABLE IF NOT EXISTS game_data ("
               "id INT AUTO_INCREMENT PRIMARY KEY,"
               "remainStep INT,"
               "level INT"
               ")");

    // 插入游戏数据
    query.prepare("INSERT INTO game_data (remainStep, level) VALUES (:remainStep, :level)");
    query.bindValue(":remainStep", remainStep);
    query.bindValue(":level", level);
    if (!query.exec()) {
//        qDebug() << "Failed to save game data:" << query.lastError().text();
        QMessageBox::warning(this,"插入数据失败",database.lastError().text());

        return;
    }

    qDebug() << "Game data saved successfully.";

    // 关闭数据库连接
    database.close();
}
