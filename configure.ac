#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(libdelimText, 20160623)
AC_CONFIG_SRCDIR([src/delimTextFile.h])
AM_INIT_AUTOMAKE
AC_PROG_RANLIB

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AX_BOOST_BASE([1.48],, [AC_MSG_ERROR([This program needs Boost, but it was not found in your system])])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
