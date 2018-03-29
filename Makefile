CPP = g++
CPPFLAGS = -std=c++11

all: main

main: main.cc
	$(CPP) $(CPPFLAGS) Player.cc Invader.cc Object.cc GetKey.cc Bullet.cc Game.cc GameTimer.cc MotherShip.cc -o invaders $^

clean:
	rm -f invaders
