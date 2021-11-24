CXX=g++
CXXFLAGS=-std=c++14 -MMD -g
OBJECTS=bitboard.o debugDisplay.o game.o main.o position.o subject.o textDisplay.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=kingbit

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}