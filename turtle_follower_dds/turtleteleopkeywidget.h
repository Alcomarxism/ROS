#ifndef TURTLETELEOPKEYWIDGET_H
#define TURTLETELEOPKEYWIDGET_H

#include <QWidget>
#include "dds/dds.h"

#define TURTLE_SPEED 0.01
#define TURTLE_ROTATE_SPEED 0.1

class TurtleTeleopKeyWidget : public QWidget{
    Q_OBJECT
private:
    dds_entity_t participant;
    dds_entity_t topic;
    dds_entity_t writer;
    void keyPressEvent(QKeyEvent *event) override;
public:
    explicit TurtleTeleopKeyWidget(dds_entity_t ptcpnt,QWidget *parent = nullptr);
    ~TurtleTeleopKeyWidget();
};

#endif // TURTLETELEOPKEYWIDGET_H
