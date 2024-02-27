#ifndef UNOCARDBASE_H
#define UNOCARDBASE_H

#include <QObject>
#include "Shared_global.h"

class SHARED_EXPORT UnoCardBase : public QObject
{
    Q_OBJECT
public:
    explicit UnoCardBase(const int id, const QString color, QObject *parent = nullptr);
    virtual void toJson(QJsonObject &json) const = 0;
    int getId() const;
    QString getColor() const;
protected:
    const int id;
    const QString color;

signals:
};

#endif // UNOCARDBASE_H
