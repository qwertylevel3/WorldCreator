#ifndef GAME_H
#define GAME_H

#include<QObject>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QList>

class Sprite;
class Character;
class Terrain;
class Bullet;
class Effect;
class Player;


//----------------------------GraphicsView------------------------------//

class GraphicsView: public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(QWidget *parent = 0);

protected:
    virtual void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void wheelEvent(QWheelEvent* event);
    double scaleFactor;//放缩比例
signals:
    void keyPressed(QKeyEvent* key);
    void keyReleased(QKeyEvent* key);
};

//----------------------------Game------------------------------//

class Game:public QObject
{
    Q_OBJECT
public:
    static Game* instance();
    bool init(const QString& worldName);
    void drawCoordinate();

    QGraphicsScene* getScene(){return scene;}
    GraphicsView* getView() {return view;}
    double getG(){return G;}
    double getT(){return T;}

    //模拟环境，包括重力，地形碰撞等
    void simulation();
    //检测子弹碰撞
    void bulletCollision();

    void setShowRects(bool s) {showRects=s;}
    bool getShowRects(){return showRects;}

    bool isCollision(Sprite* a,Sprite* b);

    void start();
public slots:
    void update();
private:
    static Game* p;
    Game();
    ~Game();

    QGraphicsScene* scene;
    GraphicsView* view;
    QTimer* timer;

    bool showRects;//显示碰撞矩形

    double G;//重力加速度
    double T;//单帧时间间隔
    
    int misssionNumber;//关卡总数
};

#endif // GAME_H
