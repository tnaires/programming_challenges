#include <stdio.h>

#define NUM_DIGITS 8

typedef struct _number {
	int digits[NUM_DIGITS];
	int count;
} number;

number new_number() {
	number result;
	int i;
	
	for (i = 0; i < NUM_DIGITS; i++) {
		result.digits[i] = -1;
	}
	
	result.count = 0;
	return result;
}

int valid_position(int pos) {
	return (pos >= 0) && (pos < NUM_DIGITS);
}

number set_digit(number num, int digit, int pos) {
	if (valid_position(pos)) {
		num.digits[pos] = digit;
		num.count++;
	}
	
	return num;
}

int get_digit(number num, int pos) {
	if (valid_position(pos)) {
		int position = NUM_DIGITS + pos - num.count;
		
		if (position < NUM_DIGITS) return num.digits[position];
	}
	
	return -1;
}

void print_times(char c, int times) {
	int i;
	
	for (i = 0; i < times; i++) {
		printf("%c", c);
	}
}

void display(number num, int s) {
	int columns = s + 2;
	int i, j;
	
	for (i = 0; i < num.count; i++) {
		int digit = get_digit(num, i);
		
		switch (digit) {
			case 0:
			case 2:
			case 3:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
				printf(" ");
				print_times('-', s);
				printf(" ");
				break;
			case 1:
			case 4:
				print_times(' ', columns);
				break;
		}
		
		if (i != num.count - 1) printf(" ");
	}
	
	printf("\n");
	
	for (j = 0; j < s; j++) {
		for (i = 0; i < num.count; i++) {
			int digit = get_digit(num, i);
			
			switch (digit) {
				case 0:
				case 4:
				case 8:
				case 9:
					printf("|");
					print_times(' ', columns - 2);
					printf("|");
					break;
				case 1:
				case 2:
				case 3:
				case 7:
					print_times(' ', columns - 1);
					printf("|");
					break;
				case 5:
				case 6:
					printf("|");
					print_times(' ', columns - 1);
					break;
			}
			
			if (i != num.count - 1) printf(" ");
		}
		
		printf("\n");
	}
	
	for (i = 0; i < num.count; i++) {
		int digit = get_digit(num, i);
		
		switch (digit) {
			case 0:
			case 1:
			case 7:
				print_times(' ', columns);
				break;
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 8:
			case 9:
				printf(" ");
				print_times('-', s);
				printf(" ");
				break;
		}
		
		if (i != num.count - 1) printf(" ");
	}
	
	printf("\n");
	
	for (j = 0; j < s; j++) {
		for (i = 0; i < num.count; i++) {
			int digit = get_digit(num, i);
			
			switch (digit) {
				case 0:
				case 6:
				case 8:
					printf("|");
					print_times(' ', columns - 2);
					printf("|");
					break;
				case 1:
				case 3:
				case 4:
				case 5:
				case 7:
				case 9:
					print_times(' ', columns - 1);
					printf("|");
					break;
				case 2:
					printf("|");
					print_times(' ', columns - 1);
					break;
			}
			
			if (i != num.count - 1) printf(" ");
		}
		
		printf("\n");
	}
	
	for (i = 0; i < num.count; i++) {
		int digit = get_digit(num, i);
		
		switch (digit) {
			case 0:
			case 2:
			case 3:
			case 5:
			case 6:
			case 8:
			case 9:
				printf(" ");
				print_times('-', s);
				printf(" ");
				break;
			case 1:
			case 4:
			case 7:
				print_times(' ', columns);
				break;
		}
		
		if (i != num.count - 1) printf(" ");
	}
	
	printf("\n");
}

int main() {
	int s, n;
	
	while (scanf("%d %d", &s, &n) != EOF) {
		if (s == 0 && n == 0) break;
		
		number num = new_number();
		
		if (n == 0) {
			num = set_digit(num, n, NUM_DIGITS - 1);
		} else {
			int i;
			
			for (i = NUM_DIGITS - 1; i >= 0; i--) {
				if (n > 0) {
					num = set_digit(num, n % 10, i);
					n /= 10;
				} else {
					break;
				}
			}
		}
		
		display(num, s);
		printf("\n");
	}
	
	return 0;
}