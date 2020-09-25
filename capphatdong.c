#include<stdio.h>
#include<stdlib.h>
int main() {
	int* p, * n, * h;
	int a, tem, t;
	scanf_s("%d", &a);
	t = a - 1; 
	p = malloc(sizeof(double) * t );
	for (n = p; n <= p + t ; n++) {
		printf("so thu %d:  ", n - p +1);// vi thu tu dau tien la 0
		scanf_s("%d", n);	
	}
	for (n = p; n < (p + t - 1) ; n++) {
		for (h = p + 1; h < (p + t); h++) {
			if (*n > *h) {
				tem = *n;
				*n = *h;
				*h = tem;
			}
		}
	}
	for (n = p; n <= p + t; n++) {
		printf("%d  ", ( *n));
	}
	return 0;
}