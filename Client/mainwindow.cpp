#include "mainwindow.h"
#include "ui_StartScreen.h"
#include "client.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create the button, make "this" the parent
    m_button = new QPushButton("StartButton", this);
    // set size and location of the button
    m_button->setGeometry(QRect(QPoint(960, 520), QSize(200, 50)));

    // Connect button signal to appropriate slot
    connect(m_button, &QPushButton::released, this, &MainWindow::handleButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton()
{
    m_button->setText("Pissman");
    m_client->startGame();
}

void MainWindow::setClient(Client *client)
{
    m_client = client;
}
