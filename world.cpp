#include "world.h"
#include<QTimer>
#include"manager/bulletmanager.h"
#include"manager/charactermanager.h"
#include"manager/decorationmanager.h"
#include"manager/effectmanager.h"
#include"manager/missionmanager.h"
#include"manager/terrainmanager.h"
#include<QDebug>
#include<QFile>
#include<QDir>
#include<QMessageBox>
#include"mission.h"
#include"worlddescriptiondialog.h"

World::World()
{
    scene=new QGraphicsScene;
    scene->setSceneRect(-500,-500,2000,1000);
    view=new GraphicsView();
    view->setScene(scene);

    view->setDragMode(QGraphicsView::ScrollHandDrag);

    view->setScene(scene);
    currSprite=0;
    spriteInClipboard=0;

    doSimulate=false;

    connect(CharacterManager::instance(),SIGNAL(selected(Sprite*)),this,SLOT(getSelected(Sprite*)));
    connect(TerrainManager::instance(),SIGNAL(selected(Sprite*)),this,SLOT(getSelected(Sprite*)));
    connect(DecorationManager::instance(),SIGNAL(selected(Sprite*)),this,SLOT(getSelected(Sprite*)));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(25);
}

void World::getSelected(Sprite *p)
{
    currSprite=p;
}

void World::cut()
{
    spriteInClipboard=currSprite;
    del();
}

void World::copy()
{
    spriteInClipboard=currSprite;
}

void World::close()
{
    G=200;
    T=0.05;

    CharacterManager::instance()->clear();
    BulletManager::instance()->clear();
    TerrainManager::instance()->clear();
    EffectManager::instance()->clear();
    DecorationManager::instance()->clear();

    worldName="";
}

void World::del()
{
    if(currSprite)
    {
        QGraphicsScene* s=currSprite->scene();
        if(s)
        {
            //在场景中remove后，Manager update时自动去除
            s->removeItem(currSprite);
            currSprite=0;
            somethingChanged();
        }
    }
}

//从面板添加Sprite，自动添加，只需善后
void World::addSpriteFromPanel(Sprite *p)
{
    if(p)
    {
        view->centerOn(p);
        somethingChanged();
    }
}

void World::setSimulateGravity(bool s)
{
    doSimulate=s;
}

void World::paste()
{
    if(spriteInClipboard)
    {
        Sprite* p=spriteInClipboard->getManager()->add(spriteInClipboard);
//        qDebug()<<QCursor::pos()<<endl;
//        qDebug()<<view->mapToScene(QCursor::pos())<<endl;
//        p->setPos(view->mapToScene(QCursor::pos()).x()-p->getPixmap().size().width()/4
//                  ,view->mapToScene(QCursor::pos()).y()-p->getPixmap().size().height()/2);
        p->setPos(view->mapToScene(QCursor::pos()));
        view->centerOn(p);
        somethingChanged();
    }
}

void World::somethingChanged()
{
    emit modified();
}


bool World::init(const QString& worldName)
{
    G=200;
    T=0.05;

    CharacterManager::instance()->clear();
    BulletManager::instance()->clear();
    TerrainManager::instance()->clear();
    EffectManager::instance()->clear();
    DecorationManager::instance()->clear();

    CharacterManager::instance()->init(scene,QString("common"));
    BulletManager::instance()->init(scene,"common");
    TerrainManager::instance()->init(scene,QString("common"));
    EffectManager::instance()->init(scene,"common");
    DecorationManager::instance()->init(scene,QString("common"));
    //MissionManager::instance()->init("common");

    //MissionManager::instance()->init(worldName);



    loadWorld(worldName);

    setCharacterDragable(true);
    setDecorationDragable(true);
    setTerrainDragable(true);

    return true;
}

void World::setTerrainDragable(bool d)
{
    for(int i=0;i<TerrainManager::instance()->getTotalNumber();i++)
    {
        TerrainManager::instance()->getAllTerrain()[i]->setDragable(d);
    }
}

void World::setCharacterDragable(bool d)
{
    for(int i=0;i<CharacterManager::instance()->getTotalNumber();i++)\
    {
        CharacterManager::instance()->getAllCharacter()[i]->setDragable(d);
    }
}

void World::setDecorationDragable(bool d)
{
    for(int i=0;i<DecorationManager::instance()->getTotalNumber();i++)
    {
        DecorationManager::instance()->getAllDecoration()[i]->setDragable(d);
    }
}

void World::setShowRect(bool s)
{
    showRect=s;
    DecorationManager::instance()->setShowRect(s);
    CharacterManager::instance()->setShowRect(s);
    TerrainManager::instance()->setShowRect(s);
}
bool World::showGrid()
{
    return false;
}

bool World::writeFile(const QString &fileName)
{
    QString path=QDir::currentPath()
            +QDir::separator()+"world"
            +QDir::separator()+worldName
            +QDir::separator()+fileName+".wod";

    QFile file(path);

    //qDebug()<<path<<endl;

    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(0,tr("World"),tr("cannot write file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    out<<worldName<<endl;

    out<<G<<" "<<T<<endl;

    writeTerrain(out);
    writeDecoration(out);
    writeCharacter(out);

    return true;
}

bool World::isCollision(Sprite *a, Sprite *b)
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


void World::update()
{
    CharacterManager::instance()->update();
    TerrainManager::instance()->update();
    BulletManager::instance()->update();
    EffectManager::instance()->update();
    DecorationManager::instance()->update();

    if(doSimulate)
    {
        simulation();
    }

    scene->update();
    view->viewport()->update();
}


void World::simulation()
{
    QList<Character*>& allCharacter=CharacterManager::instance()->getAllCharacter();
    QList<Terrain*>& allTerrain=TerrainManager::instance()->getAllTerrain();


    for(int i=0;i<allCharacter.size();i++)
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


bool World::createNewWorld(const QString fileName)
{ 
    QString path=QDir::currentPath()
            +QDir::separator()+"world"
            +QDir::separator()+fileName;
    QDir dir;
    dir.mkdir(path);

    worldName=fileName;

    QFile file(path+"/"+worldName+".wod");
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(0,tr("World"),tr("cannot write file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    out<<fileName<<endl;
    this->init(worldName);

    return true;
}

bool World::loadFile(const QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"can not open "<<fileName<<endl;
        return false;
    }
    QTextStream in(&file);
    in>>worldName;

    init(worldName);
    return true;
}

void World::newMission(const QString &missionName)
{

}

bool World::loadWorld(const QString& worldName)
{
    QString path=QDir::currentPath()
            +QDir::separator()+"world"
            +QDir::separator()+worldName
            +QDir::separator()+worldName+".wod";

    QFile file(path);

    //qDebug()<<path<<endl;

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"can not find file:"<<path<<"data.dat"<<endl;
        return false;
    }
    QTextStream in(&file);

    in>>this->worldName;

    in>>G>>T;

    bool loadSuccess=false;
    loadSuccess=loadTerrain(in);
    if(!loadSuccess)
    {
        qDebug()<<"load terrain fail"<<endl;
        return false;
    }
    loadSuccess=loadDecoration(in);
    if(!loadSuccess)
    {
        qDebug()<<"load decoration fail"<<endl;
        return false;
    }
    loadSuccess=loadCharacter(in);
    if(!loadSuccess)
    {
        qDebug()<<"load character fail"<<endl;
        return false;
    }

    return true;
}

bool World::loadTerrain(QTextStream& in)
{
    int num;
    in>>num;
    for(int i=0;i<num;i++)
    {
        QString name;
        in>>name;
        Terrain* t=TerrainManager::instance()->addTerrain(name);
        int x,y;
        in>>x>>y;
        t->setPos(x,y);
    }
    return true;
}

bool World::loadCharacter(QTextStream& in)
{
    int num;
    in>>num;
    for(int i=0;i<num;i++)
    {
        QString name;
        in>>name;
        Character* c=CharacterManager::instance()->addCharacter(name);
        QString type;
        in>>type;
        if(type=="Enemy")
        {
            c->setType(Character::Enemy);
        }
        else if(type=="NPC")
        {
            c->setType(Character::NPC);
        }
        else if(type=="Player")
        {
            qDebug()<<"error to add player"<<endl;
        }
        else
        {
            qDebug()<<"unknow type"<<endl;
        }
        int x,y;
        in>>x>>y;
        c->setPos(x,y);
    }
    return true;
}

bool World::loadDecoration(QTextStream& in)
{
    int num;
    in>>num;
    for(int i=0;i<num;i++)
    {
        QString name;
        in>>name;
        Decoration* d=DecorationManager::instance()->addDecoration(name);
        int x,y;
        in>>x>>y;
        d->setPos(x,y);
    }
    return true;
}

bool World::writeTerrain(QTextStream &out)
{
    int num=TerrainManager::instance()->getTotalNumber();
    out<<num<<endl;
    for(int i=0;i<num;i++)
    {
        QString name=TerrainManager::instance()->getAllTerrain()[i]->getName();
        out<<name<<endl;
        QPointF p=TerrainManager::instance()->getAllTerrain()[i]->pos();
        out<<int(p.x())<<" "<<int(p.y())<<endl;

    }
    return true;
}

bool World::writeCharacter(QTextStream &out)
{
    int num=CharacterManager::instance()->getTotalNumber();
    out<<num<<endl;
    for(int i=0;i<num;i++)
    {
        QString name=CharacterManager::instance()->getAllCharacter()[i]->getName();
        out<<name<<endl;

        Character::Type t=CharacterManager::instance()->getAllCharacter()[i]->getType();

        if(t==Character::Enemy)
        {
            out<<"Enemy"<<endl;
        }
        else if(t==Character::NPC)
        {
            out<<"NPC"<<endl;
        }
        else if(t==Character::Player)
        {
            out<<"Player"<<endl;
        }
        else
        {
            return false;
        }

        QPointF p=CharacterManager::instance()->getAllCharacter()[i]->pos();
        out<<int(p.x())<<" "<<int(p.y())<<endl;

    }
    return true;
}

bool World::writeDecoration(QTextStream &out)
{
    int num=DecorationManager::instance()->getTotalNumber();
    out<<num<<endl;
    for(int i=0;i<num;i++)
    {
        QString name=DecorationManager::instance()->getAllDecoration()[i]->getName();
        out<<name<<endl;
        QPointF p=DecorationManager::instance()->getAllDecoration()[i]->pos();
        out<<int(p.x())<<" "<<int(p.y())<<endl;

    }
    return true;
}

void World::worldDescription()
{
    WorldDescriptionDialog dialog;
    dialog.exec();
}

void World::spriteSetting()
{
    if(currSprite)
    {
        currSprite->setting();
    }
}




World::~World()
{
    delete scene;
    delete view;
    delete currSprite;
    delete timer;
}

