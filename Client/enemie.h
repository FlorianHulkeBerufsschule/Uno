#ifndef ENEMIE_H
#define ENEMIE_H

#include <QObject>

class Enemie : public QObject
{
    Q_OBJECT
public:
    explicit Enemie(int cardCount, int id, QString name, QObject *parent = nullptr);
    static Enemie *fromJsonObj(QJsonObject json);
    int getCardCount();
    int getId();
    QString getName();

signals:

private:
    int m_cardCount;
    int m_id;
    QString m_name;
};

#endif // ENEMIE_H
