#include "scorewindow.h"

ScoreWindow::~ScoreWindow(void)
{
	// leave font_ alone
}

ScoreWindow::ScoreWindow(void)
//	: x(280+180+20), y(60)
{
	surfaceX = 280+180+20;
	surfaceY = 60;	
}

void ScoreWindow::setup()
{
	dialogBox.SetFont(resc.getFontVera());
	dialogBox.SetMargin(15);
	forceRefresh();
	dialogBox.ReCreate(GraphicDriver::getScreen()); // must be done once
}

void ScoreWindow::forceRefresh() {
	snprintf(text_, 16, "Score: %7u", GameEngine::getScore());
	dialogBox.RemoveLine(0);
	dialogBox.AddLine(text_);
	dialogBox.ReCreate(GraphicDriver::getScreen());	
}

void ScoreWindow::refresh()
{
	int newScore = GameEngine::getScore();
	if ( score != newScore ) {
		score = newScore;
		forceRefresh();
	}
}

void ScoreWindow::blitTo(SDL_Surface *screen) {
	refresh();
	dialogBox.Draw(screen, surfaceX, surfaceY);
}

