
#include "test1.h"

// - setup display
// - wait a few seconds
// - reset display
int testSetupScreen() {
  cout << "testSetupScreen: Going to change the resolution to 640x480 for 10 seconds, please wait ... ";
  flush(cout);

  GraphicDriver gd;
  gd.setupScreen(640, 480, 0, SDL_WINDOW_FULLSCREEN);

  sleep(10);
  SDL_Quit();

  cout << "done." << endl;

  return 0;
}

// - setup display
// - load picture
// - reset display
int testPicture() {
  cout << "testPicture: Going to change the resolution to 640x480 and load an image for 10 seconds, please wait ... " << endl;

  GraphicDriver gd;
  gd.setupScreen(640, 480, 0, SDL_WINDOW_FULLSCREEN);

  SDL_Texture *image = gd.loadImage("../../nsb/resources/pics/background1.png");

  if (image) {
    gd.blitToMain(image, 0, 0);
    gd.flip();
  }

  sleep(10);
  SDL_Quit();

  cout << "Done." << endl;

  return 0;
}

// - bring up window
// - run input fetch loop
// - quit on user request
int testInput() {
  cout << "testInput." << endl;

  GraphicDriver gd;
  gd.setupScreen(640, 480, 0, SDL_WINDOW_FULLSCREEN);

  int action;
  do {
    action = Input::getAction(true);
  } while(action != Input::SHUTDOWN and action != Input::EXITSTATE);

  SDL_Quit();
  cout << "Done." << endl;

  return 0;
}

void testBlitBlitting(void *args[]) {
  GraphicDriver *gd = (GraphicDriver*) args[0];
  SDL_Texture **images = (SDL_Texture**) args[1];

  if(!gd || !images) return;

  SDL_Texture *background = images[0];
  SDL_Texture *img1 = images[1];
  SDL_Texture *img2 = images[2];
  SDL_Texture *img3 = images[3];

  if (background)
    gd->blitToMain(background, 0, 0);

  if (img1)
    gd->blitToMain(img1, 100, 100);

  if (img2)
    gd->blitToMain(img2, 200, 200);

  if (img3) {
    gd->blitToMain(img3, 300, 300);
    gd->blitToMain(img3, 400, 300);
    gd->blitToMain(img3, 500, 300);
  }

  gd->flip();
}

void inputLoop(void (*f)(void *args[]), void *args[]) {
  int action;
  do {
    if (f) { (*f)(args); };
    action = Input::getAction(false);
  } while(action != Input::SHUTDOWN and action != Input::EXITSTATE);
}

// - bring up window
// - run input fetch loop
// - quit on user request
int testBlit() {
  cout << "testBlit." << endl;

  GraphicDriver gd;
  gd.setupScreen(640, 480, 0, SDL_WINDOW_FULLSCREEN);

  SDL_Texture *background = gd.loadImage("../../nsb/resources/pics/background1.png");
  SDL_Texture *img1 = gd.loadImage("../../nsb/resources/pics/round1a2.png");
  SDL_Texture *img2 = gd.loadImage("../../nsb/resources/pics/round2a.png");
  SDL_Texture *img3 = gd.loadImage("../../nsb/resources/pics/round3a.png");

  SDL_Texture *images[4] = { background, img1, img2, img3 };
  void *args[2] = { &gd, &images };

  //inputLoop(NULL, NULL);
  inputLoop(&testBlitBlitting, args);

  SDL_DestroyTexture(background);
  SDL_DestroyTexture(img1);
  SDL_DestroyTexture(img2);
  SDL_DestroyTexture(img3);

  cout << "Done." << endl;

  return 0;
}

int printHelp() {
  cout << "Run with one of the following arguments:" << endl
    << "  setup-screen" << endl
    << "  picture" << endl
    << "  input" << endl
    << "  blit" << endl;

  return 0;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printHelp();

  } else {
    char* arg = argv[1];

    if (strcmp(arg, "setup-screen") == 0)
      return testSetupScreen();
    else if (strcmp(arg, "picture") == 0)
      return testPicture();
    else if (strcmp(arg, "input") == 0)
      return testInput();
    else if (strcmp(arg, "blit") == 0)
      return testBlit();
    else
      return printHelp();
  }
}
