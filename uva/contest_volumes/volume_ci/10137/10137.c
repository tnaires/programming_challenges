#include <stdio.h>
#include <math.h>

int main() {
	int n;
	float spending[1000];
	
	while (scanf("%d", &n) != EOF) {
		if (n == 0) break;
		
		int i;
		float sum = 0;
		
		for (i = 1; i <= n; i++) {
			scanf("%f", &spending[i]);
			sum += spending[i];
		}
		
		float avg = ceil((sum / n) * 100) / 100;
		float result = 0;
		
		for (i = 1; i <= n; i++) {
			if (spending[i] > avg) {
				result += spending[i] - avg;
			}
		}
		
		printf("$%.2f\n", result);
	}
	
	return 0;
}
