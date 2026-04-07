#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) , ui(new Ui::MainWindow){
    ui->setupUi(this);
    participant = dds_create_participant(DDS_DOMAIN_DEFAULT, NULL, NULL);
    teleopWidget=new TurtleTeleopKeyWidget(participant,this);
    teleopWidget->setFocus();
    for(int i=1;i<=NUM_TURTLES;i++)
        turtles.push_back(new TurtleWidget(participant,"turtle"+std::to_string(i),this));
    for(int i=2;i<=NUM_TURTLES;i++)
        turtlesFollowers.push_back(new TurtleFollowerWidget(participant,"turtle"+std::to_string(i),"turtle"+std::to_string(i-1),this));
}

MainWindow::~MainWindow(){
    delete ui;
    dds_delete(participant);
}
