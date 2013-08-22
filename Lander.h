#pragma once

#include "GameComponent.h"

class Lander : public GameComponent
{
public:
	Lander(Game& game, const CL_Vec2<float>& position, float fuel);

	void update(float elapsed);
	void draw(float elapsed);

	void setJetEngine(bool active, int index);

	static const int MAIN_ENGINE = 0;
	static const int LEFT_ENGINE = 1;
	static const int RIGHT_ENGINE = 2;
private:
	struct JetEngine
	{
		CL_Vec2<float> acceleration;
		bool isActive;

		JetEngine() {}
		JetEngine(const CL_Vec2<float>& acceleration, bool isActive = false) : acceleration(acceleration), isActive(isActive) {}

		void operator=(const JetEngine& other)
		{
			this->acceleration = other.acceleration;
			this->isActive = other.isActive;
		}
	};

	const float radius;

	JetEngine engines[3];

	float fuel;

	CL_Vec2<float> position;
	CL_Vec2<float> velocity;

	CL_Font font;
};

