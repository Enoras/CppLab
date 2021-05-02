#include "include/SDL.h"
#include <stdio.h>
#include <string.h>
#include <random>
#include <ctime>

//Screen dimension constants
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

const int NUM_REC = 8;
const int SIZE_REC = 40;
const int NUM_COLOR = 6;


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* color[NUM_COLOR+1];
int field[NUM_REC][NUM_REC];

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "Match3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	for (int i = 1; i <= NUM_COLOR; i++) {
		char s[20];
		const char *ex = ".bmp";
		SDL_itoa(i, s, 10);
		strcat(s, ex);
		

		color[i-1] = SDL_LoadBMP(s);

		if (color[i-1] == NULL)
		{
			printf("Unable to load image %s! SDL Error: %s\n", "03_event_driven_programming", SDL_GetError());
			success = false;
		}
		color[NUM_COLOR] = SDL_LoadBMP("0.bmp");
	}

	return success;
}

void filling_color() {
	srand(time(0));
	for (int i = 0; i < NUM_REC; i++) {
		for (int j = 0; j < NUM_REC; j++) {
			field[i][j] = rand() % NUM_COLOR;
			if (field[i][j-1] == field[i][j])
				field[i][j] = rand() % NUM_COLOR;
			if (field[i-1][j] == field[i][j])
				field[i][j] = rand() % NUM_COLOR;
		}
	}
}

void show_image() {

	SDL_Rect r;
	r.w = SIZE_REC-2;
	r.h = SIZE_REC-2;
	r.x = 0;
	r.y = 0;

	SDL_Rect p;
	p.x = 0;
	p.y = 0;

	for (int i = 0; i < NUM_REC; i++) {
		for (int j = 0; j < NUM_REC; j++) {
			SDL_BlitSurface(color[field[i][j]], &r, gScreenSurface, &p);
			p.x += SIZE_REC;
		}
		p.x = 0;
		p.y += SIZE_REC;
	}

	//Update the surface
	SDL_UpdateWindowSurface(gWindow);
}

void swap_rec(int *x, int *y) {

	int i0 = x[0] / SIZE_REC;
	int j0 = y[0] / SIZE_REC;
	int i1 = x[1] / SIZE_REC;
	int j1 = y[1] / SIZE_REC;

	if (((i0 - i1 == 0) && (abs(j0 - j1) == 1)) || ((j0 - j1 == 0) && (abs(i0 - i1) == 1))) {

		int h = field[j0][i0];
		field[j0][i0] = field[j1][i1];
		field[j1][i1] = h;
	}

}

void search_re(int c ,int i,int j, int* k, int way[NUM_REC][NUM_REC]) {
	if (i >= NUM_REC || j >= NUM_REC || i<0 || j<0)
		return;
	if (way[i][j] == 1) return;

	if (field[i][j] == c) {
		(*k)++;
		way[i][j] = 1;
		search_re(c, i + 1, j, k, way);
		search_re(c, i, j + 1, k, way);
		search_re(c, i - 1, j, k, way);
		search_re(c, i, j - 1, k, way);
	}
}


void del(int i, int j, int way[NUM_REC][NUM_REC]) {
	if (i >= NUM_REC || j >= NUM_REC || i < 0 || j < 0)
		return;

	if (way[i][j] == 1) {
		way[i][j] = 0;
		field[i][j] = NUM_COLOR;
		del(i + 1, j, way);
		del(i, j + 1, way);
		del(i - 1, j, way);
		del(i, j - 1, way);
		
	}
}

//void clear_way(int way[NUM_REC][NUM_REC]) {
//	for (int i = 0; i < NUM_REC; i++) {
//		for (int j = 0; j < NUM_REC; j++) {
//			way[i][j] = 0;
//
//		}
//	}
//}

int delete_re() {
	int num_elem = 0;

	for (int i = 0; i < NUM_REC; i++) {
		for (int j = 0; j < NUM_REC; j++) {
			if (field[i][j] != NUM_COLOR) {
				int k = 0;
				int check_way[NUM_REC][NUM_REC] = { 0 };
				search_re(field[i][j], i, j, &k, check_way);
				if (k >= 3) {
					del(i, j, check_way);
					num_elem++;
				}
			}
			
		}
	}
	return num_elem;
}

int search_empty_rec() {
	for (int i = 0; i < NUM_REC; i++) {
		for (int j = 0; j < NUM_REC; j++) {
			if (field[i][j] == NUM_COLOR) return 1;
		}
	}

	return 0;
}


void filling_empty_rec() {

	while (search_empty_rec()) {
		
		for (int j = 0; j < NUM_REC; j++) {
			for (int i = NUM_REC - 1; i >= 0; i--) {

				if (field[i][j] == NUM_COLOR) {
					if (i == 0) field[i][j] = rand() % NUM_COLOR;

					else {
						int h = field[i][j];
						field[i][j] = field[i - 1][j];
						field[i - 1][j] = h;
					}
				}
			}
		}

		SDL_Delay(200);
		show_image();
				
	}

}

void processing() {

	while (delete_re() != 0) {
		filling_empty_rec();
	}

}

void close()
{
	//Deallocate surface
	for (int i = 1; i <= NUM_COLOR; i++) {
		SDL_FreeSurface(color[i-1]);
	}

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{

	SCREEN_HEIGHT = SIZE_REC * NUM_REC;
	SCREEN_WIDTH = SIZE_REC * NUM_REC;
	
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{		

			filling_color();
			processing();
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;
	
			int x[2], y[2];
			int k = 0;

			//While application is running
			while( !quit )
			{

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}


					if( e.type == SDL_MOUSEBUTTONDOWN)
					{
						SDL_GetMouseState(&x[k], &y[k]);
						k++;
						if (k == 2) {
							swap_rec(x, y);
							SDL_Delay(200);
							processing();
							k = 0;
						}
						
					}
				}


				//Apply the image
    			show_image();

				
			}
		}
	}
	//Free resources and close SDL
	close();

	return 0;
}