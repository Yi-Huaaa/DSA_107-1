#ifndef PANCAKE_NAMES_H
#define PANCAKE_NAMES_H

#define MAX_NM 20000000

#include <stdio.h>
#include <stdlib.h>

int N = 4;
char S[MAX_NM][5] = {"abc", "abe", "bcde", "abc"};
int M = 3;
char Q1[MAX_NM][5] = {"a", "ab", "ab"}, Q2[MAX_NM][6] = {"b", "abc", "dce"};
int _answer[MAX_NM];

void InitPancakes() {}
void AnswerArvin(int i, int count) {
    if (i >= M) {
        fprintf(stderr, "index %d out of range (M=%d)\n", i, M);
        exit(1);
    }
    _answer[i] = count;
}

void ByeArvin() {
    int _correct[] = {3, 2, 4};
    for (int i = 0; i < M; ++i) {
        if (_answer[i] != _correct[i]) {
            fprintf(stderr, "Answer to query #%d is incorrect."
                "You answered %d but the correct answer is %d.\n",
                i, _answer[i], _correct[i]);
            exit(1);
        }
    }
    puts("Correct on sample case!");
    exit(0);
}

#endif /* #ifndef PANCAKE_NAMES_H */
