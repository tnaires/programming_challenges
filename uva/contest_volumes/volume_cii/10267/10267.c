#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_LENGTH 50
#define ARG_LENGTH 5
#define DELIMITERS " \n"
#define TABLE_SIZE 250
#define DEFAULT_COLOR 'O'

typedef struct _table {
	char pixels[TABLE_SIZE][TABLE_SIZE];
	int rows, cols;
} table;

table C(table t) {
	int i, j;
	
	for (i = 0; i < t.rows; i++) {
		for (j = 0; j < t.cols; j++) {
			t.pixels[i][j] = DEFAULT_COLOR;
		}
	}
	
	return t;
}

table I(int m, int n) {
	table result;
	result.rows = n;
	result.cols = m;
	
	return C(result);
}

table L(table t, int x, int y, char c) {
	t.pixels[y - 1][x - 1] = c;
	return t;
}

table K(table t, int x1, int y1, int x2, int y2, char c) {
	int i, j;
	
	for (i = x1 - 1; i < x2; i++) {
		for (j = y1 - 1; j < y2; j++) {
			t.pixels[j][i] = c;
		}
	}
	
	return t;
}

table V(table t, int x, int y1, int y2, char c) {
	return K(t, x, y1, x, y2, c);
}

table H(table t, int x1, int x2, int y, char c) {
	return K(t, x1, y, x2, y, c);
}

table copy(table t) {
	table result;
	result.rows = t.rows;
	result.cols = t.cols;
	int i, j;
	
	for (i = 0; i < t.rows; i++) {
		for (j = 0; j < t.cols; j++) {
			result.pixels[i][j] = t.pixels[i][j];
		}
	}
	
	return result;
}

table paint(table t, int x, int y, char c) {
	if (x >= 0 && x < t.cols && y >= 0 && y < t.rows) {
		t.pixels[y][x] = c;
	}
	
	return t;
}

table F(table t, int x, int y, char c) {
	table original = copy(t);
	x -= 1;
	y -= 1;
	t.pixels[y][x] = c;
	int search = 1, painted = 0;
	
	do {
		painted = 0;
		
		int sx = x - search;
		int sy = y;
		
		if (sx >= 0 && sx < t.cols && sy >= 0 && sy < t.rows) {
			if (original.pixels[sy][sx] == t.pixels[sy][sx]) {
				t.pixels[sy][sx] = c;
				painted = 1;
			}
		}
		
		sx = x - search;
		sy = y - search;
		
		if (sx >= 0 && sx < t.cols && sy >= 0 && sy < t.rows) {
			if (original.pixels[sy][sx] == t.pixels[sy][sx]) {
				t.pixels[sy][sx] = c;
				painted = 1;
			}
		}
		
		sx = x;
		sy = y - search;
		
		if (sx >= 0 && sx < t.cols && sy >= 0 && sy < t.rows) {
			if (original.pixels[sy][sx] == t.pixels[sy][sx]) {
				t.pixels[sy][sx] = c;
				painted = 1;
			}
		}
		
		sx = x + search;
		sy = y - search;
		
		if (sx >= 0 && sx < t.cols && sy >= 0 && sy < t.rows) {
			if (original.pixels[sy][sx] == t.pixels[sy][sx]) {
				t.pixels[sy][sx] = c;
				painted = 1;
			}
		}
		
		sx = x + search;
		sy = y;
		
		if (sx >= 0 && sx < t.cols && sy >= 0 && sy < t.rows) {
			if (original.pixels[sy][sx] == t.pixels[sy][sx]) {
				t.pixels[sy][sx] = c;
				painted = 1;
			}
		}
		
		sx = x + search;
		sy = y + search;
		
		if (sx >= 0 && sx < t.cols && sy >= 0 && sy < t.rows) {
			if (original.pixels[sy][sx] == t.pixels[sy][sx]) {
				t.pixels[sy][sx] = c;
				painted = 1;
			}
		}
		
		sx = x;
		sy = y + search;
		
		if (sx >= 0 && sx < t.cols && sy >= 0 && sy < t.rows) {
			if (original.pixels[sy][sx] == t.pixels[sy][sx]) {
				t.pixels[sy][sx] = c;
				painted = 1;
			}
		}
		
		sx = x - search;
		sy = y + search;
		
		if (sx >= 0 && sx < t.cols && sy >= 0 && sy < t.rows) {
			if (original.pixels[sy][sx] == t.pixels[sy][sx]) {
				t.pixels[sy][sx] = c;
				painted = 1;
			}
		}
		
		search++;
	} while (painted);
	
	return t;
}

void S(table t, char filename[]) {
	printf("%s\n", filename);
	int i, j;
	
	for (i = 0; i < t.rows; i++) {
		for (j = 0; j < t.cols; j++) {
			printf("%c", t.pixels[i][j]);
		}
		
		printf("\n");
	}
}

int main() {
	char line[CMD_LENGTH];
	table t;
	
	while (fgets(line, CMD_LENGTH, stdin)) {
		char *token = strtok(line, DELIMITERS);
		char cmd = token[0];
		
		switch (cmd) {
			case 'I':
			case 'C':
			case 'L':
			case 'V':
			case 'H':
			case 'K':
			case 'F':
			case 'S':
			case 'X':
				break;
			default:
				continue;
		}
		
		char *args[5];
		int arg_count = 0;
		
		do {
			token = strtok(NULL, DELIMITERS);
			
			if (token) {
				args[arg_count] = token;
				arg_count++;
			} else {
				break;
			}
		} while (1 == 1);
		
		switch (cmd) {
			case 'I':
				t = I(atoi(args[0]), atoi(args[1]));
				break;
			case 'C':
				t = C(t);
				break;
			case 'L':
				t = L(t, atoi(args[0]), atoi(args[1]), args[2][0]);
				break;
			case 'V':
				t = V(t, atoi(args[0]), atoi(args[1]), atoi(args[2]), args[3][0]);
				break;
			case 'H':
				t = H(t, atoi(args[0]), atoi(args[1]), atoi(args[2]), args[3][0]);
				break;
			case 'K':
				t = K(t, atoi(args[0]), atoi(args[1]), atoi(args[2]), atoi(args[3]), args[4][0]);
				break;
			case 'F':
				t = F(t, atoi(args[0]), atoi(args[1]), args[2][0]);
				break;
			case 'S':
				S(t, args[0]);
				break;
			case 'X':
				break;
		}
	}
	
	return 0;
}
