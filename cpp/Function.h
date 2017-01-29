//*************************************************************
//  File: Function.h
//  Date created: 1/28/2017
//  Date edited: 1/29/2017
//  Author: Nathan Martindale
//  Copyright © 2017 Digital Warrior Labs
//  Description: 
//*************************************************************

#ifndef FF_FUNCTION_H
#define FF_FUNCTION_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

namespace dwl
{
	class FFFunction
	{
		private:
			float m_fColor;
			float m_fWeight;

			bool m_bIsSymmetry;

			float m_fTempX;
			float m_fTempY;

			float m_fResultX;
			float m_fResultY;

			vector<float> m_vMatrixCoefficients;
			vector<float> m_vVariationWeights;
			//float* m_vMatrixCoefficients;
			//float* m_vVariationWeights;

			float Calc_R(float fX, float fY);
			
			// variation functions
			void Var_Linear(float fX, float fY);
			void Var_Sinusoidal(float fX, float fY);
			void Var_Spherical(float fX, float fY);
			void Var_Swirl(float fX, float fY);
			
		public:

			static const int VAR_LINEAR = 0;
			static const int VAR_SINUSOIDAL = 1;
			static const int VAR_SPHERICAL = 2;
			static const int VAR_SWIRL = 3;
			
			FFFunction();
			void Run(float fX, float fY);

			void SetSymmetry(bool bIsSymmetry) { m_bIsSymmetry = bIsSymmetry; }
			bool IsSymmetry() { return m_bIsSymmetry; }

			vector<float> GetVariationWeights() { return m_vVariationWeights; }
			void SetVariationWeights(vector<float> aVariationWeights) { m_vVariationWeights = aVariationWeights; }
			void SetVariationWeight(int iVariation, float fWeight) { m_vVariationWeights[iVariation] = fWeight; }

			void SetMatrixCoefficients(vector<float> aMatrixCoefficients) { m_vMatrixCoefficients = aMatrixCoefficients; }

			float GetResultX() { return m_fResultX; }
			float GetResultY() { return m_fResultY; }

			string FunctionInfo();	 
	};
}
#endif // FF_FUNCTION_H
