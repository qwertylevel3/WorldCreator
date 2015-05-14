#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsObject>
#include<QVector>
#include<QMap>
#include"state.h"
#include<QTextStream>

class Skill;
class GraphicsView;
class Manager;

//----------------------------Sprite------------------------------//

class Sprite : public QGraphicsObject
{
    Q_OBJECT
public:
    Sprite(const QString &worldName,const QString &name,GraphicsView* rec=0,QGraphicsItem * parent = 0);
    ~Sprite();

    virtual void update();
    virtual bool read(const QString& worldName,const QString &name);
    virtual Sprite* clone();
    
    void setOrientation(int ori){orientation=ori;}
    void setCurrState(int index){currState=index;}
    void setCurrSkill(int index){currSkill=index;}
    void setViewReceiver(GraphicsView* rec);
    void setDragable(bool d);
    void setName(QString n){name=n;}
    void setManager(Manager* p){manager=p;}
    void setShowRect(bool s){showRect=s;}
    void setStateTotal(int t){stateTotal=t;}

    int getStateTotal(){return stateTotal;}
    bool getShowRect(){return showRect;}
    Manager* getManager(){return manager;}
    QString getName(){return name;}
    int getOrientation(){return orientation;}
    int getCureState(){return currState;}
    GraphicsView* getReceiver(){return receiver;}
    State* getState(int index){return stateBox[index];}
    QVector<QRectF>& getRects(){return stateBox[currState]->getRects();}

    QPixmap getPixmap(){return stateBox[currState]->getPixmap();}
    int getPixmapWidth(){return stateBox[currState]->getPixmapWidth();}
    int getPixmapHeight(){return stateBox[currState]->getPixmapHeight();}
    bool isDragable(){return dragable;}

    QList<State*>& getStateBox(){return stateBox;}
    QList<Skill*>& getSkillBox(){return skillBox;}


    virtual void skillStart(int index);
    virtual void skillEnd(int index);
    virtual void skillRun(int index);
    virtual void setting();
    virtual void readFromStream(QTextStream& in);
    virtual void writeToStream(QTextStream& out);
    virtual void init();
public slots:
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
protected:
    Sprite(){}
    QPoint mouseOffset;
    QString name;
    Manager* manager;

    bool dragable;
    int stateTotal;
    int currState;
    int currSkill;
    int orientation;//朝向，1右，-1左
    bool showRect;

    QList<State*> stateBox;
    QList<Skill*> skillBox;
    GraphicsView* receiver;//接受键盘事件的view
};

#endif // SPRITE_H
