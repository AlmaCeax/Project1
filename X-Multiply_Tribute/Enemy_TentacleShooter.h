#ifndef __TENTACLESHOOTER_H__
#define __TENTACLESHOOTER_H__

#include "Enemy.h"

class Enemy_TentacleShooter :
	public Enemy
{
private:
	Animation anim;
	Animation hitanim;
	int shootTimer = 0;
	bool up = false;
public:
	Enemy_TentacleShooter(int x, int y, bool up);

	void Move();
};

#endif
