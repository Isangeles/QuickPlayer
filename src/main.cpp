#include "gui/mainwindow.h"
#include "core/musicplayer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //TEST CODE
    MusicPlayer *quickPlayer = new MusicPlayer();
    //quickPlayer->next();
    std::cout << (quickPlayer->playlist()->currentMedia().canonicalUrl().toString().toStdString());
    //quickPlayer->play();
    //
    return a.exec();
}
