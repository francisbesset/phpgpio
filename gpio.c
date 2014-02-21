/*
   +----------------------------------------------------------------------+
   | GPIO Extension                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2014 Francis Besset                                    |
   +----------------------------------------------------------------------+
   | Redistribution and use in source and binary forms, with or without   |
   | modification, are permitted provided that the conditions mentioned   |
   | in the accompanying LICENSE file are met (BSD-3-Clause).             |
   +----------------------------------------------------------------------+
   | Author: Francis Besset <francis.besset@gmail.com>                    |
   +----------------------------------------------------------------------+
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_gpio.h"
#include "wiringPi.h"

#ifdef COMPILE_DL_GPIO
ZEND_GET_MODULE(gpio)
#endif

#ifndef TRUE
#define TRUE  (1==1)
#define FALSE (1==2)
#endif

static int isInitialized = FALSE;
static int wpMode = WPI_MODE_PINS;

PHP_MINIT_FUNCTION(gpio)
{
  /* wp modes */
  REGISTER_LONG_CONSTANT("GPIO_MODE_PINS", WPI_MODE_PINS, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("GPIO_MODE_GPIO", WPI_MODE_GPIO, CONST_CS | CONST_PERSISTENT);

  /* values */
  REGISTER_LONG_CONSTANT("GPIO_LOW", LOW, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("GPIO_HIGH", HIGH, CONST_CS | CONST_PERSISTENT);

  /* pin modes */
  REGISTER_LONG_CONSTANT("GPIO_INPUT", INPUT, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("GPIO_OUTPUT", OUTPUT, CONST_CS | CONST_PERSISTENT);

  return SUCCESS;
}

ZEND_BEGIN_ARG_INFO(arginfo_gpio_mode, 0)
  ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_gpio_pin_mode, 0)
  ZEND_ARG_INFO(0, pin)
  ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_gpio_read, 0)
  ZEND_ARG_INFO(0, pin)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_gpio_write, 0)
  ZEND_ARG_INFO(0, pin)
  ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

zend_function_entry gpio_functions[] = {
  PHP_FE(gpio_mode, arginfo_gpio_mode)
  PHP_FE(gpio_pin_mode, arginfo_gpio_pin_mode)
  PHP_FE(gpio_read, arginfo_gpio_read)
  PHP_FE(gpio_write, arginfo_gpio_write)
  {NULL, NULL, NULL}
};

zend_module_entry gpio_module_entry = {
  STANDARD_MODULE_HEADER,
  "gpio",
  gpio_functions,
  PHP_MINIT(gpio),
  NULL,
  NULL,
  NULL,
  NULL,
  PHP_GPIO_VERSION,
  STANDARD_MODULE_PROPERTIES
};

PHP_FUNCTION(gpio_mode)
{
  // return the current mode
  ZVAL_LONG(return_value,wpMode);

  // call function without args (read current mode)
  if (ZEND_NUM_ARGS() == 0) {
    return;
  }

  long newMode;

  // call function with 1 arg (set new mode)
  if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &newMode) == FAILURE) {
    return;
  }

  if (newMode == wpMode) {
    return; // do nothing
  }

  switch (newMode) {
    case WPI_MODE_GPIO:
      wpMode = WPI_MODE_GPIO;
      break;

    case WPI_MODE_PINS:
      wpMode = WPI_MODE_PINS;
      break;

    default:
      php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid GPIO mode");
      return;
  }

  isInitialized = FALSE;
}

PHP_FUNCTION(gpio_pin_mode)
{
  long pin, mode;

  if(zend_parse_parameters(ZEND_NUM_ARGS(), "ll", &pin, &mode) == FAILURE) {
    return;
  } else if (!_wp_setup_mode()) {
    return;
  }

  pinMode((int) pin, (int) mode);

  RETURN_TRUE;
}

PHP_FUNCTION(gpio_read)
{
  long pin, result;

  if(zend_parse_parameters(ZEND_NUM_ARGS(), "l", &pin) == FAILURE) {
    return;
  } else if (!_wp_setup_mode()) {
    return;
  }

  result = (long) digitalRead((int) pin);
  {
    ZVAL_LONG(return_value,result);
  }

  return;
}

PHP_FUNCTION(gpio_write)
{
  long pin, value;

  if(zend_parse_parameters(ZEND_NUM_ARGS(), "ll", &pin, &value) == FAILURE) {
    return;
  } else if (!_wp_setup_mode()) {
    return;
  }

  digitalWrite((int) pin, (int) value);

  RETURN_TRUE;
}

int _wp_setup_mode(void)
{
  if (isInitialized) {
    return 1;
  } else if (geteuid() != 0) {
    php_error_docref(NULL TSRMLS_CC, E_WARNING, "You must be root to use the current mode. (Did you forget sudo?)");

    return 0;
  }

  if (wpMode == WPI_MODE_GPIO) {
    wiringPiSetupGpio();
  } else {
    wiringPiSetup();
  }

  isInitialized = TRUE;

  return 1;
}
