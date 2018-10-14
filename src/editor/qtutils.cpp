#include "qtutils.h"

QTUtils::QTUtils()
{

}

void QTUtils::checkErrors(QWidget *window, FMOD_RESULT result)
{
    if(result != FMOD_OK)
        QMessageBox::critical(window, "FMOD Error", FMOD_ErrorString(result));
}

int QTUtils::getRandomInt(int min, int max)
{
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(min,max); // guaranteed unbiased

    return uni(rng);
}
