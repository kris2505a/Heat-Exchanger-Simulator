#pragma once
#include <cmath>

struct InputValues {
	float T1;	//Temperature at entrance - K
	float T2;	//Temperature at exit - K
	float m;	//Mass of the flowing fluid - kg/sec
	float Cp;	//Specific heat of the fluid - J/kg K
	float h;	//Heat transfer coefficient - W/m^2 K

	float tempDiff() {
		return abs(T1 - T2);
	}

	float getC() {
		return m * Cp;
	}
	
};

enum FlowType {
	PARALLEL_FLOW,
	COUNTER_FLOW
};