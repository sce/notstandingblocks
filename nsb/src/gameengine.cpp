#include "gameengine.h"


// initialize static members:
//const unsigned int GameEngine::INITIALFALLINTERVAL = 500;
const unsigned int GameEngine::INITIALFALLINTERVAL = 200;
LOG::LOGLEVEL GameEngine::wantloglevel_ = LOG::DEFAULTLL;
const int GameEngine::DEAD = -1;
Block *GameEngine::nextBlock_ = NULL;
unsigned int GameEngine::score_ = 0;
// ---

GameEngine::GameEngine(void) 
{ 
	actBlock_ = NULL;
	prevBlock_ = NULL;
					
	dx_ = 0; // standard FIXME
	dy_ = 0; // standard // hmm...

	movesSinceLastCrash_ = 0;
	nextFallUpdate_ = 0;
	fallInterval_ = INITIALFALLINTERVAL;
	wait_ = true;
	nextRowDeleteUpdate_ = 0;
	nextPrevBlockUpdate_ = 0;
	
	fallNow = false;
	
	for ( int i=0; i<GameResc::MAPY; i++ )
		deleteRow[i] = false;
}

void GameEngine::setLoglevel(LOG::LOGLEVEL loglevel)
{
	wantloglevel_ = loglevel;
}

GameEngine::~GameEngine(void)
{
	cleanup();
}

void GameEngine::cleanup(void)
{
	if (actBlock_) delete actBlock_;
	if (nextBlock_) delete nextBlock_;
	if (prevBlock_) delete prevBlock_;
}

void GameEngine::setdx(int dx)
{
	dx_ = dx;
}

void GameEngine::setdy(int dy)
{
	dy_ = dy;
}

int GameEngine::getdy(void)
{
	return dy_;
}

int GameEngine::getdx(void)
{
	return dx_;
} 

Block *GameEngine::getNextBlock(void)
{
	return nextBlock_;
}

unsigned int GameEngine::getScore(void)
{
	return score_;
}

void GameEngine::actBlockFallNow() {
	fallNow = true;
}

void GameEngine::startNew(void)
{
	LOG::Log("+ GameEngine::startNew(void)", LOG::VERBOSE, wantloglevel_);

	movesSinceLastCrash_ = 0;
	nextFallUpdate_ = 0;
	fallInterval_ = INITIALFALLINTERVAL;
	score_ = 0;
	 
	if ( prevBlock_ == NULL ) prevBlock_ = new Block();

	if ( actBlock_ == NULL ) 
		actBlock_ = new Block();
	else 
		actBlock_->createRandomBlock();

	if ( nextBlock_ == NULL ) 
		nextBlock_ = new Block();
	else
		nextBlock_->createRandomBlock();
	
	// clear/fix map
	Map::startNew();

	// reset speed/movement
	dx_ = 0; // standard FIXME
	dy_  = 1; // standard
	
	LOG::Log("- GameEngine::startNew(void)", LOG::VERBOSE, wantloglevel_);
}


void GameEngine::putPrevBlockPermOnMap(void)
{
	putBlockOnMap(prevBlock_, prevBlock_->getBlocktype()+1);
}

void GameEngine::putActBlockPermOnMap(void)
{
	//putActBlockOnMap(-1); // blocktype starts at 0
	// using -1 will confuse markFullRows
	
	putActBlockOnMap(Block::BLOCKTYPES+1); // use highest unused value for index

	if ( nextPrevBlockUpdate_ != 0 )
		putPrevBlockPermOnMap();

	nextPrevBlockUpdate_ = SDL_GetTicks()+INITIALFALLINTERVAL/2;

	// copy data
	prevBlock_->copyFrom(actBlock_);
	actBlock_->copyFrom(nextBlock_);
	nextBlock_->createRandomBlock();

}

void GameEngine::putActBlockOnMap(void)
{
	putActBlockOnMap(actBlock_->getBlocktype()+1); // blocktype starts at 0
}

void GameEngine::putBlockOnMap(Block* block, int value)
{
	Map::putBlockOnMap(block, value);
}


void GameEngine::putActBlockOnMap(int value)
{
	putBlockOnMap(actBlock_, value);
}

void GameEngine::removeActBlockFromMap(void)
{
	Map::removeBlockFromMap(actBlock_);	
}

int GameEngine::markFullRows(void)
{
	int fullRows = 0;
	int occupied = 0;
	char *string = new char[256];

	for (int y=0; y<Map::MAPY; y++)
	{
		occupied = 0;
		
		// Check if it's already marked for deletion:
		if ( deleteRow[y] == false )
		{
			// Count squares:
			for (int x=0; x<Map::MAPX; x++)
				if ( Map::getXY(x,y) != Map::EMPTY )
					occupied++;

			// Check if it's full:
			if ( occupied == Map::MAPX )
			{
				snprintf(string, 256, 
						"* GameEngine::removeFullRows(): Row %i full!", y);
				LOG::Log(string, LOG::INFO, wantloglevel_);

				// Mark it:
				Map::markFullRow(y);
				deleteRow[y] = true;

				fullRows++; // needed?
				nextRowDeleteUpdate_ = SDL_GetTicks()+INITIALFALLINTERVAL/2;
			}
		}
	}

	delete string;
	return fullRows;
}

int GameEngine::removeMarkedRows(void)
{
	int removedRows = 0;

	for (int y=0; y<Map::MAPY; y++)
	{
		// Check if it's marked for deletion:
		if ( deleteRow[y] == true )
		{
			if ( !wait_ ) removeActBlockFromMap();
			// Remove it:
			Map::removeRow(y);
			deleteRow[y] = false;

			//rowsMarked_ = false;
			nextRowDeleteUpdate_ = 0;
			removedRows++; // needed?
			
			if ( !wait_ ) putActBlockOnMap();
		}

	}
	score_ += (removedRows*10)*(removedRows*10);
	return removedRows;
}

void GameEngine::rotateBlock(void) 
{	
	Block *newBlock = new Block();
	newBlock->copyFrom(actBlock_);
	newBlock->rotateCW();
	
	removeActBlockFromMap(); // Mustn't collide with itself

	if ( !Map::doesCollide(newBlock) ) {
		delete actBlock_;
		actBlock_ = newBlock;
	} else {
		delete newBlock;
	}
	
	putActBlockOnMap();
	return;
}

int GameEngine::doOneFrame(void)
{
	LOG::Log("", LOG::VERBOSE, wantloglevel_);
	LOG::Log("+ GameEngine::doOneFrame(void)", LOG::VERBOSE, wantloglevel_);

	unsigned int now = SDL_GetTicks();
	int rows = 0; // the return value

	if ( wait_ == true )
	{
		if ( now > nextFallUpdate_ )
		{
			nextFallUpdate_ = now+fallInterval_;
			wait_ = false;
		}
		else
		{
			if ( nextPrevBlockUpdate_ != 0 && nextPrevBlockUpdate_ < now )
			{
				putPrevBlockPermOnMap();
				nextPrevBlockUpdate_ = 0;
			}

			if ( nextRowDeleteUpdate_ != 0 && nextRowDeleteUpdate_ < now )
			{
				rows += removeMarkedRows();
				if ( rows == 0 ) 
					rows = -2; // meaning: new block on the way
			}
			return rows;
		}
	}
	
	Block *newBlock = new Block();
	newBlock->copyFrom(actBlock_);

	removeActBlockFromMap(); // We don't want it colliding with itself.
	bool putBlockBackOnMap = true;
		
	// First check if it's falling:
	if ( now >= nextFallUpdate_ || fallNow ) {
		// Try to move both in x/y directions:
		newBlock->move(dx_,dy_);
		if ( !Map::doesCollide(newBlock) ) 
		{
			delete actBlock_;
			actBlock_ = newBlock;
			newBlock = NULL;
			movesSinceLastCrash_++;
			if ( fallNow )
				fallNow = false;
			else
				nextFallUpdate_ = now+fallInterval_;
		} 
		else 
		{ // That didn't go well, try just falling:
			newBlock->move(-dx_,0); // move back in x-direction
			if ( !Map::doesCollide(newBlock) ) {
				delete actBlock_;
				actBlock_ = newBlock;
				newBlock = NULL;
				movesSinceLastCrash_++;
				if ( fallNow )
					fallNow = false;
				else
					nextFallUpdate_ = now+fallInterval_;
			} 
			else 
			{ // Can't move in either direction: place it where it is:
				putActBlockPermOnMap();
				rows = markFullRows();
				if ( rows == 0 )
					rows = -2; // meaning: new block on the way
				else
					rows = 0; // hmm.. a better way to solve this?

				if ( movesSinceLastCrash_ == 0 ) // uhh oh
					rows = DEAD; // game over
				else // successful crash
					movesSinceLastCrash_ = 0;

				wait_ = true;
				
				putBlockBackOnMap = false;
				nextFallUpdate_ = now+fallInterval_;
				delete newBlock;
				newBlock = NULL;
			}
		} 
	}
	else if ( dx_ != 0 )
	{ // It's not time to fall, just try x-direction:
		newBlock->move(dx_,0);
		if ( !Map::doesCollide(newBlock) ) {
			delete actBlock_;
			actBlock_ = newBlock;
			newBlock = NULL;
		} 
		else
			delete newBlock;
		// If it can't move, don't move it.
	}

	// Done with the moving bit :)

	if ( putBlockBackOnMap )	
		putActBlockOnMap();

	if ( nextRowDeleteUpdate_ != 0 && nextRowDeleteUpdate_ < now )
	{
		if ( rows != DEAD )
		{
			rows += removeMarkedRows();
			//if ( rows == 0 ) 
				//rows = -2; // meaning: new block on the way
		}
	}

	// reset to standard
	dx_ = 0; // standard FIXME
	dy_ = 1; // standard

	LOG::Log("- GameEngine::doOneFrame(void)", LOG::VERBOSE, wantloglevel_);
	return rows; 
}

