#pragma once

namespace Engine
{
	class Maths
	{
		/*** Constants ***/
	public:
		static const double PI;
		static const double PosInf;
		static const double NegInf;

		/*** Ctors ***/
	private:
		Maths();

		/*** Fields ***/
		/*** Methods ***/
	public:
		static double Clamp(double Value, double Minimum, double Maximum);
		static double ClampMin(double Value, double Minimum);
		static double ClampMax(double Value, double Maximum);
		static double Clamp01(double Value);
	};
}
