/* SurfaceLoader.cpp
 * *****************
 *
 * Implementation of the SurfaceLoader header..
 */

#include <iostream>
#include "SurfaceLoader.hpp"

using namespace cs454_2006;

// Loads and returns the requested surface.
// If the surface has been requested/loaded before, it exists in the map
// and is returned right away.
SDL_Surface* SurfaceLoader::loadSurface(std::string const& path)
{
	// search if image has been loaded
	SurfaceMap::const_iterator s = surfaces.find(path);
	SDL_Surface* result;
	if (s == surfaces.end()) // has not been loaded
		// load now
		surfaces[path] = (result = load_image(path));
		// error about image loaded checked in load_image
	else // surface has been loaded
		// use map.find result
		result = s->second;
	std::cerr << " *** Loaded surface " << path << " at " << result <<
	 std::endl;
	return result;
} // loadSurface()

void SurfaceLoader::unload_image(SDL_Surface* s) const
	{ SDL_FreeSurface(s); }
void SurfaceLoader::unload_image(std::string& path) const
	{ unload_image( getSurface(path) ); }

SDL_Surface* SurfaceLoader::getSurface(std::string const& path) const {
	SurfaceMap::const_iterator s = surfaces.find(path);
	return  s == surfaces.end() ? static_cast<SDL_Surface*>(0) : s->second;
}

SurfaceLoader::~SurfaceLoader(void)
{
	std::cerr << " *** Killing SurfaceLoader" << std::endl;
	SurfaceMap::const_iterator ite = surfaces.begin();
	while (ite != surfaces.end()) {
		SDL_Surface* surf = ite++->second;
		unload_image(surf);
		std::cerr << " *** Unloaded surface at " << surf <<
		 std::endl;
	}

	instance = NULL;
} // ~SurfaceLoader()

SDL_Surface* SurfaceLoader::load_image(std::string const& filename) const
{
	// tmp storage
	SDL_Surface* loaded = NULL;
	// optimased
	SDL_Surface* opted = NULL;
	// Load
	loaded = IMG_Load(filename.c_str());
	// err check
	std::cerr << " *** " << filename;
	if (!loaded) { // error while loading
		std::cerr << " could not be loaded." <<
		 std::endl;
		nf(-1, "Could not load image.");
	} else {
		std::cerr << " loaded." << std::endl;
		// optimise 
		opted = SDL_DisplayFormat(loaded);
		if (!opted) nf(-1, "Could not optimise loaded image");
		// free the previous
		SDL_FreeSurface(loaded);
	}
	// add transparency colour
	Uint32 colourkey = SDL_MapRGB(opted->format, 0xff, 0x0, 0xff);
	SDL_SetColorKey(opted, SDL_RLEACCEL | SDL_SRCCOLORKEY, colourkey);

	// return optimised result
	return opted;
} // load_image

SurfaceLoader::SurfaceLoader(void) {
	std::cerr << " *** Created SurfaceHolder" << std::endl;
} // SurfaceLoader()

SurfaceLoader* SurfaceLoader::getInstance(void) {
	if (!instance)
		instance = new SurfaceLoader();
	return instance;
} // getInstance()

// Singlaton class - single instance reference
SurfaceLoader* SurfaceLoader::instance = NULL;
