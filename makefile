CXX      = g++
CXXFLAGS = -O2
OBJ      = board.o dgame.o dirnet.o evalnet.o features.o player.o nd.o

nd: $(OBJ)
	$(CXX) $(OBJ) -o nd

%.o: %.cpp *.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o nd
