#ifndef QTUTILS_H
#define QTUTILS_H

#include <fmod.hpp>
#include <fmod_errors.h>
#include <QtWidgets>
#include <QMessageBox>
#include <random>

class QTUtils
{
public:
    QTUtils();
    static void checkErrors(QWidget *window, FMOD_RESULT result);
    static int getRandomInt(int min, int max);
};

#endif // QTUTILS_H
