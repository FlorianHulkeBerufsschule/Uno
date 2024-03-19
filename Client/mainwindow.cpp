#include "mainwindow.h"
#include "queueview.h"
#include "ui_mainwindow.h"
#include "client.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateClient(QUrl url, bool debug)
{
    m_client = new Client(url, debug);
    setCentralWidget(new QueueView(m_client));
}

//void MainWindow::generateClient()

