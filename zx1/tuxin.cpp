#include <stdio.h>
#include <time.h>
#include <complex.h>
#include <math.h>
#include <easyx.h>
int main() {
	initgraph(600, 600, 1);
	setbkcolor(RGB(123, 234, 54));
	cleardevice();

	while (1) {
		cleardevice();
		circle(300, 300, 100);
		setlinecolor(RED);
		line(2, 2, 500, 500);
	}
	
	closegraph();
	return 0;
}