#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "client.h"
#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setClient(Client *client);
    ~MainWindow();

private slots:
    void handleButton();
    void on_lineEdit_textEdited(const QString &arg1);
    void on_LoginButton_clicked();

private:
    Ui::MainWindow *ui;
    QPushButton *m_startButton;
    Client *m_client;
    QString m_username;
};
#endif // MAINWINDOW_H
