//*************************************************************
//  File: FlameFractal.h
//  Date created: 1/28/2017
//  Date edited: 2/14/2017
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
#include <fstream>
#include <sstream>

#include "Function.h"
#include "ProgressBar.h"

#include "lib/pugixml.hpp"

#define PI 3.14159265

using namespace std;
using namespace pugi;

namespace dwl
{
	class FlameFractal
	{
		private:
			int m_iProgressBarSize = 80;
			
			int m_iWidth;
			int m_iHeight;

			float m_fTempR;
			float m_fTempG;
			float m_fTempB;

			float m_fTempX;
			float m_fTempY;

			// used only for solution start (TODO: break out the solve function
			// into initialization and actual solving, since solving can be
			// continued
			float m_fStartX;
			float m_fStartY;
			float m_fStartC;

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


			
		public:

			FlameFractal(int iWidth, int iHeight);

			int GetWidth() { return m_iWidth; }
			int GetHeight() { return m_iHeight; }

			void AddFunction(FFFunction pFunction) { m_vFunctions.push_back(pFunction); }
			void ClearFunctions() { m_vFunctions = vector<FFFunction>(); }

			void PreparePlot();
			void SetBaseImage(float fR, float fG, float fB, float fA);
			void InitializeSolution();
			void Solve(int iIterationCount);
			void Render(float fGamma, float fBrightness, int iFilterMethod);

			// TODO: don't forget, store functions as well!
			void SaveFunctionCode(string sFileName);
			void SaveImageTrace(string sFileName);

			void LoadImageTrace(string sFileName);
			void LoadFunctionCode(string sFileName);

			void SaveImageData(string sFileName);

			vector<vector<vector<int> > >* GetImage() { return m_vFinalImage; } // TODO: not sure if I need this anymore

			void SetProgressBarSize(int iSize) { m_iProgressBarSize = iSize; }
	};
}

#endif // FF_H
