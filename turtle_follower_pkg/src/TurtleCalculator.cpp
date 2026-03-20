#include "TurtleCalculator.h"
#include <random>
#include <cmath>
#include <iostream>
#define _USE_MATH_DEFINES


TurtleCalculator::TurtleCalculator(float speed,float rotateSpeed):turtleSpeed(speed),turtleRotateSpeed(rotateSpeed){
    myX=myY=myTheta=0;
    targetX=targetY=targetTheta=0;
    currSpeed=currRotateSpeed=0;
    randomizeMyCords();
}

void TurtleCalculator::randomizeMyCords(){
    std::mt19937 generator(std::random_device{}());
    std::uniform_real_distribution<double> distributionCords(MIN_CORDS,MAX_CORDS);
    std::uniform_real_distribution<double> distributionAng(-M_PI,M_PI);
    myX = distributionCords(generator);
    myY = distributionCords(generator);
    myTheta=distributionAng(generator);
}

void TurtleCalculator::calculateMove(){
    float dx = targetX-myX;
    float dy = targetY-myY; 
    float dist=sqrt(dx*dx+dy*dy);
     if(dist<DIST_EPS){
	    currRotateSpeed = 0;
        currSpeed = 0;
        return;
    }
    float rotateAng=atan2(dy,dx)-myTheta;
    if(rotateAng>M_PI)
	    rotateAng-=2*M_PI;
    if(rotateAng<-M_PI)
	    rotateAng+=2*M_PI;
    currRotateSpeed = rotateAng/M_PI*turtleRotateSpeed;
    currSpeed = fabs(rotateAng)<ANGLE_EPS ? turtleSpeed:0;
}

void TurtleCalculator::setMyPos(float x,float y,float theta){
    myX=x;
    myY=y;
    myTheta=theta;
    calculateMove();
}

void TurtleCalculator::setTargetPos(float x,float y,float theta){
    targetX=x;
    targetY=y;
    targetTheta=theta;
    calculateMove();
}

float TurtleCalculator::getCurrSpeed(){
    return currSpeed;
}
float TurtleCalculator::getCurrRotateSpeed(){
    return currRotateSpeed;
}

float TurtleCalculator::getX(){
    return myX;
}

float TurtleCalculator::getY(){
    return myY;
}

float TurtleCalculator::getTheta(){
    return myTheta;
}