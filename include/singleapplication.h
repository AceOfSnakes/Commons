#ifndef SINGLEAPPLICATION_H
#define SINGLEAPPLICATION_H
#include <QString>
#include <QObject>
#include <QLocalServer>
class SingleApplication : public QObject
{
    Q_OBJECT
public:
    SingleApplication(const QString &uniqueKey, QObject *parent = nullptr);
    bool checkInstance();
signals:
    void wakeUpRequested();
private slots:
    void handleNewConnection();
private:
    QString serverName;
    QLocalServer *server = nullptr;
};

#endif // SINGLEAPPLICATION_H
