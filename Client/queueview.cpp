#include "queueview.h"
#include "ui_queueview.h"

QueueView::QueueView(Client *client, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QueueView)
    , m_client(client)
{
    ui->setupUi(this);

    m_loginButton = new QPushButton("Login", this);
    m_loginButton->setGeometry(QRect(QPoint(1000, 420), QSize(111, 41)));
    connect(m_loginButton, &QPushButton::released, this, &QueueView::handleLoginButton);
}

QueueView::~QueueView()
{
    delete ui;
}

void QueueView::on_lineEdit_textChanged(const QString &arg1)
{
    m_username = arg1;
}

void QueueView::handleLoginButton()
{
    m_client->login(m_username);
}


void QueueView::on_StartButton_clicked()
{
     m_client->startGame();
}

