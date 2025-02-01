CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = sudoku
SRCS = sudoku.c


OBJS = $(SRCS:.c=.o)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm 


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(TARGET)


run: $(TARGET)
	./$(TARGET)
