
BUILD_LINUX64=1
# BUILD_ARM_RTS=1

FEATURE_RTMP=1

ifdef FEATURE_RTMP
CXXFLAGS += -D FEATURE_RTMP
endif
