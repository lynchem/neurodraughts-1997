all: clean nd

nd: board.o dgame.o dirnet.o evalnet.o features.o player.o nd.o
	g++ obj/board.o obj/dgame.o obj/dirnet.o obj/evalnet.o obj/features.o obj/player.o obj/nd.o -o nd

board.o:
	g++ -c board.cpp -o obj/board.o
	
dgame.o:
	g++ -c dgame.cpp -o obj/dgame.o
	
dirnet.o:
	g++ -c dirnet.cpp -o obj/dirnet.o
	
evalnet.o:
	g++ -c evalnet.cpp -o obj/evalnet.o
	
features.o:
	g++ -c features.cpp -o obj/features.o
	
player.o:
	g++ -c player.cpp -o obj/player.o
	
nd.o:
	g++ -c nd.cpp -o obj/nd.o


clean:
	rm -rf obj/* nd
