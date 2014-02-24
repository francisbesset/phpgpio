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

#define PHP_GPIO_VERSION "0.2.1-DEV"

#include "php.h"

#ifdef ZTS
#include "TSRM.h"
#endif

extern zend_module_entry gpio_module_entry;
#define phpext_gpio_ptr &gpio_module_entry

PHP_MINIT_FUNCTION(gpio);
PHP_MSHUTDOWN_FUNCTION(gpio);

PHP_FUNCTION(gpio_mode);
PHP_FUNCTION(gpio_pin_mode);
PHP_FUNCTION(gpio_read);
PHP_FUNCTION(gpio_write);

int _wp_setup_mode(void);

#endif
