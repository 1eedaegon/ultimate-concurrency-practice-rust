# OS: MacOS(M2 sillicon)

# Change compile target this(여기서 바꾼다.):
# TARGET = pthreads-c
TARGET = -c

############# Rust ############

############ Clang ############
CC = gcc

# With all warning and debugging 
# And allow void type pointer casting
# And allow no pointer type casting
CFLAGS = -Wall -g -Wno-pointer-to-int-cast -Wint-to-void-pointer-cast -Wunused-command-line-argument

SRC = $(TARGET).c
OBJ = $(SRC:.c=.o)
BIN = $(TARGET).bin

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ)

c-all: $(BIN)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

c-run: $(BIN)
	./$(BIN)

c-clean:
	rm -f $(OBJ) $(BIN)
################################


