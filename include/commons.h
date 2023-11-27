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
#if QT_VERSION >= 0x060000
    void static moveWindow(QObject *obj, QEvent *event, QMainWindow *window);
#endif
};

#endif // COMMONS_H
