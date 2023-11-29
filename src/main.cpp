#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "src/LogManager.h"


#ifdef QT_DEBUG
static QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(0);
#endif

void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &message)
{
    LogManager::writeLogToFile(type, context, message);

    LogManager::writeLogToConsole(type, context, message);

#ifdef QT_DEBUG
    // Call the default handler.
    (*QT_DEFAULT_MESSAGE_HANDLER)(type, context, message);
#endif
}

void installMessageHandler()
{
    qInstallMessageHandler(customMessageHandler);

#ifdef QT_DEBUG
    qSetMessagePattern("[%{time yyyy-MM-ddThh:mm:ss.zzzZ t}] [%{type}] %{message} (%{file}:%{line}, %{function})");
#elif
    qSetMessagePattern("[%{time yyyy-MM-ddThh:mm:ss.zzzZ t}] [%{type}] %{message}");
#endif
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterSingletonType<LogManager>("LogManager", 1, 0, "LogManager", [&](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        return LogManager::GetInstance();
    });

    installMessageHandler();

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/ui/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    // Depending on what you do inside your MessageHandler, it might be easier/better to reset it on close
    QObject::connect(
        &app, &QGuiApplication::aboutToQuit,
        &app, []()
        {
            qInstallMessageHandler(0);
        });
    
    engine.load(url);

    return app.exec();
}
