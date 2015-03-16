#include "log.h"

// initialize static members:
enum LOG::LOGLEVEL LOG::loglevel_ = LOG::DEBUG;
const char* LOG::logname_[6] =
	{ "   NONE", "  ERROR", "WARNING", "   INFO", "VERBOSE", "  DEBUG" };

const enum LOG::LOGLEVEL LOG::DEFAULTLL = LOG::NONE; // means class LOG
																		// will decide
unsigned int const LOG::MAXWRITES = 1000;
FILE* LOG::logfile_ = NULL; // when NULL: log is sent to the terminal
const int LOG::FLUSHINTERVAL = 1; // how many messages are passed to
		// LOG before it flushes it to the logfile (1 only for debug)
unsigned int LOG::writes_ = 0;
// -------------------


LOG::LOG(void)
{ /* hmm.. */ }

int LOG::setLogfile(char* filename)
{
	// should add check to see if it's already using this file..

	if ( logfile_ != NULL )
		fclose(logfile_);

	if ( filename == NULL )
		return 0; // don't open any new file, use terminal. 0 means success


	//logfile_ = fopen(filename, "a");
	logfile_ = fopen(filename, "w");

	if ( logfile_ != NULL )
	{
		fputs("\nLogging turned on.\n", logfile_);
		return 0; // success
	}

	return 1; // ERROR
}

void LOG::closeLogfile(void)
{
	if ( logfile_ != NULL )
	{
		fputs("Logging turned off.\n", logfile_);
		fclose(logfile_);
		logfile_ = NULL;
		writes_ = 0;
	}
}

void LOG::Log(char* message, enum LOGLEVEL ll,
						 			  enum LOGLEVEL wantll)
{
	if ( loglevel_ == NONE && logfile_ == NULL )
		return; // well, there you go

	//return; // <--- We're trying this to fix a bug
	// decide if message is going to be logged, or discarded
	if ( ll <= loglevel_ || ll <= wantll )
	{
		static int timetoflush = FLUSHINTERVAL; // decide when to flush
		//static char *string = new char[256]; // why not static? it's often used
		char *string = new char[256]; // why not static? it's often used
		snprintf(string, 256, "%s: %s\n", LOG::logname_[ll], message);

		if ( logfile_ != NULL )	 // is there a logfile opened?
		{
			if ( writes_++ > MAXWRITES )
			{
				fputs("Excessive logging: ", logfile_);
				closeLogfile();
				return;
			}

			fputs(string, logfile_);
			if ( --timetoflush == 0 )
			{
				fflush(logfile_);
				timetoflush = FLUSHINTERVAL;
			}

		}
		//else
		//{
			// during development the terminal is used for graphics
			// so this is turned off to prevent the terminal from 
			// getting messed up
			//printf(string); // no logfile, ouput to terminal then
		//}
		delete string;
	}

	// if not: it's just discarded, not dealt with
	// Note: the lowest priority is counted here, doesn't matter if it's
	// decided in class LOG (ll) or in the calling class (wantll).
}

void LOG::setLoglevel(enum LOGLEVEL ll)
{
	loglevel_ = ll;
}

int LOG::getLoglevel(void)
{
	return loglevel_;
}
