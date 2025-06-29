// pin configuration
#define MINI_GONK_LEFT_ESC_PIN 23
#define MINI_GONK_RIGHT_ESC_PIN 22

#define MINI_GONK_LEFT_SWITCH_PIN 19
#define MINI_GONK_RIGHT_SWITCH_PIN 21

#define MINI_GONK_LED_1_PIN 12
#define MINI_GONK_LED_2_PIN 13

#define MINI_GONK_RANDOM_SEED_PIN 36


// ESC configuration
#define MINI_GONK_MIN_ESC_MICROSECONDS 1100
#define MINI_GONK_CENTER_ESC_MICROSECONDS 1500
#define MINI_GONK_MAX_ESC_MICROSECONDS 1900
#define MINI_GONK_LEFT_ESC_REVERSE false
#define MINI_GONK_RIGHT_ESC_REVERSE true

#define BIT_DEBOUNCE_COUNT 8  //number of debounce routine calls that have to be unchanged for switch state to be updated
#define BIT_DEBOUNCE_PATTERN (1 << (BIT_DEBOUNCE_COUNT + 1)) - 1  //