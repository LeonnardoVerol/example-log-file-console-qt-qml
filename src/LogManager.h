#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <QObject>

class LogManager : public QObject
{
    Q_OBJECT

public:
    static LogManager *GetInstance(QObject *parent = nullptr);

    static void writeLogToFile(QtMsgType type, const QMessageLogContext &context, const QString &message);
    static void writeLogToConsole(QtMsgType type, const QMessageLogContext &context, const QString &message);

signals:
    void addLineAll(QString line); // you can create filters if you want to

protected:
    static LogManager* singleton;
    explicit LogManager(QObject *parent = nullptr);
};

#endif // LOGMANAGER_H
