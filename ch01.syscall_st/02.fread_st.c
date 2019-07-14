#include <stdio.h>
#include <stdlib.h>

typedef struct INFO {
	char	name[20];
	int		age;
	float	height;
} INFO;

int main(int argc, char * argv[]){
	FILE *fp;
	int i;
	INFO data;
	
	if((fp = fopen(argv[1], ___)) == NULL){
		perror("fopen");
		exit(1);
	}
	
	while(1) {
		............
		if(.....){
			break;
		}
		printf("name:%s, age:%d, height:%.1f\n", data.name, data.age, data.height);
	}
	
	fclose(fp);
	return 0;
					
}
