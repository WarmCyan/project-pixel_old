//*************************************************************
//  File: FlameFractal.h
//  Date created: 1/28/2017
//  Date edited: 1/29/2017
//  Author: Nathan Martindale
//  Copyright © 2017 Digital Warrior Labs
//  Description: 
//*************************************************************

#ifndef FF_H
#define FF_H

#include <iostream>
#include <vector>
#include <random>

#include "Function.h"

using namespace std;

namespace dwl
{
	class FlameFractal
	{
		private:
			int m_iWidth;
			int m_iHeight;

			float m_fTempR;
			float m_fTempG;
			float m_fTempB;

			float m_fTempX;
			float m_fTempY;

			//float m_fTempC;

			//vector<vector<float[3]> >* m_vPoints;
			vector<vector<vector<float> > >* m_vPoints;
			//int m_aImage[][][3];
			//int m_aFilteredImage[][][3];
			//float m_aFinalImage[1][1][3];
			
			vector<FFFunction> m_vFunctions;

			void PreparePlot();

			void PlotPoint(float fX, float fY, float fC);

			void ColorMap(float fColor);

			void FinalTransform(float fX, float fY);
			float FinalColorTransform(float cX);

			void CopyArray(float** m_aInput, float** *m_aOutput);


			float RandomFloat();
			
		public:

			FlameFractal(int iWidth, int iHeight);

			void AddFunction(FFFunction pFunction) { m_vFunctions.push_back(pFunction); }

			void Solve(int iIterationCount);
			void Render(float fGamma, float fBrightness);

			vector<vector<vector<float> > >* GetImage() { return m_vPoints; }
	};
}

#endif // FF_H
