#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QtGui>
#include <QApplication>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <filesystem>
#include <fstream>
#include <string>

#include "qtutils.h"
#include "timingdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setCurrentBeat();

private slots:
    void on_actionNewSong_triggered();
    void updateTimeBar();

    void on_timeBar_sliderMoved(int position);
    void on_playButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);
    void on_timeEdit_userTimeChanged(const QTime &time);

    void on_actionPlay_Pause_triggered();

    void on_actionSong_Info_triggered();

    void keyPressEvent(QKeyEvent *event);

    void beepMetronome();

    void on_actionPlay_Metronome_toggled();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    FMOD::System *soundSystem_;
    FMOD::Channel *soundChannel_, *sfxChannel_;
    FMOD::Sound *song_, *beep_;
    FMOD::DSP *pitchShifter1_, *pitchShifter2_;
    QTimer *timer_, *metronomeBeep_;
    QTime songPosition_;
    QString songPath = "";
    bool isDSPAdded_;

    float songFrequency_;
    int currentBeat_ = 0;

    SongData songData;
    TimingDialog timingDiag;

};

#endif // MAINWINDOW_H
