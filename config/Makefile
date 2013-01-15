CC=g++
SRC=Config
MAIN=test

all:$(MAIN).o $(SRC).o
	$(CC)  $(MAIN).o $(SRC).o

$(MAIN).o:$(MAIN).cpp
	$(CC) -c $(MAIN).cpp

$(SRC).o:$(SRC).cpp
	$(CC) -c $(SRC).cpp

clean:
	rm -rf *.o test
