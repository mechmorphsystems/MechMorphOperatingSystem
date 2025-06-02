#line 1 "/home/vasya/arduino/MechMorphOperatingSystem/src/DroidsLigic/DO/DOBodyMovement.cpp"
#include "DOBodyMovement.h"

// volatile bool IMUdataReady = false;
// void IRAM_ATTR dmpDataReady() {
//     IMUdataReady = true;
// }


void DOBodyMovement::init(GamepadController* controller)
{
    DOBodyMovement::controller = controller;
    // // DOBodyMovement::headMovement = headMovement;
    // Wire.begin();
    // mpu.initialize();
    // mpu.initialize();
    // devStatus = mpu.dmpInitialize();
    // mpu.setXAccelOffset(DO_MPU_6050_ACCEL_X_OFFSET);
    // mpu.setYAccelOffset(DO_MPU_6050_ACCEL_Y_OFFSET);
    // mpu.setZAccelOffset(DO_MPU_6050_ACCEL_Z_OFFSET);
    // mpu.setXGyroOffset(DO_MPU_6050_GYRO_X_OFFSET);
    // mpu.setYGyroOffset(DO_MPU_6050_GYRO_Y_OFFSET);
    // mpu.setZGyroOffset(DO_MPU_6050_GYRO_Z_OFFSET);
    // mpu.setDMPEnabled(true);

    // if (devStatus == 0) {
    //     // turn on the DMP, now that it's ready
    //     mpu.setDMPEnabled(true);
    //     attachInterrupt(digitalPinToInterrupt(DO_MPU_6050_INT_PIN), dmpDataReady, RISING);
    //     mpuIntStatus = mpu.getIntStatus();
    //     // get expected DMP packet size for later comparison
    //     packetSize = mpu.dmpGetFIFOPacketSize();
    // }

    // stabilityPid.SetMode(AUTOMATIC);
    // stabilityPid.SetOutputLimits(0, 150);
    // stabilityPid.SetSampleTime(10);

    throttleEsc.setup(
        DO_ESC_2_PIN,
        DO_CENTER_ESC_MICROSECONDS,
        DO_MIN_ESC_MICROSECONDS,
        DO_MAX_ESC_MICROSECONDS
    );
    steeringEsc.setup(
        DO_ESC_1_PIN,
        DO_CENTER_ESC_MICROSECONDS,
        DO_MIN_ESC_MICROSECONDS,
        DO_MAX_ESC_MICROSECONDS
    );

    throttleEsc.init();
    steeringEsc.init();

    // mainBarServo.setup(
    //     DO_MAIN_BAR_SERVO,
    //     DO_MAIN_BAR_SERVO_CENTRE_ANGLE,
    //     DO_MAIN_BAR_SERVO_ANGLE_LIMIT
    // );

    // mainBarServo.init();
}

void DOBodyMovement::run()
{
    throttle = controller->getRightY();
    steering = controller->getRightX();

    // if (IMUdataReady) {
    //     readAngles();
    // }

    if (DO_THROTTLE_ESC_REVERSE) {
        throttle = -throttle;
    }

    if (DO_STEERING_ESC_REVERSE) {
        steering = -steering;
    }

    // pitch = (ypr[2] * 180/M_PI); // adjust to degrees

    // if (throttle > 0)
    // {
    //     mainBarServo.run(constrain(map(pitch, -90, 90,-512, 512), -512, 512));
    // } else {
    //     // PID vars
    //     setpoint = throttle; 
    //     input = pitch;

    //     stabilityPid.Compute();
    //     throttle = throttle - (pitch < -5 || pitch > 5 ? output : 0);

    //     mainBarServo.run(controller->getLeftY());
    // }

        // move motors
    throttleEsc.run(throttle);
    steeringEsc.run(steering);
}

// void DOBodyMovement::readAngles()
// {
//     mpuIntStatus = mpu.getIntStatus();
//     fifoCount = mpu.getFIFOCount();
    
//     if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
//         // reset so we can continue cleanly
//         mpu.resetFIFO();
//      } 
     
//      else if (mpuIntStatus & 0x02) {
//         // wait for correct available data length, should be a VERY short wait
//         while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

//         // read a packet from FIFO
//         mpu.getFIFOBytes(fifoBuffer, packetSize);
        
//         // track FIFO count here in case there is > 1 packet available
//         // (this lets us immediately read more without waiting for an interrupt)
//         fifoCount -= packetSize;

//         mpu.dmpGetQuaternion(&q, fifoBuffer);
//         mpu.dmpGetGravity(&gravity, &q);
//         mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

//         IMUdataReady = false;
//         //count = count + 1;
//     }
// }