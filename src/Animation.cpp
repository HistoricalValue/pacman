#include "Animation.hpp"

animid_t Animation::GetId (void) const {return id;}
Animation::Animation(animid_t _id) : id(_id) { }
Animation::~Animation(void) { }
