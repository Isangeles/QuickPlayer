/*
 * musicplayer.h
 *
 * Copyright 2017-2019 Dariusz Sikora <dev@isangeles.pl>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QListView>
#include <QFileSystemModel>
#include <QStandardPaths>
#include <QMediaPlaylist>
#include <QMediaPlayer>
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
