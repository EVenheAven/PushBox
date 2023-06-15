#ifndef RULE_H
#define RULE_H
#include <QPainter>
#include <QEvent>
#include <QKeyEvent>
#include <QString>
#include <QRect>
#include <QImage>
#include <QPixmap>
#include "gamedata.h"
#include "config.h"
#include <QSoundEffect>

class Rule
{
public:
    Rule(int index);
    void drawmap(QPainter *pDraw);

    bool keyboard(QKeyEvent *e);

    bool updata(int x0, int y0, int x1, int y1, int x2, int y2);

//    void soundEffect(int type);

    int gameover();


    int manX;
    int manY;
    int step;
    int levelindex;
protected:
    int mMap[12][12];
signals:

};

void soundEffect(int type);

#endif // RULE_H
