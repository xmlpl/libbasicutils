EXTRA_DIST = data

AM_CXXFLAGS = $(shell BasicUtils-config --cflags)
AM_LDFLAGS = $(shell BasicUtils-config --libs)

noinst_PROGRAMS =\
	DeallocationTest\
	MultipleRefTest\
	DerefTest\
	RefCountTest\
	NullAssignTest

DeallocationTest_SOURCES = DeallocationTest.cpp
MultipleRefTest_SOURCES = MultipleRefTest.cpp
DerefTest_SOURCES = DerefTest.cpp
RefCountTest_SOURCES = RefCountTest.cpp
NullAssignTest_SOURCES = NullAssignTest.cpp
