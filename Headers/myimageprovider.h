#ifndef MYIMAGEPROVIDER_H
#define MYIMAGEPROVIDER_H

#include <QObject>

class myimageprovider : public QObject
{
    Q_OBJECT
public:
    explicit myimageprovider(QObject *parent = nullptr);

signals:

};

#endif // MYIMAGEPROVIDER_H
