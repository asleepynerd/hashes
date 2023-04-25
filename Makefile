CC = g++

CFLAGS = -Wall 

INCLUDE = -I include

SRC = src

BIN = bin

all: init sha1024 md7 ush

lanman2: $(SRC)/ush.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -o $(BIN)/ush $(SRC)/ush.cpp

md7: $(SRC)/md7.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -o $(BIN)/md7 $(SRC)/md7.cpp

sha1024: $(SRC)/sha1024.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -o $(BIN)/sha1024 $(SRC)/sha1024.cpp

init:
	mkdir -p $(BIN)

clean:
	rm -rf $(BIN)
