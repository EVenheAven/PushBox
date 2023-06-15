#ifndef CONFIG_H
#define CONFIG_H

/********** 游戏配置数据 **********/
#define GAME_TITLE "BoxMan" //窗口标题

/********** 地图类配置数据 **********/
#define WNUM 12         //横向方块数目
#define HNUM 12         //纵向方块数目
#define BLOCKW 100      //方块宽度
#define BLOCKH 100      //方块高度
#define WALL 0          //表示背景
#define BOX 1           //表示砖
#define WAY 2           //表示通道
#define DES 3           //表示目的地
#define ENEMY 4         //表示敌人
#define MANINWAY 5      //表示人在通道
#define MANINDES 6      //表示人在目的地
#define ENEMYBEATTACK 7 //敌人残血
#define CAVE 8          //地刺
#define DOOR 9          //最终大门
#define ATKER 10        //武器
#define SENEMY 11       //精英
#define SENEMYD 12      //精英怪死亡
#define HURT 13         //受伤
#define ATKMAN 14       //超级卡比
#define CAVEBOX 15      //地刺砖
#define ATKMANHURT 16   //超级卡比受伤
#define BIU 17          //横着的激光
#define UFO 18          //激光发射怪
#define BIU2 19         //竖着的激光
#define MANINDOOR 20    //最终大门进入
#define LOSE 21         //失败

#endif // CONFIG_H
