#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "client.h"
#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class StartWindow;
}
QT_END_NAMESPACE

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr);
    void setClient(Client *client);
    ~StartWindow();

private slots:
    void handleButton();
    void on_lineEdit_textEdited(const QString &arg1);
    void on_LoginButton_clicked();

private:
    Ui::StartWindow *ui;
    QPushButton *m_startButton;
    Client *m_client;
    QString m_username;
};
#endif // STARTWINDOW_H
