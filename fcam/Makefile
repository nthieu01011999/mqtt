###############################################################################
# author: ThanNT
# date: 6/1/2017
###############################################################################

-include config.mk

RPI_SYS_DIR	=
TOOLS_DIR	=

ifdef BUILD_LINUX64
CROSS_COMPILE=
OBJ_DIR		= _build
NAME_MODULE	= fcam-rts-linux64
endif
ifdef BUILD_ARM_RTS
OBJ_DIR		= _build_rts
CROSS_COMPILE= /home/it/Desktop/Camera/cam/rts39xx_sdk_v5.0.1/toolchain/tool/bin/arm-linux-uclibcgnueabi-
NAME_MODULE	= fcam-rts
endif


CXX	  =$(CROSS_COMPILE)g++
CC	  =$(CROSS_COMPILE)gcc
AR	  =$(CROSS_COMPILE)ar
STRIP =$(CROSS_COMPILE)strip


OPTIMIZE_OPTION	=	-g -s -O3
WARNNING_OPTION	+=	#-Werror -W -Wno-missing-field-initializers

CXXFLAGS += $(HAVE_FLAGS)

-include sources/ak/Makefile.mk
-include sources/sys/Makefile.mk
-include sources/app/Makefile.mk
-include sources/common/Makefile.mk
-include sources/driver/Makefile.mk
-include sources/libraries/Makefile.mk

ifdef BUILD_LINUX64
GENERAL_FLAGS +=\
	-DBUILD_LINUX64
else
GENERAL_FLAGS +=\
	-DBUILD_ARM_RTS
endif

# CXX compiler option
CXXFLAGS	+=\
		$(OPTIMIZE_OPTION)	\
		$(WARNNING_OPTION)	\
		-Wall				\
		-pipe				\
		-ggdb				\
		$(GENERAL_FLAGS)

# Library paths
LDFLAGS	+= -Wl,-Map=$(OBJ_DIR)/$(NAME_MODULE).map


ifdef BUILD_LINUX64
DEPENDENCIES=sources/libraries/linux64
endif
ifdef BUILD_ARM_RTS
DEPENDENCIES=sources/libraries/arm_rts
LDLIBS +=  $(DEPENDENCIES)/lib/libfreetype.a
endif

ifdef BUILD_LINUX64
LDLIBS +=  $(DEPENDENCIES)/lib/libdatachannel.a
LDLIBS +=  $(DEPENDENCIES)/lib/libjuice.a
LDLIBS +=  $(DEPENDENCIES)/lib/libsrtp2.a
LDLIBS +=  $(DEPENDENCIES)/lib/libusrsctp.a

LDLIBS	+=\
		-lpthread			\
		-lrt				\
		-lm					\
		-lcurl				\
		-lcrypto			\
		-lssl				\
		-lmosquittopp				\
		-lmosquitto				
endif

ifdef BUILD_ARM_RTS
LDLIBS +=  $(DEPENDENCIES)/lib/libmosquittopp.a
LDLIBS +=  $(DEPENDENCIES)/lib/libmosquitto.a

# lib webrtc
LDLIBS +=  $(DEPENDENCIES)/libdatachannel/lib/libdatachannel.a
LDLIBS +=  $(DEPENDENCIES)/libdatachannel/lib/libjuice.a
LDLIBS +=  $(DEPENDENCIES)/libdatachannel/lib/libsrtp2.a
LDLIBS +=  $(DEPENDENCIES)/libdatachannel/lib/libusrsctp.a
LDLIBS += sources/libraries/librealtex/lib/librtsio.a

ifdef FEATURE_RTMP
LDLIBS +=  $(DEPENDENCIES)/lib/libRTMP.a
LDLIBS +=  $(DEPENDENCIES)/lib/librtmp.a
LDLIBS +=  $(DEPENDENCIES)/lib/libFPTHmac.a
endif

LDLIBS += -L$(DEPENDENCIES)/lib
LDLIBS	+=\
		-lpthread			\
		-lrt				\
		-lm					\
		-lcurl				\
		-lcrypto			\
		-lssl				\
	
# lib SDK
LDLIBS	+=\
		-lasound			\
		-lrtsaudio			\
		-lrtsvideo			\
		-lrtstream			\
		-lsoxr				\

endif
		
all: create $(OBJ_DIR)/$(NAME_MODULE) #scp

create:
	@echo mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)

	@echo "DEPENDENCIES" $(DEPENDENCIES)

$(OBJ_DIR)/%.o: %.cpp
	@echo CXX $<
	@$(CXX) -c -o $@ $< $(CXXFLAGS) -std=c++17 $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c
	@echo CC $<
	@$(CC) -c -o $@ $< $(CXXFLAGS) $(LDFLAGS)

$(OBJ_DIR)/$(NAME_MODULE): $(OBJ)
	@echo ---------- START LINK PROJECT ----------
	@echo $(CXX) -o $@ $^ $(CXXFLAGS)
	@echo "\n\n"
	@echo LIB $(LDLIBS) "\n\n"audio_stream
	@$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

.PHONY: cp
copy: $(OBJ_DIR)/$(NAME_MODULE)
	sudo cp $(OBJ_DIR)/$(NAME_MODULE) /mnt/nfs_share/

#.PHONY: scp
#scp:
#	# scp $(OBJ_DIR)/$(NAME_MODULE) root@192.168.1.112:/tmp/
#	scp $(OBJ_DIR)/$(NAME_MODULE) huynt@192.168.1.141:/home/huynt/Workspace/FPT/Github/Camera/demo_nfs

.PHONY: flash
flash:
	@sudo LD_LIBRARY_PATH=/usr/local/lib/ $(OBJ_DIR)/$(NAME_MODULE)

.PHONY: debug
debug:
	sudo gdb $(OBJ_DIR)/$(NAME_MODULE)

.PHONY: install
install:
	cp $(OBJ_DIR)/$(NAME_MODULE) /usr/local/bin

.PHONY: clean
clean:
	@echo rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR)

.PHONY: strip
strip:
	$(STRIP) $(OBJ_DIR)/$(NAME_MODULE)
