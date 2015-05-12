#include "game.h"
#include <QtGui/QKeyEvent>
#include<math.h>
#include<QTimer>
#include<QDebug>
#include"character/character.h"
#include"terrain/terrain.h"
#include"bullet/bullet.h"
#include"effect/effect.h"
#include"manager/charactermanager.h"
#include"manager/terrainmanager.h"
#include"manager/bulletmanager.h"
#include"manager/effectmanager.h"
#include"manager/decorationmanager.h"
#include"character/player.h"
#include"manager/missionmanager.h"

//----------------------------GraphicsView------------------------------//

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    scaleFactor=1;
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    double numDegrees = event->delta()/8.0;
    double numSteps = numDegrees/15.0;
    scaleFactor = pow(1.125,numSteps);

    scale(scaleFactor,scaleFactor);
}

void GraphicsView::keyPressEvent(QKeyEvent *e)
{
    emit keyPressed(e);
}
void GraphicsView::keyReleaseEvent(QKeyEvent *e)
{
    emit keyReleased(e);
}

void GraphicsView::resizeEvent(QResizeEvent *)
{

}



//----------------------------Game------------------------------//


Game::Game()
{

}

Game* Game::p=0;

Game* Game::instance()
{
    if(!p)
        p=new Game;
    return p;
}


bool Game::init(const QString& worldName)
{
    G=200;
    T=0.05;

    showRects=true;

    scene=new QGraphicsScene;
    scene->setSceneRect(-500,-500,2000,1000);
    view=new GraphicsView();
    view->setScene(scene);

    view->setDragMode(QGraphicsView::ScrollHandDrag);

    CharacterManager::instance()->init(scene,QString(worldName));
    BulletManager::instance()->init(scene,worldName);
    TerrainManager::instance()->init(scene,QString(worldName));
    EffectManager::instance()->init(scene,worldName);
    DecorationManager::instance()->init(scene,QString(worldName));
    MissionManager::instance()->init(worldName);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(25);


    return true;
}

void Game::start()
{
    MissionManager::instance()->start(0);
}

//QGraphicsObject.pos()返回值整整少了一半，不知为何,故乘2补全
//因为scene坐标系统整整大了一倍。。。。。
//scene坐标系莫名其妙为2像素1单位，而且改不了我日，真日了狗了
bool Game::isCollision(Sprite *a, Sprite *b)
{
    for(int i=0;i<a->getRects().size();i++)
    {
        for(int j=0;j<b->getRects().size();j++)
        {
            QRectF aa=a->getRects()[i];
            //qDebug()<<a->pos().x()<<" "<<a->pos().y()<<endl;
            //qDebug()<<"a"<<a->pos().x()<<" "<<a->pos().y()<<" "<<a->getPixmapWidth()<<" "<<a->getPixmapHeight()<<endl;
            aa.setCoords(a->pos().x()*2+aa.x(),
                         a->pos().y()*2+aa.y(),
                         a->pos().x()*2+aa.x()+aa.width(),
                         a->pos().y()*2+aa.y()+aa.height());
            QRectF bb=b->getRects()[j];
            //qDebug()<<"b"<<b->pos().x()<<" "<<b->pos().y()<<" "<<b->getPixmapWidth()<<" "<<b->getPixmapHeight()<<endl;
            bb.setCoords(b->pos().x()*2+bb.x(),
                         b->pos().y()*2+bb.y(),
                         b->pos().x()*2+bb.x()+bb.width(),
                         b->pos().y()*2+bb.y()+bb.height());
            QRectF r=aa.intersected(bb);
            //qDebug()<<"r"<<r.x()<<" "<<r.y()<<" "<<r.width()<<" "<<r.height()<<endl;
            //发现接触
            if(r.width()!=0 && r.height()!=0)
            {
                return true;
            }
        }
    }
    return false;
}


void Game::update()
{
    CharacterManager::instance()->update();
    TerrainManager::instance()->update();
    BulletManager::instance()->update();
    EffectManager::instance()->update();
    DecorationManager::instance()->update();

    simulation();
    bulletCollision();

    scene->update();
    view->viewport()->update();

}

void Game::drawCoordinate()
{
    scene->addText("(0,0)");
    for(int i=-2000;i<2000;i+=100)
    {
        scene->addLine(i,-1000,i,1000);
    }
    for(int i=-1000;i<1000;i+=100)
    {
        scene->addLine(-2000,i,2000,i);
    }
}

void Game::simulation()
{
    QList<Character*>& allCharacter=CharacterManager::instance()->getAllCharacter();
    QList<Terrain*>& allTerrain=TerrainManager::instance()->getAllTerrain();


    for(int i=0;i<allCharacter.size();i++)
    {
        if(!allCharacter[i]->isOutOfScene())
        {
            //纵向检测
            double V=allCharacter[i]->getVy();
            allCharacter[i]->setVy(allCharacter[i]->getVy()+G*T);
            allCharacter[i]->setY(G*T*T/2+V*T+allCharacter[i]->pos().y());

            bool flag=false;
            for(int j=0;j<allTerrain.size();j++)
            {
                if(isCollision(allCharacter[i],allTerrain[j]))
                {
                    flag=true;
                    break;
                }
            }
            if(flag)//碰撞
            {

                allCharacter[i]->setY(allCharacter[i]->pos().y()-G*T*T/2-V*T);
                allCharacter[i]->setStable(true);//不稳定态结束//跳跃用...
                allCharacter[i]->setVy(0);
            }

            //横向检测
            flag=false;
            allCharacter[i]->setPos(allCharacter[i]->pos().x()+allCharacter[i]->getVx()
                           ,allCharacter[i]->pos().y());
            for(int j=0;j<allTerrain.size();j++)
            {
                if(isCollision(allCharacter[i],allTerrain[j]))
                {
                    flag=true;
                    break;
                }
            }
            if(flag)
            {
                allCharacter[i]->setPos(allCharacter[i]->pos().x()-(allCharacter[i]->getVx())
                               ,allCharacter[i]->pos().y());
            }
        }

    }
}

void Game::bulletCollision()
{
    QList<Bullet*>& allBullet=BulletManager::instance()->getAllBullet();
    QList<Character*>& allCharacter=CharacterManager::instance()->getAllCharacter();

    for(int i=0;i<allBullet.size();i++)
    {
        allBullet[i]->setPos(allBullet[i]->pos().x()+allBullet[i]->getVx()
                             ,allBullet[i]->pos().y()+allBullet[i]->getVy());
        allBullet[i]->update();
        for(int j=1;j<allCharacter.size();j++)
        {
            if(allBullet[i]->isVisible()
                    && allCharacter[j]->getCureState()!=3
                    && allCharacter[j]->isVisible()
                    && allCharacter[j]->getType()==Character::Enemy
                    && isCollision(allBullet[i],allCharacter[j]))
            {
                QPointF temp1=allBullet[i]->pos();
                QPointF temp2=allCharacter[j]->pos();
                QPointF temp=(temp1+temp2)/2;
                allBullet[i]->setVisible(false);
                allCharacter[j]->skillStart(3);

                Effect* effect=EffectManager::instance()->addEffect("explosion_1");
                effect->setPos(temp);
            }
        }
    }
}



Game::~Game()
{
    delete scene;
    delete view;
    delete timer;
}

