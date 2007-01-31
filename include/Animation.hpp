#ifndef _ANIMATION_HPP_
#define _ANIMATIPN_HPP_

#include <string>

typedef signed char	offset_t;
typedef unsigned short	delay_t;
typedef unsigned short	animid_t;

class Animation  {
	animid_t id;
	public:
	animid_t GetId (void) const;
	virtual Animation* Clone (animid_t newId) const = 0;
	Animation (animid_t _id);
	virtual ~Animation();
};

#endif
