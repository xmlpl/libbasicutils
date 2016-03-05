# $1 - Name
# $2 - Minimum Version
# $3 - Commands if mininum version matched.
# $4 - Commands if not

AC_DEFUN([AC_CHECK_CONFIG],[

AC_PATH_PROG($1_CONFIG, $1-config, no)

if test "$$1_CONFIG" = "no"; then
  echo "*** The $1-config script installed by $1 could not be found"
  echo "*** If $1 was installed in PREFIX, make sure PREFIX/bin is in"
  echo "*** your path, or set the $1_CONFIG environment variable to the"
  echo "*** full path to $NAME-config."
  ifelse([$4], , :, [$4])

else

  AC_MSG_CHECKING(for $1 version >= $2)

  $1_CFLAGS=`$$1_CONFIG --cflags`
  $1_LIBS=`$$1_CONFIG --libs`
  $1_PREFIX=`$$1_CONFIG --prefix`
  $1_EXEC_PREFIX=`$$1_CONFIG --exec-prefix`

  major=`$$1_CONFIG --version | \
    sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
  minor=`$$1_CONFIG --version | \
    sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
  micro=`$$1_CONFIG --version | \
    sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`

  min_major=`echo "$2" | \
    sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
  min_minor=`echo "$2" | \
    sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
  min_micro=`echo "$2" | \
    sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`

  version_ok="false"
  if test "$major" -gt "$min_major"; then
    version_ok="true"

  elif test "$major" -eq "$min_major"; then
    if test "$minor" -gt "$min_minor"; then
      version_ok="true"

    elif test "$minor" -eq "$min_minor"; then
      if test "$micro" -ge "$min_micro"; then
        version_ok="true"
      fi
    fi
  fi

  $1_VERSION="$major.$minor.$micro"

  if test "$version_ok" = "true"; then
    AC_MSG_RESULT([yes version = $major.$minor.$micro])
    AC_SUBST($1_CFLAGS)
    AC_SUBST($1_LIBS)
    AC_SUBST($1_CONFIG)
    AC_SUBST($1_VERSION)
    AC_SUBST($1_PREFIX)
    AC_SUBST($1_EXEC_PREFIX)
    ifelse([$3], , :, [$3])

  else
    AC_MSG_RESULT(no)
    echo "*** '$1-config --version' returned $major.$minor.$micro, but the minimum version"
    echo "*** of $1 required is $min_major.$min_minor.$min_micro. If $1-config is correct, then it is"
    echo "*** best to upgrade to the required version."
    echo "*** If $1-config was wrong, set the environment variable $1_CONFIG"
    echo "*** to point to the correct copy of $1-config, and remove the file"
    echo "*** config.cache if it exists, before re-running configure."
    ifelse([$4], , :, [$4])
  fi
fi

])
