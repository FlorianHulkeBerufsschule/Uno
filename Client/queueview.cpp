#include "queueview.h"
#include "ui_queueview.h"

QueueView::QueueView(Client *client, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QueueView)
    , m_client(client)
{
    ui->setupUi(this);
}

QueueView::~QueueView()
{
    delete ui;
}
