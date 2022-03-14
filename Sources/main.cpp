#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QMetaObject>
#include <QTranslator>
#include <QDebug>
#include <QQmlContext>
#include "qmllanguage.h"
#include "person.h"
#include "jigsaw.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //解决窗口拖拽时闪烁的问题
    QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    QCoreApplication::setOrganizationName("Some organization");


    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    //切换为本地语言
    QTranslator translator;
    QLocale locale;
    if( locale.language() == QLocale::English ) {
        translator.load(":/translators/en_us.qm");
    }
    else if( locale.language() == QLocale::Chinese ) {
        translator.load(":/translators/zh_CN.qm");
    }
    app.installTranslator(&translator);

    //语言切换函数暴露给qml调用
    QmlLanguage qmlLanguage(app, engine);
    engine.rootContext()->setContextProperty("qmlLanguage", &qmlLanguage);

    const QUrl url(QStringLiteral("qrc:/qmls/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    //qmlRegisterType<Info>("infoModel", 1, 0, "Info");

    jigsaw jig(engine);
    //方式2
    auto context = engine.rootContext();
    context->setContextProperty("Jigsaw", &jig);
    engine.load(url);


    auto root = engine.rootObjects();
    auto OpenFloderDialog = root.first()->findChild<QObject*>("floderDialog");
    QObject::connect(OpenFloderDialog, SIGNAL(openForlder(QString)), &jig, SLOT(openFolder(QString)));
    auto JigsawWindow = root.first()->findChild<QObject*>("jigsawWindow");
    QObject::connect(JigsawWindow, SIGNAL(requestImageInfo(int)), &jig, SLOT(requestImageInfo(int)));
    QObject::connect(JigsawWindow, SIGNAL(popImageSignal(int)), &jig, SLOT(popImage(int)));
    QObject::connect(JigsawWindow, SIGNAL(pushImageSignal(int)), &jig, SLOT(pushImage(int)));

    return app.exec();
}


