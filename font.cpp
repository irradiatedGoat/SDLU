#include "font.h"
#include "String.h"

Queue<char>* Font::tokenize(char* text, int width, char breakChar)
{
	Queue<char>* words = new Queue<char>();
	Queue<char>* tokens = new Queue<char>();

	int strLength = strlen(text);
	int curr = 0;
	int eoLastWord = 0;
	char* temp;
	while(text[curr])
	{
		if(text[curr] == breakChar || curr == strLength-1)
		{
			temp = new char[(curr-eoLastWord)+1];
			for(int counter =0; counter < (curr-eoLastWord)+1; counter++)
			{
				temp[counter] = text[eoLastWord+counter];
			}
			temp[(curr-eoLastWord)+1]= 0;
			words->insert(temp);
			eoLastWord = curr+1;
		}

		curr++;
	}

//	int totalPixels;
	char* buff = 0;
	char* tmp;
	char* c;
	//Parse through words making sure they don't hit the width barrier removing them
	//and concat them into the token current queue
	//if width is hit then start new token string
	while(words->length())
	{
		if(buff)
		{
			tmp = words->remove();
			c = new char[strlen(buff)+strlen(tmp)+1];
			int counter;
			for(counter = 0; counter < strlen(buff); counter++)
			{
				c[counter] = buff[counter];
			}
			int count;
			for(count = 0; count < strlen(tmp); count++)
			{
				c[counter+count] = tmp[count];
			}
			c[counter+count+1] = '\0';
			delete []buff;
			delete []tmp;
			buff = c;
		}
		else
		{
			buff = words->remove();
		}
		if((renderedWidth(buff)+ renderedWidth(words->display())) > width)
		{
			tokens->insert(buff);
			buff = 0;
		}
	}
		/*
		totalPixels=0;
		words->beginning();
		buff = new char[strlen(words->display())+1];
		tmp = words->remove();
		for(int counter = 0; counter < strlen(tmp)+1; counter++)
		{
			buff[counter] = tmp[counter];
		}
		totalPixels = renderedWidth(buff);
		while(renderedWidth(tmp)+totalPixels < width)
		{
			tmp = words->remove();
			c = new char[strlen(buff)+strlen(tmp)+1];
			for(counter = 0; counter < strlen(buff); counter++)
			{
				c[counter] = buff[counter];
			}
			for(int count = 0; count < strlen(tmp); count++)
			{
				c[counter+count] = tmp[count];
			}
			c[counter+count+1] = '\0';
			delete []buff;
			delete []tmp;
			buff = c;
			totalPixels = renderedWidth(buff);
			if(!words->length())
			{
				break;
			}
		}
		tokens->insert(buff);
	
	}*/
	return tokens;
	
	
	return 0;
	
}

Font::Font(TTF_Font* fo)
{
	f = fo;
};

bool Font::init(char* file, int pointsize)
{
	f = TTF_OpenFont(file, pointsize);
	if(f != 0)
	{
		return true;
	}
	return false;
}

int Font::renderedWidth(char* text)
{
	if(f == 0 || text == 0)
	{
		return 0;
	}
	int length =0;
	TTF_SizeText(f, text, &length, 0);
	
	return length;
};

int Font::renderedHeight(char* text)
{
	if(f == 0)
	{
		return 0;
	}
	return TTF_FontHeight(f);
};

SpriteController* Font::renderNew(char* text, SDL_Rect* metrics, Uint8 r, Uint8 g, Uint8 b)
{
	if(f != 0)
	{
		SDL_Color color={r,g,b};
		return renderNew(text,metrics,color);
	}
	return 0;
};

SpriteController* Font::renderNew(char* text, SDL_Rect* metrics, SDL_Color color)
{
	if(f != 0)
	{
		SDL_Rect* temp = new SDL_Rect();
		int tempW, tempH;
		TTF_SizeText(f, text, &tempW, &tempH);

		temp->x = 0;
		temp->y = 0;
		temp->w = tempW;
		temp->h = tempH;
		SDL_Surface* text_surface;
		if(text_surface = TTF_RenderText_Solid(f,text,color))
		{
			return new SpriteController(new Sprite(new State(text_surface, temp,1), 1),0,0, 0, 0, metrics->x, metrics->y, 10);		
		}
	}
	return 0;
};

SpriteController* Font::renderNew(char* text, char breakChar, SDL_Rect* metrics, Uint8 r, Uint8 g, Uint8 b)
{
	if(f != 0)
	{
		SDL_Color color={r,g,b};
		return renderNew(text, breakChar, metrics, color);
	}
	return 0;
};

SpriteController* Font::renderNew(char* text, char breakChar, SDL_Rect* metrics, SDL_Color color)
{
	if(f != 0)
	{
		Queue<char>* tokens;
		if(renderedWidth(text) > metrics->w)
		{
			tokens = tokenize(text, metrics->w, breakChar);
		}
		else
		{
			return renderNew(text, metrics,color);
		}
		SDL_Surface* total = new SDL_Surface();
		SDL_Rect target;
		target.x = 0;
		target.y = 0;
		target.w = 640;
		target.h = 480;
		int offset = 0;
		Queue<SDL_Surface> surfaces;
		Queue<SDL_Rect> rects;
		while(tokens->length())
		{
			
			char* tex = tokens->remove();
			SDL_Rect *temp = new SDL_Rect;
			int tempW, tempH;
			TTF_SizeText(f, tex, &tempW, &tempH);

			temp->x = 0;
			temp->y = offset;
			temp->w = tempW;
			temp->h = tempH;
			offset += tempH;
			SDL_Surface* text_surface;
			if(text_surface = TTF_RenderText_Solid(f,tex,color))
			{
				surfaces.insert(text_surface);
				rects.insert(temp);

//				delete []tex;
			}
			else
			{
				return 0;
			}

		}
		delete tokens;
		SDL_Rect* tmp;
		SDL_Surface* sur;
		SDL_Rect dest;
		dest.x = 0;
		dest.y = 0;
		dest.w = 640;
		dest.y = 480;
		while(surfaces.length())
		{
			sur = surfaces.remove();
			tmp = rects.remove();
			SDL_BlitSurface(sur, tmp, total, &dest);
		}
		SDL_Rect* final = new SDL_Rect();
		final->x = 0;
		final->y = 0;
		final->w = metrics->w;
		final->h = offset;
		return new SpriteController(new Sprite(new State(total, final,1), 1), 0, 0, metrics->x, metrics->y, 10);
		/*SDL_Rect* temp = new SDL_Rect();
		int tempW, tempH;
		TTF_SizeText(f, text, &tempW, &tempH);

		temp->x = 0;
		temp->y = 0;
		temp->w = tempW;
		temp->h = tempH;
		SDL_Surface* text_surface;
		if(text_surface = TTF_RenderText_Solid(f,text,color))
		{
			return new SpriteController(new Sprite(new State(text_surface, temp,1), 1), 0, 0, metrics->x, metrics->y, 10);
		}*/
	}
	return 0;
};