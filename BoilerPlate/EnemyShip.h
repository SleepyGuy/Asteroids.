#pragma once
#include "Entities.h"
#include "Vector2.h"

using namespace Asteroids;
using namespace Engine::Math;
class EnemyShip : public Entities
{
public :
	EnemyShip();
	void Render() override;
	void Update(float deltaTime) override;
	void GeneratePoints();
	float x;
	Vector2D Position;
};
