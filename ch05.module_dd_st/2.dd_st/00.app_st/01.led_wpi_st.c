#include <stdio.h>
#include <stdlib.h>
#include <________.h>

int ledOnOff(int gno)
{
	int i;
	..........
	
	for(i=0; i<5; i++) {
		............
		delay(1000);
		............
		delay(1000);
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int gno;
	
	if(argc < 2) {
		printf("Usage : %s GPIO_NO\n", argv[0]);
		exit(-1);
	}
	gno = atoi(argv[1]);
	
	.........
	
	ledOnOff(gno);
	
	return 0;
}

//$ gpio readall
// BCM(GPIO)-18, (Pin-12) -> wpi-1
//$ sudo ./a.out 1

/*
$ gpio -g mode 18 out
$ gpio -g write 18 1
$ gpio -g write 18 0

$ gpio export 18 out
$ gpio -g write 18 1
$ gpio unexport 18

$ gpio readall  (GPIO18 -> Wpi 1)
$ gpio mode 1 out
$ gpio write 1 1
$ gpio write 1 0
*/




