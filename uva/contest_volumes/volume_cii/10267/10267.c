#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_LENGTH 50
#define ARG_LENGTH 5
#define DELIMITERS " \n"
#define TABLE_SIZE 250
#define DEFAULT_COLOR 'O'
#define FILENAME_LENGTH 12

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
	int xleft, xright;
	
	if (x1 < x2) {
		xleft = x1;
		xright = x2;
	} else {
		xleft = x2;
		xright = x1;
	}
	
	int ytop, ybottom;
	
	if (y1 < y2) {
		ytop = y1;
		ybottom = y2;
	} else {
		ytop = y2;
		ybottom = y1;
	}
	
	int i, j;
	
	for (i = xleft - 1; i < xright; i++) {
		for (j = ytop - 1; j < ybottom; j++) {
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

table F(table t, int x, int y, char c) {
	table original = copy(t);
	x -= 1;
	y -= 1;
	t.pixels[y][x] = c;
	int search = 1, painted;
	
	do {
		painted = 0;
		
		int sx1 = x - search;
		int sx2 = x + search;
		int sy1 = y - search;
		int sy2 = y + search;
		int i;
		
		for (i = sy1; i <= sy2; i++) {
			if (sx1 >= 0 && sx1 < t.cols && i >= 0 && i < t.rows) {
				if (original.pixels[y][x] == t.pixels[i][sx1]) {
					t.pixels[i][sx1] = c;
					painted = 1;
				}
			}
			
			if (sx2 >= 0 && sx2 < t.cols && i >= 0 && i < t.rows) {
				if (original.pixels[y][x] == t.pixels[i][sx2]) {
					t.pixels[i][sx2] = c;
					painted = 1;
				}
			}
		}
		
		for (i = sx1; i <= sx2; i++) {
			if (i >= 0 && i < t.cols && sy1 >= 0 && sy1 < t.rows) {
				if (original.pixels[y][x] == t.pixels[sy1][i]) {
					t.pixels[sy1][i] = c;
					painted = 1;
				}
			}
			
			if (i >= 0 && i < t.cols && sy2 >= 0 && sy2 < t.rows) {
				if (original.pixels[y][x] == t.pixels[sy2][i]) {
					t.pixels[sy2][i] = c;
					painted = 1;
				}
			}
		}
		
		search++;
	} while (painted);
	
	return t;
}

void S(table t, char filename[]) {
	int i, j;
	char filename_dos[FILENAME_LENGTH + 1];
	
	strncpy(filename_dos, filename, FILENAME_LENGTH);
	printf("%s\n", filename_dos);
	
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
				return 0;
				break;
		}
	}
	
	return 0;
}
