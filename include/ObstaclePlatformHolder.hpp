/* ObstaclePlatformHolder
 *
 * Parses the configuration file to create all obstacle platforms of
 * the map. It also server as a holder/accessor for all the platforms.
 */

#ifndef __ObstaclePlatformHolder_hpp__
#define __ObstaclePlatformHolder_hpp__

#include <list>

#include "ObstaclePlatform.hpp"
#include "SpriteHolder.hpp"

typedef unsigned short int obstplatid_t;

class ObstaclePlatformHolder {
	public :
	typedef std::map<obstplatid_t, ObstaclePlatform*> obstplats_map;
	ObstaclePlatformHolder(std::string const &config_file_path,
	 SpriteHolder *sprite_holder);
	~ObstaclePlatformHolder(void);
	ObstaclePlatform *getObstaclePlatform(obstplatid_t id);
	obstplats_map &getObstaclePlatforms(void);
	void displayPlatforms(SDL_Surface *destination);
	private :
	obstplats_map plats;
};

#endif // __ObstaclePlatformHolder_hpp__
