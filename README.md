# PhpGpio

The phpgpio extension provides an API to control your GPIO's (with the [Wiring Pi](http://wiringpi.com) library).
This code has been developed and maintained by [Francis Besset](http://francis-besset.com).

You can send comments, patches, questions [on GitHub](https://github.com/FrancisBesset/phpgpio/issues).

# Table of contents

1. [Installing/Configuring](#installingconfiguring)
    * [Installation](#installation)
2. [Usage](#usage)
    * [Predefined constants](#predefinedconstants)
    * [Functions](#functions)
        * [gpio_mode](#gpio_modeint-mode)
        * [gpio_pin_mode](#gpio_pin_modeint-pin-int-mode)
        * [gpio_read](#gpio_readint-pin)
        * [gpio_write](#gpio_writeint-pin-int-value)

## Installing/Configuring

### Installation

```sh
phpize
./configure [--with-wiringpi=path to wiring pi library]
make && make install
```

`make install` copies `gpio.so` to an appropriate location, but you still need to enable the module in the PHP config file. To do so, either edit your php.ini or add a gpio.ini file in `/etc/php5/conf.d` with the following contents: `extension=gpio.so`.

## Usage

### Predefined constants

```
GPIO_MODE_PINS - Mode PINS (needs root user)
GPIO_MODE_GPIO - Mode GPIO (needs root user)
GPIO_MODE_GPIO_SYS - Mode GPIO Systems (slightly slower, but always usable as a non-root user)

GPIO_LOW - Value low
GPIO_HIGH - Value high

GPIO_INPUT - Mode input
GPIO_OUTPUT - Mode output
GPIO_PWM - Mode PWM
```

### Functions

#### gpio_mode([int $mode])

Return the current mode if `$mode` is not specified.
Return the old mode if `$mode` is specified.

The default mode is `GPIO_MODE_PINS`.

```php
$oldMode = gpio_mode(GPIO_MODE_GPIO); // set GPIO_MODE_GPIO mode
$currentMode = gpio_mode(); // $currentMode === GPIO_MODE_GPIO

gpio_pin_mode(18, GPIO_OUPUT);
gpio_write(18, GPIO_HIGH);
```

The function return `GPIO_MODE_PINS`, `GPIO_MODE_GPIO` or `GPIO_MODE_GPIO_SYS`.

#### gpio_pin_mode(int $pin, int $mode)

Set the mode for a pin.

```php
gpio_mode(GPIO_MODE_PINS);

gpio_pin_mode(1, GPIO_OUTPUT); // set the pin #1 to output mode
```

The function return `true`.

#### gpio_pwm(int $pin, int $value)

Set the PWM value for a pin.

```
gpio_mode(GPIO_MODE_PINS);

gpio_pin_mode(1, GPIO_PWM); // set the pin #1 to PWM mode
gpio_pwm(1, 50); // set the pin #1 to 50% high value
gpio_pwm(1, 75); // set the pin #1 to 75% high value
```

The function return `true`.

#### gpio_read(int $pin)

Get the value for a pin.

```php
gpio_mode(GPIO_MODE_PINS);

gpio_pin_mode(1, GPIO_INPUT);

if (GPIO_HIGH === gpio_read(1)) {
    echo "The pin #1 is HIGH\n";
} else {
    echo "The pin #1 is LOW\n";
}
```

The function return `GPIO_HIGH` or `GPIO_LOW` constant value.

#### gpio_write(int $pin, int $value)

Set the value for a pin.

```php
gpio_mode(GPIO_MODE_PINS);

gpio_pin_mode(1, GPIO_OUTPUT); // set the pin #1 to output mode
gpio_write(1, GPIO_HIGH); // set the pin #1 to high value
```

The function return `true`.
