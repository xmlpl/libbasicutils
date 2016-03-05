EXTRA_DIST = data

AM_CXXFLAGS = $(shell BasicUtils-config --cflags)
AM_LDFLAGS = $(shell BasicUtils-config --libs) -module -export-dynamic

noinst_PROGRAMS =\
	SimplePluginTest\
	PluginLoadTest\
	PluginInstantiateTest\
	PluginDependencyTest\
	DepCycleTest

PLUGINS =\
	libPluginA.la\
	libPluginB.la\
	libPluginC.la\
	libPluginD.la\
	libPluginE.la\
	libPluginF.la

SimplePluginTest_SOURCES = SimplePluginTest.cpp
PluginLoadTest_SOURCES = PluginLoadTest.cpp
PluginLoadTest_DEPENDENCIES = libPluginA.la libPluginB.la
PluginInstantiateTest_SOURCES = PluginInstantiateTest.cpp
PluginInstantiateTest_DEPENDENCIES = libPluginA.la libPluginB.la
PluginDependencyTest_SOURCES = PluginDependencyTest.cpp
PluginDependencyTest_DEPENDENCIES = libPluginA.la libPluginB.la libPluginC.la
DepCycleTest_SOURCES = DepCycleTest.cpp
DepCycleTest_DEPENDENCIES = libPluginD.la libPluginE.la libPluginF.la


lib_LTLIBRARIES = $(PLUGINS)

libPluginA_la_SOURCES = PluginA.cpp Plugin.h
libPluginB_la_SOURCES = PluginB.cpp Plugin.h
libPluginC_la_SOURCES = PluginC.cpp Plugin.h
libPluginD_la_SOURCES = PluginD.cpp Plugin.h
libPluginE_la_SOURCES = PluginE.cpp Plugin.h
libPluginF_la_SOURCES = PluginF.cpp Plugin.h
