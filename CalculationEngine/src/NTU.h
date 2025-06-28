#pragma once
#include "InputValues.h"

class NTU {
private:
	InputValues m_hotBody;
	InputValues m_coldBody;

	float m_area;
	float m_heatExchanged;
	float m_logMeanTempDifference;
	float m_overallHeatTransferCoeff;
	float m_effectiveness;
	float m_overallHeatExchanged;
	float m_ntu;

	float m_Cmin;
	float m_Cmax;

	FlowType m_flow;


	void calculateArea();
	void calculateLogMeanTempDifference();
	void calculateOverallHeatTransferCoeff();
	void calculateExitTemperatures();
	//void calculateEffectiveness();
	void calculateNTU();
	void calculateCminCmax();
	void calculateOverallHeatExchanged();
	void calculateHeatExchanged();
	
public:
	NTU(const InputValues& _hotBody, const InputValues& _coldBody, FlowType _type);
	~NTU() = default;

	void printResults();
	
};