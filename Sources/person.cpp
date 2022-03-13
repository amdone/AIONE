#include "person.h"
#include <QDebug>
#include <windows.h>

Person::Person(QString name, int age) noexcept :_name(name), _age(age)  {}

void Person::printInfo() const noexcept{
    qDebug() << this->_name << " " << this->_age <<"\n";
    //Sleep(1000);
    emit this->qmlCall();
}
