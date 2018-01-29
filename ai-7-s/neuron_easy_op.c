#include <stdio.h>

int step(float y) {
	if (y > 0.0) return 1;
	else return 0;
}

float weighted_sum_2(int x1, int x2, int w1, int w2, float theta) {
	return (x1*w1) + (x2*w2) + theta;
}

float weighted_sum_1(int x, int w, float theta) {
	return (x*w) + theta;
}

int and(int x1, int x2) {
	int w1 = 1, w2 = 1;
	float theta = -1.5;
	float y = weighted_sum_2(x1, x2, w1, w2, theta);
	return step(y);
}

int or(int x1, int x2) {
	int w1 = 1, w2 = 1;
	float theta = -0.5;
	float y = weighted_sum_2(x1, x2, w1, w2, theta);
	return step(y);
}

int not(int x) {
	int w = -1;
	float theta = 0.5;
	float y = weighted_sum_1(x, w, theta);
	return step(y);
}

int main(void)
{
	printf("and: (1,0) -> %d\n", and(1,0));
	printf("and: (1,1) -> %d\n", and(1,1));
	printf("and: (0,0) -> %d\n", and(0,0));
	printf("or : (1,0) -> %d\n", or(1,0));
	printf("or : (1,1) -> %d\n", or(1,1));
	printf("or : (0,0) -> %d\n", or(0,0));
	printf("not: (1)   -> %d\n", not(1));
	printf("not: (0)   -> %d\n", not(0));
	return 0;
}