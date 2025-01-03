CC = g++
CFLAGS = -g -std=c++11 -Wall 
SRC_DIR = src
BUILD_DIR = obj
INCLUDE_DIR = include
BIN_DIR = bin

$(shell mkdir -p $(BUILD_DIR) $(BIN_DIR))

all: ${BIN_DIR}/main

${BUILD_DIR}/Game.o: ${INCLUDE_DIR}/Game.hpp ${SRC_DIR}/Game.cpp 
	@mkdir -p ${BUILD_DIR}
	$(CC) $(CFLAGS) -c ${SRC_DIR}/Game.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/Game.o

${BUILD_DIR}/Reversi.o: ${INCLUDE_DIR}/Game.hpp ${INCLUDE_DIR}/Reversi.hpp ${SRC_DIR}/Reversi.cpp 
	@mkdir -p ${BUILD_DIR}
	$(CC) $(CFLAGS) -c ${SRC_DIR}/Reversi.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/Reversi.o

${BUILD_DIR}/main.o: ${INCLUDE_DIR}/Game.hpp ${INCLUDE_DIR}/Reversi.hpp ${SRC_DIR}/main.cpp 
	@mkdir -p ${BUILD_DIR}
	$(CC) $(CFLAGS) -c ${SRC_DIR}/main.cpp -I$(INCLUDE_DIR) -o ${BUILD_DIR}/main.o

${BIN_DIR}/main: ${BUILD_DIR}/main.o ${BUILD_DIR}/Reversi.o ${BUILD_DIR}/Game.o
	@mkdir -p ${BIN_DIR}
	$(CC) $(CFLAGS) ${BUILD_DIR}/main.o ${BUILD_DIR}/Reversi.o ${BUILD_DIR}/Game.o -o ${BIN_DIR}/main

clean:
	@rm -f ${BUILD_DIR}/*.o
	@rm -f ${BIN_DIR}/*

valgrind: ${BIN_DIR}/main

.PHONY: all clean valgrind