#include "resources.h"

// Static non-constant inits:
TTF_Font *Resources::fontVera = NULL;

int Resources::instances = 0;
bool Resources::graphicsSetup = false;

// The classes in sce.commons use this "default" path for accessing vera.ttf.
// The project-specific classes uses the overridden value in their
// local <project-name>resc class or so. Just so you know.
Resources::Resources() 
	: FONTVERA("resources/fonts/vera.ttf"), FONTVERASIZE(16)
{
	//printf("Resources()\n");
	instances++;
}

Resources::~Resources()
{
	//printf("~Resources()\n");
	if ( --instances == 0 ) {
		if ( fontVera ) {
			//printf(" -> Closing fontVera\n");
			TTF_CloseFont(fontVera);
			fontVera = NULL;
		}	
	}
}

void Resources::closeFontVera() {
		if ( fontVera ) {
			//printf("closeFontVera(): Closing fontVera\n");
			TTF_CloseFont(fontVera);
			fontVera = NULL;
		}	
}

void Resources::setupFontVera() {
	if ( fontVera == NULL && graphicsSetup )
		fontVera = GraphicDriver::openFont(Resources::FONTVERA, 
			Resources::FONTVERASIZE);
	
	//printf("%i\n", fontVera);
}

TTF_Font *Resources::getFontVera() {
	setupFontVera();
	if ( fontVera == NULL ) {
		//printf("%i\n", fontVera);
		printf("Resources::getFontVera(): Forced Exit: Couldn't load %s.\n", Resources::FONTVERA);
		exit(1);
	}
	return fontVera;
}

