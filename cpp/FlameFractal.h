//*************************************************************
//  File: FlameFractal.h
//  Date created: 1/28/2017
//  Date edited: 2/8/2017
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

#include "lib/pugixml.hpp"

#define PI 3.14159265

using namespace std;
using namespace pugi;

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

			float m_fKernelScalar;
			float m_fKernelExpDenom;

			float m_fTraceX;
			float m_fTraceY;
			float m_fTraceC;

			vector<vector<vector<float> > >* m_vPoints;
			vector<vector<vector<float> > >* m_vImage;
			vector<vector<vector<float> > >* m_vPostProcImage;
			vector<vector<vector<int> > >* m_vFinalImage;
			
			vector<FFFunction> m_vFunctions;

			void PreparePlot();

			void PlotPoint(float fX, float fY, float fC);

			void ColorMap(float fColor);

			void FinalTransform(float fX, float fY);
			float FinalColorTransform(float cX);

			void CopyImage(vector<vector<vector<float> > >* m_vInput, vector<vector<vector<float> > >* m_vOutput);

			// gaussian kernel blur stuff
			void CalculateKernelScalars(float fStdDev);
			float CalculateConvolutionForDistance(int iX, int iY);
			vector<vector<float> >* CalculateConvolutionMatrix(int iSize, float fStdDev, bool bDebug);

			void CalculatePointFactor(int iX, int iY, float fFactor, bool bDebug);
			void FilterPoint(int iX, int iY, vector<vector<float> >* vConvolutionMatrix, bool bDebug);

			float RandomFloat();

			void SetBaseImage(float fR, float fG, float fB, float fA);

			
		public:

			FlameFractal(int iWidth, int iHeight);

			int GetWidth() { return m_iWidth; }
			int GetHeight() { return m_iHeight; }

			void AddFunction(FFFunction pFunction) { m_vFunctions.push_back(pFunction); }
			void ClearFunctions() { m_vFunctions = vector<FFFunction>(); }

			void Solve(int iIterationCount);
			void Render(float fGamma, float fBrightness, int iFilterMethod);

			/*vector<vector<vector<int> > >* GetImageTrace() { return m_vPoints; }
			float GetTraceX() { return m_fTraceX; }
			float GetTraceY() { return m_fTraceY; }
			float GetTraceC() { return m_fTraceC; }*/

			// TODO: don't forget, store functions as well!
			void SaveFunctionCode(string sFileName);
			void SaveImageTrace(string sFileName);

			void LoadFunctionCode(string sFileName);

			vector<vector<vector<int> > >* GetImage() { return m_vFinalImage; }
	};
}

#endif // FF_H
