obj-m	:= sk_drv.o
APP	= sk_app


KDIR	:= /lib/modules/$(shell uname -r)/build
CC = gcc -DHOST
#KDIR	:= /work_kernel/linux
#CC = /opt/gnueabi/opt/ext-toolchain/bin/arm-linux-gnueabihf-gcc

all : module app task1 task2

module:
	$(MAKE) -C $(KDIR) SUBDIRS=$$PWD modules

app:
	$(CC) -o $(APP) $(APP).c

task1:
	$(CC) -o $@ task1.c

task2:
	$(CC) -o $@ task2.c

clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean

