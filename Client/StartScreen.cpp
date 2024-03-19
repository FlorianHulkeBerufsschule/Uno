#include "startwindow.h"
#include "ui_StartScreen.h"
#include "client.cpp"

StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWindow)
{
    ui->setupUi(this);

    // Create the button, make "this" the parent
    m_startButton = new QPushButton("Start", this);
    // set size and location of the button
    m_startButton->setGeometry(QRect(QPoint(960, 520), QSize(200, 50)));

    // Connect button signal to appropriate slot
    connect(m_startButton, &QPushButton::released, this, &StartWindow::handleButton);
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::handleButton()
{
    //m_button->setText("kek");
    m_client->startGame();
}

void StartWindow::setClient(Client *client)
{
    m_client = client;
}

void StartWindow::on_lineEdit_textEdited(const QString &arg1)
{
    m_username = arg1;
}

void StartWindow::on_LoginButton_clicked()
{
    m_client->login(m_username);
}

