#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace fs = std::experimental::filesystem;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    FMOD_RESULT result;

    soundChannel_ = nullptr;

    result = FMOD::System_Create(&soundSystem_);
    QTUtils::checkErrors(this, result);

    result = soundSystem_->init(32, FMOD_INIT_NORMAL, nullptr);
    QTUtils::checkErrors(this, result);

    timer_ = new QTimer(this);
    QObject::connect(timer_, SIGNAL(timeout()), this, SLOT(updateTimeBar()));
    timer_->start(100); //time specified in ms

    metronomeBeep_ = new QTimer(this);
    QObject::connect(metronomeBeep_, SIGNAL(timeout()), this, SLOT(beepMetronome()));
    metronomeBeep_->start(50); //time specified in ms

    timingDiag.setSongData(&songData);
    timingDiag.setSongPosition(&songPosition_);
    timingDiag.setCurrentBeat(&currentBeat_);

    result = soundSystem_->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &pitchShifter1_);
    QTUtils::checkErrors(this, result);

    result = soundSystem_->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &pitchShifter2_);
    QTUtils::checkErrors(this, result);

    result = pitchShifter1_->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 1);
    QTUtils::checkErrors(this, result);

    result = pitchShifter2_->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 1);
    QTUtils::checkErrors(this, result);

    result = soundSystem_->createSound("../sfx/bip.flac", FMOD_2D | FMOD_LOOP_OFF, nullptr, &beep_);
    QTUtils::checkErrors(this, result);

    isDSPAdded_ = false;

    songData.offset = QTime(0,0);
    songData.BPM = 120;
    songData.speed = 500;

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    if(isDSPAdded_)
    {
        soundChannel_->removeDSP(pitchShifter1_);
        soundChannel_->removeDSP(pitchShifter2_);
    }

    pitchShifter1_->release();
    pitchShifter2_->release();
    song_->release();
    beep_->release();
    soundSystem_->release();

    delete ui;
    delete timer_;
    delete metronomeBeep_;
}

void MainWindow::setCurrentBeat()
{
    bool isPlaying;
    soundChannel_->isPlaying(&isPlaying);
    if(ui->actionPlay_Metronome->isChecked() && isPlaying)
    {
        unsigned int pos, off = static_cast<unsigned int>(60000 * songData.offset.minute() + 1000 * songData.offset.second() +songData.offset.msec());
        unsigned int delta = static_cast<unsigned int>(60000 / songData.BPM);
        soundChannel_->getPosition(&pos, FMOD_TIMEUNIT_MS);
        currentBeat_ = (static_cast<int>(pos)-static_cast<int>(off))/static_cast<int>(delta);
    }
}

void MainWindow::on_actionNewSong_triggered()
{
    soundChannel_->stop();
    QString fichier = QFileDialog::getOpenFileName(this, "Open a song", QString(), "Song (*.mp3 *.ogg *.wav *.flac)");
    FMOD_RESULT result = soundSystem_->createStream(fichier.toStdString().c_str(), FMOD_2D | FMOD_CREATESTREAM, nullptr, &song_);
    if(result == FMOD_OK)
    {
        soundSystem_->playSound(song_, nullptr, false, &soundChannel_);
        soundChannel_->getFrequency(&songFrequency_);

        songPath = fichier;

        on_actionSong_Info_triggered();

        if(isDSPAdded_)
        {
            result = soundChannel_->removeDSP(pitchShifter1_);
            QTUtils::checkErrors(this, result);
            result = soundChannel_->removeDSP(pitchShifter2_);
            QTUtils::checkErrors(this, result);
        }

        FMOD_RESULT r1, r2;
        r2 = soundChannel_->addDSP(FMOD_CHANNELCONTROL_DSP_HEAD, pitchShifter2_);
        QTUtils::checkErrors(this, r2);
        r1 = soundChannel_->addDSP(FMOD_CHANNELCONTROL_DSP_HEAD, pitchShifter1_);
        QTUtils::checkErrors(this, r1);

        if(r1 == FMOD_OK && r2 == FMOD_OK)
            isDSPAdded_ = true;
    }
    else
        QMessageBox::critical(this, "FMOD Error", FMOD_ErrorString(result));

    ui->playButton->setText("Pause");
    ui->comboBox->setCurrentText("x1");
}

void MainWindow::updateTimeBar()
{
    bool isPlaying;
    soundChannel_->isPlaying(&isPlaying);
    if(isPlaying)
    {
        unsigned int songPosition, songLength = 0;
        soundChannel_->getPosition(&songPosition, FMOD_TIMEUNIT_MS);
        song_->getLength(&songLength, FMOD_TIMEUNIT_MS);

        QTime qsongLength(0, 0), qsongPositon(0, 0);
        qsongLength = qsongLength.addMSecs(static_cast<int>(songLength));
        qsongPositon = qsongPositon.addMSecs(static_cast<int>(songPosition));
        songPosition_ = qsongPositon;

        ui->songLengthLabel->setText(qsongLength.toString("mm:ss:zzz"));
        bool paused;
        soundChannel_->getPaused(&paused);
        if(!paused)
            ui->timeEdit->setTime(qsongPositon);
        ui->timeBar->setValue(static_cast<int>(static_cast<float>(ui->timeBar->maximum()) * static_cast<float>(songPosition) / static_cast<float>(songLength)));
    }

}

void MainWindow::on_timeBar_sliderMoved(int position)
{
    unsigned songLength;
    song_->getLength(&songLength, FMOD_TIMEUNIT_MS);

    soundChannel_->setPosition(static_cast<unsigned int>(position/static_cast<float>(ui->timeBar->maximum()) * songLength), FMOD_TIMEUNIT_MS);
    setCurrentBeat();
}

void MainWindow::on_playButton_clicked()
{
    bool isPaused;
    soundChannel_->getPaused(&isPaused);
    soundChannel_->setPaused(!isPaused);
    const char* message = !isPaused ? "Play" : "Pause";
    ui->playButton->setText(message);
    ui->timeEdit->setEnabled(!isPaused);
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QString text = arg1;
    text.remove(0, 1);
    float factor = text.toFloat();
    soundChannel_->setFrequency(songFrequency_ * factor);
    if(factor < 0.5f)
    {
        pitchShifter1_->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 2);
        pitchShifter2_->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 2/factor);
    }
    else if(factor > 2.f)
    {
        pitchShifter1_->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.5);
        pitchShifter2_->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.5f/factor);
    }
    else
    {
        pitchShifter1_->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 1/factor);
        pitchShifter2_->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 1);
    }

}

void MainWindow::on_timeEdit_userTimeChanged(const QTime &time)
{
    bool paused;
    soundChannel_->getPaused(&paused);
    if(paused)
        soundChannel_->setPosition(static_cast<unsigned int>(time.msec() + time.second()*1000 + time.minute()*60000), FMOD_TIMEUNIT_MS);
}

void MainWindow::on_actionPlay_Pause_triggered()
{
    on_playButton_clicked();
}

void MainWindow::on_actionSong_Info_triggered()
{
    timingDiag.setPrevSongDate(songData);
    timingDiag.show();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    unsigned int pos, off = static_cast<unsigned int>(60000 * songData.offset.minute() + 1000 * songData.offset.second() +songData.offset.msec());
    unsigned int delta = static_cast<unsigned int>(60000 / (4.f*songData.BPM));
    soundChannel_->getPosition(&pos, FMOD_TIMEUNIT_MS);
    unsigned int section = (pos-off)/delta;
    QTime qsongPositon(0,0);


    if(event->key() == Qt::Key_Left)
    {
        soundChannel_->setPosition((section-1)*delta + off, FMOD_TIMEUNIT_MS);
        qsongPositon = qsongPositon.addMSecs(static_cast<int>((section-1)*delta + off));
        ui->timeEdit->setTime(qsongPositon);
    }

    if(event->key() == Qt::Key_Right)
    {
        soundChannel_->setPosition((section+1)*delta + off, FMOD_TIMEUNIT_MS);
        qsongPositon = qsongPositon.addMSecs(static_cast<int>((section+1)*delta + off));
        ui->timeEdit->setTime(qsongPositon);
    }

    if(event->key() == Qt::Key_O)
    {
        unsigned int off = static_cast<unsigned int>(60000 * songData.offset.minute() + 1000 * songData.offset.second() + songData.offset.msec());
        soundChannel_->setPosition(off, FMOD_TIMEUNIT_MS);
    }

}

void MainWindow::beepMetronome()
{
    if(ui->actionPlay_Metronome->isChecked())
    {
        unsigned int pos, off = static_cast<unsigned int>(60000 * songData.offset.minute() + 1000 * songData.offset.second() + songData.offset.msec());
        float delta = 60000 / songData.BPM;
        soundChannel_->getPosition(&pos, FMOD_TIMEUNIT_MS);
        int section = static_cast<int>((static_cast<int>(pos)-static_cast<int>(off))/delta);
        if(section > currentBeat_)
        {
            soundSystem_->playSound(beep_, nullptr, false, &sfxChannel_);
            sfxChannel_->setVolume(5);
            currentBeat_++;
        }
    }
}

void MainWindow::on_actionPlay_Metronome_toggled()
{
    setCurrentBeat();

}

void MainWindow::on_actionSave_triggered()
{
    fs::path path = "../music";
    path/=songData.id.toStdString();
    if(songPath != "" && songData.id != "")
    {
        if(!fs::exists(path))
            fs::create_directory(path);

        fs::path mnmPath = path/songData.id.toStdString();
        mnmPath += ".mnm";
        std::ofstream file(mnmPath.string(), std::ios::out);

        fs::path sp = songPath.toStdString();
        path/=sp.filename();
        if(!fs::equivalent(sp, path))
            fs::copy_file(sp, path);

        float offset = 60 * songData.offset.minute() + songData.offset.second() + songData.offset.msec()/1000.f;

        file << "Name=" << songData.name.toStdString() << std::endl;
        file << "Artist=" << songData.artist.toStdString() << std::endl;
        file << "Path=" << sp.filename() << std::endl;
        file << "Offset=" << offset << std::endl;
        file << "BPM=" << songData.BPM << std::endl;
        file << "Length=" << ui->songLengthLabel->text().toStdString() << std::endl;
        file << "DATA" << std::endl;

        unsigned int songLength;
        song_->getLength(&songLength, FMOD_TIMEUNIT_MS);
        float sl = (songLength/1000.f - offset)/60;


        for(int i = 0; i < songData.BPM * sl; i++)
            file << offset + 60.f/songData.BPM * i << " " << offset + 60.f/songData.BPM * (i+0.5f) << " " << songData.speed << " " << QTUtils::getRandomInt(0,7) << std::endl;

        file.close();

        QMessageBox::information(this, "Beatmap saved", "The beatmap have been sucessfully saved.");
    }
}
