/*
 * mainwindow.h
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTime>
#include <QMessageBox>
#include <QtMath>
#include "src/core/musicplayer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MusicPlayer *mp;
    QModelIndex selectedTrack;
    void loadDir();
    void updateSlider(qint64 mPos);
    qint64 toSec(qint64 mSec);
    QString getTime(qint64 duration);

private slots:
    void on_nextB_clicked();
    void on_prevB_clicked();
    void on_stopB_clicked();
    void on_controlB_clicked();
    void sliderToMpos(int newValue);
    void on_actionlocal_triggered();
    void on_actionQuit_triggered();
    void on_actionAbout_triggered();
    void on_actionAbout_Qt_triggered();
    void on_media_change(QMediaContent media);
    void on_pState_change(QMediaPlayer::State state);
    void on_pMediaPos_change(qint64 pos);
};

#endif // MAINWINDOW_H
