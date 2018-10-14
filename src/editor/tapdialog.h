#ifndef TAPDIALOG_H
#define TAPDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QKeyEvent>
#include <QLineEdit>
#include <QTime>

namespace Ui {
class TapDialog;
}

class TapDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TapDialog(QWidget *parent = nullptr);
    ~TapDialog();
    void setDialogText(QLineEdit *edit);
    void setPrevBPM(QString bpm);

private slots:
    void on_buttonBox_accepted();
    void keyPressEvent(QKeyEvent *event);

    void on_buttonBox_rejected();

private:
    Ui::TapDialog *ui;
    QTime BPMclock;
    QLineEdit *BPM_Text;
    size_t nbInsert = 0;
    std::vector<float> BPM = {120, 120, 120, 120, 120};
    QString prevBPM;

};

#endif // TAPDIALOG_H
