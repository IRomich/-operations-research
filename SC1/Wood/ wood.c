#include <stdio.h>
#include <stdlib.h>

int main(void){
	int i, n, t1 = 0, t2 = 0, t3 = 0, t4 = 0;
	int black[20], red[20], blue[20], green[20];
	scanf("%d", &n);
	for (i = 0; i < n; i++){
		switch ((i + 1) % 4){
			case 0:
				black[t4++] = i + 1;
				break;
			case 1:
				green[t1++] = i + 1;
				break;
			case 2:
				red[t2++] = i + 1;
				break;
			case 3:
				blue[t3++] = i + 1;
		}
		
	}
	printf("Green: ");
	for (i = 0; i < t1; i++)
	{
		printf("%d ", green[i]);
	}
	printf("\nRed: ");
	for (i = 0; i < t2; i++)
	{
		printf("%d ", red[i]);
	}
	printf("\nBlue: ");
	for (i = 0; i < t3; i++)
	{
		printf("%d ", blue[i]);
	}
	printf("\nBlack: ");
	for (i = 0; i < t4; i++)
	{
		printf("%d ", black[i]);
	}
	return 0;
}