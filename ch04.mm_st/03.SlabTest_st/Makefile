obj-m	:= slabTest.o

KDIR	:= /lib/modules/$(shell uname -r)/build
KBUILD_CFLAGS += -DHOST
#KDIR	:= /work_kernel/linux
#CC = /opt/gnueabi/opt/ext-toolchain/bin/arm-linux-gnueabihf-gcc

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$$PWD modules
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
