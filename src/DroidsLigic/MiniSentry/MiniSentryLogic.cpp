#include "MiniSentryLogic.h"

void MiniSentryLogic::init()
{
    controller.init();

    esc1.setup(
        MINI_SENTRY_ESC_1_PIN,
        MINI_SENTRY_CENTER_ESC_MICROSECONDS,
        MINI_SENTRY_MIN_ESC_MICROSECONDS,
        MINI_SENTRY_MAX_ESC_MICROSECONDS,
        MINI_SENTRY_ESC_1_REVERSE
    );

    esc2.setup(
        MINI_SENTRY_ESC_2_PIN,
        MINI_SENTRY_CENTER_ESC_MICROSECONDS,
        MINI_SENTRY_MIN_ESC_MICROSECONDS,
        MINI_SENTRY_MAX_ESC_MICROSECONDS,
        MINI_SENTRY_ESC_2_REVERSE
    );

    esc3.setup(
        MINI_SENTRY_ESC_3_PIN,
        MINI_SENTRY_CENTER_ESC_MICROSECONDS,
        MINI_SENTRY_MIN_ESC_MICROSECONDS,
        MINI_SENTRY_MAX_ESC_MICROSECONDS,
        MINI_SENTRY_ESC_3_REVERSE
    );

    esc1.init();
    esc2.init();
    esc3.init();


    leftDoorServo.setup(
        MINI_SENTRY_LEFT_DOOR_SERVO_PIN
    );

    rightDoorServo.setup(
        MINI_SENTRY_RIGHT_DOOR_SERVO_PIN
    );

    leftDoorServo.init();
    rightDoorServo.init();
    leftDoorServo.writeAngle(MINI_SENTRY_LEFT_DOOR_ZERO_ANGLE);
    rightDoorServo.writeAngle(MINI_SENTRY_RIGHT_DOOR_ZERO_ANGLE);

    animationRunnrer.setup(&leftDoorServo, &rightDoorServo);
    
    for (uint8_t i = 0; i < 7; i++) {
        pinMode(leds[i], OUTPUT);
    }

    pinMode(MINI_SENTRY_RANDOM_SEED_PIN, INPUT);
}

void MiniSentryLogic::run()
{
    controller.update();
    movement();
    ledBlink();

    if (controller.triangleButtonClick() || animationRunnrer.isRunnung(0)) {
        animationRunnrer.run(0);
    }

    if (controller.croossButtonClick()) {
        animationRunnrer.stop();
    }

    
}

void MiniSentryLogic::movement()
{
    yValue  = controller.getLeftY();
    xValue  = controller.getRightX();
    rotation  = controller.getBrakeThrottleMixed();

    // Convert the input values to direction vectors///////////////////////////
    theta = atan2(yValue, xValue);
    magnitude = sqrt((yValue * yValue) + (xValue * xValue));

    if (magnitude > 75.0f || rotation > STICK_DEADZONE || rotation < -STICK_DEADZONE) { // the f is a float number to check against i.e. 1/3 = 0.33333
        float vx = magnitude * cos(theta);
        float vy = magnitude * sin(theta);
        const float sqrt3o2 = 1.0 * sqrt(3) / 2;

        //Find wheel vecotrs and do math stuff/////////////////////////////////////////////////////////
        esc1Speed = -vx;                     // v dot [-1, 0] / 25mm               // the 25mm represents the radius of the omniwheel to calculate the angular velocity
        esc2Speed = 0.5 * vx - sqrt3o2 * vy; // v dot [1/2, -sqrt(3)/2] / 25mm
        esc3Speed = 0.5 * vx + sqrt3o2 * vy; // v dot [1/2, +sqrt(3)/2] / 25mm

        esc1Speed = constrain(esc1Speed + rotation, -512, 512);
        esc2Speed = constrain(esc2Speed + rotation, -512, 512);
        esc3Speed = constrain(esc3Speed + rotation, -512, 512);
    }
    else {
        esc1Speed = esc2Speed = esc3Speed = 0;
    }

    esc1.run(esc1Speed);
    esc2.run(esc2Speed);
    esc3.run(esc3Speed);
}

void MiniSentryLogic::ledBlink()
{
    for (uint8_t i = 0; i < 5; i++) {
        if (millis() - ledTimers[i] >= ledIntervals[i]) {
            ledTimers[i] = millis();
            randomSeed(analogRead(MINI_SENTRY_RANDOM_SEED_PIN));
            ledIntervals[i] = random(1000);

            ledStates[i] = !ledStates[i];
            digitalWrite(leds[i], ledStates[i]);
        }
    }
}