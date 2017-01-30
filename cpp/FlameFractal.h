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
#include <cmath>
#include <algorithm>

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
			vector<vector<vector<float> > >* m_vImage;
			vector<vector<vector<float> > >* m_vPostProcImage;
			vector<vector<vector<int> > >* m_vFinalImage;
			//int m_aImage[][][3];
			//int m_aFilteredImage[][][3];
			//float m_aFinalImage[1][1][3];
			
			vector<FFFunction> m_vFunctions;

			void PreparePlot();

			void PlotPoint(float fX, float fY, float fC);

			void ColorMap(float fColor);

			void FinalTransform(float fX, float fY);
			float FinalColorTransform(float cX);

			void CopyImage(vector<vector<vector<float> > >* m_vInput, vector<vector<vector<float> > >* m_vOutput);


			float RandomFloat();

			void SetBaseImage(float fR, float fG, float fB, float fA);
			
		public:

			FlameFractal(int iWidth, int iHeight);

			int GetWidth() { return m_iWidth; }
			int GetHeight() { return m_iHeight; }

			void AddFunction(FFFunction pFunction) { m_vFunctions.push_back(pFunction); }

			void Solve(int iIterationCount);
			void Render(float fGamma, float fBrightness);

			vector<vector<vector<int> > >* GetImage() { return m_vFinalImage; }
	};
}

#endif // FF_H
