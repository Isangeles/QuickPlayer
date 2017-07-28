#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QListView>
#include <QFileSystemModel>
#include <QStandardPaths>
#include <QMediaContent>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <iostream>
/**
 * @brief The MusicPlayer class Class for music player
 */
class MusicPlayer : public QMediaPlayer
{
    Q_OBJECT
public:
    MusicPlayer();
    ~MusicPlayer();
    bool openIn(QString dir);
    bool add(QMediaContent media);
    bool addAll(QList<QMediaContent> media);
    void play(QMediaContent media);
    void play(int index);
    void play(QString mediaPath);
    void play();
    void next();
    void prev();
    std::string getTrackPath();
    QDir getDir();
    QStringList getFormats();

private:
    QDir *currentDir;
    QMediaPlaylist *playList;
    QList<QMediaContent> getDirContent();
    int getFromPlaylist(QMediaContent mediaToCheck);
};

#endif // MUSICPLAYER_H
