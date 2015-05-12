#include "spritepanel.h"
#include"manager/charactermanager.h"
#include"manager/terrainmanager.h"
#include"manager/decorationmanager.h"
#include<QVBoxLayout>

SpritePanel::SpritePanel(QWidget *parent)
    :QDialog(parent)
{
    listWidget=new QListWidget;
    listWidget->setIconSize(QSize(60,60));

}


SpritePanel::~SpritePanel()
{
    delete listWidget;
    delete addButton;
}

CharacterPanel::CharacterPanel(QWidget *parent)
    :SpritePanel(parent)
{

    update();
    addButton=new QPushButton(QString("Add"),this);

    connect(addButton,SIGNAL(clicked()),this,SLOT(add()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(listWidget);
    mainLayout->addWidget(addButton);
    setLayout(mainLayout);

    setWindowTitle(tr("Character Panel"));
}

void CharacterPanel::update()
{
    QMapIterator<QString,Character*> i(CharacterManager::instance()->getPrototype());
    while(i.hasNext())
    {
        i.next();
        QListWidgetItem *item=new QListWidgetItem(i.key(),listWidget);
        item->setIcon(QIcon(i.value()->getPixmap()));
        item->setData(Qt::UserRole,i.key());
    }
}

void CharacterPanel::clear()
{
    listWidget->clear();
}

void CharacterPanel::add()
{
    CharacterManager::instance()->addCharacter(listWidget->currentItem()->data(Qt::UserRole).toString());
}

TerrainPanel::TerrainPanel(QWidget *parent)
    :SpritePanel(parent)
{
    update();
    addButton=new QPushButton(QString("Add"),this);

    connect(addButton,SIGNAL(clicked()),this,SLOT(add()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(listWidget);
    mainLayout->addWidget(addButton);
    setLayout(mainLayout);

    setWindowTitle(tr("Terrain Panel"));
}

void TerrainPanel::update()
{
    QMapIterator<QString,Terrain*> i(TerrainManager::instance()->getPrototype());
    while(i.hasNext())
    {
        i.next();
        QListWidgetItem *item=new QListWidgetItem(i.key(),listWidget);
        item->setIcon(QIcon(i.value()->getPixmap()));
        item->setData(Qt::UserRole,i.key());
    }
}

void TerrainPanel::clear()
{
    listWidget->clear();
}

void TerrainPanel::add()
{
    TerrainManager::instance()->addTerrain(listWidget->currentItem()->data(Qt::UserRole).toString());
}


DecorationPanel::DecorationPanel(QWidget *parent)
    :SpritePanel(parent)
{
    update();
    addButton=new QPushButton(QString("Add"),this);

    connect(addButton,SIGNAL(clicked()),this,SLOT(add()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(listWidget);
    mainLayout->addWidget(addButton);
    setLayout(mainLayout);

    setWindowTitle(tr("Decoration Panel"));
}

void DecorationPanel::update()
{
    QMapIterator<QString,Decoration*> i(DecorationManager::instance()->getPrototype());
    while(i.hasNext())
    {
        i.next();
        QListWidgetItem *item=new QListWidgetItem(i.key(),listWidget);
        item->setIcon(QIcon(i.value()->getPixmap()));
        item->setData(Qt::UserRole,i.key());
    }
}

void DecorationPanel::clear()
{
    listWidget->clear();
}

void DecorationPanel::add()
{
    DecorationManager::instance()->addDecoration(listWidget->currentItem()->data(Qt::UserRole).toString());
}


