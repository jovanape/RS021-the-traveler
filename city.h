#ifndef CITY_H
#define CITY_H

#include "building.h"
#include "evil.h"
#include "player.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QString>

/*
 * Ovo je apstraktna klasa koja sluzi za pravljenje gradova/ nivoa
 *
 */


class City : public QGraphicsView {
    Q_OBJECT
public:
    City(QString name, int playerPosX, int playerPosY, int playerStep, int level_number);
    QGraphicsScene * getScene();
    ~City();

    int getLevel();
    QString getName();

    void buildBasic(const QJsonObject &jsonObj, const QString &img, const QJsonArray &buildings);
    virtual void buildSpecial(QJsonObject &json) = 0;

public slots:
    void finished();
    void removeTee(QGraphicsItem *item);

signals:
    void goToNextLevel(int level);

protected:
    Player *_player;
    int _level_number;
    QGraphicsScene *_scene;
    QList<Building*> listOfBuildings;
    QString _name;
    QList<Evil*> listOfEvils;
    int numOfTees = 2;

    void setBackgraundImage(QString path);
    void setCityDimensions(int x, int y, int w, int h);
};

#endif // CITY_H
