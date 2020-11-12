CC = clang

ROOT_DIR = .

CFLAGS = -std=c11
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wundef
CFLAGS += -Wno-ignored-qualifiers
CFLAGS += -I. -pthread

DEPS =
SRC = shared_stack.c systack.c
OBJS = ${SRC:.c=.o}

.PHONY: clean test

all: $(OBJS)
	$(CC) $(OBJS) -fPIC -shared -o shared_stack.so $(CFLAGS)

static: $(OBJS)
	$(CC) $(OBJS) -c $^ $(CFLAGS)
	ar rcs ./shared_stack.a $^

test: test.c $(OBJS)
	$(CC) $(OBJS) -o $@ $(CFLAGS)
	./test

$(OBJS): $(SRC) $(DEPS)
	$(CC) -c $^ $(CFLAGS)

clean:
	@rm ./*.o -f
	@rm ./*.so -f
	@rm ./*.out
	@rm test
