BUILD_FOLDER = build
TARGET = libcsv.a
TEST = test

CFLAGS = -Wall -fPIC -O4
INCLUDE = -Iinclude

SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c, $(BUILD_FOLDER)/%.o, $(SRC))

default: $(BUILD_FOLDER) $(BUILD_FOLDER)/$(TARGET) $(TEST)

$(BUILD_FOLDER)/$(TARGET): $(OBJ)
	ar rcs $@ $^

$(BUILD_FOLDER):
	mkdir $(BUILD_FOLDER)

$(BUILD_FOLDER)/%.o: src/%.c
	gcc -c $< -o $@ $(CFLAGS) $(INCLUDE)

$(TEST):
	make -C $(TEST) default

clean:
	rm -rf $(BUILD_FOLDER)
	make -C $(TEST) clean

.PHONY: test