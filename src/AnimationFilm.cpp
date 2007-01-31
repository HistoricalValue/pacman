#include "AnimationFilm.hpp"
#include "commons.hpp"

using namespace cs454_2006;

void AnimationFilm::DisplayFrame (SDL_Surface *dest, SDL_Rect *at, char frameNo) const {
	SDL_Rect fbox = GetFrameBox(frameNo);
	nf(SDL_BlitSurface(bitmap, &fbox, dest, at), "Failed blit");
}

std::ostream& operator<<(std::ostream& o, AnimationFilm& a) {
	const char tab = '\t', comma = ',', lbrace = '{', rbrace = '}',
	 space = ' ';
	o << a.id << std::endl << tab << a.bitmap << std::endl << tab;
	
	std::vector<SDL_Rect>::const_iterator ite;
	for (ite = a.boxes.begin(); ite != a.boxes.end(); ite++)
		o << lbrace << ite->x << comma << ite->y << comma <<
		 ite->w << comma << ite->h << rbrace << space;

	return o << std::endl;
}

char AnimationFilm::GetTotalFrames (void) const { return boxes.size(); }
SDL_Surface* AnimationFilm::GetBitmap (void) const { return bitmap; }
std::string const& AnimationFilm::GetId (void) const { return id; }
SDL_Rect const&	AnimationFilm::GetFrameBox (unsigned char frameNo) const{
	assert(boxes.size()>frameNo);
	return boxes[frameNo];
}

// Constructor
AnimationFilm::AnimationFilm (
 SDL_Surface* _bitmap,
 std::vector<SDL_Rect> const& _boxes,
 std::string const& _id
)
 : bitmap(_bitmap), boxes(_boxes), id(_id)
{ }
