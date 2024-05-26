CC = gcc
CFLAGS = -Wall -g
OUTPUT_DIR = bin
SRC_DIR = src
INCLUDE_DIR = include
LIB_DIR = lib

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OUTPUT_DIR)/%.o, $(SOURCES))
TARGETS = $(patsubst $(SRC_DIR)/%.cpp, $(OUTPUT_DIR)/%, $(SOURCES))

all: $(TARGETS)

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

$(OUTPUT_DIR)/%: $(SRC_DIR)/%.cpp | $(OUTPUT_DIR)
	$(CC) $(CFLAGS) -o $@ $< -lstdc++

$(OUTPUT_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OUTPUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OUTPUT_DIR)/*.o $(OUTPUT_DIR)/*

print:
	@echo "SOURCES: $(SOURCES)"
	@echo "OBJECTS: $(OBJECTS)"
	@echo "TARGETS: $(TARGETS)"