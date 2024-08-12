#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reader.h"

struct words *read_lexicon(const char *filename, int *num_words) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening lexicon file");
        return NULL;
    }

    // Allocate memory for initial word_sentiments array
    int max_words = MAX_WORDS;
    struct words *word_sentiments = malloc(max_words * sizeof(struct words));
    if (word_sentiments == NULL) {
        // Handle memory allocation error
        perror("Memory allocation Failed!!");
        fclose(file);
        return NULL;
    }

    *num_words = 0;

    // Read each line from the lexicon file
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        // Parsing line
        char word[MAX_WORD_LENGTH];
        float score;
        if (sscanf(line, "%s %f", word, &score) == 2) {
            // Copy values to struct
            strcpy(word_sentiments[*num_words].word, word);
            word_sentiments[*num_words].score = score;

            (*num_words)++;

            // Check for memory reallocation
            if (*num_words >= max_words) {
                max_words *= 2;
                struct words *temp = realloc(word_sentiments, max_words * sizeof(struct words));
                if (temp == NULL) {
                    perror("Memory reallocation Failed!!");
                    fclose(file);
                    free(word_sentiments);
                    return NULL;
                }
                word_sentiments = temp;
            }
        }
    }

    // Close the file
    fclose(file);

    return word_sentiments;
}
