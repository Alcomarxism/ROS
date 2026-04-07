#ifndef TURTLEFOLLOWERWIDGET_H
#define TURTLEFOLLOWERWIDGET_H

#include <QWidget>
#include <QTimer>
#include <string>
#include "turtlecalculator.h"
#include "dds/dds.h"

#define MOVE_CALCULATE_DELAY 100

class TurtleFollowerWidget : public QWidget, public TurtleCalculator{
    Q_OBJECT
private:
    dds_entity_t participant;
    dds_entity_t myPosTopic;
    dds_entity_t readerMyPos;
    dds_entity_t followPosTopic;
    dds_entity_t readerFollowPos;
    dds_entity_t teleopTopic;
    dds_entity_t writerTeleop;
    std::string mName;
    std::string fName;
    QTimer *timerCalculateMove;
private slots:
    void onTimerCalculateMoveTick();
public:
    explicit TurtleFollowerWidget(dds_entity_t ptcpnt,std::string myTurtleName,std::string followTurtleName,QWidget *parent = nullptr);
    ~TurtleFollowerWidget();
signals:
};

#endif // TURTLEFOLLOWERWIDGET_H
