CXX = g++
CXXFLAGS = -std=c++14 -MMD -Wall -g -Werror=vla
EXEC = kingbit
OBJECTS = main.o game.o textDisplay.o position.o subject.o debugDisplay.o bitboard.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}