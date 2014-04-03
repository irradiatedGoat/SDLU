#ifndef _FONT_H_
#define _FONT_H_

#include "datastruct.h"
#include "spritecontroller.h"
#include "SDL_TTF.h"

class Font
{
private:
	TTF_Font* f;
	Queue<char>* tokenize(char* text, int width, char breakChar = ' ');
public:
	Font(TTF_Font* fo);
	Font(){};
	bool init(char* file, int pointsize);
	~Font(){};
	int renderedWidth(char* text);
	int renderedHeight(char* text);
	SpriteController* renderNew(char* text, SDL_Rect* metrics, Uint8 r, Uint8 g, Uint8 b);
	SpriteController* renderNew(char* text, SDL_Rect* metrics, SDL_Color);
	SpriteController* renderNew(char* text, char breakChar, SDL_Rect* metrics, Uint8 r, Uint8 g, Uint8 b);
	SpriteController* renderNew(char* text, char breakChar, SDL_Rect* metrics, SDL_Color);
	
};
#endif