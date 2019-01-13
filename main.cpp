#include "mainmenuwindow.h"
#include <QApplication>
#include "evil.h"
#include <QMediaPlayer>

int change_now;

QMediaPlayer *music;
QString nameText;

int main(int argc, char *argv[])
{
    music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/bckg_music.mp3"));
    QString nameText = "";

    change_now = 0;

    QApplication a(argc, argv);
    MainMenuWindow w;
    w.show();

    return a.exec();
}
