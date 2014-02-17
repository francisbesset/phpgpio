dnl config.m4 for extension GPIO

PHP_ARG_WITH(wiringpi, for WiringPi support,
[  --with-wiringpi=DIR     Path to Wiring Pi library])

if test "$PHP_WIRINGPI" != "no"; then
  if test -r $PHP_WIRINGPI/include/wiringPi.h; then
    WIRINGPI_DIR=$PHP_WIRINGPI/include
  elif test -r $PHP_WIRINGPI/wiringPi.h; then
    WIRINGPI_DIR=$PHP_WIRINGPI
  else
    AC_MSG_CHECKING(for WiringPi in default path)
    for i in /usr/local /usr; do
      if test -r $i/include/wiringPi.h; then
        WIRINGPI_DIR=$i/include
        AC_MSG_RESULT(found in $i)
        break
      fi
    done
  fi

  if test -z "$WIRINGPI_DIR"; then
    AC_MSG_RESULT(not found)
    AC_MSG_ERROR(Please reinstall the WiringPi distribution -
    wiringPi.h should be in <wiringpi-dir>/include/)
  fi

  PHP_ADD_INCLUDE($WIRINGPI_DIR)
  PHP_NEW_EXTENSION(gpio, gpio.c $WIRINGPI_DIR/wiringPi.c $WIRINGPI_DIR/piHiPri.c, $ext_shared)
fi
