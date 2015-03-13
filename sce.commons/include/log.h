#ifndef __log_h__
#define __log_h__

#include <stdlib.h>
#include <stdio.h>

/*
 * How this works:
 * Use setDebuglevel to tell Debug what messages to let through, and thus
 * what to discard.
 *
 * However, one might want to lett every INFO message from one (new) class
 * go through, and only ERROR messages from the other (stable) classes through.
 * Just set that class' PRIODEBUG member to Debug::PRIOINFO, and Debug
 * will let everything from that class that's at least INFO through, eventhough
 * its global setting is to let only ERROR messages.
 *
 */


class LOG
{
	public:
		enum LOGLEVEL { // Choose what messages are logged/discarded
			NONE,			// Do not actually let messages through
			ERROR,		// This is the default, only let errors through
			WARNING,		// Warnings get logged too
			INFO,			// Normal info like something happening is logged
			VERBOSE,		// Details of programflow/execution is logged
			DEBUG			// Embarrisingly much (redundant) info
		};

	private:
		static enum LOGLEVEL loglevel_;
		static const char* logname_[6];
		static FILE *logfile_;
		static const int FLUSHINTERVAL;
		static unsigned int writes_;
		static const unsigned int MAXWRITES;

	public:
		static const LOGLEVEL DEFAULTLL;
		LOG(void);

		static void Log(char* message, enum LOGLEVEL ll, enum LOGLEVEL wantll);

		static int  setLogfile(char* filename);
		static void closeLogfile(void);
		static void setLoglevel(enum LOGLEVEL);
		static int  getLoglevel(void);
};


#endif /* __log_h__ */
