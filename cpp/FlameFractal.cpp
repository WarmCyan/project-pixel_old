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

	void FlameFractal::PreparePlot()
	{
		cout << "Preparing plot..." << endl;

		//m_aPoints = new float[m_iHeight][m_iWidth][3];
		//m_vPoints = new vector<vector<float[3]> >(m_iHeight, vector<float[3]>(m_iWidth, 0));
		m_vPoints = new vector<vector<vector<float> > >(m_iHeight, vector<vector<float> >(m_iWidth, vector<float>(3, 0)));
	
		for (int y = 0; y < m_iHeight; y++)
		{
			for (int x = 0; x < m_iWidth; x++)
			{
				/*m_vPoints[y][x][0] = 0.0f;
				m_vPoints[y][x][1] = 0.0f;
				m_vPoints[y][x][2] = 0.0f;
				m_vPoints[y][x][3] = 0.0f;*/

				cout << (*m_vPoints)[y][x][0] << endl;
			}
		}

		cout << "Plot prepared!" << endl;
	}

	void FlameFractal::ColorMap(float fColor)
	{
		m_fTempR = 1.0f - fColor;
		m_fTempG = 1.0f - (fColor / 2);
		m_fTempB = 1.0f;
	}

	void FlameFractal::Solve(int iIterationCount)
	{
		PreparePlot();

		cout << "Solving..." << endl;

		// choose a random starting point
	}
}

#endif // FF_CPP
