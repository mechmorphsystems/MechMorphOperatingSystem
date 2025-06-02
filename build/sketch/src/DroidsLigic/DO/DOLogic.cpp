#line 1 "/home/vasya/arduino/MechMorphOperatingSystem/src/DroidsLigic/DO/DOLogic.cpp"
#include "DOLogic.h"

void DOLogic::init()
{
    controller.init();
    player.init();
    doBodyMovement.init(&controller);
    doHeadMovement.init(&controller);

}

void DOLogic::run()
{
    controller.update();

    doBodyMovement.run();
    doHeadMovement.run();

    if (controller.croossButtonClick())
    {
        player.playFile(4);
    }

    if (controller.circleButtonClick())
    {
        player.playFile(6);
    }
    
}