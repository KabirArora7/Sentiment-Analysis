#ifndef SENTIMENT_ANALYSIS_H
#define SENTIMENT_ANALYSIS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_WORD_LENGTH 50
#define MAX_INTENSITY_SCORES 10
#define MAX_LINE_LENGTH 1000
#define MAX_WORDS 1000

struct words {
    char word[MAX_WORD_LENGTH];
    float score;
    float SD;
    int SIS_array[MAX_INTENSITY_SCORES];
};

float sentiment_analysis(char *sentence, struct words *word_sentiments, int num_words);

#endif
