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

PHP_MINIT_FUNCTION(gpio)
{
  /* values */
  REGISTER_LONG_CONSTANT("GPIO_LOW", PHP_GPIO_LOW, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("GPIO_HIGH", PHP_GPIO_HIGH, CONST_CS | CONST_PERSISTENT);

  /* modes */
  REGISTER_LONG_CONSTANT("GPIO_INPUT", PHP_GPIO_INPUT, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("GPIO_OUTPUT", PHP_GPIO_OUTPUT, CONST_CS | CONST_PERSISTENT);

  return SUCCESS;
}

ZEND_BEGIN_ARG_INFO(arginfo_gpio_setup, 0)
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
  PHP_FE(gpio_setup, arginfo_gpio_setup)
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

PHP_FUNCTION(gpio_setup)
{
  if (zend_parse_parameters_none() == FAILURE) {
    return;
  }

  wiringPiSetup();

  RETURN_TRUE;
}

PHP_FUNCTION(gpio_pin_mode)
{
  long pin, mode;

  if(zend_parse_parameters(ZEND_NUM_ARGS(), "ll", &pin, &mode) == FAILURE) {
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
  }

  digitalWrite((int) pin, (int) value);

  RETURN_TRUE;
}
