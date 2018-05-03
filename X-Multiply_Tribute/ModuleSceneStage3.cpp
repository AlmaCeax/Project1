#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollision.h"
#include "ModuleSceneStart.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "ModuleSceneStage3.h"



ModuleSceneStage3::ModuleSceneStage3()
{
	for (int i = 0; i < 3; ++i)
	{
		textures[i] = nullptr;
	}
}


ModuleSceneStage3::~ModuleSceneStage3()
{

}


bool ModuleSceneStage3::Start() {
	App->current_scene = this;

	App->collision->Enable();
	App->player->Enable();

	App->render->SetCameraPosition(0, 337);

	music = App->audio->LoadMusic("Assets/Audio/Music/06_The_Rolling_Worms_Stage_3-1_.ogg");
	textures[0] = App->textures->Load("Assets/Sprites/Stages/Stage3/Background/Backgroundbg03.png");
	textures[1] = App->textures->Load("Assets/Sprites/Stages/Stage3/Background/Layerbg03.png");

	Mix_PlayMusic(music, -1);
	return true;
}

bool ModuleSceneStage3::Init()
{
	rect[0] = { 0,0,5098,544 };
	rect[1] = { 0,0,5104,561 };
	return true;
}

update_status ModuleSceneStage3::Update()
{

	App->render->Blit(textures[0], 0, 0, &rect[0], 0.5f);
	App->render->Blit(textures[1], 0, 0, &rect[0]);
	return update_status::UPDATE_CONTINUE;
}

bool ModuleSceneStage3::CleanUp()
{
	App->player->Disable();
	App->collision->Disable();

	for (int i = 0; i < 3; ++i)
	{
		App->textures->Unload(textures[i]);
		textures[i] = nullptr;
	}

	App->audio->UnloadMusic(music);
	music = nullptr;

	return true;
}

