#ifndef QUEUEVIEW_H
#define QUEUEVIEW_H

#include "client.h"
#include <QWidget>
#include <QPushButton>

namespace Ui {
class QueueView;
}

class QueueView : public QWidget
{
    Q_OBJECT

public:
    explicit QueueView(Client *client,QWidget *parent = nullptr);
    ~QueueView();


private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void handleLoginButton();

    void on_StartButton_clicked();

private:
    Ui::QueueView *ui;
    Client *m_client;
    QString m_username;
    QPushButton *m_loginButton;

signals:

};

#endif // QUEUEVIEW_H
