#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneStage2.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "ModuleSceneStage1.h"


ModuleSceneStage1::ModuleSceneStage1()
{
	for (int i = 0; i < NUM_LAYERS; ++i)
	{
		textures[i] = nullptr;
	}
}

bool ModuleSceneStage1::Init()
{

	if (!loadMapTextures()) {
		return false;
	}

	startAnimation.PushBack({28, 24, 48, 102});
	startAnimation.PushBack({107, 24, 48, 105});
	startAnimation.PushBack({188, 24, 48, 103});
	startAnimation.PushBack({266, 24, 48, 113});
	startAnimation.PushBack({335, 24, 48, 121});
	startAnimation.PushBack({414, 24, 48, 123});
	startAnimation.PushBack({414, 157, 48, 122});
	startAnimation.PushBack({335, 157, 48, 120});
	startAnimation.PushBack({266, 157, 48, 112});
	startAnimation.PushBack({188, 157, 48, 103});
	startAnimation.PushBack({107, 157, 48, 105});
	startAnimation.PushBack({28, 157, 48, 102});

	startAnimation.repeat = false;
	startAnimation.speed = 0.09f;


	textrect[2] = new SDL_Rect();
	textrect[2]->x = 28;
	textrect[2]->y = 24;
	textrect[2]->w = 48;
	textrect[2]->h = 102;

	injecting = true;

	return true;
}

bool ModuleSceneStage1::Start() {
	App->player->Disable();
	right = false;
	up = false;
	down = false;
	left = false;

	music = App->audio->LoadMusic("Assets/Audio/Music/02_Into_the_Human_Body_Stage_1.ogg");
	shipSpawn = App->audio->LoadFx("Assets/Audio/SFX/xmultipl-026.wav");
	Mix_PlayMusic(music, -1);
	Mix_PlayChannel(-1, shipSpawn, 0);
	return true;
}

update_status ModuleSceneStage1::Update()
{

	checkCameraEvents();
	updateCamera();
	injection();

	App->render->Blit(textures[0], 0, 0, textrect[0], 0.5f);
	App->render->Blit(textures[1], 0, 0, textrect[1]);
	App->render->Blit(textures[2], xInjection, yInjection, textrect[2], 0.9f);


	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) App->fade->FadeToBlack(this, App->stage2, 2);

	return update_status::UPDATE_CONTINUE;
}

bool ModuleSceneStage1::CleanUp()
{
	App->player->Disable();

	for (int i = 0; i < NUM_LAYERS; ++i)
	{
		App->textures->Unload(textures[i]);
		textures[i] = nullptr;
	}

	App->audio->UnloadMusic(music);
	music = nullptr;
	App->audio->UnloadSFX(shipSpawn);
	shipSpawn = nullptr;
	right = false;

	return true;
}


void ModuleSceneStage1::checkCameraEvents()
{
	if (App->render->camera.x > 8000 && App->render->camera.x < 10300)
	{
		down = true;
	}
	else if (down) down = false;
}

void ModuleSceneStage1::updateCamera()
{
	if (App->stage1->IsEnabled()) {
		int speed = 3;

		if (right) {
			App->render->camera.x += speed;
			App->player->position.x += 1;
		}
		if (left)App->render->camera.x -= speed;
		if (up) {
			timer++;
			if (timer >= 3) {
				App->render->camera.y -= speed;
				timer = 0;
			}
		}
		if (down) {
			timer++;
			if (timer >= 3) {
				App->render->camera.y += speed;
				App->player->position.y += 1;
				timer = 0;
			}
		}
	}
}

ModuleSceneStage1::~ModuleSceneStage1()
{
}

bool ModuleSceneStage1::loadMapTextures()
{
	LOG("Loading background textures");
	//Load all background textures
	textures[0] = App->textures->Load("Assets/Sprites/Stages/Stage1/Background/FirstLvlMap.png");
	textures[1] = App->textures->Load("Assets/Sprites/Stages/Stage1/Background/BG01.png");
	textures[2] = App->textures->Load("Assets/Sprites/Stages/Stage1/Background/injection1.png");

	if (textures[0] == nullptr) {
		return false;
	}
	else return true;
}

void ModuleSceneStage1::injection()
{
	if (yInjection >= -4 && injecting)
	{
		if (startAnimation.GetCurrentFrameIndex() == 6)
		{
			App->player->Enable();
			right = true;
			injecting = false;
		}
		textrect[2] = &startAnimation.GetCurrentFrame();
	}
	else {
		if (!injecting)
		{
			if (startAnimation.isDone())
			{
				yInjection--;
			}
			else {
				textrect[2] = &startAnimation.GetCurrentFrame();
			}
		}
		else yInjection++;
	}
}