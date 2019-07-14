#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

#define	DEVICE_FILENAME	"/dev/mem"

#define	GPIO_BASE	(0x3F200000)
#define	GPIO_SIZE	(256)
#define	GPFSEL1		(0x3F200004)	//GPIO18:bit26-24 -> 001(output)
#define	GPSET0		(0x3F20001C)	//GPIO18:bit18 -> 1(set)
#define	GPCLR0		(0x3F200028)	//GPIO18:bit18 -> 1(clear)
#define	OFF_GPFSEL1	(0x04)
#define	OFF_GPSET0	(0x1C)
#define	OFF_GPCLR0	(0x28)

volatile unsigned int *gpio;

int main(void)
{
	int fd;
	void *gpio_map;
	int i;

	fd = _____(DEVICE_FILENAME, O_RDWR|O_SYNC);
	if(fd < 0) {
		perror("/dev/mem file open error!!");
		exit(-1);
	} else printf("/dev/mem file open ok!!\n");

	gpio_map = _____(NULL, GPIO_SIZE, PROT_READ|PROT_WRITE, 
				MAP_SHARED, fd, GPIO_BASE);
	if(gpio_map == MAP_FAILED) {
		printf("[APP]gpio_mmap error!!\n");
		exit(-2);
	}
	gpio = (volatile unsigned int *)gpio_map;
	printf("gpio mmap ok(addr:%p)!!\n", gpio);
	
	*(gpio + OFF_GPFSEL1/4) &= ~(7 << 24);	//bit26~24 clear
	*(gpio + OFF_GPFSEL1/4) |= (1 << 24);	//bit26~24 -> 001(ouput mode)
	for(i=0; i<5; i++) {
		*(gpio + ________ ) |= (1 << 18);		//bit18 -> 1(led on)
		sleep(1);
		*(gpio + ________ ) |= (1 << 18);		//bit18 -> 1(led off)
		sleep(1);
	}	
	
	_______(gpio_map, GPIO_SIZE);
	_______(fd);
	printf("led end...\n");
	return 0;
}

