#ifndef TIMINGDIALOG_H
#define TIMINGDIALOG_H

#include <QDialog>
#include <QTime>
#include <QMessageBox>
#include <QKeyEvent>

#include <vector>

#include "tapdialog.h"

typedef struct {
    QString id;
    QString name;
    QString artist;
    QTime offset;
    float BPM;
    float speed;
} SongData;

namespace Ui {
class TimingDialog;
}

class TimingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TimingDialog(QWidget *parent = nullptr);
    ~TimingDialog();
    void setSongData(SongData *sd);
    void setPrevSongDate(SongData &sd);
    void setSongPosition(QTime *t);
    void setCurrentBeat(int *cb);

private slots:
    void on_setPositionButton_clicked();

    void on_tapButton_pressed();

    void on_BPM_lineEdit_textChanged(const QString &arg1);

    void on_timeEdit_timeChanged(const QTime &time);

    void on_artist_lineEdit_textChanged(const QString &arg1);

    void on_id_lineEdit_textChanged(const QString &arg1);

    void on_name_lineEdit_textChanged(const QString &arg1);

    void on_buttonBox_rejected();

    void on_speed_lineEdit_textChanged(const QString &arg1);

private:
    Ui::TimingDialog *ui;
    SongData *song_data;
    SongData prev;
    QTime *songPosition;
    TapDialog tapDialog;
    int *currentBeat;
};

#endif // TIMINGDIALOG_H
