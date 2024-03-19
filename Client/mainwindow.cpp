#include "mainwindow.h"
#include "queueview.h"
#include "ui_mainwindow.h"
#include "client.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(new QueueView(m_client));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setClient(Client *client)
{
    m_client = client;
}

