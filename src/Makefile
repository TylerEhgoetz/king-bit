CXX=g++
CXXFLAGS=-std=c++14 -MMD
OBJECTS=main.o subject.o game.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
