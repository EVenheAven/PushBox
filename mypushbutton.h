#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#include<QDebug>
#include <QPushButton>
#include <QEvent>
#include<QString>
#include <QObject>

class MPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MPushButton(QObject *parent = nullptr);
    MPushButton(QString normalImag,QString pressImg = "",QString hoverImg = "");
    QString normalPath;//正常图片路径
    QString pressPath;//按下图片路径
    QString hoverPath;//悬浮时图片路径
    //向下跳跃
    void zoom1();
    //向上跳跃
    void zoom2();

    void mousePressEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);

    void enterEvent(QEnterEvent *e);

    void leaveEvent(QEvent *e);
signals:

};

#endif // MYPUSHBUTTON_H
