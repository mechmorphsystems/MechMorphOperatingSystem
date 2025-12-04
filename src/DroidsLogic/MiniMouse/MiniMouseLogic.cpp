#include "MiniMouseLogic.h"

void MiniMouseLogic::init()
{
    controller.init();

    esc.setup(
        MINI_MOUSE_ESC_PIN,
        MINI_MOUSE_CENTER_ESC_MICROSECONDS,
        MINI_MOUSE_MIN_ESC_MICROSECONDS,
        MINI_MOUSE_MAX_ESC_MICROSECONDS,
        MINI_MOUSE_ESC_REVERSE
    );

    esc.init();

    servo.setup(
        MINI_MOUSE_SERVO_PIN,
        MINI_MOUSE_SERVO_ZERO_ANGLE,
        MINI_MOUSE_SERVO_ANGLE_LIMIT,
        MINI_MOUSE_SERVO_REVERSE
    );

    servo.init();

    driveSystem.init(&esc, &servo);

    player.init();
    player.playFile(1);
}

void MiniMouseLogic::run()
{
    controller.update();
    player.loop();

    driveSystem.run(controller.getLeftY(), controller.getRightX());
}
