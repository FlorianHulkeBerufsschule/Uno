#include "gameview.h"
#include "ui_gameview.h"

GameView::GameView(Client *client, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameView)
    , m_client(client)
{
    ui->setupUi(this);
}

GameView::~GameView()
{
    delete ui;
}
