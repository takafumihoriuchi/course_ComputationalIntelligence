#include <stdio.h>

int step(float y) {
	if (y > 0.0) return 1;
	else return 0;
}

int main(void)
{
	// initial values
	float w1 = 0.0;		// initial wieght
	float w2 = 0.2;		// initial wieght
	float theta = 0.5;	// threshold
	float k = 0.9;		// coefficient of learning efficiency
	float alpha = 0.2;	// coefficient of learning efficiency
	// input and labeled training data
	int x1 = 0;			// input
	int x2 = 1;			// input
	int d = 1;			// answer

	int x = !d;
	printf("\nd  : %d\n\n", d);
	while (x != d) {
		float y = (w1 * x1) + (w2*x2) - theta;
		x = step(y);
		w1 = (k * w1) + alpha*(d-x)*x1;
		w2 = (k * w2) + alpha*(d-x)*x2;
		printf("x  : %d\n", x);
		printf("w1 : %f\n", w1);
		printf("w2 : %f\n\n", w2);
	}
	// while文を仮に100回続けたとしても、一つの値に収束する訳ではない
	// 最適なw1、w2に収束はしない
	// この初期値だと、３回の更新で教師データと一致する推測値が得られる

	return 0;
}