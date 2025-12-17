#include "MiniR2D2LightLogic.h"

void MiniR2D2LightLogic::init(Adafruit_NeoPixel* neoPixelLed, Adafruit_PWMServoDriver* servoDriver)
{
    MiniR2D2LightLogic::neoPixelLed = neoPixelLed;
    MiniR2D2LightLogic::servoDriver = servoDriver;
}

void MiniR2D2LightLogic::runNeopixelLedLight()
{
    for (uint8_t i = 0; i < 10; i++) {
        if (millis() - ledTimers[i] >= ledIntervals[i]) {
            ledTimers[i] = millis();
            randomSeed(analogRead(MINI_R2D2_RANDOM_SEED_PIN));
            ledIntervals[i] = random(1000);

            ledStates[i] = !ledStates[i];
            
            if (ledStates[i]) {
                if (3 == i || 4 == i || 6 == i) {
                    uint8_t lightLevel = random(0, 255);
                    neoPixelLed->setPixelColor(i, neoPixelLed->Color(lightLevel, lightLevel, lightLevel));
                } else {
                    neoPixelLed->setPixelColor(i, neoPixelLed->Color(neoPixelLedHighLight[i][0], neoPixelLedHighLight[i][1], neoPixelLedHighLight[i][2]));
                }
            } else {
                neoPixelLed->setPixelColor(i, neoPixelLed->Color(neoPixelLedLowLight[i][0], neoPixelLedLowLight[i][1], neoPixelLedLowLight[i][2]));
            }
        }
    }

    neoPixelLed->show();
}

void MiniR2D2LightLogic::runRegularLedLight()
{
    for (uint8_t i = 0; i < 10; i++) {
        if (millis() - ledTimers[i] >= ledIntervals[i]) {
            ledTimers[i] = millis();
            randomSeed(analogRead(MINI_R2D2_RANDOM_SEED_PIN));
            ledIntervals[i] = random(1000);

            ledStates[i] = !ledStates[i];
            
            if (ledStates[i]) {
                servoDriver->setPWM(i + 5, 4096, 0); // high
            } else {
                servoDriver->setPWM(i + 5, 0, 4096); // low
            }
        }
    }
}