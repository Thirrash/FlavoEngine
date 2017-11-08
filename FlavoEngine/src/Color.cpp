#include "Color.h"
#include "Maths.h"

const Engine::Color Engine::Color::White(1.0f, 1.0f, 1.0f, 1.0f);
const Engine::Color Engine::Color::Red(1.0f, 0.0f, 0.0f, 1.0f);
const Engine::Color Engine::Color::Green(0.0f, 1.0f, 0.0f, 1.0f);
const Engine::Color Engine::Color::Blue(0.0f, 0.0f, 1.0f, 1.0f);
const Engine::Color Engine::Color::Black(0.0f, 0.0f, 0.0f, 1.0f);

Engine::Color::Color(float Red, float Green, float Blue, float Alpha) {
	this->R = Engine::Maths::Clamp01(Red);
	this->G = Engine::Maths::Clamp01(Green);
	this->B = Engine::Maths::Clamp01(Blue);
	this->A = Engine::Maths::Clamp01(Alpha);
}