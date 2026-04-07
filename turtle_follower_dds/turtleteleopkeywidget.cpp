#include "turtleteleopkeywidget.h"
#include "TeleopMsg.h"
#include <QKeyEvent>

TurtleTeleopKeyWidget::TurtleTeleopKeyWidget(dds_entity_t ptcpnt,QWidget *parent): QWidget{parent},participant(ptcpnt){
    dds_qos_t *qos = dds_create_qos();
    dds_qset_reliability(qos, DDS_RELIABILITY_BEST_EFFORT, 0);
    dds_qset_history(qos, DDS_HISTORY_KEEP_LAST, 1);
    topic = dds_create_topic(participant, &TeleopMsg_desc, "turtle1_teleop", NULL, NULL);
    writer = dds_create_writer(participant, topic, qos, NULL);
    dds_delete_qos(qos);
}

void TurtleTeleopKeyWidget::keyPressEvent(QKeyEvent *event){
    TeleopMsg msg;
    switch (event->key()) {
    case Qt::Key_Left:
        msg.angSpeed =-TURTLE_ROTATE_SPEED;
        break;
    case Qt::Key_Right:
        msg.angSpeed =TURTLE_ROTATE_SPEED;
        break;
    case Qt::Key_Up:
        msg.speed=TURTLE_SPEED;
        break;
    case Qt::Key_Down:
        msg.speed=-TURTLE_SPEED;
        break;
    default:
        QWidget::keyPressEvent(event);
        return;
    }
    dds_write(writer, &msg);
    update();
}


TurtleTeleopKeyWidget::~TurtleTeleopKeyWidget()
{
    dds_delete(topic);
    dds_delete(writer);
}
