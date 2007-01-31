/* SpriteHolder
 *
 * Keeps list of all Sprites and offers methods for massive sprite
 * manipulation.
 *
 */

#ifndef __SpriteHolder_hpp__
#define __SpriteHolder_hpp__

#include <map>
#include <list>
#include <string>
#include "GameSprite.hpp"
#include "ObstacleSprite.hpp"
#include "AnimationFilmHolder.hpp"

class SpriteHolder {
	public :
	void addSprite(Sprite* s, int z_order);
	Sprite* removeSprite(Sprite* s);
	Sprite* getSprite(spriteid_t);
	void displaySprites(SDL_Surface* dst);
	std::list<Sprite*> const& getSprites(void) const;
	std::list<GameSprite*> const& getGameSprites(void) const;
	std::list<ObstacleSprite*> const& getObstacleSprites(void) const;
	SpriteHolder(std::string& config_file_path, AnimationFilmHolder*);
	~SpriteHolder(void);
	typedef std::map<int, std::list<Sprite*> > SpritesMap;
	private :
	SpritesMap sprites;
	std::list<Sprite*> allsprites;
	std::list<GameSprite*> gamesprites;
	std::list<ObstacleSprite*> obstaclesprites;
};

#endif // __SpriteHolder_hpp__
