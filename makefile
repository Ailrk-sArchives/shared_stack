CC = clang

ROOT_DIR = .

CFLAGS = -std=c11
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wundef
CFLAGS += -Wno-ignored-qualifiers
CFLAGS += -I. -pthread

DEPS =
SRC = test.c shared_stack.c systack.c
OBJS = ${SRC:.c=.o}

.PHONY: clean test

test: $(OBJS)
	$(CC) $(OBJS) -o $@ $(CFLAGS)

$(OBJS): $(SRC) $(DEPS)
	$(CC) -c $^ $(CFLAGS)

clean:
	@rm ./*.o -f
	@rm ./temp -rf
	@rm test
