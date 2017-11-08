#include "Maths.h"
#include <cmath>
#include <float.h>

const double Engine::Maths::PI = 3.14159265359;
const double Engine::Maths::PosInf = DBL_MAX;
const double Engine::Maths::NegInf = DBL_MIN;

Engine::Maths::Maths() {

}

double Engine::Maths::Clamp(double Value, double Minimum, double Maximum) {
	return (Value > Maximum) ? Maximum : (Value < Minimum) ? Minimum : Value;
}

double Engine::Maths::ClampMin(double Value, double Minimum) {
	return (Value < Minimum) ? Minimum : Value;
}

double Engine::Maths::ClampMax(double Value, double Maximum) {
	return (Value > Maximum) ? Maximum : Value;
}

double Engine::Maths::Clamp01(double Value) {
	return (Value > 1.0) ? 1.0 : (Value < 0.0) ? 0.0 : Value;
}

