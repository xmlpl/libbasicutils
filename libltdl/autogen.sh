libtoolize --force --copy --automake &&\
aclocal &&\
autoheader &&\
autoconf &&\
automake --copy -a\
