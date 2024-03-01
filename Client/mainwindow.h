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
private:
    Ui::MainWindow *ui;
    QPushButton *m_button;
    Client *m_client;
};
#endif // MAINWINDOW_H
