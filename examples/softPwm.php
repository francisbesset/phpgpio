<?php

define('RANGE', 100);
define('NUM_LEDS', 8);

gpio_mode(GPIO_MODE_PINS);

$leds = array(0, 1, 2, 3, 4, 5, 6, 7);
$values = array(0, 25, 50, 75, 100, 75, 50, 25);

foreach ($leds as $i => $led) {
    gpio_pin_mode($led, GPIO_PWM);
    printf("%3d, %3d, %3d\n", $i, $led, $values[$i]);
}

fgets(STDIN);

// Bring all up one by one:
foreach ($leds as $i => $led) {
    for ($j = 0; $j <= RANGE; ++$j) {
        gpio_pwm($led, $j);
        usleep(10000);
    }
}

fgets(STDIN);

// All Down
for ($i = 100; $i > 0; --$i) {
    foreach ($leds as $led) {
        gpio_pwm($led, $i);
    }

    usleep(10000);
}

fgets(STDIN);

while (true) {
    foreach ($leds as $i => $led) {
        gpio_pwm($led, $values[$i]);
    }

    usleep(50000);

    $i = $values[0];
    for ($j = 0; $j < NUM_LEDS - 1; ++$j) {
        $values[$j] = $values[$j + 1];
    }

    $values[NUM_LEDS - 1] = $i;
}
