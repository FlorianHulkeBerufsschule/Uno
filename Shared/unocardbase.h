#ifndef UNOCARDBASE_H
#define UNOCARDBASE_H

#include <QObject>
#include "Shared_global.h"
#include "unocardcolor.h"

class SHARED_EXPORT UnoCardBase : public QObject
{
    Q_OBJECT
public:
    explicit UnoCardBase(const int id, const UnoCardColor color, QObject *parent = nullptr);
    // JSON
    static UnoCardBase* fromJsonObj(QJsonObject object);
    static UnoCardBase* fromJsonDoc(QJsonDocument document);
    static UnoCardBase* fromJsonStr(QString string);
    virtual QJsonObject toJsonObj() const = 0;
    QJsonDocument toJsonDoc() const;
    QString toJsonStr() const;
    // getter
    int getId();
    UnoCardColor getColor();
protected:
    int m_id;
    UnoCardColor m_color;

signals:
};

#endif // UNOCARDBASE_H
