#include "mainwindow.h"
#include "queueview.h"
#include "ui_mainwindow.h"
#include "client.cpp"
#include "gameview.h"

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
    connect(m_client, &Client::showGameView, this, &MainWindow::showGameView);
    setCentralWidget(new QueueView(m_client));
}

void MainWindow::showGameView(){
    setCentralWidget(new GameView(m_client));
}

