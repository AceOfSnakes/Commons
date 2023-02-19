#ifndef COMMONS_H
#define COMMONS_H

#include <QString>
#include <QEvent>
#include <QMainWindow>

#ifdef __linux__
    #define WINDOW_FLAGS Qt::Drawer | Qt::Dialog
#else
    #define WINDOW_FLAGS Qt::Dialog
#endif

class Commons
{
public:
    Commons();
    QString static compilerQString();
    QString static prettyProductName();
    void static moveWindow(QObject *obj, QEvent *event, QMainWindow *window);
};

#endif // COMMONS_H
