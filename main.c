#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "sentiment_analysis.h"
#include <ctype.h>
#include "reader.h"

int is_punctuation(char c) {
    return ispunct(c);
}

float calculate_average_score(char *line, struct words *word_sentiments, int num_words) {
    float main_score = 0.0;
    int counter_for_words = 0;

    // Dynamic Memory Allocation
    int length = strlen(line);
    char *copier = (char *)malloc((length + 1) * sizeof(char));
    // Checks for errors
    if (copier == NULL) {
        perror("Dynamic memory allocation failed!!");
        return -1.0;
    }
    // Allocated memory gets the line's copy
    strcpy(copier, line);

    // Tokenize the line into words
    // This is done by using strtok()
    // Include punctuation as part of the word
    char *tokenize = strtok(copier, " \t\n\r"); // Include space, tab, newline, and carriage return as delimiters
    while (tokenize != NULL) {
        // Checks if the token ends with punctuation
        int len = strlen(tokenize);
        if (is_punctuation(tokenize[len - 1])) {
            // If the token ends with punctuation, handle it accordingly
            // Create a copy of the token without the punctuation
            char *word_without_punctuation = malloc(len * sizeof(char));
            if (word_without_punctuation == NULL) {
                perror("Dynamic memory allocation failed!!");
                free(copier);
                return -1.0;
            }
            strncpy(word_without_punctuation, tokenize, len - 1); 
            // Copy the token without the last character (punctuation)
            word_without_punctuation[len - 1] = '\0'; 
            // Null
            //It terminates the copied word

            // Look for the word (without punctuation) in the word_sentiments array
            int j = 0;
            while (j < num_words) {
                // Compare the current token (word without punctuation) with each word in the lexicon
                if (strcasecmp(word_without_punctuation, word_sentiments[j].word) == 0) {
                    // If the word (without punctuation) is found, add its sentiment score to the total score
                    main_score += word_sentiments[j].score;
                    counter_for_words++;
                    break; // Stop searching for this word in the lexicon
                }
                j++;
            }
            // Free the allocated memory for the copied word without punctuation
            free(word_without_punctuation);             
        } else {
            // If the token does not end with punctuation handle it
            counter_for_words++;

            // Look for the word in the word_sentiments array
            int j = 0;
            while (j < num_words) {
                // Compare the current token (word) with each word in the vader_lexicon.txt
                if (strcasecmp(tokenize, word_sentiments[j].word) == 0) {
                    // Adding sentiment score to total score
                    main_score += word_sentiments[j].score;
                    break;
                }
                j++;
            }
        }
        tokenize = strtok(NULL, " \t\n\r"); // Move to the next token (word), including whitespace and punctuation characters
    }

    // Free allocated memory
    free(copier);

    // Calculating average score
    float average_score = 0.0;
    if (counter_for_words > 0) {
        average_score = main_score / counter_for_words;
    }

    return average_score;
}



float sentiment_analysis(char *line, struct words *word_sentiments, int num_words) {
          return calculate_average_score(line, word_sentiments, num_words);
      }

      int main(int argc, char *argv[]) {
          if (argc != 3) {
              printf("Usage: %s <vader_lexicon.txt> <validation.txt>\n", argv[0]);
              return 1;
          }

          int num_words; // Number of words read from the lexicon
          struct words *word_sentiments = read_lexicon(argv[1], &num_words);
          if (word_sentiments == NULL) {
              printf("Failed to read lexicon file.\n");
              return 1;
          }

          FILE *validation_text;
          char line[MAX_LINE_LENGTH];

          // Opening the validation.txt
          validation_text = fopen(argv[2], "r");
          if (validation_text == NULL) {
              perror("Error opening validation file");
              free(word_sentiments);
              return 1;
          }

          // Reading each line from the validation file
          printf("%-90s  %s\n", "string sample", "score");
          printf("--------------------------------------------------------------------------------------------------\n");
          while (fgets(line, MAX_LINE_LENGTH, validation_text) != NULL) {
              // Remove trailing newline character
              line[strcspn(line, "\n")] = 0;

              
              float score = sentiment_analysis(line, word_sentiments, num_words);
              // Score Calculated
            
              // Printing the final result
              printf("%-90s  %.2f\n", line, score);
          }

          // Closing the validation file
          fclose(validation_text);

          // Free the dynamic allocated memory
          free(word_sentiments);

          return 0;
      }
