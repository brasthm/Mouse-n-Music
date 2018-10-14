#include "tapdialog.h"
#include "ui_tapdialog.h"

TapDialog::TapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TapDialog)
{
    ui->setupUi(this);
    BPMclock.start();
}

TapDialog::~TapDialog()
{
    delete ui;
}

void TapDialog::setDialogText(QLineEdit *edit)
{
    BPM_Text = edit;
}

void TapDialog::setPrevBPM(QString bpm)
{
    prevBPM = bpm;
}


void TapDialog::on_buttonBox_accepted()
{
    close();
}

void TapDialog::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_T)
    {
        BPM[nbInsert] = 1000 * 60 /static_cast<float>(BPMclock.elapsed());
        nbInsert++;
        if(nbInsert >= BPM.size())
            nbInsert = 0;

        BPMclock.restart();

        float s = 0;

        for(auto x:BPM)
            s+=x;

        ui->BPM_Label->setText(QString::number(static_cast<int>(0.5f + s/BPM.size())));
        BPM_Text->setText(ui->BPM_Label->text());
    }

}

void TapDialog::on_buttonBox_rejected()
{
    BPM_Text->setText(prevBPM);
    close();
}
