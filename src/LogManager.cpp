#include "LogManager.h"

#include <QGuiApplication>
#include <QDateTime>
#include <QDir>

LogManager *LogManager::singleton = nullptr;

LogManager::LogManager(QObject *parent)
    : QObject{parent}
{
}

LogManager *LogManager::GetInstance(QObject *parent)
{
    if(singleton == nullptr)
    {
        singleton = new LogManager(parent);
    }
    return singleton;
}

void LogManager::writeLogToFile(QtMsgType type, const QMessageLogContext &context, const QString &message)
{
    // you can create filters, for diferent files if you want to
    QString rootPath = QGuiApplication::applicationDirPath();
    QString filename = QString("%1-%2.log")
                           .arg(QGuiApplication::applicationDisplayName())
                           .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd"));

    QString logsDir = QDir::cleanPath(rootPath + QDir::separator() + "logs");
    QDir qdir;
    qdir.mkdir(logsDir);

    QString filepath = QDir::cleanPath(logsDir + QDir::separator() + filename);

    QFile outFile(filepath);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);

    QTextStream textStream(&outFile);
    textStream << qFormatLogMessage(type, context, message) << "\n";

    outFile.close();
}

void LogManager::writeLogToConsole(QtMsgType type, const QMessageLogContext &context, const QString &message)
{
    // you can create filters if you want to
    emit LogManager::GetInstance()->addLineAll(qFormatLogMessage(type, context, message));
}
