CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -g
SRC = src/my_lib.c src/utils.c
OBJ = $(SRC:.c=.o)
LIB = libcustom.a

.PHONY: all clean test

all: $(LIB)

$(LIB): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# test: $(LIB) $(TEST_OBJ)
# 	$(CC) $(CFLAGS) -o test_custom_library $(TEST_OBJ) -L. -lcustom
# 	./test_custom_library

clean:
	rm -f $(OBJ) $(LIB) test_my_lib $(TEST_OBJ)