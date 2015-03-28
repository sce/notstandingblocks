#!/bin/bash

g++ -I../include test1.cpp -L../src -lSCE_drivers $(sdl2-config --libs) -lSDL2_ttf -lSDL2_image $@
