#define DIST_EPS 0.05
#define ANGLE_EPS 0.1

class TurtleCalculator{
private:
    float turtleSpeed;
    float turtleRotateSpeed;
    float myX,myY,myTheta;
    float targetX,targetY,targetTheta;
    float currSpeed,currRotateSpeed;
    void calculateMove();
public:
    TurtleCalculator();
    void setMyPos(float x,float y,float theta);
    void setTargetPos(float x,float y,float theta);
    float getCurrSpeed();
    float getCurrRotateSpeed();
    float getX();
    float getY();
    float getTheta();
    void setTurtleSpeed(float speed);
    void setRotateSpeed(float rotateSpeed);
};