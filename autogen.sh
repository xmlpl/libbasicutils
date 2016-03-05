libtoolize --force --copy --automake &&\
aclocal -I config/m4 &&\
autoheader &&\
autoconf &&\
automake --copy -a 
