#
# Makefile
#

include ../../Config.mk

CIRCLEHOME = ../../libs/circle
NEWLIBDIR = ../../install/$(NEWLIB_ARCH)

OBJS	= main.o kernel.o

include $(CIRCLEHOME)/Rules.mk

CFLAGS += -I "$(NEWLIBDIR)/include" -I $(STDDEF_INCPATH) -I ../../include -I "/home/tait/Documents/flite/include"
LIBS := "$(NEWLIBDIR)/lib/libm.a" "$(NEWLIBDIR)/lib/libc.a" "$(NEWLIBDIR)/lib/libcirclenewlib.a" \
 	$(CIRCLEHOME)/addon/SDCard/libsdcard.a \
  	$(CIRCLEHOME)/lib/usb/libusb.a \
  	$(CIRCLEHOME)/lib/sound/libsound.a \
 	$(CIRCLEHOME)/lib/input/libinput.a \
 	$(CIRCLEHOME)/addon/fatfs/libfatfs.a \
 	$(CIRCLEHOME)/lib/fs/libfs.a \
  	$(CIRCLEHOME)/lib/net/libnet.a \
  	$(CIRCLEHOME)/lib/sched/libsched.a \
  	$(CIRCLEHOME)/lib/libcircle.a \
  	/home/tait/Documents/flite/build/aarch64-elf/lib/libflite_cmu_us_slt.a \
  	/home/tait/Documents/flite/build/aarch64-elf/lib/libflite_usenglish.a \
  	/home/tait/Documents/flite/build/aarch64-elf/lib/libflite_cmulex.a \
  	/home/tait/Documents/flite/build/aarch64-elf/lib/libflite.a 

sound.h: sound.h.gz
	@echo "  UNZIP $@"
	@gunzip -c sound.h.gz > sound.h

deploy: kernel.o main.o
	sudo mount /dev/sdb1 /mnt
	sudo cp kernel8-rpi4.img /mnt
	sudo umount /mnt

-include $(DEPS)
