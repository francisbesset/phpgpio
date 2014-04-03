dnl config.m4 for extension GPIO

PHP_ARG_WITH(wiringpi, for WiringPi support,
[  --with-wiringpi=DIR     Path to WiringPi library])

if test "$PHP_WIRINGPI" != "no"; then
  if test -r $PHP_WIRINGPI/include/wiringPi.h; then
    WIRINGPI_DIR=$PHP_WIRINGPI
  else
    AC_MSG_CHECKING(for WiringPi in default path)
    for i in /usr/local /usr; do
      if test -r $i/include/wiringPi.h; then
        WIRINGPI_DIR=$i
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

  PHP_ADD_INCLUDE($WIRINGPI_DIR/include)

  LIBNAME=wiringPi
  LIBSYMBOL=digitalRead

  PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  [
    PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $WIRINGPI_DIR/lib, GPIO_SHARED_LIBADD)
  ],[
    AC_MSG_ERROR([wrong WiringPi lib version or lib not found])
  ],[
    -L$WIRINGPI_DIR/lib -lm
  ])
  PHP_SUBST(GPIO_SHARED_LIBADD)

  PHP_NEW_EXTENSION(gpio, gpio.c, $ext_shared)
fi
