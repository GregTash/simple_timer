CC = gcc
CFLAGS = -Wall -std=c99
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRC = src/main.c
BUILD_DIR = build

.PHONY: all clean raylib

all: $(BUILD_DIR)/timer

$(BUILD_DIR)/timer: $(SRC) raylib
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $(BUILD_DIR)/simple_timer $(LDFLAGS)