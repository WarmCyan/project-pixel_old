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
		m_vImage = new vector<vector<vector<float> > >(m_iHeight, vector<vector<float> >(m_iWidth, vector<float>(3, 0)));
		m_vPostProcImage = new vector<vector<vector<float> > >(m_iHeight, vector<vector<float> >(m_iWidth, vector<float>(3, 0)));
		m_vFinalImage = new vector<vector<vector<int> > >(m_iHeight, vector<vector<int> >(m_iWidth, vector<int>(3, 0)));
	
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

	void FlameFractal::SetBaseImage(float fR, float fG, float fB, float fA)
	{
		/*for (int y = 0; y < m_vImage->size(); y++)
		{
			for (int x = 0; x < (*m_vImage)[y].size(); x++)
			{
				float fDensity = (*m_vImage)[y][x][3];
				float fR = (*m_vImage)[y][x][0];
				float fG = (*m_vImage)[y][x][1];
				float fB = (*m_vImage)[y][x][2];
			}
		}*/
	}

	void FlameFractal::PlotPoint(float fX, float fY, float fC)
	{
		ColorMap(fC);

		int iCoordX = (int) fX;
		int iCoordY = (int) fY;

		//cout << "plotting: " << iCoordX << "," << iCoordY << endl; // DEBUG

		(*m_vPoints)[iCoordY][iCoordX][0] += m_fTempR;
		(*m_vPoints)[iCoordY][iCoordX][1] += m_fTempG;
		(*m_vPoints)[iCoordY][iCoordX][2] += m_fTempB;
		(*m_vPoints)[iCoordY][iCoordX][3] += 1.0f;

		// cout << "density: " << (*m_vPoints)[iCoordY][iCoordX][3] << endl; // DEBUG
	}

	void FlameFractal::ColorMap(float fColor)
	{
		m_fTempR = 1.0f - fColor;
		m_fTempG = 1.0f - (fColor / 2);
		m_fTempB = 1.0f;
	}

	void FlameFractal::FinalTransform(float fX, float fY)
	{
		m_fTempX = fX * 400 + 500;
		m_fTempY = fY * 400 + 500;
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

			//cout << "Point: " << fX_f << "," << fY_f << endl; // DEBUG

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

	void FlameFractal::CopyImage(vector<vector<vector<float> > >* m_vInput, vector<vector<vector<float> > >* m_vOutput)
	{
		for (int y = 0; y < m_vInput->size(); y++)
		{
			for (int x = 0; x < (*m_vInput)[y].size(); x++)
			{
				(*m_vOutput)[y][x] = (*m_vInput)[y][x];
			}
		}
	}

	void FlameFractal::CalculateKernelScalars(float fStdDev)
	{
		m_fKernelScalar = 1 / (2 * PI * pow(fStdDev, 2));
		m_fKernelExpDenom = 2 * pow(fStdDev, 2);
	}
	float FlameFractal::CalculateConvolutionForDistance(int iX, int iY)
	{
		return m_fKernelScalar * exp(-((pow(iX, 2) + pow(iY, 2)) / m_fKernelExpDenom));
	}
	vector<vector<float> >* FlameFractal::CalculateConvolutionMatrix(int iSize, float fStdDev, bool bDebug)
	{
		CalculateKernelScalars(fStdDev);

		int iMatrixSize = iSize * 2 + 1;
		float fMatrixSum = 0.0f; // used for normalization
		vector<vector<float> >* vMatrix = new vector<vector<float > >(iMatrixSize, vector<float>(iMatrixSize, 0));

		if (bDebug) { cout << "iSize: " << iSize << " MatrixSize: " << iMatrixSize << endl; }

		//for (int y = -iSize; y < iSize + 1; y++) // TODO: shouldn't that be iSize + 1?
		for (int y = 0; y < iMatrixSize; y++)
		{
			int iY = y - iSize;
			for (int x = 0; x < iMatrixSize; x++)
			{
				int iX = x - iSize;

				float fConvolutionValue = CalculateConvolutionForDistance(iX, iY);
				(*vMatrix)[y][x] = fConvolutionValue;
				fMatrixSum += fConvolutionValue;
			}
		}

		// normalize
		for (int y = 0; y < iMatrixSize; y++)
		{
			for (int x = 0; x < iMatrixSize; x++)
			{
				(*vMatrix)[y][x] /= fMatrixSum;
				if (bDebug) { cout << "matrix value: " << (*vMatrix)[y][x] << endl; }
			}
		}

		return vMatrix;
	}
	
	void FlameFractal::CalculatePointFactor(int iX, int iY, float fFactor, bool bDebug)
	{
		m_fTempR = 0.0f;
		m_fTempG = 0.0f;
		m_fTempB = 0.0f;

		if (bDebug) { cout << "on coord " << iX << "," << iY << endl; }

		if (iX < m_iWidth && iX >= 0 && iY < m_iHeight && iY >= 0)
		{
			m_fTempR = (*m_vImage)[iY][iX][0] * fFactor;
			m_fTempG = (*m_vImage)[iY][iX][1] * fFactor;
			m_fTempB = (*m_vImage)[iY][iX][2] * fFactor;

			if (bDebug) { cout << (*m_vPoints)[iY][iX][3] << endl; }
		}
	}
	void FlameFractal::FilterPoint(int iX, int iY, vector<vector<float> >* vConvolutionMatrix, bool bDebug)
	{
		float fR = 0.0f;
		float fG = 0.0f;
		float fB = 0.0f;

		for (int ly = 0; ly < vConvolutionMatrix->size(); ly++)
		{
			int iYOffset = ly - floor(vConvolutionMatrix->size() / 2);
			if (bDebug) { cout << "on y offset " << iYOffset << endl; }
			for (int lx = 0; lx < (*vConvolutionMatrix)[ly].size(); lx++)
			{
				int iXOffset = lx - floor((*vConvolutionMatrix)[ly].size() / 2);
				if (bDebug) { cout << "\ton x offset " << iXOffset << endl; }
				if (bDebug) { cout << "\t\t" << (*vConvolutionMatrix)[ly][lx] << endl; }
				CalculatePointFactor(iX + iXOffset, iY + iYOffset, (*vConvolutionMatrix)[ly][lx], bDebug);

				if (bDebug) { cout << "\t\t" << m_fTempR << "," << m_fTempG << "," << m_fTempB << endl; }

				fR += m_fTempR;
				fG += m_fTempG;
				fB += m_fTempB;
			}
		}
		if (bDebug) { cout << fR << "," << fG << "," << fB << endl; }

		m_fTempR = fR;
		m_fTempG = fG;
		m_fTempB = fB;
	}

	void FlameFractal::Render(float fGamma, float fBrightness, bool bSkipFiltering)
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
				if (fDensity > 1) // NOTE: this is technically an error (should be > 0), but I prefer the brightness scalar that results from this
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
		cout << "Second pass... (Resolving colors, applying gamma and brightness corrections)" << endl;

		//CopyImage(m_vPoints, m_vImage);
		for (int y = 0; y < m_vPoints->size(); y++)
		{
			for (int x = 0; x < (*m_vPoints)[y].size(); x++)
			{
				(*m_vImage)[y][x][0] = (*m_vPoints)[y][x][0];
				(*m_vImage)[y][x][1] = (*m_vPoints)[y][x][1];
				(*m_vImage)[y][x][2] = (*m_vPoints)[y][x][2];
				(*m_vImage)[y][x][3] = (*m_vPoints)[y][x][3];
			}
		}			

		for (int y = 0; y < m_vImage->size(); y++)
		{
			for (int x = 0; x < (*m_vImage)[y].size(); x++)
			{
				float fDensity = (*m_vImage)[y][x][3];
				float fR = (*m_vImage)[y][x][0];
				float fG = (*m_vImage)[y][x][1];
				float fB = (*m_vImage)[y][x][2];

				if (fDensity > 1) // NOTE: If this is > 0, get weird white spots. DON'T TOUCH!
				{
					// log-density brightness scalar
					float fLogScalar = log(fDensity) / fDensity;

					// gamma correction
					float fLogScalar_c = pow(fLogScalar, 1 / fGamma);

					// resolve rgb colors and apply brightness scalars
					fR *= fLogScalar_c * fBrightnessScalar;
					fG *= fLogScalar_c * fBrightnessScalar;
					fB *= fLogScalar_c * fBrightnessScalar;

					// cap overflows
					fR = min(255.0f, fR);
					fG = min(255.0f, fG);
					fB = min(255.0f, fB);

					// reassign
					(*m_vImage)[y][x] = { fR, fG, fB, 255.0f };

				}
				(*m_vImage)[y][x][3] = 255.0f;
				//cout << fR << fG << fB << endl;
				//cout << fDensity << endl;
			}
		}

		// THIRD PASS
		
		cout << "Third pass... (Post processing/filtering)" << endl;

		//m_vPostProcImage = m_vImage;
		for (int y = 0; y < m_vImage->size(); y++)
		{
			for (int x = 0; x < (*m_vImage)[y].size(); x++)
			{
				(*m_vPostProcImage)[y][x][0] = (*m_vImage)[y][x][0];
				(*m_vPostProcImage)[y][x][1] = (*m_vImage)[y][x][1];
				(*m_vPostProcImage)[y][x][2] = (*m_vImage)[y][x][2];
				(*m_vPostProcImage)[y][x][3] = (*m_vImage)[y][x][3];
			}
		}			
		
		if (!bSkipFiltering)
		{
			for (int y = 0; y < m_vPostProcImage->size(); y++)
			{
				cout << "row " << y << endl;
				for (int x = 0; x < (*m_vPostProcImage)[y].size(); x++)
				{
					float fR = (*m_vImage)[y][x][0];
					float fG = (*m_vImage)[y][x][1];
					float fB = (*m_vImage)[y][x][2];
					float fDensity = (*m_vPoints)[y][x][3];

					float n = fDensity;
					if (n < 1) { n = 1; }

					//float fStdDev = 10 * (2 / (n + 1));
					float fStdDev = 5 * (1 / n);
					//float fStdDev = 5;
					int iSize = max(min((int)fStdDev * 3, 30), 1); // has to be at least 1!

					//cout << fStdDev << endl; // DEBUG
					if (fStdDev > .01)
					{
						vector<vector<float> >* vMatrix = CalculateConvolutionMatrix(iSize, fStdDev, false);
						FilterPoint(x, y, vMatrix, false);
						fR = m_fTempR;
						fG = m_fTempG;
						fB = m_fTempB;

						delete vMatrix;
					}

					(*m_vPostProcImage)[y][x][0] = fR;
					(*m_vPostProcImage)[y][x][1] = fG;
					(*m_vPostProcImage)[y][x][2] = fB;

					if (fB == 0 && (*m_vImage)[y][x][2] != 0)
					{
						cout << "actual blue for " << x << "," << y << ": " << (*m_vImage)[y][x][2] << endl;
						cout << "WARNING - zeroed" << endl;
						vector<vector<float> >* vMatrix = CalculateConvolutionMatrix(iSize, fStdDev, true);
						FilterPoint(x, y, vMatrix, true);
						return;
					}
				}
			}
		}


		// FOURTH PASS
		cout << "Fourth pass... (final transformations)" << endl;

		for (int y = 0; y < m_vImage->size(); y++)
		{
			for (int x = 0; x < (*m_vImage)[y].size(); x++)
			{
				/*(*m_vFinalImage)[y][x][0] = (int)((*m_vImage)[y][x][0]);
				(*m_vFinalImage)[y][x][1] = (int)((*m_vImage)[y][x][1]);
				(*m_vFinalImage)[y][x][2] = (int)((*m_vImage)[y][x][2]);
				(*m_vFinalImage)[y][x][3] = (int)((*m_vImage)[y][x][3]);*/
				
				(*m_vFinalImage)[y][x][0] = (int)((*m_vPostProcImage)[y][x][0]);
				(*m_vFinalImage)[y][x][1] = (int)((*m_vPostProcImage)[y][x][1]);
				(*m_vFinalImage)[y][x][2] = (int)((*m_vPostProcImage)[y][x][2]);
				(*m_vFinalImage)[y][x][3] = (int)((*m_vPostProcImage)[y][x][3]);
			
				
				//if ((*m_vFinalImage)[y][x][3] != 255)
				/*if ((*m_vImage)[y][x][3] != 255)
				{
					cout << (*m_vImage)[y][x][3] << endl;
					cout << "WARNING - alpha isn't up" << endl;
				}*/
			}
		}
	}
}

#endif // FF_CPP
