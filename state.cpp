
#include "state.h"
using namespace std;

//////////
// This function does the pixel math to determine the color of a pixel.
//  If the pixel is the same color as the surface's colorkey (it's
//  transparent pixel color) then the function returns true, false otherwise.
//
//////////

int SDL_CollideTransparentPixelTest(SDL_Surface *surface , int x , int y)
{
	int bpp = surface->format->BytesPerPixel;

	// here p is the address to the pixel we want to retrieve
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	Uint32 pixelcolor;

	// Safe conversion between the pixel and an int value.
	switch(bpp)
	{
		case(1):
			pixelcolor = *p;
		break;

		case(2):
			pixelcolor = *(Uint16 *)p;
		break;

		case(3):
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				pixelcolor = p[0] << 16 | p[1] << 8 | p[2];
			else
				pixelcolor = p[0] | p[1] << 8 | p[2] << 16;
		break;

		case(4):
			pixelcolor = *(Uint32 *)p;
		break;
	}

	// test and return whether pixels color == color of transparent pixels for that surface
	return (pixelcolor == surface->format->colorkey);
}



//////////
// This function generates the bitmask for the entire statemap.  It is a 
//	private function becasue it should only be called by init.
//
//////////

void State::buildMask()
{

	// This is a saftey feature from SDL.  
	SDL_LockSurface(stateMap);
	
	bitmask = new bool[stateMap->w*stateMap->h];

	int w = stateMap->w;

	Uint32 *pixel = (Uint32*)stateMap->pixels;
	
	for(int x = 0; x < stateMap->w; x++)
	{
		for(int y = 0; y < stateMap->h; y++)
		{
		
			if(SDL_CollideTransparentPixelTest(stateMap,x,y))
			{
				bitmask[x+(y*w)] = true;
			}
			else
			{
				bitmask[x+(y*w)] = false;
			}
		}
	}

	SDL_UnlockSurface(stateMap);
}


//////////
// Sets the rectangles and number of frames for this state.  Generates the SDL 
//  surface to be used and sets the transparency with the color in rbg form.
//	Returns false if it fails for some reason.  True otherwise.
//
//////////

bool State::init(char* bitmapName, SDL_Rect* frames, int numberOfFrames,Uint8 r,Uint8 b, Uint8 g)
{
	SDL_Surface* temp = SDL_LoadBMP(bitmapName);					// Load the bitmap
	if(temp == NULL)												// Loading the bitmap failed.  
		cout << "Bitmap Load failed: " << SDL_GetError() << endl;			// report failure on console

	
	stateMap = SDL_DisplayFormat(temp);								// Create SDL surface for drawing later
	if (stateMap == NULL)											// Converting to an SDL surface failed.  Exiting
		return false;


	SDL_FreeSurface(temp);											//Garbage collection


	Uint32 ColorKey = SDL_MapRGB(stateMap->format, r, g, b);		// Generate the color key
	SDL_SetColorKey(stateMap,SDL_SRCCOLORKEY | SDL_RLEACCEL,ColorKey);		// And set the transparency for the SDL surface


	numFrames = numberOfFrames;										// Set the number of frames in animation
	lFrame = frames;												// Set the frames for the bitmap
	buildMask();													// Build the bitmask

	return true;				// WINNAR!!11!!1one11!one!!!
}



//////////
// Sets the rectangles and number of frames for this state.  Generates the SDL 
//  surface to be used and sets the transparency with the color given.
//	Returns false if it fails for some reason.  True otherwise.
//
//////////

bool State::init(char* bitmapName, SDL_Rect* frames, int numberOfFrames, Uint32 ColorKey)
{
	SDL_Surface* temp = SDL_LoadBMP(bitmapName);					// Load the bitmap
	if(temp == NULL)												// Loading the bitmap failed.  
		cout << "Bitmap Load failed: " << SDL_GetError() << endl;			// report failure on console

	
	stateMap = SDL_DisplayFormat(temp);								// Create SDL surface for drawing later
	if (stateMap == NULL)											// Converting to an SDL surface failed.  Exiting
		return false;

	
	SDL_FreeSurface(temp);											//Garbage collection


	SDL_SetColorKey(stateMap,SDL_SRCCOLORKEY | SDL_RLEACCEL,ColorKey);		// Set the transparency for the SDL surface


	numFrames = numberOfFrames;										// Set the number of frames in animation
	lFrame = frames;												// Set the frames for the bitmap
	buildMask();													// Build the bitmask

	return true;				// WINNAR!!11!!1one11!one!!!
}


//////////
// Sets the rectangles and number of frames for this state.  Generates the SDL 
//  surface to be used and sets the transparency with the upper left pixel of
//  the bitmap.
//	Returns false if it fails for some reason.  True otherwise.
//
//////////

bool State::init(char* bitmapName, SDL_Rect* frames, int numberOfFrames)
{
	SDL_Surface* surfaceTemp = SDL_LoadBMP(bitmapName);					// Load the bitmap
	if(surfaceTemp == NULL)												// Test the surface.  
		cout << "Bitmap Load failed: " << SDL_GetError() << endl;			// report failure on console

	
	stateMap = SDL_DisplayFormat(surfaceTemp);							// Create SDL surface for drawing later
	if (stateMap == NULL)												// Converting to an SDL surface failed.  Exiting
		return false;

	
	SDL_FreeSurface(surfaceTemp);										// Garbage collection


	// Extracting color components from a 32-bit color value 
	SDL_PixelFormat *fmt = stateMap->format;

	SDL_LockSurface(stateMap);
	Uint32 pixel=*((Uint32*)stateMap->pixels);
	Uint32 temp;
	SDL_UnlockSurface(stateMap);

	Uint8 red, green, blue;

	// Get Red component 
	temp=pixel&fmt->Rmask; // Isolate red component 
	temp=temp>>fmt->Rshift;// Shift it down to 8-bit 
	temp=temp<<fmt->Rloss; // Expand to a full 8-bit number 
	red=(Uint8)temp;

	// Get Green component 
	temp=pixel&fmt->Gmask; // Isolate green component
	temp=temp>>fmt->Gshift;// Shift it down to 8-bit
	temp=temp<<fmt->Gloss; // Expand to a full 8-bit number
	green=(Uint8)temp;

	// Get Blue component
	temp=pixel&fmt->Bmask; // Isolate blue component 
	temp=temp>>fmt->Bshift;// Shift it down to 8-bit 
	temp=temp<<fmt->Bloss; // Expand to a full 8-bit number 
	blue=(Uint8)temp;

	
	temp = SDL_MapRGB(stateMap->format, red, green, blue);			// Set temp to the first pixel color value
	SDL_SetColorKey(stateMap,SDL_SRCCOLORKEY | SDL_RLEACCEL, temp);	// Set the transparency for the SDL surface


	numFrames = numberOfFrames;										// Set the number of frames in animation
	lFrame = frames;												// Set the frames for the bitmap
	buildMask();													// Build the bitmask 

	return true;				// WINNAR!!11!!1one11!one!!!
}



//////////
// Draws the given frame to the target rect on the sdl surface.
// Fails if the frame number is out of bounds.
//
//////////

void State::draw(SDL_Surface* screen, SDL_Rect* target, int thisFrame)
{
	if(thisFrame >= 0 && thisFrame < numFrames)
		SDL_BlitSurface(stateMap, &lFrame[thisFrame], screen, target);
}



//////////
// Destroys the bitmap in memory.
//	These are the only objects that need to be destroyed by this object.
//	Because of the open ended nature of the system the same frames may
//	be used by several different objects and therefore cannot be destroyed
//	by this object.
//
//////////

State::~State()
{
	SDL_FreeSurface(stateMap);
	delete []bitmask;
	delete stateMap;
}



//////////
// Checking function for collision detection.
//	This takes the coordinates on the last frame of animation as an argument.
//	It adds the frame coordinates to these values to get the correct pixel 
//	location on the bitmask and returns that location.
//	Returns true if the frame or coordinates are out of bounds.
//
//////////

bool State::isPixelTransparent(int thisFrame, int x , int y)
{
	// Safety checking
	if(thisFrame < 0 || thisFrame >= numFrames)
	{
		return true;
	}

	// check to make sure pixel is inside of the current state.
	if( x < 0 || x > lFrame[thisFrame].w || y < 0 || y > lFrame[thisFrame].h)
	{
		return true;
	}

	
	//Convert coordinates to an array
	int tableValue = (x+lFrame[thisFrame].x) + ((y+lFrame[thisFrame].y)*stateMap->w);



	return bitmask[tableValue];
}
