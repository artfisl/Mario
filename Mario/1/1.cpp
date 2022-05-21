#pragma comment(lib, "SDL2_mixer.lib")
#include "SDL.h"
#include "stdlib.h"
#include <cstdio>
#include <locale>
#include <iostream>
#include <SDL_image.h>
#include "SDL_mixer.h"

using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

Mix_Chunk* Sound = NULL;
Mix_Music* fon = NULL;



void DrawMap(SDL_Renderer*& renderer, SDL_Rect wall, SDL_Texture* image) {

	SDL_RenderCopy(renderer, image, nullptr, &wall);
	SDL_RenderPresent(renderer);
}

void loadmusic()
{

	fon = Mix_LoadMUS("overworld.wav");
	Mix_PlayMusic(fon, -1);
}

void sound()
{
	Sound = Mix_LoadWAV("coin.wav");
	Mix_PlayChannel(-1, Sound, 0);
}
void death()
{
	Sound = Mix_LoadWAV("death.wav");
	Mix_PlayChannel(-1, Sound, 0);
}

int Sravnenie(SDL_Rect r1, SDL_Rect mario) {

	if (mario.x > r1.x + r1.w || mario.x + mario.w < r1.x || mario.y > r1.y + r1.h || mario.y + mario.h < r1.y) return 0;

	return 1;
}

void win(SDL_Renderer* renderer,int n)
{
	SDL_Rect win = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_Texture* image5 = IMG_LoadTexture(renderer, "win.bmp");
	SDL_Texture* image0 = IMG_LoadTexture(renderer, "win1.bmp");
	if (n == 3)
	{
		SDL_RenderCopy(renderer, image0, nullptr, &win);
		//quit = true;

	}
	else
		SDL_RenderCopy(renderer, image5, nullptr, &win);
	SDL_RenderPresent(renderer);
	SDL_Delay(3000);
}

void not_win(SDL_Renderer* renderer) {
	SDL_Rect notWin = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_Texture* image5 = IMG_LoadTexture(renderer, "not_win.bmp");
	SDL_RenderCopy(renderer, image5, nullptr, &notWin);
	SDL_RenderPresent(renderer);
	death();
	SDL_Delay(3000);
}


int main(int argc, char** argv)
{
	setlocale(0, "");
	srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow(u8"Марио",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Surface* surface = NULL;

	Mix_Init(0);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);


	int n=1;

	SDL_Event event;
	bool quit = false;
	loadmusic();
	int life = 1, life1 = 1, cnt = 0;
	SDL_Rect wall[8],wall1[8],wall2[8];
	SDL_Texture* image = IMG_LoadTexture(renderer, "gnd_red_1.bmp");
	SDL_Surface* back = IMG_Load("back.bmp");
	SDL_Texture* Back = SDL_CreateTextureFromSurface(renderer, back);
	SDL_FreeSurface(back);
	int x = 700, y = 501, dmove = 10;
	SDL_Rect mario = { x,y,40,40 };
	SDL_Surface* image2= IMG_Load("mario.bmp");
	SDL_SetColorKey(image2, SDL_TRUE, SDL_MapRGB(image2->format, 255, 255, 255));
	SDL_Texture* Texture2 = SDL_CreateTextureFromSurface(renderer, image2);
	SDL_FreeSurface(image2);

	wall[0] = { 0,0,50,SCREEN_HEIGHT }; 
	wall[1] = { 0,0,SCREEN_WIDTH,50 }; 
	wall[2] = { SCREEN_WIDTH - 50,0,50,SCREEN_HEIGHT }; 
	wall[3] = { 0,550,SCREEN_WIDTH,50 }; 
	wall[4] = { 40,245,SCREEN_WIDTH / 3,50 }; 
	wall[5] = { 535,450,SCREEN_WIDTH / 3,50 }; 
	wall[6] = { 580,250,SCREEN_WIDTH / 3,50 }; 
	wall[7] = { 0,450,SCREEN_WIDTH / 3,50 }; 

	wall1[0] = { 0,0,50,SCREEN_HEIGHT };
	wall1[1] = { 0,0,SCREEN_WIDTH,50 }; 
	wall1[2] = { SCREEN_WIDTH - 50,0,50,SCREEN_HEIGHT }; 
	wall1[3] = { 0,550,SCREEN_WIDTH,50 }; 
	wall1[4] = { 280,110,SCREEN_WIDTH / 3,50 }; 
	wall1[5] = { 400,450,SCREEN_WIDTH / 3,50 }; 
	wall1[6] = { 580,250,SCREEN_WIDTH / 3,50 }; 
	wall1[7] = { 0,350,SCREEN_WIDTH / 3,50 }; 

	wall2[0] = { 0,0,50,SCREEN_HEIGHT }; 
	wall2[1] = { 0,0,SCREEN_WIDTH,50 }; 
	wall2[2] = { SCREEN_WIDTH - 50,0,50,SCREEN_HEIGHT }; 
	wall2[3] = { 0,550,SCREEN_WIDTH,50 }; 
	wall2[4] = { 0,180,SCREEN_WIDTH / 3,50 }; 
	wall2[5] = { 280,500,SCREEN_WIDTH / 3,50 }; 
	wall2[6] = { 280,330,SCREEN_WIDTH / 3,50 }; 
	wall2[7] = { 500,180,SCREEN_WIDTH / 3,50 }; 

	SDL_Rect bonus[9],bonus1[9],bonus2[9];
	SDL_Surface* image3 = IMG_Load("coin_use20.bmp");
	SDL_SetColorKey(image3, SDL_TRUE, SDL_MapRGB(image3->format, 255, 0, 255));
	SDL_Texture* Texture3 = SDL_CreateTextureFromSurface(renderer, image3);
	SDL_FreeSurface(image3);

	int wB = 20;
	int wH = 20;
	int k = 0;
	bonus[0] = { 55, 530, wB, wH };
	bonus[1] = { 340, 320, wB, wH};
	bonus[2] = { 70, 430, wB, wH };
	bonus[3] = { 730, 425, wB, wH };
	bonus[4] = { 630, 425, wB, wH };
	bonus[5] = { 80, 70, wB, wH };
	bonus[6] = { 560, 220, wB, wH };
	bonus[7] = { 720, 200, wB, wH };
	bonus[8] = { 250, 200, wB, wH };

	bonus1[0] = { 100, 530, wB, wH };
	bonus1[1] = { 50, 440, wB, wH };
	bonus1[2] = { 500, 67, wB, wH };
	bonus1[3] = { 500, 420, wB, wH };
	bonus1[4] = { 420, 270, wB, wH };
	bonus1[5] = { 275, 80, wB, wH };
	bonus1[6] = { 650, 75, wB, wH };
	bonus1[7] = { 100, 300, wB, wH };
	bonus1[8] = { 600, 220, wB, wH };

	bonus2[0] = { 290, 470, wB, wH };
	bonus2[1] = { 510, 470, wB, wH };
	bonus2[2] = { 80, 520, wB, wH };
	bonus2[3] = { 300, 300, wB, wH };
	bonus2[4] = { 500, 300, wB, wH };
	bonus2[5] = { 80, 150, wB, wH };
	bonus2[6] = { 650, 150, wB, wH };
	bonus2[7] = { 720, 250, wB, wH };
	bonus2[8] = { 400, 220, wB, wH };


	SDL_Rect enemy[2] = { 100,520,30,30, 200,220,30,30 };
	SDL_Rect enemy1[3] = { 100,520,30,30, 450,75,30,30, 650,220,30,30 };
	SDL_Rect enemy2[4]= { 100,150,30,30, 400,300,30,30, 650,150,30,30, 400,467,30,30 };
	SDL_Surface* image4 = IMG_Load("goombas_0.bmp");
	SDL_SetColorKey(image4, SDL_TRUE, SDL_MapRGB(image4->format, 255, 0, 255));
	SDL_Texture* Texture4 = SDL_CreateTextureFromSurface(renderer, image4);

	SDL_Surface* squid = IMG_Load("squid0.bmp");
	SDL_SetColorKey(squid, SDL_TRUE, SDL_MapRGB(squid->format, 255, 0, 255));
	SDL_Texture* Squid = SDL_CreateTextureFromSurface(renderer, squid);

	SDL_Surface* lvl1 = IMG_Load("lvl1.bmp");
	SDL_SetColorKey(lvl1, SDL_TRUE, SDL_MapRGB(lvl1->format, 0, 0, 0));
	SDL_Texture* LVL1 = SDL_CreateTextureFromSurface(renderer, lvl1);
	SDL_Surface* lvl2 = IMG_Load("lvl2.bmp");
	SDL_SetColorKey(lvl2, SDL_TRUE, SDL_MapRGB(lvl2->format, 0, 0, 0));
	SDL_Texture* LVL2 = SDL_CreateTextureFromSurface(renderer, lvl2);
	SDL_Surface* lvl3 = IMG_Load("lvl3.bmp");
	SDL_SetColorKey(lvl3, SDL_TRUE, SDL_MapRGB(lvl3->format, 0, 0, 0));
	SDL_Texture* LVL3= SDL_CreateTextureFromSurface(renderer, lvl3);
	SDL_FreeSurface(lvl1);
	SDL_FreeSurface(lvl2);
	SDL_FreeSurface(lvl3);
	SDL_Rect lvl[3]={100,500,50,50,300,500,50,50,500,500,50,50};
	
	
	int ch_enemy = 0;
	bool p = false;
	bool o = false;
	bool o1 = false;
	bool o2 = false;
	bool o3 = false;
	
	while (life1 != 0)
	{
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				quit = true;
			int x1 = 0, y1 = 0;
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_UP))
			{
				y1 -= dmove-3;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_DOWN))
			{
				y1 += dmove+3;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_LEFT))
			{
				x1 -= dmove;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RIGHT))
			{
				x1 += dmove;
			}
			if (n == 1)
			{
				if (!o)
					if (enemy[0].x < 720)
					{
						enemy[0].x += 5;
						if (enemy[0].x >= 710)
							o = true;

					}
				if (o)
					if (enemy[0].x > 50)
					{
						enemy[0].x -= 5;
						if (enemy[0].x <= 50)
							o = false;
					}

				if (!o1)
					if (enemy[1].x < 250)
					{
						enemy[1].x += 5;
						if (enemy[1].x >= 250)
							o1 = true;
					}
				if (o1)
					if (enemy[1].x > 50)
					{
						enemy[1].x -= 5;
						if (enemy[1].x <= 50)
							o1 = false;
					}
			}
			if (n == 2)
			{
				
				if (!o)
					if (enemy1[0].x < 720)
					{
						enemy1[0].x += 5;
						if (enemy1[0].x >= 710)
							o = true;

					}
				if (o)
					if (enemy1[0].x > 50)
					{
						enemy1[0].x -= 5;
						if (enemy1[0].x <= 50)
							o = false;
					}

				if (!o1)
					if (enemy1[1].x < 530)
					{
						enemy1[1].x += 5;
						if (enemy1[1].x >= 530)
							o1 = true;
					}
				if (o1)
					if (enemy1[1].x > 270)
					{
						enemy1[1].x -= 5;
						if (enemy1[1].x <= 270)
							o1 = false;
					}
				if (!o2)
					if (enemy1[2].x < 725)
					{
						enemy1[2].x += 5;
						if (enemy1[2].x >= 725)
							o2 = true;
					}
				if (o2)
					if (enemy1[2].x > 580)
					{
						enemy1[2].x -= 5;
						if (enemy1[2].x <= 580)
							o2 = false;
					}
			}
			if (n == 3)
			{
				if (!o)
					if (enemy2[0].x < 260)
					{
						enemy2[0].x += 5;
						if (enemy2[0].x >= 260)
							o = true;

					}
				if (o)
					if (enemy2[0].x > 50)
					{
						enemy2[0].x -= 5;
						if (enemy2[0].x <= 50)
							o = false;
					}

				if (!o1)
					if (enemy2[1].x < 550)
					{
						enemy2[1].x += 5;
						if (enemy2[1].x >= 550)
							o1 = true;
					}
				if (o1)
					if (enemy2[1].x > 270)
					{
						enemy2[1].x -= 5;
						if (enemy2[1].x <= 270)
							o1 = false;
					}
				if (!o2)
					if (enemy2[2].x < 725)
					{
						enemy2[2].x += 5;
						if (enemy2[2].x >= 725)
							o2 = true;
					}
				if (o2)
					if (enemy2[2].x > 500)
					{
						enemy2[2].x -= 5;
						if (enemy2[2].x <= 500)
							o2 = false;
					}
				if (!o3)
					if (enemy2[3].x < 725)
					{
						enemy2[3].x += 5;
						if (enemy2[3].x >= 725)
							o3 = true;
					}
				if (o3)
					if (enemy2[3].x > 50)
					{
						enemy2[3].x -= 5;
						if (enemy2[3].x <= 50)
							o3 = false;
					}
			}
				
			



				mario.x += x1;
				mario.y += y1;
				
				
				bool t = false;
				for (int i = 0; i < 8; i++) {
					if(n==1)
						if (Sravnenie(wall[i], mario)) {
							t = true;
							break;
						}
					if (n == 2)
						if (Sravnenie(wall1[i], mario)) {
							t = true;
							break;
						}
					if(n==3)
						if (Sravnenie(wall2[i], mario)) {
							t = true;
							break;
						}
				}

				if (t) {
					mario.x -= x1;
					mario.y -= y1;
					
				}

				int k1;
				for (int i = 0; i < 9; i++) {
					if (Sravnenie(bonus[i], mario) && bonus[i].w != 0 &&n==1|| 
						Sravnenie(bonus1[i], mario) && bonus1[i].w != 0 && n == 2||
						Sravnenie(bonus2[i], mario) && bonus2[i].w != 0 && n == 3) {
						k1 = rand() % 20 + 10;
						k += k1;
						if(n==1)
							bonus[i].w = 0;
						if (n == 2)
							bonus1[i].w = 0;
						if(n==3)
							bonus2[i].w = 0;
						sound();
						//cout << i + 1 << " bonus: " << k1 << endl;
						if (n==1 && bonus[0].w == 0 && bonus[1].w == 0 && bonus[2].w == 0 && bonus[3].w == 0 && bonus[4].w == 0 && bonus[5].w == 0
							&& bonus[6].w == 0 && bonus[7].w == 0 && bonus[8].w == 0) {
							cnt = 9; win(renderer,n); n += 1; mario.x = 700; mario.y = 501;
							
							enemy[0].x = -1000;
							enemy[1].x = -1000;
							enemy2[0].x = -1000;
							enemy2[1].x = -1000;
							enemy2[2].x = -1000;
						}
						if (n == 2 && bonus1[0].w == 0 && bonus1[1].w == 0 && bonus1[2].w == 0 && bonus1[3].w == 0 && bonus1[4].w == 0 && bonus1[5].w == 0
							&& bonus1[6].w == 0 && bonus1[7].w == 0 && bonus1[8].w == 0)
						{
							cnt = 9; win(renderer,n); n += 1; mario.x = 700; mario.y = 501;

							enemy1[0].x = -1000;
							enemy1[1].x = -1000;
							enemy1[2].x = -1000;
							enemy2[0].x = 100;
							enemy2[1].x = 400;
							enemy2[2].x = 650;
							enemy2[3].x = 400;

						}
						if (n == 3 && bonus2[0].w == 0 && bonus2[1].w == 0 && bonus2[2].w == 0 && bonus2[3].w == 0 && bonus2[4].w == 0 && bonus2[5].w == 0
							&& bonus2[6].w == 0 && bonus2[7].w == 0 && bonus2[8].w == 0)
						{
							cnt = 9; win(renderer, n); life1 = 0; p = true;

						}
						break;
					}
				}


				bool t2 = false;
				for (int i = 0; i < 2; i++)
					if (Sravnenie(enemy[i], mario)&&n==1)
					{
						t2 = true;
						life--;
						if (life == 0)life1 = 0;
						break;
					}
				for (int i = 0; i < 3; i++)
					if (Sravnenie(enemy1[i], mario) && n == 2)
					{
						t2 = true;
						life--;
						if (life == 0)life1 = 0;
						break;
					}
				for (int i = 0; i < 4; i++)
					if (Sravnenie(enemy2[i], mario) && n == 3)
					{
						t2 = true;
						life--;
						if (life == 0)life1 = 0;
						break;
					}

				if (t2) {
					mario.x -= x1;
					mario.y -= y1;
				}
			
			
		}
		
		
		
			//mario.y += 3;
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, Back, NULL, NULL);
			SDL_RenderCopy(renderer, Texture2, nullptr, &mario);
			for (int i = 0; i < 8; i++) {
				if(n==1)
					SDL_RenderCopy(renderer, image, nullptr, &wall[i]);
				if(n==2)
					SDL_RenderCopy(renderer, image, nullptr, &wall1[i]);
				if(n==3)
					SDL_RenderCopy(renderer, image, nullptr, &wall2[i]);
			}

			for (int i = 0; i < 9; i++) {
				if(n==1)
					SDL_RenderCopy(renderer, Texture3, nullptr, &bonus[i]);
				if(n==2)
					SDL_RenderCopy(renderer, Texture3, nullptr, &bonus1[i]);
				if (n == 3)
					SDL_RenderCopy(renderer, Texture3, nullptr, &bonus2[i]);
			}

			for (int i = 0; i < 2; i++) {
				if(n==1)
					SDL_RenderCopy(renderer, Texture4, nullptr, &enemy[i]);
			}
			for (int i = 0; i < 3; i++)
			{
				if(n==2)
					SDL_RenderCopy(renderer, Texture4, nullptr, &enemy1[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				if (n == 3)
				{
					if (i != 3)
						SDL_RenderCopy(renderer, Texture4, nullptr, &enemy2[i]);
					else
						SDL_RenderCopy(renderer, Squid, nullptr, &enemy2[i]);
				}
					
			}
			
			// Отрисовка сцены 
			SDL_RenderPresent(renderer);

		}
		if (life1 == 0)
		{
			Mix_HaltMusic();
			if(!p)
				not_win(renderer);


		}
	

	
	
	Mix_CloseAudio();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 1;
}
