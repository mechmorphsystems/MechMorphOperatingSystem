#line 1 "/home/vasya/arduino/MechMorphOperatingSystem/src/Controllers/GamepadController.cpp"
#include "GamepadController.h"

ControllerPtr myControllers[BP32_MAX_GAMEPADS];

void onConnectedController(ControllerPtr ctl) {
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == nullptr) {
            ControllerProperties properties = ctl->getProperties();
            myControllers[i] = ctl;
        }
    }
}

void onDisconnectedController(ControllerPtr ctl) {
    bool foundController = false;

    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == ctl) {
            Serial.printf("CALLBACK: Controller disconnected from index=%d\n", i);
            myControllers[i] = nullptr;
            foundController = true;
            break;
        }
    }

    if (!foundController) {
        Serial.println("CALLBACK: Controller disconnected, but not found in myControllers");
    }
}

void GamepadController::init()
{
    BP32.setup(&onConnectedController, &onDisconnectedController);
    BP32.enableVirtualDevice(false);
}

void GamepadController::update()
{
    bool dataUpdated = BP32.update();
    if (dataUpdated) {
        controllerPtr = myControllers[0];
    }

    if (controllerPtr && controllerPtr->isConnected() && controllerPtr->hasData()) {
        tick(D_PAD);
        tick(BUTTONS);
        // changeColorLedIfAnyButtonHold();
        setBlueColorLed();
    }
}

bool GamepadController::dPadUpClick()
{
    if (buttonClics[D_PAD][D_PAD_UP]) {
        buttonClics[D_PAD][D_PAD_UP] = false;

        return true;
    }
    
    return false;
}

bool GamepadController::dPadDownClick()
{
    if (buttonClics[D_PAD][D_PAD_DOWN]) {
        buttonClics[D_PAD][D_PAD_DOWN] = false;

        return true;
    }
    
    return false;
}

bool GamepadController::dPadLeftClick()
{
    if (buttonClics[D_PAD][D_PAD_LEFT]) {
        buttonClics[D_PAD][D_PAD_LEFT] = false;

        return true;
    }
    
    return false;
}

bool GamepadController::dPadRightClick()
{
    if (buttonClics[D_PAD][D_PAD_RIGHT]) {
        buttonClics[D_PAD][D_PAD_RIGHT] = false;

        return true;
    }
    
    return false;
}

bool GamepadController::croossButtonClick()
{
    if (buttonClics[BUTTONS][CROSS]) {
        buttonClics[BUTTONS][CROSS] = false;

        return true;
    }
    
    return false;
}

bool GamepadController::squareButtonClick()
{
    if (buttonClics[BUTTONS][SQUARE]) {
        buttonClics[BUTTONS][SQUARE] = false;

        return true;
    }
    
    return false;
}

bool GamepadController::triangleButtonClick()
{
    if (buttonClics[BUTTONS][TRIANGLE]) {
        buttonClics[BUTTONS][TRIANGLE] = false;

        return true;
    }
    
    return false;
}

bool GamepadController::circleButtonClick()
{
    if (buttonClics[BUTTONS][CIRCLE]) {
        buttonClics[BUTTONS][CIRCLE] = false;

        return true;
    }
    
    return false;
}

bool GamepadController::l1ButtonClick()
{
    if (buttonClics[BUTTONS][L1]) {
        buttonClics[BUTTONS][L1] = false;

        return true;
    }
    
    return false;
}

bool GamepadController::l3ButtonClick()
{
    if (buttonClics[BUTTONS][L3]) {
        buttonClics[BUTTONS][L3] = false;

        return true;
    }
    
    return false;
}

bool GamepadController::r1ButtonClick()
{
    if (buttonClics[BUTTONS][R1]) {
        buttonClics[BUTTONS][R1] = false;

        return true;
    }
    
    return false;
}

bool GamepadController::r3ButtonClick()
{
    if (buttonClics[BUTTONS][R3]) {
        buttonClics[BUTTONS][R3] = false;

        return true;
    }
    
    return false;
}

bool GamepadController::dPadUpHold()
{
    return buttonHolds[D_PAD][D_PAD_UP];
}

bool GamepadController::dPadDownHold()
{
    return buttonHolds[D_PAD][D_PAD_DOWN];
}

bool GamepadController::dPadLeftHold()
{
    return buttonHolds[D_PAD][D_PAD_LEFT];
}

bool GamepadController::dPadRightHold()
{
    return buttonHolds[D_PAD][D_PAD_RIGHT];
}

bool GamepadController::croossButtonHold()
{
    return buttonHolds[BUTTONS][CROSS];
}

bool GamepadController::squareButtonHold()
{
    return buttonHolds[BUTTONS][SQUARE];
}

bool GamepadController::triangleButtonHold()
{
    return buttonHolds[BUTTONS][TRIANGLE];
}

bool GamepadController::circleButtonHold()
{
    return buttonHolds[BUTTONS][CIRCLE];
}

bool GamepadController::l1ButtonHold()
{
    return buttonHolds[BUTTONS][L1];
}

bool GamepadController::l3ButtonHold()
{
    return buttonHolds[BUTTONS][L3];
}

bool GamepadController::r1ButtonHold()
{
    return buttonHolds[BUTTONS][R1];
}

bool GamepadController::r3ButtonHold()
{
    return buttonHolds[BUTTONS][R3];
}

int32_t GamepadController::getLeftX()
{
    if (controllerPtr && controllerPtr->isConnected())
    {
        return controllerPtr->axisX();
    }
    
    return 0;
}

int32_t GamepadController::getLeftY()
{
    if (controllerPtr && controllerPtr->isConnected())
    {
        return controllerPtr->axisY();
    }
    
    return 0;
}

int32_t GamepadController::getRightX()
{
    if (controllerPtr && controllerPtr->isConnected())
    {
        return controllerPtr->axisRX();
    }
    
    return 0;
}

int32_t GamepadController::getRightY()
{
    if (controllerPtr && controllerPtr->isConnected())
    {
        return controllerPtr->axisRY();
    }
    
    return 0;
}

int32_t GamepadController::getBrake()
{
    if (controllerPtr && controllerPtr->isConnected())
    {
        return controllerPtr->brake();
    }
    
    return 0;
}


int32_t GamepadController::getThrottle()
{
    if (controllerPtr && controllerPtr->isConnected())
    {
        return controllerPtr->throttle();
    }
    
    return 0;
}

int32_t GamepadController::getBrakeThrottleMixed()
{
    if (controllerPtr && controllerPtr->isConnected())
    {
        if (controllerPtr->brake() < STICK_DEADZONE && controllerPtr->throttle() < STICK_DEADZONE) {
            return 0;
        }

        if (controllerPtr->brake() > STICK_DEADZONE && controllerPtr->throttle() > STICK_DEADZONE) {
            return 0;
        }

        if (controllerPtr->brake() > STICK_DEADZONE) {
            return -constrain(map(controllerPtr->brake(), 0, 1024, 0, 512), 0, 512);
        }

        if (controllerPtr->throttle() > STICK_DEADZONE) {
            return constrain(map(controllerPtr->throttle(), 0, 1024, 0, 512), 0, 512);
        }

    }
    
    return 0;
}

void GamepadController::blinkGreen()
{}

void  GamepadController::tick(uint8_t buttonType)
{
    uint16_t receivedValue = buttonType == D_PAD ? controllerPtr->dpad() : controllerPtr->buttons();
    uint8_t buttonsCount = buttonType == D_PAD ? D_PAD_COUNT : BUTTONS_COUNT;
    
    for (uint8_t i = 0; i < buttonsCount; i++) {
        // click
        if (receivedValue == buttonCodes[buttonType][i] && !buttonFlags[buttonType][i]) {
            buttonsHoldTimeout[buttonType][i] = millis();
            
            buttonFlags[buttonType][i] = true;
            buttonClics[buttonType][i] = true;
        }

        // release
        if (receivedValue != buttonCodes[buttonType][i] && buttonFlags[buttonType][i]) {
            buttonFlags[buttonType][i] = false;
            buttonClics[buttonType][i] = false;
            buttonHoldFlags[buttonType][i] = false;
            buttonHolds[buttonType][i] = false;
        }

        //hold
        if (receivedValue == buttonCodes[buttonType][i] && !buttonHoldFlags[buttonType][i] && (millis() - buttonsHoldTimeout[buttonType][i] >= 500)) {
            buttonsHoldTimeout[buttonType][i] = millis();

            buttonHoldFlags[buttonType][i] = true;
            buttonHolds[buttonType][i] = true;
        }
    }
}

void GamepadController::setRedColorLed()
{
    if (RED != colorState) {
        colorState = RED;
        controllerPtr->setColorLED(255, 0, 0);
    }
}

void GamepadController::setGreenColorLed()
{
    if (GREEN != colorState) {
        colorState = GREEN;
        controllerPtr->setColorLED(0, 255, 0);
    }
}

void GamepadController::setBlueColorLed()
{
    if (BLUE != colorState) {
        colorState = BLUE;
        controllerPtr->setColorLED(0, 0, 255);
    }
}

void GamepadController::changeColorLedIfAnyButtonHold()
{
    for (uint8_t i = 0; i < (sizeof(buttonHolds) / sizeof(buttonHolds[0])); i++) {
        uint8_t buttonsCount = i == D_PAD ? D_PAD_COUNT : BUTTONS_COUNT;

        for (uint8_t j = 0; j < buttonsCount; j++) {
            if (buttonHolds[i][j])
            {
                // Serial.print(i); Serial.print(" "); Serial.print(j); Serial.print(" "); Serial.println(buttonHoldFlags[i][j]);
                setGreenColorLed();
                return;
            }
            
        }
    }

    setBlueColorLed();
}