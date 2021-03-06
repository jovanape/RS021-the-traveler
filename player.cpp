#include "player.h"
#include "building.h"
#include <QGraphicsScene>
#include <QDebug>
#include "sushi.h"
#include "city.h"
#include "game.h"
#include <QGraphicsView>
#include <QGraphicsItem>
#include "tee.h"

Player::Player(int x, int y, int step){
    _xPos = x;
    _yPos = y;
    _step = step;
    this->setPos(_xPos,_yPos);
    this->setPixmap(_left);

    /*
     * Da bi objekat mogao da odreaguje na neki event mora da se fokusira.
     * Ovo nam je potrebno za kretanje.
     */

    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

    _fakePlayer = new QGraphicsPixmapItem;
    _fakePlayer->setPos(_xPos,_yPos);
    _fakePlayer->setPixmap(QPixmap(":/images/images/fake-player.png"));
    _fakePlayer->setScale(0.6);
}

Player::~Player(){

}

void Player::keyPressEvent(QKeyEvent *event){

    if(event->key() == Qt::Key_Left){
        _fakePlayer->setPos(x() - _step, y());
        checkCollisionWithFood();
        if(collisionWithBuildings() == false){
            if (pos().x() > 0) {
                setPos(x() - _step, y());
                this->setPixmap(_left);
            }
        }
    }
    else if(event->key() == Qt::Key_Right){
        _fakePlayer->setPos(x() + _step, y());
        checkCollisionWithFood();
        if(collisionWithBuildings() == false){
            if (pos().x() + 60 < 900) {
                this->setPixmap(_right);
                setPos(x() + _step, y());
            }

            if (pos().x() + 60 >= 900 && pos().y() > 400 and _toTheExit == true) {
                // donji desni ugao
                emit escapedEvilObjects();
            }
        }
    }
    else if(event->key() == Qt::Key_Up){
        _fakePlayer->setPos(x(), y() - _step);
        checkCollisionWithFood();
        if(collisionWithBuildings() == false) {
            if (pos().y() > 0) {
                this->setPixmap(_left);
                setPos(x(), y() - _step);
            }
        }
    }
    else if(event->key() == Qt::Key_Down){
        _fakePlayer->setPos(x(), y() + _step);
        checkCollisionWithFood();
        if(collisionWithBuildings() == false) {
            if (pos().y() + 110 < 599) {
                this->setPixmap(_right);
                setPos(x(), y() + _step);
            }
        }
    }
}

void Player::keyReleaseEvent(QKeyEvent *event){
    if((event->key() == Qt::Key_Left) ||
       (event->key() == Qt::Key_Right) ||
       (event->key() == Qt::Key_Up) ||
       (event->key() == Qt::Key_Down)){

        _xPos = x();
        _yPos = y();
    }
}


QGraphicsPixmapItem *Player::getFakePlayer(){
    return _fakePlayer;
}

int Player::getX(){
    return _xPos;
}

int Player::getY(){
    return _yPos;
}

bool Player::collisionWithBuildings() {
    QList<QGraphicsItem*> colliding_items = _fakePlayer->collidingItems();
    int n = colliding_items.size();
    for(int i = 0; i < n; ++i){
        if((typeid(*(colliding_items[i])) == typeid(Building))){
            return true;
        }
    }
    return false;
}

void Player::checkCollisionWithFood()
{
    colliding_items2 = _fakePlayer->collidingItems();
    int n = colliding_items2.size();
    for(int i = 0; i < n; ++i){
        if((typeid(*(colliding_items2[i])) == typeid(Sushi)) || (typeid(*(colliding_items2[i])) == typeid(Tee))){
            emit takeFood(colliding_items2[i]);
        }
    }
}

void Player::toTheExit() {
    _toTheExit = true;
}
