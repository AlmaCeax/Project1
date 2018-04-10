#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"
#define MAX_FRAMES 25

class Animation
{
public:
	bool repeat = true;
	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];

private:
	float current_frame;
	int last_frame = 0;

public:

	void PushBack(const SDL_Rect& rect)
	{
		frames[last_frame++] = rect;
	}

	bool isDone()
	{
		if (current_frame == last_frame-1) return true;
		else return false;
	}

	int GetCurrentFrameIndex()
	{
		return current_frame;
	}

	SDL_Rect& GetCurrentFrame()
	{
		current_frame += speed;
		if (current_frame >= last_frame && repeat == false)
		{
			current_frame = (int)current_frame - 1;
		}
		else if(current_frame >= last_frame && repeat == true)
		{
			current_frame = 0;
		}

		return frames[(int)current_frame];
	}
	void ResetAnimation() {
		current_frame = 0;
	}
};

#endif