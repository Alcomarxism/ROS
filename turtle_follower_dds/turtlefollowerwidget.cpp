#include "turtlefollowerwidget.h"
#include "PosMsg.h"
#include "TeleopMsg.h"

TurtleFollowerWidget::TurtleFollowerWidget(dds_entity_t ptcpnt, std::string myTurtleName, std::string followTurtleName, QWidget *parent)
    : QWidget{parent},mName(myTurtleName),fName(followTurtleName),participant(ptcpnt)
{
    timerCalculateMove=new QTimer(this);
    connect(timerCalculateMove, &QTimer::timeout, this, &TurtleFollowerWidget::onTimerCalculateMoveTick);
    timerCalculateMove->start(MOVE_CALCULATE_DELAY);

    dds_qos_t *qos = dds_create_qos();
    dds_qset_reliability(qos, DDS_RELIABILITY_BEST_EFFORT, 0);
    dds_qset_history(qos, DDS_HISTORY_KEEP_LAST, 1);

    myPosTopic = dds_create_topic(participant, &PosMsg_desc, (mName+"_pos").c_str(), NULL, NULL);
    readerMyPos = dds_create_reader(participant, myPosTopic, qos, NULL);

    followPosTopic = dds_create_topic(participant, &PosMsg_desc, (fName+"_pos").c_str(), NULL, NULL);
    readerFollowPos = dds_create_reader(participant, followPosTopic, qos, NULL);

    teleopTopic = dds_create_topic(participant, &TeleopMsg_desc, (mName+"_teleop").c_str(), NULL, NULL);
    writerTeleop = dds_create_writer(participant, teleopTopic, qos, NULL);
    dds_delete_qos(qos);

    setTurtleSpeed(0.01);
    setRotateSpeed(1);
}

void TurtleFollowerWidget::onTimerCalculateMoveTick(){
    void *samplesMy[1]= {nullptr};
    dds_sample_info_t infosMy[1];
    int ret = dds_take(readerMyPos, samplesMy, infosMy, 1, 1);
    if (ret > 0) {
        if (infosMy[0].valid_data && samplesMy[0] != nullptr) {
            PosMsg* msg = (PosMsg*)samplesMy[0];
            setMyPos(msg->x, msg->y, msg->theta);
        }
        dds_return_loan(readerMyPos, samplesMy, ret);
    }

    void *samplesFollow[1]= {nullptr};
    dds_sample_info_t infosFollow[1];
    ret = dds_take(readerFollowPos, samplesFollow, infosFollow, 1, 1);
    if (ret > 0) {
        if (infosFollow[0].valid_data && samplesFollow[0] != nullptr) {
            PosMsg* msg = (PosMsg*)samplesFollow[0];
            setTargetPos(msg->x, msg->y, msg->theta);
        }
        dds_return_loan(readerFollowPos, samplesFollow, ret);
    }
    TeleopMsg msg;
    msg.speed=getCurrSpeed();
    msg.angSpeed=getCurrRotateSpeed();
    dds_write(writerTeleop, &msg);
}

TurtleFollowerWidget::~TurtleFollowerWidget()
{
    dds_delete(myPosTopic);
    dds_delete(readerMyPos);
    dds_delete(followPosTopic);
    dds_delete(readerFollowPos);
    dds_delete(teleopTopic);
    dds_delete(writerTeleop);
}
