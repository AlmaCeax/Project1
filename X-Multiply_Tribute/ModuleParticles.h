#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_PARTICLES 50

struct SDL_Texture;
struct Collider;
struct Mix_Chunk;
enum COLLIDER_TYPE;

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	int w, h = 0;
	Uint32 born = 0;
	Uint32 life = 0;
	int offsetx = 0;
	int offsety = 0;
	bool fx_played = false;
	bool isPlayerAttached = false;
	Mix_Chunk* sfx = nullptr;
	int id = 0;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);
	void OnCollision(Collider* c1, Collider* c2);

private:

	SDL_Texture * graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;

public:
	Particle baseShot;
	Particle baseShotExp;
	Particle baseShotColExp;
	Particle bombshot;
	Particle bombExplosion;
};

#endif // __MODULEPARTICLES_H__