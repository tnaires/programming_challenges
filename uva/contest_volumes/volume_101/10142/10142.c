#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 82
#define MAX_BALLOTS 1000
#define MAX_CANDIDATES 20

typedef struct candidate {
  char name[LINE_LENGTH];
} Candidate;

typedef struct ballot {
  int votes[MAX_CANDIDATES];
} Ballot;

int get_n_cases() {
  int n_cases;
  char line[LINE_LENGTH];

  fgets(line, LINE_LENGTH, stdin);
  sscanf(line, "%d", &n_cases);
  fgets(line, LINE_LENGTH, stdin);

  return n_cases;
}

Candidate* get_candidates() {
  char line[LINE_LENGTH];
  int n_candidates, i;

  fgets(line, LINE_LENGTH, stdin);
  sscanf(line, "%d", &n_candidates);
  Candidate* candidates = (Candidate *) calloc(n_candidates, sizeof(Candidate));

  for (i = 0; i < n_candidates; i++) {
    fgets(candidates[i].name, LINE_LENGTH, stdin);
  }

  return candidates;
}

Ballot* get_ballots() {
  char line[LINE_LENGTH];
  Ballot* ballots = (Ballot *) calloc(MAX_BALLOTS, sizeof(Ballot));
  int i = 0, j = 0;

  while (fgets(line, LINE_LENGTH, stdin)) {
    if (line[0] == '\n') {
      break;
    }

    char* token = strtok(line, " ");

    while (token) {
      ballots[i].votes[j++] = atoi(token);
      token = strtok(NULL, " ");
    }

    i++;
  }

  return ballots;
}

int main() {
  int i, n_cases = get_n_cases();

  for (i = 0; i < n_cases; i++) {
    Candidate* candidates = get_candidates();
    Ballot* ballots = get_ballots();

    free(ballots);
    free(candidates);
  }

  return 0;
}
