CC = g++
CFLAGS = -Wall
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRC = src/main.cpp
BUILD_DIR = build

.PHONY: all clean raylib

all: $(BUILD_DIR)/timer

$(BUILD_DIR)/timer: $(SRC) raylib
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $(BUILD_DIR)/simple_timer $(LDFLAGS)