/*
 * musicplayer.cpp
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

#include "musicplayer.h"
/**
 * @brief MusicPlayer::MusicPlayer Music player constructor, opens music player in system default music directory
 */
MusicPlayer::MusicPlayer()
{
    currentDir = new QDir(QStandardPaths::locate(QStandardPaths::MusicLocation, "", QStandardPaths::LocateDirectory));
    currentDir->setFilter(QDir::Filter::Files);

    currentDir->setNameFilters(getFormats());

    playList = new QMediaPlaylist();
    this->setPlaylist(playList);
    addAll(getDirContent());
}
/**
 * @brief MusicPlayer::~MusicPlayer Music player deconstructor
 */
MusicPlayer::~MusicPlayer()
{
    delete currentDir;
    delete playList;
}
/**
 * @brief MusicPlayer::openIn Opens music player in specified directory
 * @param dir QString with path to desired directory
 * @return True if music player was opened successfully, false otherwise
 */
bool MusicPlayer::openIn(QString dir)
{
    currentDir = new QDir(dir);
    playlist()->clear();
    addAll(getDirContent());
    //next();
    return true;
}
/**
 * @brief MusicPlayer::add Adds specified media to current playlist
 * @param media QMediaContent to add
 * @return True if content was successfully added, fale otherwise
 */
bool MusicPlayer::add(QMediaContent media)
{
    return playList->addMedia(media);
}
/**
 * @brief MusicPlayer::addAll Adds all specified media to current playlist
 * @param media QList with QMediaContent
 * @return True if content was successfully added, false otherwise
 */
bool MusicPlayer::addAll(QList<QMediaContent> media)
{
    return playList->addMedia(media);
}
/**
 * @brief MusicPlayer::play Starts playing specified media
 * @param media QMediaContent to play
 */
void MusicPlayer::play(QMediaContent media)
{
    stop();
    int mediaId = getFromPlaylist(media);
    if(mediaId != -1)
        playlist()->setCurrentIndex(mediaId);
    else
        this->setMedia(media);
    play();
}
/**
 * @brief MusicPlayer::play Starts playing media with specified ID on playlist
 * @param index ID on current playlist
 */
void MusicPlayer::play(int index)
{
    playList->setCurrentIndex(index);
    play();
}

void MusicPlayer::play(QString mediaPath)
{
    QMediaContent media = QMediaContent(QUrl::fromLocalFile(mediaPath));
    play(media);
}

/**
 * @brief MusicPlayer::play Starts or resume playing current media
 */
void MusicPlayer::play()
{
    QMediaPlayer::play();
}
/**
 * @brief MusicPlayer::next Advance to the next track on current playlist
 */
void MusicPlayer::next()
{
    stop();
    playList->next();
    play();
}
/**
 * @brief MusicPlayer::prev Return to the previous track on current playlist
 */
void MusicPlayer::prev()
{
    stop();
    playList->previous();
    play();
}
/**
 * @brief MusicPlayer::getCurrentTrackPath Returns path to current track
 * @return String with path to current media content
 */
std::string MusicPlayer::getTrackPath()
{
    return currentMedia().canonicalUrl().toString().toStdString();
}
/**
 * @brief MusicPlayer::getDir Returns current player directory
 * @return QDir object representing current directory
 */
QDir MusicPlayer::getDir()
{
    return *currentDir;
}
/**
 * @brief MusicPlayer::getFormats Returns list with files formats handled by player
 * @return QStringList with handled extansions
 */
QStringList MusicPlayer::getFormats()
{
    QStringList formatsList;
    formatsList << "*.mp3";
    return formatsList;
}

/**
 * @brief MusicPlayer::getContent Returns QList with all media content in current directory
 * @return QList with QMediaContent
 */
QList<QMediaContent> MusicPlayer::getDirContent()
{
    QList<QMediaContent> mediaList;
    QStringList files = currentDir->entryList();
    for(QString &f : files)
    {
        mediaList.push_back(QUrl::fromLocalFile(currentDir->path() + "/" + f));
    }
    return mediaList;
}
/**
 * @brief MusicPlayer::getFromPlaylist Returns media with specified URL from playlist
 * @param mediaUrl Desired media URL
 * @return QMediaContent or null if content with specified URL was not found
 */
int MusicPlayer::getFromPlaylist(QMediaContent mediaToCheck)
{
    for(int i = 0; i < playList->mediaCount(); i ++)
    {
        QMediaContent media = playList->media(i);
        if(media.canonicalUrl() == mediaToCheck.canonicalUrl())
            return i;
    }
    return -1;
}
