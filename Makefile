CC = g++

CFLAGS = -Wall 

INCLUDE = -I include

SRC = src

BIN = bin

all: init sha1024

sha1024: $(SRC)/sha1024.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -o $(BIN)/sha1024 $(SRC)/sha1024.cpp

init:
	mkdir -p $(BIN)

clean:
	rm -rf $(BIN)
