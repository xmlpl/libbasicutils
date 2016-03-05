AC_DEFUN([AC_COMPILE_FLAGS],[

  efence=false

  if test -f .notdist ; then
    werror=true
    debug=true
    optimize=false
  else
    werror=false
    debug=false
    optimize=true
  fi


  AC_ARG_ENABLE(debug-mode,
                [  --enable-debug-mode       Build in debug mode],
                [debug=true],[])

  AC_ARG_ENABLE(optimize,
                [  --enable-optimize         Build with optimizations],
                [optimize=true],[])

  AC_ARG_ENABLE(efence,
                [  --enable-efence           Build with efence mode],
                [debug=true
                 efence=true],[])

  CFLAGS="$CFLAGS -Wall"

  if test ${werror}x = truex; then
    CFLAGS="$CFLAGS -Werror"
  fi

  if test ${debug}x = truex; then
    CFLAGS="$CFLAGS -g"
    CPPFLAGS="$CPPFLAGS -D__DEBUG__"
  fi

  if test ${optimize}x = truex; then
    CFLAGS="$CFLAGS -O2"

    if test ${debug}x = falsex; then
	LDFLAGS="$LDFLAGS -s"
    fi
  fi

  if test ${efence}x = truex; then
    LIBS="$LIBS -lefence"
  fi

  CXXFLAGS="$CXXFLAGS $CFLAGS"

  AC_SUBST(CPPFLAGS)
  AC_SUBST(CFLAGS)
  AC_SUBST(CXXFLAGS)
  AC_SUBST(LIBS)
  AC_SUBST(LDFLAGS)
])
