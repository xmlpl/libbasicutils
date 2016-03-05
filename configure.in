# Disable caching
define([AC_CACHE_LOAD], )
define([AC_CACHE_SAVE], )

# Init
AC_PREREQ(2.56)
AC_INIT(libbasicutils, 0.1.11)
AC_CONFIG_SRCDIR(README)
AC_CONFIG_AUX_DIR(./config)

AM_INIT_AUTOMAKE([nostdinc])
AM_CONFIG_HEADER(config.h)


# Flags
AC_COMPILE_FLAGS

# Tools
AC_LANG_CPLUSPLUS
AC_PROG_CXX
AC_PROG_CXXCPP
AC_PROG_INSTALL
AM_PROG_LIBTOOL

# For ltdl
AC_CHECK_LIB(ltdl, lt_dlinit, ,
  [AC_MSG_ERROR([Cannot find required library libltdl])])


touch install.test
if $INSTALL -p install.test install.test2 >/dev/null 2>/dev/null; then
  INSTALL="${INSTALL} -p"
fi
rm -f install.test install.test2



# Create Makefiles
AC_OUTPUT([Makefile
	  src/Makefile
	  scripts/Makefile
	  tests/Makefile
	  tests/BasicSmartPointerTests/Makefile
	  tests/BasicDynamicClassTests/Makefile
	  tests/BasicPluginTests/Makefile
	  scripts/BasicUtils-config
	  doc/Makefile
	  doc/Doxyfile
	  ], [chmod +x scripts/BasicUtils-config]
         )

echo
echo
echo "   Everything seems to be ok."
echo "Now run 'make' and 'make install'."
echo
echo
