#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([libSCE_commons], [devel], [christoffer@eliesen.no])
AC_CONFIG_AUX_DIR(config)
AM_INIT_AUTOMAKE(commons,devel)
AC_PREREQ([2.60])
AM_CONFIG_HEADER(config.h)
AC_CONFIG_SRCDIR([src/log.cpp])


# Checks for programs.
AC_PROG_MAKE_SET
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST

# Checks for library functions.

#AC_CONFIG_FILES([Makefile src/Makefile])

AC_OUTPUT(Makefile src/Makefile)
