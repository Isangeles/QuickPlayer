/*
 * mainwindow.cpp
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

#include "mainwindow.h"
#include "ui_mainwindow.h"
/**
 * @brief MainWindow::MainWindow Main window constructor
 * @param parent Parent widget
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mp = new MusicPlayer();
    loadDir();
    QObject::connect(mp, SIGNAL(mediaChanged(QMediaContent)), this, SLOT(on_media_change(QMediaContent)));
    QObject::connect(mp, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(on_pState_change(QMediaPlayer::State)));
    QObject::connect(mp, SIGNAL(positionChanged(qint64)), this, SLOT(on_pMediaPos_change(qint64)));
    QObject::connect(ui->musicSlider, SIGNAL(sliderMoved(int)), this, SLOT(sliderToMpos(int)));
}
/**
 * @brief MainWindow::~MainWindow Main window deconstructor
 */
MainWindow::~MainWindow()
{
    delete ui;
    delete mp;
}
/**
 * @brief MainWindow::loadDir Loads current player directory to window list view
 */
void MainWindow::loadDir()
{
    QFileSystemModel *model = new QFileSystemModel(ui->playlist);
    model->setRootPath(mp->getDir().path());
    model->setNameFilters(mp->getFormats());
    model->setNameFilterDisables(false);
    ui->playlist->setModel(model);
    ui->playlist->setRootIndex(model->index(model->rootPath()));
}
/**
 * @brief MainWindow::on_nextB_clicked Triggered when next button was clicked
 */
void MainWindow::on_nextB_clicked()
{
    mp->next();
}
/**
 * @brief MainWindow::on_prevB_clicked Triggered when previous button was clicked
 */
void MainWindow::on_prevB_clicked()
{
    mp->prev();
}
/**
 * @brief MainWindow::on_stopB_clicked Triggered when stop button was clicked
 */
void MainWindow::on_stopB_clicked()
{
    mp->stop();
}
/**
 * @brief MainWindow::on_controlB_clicked Triggered when play/stop button was clicked
 */
void MainWindow::on_controlB_clicked()
{
    QModelIndex selectedID = ui->playlist->currentIndex();
    QFileSystemModel *model = (QFileSystemModel*)ui->playlist->model();
    QString selectedMediaPath = model->filePath(selectedID);

    switch (mp->state())
    {
    case QMediaPlayer::PlayingState:
        if(selectedID != selectedTrack)
        {
            mp->play(selectedMediaPath);
        }
        else
        {
            mp->pause();
        }
        break;
    case QMediaPlayer::PausedState:
        if(selectedID != selectedTrack)
        {
            mp->play(selectedMediaPath);
        }
        else
        {
            mp->play();
        }
        break;
    case QMediaPlayer::StoppedState:
        mp->play(selectedMediaPath);
        break;
    default:
        break;
    }
    selectedTrack = selectedID;
}

void MainWindow::sliderToMpos(int newValue)
{
    int value = newValue;
    qint64 duration = mp->duration();
    double timeDouble = (static_cast<double>(duration)*static_cast<double>(value)) / 100;
    qint64 timeToSet = qFloor(timeDouble);
    mp->setPosition(timeToSet);
}

void MainWindow::on_actionlocal_triggered()
{
    QFileDialog fd(this, Qt::Dialog);
    mp->openIn(fd.getExistingDirectory());
    loadDir();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About"), tr("Lightweight music player\r\nCreated by: ") + "Isangeles(github.com/Isangeles)");
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

void MainWindow::on_media_change(QMediaContent media)
{
    //ui->duration->setText(getTime(mp->duration()));
}
/**
 * @brief MainWindow::on_pState_change Triggered when player state was changed
 * @param state New player state
 */
void MainWindow::on_pState_change(QMediaPlayer::State state)
{
    switch (state)
    {
    case QMediaPlayer::PlayingState:
        ui->statusBar->showMessage("Playing: " + QString::fromStdString(mp->getTrackPath()));
        break;
    case QMediaPlayer::PausedState:
        ui->statusBar->showMessage("Paused: " + QString::fromStdString(mp->getTrackPath()));
        break;
    case QMediaPlayer::StoppedState:
        ui->statusBar->showMessage("Stopped: " + QString::fromStdString(mp->getTrackPath()));
        break;
    default:
        break;
    }
}
/**
 * @brief MainWindow::on_pMediaPos_change Triggered when player media position changed
 * @param pos
 */
void MainWindow::on_pMediaPos_change(qint64 pos)
{
    updateSlider(pos);
}
/**
 * @brief MainWindow::updateSlider Updates music slider
 * @param mPos Current media position
 */
void MainWindow::updateSlider(qint64 mPos)
{
    qint64 timeSec = toSec(mPos);
    qint64 durationSec = toSec(mp->duration());
    double floatSliderValue = 0;
    if(timeSec != 0)
        floatSliderValue = (static_cast<double>(timeSec)/static_cast<double>(durationSec)) * 100;
    else
        floatSliderValue = 0;

    qint64 sliderValue = qFloor(floatSliderValue);

    ui->time->setText(getTime(mPos));
    ui->duration->setText(getTime(mp->duration()));
    ui->musicSlider->setValue(sliderValue);
}
/**
 * @brief MusicSlider::getTime Converts milliseconds to time in [h:m:s] format
 * @param duration Time in milliseconds
 * @return String with time
 */
QString MainWindow::getTime(qint64 duration)
{

    int seconds = (duration/1000) % 60;
    int minutes = (duration/60000) % 60;
    int hours = (duration/3600000) % 24;

    QTime time(hours, minutes,seconds);

    return time.toString();
}
/**
 * @brief MusicSlider::toSec Converts milliseconds to seconds
 * @param milSec Time in milliseconds
 * @return Time in seconds
 */
qint64 MainWindow::toSec(qint64 mSec)
{
    return (mSec+500) / 1000;
}
