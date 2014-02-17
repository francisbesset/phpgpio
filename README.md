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
GPIO_LOW - Value low
GPIO_HIGH - Value high

GPIO_INPUT - Mode input
GPIO_OUTPUT - Mode output
```

### Functions

#### gpio_setup()

This function must be called in first without arguments.

```php
gpio_setup();
```

The function return `true`.

#### gpio_pin_mode(int $pin, int $mode)

Set the mode for a pin.

```php
gpio_setup();
gpio_pin_mode(1, GPIO_OUTPUT); // set the pin #1 to output mode
```

The function return `true`.

#### gpio_read(int $pin)

Get the value for a pin.

```php
gpio_setup();
gpio_pin_mode(1, GPIO_INPUT);

if ($pin1Value === gpio_read(1)) {
    echo "The pin #1 is HIGH\n";
} else {
    echo "The pin #1 is LOW\n";
}
```

The function return `GPIO_HIGH` or `GPIO_LOW` constant value.

#### gpio_write(int $pin, int $value)

Set the value for a pin.

```php
gpio_setup();
gpio_pin_mode(1, GPIO_OUTPUT); // set the pin #1 to output mode
gpio_write(1, GPIO_HIGH); // set the pin #1 to high value
```

The function return `true`.
