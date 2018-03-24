CPP = clang++-3.7
CPPFLAGS = -std=c++14 -g -Weverything

all: main

main: main.cc
	$(CPP) $(CPPFLAGS) Player.cc Invader.cc Object.cc GetKey.cc Bullet.cc Game.cc GameTimer.cc -o invaders $^