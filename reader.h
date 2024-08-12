#ifndef LEXICON_READER_H
#define LEXICON_READER_H

#include "sentiment_analysis.h" // Include necessary headers

// Function declaration
struct words *read_lexicon(const char *filename, int *num_words);

#endif 
