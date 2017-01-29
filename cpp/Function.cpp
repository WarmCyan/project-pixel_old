//*************************************************************
//  File: Function.cpp
//  Date created: 1/28/2017
//  Date edited: 1/28/2017
//  Author: Nathan Martindale
//  Copyright © 2017 Digital Warrior Labs
//  Description: 
//*************************************************************

#ifndef FF_FUNCTION_CPP
#define FF_FUNCTION_CPP

#include "Function.h"

using namespace std;

namespace dwl
{
	FFFunction::FFFunction()
	{
		m_fColor = 0.0f;
		m_fWeight = 1.0f;

		m_bIsSymmetry = false;

		//float aMatrixCoefficients
		m_vMatrixCoefficients = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f }; // linear by default (ax + by + c, dx + ey + f)
		m_vVariationWeights = { 0.0f, 0.0f, 0.0f, 0.0f };
	}

	vector<float> FFFunction::Run(float fX, float fY)
	{
		float fResultX = 0.0f;
		float fResultY = 0.0f;

		/*float fA = m_vMatrixCoefficients[0];
		float fB = m_vMatrixCoefficients[1];
		float fC = m_vMatrixCoefficients[2];
		float fD = m_vMatrixCoefficients[3];
		float fE = m_vMatrixCoefficients[4];
		float fF = m_vMatrixCoefficients[5];*/

		float fTerm1 = m_vMatrixCoefficients[0]*fX + m_vMatrixCoefficients[1]*fY + m_vMatrixCoefficients[2];
		float fTerm2 = m_vMatrixCoefficients[3]*fX + m_vMatrixCoefficients[4]*fY + m_vMatrixCoefficients[5];
		
		if (m_vVariationWeights[VAR_LINEAR] > 0)
		{
			vector<float> vTemp = Var_Linear(fTerm1, fTerm2);
			fResultX += vTemp[0]*m_vVariationWeights[VAR_LINEAR];
			fResultY += vTemp[1]*m_vVariationWeights[VAR_LINEAR];
		}
		
		if (m_vVariationWeights[VAR_SINUSOIDAL] > 0)
		{
			vector<float> vTemp = Var_Sinusoidal(fTerm1, fTerm2);
			fResultX += vTemp[0]*m_vVariationWeights[VAR_SINUSOIDAL];
			fResultY += vTemp[1]*m_vVariationWeights[VAR_SINUSOIDAL];
		}
		
		if (m_vVariationWeights[VAR_SPHERICAL] > 0)
		{
			vector<float> vTemp = Var_Spherical(fTerm1, fTerm2);
			fResultX += vTemp[0]*m_vVariationWeights[VAR_SPHERICAL];
			fResultY += vTemp[1]*m_vVariationWeights[VAR_SPHERICAL];
		}

		if (m_vVariationWeights[VAR_SWIRL] > 0)
		{
			vector<float> vTemp = Var_Swirl(fTerm1, fTerm2);
			fResultX += vTemp[0]*m_vVariationWeights[VAR_SWIRL];
			fResultY += vTemp[1]*m_vVariationWeights[VAR_SWIRL];
		}

		return { fResultX, fResultY };
	}

	float FFFunction::Calc_R(float fX, float fY) { return sqrt(pow(fX, 2) + pow(fY, 2)); }

	// variations
	
	vector<float> FFFunction::Var_Linear(float fX, float fY) { return { fX, fY }; }
	vector<float> FFFunction::Var_Sinusoidal(float fX, float fY) { return { sin(fX), sin(fY) }; }
	vector<float> FFFunction::Var_Spherical(float fX, float fY) 
	{
		float fR = Calc_R(fX, fY);
		float fCoef = 1 / (pow(fR, 2));

		return { fX*fCoef, fY*fCoef };
	}
	vector<float> FFFunction::Var_Swirl(float fX, float fY)
	{
		float fR = Calc_R(fX, fY);
		float fRSquared = pow(fR, 2);
		float fcosRSquared = cos(fRSquared);
		float fsinRSquared = sin(fRSquared);
		return { fX*fsinRSquared - fY*fcosRSquared, fX*fcosRSquared + fY*fsinRSquared };
	}
}

#endif // FF_FUNCTION_CPP
