#Generated by VisualGDB (http://visualgdb.com)
#DO NOT EDIT THIS FILE MANUALLY UNLESS YOU ABSOLUTELY NEED TO
#USE VISUALGDB PROJECT PROPERTIES DIALOG INSTEAD

BINARYDIR := Release

#Toolchain
CC := gcc
CXX := g++
LD := $(CXX)
AR := ar
OBJCOPY := objcopy

#Additional flags
PREPROCESSOR_MACROS := NDEBUG RELEASE
INCLUDE_DIRS := /home/tester/myprojects/common/ycommonserver/include /usr/local/include/boost/boost /usr/local/include/boost
LIBRARY_DIRS := /home/tester/myprojects/common/ycommonserver/lib /usr/local/lib
LIBRARY_NAMES := ycommonserverlib ssl crypto boost_system boost_log boost_log_setup boost_chrono boost_thread boost_filesystem boost_locale PocoUtil PocoJSON PocoXML PocoFoundation pthread dl
ADDITIONAL_LINKER_INPUTS := 
MACOS_FRAMEWORKS := 
LINUX_PACKAGES := 

CFLAGS := -ggdb -ffunction-sections -O3
CXXFLAGS := -ggdb -ffunction-sections -O3 -std=c++11 -fpermissive
ASFLAGS := 
LDFLAGS := -Wl,-gc-sections   -static-libstdc++ -static
COMMONFLAGS := 

START_GROUP := -Wl,--start-group
END_GROUP := -Wl,--end-group

#Additional options detected from testing the toolchain
IS_LINUX_PROJECT := 1
