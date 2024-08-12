CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRC_MAIN = main.c
SRC_READER = reader.c
HEADERS = sentiment_analysis.h reader.h
TARGET = mySA

all : $(TARGET)

$(TARGET): $(SRC_MAIN:.c=.o) $(SRC_READER:.c=.o) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC_MAIN:.c=.o) $(SRC_READER:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) vader_lexicon.txt validation.txt


clean:
	rm -f $(TARGET) *.o
