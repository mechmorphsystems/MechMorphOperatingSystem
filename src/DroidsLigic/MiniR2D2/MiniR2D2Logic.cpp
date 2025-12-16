#include "MiniR2D2Logic.h"

void MiniR2D2Logic::init()
{
    controller.init();
    player.init();
    pinMode(MINI_R2D2_RANDOM_SEED_PIN, INPUT);

    esc2.setup(
        MINI_R2D2_ESC_1_PIN,
        MINI_R2D2_CENTER_ESC_MICROSECONDS,
        MINI_R2D2_MIN_ESC_MICROSECONDS,
        MINI_R2D2_MAX_ESC_MICROSECONDS,
        MINI_R2D2_ESC_1_REVERSE
    );
    esc1.setup(
        MINI_R2D2_ESC_2_PIN,
        MINI_R2D2_CENTER_ESC_MICROSECONDS,
        MINI_R2D2_MIN_ESC_MICROSECONDS,
        MINI_R2D2_MAX_ESC_MICROSECONDS,
        MINI_R2D2_ESC_2_REVERSE
    );

    esc2.init();
    esc1.init();

    headServo.setup(
        MINI_R2D2_HEAD_SERVO_PIN
    );

    leftArmServo.setup(
        MINI_R2D2_LEFT_ARM_SERVO_PIN,
        MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE,
        MINI_R2D2_LEFT_ARM_SERVO_ANGLE_LIMIT
    );

    rightArmServo.setup(
        MINI_R2D2_RIGHT_ARM_SERVO_PIN,
        MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE,
        MINI_R2D2_RIGHT_ARM_SERVO_ANGLE_LIMIT
    );

    shoulderServo.setup(
        MINI_R2D2_SHOULDER_SERVO_PIN,
        MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE
    );

    centerLiftServo.setup(
        MINI_R2D2_CENTER_LIFT_SERVO_PIN,
        MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE
    );

    headServo.init();
    leftArmServo.init();
    rightArmServo.init();
    shoulderServo.init();
    centerLiftServo.init();

    animationRunnrer.setup(&leftArmServo, &rightArmServo, &shoulderServo, &centerLiftServo);

    pixel.begin();
    pixel.show();
    pixel.setBrightness(128);

    servoDriver.begin();
    servoDriver.setPWMFreq(50);
}

void MiniR2D2Logic::run()
{
    controller.update();

    runMotor();


    //  if (controller.squareButtonClick() || animationRunnrer.isRunnung(0))
    // if (controller.squareButtonClick())
    // {
    //     if (state) {
    //         servoDriver.setPWM(3, 0, 600);
    //     } else {
    //         servoDriver.setPWM(3, 0, 200);
    //     }

    //     state = !state;
        
    // }

    if (controller.triangleButtonClick() || animationRunnrer.isRunnung(0))
    {
        animationRunnrer.run(0);
    }

    if (controller.croossButtonClick() || animationRunnrer.isRunnung(1))
    {
        animationRunnrer.run(1);
    }

    if (controller.circleButtonClick() || animationRunnrer.isRunnung(2))
    {
        animationRunnrer.run(2);
    }

    if (controller.r1ButtonClick())
    {
        animationRunnrer.stop();
    }

    if (controller.dPadUpClick()) {
        player.playFile(55);
    }

    if (controller.dPadDownClick()) {
        player.playFile(56);
    }

    if (controller.l1ButtonClick()) {
        randomSeed(analogRead(MINI_R2D2_RANDOM_SEED_PIN));
        player.playFile(random(1, 54));
    }

    headServo.run(controller.getBrakeThrottleMixed());

    FrontLogicDisplayLight();
    RearLogicDisplayLight();
    PsiLight();
    HoloprojectorLight();

    pixel.show();

    moveHoloprojector();
}

void MiniR2D2Logic::runMotor()
{
    yValue = controller.getLeftY();
    xValue = controller.getRightX();

    rawLeft = xValue + yValue;
    rawRight = xValue - yValue;

    diff = abs(abs(xValue) - abs(yValue));
    rawLeft = rawLeft < 0 ? rawLeft - diff : rawLeft + diff;
    rawRight = rawRight < 0 ? rawRight - diff : rawRight + diff;

    rawLeft = constrain(rawLeft, -512, 512);
    rawRight = constrain(rawRight, -512, 512);
    esc2.run(rawLeft);
    esc1.run(rawRight);
}

void MiniR2D2Logic::FrontLogicDisplayLight()
{
    for (uint8_t i = 0; i < 2; i++) {
        if (millis() - ledTimers[i] >= ledIntervals[i]) {
            ledTimers[i] = millis();
            randomSeed(analogRead(MINI_R2D2_RANDOM_SEED_PIN));
            ledIntervals[i] = random(1000);

            ledStates[i] = !ledStates[i];
            
            if (ledStates[i]) {
                pixel.setPixelColor(i, pixel.Color(255, 255, 255));
            } else {
                pixel.setPixelColor(i, pixel.Color(0, 0, 255));
            }
        }
    }
}

void MiniR2D2Logic::RearLogicDisplayLight()
{
    for (uint8_t i = 7; i < 10; i++) {
        if (millis() - ledTimers[i] >= ledIntervals[i]) {
            ledTimers[i] = millis();
            randomSeed(analogRead(MINI_R2D2_RANDOM_SEED_PIN));
            ledIntervals[i] = random(1000);

            ledStates[i] = !ledStates[i];
            
            if (ledStates[i]) {
                pixel.setPixelColor(i, pixel.Color(255, 0, 0));
            } else {
                pixel.setPixelColor(i, pixel.Color(0, 255, 0));
            }
        }
    }
}


void MiniR2D2Logic::PsiLight()
{
    for (uint8_t i = 2; i < 4; i++) {
        if (3 == i) {
            i = 5;
        }
        
        if (millis() - ledTimers[i] >= ledIntervals[i]) {
            ledTimers[i] = millis();
            randomSeed(analogRead(MINI_R2D2_RANDOM_SEED_PIN));
            ledIntervals[i] = random(1000);

            ledStates[i] = !ledStates[i];
            
            if (2 == i) {
                if (ledStates[i]) {
                    pixel.setPixelColor(i, pixel.Color(0, 255, 0));
                } else {
                    pixel.setPixelColor(i, pixel.Color(0, 0, 255));
                }
            } else {
                if (ledStates[i]) {
                    pixel.setPixelColor(i, pixel.Color(255, 0, 0));
                } else {
                    pixel.setPixelColor(i, pixel.Color(255, 255, 0));
                }
            }
        }
    }
}


void MiniR2D2Logic::HoloprojectorLight()
{
    for (uint8_t i = 3; i < 6; i++) {
        if (5 == i) {
            i = 6;
        }
        

        if (millis() - ledTimers[i] >= ledIntervals[i]) {
            ledTimers[i] = millis();
            randomSeed(analogRead(MINI_R2D2_RANDOM_SEED_PIN));
            ledIntervals[i] = random(1000);

            ledStates[i] = !ledStates[i];
            
            if (ledStates[i]) {
                pixel.setPixelColor(i, pixel.Color(255, 255, 255));
            } else {
                pixel.setPixelColor(i, pixel.Color(125, 125, 125));
            }
        }
    }
}

void MiniR2D2Logic::moveHoloprojector()
{
    for (uint8_t i = 0; i < 3; i++) {
        if (millis() - holoprojectorTimers[i] >= holoprojectorIntervals[i]) {
            holoprojectorTimers[i] = millis();
            randomSeed(analogRead(MINI_R2D2_RANDOM_SEED_PIN));
            

            holoprojectorStates[i] = !holoprojectorStates[i];
            
            if (holoprojectorStates[i]) {
                servoDriver.setPWM(i, 0, random(150, 600));
                holoprojectorIntervals[i] = random(1000);
            } else {
                servoDriver.setPWM(i, 0, 360);
                holoprojectorIntervals[i] = random(10000, 15000);
            }
        }
    }
}