#include "queueview.h"
#include "ui_queueview.h"
#include "qjsonobject.h"
#include "qjsonarray.h"

QueueView::QueueView(Client *client, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QueueView)
    , m_client(client)
{
    ui->setupUi(this);

    m_loginButton = new QPushButton("Join", this);
    m_loginButton->setGeometry(QRect(QPoint(840, 420), QSize(240, 40)));
    connect(m_loginButton, &QPushButton::released, this, &QueueView::handleLoginButton);

    connect(m_client, &Client::updatePlayerQueue, this, &QueueView::updatePlayerQueue);

    model = new QStringListModel(this);
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

void QueueView::updatePlayerQueue(QJsonObject &payload)
{
    if(payload.contains("queue") && payload["queue"].isArray())
    {
        QJsonArray queue = payload["queue"].toArray();
        m_queue.clear();
        for (int i = 0; i < queue.count(); i++)
        {
            m_queue.append(queue.at(i).toString());
        }
        model->setStringList(m_queue);
        ui->PlayerQueue->setModel(model);
    }

}

