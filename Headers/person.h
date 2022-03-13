#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <QString>

class Person : public QObject {
    Q_OBJECT
public:
    using QObject::QObject;
    Person(QString name, int age) noexcept;
    Q_INVOKABLE void printInfo() const noexcept;
signals:
    void qmlCall() const;
private:
    QString _name;
    int _age;
};

#endif // PERSON_H
