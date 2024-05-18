CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# output directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# source files
TARGET = $(BIN_DIR)/accounting

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)


all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -rf $(BUILD_DIR) $(BIN_DIR)

run:
	./$(TARGET)

.PHONY: clean