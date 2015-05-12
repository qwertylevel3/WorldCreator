#ifndef SPRITEPANEL_H
#define SPRITEPANEL_H

#include<QDialog>
#include"sprite.h"
#include"manager/manager.h"
#include<QListWidget>
#include<QPushButton>

class SpritePanel : public QDialog
{
    Q_OBJECT
public:
    SpritePanel(QWidget *parent = 0);
    ~SpritePanel();
public slots:
    virtual void add(){}
    virtual void update(){}
    virtual void clear(){}
protected:
    QListWidget* listWidget;
    QPushButton* addButton;

};

class CharacterPanel:public SpritePanel
{
    Q_OBJECT
public:
    CharacterPanel(QWidget* parent=0);
    ~CharacterPanel(){}
public slots:
    void add();
    void update();
    void clear();
};

class TerrainPanel:public SpritePanel
{
    Q_OBJECT
public:
    TerrainPanel(QWidget* parent=0);
    ~TerrainPanel(){}
public slots:
    void add();
    void update();
    void clear();
};

class DecorationPanel:public SpritePanel
{
    Q_OBJECT
public:
    DecorationPanel(QWidget* parent=0);
    ~DecorationPanel(){}
public slots:
    void add();
    void update();
    void clear();
};



#endif // SPRITEPANEL_H
