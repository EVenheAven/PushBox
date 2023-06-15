#include "mypushbutton.h"
#include<QPropertyAnimation>
MPushButton::MPushButton(QString normalImag,QString pressImg,QString hoverImg )
{
    this->normalPath = normalImag;
    this->pressPath = pressImg;
    this->hoverPath = hoverImg;
    QPixmap pix;
    bool ret = pix.load(this->normalPath);
    if(!ret)
    {
        QString str = QString("%1   图片加载失败").arg(this->normalPath);
        qDebug()<<str;
        return;
    }

    //设定图片大小
    this->setFixedSize(QSize(pix.width(),pix.height()));
    //设定不规则图片样式
    this->setStyleSheet(QString("QPushButton{border:0px;}"));
    //设定图片
    this->setIcon(QIcon(pix));
    //设置图片大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}

//向下跳跃
void MPushButton::zoom1()
{
    QPropertyAnimation *animation = new  QPropertyAnimation(this,"geometry");
    //设定时间间隔
    animation->setDuration(50);
    //设置动画对象起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
        //设置动画对象结束位置
    animation->setEndValue((QRect(this->x(),this->y()+10,this->width(),this->height())));
    //设置动画曲线
    animation->setEasingCurve(QEasingCurve::OutInBounce);
    //执行动画
    animation->start();

}
//向上跳跃
void MPushButton::zoom2()
{
    QPropertyAnimation *animation = new  QPropertyAnimation(this,"geometry");
    //设定时间间隔
    animation->setDuration(50);
    //设置动画对象起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
        //设置动画对象结束位置
    animation->setEndValue((QRect(this->x(),this->y(),this->width(),this->height())));
    animation->setEasingCurve(QEasingCurve::OutInBounce);
    //执行动画
    animation->start();
}

void MPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressPath != "")
    {
        QPixmap pix;
        bool ret = pix.load(this->pressPath);
        if(!ret)
        {
            QString str = QString("%1   图片加载失败").arg(this->pressPath);
            qDebug()<<str;
            return;
        }

        //设定图片大小
        this->setFixedSize(QSize(pix.width(),pix.height()));
        //设定不规则图片样式
        this->setStyleSheet(QString("QPushButton{border:0px;}"));
        //设定图片
        this->setIcon(QIcon(pix));
        //设置图片大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    QPushButton::mousePressEvent(e);
}

void MPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressPath != "")
    {
        QPixmap pix;
        bool ret = pix.load(this->normalPath);
        if(!ret)
        {
            QString str = QString("%1   图片加载失败").arg(this->normalPath);
            qDebug()<<str;
            return;
        }

        //设定图片大小
        this->setFixedSize(QSize(pix.width(),pix.height()));
        //设定不规则图片样式
        this->setStyleSheet(QString("QPushButton{border:0px;}"));
        //设定图片
        this->setIcon(QIcon(pix));
        //设置图片大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    QPushButton::mouseReleaseEvent(e);
}

void MPushButton::enterEvent(QEnterEvent *e)
{
    if(this->hoverPath != "")
    {
        QPixmap pix;
        bool ret = pix.load(this->hoverPath);
        if(!ret)
        {
            QString str = QString("%1   图片加载失败").arg(this->hoverPath);
            qDebug()<<str;
            return;
        }

        //设定图片大小
        this->setFixedSize(QSize(pix.width(),pix.height()));
        //设定不规则图片样式
        this->setStyleSheet(QString("QPushButton{border:0px;}"));
        //设定图片
        this->setIcon(QIcon(pix));
        //设置图片大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    QPushButton::enterEvent(e);
}

void MPushButton::leaveEvent(QEvent *e)
{
    if(this->hoverPath != "")
    {
        QPixmap pix;
        bool ret = pix.load(this->normalPath);
        if(!ret)
        {
            QString str = QString("%1   图片加载失败").arg(this->normalPath);
            qDebug()<<str;
            return;
        }

        //设定图片大小
        this->setFixedSize(QSize(pix.width(),pix.height()));
        //设定不规则图片样式
        this->setStyleSheet(QString("QPushButton{border:0px;}"));
        //设定图片
        this->setIcon(QIcon(pix));
        //设置图片大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    QPushButton::leaveEvent(e);
}

