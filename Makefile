####compilar g++ minesweeper.cpp -w -lSDL2 -o mine

#### definitions

CXX = g++
CXXFLAGS = -w -lSDL2 
OBJS = mine_header.cpp mine_main.cpp
INCLUDE = #(-I "/home.../.h")
####

mine: ${OBJS}
	@echo compiling... $< [$@]
	 	${CXX} ${OBJS} ${CXXFLAGS} ${INCLUDES} -o $@ 

clean:
	@echo cleaning...
		-rm -f *.o core *.core






