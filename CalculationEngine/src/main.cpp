#include "NTU.h"
#include <iostream>

int main() {
	float T1, t1, mh, mc, cph, cpc, hh, hc;
	
	std::cin >> T1 >> mh >> cph >> hh;

	std::cin >> t1 >> mc >> cpc >> hc;

	NTU ntu({ T1, 0.0f, mh, cph, hh }, { t1, 0.0f, mc, cpc, hc }, FlowType::COUNTER_FLOW);
	ntu.printResults();
}