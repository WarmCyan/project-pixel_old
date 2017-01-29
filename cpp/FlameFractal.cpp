//*************************************************************
//  File: FlameFractal.cpp
//  Date created: 1/28/2017
//  Date edited: 1/29/2017
//  Author: Nathan Martindale
//  Copyright © 2017 Digital Warrior Labs
//  Description: 
//*************************************************************

#ifndef FF_CPP
#define FF_CPP

#include "FlameFractal.h"

using namespace std;

namespace dwl
{

	FlameFractal::FlameFractal(int iWidth, int iHeight)
	{
		m_iWidth = iWidth;
		m_iHeight = iHeight;

		//m_vFunctions = new vector<FFFunction>();

		m_fTempR = 0.0f;
		m_fTempG = 0.0f;
		m_fTempB = 0.0f;

		m_fTempX = 0.0f;
		m_fTempY = 0.0f;
	}

	float FlameFractal::RandomFloat()
	{
		random_device rd;
		srand(rd());
		float fRandom = ((float) rand()) / (float) RAND_MAX;

		return fRandom;
	}

	void FlameFractal::PreparePlot()
	{
		cout << "Preparing plot..." << endl;

		//m_aPoints = new float[m_iHeight][m_iWidth][3];
		//m_vPoints = new vector<vector<float[3]> >(m_iHeight, vector<float[3]>(m_iWidth, 0));
		m_vPoints = new vector<vector<vector<float> > >(m_iHeight, vector<vector<float> >(m_iWidth, vector<float>(3, 0)));
	
		/*for (int y = 0; y < m_iHeight; y++)
		{
			for (int x = 0; x < m_iWidth; x++)
			{
				m_vPoints[y][x][0] = 0.0f;
				m_vPoints[y][x][1] = 0.0f;
				m_vPoints[y][x][2] = 0.0f;
				m_vPoints[y][x][3] = 0.0f;

				//cout << (*m_vPoints)[y][x][0] << endl;
			}
		}*/

		cout << "Plot prepared!" << endl;
	}

	void FlameFractal::PlotPoint(float fX, float fY, float fC)
	{
		ColorMap(fC);

		(*m_vPoints)[(int) fY][(int) fX][0] = m_fTempR;
		(*m_vPoints)[(int) fY][(int) fX][1] = m_fTempG;
		(*m_vPoints)[(int) fY][(int) fX][2] = m_fTempB;
		(*m_vPoints)[(int) fY][(int) fX][3] += 1.0f;
	}

	void FlameFractal::ColorMap(float fColor)
	{
		m_fTempR = 1.0f - fColor;
		m_fTempG = 1.0f - (fColor / 2);
		m_fTempB = 1.0f;
	}

	void FlameFractal::FinalTransform(float fX, float fY)
	{
		m_fTempX = fX * 200 + 250;
		m_fTempY = fY * 200 + 250;
	}

	float FlameFractal::FinalColorTransform(float fColor) { return fColor; }

	void FlameFractal::Solve(int iIterationCount)
	{
		PreparePlot();

		cout << "Solving..." << endl;

		// choose a random starting point
		float fX = RandomFloat() * 2 - 1;
		float fY = RandomFloat() * 2 - 1;
		float fX_f = fX;
		float fY_f = fY;

		// choose a random starting color
		float fC = RandomFloat();
		float fC_f = fC; 

		int iDisplayStep = (int) (iIterationCount / 100.0f);
		
		vector<int>* vFunctionCounts = new vector<int>(m_vFunctions.size(), 0);
			
		// determine the weighting of each function (out of 1 total)
		vector<float>* vFunctionWeights = new vector<float>(m_vFunctions.size(), 0.0f);
		float fFunctionWeightsTotal = 0.0f;


		// first pass just to get total weight
		for (int i = 0; i < m_vFunctions.size(); i++) { fFunctionWeightsTotal += m_vFunctions[i].GetWeight(); }

		// second pass to normalize the function weights 
		float fSumSoFar = 0.0f;
		for (int i = 0; i < m_vFunctions.size(); i++)
		{
			float fNormalizedWeight = m_vFunctions[i].GetWeight() / fFunctionWeightsTotal;
			fSumSoFar += fNormalizedWeight;
			(*vFunctionWeights)[i] = fSumSoFar;
		}

		// display function weight "cdf"
		cout << "Cumulative function weights: [";
		for (int i = 0; i < vFunctionWeights->size(); i++)
		{
			cout << (*vFunctionWeights)[i];
			if (i < vFunctionWeights->size() - 1) { cout << ", "; }
		}
		cout << "]" << endl;

		// run the chaos game!
		for (int iIteration = 0; iIteration <= iIterationCount; iIteration++)
		{
			// choose a random function
			float fDice = RandomFloat();
			int iSelectedFunction = 0;
			while (fDice > (*vFunctionWeights)[iSelectedFunction]) { iSelectedFunction++; }
			(*vFunctionCounts)[iSelectedFunction]++;

			// run the function
			m_vFunctions[iSelectedFunction].Run(fX, fY);
			fX = m_vFunctions[iSelectedFunction].GetResultX();
			fY = m_vFunctions[iSelectedFunction].GetResultY();

			// run final transform
			FinalTransform(fX, fY);
			fX_f = m_fTempX;
			fY_f = m_fTempY;

			// run color stuff if the running function isn't a symmetry function
			if (!m_vFunctions[iSelectedFunction].IsSymmetry())
			{
				fC = (fC + m_vFunctions[iSelectedFunction].GetColor()) / 2.0f;
				fC_f = (fC + FinalColorTransform(fC)) / 2.0f;
			}

			// ignore the first 20 iterations, (to allow convergence below size
			// of pixel) then plot each point
			if (iIteration > 20)
			{
				if (fX_f < 0 || fX_f >= m_iWidth || fY_f < 0 || fY_f >= m_iHeight) { continue; }
				PlotPoint(fX_f, fY_f, fC_f);
			}

			if (iIteration % iDisplayStep == 0) { cout << "Completed iteration " << iIteration << endl; }
		}
	}

	void FlameFractal::Render(float fGamma, float fBrightness)
	{
		cout << "Rendering... (gamma = " << fGamma << ", brightness = " << fBrightness << ")" << endl;

		// FIRST PASS
		cout << "First pass... (gathering data)" << endl;
		int iDensityCounts = 0;
		float fTotalDensity = 0.0f;
		float fMaxDensity = 0.0f;

		//cout << m_vPoints->size() << endl;
		for (int y = 0; y < m_vPoints->size(); y++)
		{
			for (int x = 0; x < (*m_vPoints)[y].size(); x++)
			{
				float fDensity = (*m_vPoints)[y][x][3];
				if (fDensity > 0)
				{
					if (fDensity > fMaxDensity) { fMaxDensity = fDensity; }
					fTotalDensity += fDensity;
					iDensityCounts++;
				}
			}
		}

		float fAverageDensity = fTotalDensity / (float) iDensityCounts;
		cout << "Average density: " << fAverageDensity << endl;
		cout << "Highest density: " << fMaxDensity << endl;

		float fBrightnessScalar = (255 / fAverageDensity) * fBrightness;
		cout << "Brightness scalar: " << fBrightnessScalar << endl;

		
		// SECOND PASS
		
		
	}
}

#endif // FF_CPP
