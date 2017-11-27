#pragma once

#include "EntityX.h"

namespace Engine
{
	enum EKeyCode
	{
		W = 87,
		A = 65,
		S = 83,
		D = 68,
		Q = 81,
		E = 69,
		R =82,
		Escape = 256
	};

	enum EKeyState
	{
		Pressed = 1,
		Released = 0
	};

	struct MouseInput : public Event<MouseInput>
	{
		double X;
		double Y;
		double Scroll;

		MouseInput(double X, double Y, double Scroll);

		static MouseInput Zero;

		bool operator ==(const MouseInput& Other);
		bool operator !=(const MouseInput& Other);
	};

	class Input
	{
	public:
		static bool IsKeyDown(EKeyCode Key);
	};
}