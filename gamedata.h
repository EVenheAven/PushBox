#ifndef GAMEDATA_H
#define GAMEDATA_H
#include <QMap>
#include <QVector>

class GameData
{
public:
    GameData();
    //key(关卡号) value(二维数组)
    QMap<int,QVector<QVector<int>>> mData;
    QMap<int,int> mstep;
};

#endif // GAMEDATA_H
