#include "rule.h"
#include "config.h"
#include <QTimer>
#include <QSoundEffect>

void soundEffect(int type){
    static QSoundEffect soundEffect;
    soundEffect.setSource(QUrl::fromLocalFile(":res/click.wav"));

    switch (type){
    case WALL:
    case WAY:
    case ATKER:{
        soundEffect.setSource(QUrl::fromLocalFile(":res/move.wav"));
        break;
    }
    case BOX:{
        soundEffect.setSource(QUrl::fromLocalFile(":res/push.wav"));
        break;
    }
    case CAVEBOX:
    case CAVE:{
        soundEffect.setSource(QUrl::fromLocalFile(":res/hurt.wav"));
        break;
    }
    case ENEMY:
    case ENEMYBEATTACK:
    case SENEMY:
    case SENEMYD:{
        soundEffect.setSource(QUrl::fromLocalFile(":res/fight.wav"));
        break;
    }
    case DES:
    case DOOR:{
        soundEffect.setSource(QUrl::fromLocalFile(":res/win.wav"));
        break;
    }
    case LOSE:{
        soundEffect.setSource(QUrl::fromLocalFile(":res/lose.wav"));
        break;
    }
    default:{
        break;
    }
    }
    qDebug()<<soundEffect.source();
    soundEffect.play();
}

Rule::Rule(int index)
{
    //加载当前关卡数
    levelindex = index;
    GameData data;
    //导入地图数据
    step = data.mstep[this->levelindex];
    for(int i=0; i<WNUM; i++)
    {
        for(int j=0; j<HNUM; j++)
        {
            mMap[i][j] = data.mData[this->levelindex][i][j];
        }
    }

    //寻找当前人的位置
    for(int i=0; i<WNUM; i++)
    {
        for(int j=0;j<HNUM; j++)
        {
            if(mMap[i][j] == MANINWAY || mMap[i][j] == MANINDES)
            {
                manX = i;
                manY = j;
            }
        }
    }
}

void Rule::drawmap(QPainter *pDraw)
{
    QString picpath;
    int t=0;
    for(int i=0; i<WNUM; i++)
    {
        for(int j=0; j<HNUM; j++)
        {
            switch (mMap[i][j])
            {
            case WALL:
                picpath = ":/res/wall.png";
                break;
            case WAY:
                picpath = ":/res/way.png";
                break;
            case BOX:
                picpath = ":/res/block1.png";

                if(levelindex == 8){
                    t=j-1;
                    int temp=t;
                    while(mMap[i][temp] == BIU){
                        temp--;
                    }
                    if(mMap[i][temp]!=UFO){
                        while(t>temp){
                            mMap[i][t] = WAY;
                            t--;
                        }
                    }
                    t=j+1;
                    temp=t;
                    while(mMap[i][temp] == BIU){
                        temp++;
                    }
                    if(mMap[i][temp]!=UFO){
                        while(t>temp){
                            mMap[i][t] = WAY;
                            t++;
                        }
                    }
                }
                if(levelindex == 9){
                    t=i+1;
                    int temp=t;
                    while(mMap[temp][j] == BIU2){
                        temp++;
                    }
                    if(mMap[temp][j]!=UFO){
                        while(t<temp){
                            mMap[t][j] = WAY;
                            t++;
                        }
                    }
                    t=i-1;
                    temp=t;
                    while(mMap[temp][j] == BIU2){
                        temp--;
                    }
                    if(mMap[temp][j]!=UFO){
                        while(t>temp){
                            mMap[t][j] = WAY;
                            t--;
                        }
                    }
                }
                break;
            case DES:
                picpath = ":/res/gold.png";
                break;
            case DOOR:
                picpath = ":/res/end.png";
                break;
            case MANINWAY:
                picpath = ":/res/kabi.png";
                break;
            case ENEMY:
                picpath = ":/res/enemy.png";
                break;
            case ENEMYBEATTACK:
                picpath = ":/res/enemy2.png";
                break;
            case CAVE:
                picpath = ":/res/cave.png";
                break;
            case CAVEBOX:
                picpath = ":/res/block2.png";
                break;
            case HURT:
                picpath = ":/res/hurtkabi.png";
                break;
            case ATKER:
                picpath = ":/res/atk.png";
                break;
            case ATKMAN:
                picpath = ":/res/atkkabi.png";
                break;
            case SENEMY:
                picpath = ":/res/enemy3.png";
                break;
            case SENEMYD:
                picpath = ":/res/enemy4.png";
                break;
            case ATKMANHURT:
                picpath = ":/res/atkmanhurt.png";
                break;
            case BIU:
                picpath = ":/res/biu.png";
                break;
            case BIU2:
                picpath = ":/res/biu2.png";
                break;
            case UFO:
                picpath = ":/res/enemy5.png";
                if(levelindex == 8){
                    t=j-1;
                    while (mMap[i][t]!=0&&mMap[i][t]!=1) {
                        if(mMap[i][t] == 5||mMap[i][t] == 14 ){
                            step =-1;
                        }
                        mMap[i][t] = BIU;
                        t--;
                    }
                }
                if(levelindex == 9){
                    t=i+1;
                    while (mMap[t][j]!=0&&mMap[t][j]!=1) {
                        if(mMap[t][j] == 5||mMap[t][j] == 14 ){
                            step =-1;
                        }
                        mMap[t][j] = BIU2;
                        t++;
                    }
                }
                break;
            }

            QPixmap pix;
            pix.load(QString(picpath));
            pix = pix.scaled(pix.width(),pix.height());
            pDraw->drawPixmap(j*pix.width(),i*pix.height(),pix.width(),pix.height(),pix);
            QFont font = pDraw->font(); // 获取当前字体
            font.setPointSize(32); // 设置字体大小
            pDraw->setFont(font); // 应用新的字体
            pDraw->setPen(QPen(Qt::white));
            pDraw->drawText(QRect(100, 125, 500, 625), QString("STEP : %1").arg(step));

        }
    }
}

bool Rule::keyboard(QKeyEvent *e)
{
    int x0 = manX;
    int y0 = manY;
    int x1;
    int y1;
    int x2;
    int y2;

    switch (e->key())
    {
    //上
    case Qt::Key_A:{
        x1 = manX;
        y1 = manY - 1;
        x2 = manX;
        y2 = manY - 2;
        break;
    }

    //下
    case Qt::Key_D:{
        x1 = manX;
        y1 = manY + 1;
        x2 = manX;
        y2 = manY + 2;
        break;
    }

    //左
    case Qt::Key_W:{
        x1 = manX - 1;
        y1 = manY;
        x2 = manX - 2;
        y2 = manY;
        break;
    }

    //右
    case Qt::Key_S:{
        x1 = manX + 1;
        y1 = manY;
        x2 = manX + 2;
        y2 = manY;
        break;
    }


    default:
        return false;
    }

    if(updata(x0, y0, x1, y1, x2, y2))
        return true;
    return false;
}

bool Rule::updata(int x0, int y0, int x1, int y1, int x2, int y2)
{


    //在这里进行音效的播放
    soundEffect(mMap[x1][y1]);

    switch (mMap[x1][y1]) {
    //前面是背景墙
    case WALL:{
        return false;
        break;
    }

    //前面是路
    case WAY:{
        if(mMap[x0][y0] == MANINWAY){
            mMap[x1][y1] = MANINWAY;
            manX = x1;
            manY = y1;
            mMap[x0][y0] = WAY;
            break;
        }

        if(mMap[x0][y0] == HURT){
            mMap[x1][y1] = MANINWAY;
            manX = x1;
            manY = y1;
            mMap[x0][y0] = CAVE;
            break;
        }

        if(mMap[x0][y0] == ATKMAN){
            mMap[x1][y1] = ATKMAN;
            manX = x1;
            manY = y1;
            mMap[x0][y0] = WAY;
            break;
        }

        if(mMap[x0][y0] == ATKMANHURT){
            mMap[x1][y1] = ATKMAN;
            manX = x1;
            manY = y1;
            mMap[x0][y0] = CAVE;
            break;
        }
        break;
    }

    case BOX:{
        if(mMap[x2][y2] == WAY)
    {
        if(mMap[x0][y0] == ATKMAN){

            mMap[x2][y2] = BOX;
            mMap[x1][y1] = ATKMAN;
            manX = x1;
            manY = y1;
            mMap[x0][y0] = WAY;
            break;
        }

        if(mMap[x0][y0] == MANINWAY)
        {
            mMap[x2][y2] = BOX;
            mMap[x1][y1] = MANINWAY;
            manX = x1;
            manY = y1;
            mMap[x0][y0] = WAY;
            break;
        }

        if(mMap[x0][y0] == HURT)
        {
            mMap[x2][y2] = BOX;
            mMap[x1][y1] = MANINWAY;
            manX = x1;
            manY = y1;
            mMap[x0][y0] = CAVE;
            break;
        }

        if(mMap[x0][y0] == ATKMANHURT)
        {
            mMap[x2][y2] = BOX;
            mMap[x1][y1] = ATKMAN;
            manX = x1;
            manY = y1;
            mMap[x0][y0] = CAVE;
            break;
        }
    }

        if(mMap[x2][y2] == CAVE){
        if(mMap[x0][y0] == ATKMAN){

            mMap[x2][y2] = CAVEBOX;
            mMap[x1][y1] = ATKMAN;
            manX = x1;
            manY = y1;
            mMap[x0][y0] = WAY;
            break;
        }

        if(mMap[x0][y0] == MANINWAY)
        {
            mMap[x2][y2] = CAVEBOX;
            mMap[x1][y1] = MANINWAY;
            manX = x1;
            manY = y1;
            mMap[x0][y0] = WAY;
            break;
        }

        if(mMap[x0][y0] == HURT)
        {
            mMap[x2][y2] = CAVEBOX;
            mMap[x1][y1] = MANINWAY;
            manX = x1;
            manY = y1;
            mMap[x0][y0] = CAVE;
            break;
        }

        if(mMap[x0][y0] == ATKMANHURT)
        {
            mMap[x2][y2] = CAVEBOX;
            mMap[x1][y1] = ATKMAN;
            manX = x1;
            manY = y1;
            mMap[x0][y0] = CAVE;
            break;
        }
    }

        if(mMap[x2][y2] == BIU){
        mMap[x2][y2] = BOX;
        if(mMap[x0][y0] == ATKMAN)
            mMap[x1][y1] = ATKMAN;
        else
            mMap[x1][y1] = MANINWAY;
        manX = x1;
        manY = y1;
        mMap[x0][y0] = WAY;
    }
        if(mMap[x2][y2] == BIU2){
        mMap[x2][y2] = BOX;
        if(mMap[x0][y0] == ATKMAN)
            mMap[x1][y1] = ATKMAN;
        else
            mMap[x1][y1] = MANINWAY;
        manX = x1;
        manY = y1;
        mMap[x0][y0] = WAY;
    }
        break;
    }

    case CAVEBOX:{
        if(mMap[x2][y2] == WAY)
        {
            if(mMap[x0][y0] == ATKMAN)
            {
                mMap[x2][y2] = BOX;
                mMap[x1][y1] = ATKMANHURT;
                manX = x1;
                manY = y1;
                mMap[x0][y0] = WAY;
                break;
            }

            if(mMap[x0][y0] == MANINWAY)
            {
                mMap[x2][y2] = BOX;
                mMap[x1][y1] = HURT;
                manX = x1;
                manY = y1;
                mMap[x0][y0] = WAY;
                break;
            }

            if(mMap[x0][y0] == HURT)
            {
                mMap[x2][y2] = BOX;
                mMap[x1][y1] = HURT;
                manX = x1;
                manY = y1;
                mMap[x0][y0] = CAVE;
                break;
            }

            if(mMap[x0][y0] == ATKMANHURT)
            {
                mMap[x2][y2] = CAVEBOX;
                mMap[x1][y1] = ATKMANHURT;
                manX = x1;
                manY = y1;
                mMap[x0][y0] = CAVE;
                break;
            }
        }

        if(mMap[x2][y2] == CAVE){
            if(mMap[x0][y0] == ATKMAN)
            {
                mMap[x2][y2] = CAVEBOX;
                mMap[x1][y1] = ATKMAN;
                manX = x1;
                manY = y1;
                mMap[x0][y0] = WAY;
                break;
            }

            if(mMap[x0][y0] == MANINWAY)
            {
                mMap[x2][y2] = CAVEBOX;
                mMap[x1][y1] = MANINWAY;
                manX = x1;
                manY = y1;
                mMap[x0][y0] = WAY;
                break;
            }

            if(mMap[x0][y0] == HURT)
            {
                mMap[x2][y2] = CAVEBOX;
                mMap[x1][y1] = MANINWAY;
                manX = x1;
                manY = y1;
                mMap[x0][y0] = CAVE;
                break;
            }
        }
        break;
    }

    case ENEMY:{
        mMap [x1][y1] = ENEMYBEATTACK;
        break;
    }

    case ENEMYBEATTACK:{
        mMap [x1][y1] = WAY;
        break;
    }

    case DES:{
        mMap[x1][y1] = MANINDES;
        gameover();
        break;
    }

    case DOOR:{
        mMap [x1][y1] = MANINDOOR;
        gameover();
        break;
    }

    case CAVE:{
        if(mMap[x0][y0] == MANINWAY){
            mMap[x1][y1] = HURT;
            step--;
            manX = x1;
            manY = y1;
            mMap[x0][y0] = WAY;
            break;
        }

        if(mMap[x0][y0] == HURT)
        {
            mMap[x1][y1] = HURT;
            step--;
            manX = x1;
            manY = y1;
            mMap[x0][y0] = CAVE;
            break;
        }

        if(mMap[x0][y0] == ATKMAN)
        {
            mMap[x1][y1] = ATKMANHURT;
            manX = x1;
            manY = y1;
            mMap[x0][y0] = WAY;
            break;
        }

        if(mMap[x0][y0] == ATKMANHURT)
        {
            mMap[x1][y1] = ATKMANHURT;
            manX = x1;
            manY = y1;
            mMap[x0][y0] = CAVE;
            break;
        }
        break;
    }

    case ATKER:{
        mMap[x1][y1] = ATKMAN;
        manX = x1;
        manY = y1;
        if(mMap[x0][y0] == MANINWAY)
        {
            mMap[x0][y0] = WAY;
            break;
        }
        if(mMap[x0][y0] == HURT)
        {
            mMap[x0][y0] = CAVE;
            break;
        }
        break;
    }

    case SENEMY:{
        if(mMap[x0][y0] == ATKMAN){
            mMap[x1][y1] = SENEMYD;
        }
        break;
    }
    case SENEMYD:{
        mMap [x1][y1] = WAY;
        break;
    }

    case BIU:{
        step = -1;
        break;
    }
    case BIU2:{
        step = -1;
        break;
    }

    default:{
        break;
    }
    }

    return true;
}

//判断游戏结束条件
int Rule::gameover()
{
    for(int i = 0;i<WNUM;i++)
        for(int j = 0;j< HNUM;j++)
        {
            if(mMap[i][j] == MANINDES || mMap[i][j] == MANINDOOR){
                return 1;
            }
        }
    return 0;
}


