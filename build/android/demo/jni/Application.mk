#APP_ABI := all
APP_ABI := armeabi

APP_STL := stlport_static
STLPORT_FORCE_REBUILD := true

APP_CPPFLAGS += -std=c++11 -Wall -g -DCXX_GNU -DBUILD_ANDROID -DBUILD_DEBUG
