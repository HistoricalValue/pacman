#ifndef __animation_hpp__
#define __animation_hpp__

#include <string>

typedef signed char	offset_t;
typedef unsigned short	delay_t;
typedef unsigned short	animid_t;

class Animation  {
	animid_t id;
	public:
	animid_t GetId (void) const;
	virtual Animation *Clone (animid_t newId) const = 0;
	Animation (animid_t _id);
	virtual ~Animation();
};

#endif
