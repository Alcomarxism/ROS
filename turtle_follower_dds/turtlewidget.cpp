#include "turtlewidget.h"
#include <QPainter>
#include "PosMsg.h"
#include "TeleopMsg.h"
#include <cmath>
#include <random>

TurtleWidget::TurtleWidget(dds_entity_t ptcpnt,std::string turtleName,QWidget *parent):QWidget{parent},myName(turtleName),participant(ptcpnt),currSpeed(0),currRotateSpeed(0){
    timerSendPos=new QTimer(this);
    connect(timerSendPos, &QTimer::timeout, this, &TurtleWidget::onTimerSendPosTick);
    timerSendPos->start(SEND_POS_DELAY);

    timerReadTeleop=new QTimer(this);
    connect(timerReadTeleop, &QTimer::timeout, this, &TurtleWidget::onTimerTeleopReadTick);
    timerReadTeleop->start(READ_TELEOP_DELAY);

    timerTurtleMove=new QTimer(this);
    connect(timerTurtleMove, &QTimer::timeout, this, &TurtleWidget::onTimerTurtleMoveTick);
    timerTurtleMove->start(TURTLE_MOVE_DELAY);

    dds_qos_t *qos = dds_create_qos();
    dds_qset_reliability(qos, DDS_RELIABILITY_BEST_EFFORT, 0);
    dds_qset_history(qos, DDS_HISTORY_KEEP_LAST, 1);

    posTopic = dds_create_topic(participant, &PosMsg_desc, (myName+"_pos").c_str(), NULL, NULL);
    writerPos = dds_create_writer(participant, posTopic, qos, NULL);

    teleopTopic = dds_create_topic(participant, &TeleopMsg_desc, (myName+"_teleop").c_str(), NULL, NULL);
    readerTeleop = dds_create_reader(participant, teleopTopic, qos, NULL);
    dds_delete_qos(qos);

    std::mt19937 generator(std::random_device{}());
    std::uniform_real_distribution<double> distributionCords(0.0,1.0);
    std::uniform_real_distribution<double> distributionAng(-M_PI,M_PI);
    x = distributionCords(generator);
    y = distributionCords(generator);
    theta = distributionAng(generator);

    this->resize(TURTLE_SIZE,TURTLE_SIZE);
}


void TurtleWidget::paintEvent(QPaintEvent *event){
    QSize windowSize = window()->size();
    this->move(x*windowSize.width()-TURTLE_SIZE/2,y*(float)windowSize.height()-TURTLE_SIZE/2);
    QPainter painter(this);
    QPixmap pixmap(":/images/image.png");
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.translate(width()/2, height()/2);
    painter.rotate(theta/M_PI*180.0 + 90.0);
    painter.scale((float)TURTLE_SIZE/pixmap.width(),(float)TURTLE_SIZE/pixmap.height());
    painter.drawPixmap(-pixmap.width()/2, -pixmap.height()/2, pixmap);
}

void TurtleWidget::onTimerSendPosTick(){
    PosMsg msg;
    msg.x=x;
    msg.y=y;
    msg.theta=theta;
    dds_write(writerPos, &msg);
}

void TurtleWidget::onTimerTeleopReadTick(){
    void *samples[1];
    dds_sample_info_t infos[1];
    int ret = dds_take(readerTeleop, samples, infos, 1, 1);
    if (ret > 0 && infos[0].valid_data) {
        TeleopMsg* msg = (TeleopMsg*)samples[0];
        currSpeed=msg->speed;
        currRotateSpeed=msg->angSpeed;
        dds_return_loan(readerTeleop, samples, ret);
    }
}

void TurtleWidget::onTimerTurtleMoveTick(){
    this->x+=currSpeed*cos(theta);
    this->y+=currSpeed*sin(theta);
    this->theta+=currRotateSpeed;
    if (theta>M_PI)
        theta-=2*M_PI;
    if (theta<-M_PI)
        theta+=2*M_PI;
    update();
}

TurtleWidget::~TurtleWidget(){
    dds_delete(posTopic);
    dds_delete(writerPos);
    dds_delete(readerTeleop);
    dds_delete(teleopTopic);
}