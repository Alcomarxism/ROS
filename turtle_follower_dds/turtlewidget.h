#ifndef TURTLEWIDGET_H
#define TURTLEWIDGET_H

#include <QWidget>
#include <string>
#include <QTimer>
#include "dds/dds.h"

#define SEND_POS_DELAY 100
#define READ_TELEOP_DELAY 100
#define TURTLE_MOVE_DELAY 100

#define TURTLE_SIZE 100

class TurtleWidget : public QWidget {
    Q_OBJECT
private:
    dds_entity_t participant;
    dds_entity_t posTopic;
    dds_entity_t writerPos;
    dds_entity_t readerTeleop;
    dds_entity_t teleopTopic;
    std::string myName;
    QTimer* timerSendPos;
    QTimer* timerReadTeleop;
    QTimer* timerTurtleMove;
    float theta;
    float x;
    float y;
    float currSpeed;
    float currRotateSpeed;
    void paintEvent(QPaintEvent *event) override;
private slots:
    void onTimerSendPosTick();
    void onTimerTeleopReadTick();
    void onTimerTurtleMoveTick();
public:
    explicit TurtleWidget(dds_entity_t ptcpnt,std::string turtleName,QWidget *parent = nullptr);
    ~TurtleWidget();
};

#endif // TURTLEWIDGET_H
