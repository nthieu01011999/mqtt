



ifdef BUILD_ARM_RTS
-include sources/libraries/arm_rts/Makefile.mk
-include sources/libraries/librealtex/Makefile.mk
endif

ifdef BUILD_LINUX64
-include sources/libraries/linux64/Makefile.mk
-include sources/libraries/librealtex/Makefile.mk
endif