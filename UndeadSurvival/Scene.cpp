#include "pch.h"
#include "Scene.h"
#include "Actor.h"
#include "UI.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	for (const vector<Actor*>& actors : _Actors)
		for (Actor* actor : actors)
			SAFE_DELETE(actor);
	_Actors->clear();

	for(UI* ui : _uis)
		SAFE_DELETE(ui);
	_uis.clear();
}

void Scene::Init()
{
	for (const vector<Actor*>& actors : _Actors)
		for (Actor* actor : actors)
			actor->BeginPlay();

	for (UI* ui : _uis)
		ui->Begin();
}

void Scene::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	GET_SINGLE(CollisionManager)->Update();

	for (const vector<Actor*>& actors : _Actors)
		for (Actor* actor : actors)
			actor->Tick();

	for(UI* ui : _uis)
		ui->Tick();
}

void Scene::Render(HDC hdc)
{
	for (const vector<Actor*>& actors : _Actors)
		for (Actor* actor : actors)
			actor->Render(hdc);

	for(UI* ui : _uis)
		ui->Render(hdc);
}

void Scene::AddActor(Actor* actor)
{
	if(actor == nullptr) return;
	_Actors[actor->getLayerType()].push_back(actor);
}

void Scene::RemoveActor(Actor* actor)
{
	if(actor == nullptr) return;
	vector<Actor*>& v = _Actors[actor->getLayerType()];
	v.erase(std::remove(v.begin(), v.end(), actor), v.end());
}