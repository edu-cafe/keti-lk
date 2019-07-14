obj-m	:= sk_drv.o
APP	= sk_app


#KDIR	:= /lib/modules/$(shell uname -r)/build
#CC = gcc -DHOST
#KBUILD_CFLAGS += -DHOST
KDIR	:= /work/linux
CC = /opt/gnueabi/opt/ext-toolchain/bin/arm-linux-gnueabihf-gcc

all : module app

module:
	$(MAKE) -C $(KDIR) SUBDIRS=$$PWD modules

app:
	$(CC) -o $(APP) $(APP).c

clean:
	$(MAKE) -C $(KDIR) M=$PWD clean
	
