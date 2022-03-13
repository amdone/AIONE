/*!
 *@file QmlLanguage.cpp
 *@brief 语言切换
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
#include "qmllanguage.h"
#include <QDebug>

QmlLanguage::QmlLanguage(QGuiApplication &app, QQmlApplicationEngine& engine)
{
    m_app = &app;
    m_engine = &engine;
}

void QmlLanguage::setLocalLanguage(){
    QTranslator translator;
    QLocale locale;
    if( locale.language() == QLocale::English ) {
        translator.load(":/translators/en_us.qm");
    }
    else if( locale.language() == QLocale::Chinese ) {
        translator.load(":/translators/zh_CN.qm");
    }
    m_app->installTranslator(&translator);
    m_engine->retranslate();
}

void QmlLanguage::setLanguage(int indexOfLanguage)
{
    QTranslator translator;
    if (indexOfLanguage == 0)
    {
        translator.load(":/translators/en_US.qm");
    }else if (indexOfLanguage == 1) {
        translator.load(":/translators/zh_CN.qm");
    }else{
        translator.load(":/translators/en_US.qm");
    }
    m_app->installTranslator(&translator);
    m_engine->retranslate();
}

int QmlLanguage::getLocalLanguage(){
    QLocale locale;
    if(locale.language() == QLocale::English){
        return 0;
    }else if(locale.language() == QLocale::Chinese){
        return 1;
    }
    return 0;
}
