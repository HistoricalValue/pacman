/* Struct with custom data used by user custom postinit functions.
 */

#ifndef __CustomPostinit_Data__
#define __CustomPostinit_Data__
struct custompostinit_data {
	std::map<GameSprite *, SDL_Rect> initpos;
}; // struct custompostinit_data
#endif // __CustomPostinit_Data__

