#include "MiniGonkLogic.h"

void MiniGonkLogic::init()
{
    controller.init();

    leftEsc.setup(
        MINI_GONK_LEFT_ESC_PIN,
        MINI_GONK_CENTER_ESC_MICROSECONDS,
        MINI_GONK_MIN_ESC_MICROSECONDS,
        MINI_GONK_MAX_ESC_MICROSECONDS,
        MINI_GONK_LEFT_ESC_REVERSE
    );

    rightEsc.setup(
        MINI_GONK_RIGHT_ESC_PIN,
        MINI_GONK_CENTER_ESC_MICROSECONDS,
        MINI_GONK_MIN_ESC_MICROSECONDS,
        MINI_GONK_MAX_ESC_MICROSECONDS,
        MINI_GONK_RIGHT_ESC_REVERSE
    );

    leftEsc.init();
    rightEsc.init();

    // player.init();
    // player.playFile(1);

    pinMode(MINI_GONK_LEFT_SWITCH_PIN, INPUT_PULLUP);
    pinMode(MINI_GONK_RIGHT_SWITCH_PIN, INPUT_PULLUP);
}

void MiniGonkLogic::run()
{
    while (millis() - timer < 2000) {
        return;
    }

    initMotion();

    while (true)
    {
        controller.update();
        // player.loop();

        motion();
    }
}


void MiniGonkLogic::initMotion()
{
    for (int i = 0; i < 15; i++) { //get the switch states
        debounce();
    }
    //  Serial.println("Initialize*******************");
    //get the cams into a known position/////////////////////////////////////////////////////////////////////
    leftEsc.run(-512);
    do {
        debounce();
    } while (leftDebounced == false);
    do {
        debounce();
    } while (leftDebounced == true);
    motorsOff();
    // Serial.println( "H-L" );

    rightEsc.run(-512);
    do {
        debounce();
    } while (rightDebounced == false); //true
    do {
        debounce();
    } while (rightDebounced == true); //false
    motorsOff();
    //Serial.println( "L-H" );

    //Serial.println( "outside motorsOff" );
    //  Serial.println("Initialize done*******************");
    
    prevRightSwitch = rightDebounced;
    prevLeftSwitch = leftDebounced;
    stateChange = true;

    currentState = STOP;
    nextState = STOP;
}

void MiniGonkLogic::motion()
{
    handeButtons();
    runMotors();

    if (currentState != STOP) {
      debounce();
      Serial.print( ".");

      if ((leftDebounced != prevLeftSwitch) && (rightDebounced != prevRightSwitch)) { //both inputs changed at same time so the motors are in sync
        // Serial.println( "");
        // Serial.println( "   in sync");
        stateChange = true;
      }
      else {
        if ((leftDebounced != prevLeftSwitch) || (rightDebounced != prevRightSwitch)) {
          //Serial.println( "");
          //Serial.println( "   || unequal");
          if (leftDebounced != prevLeftSwitch) {
            //stop the side that just changed and wait for other side to sync
            leftEsc.run(0);
            //Serial.println( "   left stop");

            do {
              debounce();
              //Serial.print("R");
            } while (rightDebounced == prevRightSwitch);
            //Serial.println("");

            if ((currentState == FORWARD) | (currentState == RIGHT)) {
              leftEsc.run(512);
              //Serial.println( "   left for");
            }
            else {
              leftEsc.run(-512);
              //Serial.println( "   left rev");
            }
            stateChange = true;
            //Serial.println( "   left forward");
          }

          else if (rightDebounced != prevRightSwitch) {
            //stop the side that just changed and wait for other side to sync
            rightEsc.run(0);
            //Serial.println( "   right stop");
            do {
              debounce();
              //Serial.print("L");
            } while (leftDebounced == prevLeftSwitch);
            //Serial.println("");
            if ((currentState == FORWARD) | (currentState == LEFT)) {
              rightEsc.run(512);
              //Serial.println("   right for");
            }
            else {
              rightEsc.run(+512);
              //Serial.println("   right rev");
            }
            stateChange = true;
            //Serial.println( "   stateChange= TRUE");
          }
        }

      }


    }

    if ((currentState == STOP) && (currentState != nextState)) { // motors aren't running so can't look for switch changes
      //Serial.println("motors not running (currentState = nextState;) ");
      currentState = nextState;
    }

    if (stateChange == true) {
      prevLeftSwitch = ! prevLeftSwitch;
      prevRightSwitch = ! prevRightSwitch;
      stateChange = !stateChange;
      if (currentState != nextState) {
        currentState = nextState;
        //motorsOff();
      }
      if (currentState == STOP) {
        motorsOff();
      }
    }
}

void MiniGonkLogic::debounce()
{
    if (digitalRead(MINI_GONK_LEFT_SWITCH_PIN)) { //shift in a one
        leftBitTrain <<= 1;
        leftBitTrain |= 1;
    } else {                       //shift in a zero
        leftBitTrain <<= 1;
    }
    if (digitalRead(MINI_GONK_RIGHT_SWITCH_PIN)) { //shift in a one
        rightBitTrain <<= 1;
        rightBitTrain |= 1;
    } else {                       //shift in a zero
        rightBitTrain <<= 1;
    }


    if ((leftBitTrain & BIT_DEBOUNCE_PATTERN) == BIT_DEBOUNCE_PATTERN) {
        leftDebounced = true;
    } else if ((leftBitTrain & BIT_DEBOUNCE_PATTERN) == 0) {
        leftDebounced = false;
    }
    if ((rightBitTrain & BIT_DEBOUNCE_PATTERN) == BIT_DEBOUNCE_PATTERN) {
        rightDebounced = true;
    } else if ((rightBitTrain & BIT_DEBOUNCE_PATTERN) == 0) {
        rightDebounced = false;
    }
}

void MiniGonkLogic::motorsOff()
{
    leftEsc.run(0);
    rightEsc.run(0);
}

void MiniGonkLogic::handeButtons()
{
    if (controller.dPadUpClick()) {
        nextState = FORWARD;
    }

    if (controller.dPadDownClick()) {
        nextState = BACKWARD;
    }

    if (controller.dPadLeftClick()) {
        nextState = LEFT;
    }

    if (controller.dPadRightClick()) {
        nextState = RIGHT;
    }

    if (controller.dPadDownClick()) {
        nextState = RIGHT;
    }

    if (controller.croossButtonClick()) {
        nextState = STOP;
    }
}

void MiniGonkLogic::runMotors()
{
    switch (currentState) {
        case FORWARD:
            leftEsc.run(512);
            rightEsc.run(512);
            break;

        case BACKWARD:
            leftEsc.run(-512);
            rightEsc.run(-512);
            break;

        case LEFT: // right
            leftEsc.run(-512);
            rightEsc.run(512);
            break;

        case RIGHT:
            leftEsc.run(512);
            rightEsc.run(-512);
            break;
        default:
            motorsOff();
            break;
    }
}