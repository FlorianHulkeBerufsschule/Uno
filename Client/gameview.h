#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include "client.h"

namespace Ui {
class GameView;
}

class GameView : public QWidget
{
    Q_OBJECT

public:
    explicit GameView(Client *client, QWidget *parent = nullptr);
    ~GameView();

private:
    Ui::GameView *ui;
    Client *m_client;
};

#endif // GAMEVIEW_H
