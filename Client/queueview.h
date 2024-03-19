#ifndef QUEUEVIEW_H
#define QUEUEVIEW_H

#include "client.h"
#include <QWidget>

namespace Ui {
class QueueView;
}

class QueueView : public QWidget
{
    Q_OBJECT

public:
    explicit QueueView(Client *client,QWidget *parent = nullptr);
    ~QueueView();

private:
    Ui::QueueView *ui;
    Client *m_client;
};

#endif // QUEUEVIEW_H
