/* BitmapLoader.hpp
 * ****************
 *
 * Header file with declarations for the BitmapLoader class.
 */

#ifndef __SurfaceLoader_hpp__
#define __SurfaceLoader_hpp__

// System includes
#include <map>
#include <string>
#include <iostream>
// Library includes
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
// Local includes
#include "commons.hpp"

// ---
class SurfaceLoader {
	typedef std::map<std::string, SDL_Surface*> SurfaceMap;
	// a map with all surfaces
	SurfaceMap surfaces;
	// private convenience functions for loading/unloading images
	SDL_Surface* load_image(std::string const& path) const;
	void unload_image(SDL_Surface* s) const;
	void unload_image(std::string& path) const;
	// The colour-key, signifying the transparency colour
	SDL_Colour colour_key;
	// Singleton Class - instance holder
	static SurfaceLoader *instance;
	SurfaceLoader (void);
	public :
	// fetches the requested image
	SDL_Surface* loadSurface(std::string const& path);
	SDL_Surface* getSurface(std::string const& path) const ;
	static SurfaceLoader* getInstance(void);
	~SurfaceLoader (void);
};

#endif // __SurfaceLoader_hpp__
