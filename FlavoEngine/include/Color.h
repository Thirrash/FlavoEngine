#pragma once

namespace Engine
{
	struct Color
	{
		/*** Constants ***/
	public:
		static const Color White;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Black;

		/*** Ctors ***/
	public:
		Color(float Red, float Green, float Blue, float Alpha);

		/*** Fields ***/
	public:
		float R;
		float G;
		float B;
		float A;

		/*** Methods ***/
	};
}


