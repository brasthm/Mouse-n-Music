#include "timingdialog.h"
#include "ui_timingdialog.h"

TimingDialog::TimingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimingDialog)
{
    ui->setupUi(this);
    tapDialog.setDialogText(ui->BPM_lineEdit);
}

TimingDialog::~TimingDialog()
{
    delete ui;
}

void TimingDialog::setSongData(SongData *sd)
{
    song_data = sd;
}

void TimingDialog::setPrevSongDate(SongData &sd)
{
    prev = sd;
}

void TimingDialog::setSongPosition(QTime *t)
{
    songPosition = t;
}

void TimingDialog::setCurrentBeat(int *cb)
{
    currentBeat = cb;
}

void TimingDialog::on_setPositionButton_clicked()
{
    ui->timeEdit->setTime(*songPosition);
}

void TimingDialog::on_tapButton_pressed()
{
    tapDialog.setPrevBPM(ui->BPM_lineEdit->text());
    tapDialog.show();
}


void TimingDialog::on_BPM_lineEdit_textChanged(const QString &arg1)
{
    if(arg1.toInt() != 0)
    {
        song_data->BPM = arg1.toFloat();
        unsigned int pos, off = static_cast<unsigned int>(60000 * song_data->offset.minute() + 1000 * song_data->offset.second() + song_data->offset.msec());
        unsigned int delta = static_cast<unsigned int>(60000 / song_data->BPM);
        pos = static_cast<unsigned int>(60000 * songPosition->minute() + 1000 * songPosition->second() + songPosition->msec());
        *currentBeat = (static_cast<int>(pos)-static_cast<int>(off))/static_cast<int>(delta);
    }

}

void TimingDialog::on_timeEdit_timeChanged(const QTime &time)
{
    song_data->offset = time;

    unsigned int pos, off = static_cast<unsigned int>(60000 * song_data->offset.minute() + 1000 * song_data->offset.second() + song_data->offset.msec());
    unsigned int delta = static_cast<unsigned int>(60000 / song_data->BPM);
    pos = static_cast<unsigned int>(60000 * songPosition->minute() + 1000 * songPosition->second() + songPosition->msec());
    *currentBeat = (static_cast<int>(pos)-static_cast<int>(off))/static_cast<int>(delta);
}

void TimingDialog::on_artist_lineEdit_textChanged(const QString &arg1)
{
    song_data->artist = arg1;
}

void TimingDialog::on_id_lineEdit_textChanged(const QString &arg1)
{
    song_data->id = arg1;
}

void TimingDialog::on_name_lineEdit_textChanged(const QString &arg1)
{
    song_data->name = arg1;
}

void TimingDialog::on_buttonBox_rejected()
{
    *song_data = prev;
}

void TimingDialog::on_speed_lineEdit_textChanged(const QString &arg1)
{
    song_data->speed = arg1.toFloat();
}
