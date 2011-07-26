#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define CHARS "abcdefghijklmnopqrstuvwxyz"
#define FILE_LENGTH 5000
#define WORD_COUNT 200
#define DELIMITERS " \n"

int cmp(const void *a, const void *b) {
	const char **ia = (const char **) a;
	const char **ib = (const char **) b;
	
	return strcmp(*ia, *ib);
}

int main() {
	char c;
	char file[FILE_LENGTH];
	int file_index = 0;
	
	do {
		c = tolower(fgetc(stdin));
		
		if (c != EOF) {
			if (strchr(CHARS, c)) {
				file[file_index++] = c;
			} else {
				file[file_index++] = ' ';
			}
		}
	} while (c != EOF);
	
	file[file_index++] = '\0';
	char *words[WORD_COUNT];
	int word_index = 0;
	char *word = strtok(file, DELIMITERS);
	
	while (word != NULL) {
		int i, found = 0;
		
		for (i = 0; i < word_index; i++) {
			if (strcmp(word, words[i]) == 0) {
				found = 1;
				break;
			}
		}
		
		if (!found) {
			words[word_index] = word;
			word_index++;
		}
		
		word = strtok(NULL, DELIMITERS);
	}
	
	qsort(words, word_index, sizeof(char *), cmp);
	int i;
	
	for (i = 0; i < word_index; i++) {
		printf("%s\n", words[i]);
	}
	
	return 0;
}
