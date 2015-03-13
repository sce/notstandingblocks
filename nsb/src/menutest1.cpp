#include "menutest1.h"

Menu::Menu() : VERSION("0.5 Release"), DATE("17th November 2005")
{	
	//printf("Menu()\n");
	tp = 0; // textboxes-pointer
	dp = 0; // dialogs-pointer
	sp = 0; // selectors-pointer
	toplayer = 0; // which is the highest level? -> meant to ease computation
	menuposition = 0; // which selector is selected?

	// For easy reffering: make global pointers to all objects 
	startsel = NULL;
	aboutsel = NULL;
	quitsel = NULL;
	aboutdia = NULL;
	welcometxt = NULL;

	background = NULL;
	
	nsb = new Game();
	audio = new GameAudio();
	graphicDrv = new GraphicDriver();
	resc = new GameResc();
	
	state = MENU;
	
	/* Setup tables */	
	for (int i=0; i<MAX_OBJECTS; i++) {
			textboxes[i] = NULL;
			dialogs[i] = NULL;
			selectors[i] = NULL;
	}
	Quit = 0;
}


Menu::~Menu() {
	//printf("~Menu()\n");
	for (int i=0; i<MAX_OBJECTS; i++)
	{
		if (textboxes[i] != NULL)
			delete textboxes[i];
		if (dialogs[i] != NULL)
			delete dialogs[i];
		if (selectors[i] != NULL)
			delete selectors[i];
	}
	if ( background ) SDL_FreeSurface(background);

/* Don't need to delete them twice.
	if ( startsel ) delete startsel;
	if ( aboutsel ) delete aboutsel;
	if ( quitsel ) delete quitsel;
	if ( aboutdia ) delete aboutdia;
	if ( welcometxt ) delete welcometxt;
*/
	//printf(" -> Deleting resc\n");
	if ( resc ) delete resc;
	
	//printf(" -> Deleting audio\n");
	if ( audio ) delete audio;
	//printf(" -> Deleting nsb\n");
	if ( nsb ) delete nsb;

	//printf(" -> Deleting graphicDrv\n");
	if ( graphicDrv ) delete graphicDrv;
	//printf(" -> Done\n");
}


void Menu::UpdateDisplay(SDL_Surface *screen)
{
	//static int black = SDL_MapRGB(screen->format, 0, 0, 0);
	//SDL_FillRect(screen, 0, black); // make it black baby
	
	GraphicDriver::blitToMain(background, 0, 0);
	
	for (int l=0; l<=toplayer; l++) // go through each layer
	{
		for (int i=0; i<tp; i++) // go through each textbox
			if (textboxes[i] != NULL)
				if (textboxes[i]->GetLayer() == l)  // is this supposed to be drawn now?
					textboxes[i]->Draw(screen);

		for (int i=0; i<dp; i++)
			if (dialogs[i] != NULL)
				if (dialogs[i]->GetLayer() == l)  // is this supposed to be drawn now?
					dialogs[i]->Draw(screen);
				
		for (int i=0; i<sp; i++)
			if (selectors[i] != NULL)
				if (selectors[i]->GetLayer() == l)  // is this supposed to be drawn now?
					selectors[i]->Draw(screen);
	}
	SDL_Flip(screen);
	SDL_Delay(1); // to free up CPU time, perhaps not needed in singel-threaded app
}


void Menu::UpdateMenu(SDL_Surface *screen)
{
	for (int i=0; i<MAX_OBJECTS; i++) {
		if (selectors[i] != NULL)
			selectors[i]->SetXY(GameResc::RESX/2-selectors[i]->GetWidth()/2, 
								GameResc::RESY/10*(i*2+4)-selectors[i]->GetHeight()/2);
	}
}


void Menu::AboutKeyHandler(SDL_Surface *screen)
{
	/* Check for keys, update info based on keys, and stuff */
	SDL_Event event;
	SDL_keysym keysym;
	
	while ( SDL_PollEvent( &event ) )
	{
		switch ( event.type ) {
			case SDL_KEYDOWN:	
				keysym = event.key.keysym;
				switch ( keysym.sym ) {
					case SDLK_RETURN:
					case SDLK_ESCAPE:
					case SDLK_q:		
						ChangeState(MENU);
						break;
					default:			
						break;
				};					
				break;
			case SDL_QUIT:
				/* exit(0); immidiate quit */
				Quit = 1;
				break; /* heh */
			default:			
				break;		
		};
	}
}	


void Menu::MenuKeyHandler(SDL_Surface *screen)
{
	/* Check for keys, update positions, and stuff */
	SDL_Event event;
	SDL_keysym keysym;

	while ( SDL_PollEvent( &event ) )
	{
		switch ( event.type ) {
			case SDL_KEYDOWN:	
				keysym = event.key.keysym;
				switch ( keysym.sym ) {
					case SDLK_RIGHT:
						if (menuposition == 2)
							menuposition = 0;
						else
							++menuposition;
						for (int i=0; i<sp; i++)
							selectors[i]->UnSelect();
						selectors[menuposition]->Select();
						break;
					case SDLK_LEFT: 	
						if (menuposition == 0)
							menuposition = 2;
						else
							--menuposition;
						for (int i=0; i<sp; i++)
							selectors[i]->UnSelect();
						selectors[menuposition]->Select();
						break;
					case SDLK_UP:		
						if (menuposition == 0)
							menuposition = 2;
						else
							--menuposition;
						for (int i=0; i<sp; i++)
							selectors[i]->UnSelect();
						selectors[menuposition]->Select();
						break;
					case SDLK_DOWN:		
						if (menuposition == 2)
							menuposition = 0;
						else
							++menuposition;
						for (int i=0; i<sp; i++)
							selectors[i]->UnSelect();
						selectors[menuposition]->Select();
						break;
					case SDLK_RETURN:
						switch (menuposition)
						{
							case 2:
								Quit = 1;
								break;
							case 1:
								ChangeState(ABOUT);
								break;
							case 0:
								nsb->run();
								audio->playMenuMusic();
								break;
							default:
								break;
						}
						break;
					case SDLK_ESCAPE:
					case SDLK_q:		
						Quit = 1;
						break;
					default:			
						break;
				};					
				break;
			case SDL_QUIT:
				/* exit(0); immidiate quit */
				Quit = 1;
				break; /* heh */
			default:			
				break;		
		};
	}
}	


void Menu::KeyHandler(SDL_Surface *screen)
{
	switch (state)
	{
		case MENU:
			MenuKeyHandler(screen);
			break;
		case ABOUT:
			AboutKeyHandler(screen);
			break;
		default:
			break; // hmm
	}
}


void Menu::ChangeState(enum STATE newstate)
{
	switch (newstate)
	{
		case MENU:
			state = MENU;
			for (int i=0; i<MAX_OBJECTS; i++) {
				if (textboxes[i] != NULL)
					textboxes[i]->InVisible();
				if (dialogs[i] != NULL)
					dialogs[i]->InVisible();
				if (selectors[i] != NULL)
					selectors[i]->InVisible();
			}
			welcometxt->Visible();
			startsel->Visible();
			aboutsel->Visible();
			quitsel->Visible();
			break;
		case ABOUT:
			state = ABOUT;
			/* for (int i=0; i<MAX_OBJECTS; i++) {
				if (textboxes[i] != NULL) textboxes[i]->InVisible();
				if (dialogs[i] != NULL) dialogs[i]->InVisible();
				if (selectors[i] != NULL) selectors[i]->InVisible();
			} */
			aboutdia->Visible();
			break;
		default:
			break;
	} }


/**
 * Returns non-zero on error, zero on success.
 */
int Menu::initprog()
{	
	SDL_EnableKeyRepeat( 100, 100 );

	graphicDrv->setupScreen(GameResc::RESX, GameResc::RESY, 
		GameResc::DEPTH, GameResc::FLAGS );
	graphicDrv->setupFont();
	
	resc->graphicsSetup = true;
	
	background = GraphicDriver::loadImage(GameResc::MAINMENUBACKGROUND);

	if ( background == NULL ) {
		return -1;
	}

	/* If we got this far, everything worked */
	//printf("Startup done\n");

	return 0;
}


int Menu::menutest ( void )
{	
	//SDL_Surface *screen;
	//TTF_Font *font_vera;
	//initprog(&screen, &font_vera);
	if ( initprog() )
		return -1;

	audio->setup();
	audio->playMenuMusic();
	
	welcometxt = new Textbox(graphicDrv->getScreen(), resc->getFontVera(), 
		"Welcome to Not Standing Blocks!");
	textboxes[tp++] = welcometxt;
	welcometxt->AddLine("Please select one of the following:");
	welcometxt->SetAlignment(CENTER);
	welcometxt->ReCreate(graphicDrv->getScreen());
	welcometxt->SetXY(GameResc::RESX/2-welcometxt->GetWidth()/2, GameResc::RESY/10);

	startsel = new Selector(graphicDrv->getScreen(), resc->getFontVera(), "  Start  ");
	selectors[sp++] = startsel;
	startsel->SetThicknes(BOTH, 1);
	startsel->SetMargin(SELECTED, 12);
	startsel->SetMargin(UNSELECTED, 8);
	startsel->ReCreate(graphicDrv->getScreen());
	startsel->SetXY(GameResc::RESX/2-startsel->GetWidth()/2, GameResc::RESY/10*4-startsel->GetHeight()/2);
	startsel->Select();

	aboutsel = new Selector(graphicDrv->getScreen(), resc->getFontVera(), "  About  ");
	selectors[sp++] = aboutsel;
	aboutsel->SetThicknes(BOTH, 1);
	aboutsel->SetMargin(SELECTED, 12);
	aboutsel->SetMargin(UNSELECTED, 8);
	aboutsel->ReCreate(graphicDrv->getScreen());
	aboutsel->SetXY(GameResc::RESX/2-aboutsel->GetWidth()/2, GameResc::RESY/10*6-aboutsel->GetHeight()/2);
	aboutsel->UnSelect();

	quitsel = new Selector(graphicDrv->getScreen(), resc->getFontVera(), "  Quit  ");
	selectors[sp++] = quitsel;
	quitsel->SetThicknes(BOTH, 1);
	quitsel->SetMargin(SELECTED, 12);
	quitsel->SetMargin(UNSELECTED, 8);
	quitsel->ReCreate(graphicDrv->getScreen());
	quitsel->SetXY(GameResc::RESX/2-quitsel->GetWidth()/2, GameResc::RESY/10*8-quitsel->GetHeight()/2);
	quitsel->UnSelect();

	aboutdia = new Dialog(graphicDrv->getScreen(), resc->getFontVera(), "  About this Game  ");
	dialogs[dp++] = aboutdia;
	aboutdia->AddLine(" ");
	aboutdia->AddLine("Code and Graphics made by:");
	aboutdia->AddLine("S. Christoffer Eliesen");
	char *Made = new char[128]; // prevent buffer overflow
	snprintf(Made, 128, "Version %s, %s", VERSION, DATE);
	aboutdia->AddLine(Made);
	
	aboutdia->AddLine(" ");
	aboutdia->AddLine("The music is not made by me, and licensed under");
	aboutdia->AddLine("Creative Commons Sampling Plus license");
	//aboutdia->AddLine("The music is so far shamelessly stolen");
	//aboutdia->AddLine("from excellent musicians.. Sorry guys :-(");
	
	aboutdia->SetAlignment(CENTER);
	aboutdia->SetMargin(20);
	aboutdia->ReCreate(graphicDrv->getScreen());
	aboutdia->SetXY(GameResc::RESX/2-aboutdia->GetWidth()/2, GameResc::RESY/2-aboutdia->GetHeight()/2);
	aboutdia->InVisible();
	aboutdia->SetLayer(1);
	toplayer = 1;

	while ( !Quit ) {
		KeyHandler(graphicDrv->getScreen());
		UpdateMenu(graphicDrv->getScreen());
		UpdateDisplay(graphicDrv->getScreen());
	};
	
	delete Made;

	return 0;
}

