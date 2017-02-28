#pragma once
#ifndef _Entities_H_
#define _Entities_H_

#include <iostream>
#include <vector>

#include "Vector2.h"
#include "Vector3.h"

namespace Asteroids 
{
	const float angle_offset = 90.0f;
	const float m_PlayerSpeed = 5.0f;
	class Entities
	{
	public:
		virtual void Render() { return; };
		virtual void Update(float deltaTime) { return; };
		virtual void translate(Engine::Math::Vector2D pos) { return; };
		virtual void rotate(float num) { return; };
		virtual void wrapAround() { return; };
		bool isColliding(Entities* rhs);

	protected:
		std::vector<Engine::Math::Vector2D> m_points;
		float m_mass;
		float m_radius;
		float m_angle;
		float m_angleInRads;
		Engine::Math::Vector2D m_position;
		Engine::Math::Vector3D m_currentColor;
	};
}

#endif // !_Entities_H_