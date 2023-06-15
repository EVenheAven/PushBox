#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QPainter>
#include <rule.h>
#include <QSoundEffect>
#include <QSqlDatabase>
class PlayScene : public QMainWindow
{
    Q_OBJECT
    QPainter *painter;
    Rule *mrule;
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int index);//关卡号
    ~PlayScene();

    int levelIndex ;
    //重写键盘事件
    void keyPressEvent(QKeyEvent *e);
    //重写绘图
    void paintEvent(QPaintEvent *);
    void saveGameData(int score);
signals:
    void Chooseback();
private:
    QSoundEffect *backgroundMusic;
    QSoundEffect *loseMusic;
//    QSqlDatabase db;
    int level;
public slots:
};

#endif // PLAYSCENE_H
