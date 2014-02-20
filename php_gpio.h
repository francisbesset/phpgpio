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

#ifndef PHP_GPIO_H
#define PHP_GPIO_H

#define PHP_GPIO_VERSION "0.2.0-DEV"

#define PHP_GPIO_LOW  LOW
#define PHP_GPIO_HIGH HIGH

#define PHP_GPIO_INPUT  INPUT
#define PHP_GPIO_OUTPUT OUTPUT

#include "php.h"

#ifdef ZTS
#include "TSRM.h"
#endif

extern zend_module_entry gpio_module_entry;
#define phpext_gpio_ptr &gpio_module_entry

PHP_MINIT_FUNCTION(gpio);
PHP_MSHUTDOWN_FUNCTION(gpio);

PHP_FUNCTION(gpio_setup);
PHP_FUNCTION(gpio_pin_mode);
PHP_FUNCTION(gpio_read);
PHP_FUNCTION(gpio_write);

#endif
