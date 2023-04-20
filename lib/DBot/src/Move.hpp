#include <Servo.h>

class Move
{
private:
    Servo frontRightLeg1;
    Servo frontRightLeg2;
    Servo frontLeftLeg1;
    Servo frontLeftLeg2;
    Servo backRightLeg1;
    Servo backRightLeg2;
    Servo backLeftLeg1;
    Servo backLeftLeg2;

public:
    Move(
        int frontRightLeg1,
        int frontRightLeg2,
        int frontLeftLeg1,
        int frontLeftLeg2,
        int backRightLeg1,
        int backRightLeg2,
        int backLeftLeg1,
        int backLeftLeg2);
    ~Move();
    void advance();
};


Move::Move(
    int frontRightLeg1,
    int frontRightLeg2,
    int frontLeftLeg1,
    int frontLeftLeg2,
    int backRightLeg1,
    int backRightLeg2,
    int backLeftLeg1,
    int backLeftLeg2)
{

    this->frontRightLeg1.attach(frontRightLeg1);
    this->frontRightLeg2.attach(frontRightLeg2);
    this->frontLeftLeg1.attach(frontLeftLeg1);
    this->frontLeftLeg2.attach(frontLeftLeg2);
    this->backRightLeg1.attach(backRightLeg1);
    this->backRightLeg2.attach(backRightLeg2);
    this->backLeftLeg1.attach(backLeftLeg1);
    this->backLeftLeg2.attach(backLeftLeg2);
}

void Move::advance(){

}