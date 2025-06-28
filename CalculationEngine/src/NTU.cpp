#include "NTU.h"
#include <iostream>

NTU::NTU(const InputValues& _hotBody, const InputValues& _coldBody, FlowType _type)
	: m_hotBody(_hotBody), m_coldBody(_coldBody), m_flow(_type),
	m_effectiveness(0.7f), m_heatExchanged(0.000f), m_logMeanTempDifference(0.000f), 
	m_area(0.000f), m_overallHeatExchanged(0.000f), m_overallHeatTransferCoeff(0.000f) {


	/*CALCULATION STEPS :
		calculate Qoverall
		calculate Area using Qoverall
		calculate NTU using Area
		calculate Effectivenss using NTU
		calculate Q using Effectiveness
		calculate T2, t2 using Q
	*/
	m_hotBody.T1 += 273;
	m_coldBody.T1 += 273;

	calculateCminCmax(); 
	calculateOverallHeatTransferCoeff();
	calculateOverallHeatExchanged(); 
	calculateNTU();
	calculateHeatExchanged();
	calculateExitTemperatures();
	calculateLogMeanTempDifference();
	calculateArea();
}

void NTU::printResults() {
	std::cout << "Cmin = " << m_Cmin << std::endl;
	std::cout << "Cmax = " << m_Cmax << std::endl;
	std::cout << "Qover = " << m_overallHeatExchanged << std::endl;
	std::cout << "U = " << m_overallHeatTransferCoeff << std::endl;
	std::cout << "Delta T = " << m_logMeanTempDifference << std::endl;
	std::cout << "A = " << m_area << std::endl;
	std::cout << "NTU = " << m_ntu << std::endl;
	std::cout << "E = " << m_effectiveness << std::endl;
	std::cout << "Q = " << m_heatExchanged << std::endl;
	std::cout << "T2 = " << m_hotBody.T2 << std::endl;
	std::cout << "t2 = " << m_coldBody.T2 << std::endl;
}

void NTU::calculateCminCmax() {
	m_Cmin = m_coldBody.getC();
	m_Cmax = m_hotBody.getC();

	if (m_Cmin > m_Cmax)
		std::swap(m_Cmin, m_Cmax);
}

void NTU::calculateArea() {
	m_area = m_overallHeatExchanged / (m_overallHeatTransferCoeff * m_logMeanTempDifference);
}

void NTU::calculateLogMeanTempDifference() {
	float x, y; //difference values;
	if (m_flow == FlowType::PARALLEL_FLOW) {
		x = m_hotBody.T1 - m_coldBody.T1;
		y = m_hotBody.T2 - m_coldBody.T2;
	}
	else {
		x = m_hotBody.T1 - m_coldBody.T2;
		y = m_hotBody.T2 - m_coldBody.T1;
	}
	m_logMeanTempDifference = (x - y) / (std::log(x / y));
}

void NTU::calculateOverallHeatTransferCoeff() {
	m_overallHeatTransferCoeff = (m_hotBody.h * m_coldBody.h) / (m_hotBody.h + m_coldBody.h);
}

void NTU::calculateExitTemperatures() {
	m_hotBody.T2 = m_hotBody.T1 - (m_heatExchanged / (m_hotBody.m * m_hotBody.Cp));
	m_coldBody.T2 = m_coldBody.T1 + (m_heatExchanged / (m_coldBody.m * m_coldBody.Cp));
}

//	IF I WERE TO CALCULATE EFFECTIVENESS, AN ENDLESS LOOP OF CALCULATIONS BEGIN, RESULTING IN BRAIN FUCK.
//void NTU::calculateEffectiveness() {
//
//	float C = m_Cmin / m_Cmax;
//
//	if (m_flow == FlowType::PARALLEL_FLOW) {
//		m_effectiveness = ((1 - std::exp(-m_ntu * (1 + C))) / (1 + C));
//	}
//	else {
//		float numerator = std::exp(-m_ntu * (1 - C));
//		m_effectiveness = ((1 - numerator) / (1 - C * numerator));
//	}
//}

void NTU::calculateOverallHeatExchanged() {
	m_overallHeatExchanged = m_Cmin * (m_hotBody.T1 - m_coldBody.T1);
}

void NTU::calculateHeatExchanged() {
	m_heatExchanged = m_effectiveness * m_Cmin * (m_hotBody.T1 - m_coldBody.T1);
}

void NTU::calculateNTU() {
	m_ntu = m_overallHeatTransferCoeff * m_area / m_Cmin;
}
