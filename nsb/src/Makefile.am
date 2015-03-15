## Makefile.am -- Process this file with automake to produce Makefile.in

INCLUDES		= -I../include -I../../sce.drivers/include -I../../sce.commons/include -I../../othersrc/include

bin_PROGRAMS = nsb
nsb_SOURCES = block.cpp gameaudio.cpp gameengine.cpp gameresc.cpp map.cpp nextblockwindow.cpp blockswindow.cpp game.cpp gamegraphics.cpp main.cpp menutest1.cpp scorewindow.cpp
nsb_LDADD = ../../sce.drivers/src/libSCE_drivers.a ../../sce.commons/src/libSCE_commons.a ../../othersrc/src/libSCE_others.a -lSDL -lSDL_mixer -lSDL_ttf -lSDL_image
nsb_LDFLAGS = -lSDL -lSDL_mixer -lSDL_ttf -lSDL_image

###libSCE_commons_a_LIBADD = -lSDL -lSDL_mixer -lSDL_ttf -lSDL_image
