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
    void generateClient(QUrl url, bool debug);
    ~MainWindow();

private slots:
    void showGameView();
    void showError(QJsonObject &payload);

private:
    Ui::MainWindow *ui;
    Client *m_client;
};
#endif // MAINWINDOW_H
