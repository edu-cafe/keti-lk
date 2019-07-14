#include <stdio.h>
#include <fcntl.h>
#include <string.h>

/*
$ echo "18" > /sys/class/gpio/export
$ echo "out" > /sys/class/gpio/gpio18/direction
$ echo "1" > /sys/class/gpio/gpio18/value
$ echo "0" > /sys/class/gpio/gpio18/value
$ echo "18" > /sys/class/gpio/unexport
*/
int ledControl(int gpio)
{
   int fd;
   char buf[BUFSIZ];

   fd = open("/sys/class/gpio/_____", O_WRONLY);          /* 해당 GPIO 장치 사용 준비 */
   sprintf(buf, "%d", gpio);
   write(fd, buf, strlen(buf));
   close(fd);

   sprintf(buf, "/sys/class/gpio/gpio%d/_______", gpio);      /* 해당 GPIO 장치의 방향 설정 */
   fd = open(buf, O_WRONLY);
   /* 장치를 LED 출력을 위해서 설정 : 입력의 경우 write(fd, "in", 2); 사용 */
   write(fd, "out", 3);                                                          
   close(fd);

   sprintf(buf, "/sys/class/gpio/gpio%d/______", gpio);          /* 장치에 값 출력 */
   fd = open(buf, O_WRONLY);
   write(fd, "1", 1);
   sleep(1);
   write(fd, "0", 1);
   close(fd);

   fd = open("/sys/class/gpio/_____", O_WRONLY);     /* 사용한 GPIO 장치 해제하기 */
   sprintf(buf, "%d", gpio);
   write(fd, buf, strlen(buf));
   close(fd);

   return 0;
}

int main(int argc, char** argv)
{
   int gno;

   if(argc < 2) {
      printf("Usage : %s GPIO_NO\n", argv[0]);
      return -1;
   }
   gno = atoi(argv[1]);

   ledControl(gno);

   return 0;
}

//BCM(GPIO)-18
//$ sudo ./a.out 18
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
