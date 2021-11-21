CXX=g++
CXXFLAGS=-std=c++14 -MMD -g
OBJECTS=local_main.o position.o bitboard.o 
DEPENDS=${OBJECTS:.o=.d}
EXEC=kingbit

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}