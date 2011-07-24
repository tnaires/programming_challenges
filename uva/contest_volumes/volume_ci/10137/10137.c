#include <stdio.h>

int main() {
	int n;
	double spending[1000];
	
	while (scanf("%d", &n) != EOF) {
		if (n == 0) break;
		
		int i;
		double sum = 0;
		
		for (i = 1; i <= n; i++) {
			scanf("%lf", &spending[i]);
			sum += spending[i];
		}
		
		double avg = sum / n;
		avg = (long) (avg * 100 + 0.5);
		avg /= 100;
		
		double result_over = 0, result_under = 0;
		
		for (i = 1; i <= n; i++) {
			if (spending[i] > avg) {
				result_over += spending[i] - avg;
			} else if (spending[i] < avg) {
				result_under += avg - spending[i];
			}
		}
		
		printf("$%.2lf\n", result_over < result_under ? result_over : result_under);
	}
	
	return 0;
}
