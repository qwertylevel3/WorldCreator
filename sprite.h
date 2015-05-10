#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsObject>
#include<QVector>
#include<QMap>
#include"state.h"

class Skill;
class GraphicsView;

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

    QString getName(){return name;}
    int getOrientation(){return orientation;}
    int getCureState(){return currState;}
    GraphicsView* getReceiver(){return receiver;}
    State* getState(int index){return stateBox[index];}
    QVector<QRectF>& getRects(){return stateBox[currState]->getRects();}

    int getPixmapWidth(){return stateBox[currState]->getPixmapWidth();}
    int getPixmapHeight(){return stateBox[currState]->getPixmapHeight();}
    bool isDragable(){return dragable;}

    QList<State*>& getStateBox(){return stateBox;}
    QList<Skill*>& getSkillBox(){return skillBox;}


    virtual void skillStart(int index);
    virtual void skillEnd(int index);
    virtual void skillRun(int index);
public slots:
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
protected:
    Sprite(){}
    QString name;
    bool dragable;
    int stateTotal;
    int currState;
    int currSkill;
    int orientation;//朝向，1右，-1左

    QList<State*> stateBox;
    QList<Skill*> skillBox;
    GraphicsView* receiver;//接受键盘事件的view
};

#endif // SPRITE_H
