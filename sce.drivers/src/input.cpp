#include "input.h"

enum Input::USERACTION Input::getAction(bool wait)
{
	SDL_Event event;
	USERACTION lastvalue = NOTHING;

  while (!wait && SDL_PollEvent(&event) or wait && SDL_WaitEvent(&event))
	{
		switch (event.type)
		{
      case SDL_WINDOWEVENT:
        //printf(" SDL_WINDOWEVENT\n");
        break;

      case SDL_MOUSEMOTION:
        //printf(" SDL_MOUSEMOTION\n");
        break;

      case SDL_MOUSEBUTTONDOWN:
        printf(" SDL_MOUSEBUTTONDOWN\n");
        break;

      case SDL_MOUSEBUTTONUP:
        printf(" SDL_MOUSEBUTTONUP\n");
        break;

      case SDL_MOUSEWHEEL:
        printf(" SDL_MOUSEWHEEL\n");
        break;

			case SDL_TEXTEDITING:
        printf(" SDL_TEXTEDITING\n");
        break;

      case SDL_TEXTINPUT:
        if (event.text.text)
          printf(" SDL_TEXTINPUT: \"%s\"\n", event.text.text);
        break;

			case SDL_KEYUP:
        printf(" SDL_KEYUP\n");
        break;

			case SDL_KEYDOWN:
        printf(" SDL_KEYDOWN\n");

				switch (event.key.keysym.sym)
				{
					case SDLK_UP:    lastvalue = GOUP;
						break;
					case SDLK_DOWN:	 lastvalue = GODOWN;
						break;
					case SDLK_LEFT:	 lastvalue = GOLEFT;
						break;
					case SDLK_RIGHT: lastvalue = GORIGHT;
						break;

					case SDLK_PAUSE:
            lastvalue = PAUSE;
						break;

				// case SDLK_RETURN:
					case SDLK_ESCAPE:
					case SDLK_q:
            // short circut exit:
						return EXITSTATE;

					default:
						break;
				};
				break; // loop the while

			case SDL_QUIT:
        printf(" SDL_QUIT\n");
				return SHUTDOWN; // recieved kill signal

			default:
        printf(" UNKNOWN\n");
				break; // loop the while
		};

    // Don't loop if we waited for this event.
    if (wait && lastvalue)
      break;
	};

	// Only return the last value,
  // everything else gets ignored (unless it's a quit action).
	return lastvalue;
}

