#include "Lander.h"
#include "Game.h"

Lander::Lander(Game& game, const CL_Vec2<float>& position, float fuel) : GameComponent(game), position(position), radius(10.0f), fuel(fuel)
{
	engines[MAIN_ENGINE] = JetEngine(CL_Vec2<float>(0.0f, 20.0f));
	engines[LEFT_ENGINE] = JetEngine(CL_Vec2<float>(-20.0f, 0.0f));
	engines[RIGHT_ENGINE] = JetEngine(CL_Vec2<float>(20.0f, 0.0f));

	for (int i = 0; i < 3; ++i)
		engines[i].isActive = false;

	font = CL_Font(window.get_gc(), "Arial", 20);
}


void Lander::update(float elapsed)
{
	if (position.y - radius <= 0)
		return;

	CL_Vec2<float> acceleration = game.getGravity();

	for (int i = 0; i < 3; ++i)
	{
		if (fuel > 0 && engines[i].isActive)
		{
			acceleration += engines[i].acceleration;
			--fuel;
		}
	}

	velocity += acceleration * elapsed;
	position += velocity * elapsed;
}


void Lander::draw(float elapsed)
{
	CL_Rect viewport = window.get_viewport();
	
	float width = (float)viewport.get_width();
	float height = (float)viewport.get_height();

	CL_Draw::circle(window.get_gc(), CL_Pointf(width / 2 + position.x, height - position.y), radius, CL_Colorf::red);

	font.draw_text(window.get_gc(), CL_Pointf(10, 20), "Vertical Velocity: " + CL_StringHelp::float_to_text(velocity.y, 1));
	font.draw_text(window.get_gc(), CL_Pointf(10, 40), "Horizontal Velocity: " + CL_StringHelp::float_to_text(velocity.x, 1));
	font.draw_text(window.get_gc(), CL_Pointf(10, 60), "Fuel: " + CL_StringHelp::float_to_text(fuel, 0));
}


void Lander::setJetEngine(bool active, int index)
{
	engines[index].isActive = active;
}