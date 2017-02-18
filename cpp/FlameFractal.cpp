//*************************************************************
//  File: FlameFractal.cpp
//  Date created: 1/28/2017
//  Date edited: 2/18/2017
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

		ProgressBar pBar = ProgressBar(3, m_iProgressBarSize);

		m_vPoints = new vector<vector<vector<float> > >(m_iHeight, vector<vector<float> >(m_iWidth, vector<float>(3, 0)));

		pBar.Update(1);
		
		m_vImage = new vector<vector<vector<float> > >(m_iHeight, vector<vector<float> >(m_iWidth, vector<float>(3, 0)));
		m_vPostProcImage = new vector<vector<vector<float> > >(m_iHeight, vector<vector<float> >(m_iWidth, vector<float>(3, 0)));
		pBar.Update(2);
		
		m_vFinalImage = new vector<vector<vector<int> > >(m_iHeight, vector<vector<int> >(m_iWidth, vector<int>(3, 0)));

		pBar.Update(3);
		pBar.Finish();
	
		cout << "Plot prepared!" << endl;
	}

	void FlameFractal::SetBaseImage(float fR, float fG, float fB, float fA)
	{
		cout << "Setting base color..." << endl;
		for (int y = 0; y < m_vFinalImage->size(); y++)
		{
			for (int x = 0; x < (*m_vFinalImage)[y].size(); x++)
			{
				float fDensity = (*m_vFinalImage)[y][x][3];
				float fR = (*m_vFinalImage)[y][x][0];
				float fG = (*m_vFinalImage)[y][x][1];
				float fB = (*m_vFinalImage)[y][x][2];
			}
		}
		cout << "Base color set!" << endl;
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
		/*m_fTempX = fX * 1000;
		m_fTempY = fY * 1000;*/
		
		//m_fTempX = fX * 640 + 1600;
		//m_fTempY = fY * 640 + 800;
		m_fTempX = fX * 400 + 500;
		m_fTempY = fY * 400 + 500;
	}

	float FlameFractal::FinalColorTransform(float fColor) { return fColor; }

	void FlameFractal::InitializeSolution()
	{
		cout << "Setting initial solution variables..." << endl;
			
		// choose a random starting point
		//float fX = RandomFloat() * 2 - 1;
		//float fY = RandomFloat() * 2 - 1;

		m_fStartX = RandomFloat() * 2 - 1;
		m_fStartY = RandomFloat() * 2 - 1;

		// choose a random starting color
		//float fC = RandomFloat();
		m_fStartC = RandomFloat();
	}

	void FlameFractal::Solve(int iIterationCount)
	{
		//PreparePlot();

		cout << "Solving..." << endl;

		// choose a random starting point
		/*float fX = RandomFloat() * 2 - 1;
		float fY = RandomFloat() * 2 - 1;
		float fX_f = fX;
		float fY_f = fY;

		// choose a random starting color
		float fC = RandomFloat();
		float fC_f = fC; */

		float fX = m_fStartX;
		float fY = m_fStartY;
		float fX_f = fX;
		float fY_f = fY;

		float fC = m_fStartC;
		float fC_f = fC;
		
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
		ProgressBar pBar = ProgressBar(iIterationCount, m_iProgressBarSize);
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

			// store trace information
			m_fTraceX = fX;
			m_fTraceY = fY;
			m_fTraceC = fC;

			// ignore the first 20 iterations, (to allow convergence below size
			// of pixel) then plot each point
			if (iIteration > 20)
			{
				if (fX_f < 0 || fX_f >= m_iWidth || fY_f < 0 || fY_f >= m_iHeight) { continue; }
				PlotPoint(fX_f, fY_f, fC_f);
			}

			pBar.Update(iIteration);
		}
		pBar.Finish();

		cout << "Solving complete!" << endl;
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

	void FlameFractal::Render(float fGamma, float fBrightness, int iFilterMethod)
	{
		cout << "Rendering... (gamma = " << fGamma << ", brightness = " << fBrightness << ")" << endl;

		// FIRST PASS
		cout << "First pass... (gathering data)" << endl;
		int iDensityCounts = 0;
		float fTotalDensity = 0.0f;
		float fMaxDensity = 0.0f;

		ProgressBar pBar1 = ProgressBar(m_vPoints->size() - 1, m_iProgressBarSize);

		//cout << m_vPoints->size() << endl;
		for (int y = 0; y < m_vPoints->size(); y++)
		{
			pBar1.Update(y);
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
		pBar1.Finish();

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
		
		ProgressBar pBar2 = ProgressBar(m_vImage->size() - 1, m_iProgressBarSize);

		for (int y = 0; y < m_vImage->size(); y++)
		{
			pBar2.Update(y);
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
		pBar2.Finish();

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

		
		if (iFilterMethod > 0)
		{
			ProgressBar pBar3 = ProgressBar(m_vPostProcImage->size() - 1, m_iProgressBarSize);
			for (int y = 0; y < m_vPostProcImage->size(); y++)
			{
				pBar3.Update(y);
				//cout << "row " << y << endl;
				for (int x = 0; x < (*m_vPostProcImage)[y].size(); x++)
				{
					float fR = (*m_vImage)[y][x][0];
					float fG = (*m_vImage)[y][x][1];
					float fB = (*m_vImage)[y][x][2];
					float fDensity = (*m_vPoints)[y][x][3];

					float n = fDensity;
					if (n < 1) { n = 1; }

					
					float fStdDev = 0.0f;
					if (iFilterMethod == 1) { fStdDev = 5 * (1 / n); }
					else if (iFilterMethod == 2) { float fStdDev = min(5.0f, fAverageDensity / n); }

					
					//float fStdDev = 5;
					int iSize = max(min((int)fStdDev * 3, 30), 1); // has to be at least 1!

					//cout << fStdDev << endl; // DEBUG
					if (fStdDev > .1)
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
			pBar3.Finish();
		}


		// FOURTH PASS
		cout << "Fourth pass... (final transformations)" << endl;

		ProgressBar pBar4 = ProgressBar(m_vImage->size() - 1, m_iProgressBarSize);

		for (int y = 0; y < m_vImage->size(); y++)
		{
			pBar4.Update(y);
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
		pBar4.Finish();
	}

	void FlameFractal::SaveFunctionCode(string sFileName)
	{
		cout << "Saving function codes to " << sFileName << "_functions.xml..." << endl;
			
		// create the root node
		xml_document* pDoc = new xml_document();
		xml_node pFunctions = pDoc->append_child("Functions");
		
		// get the xml for each individual function
		for (int i = 0; i < m_vFunctions.size(); i++)
		{
			FFFunction pFunction = m_vFunctions[i];

			xml_document* pFunctionDoc = pFunction.GetFunctionXML();
			pFunctions.append_copy(pFunctionDoc->document_element());
		}
		
		// save it!
		pDoc->save_file((sFileName + "_functions.xml").c_str());

		cout << "Functions saved successfully!" << endl;
	}

	void FlameFractal::LoadFunctionCode(string sFileName)
	{
		cout << "Loading function code from " << sFileName << "_functions.xml..." << endl;
		
		// load xml from the file
		xml_document pDoc;
		pDoc.load_file((sFileName + "_functions.xml").c_str());

		// reset list of functions
		ClearFunctions();
		
		// load each individual function into this object
		for (xml_node pFunctionNode = pDoc.document_element().child("Function"); pFunctionNode; pFunctionNode = pFunctionNode.next_sibling("Function"))
		{
			FFFunction* pFunction = new FFFunction();
			pFunction->LoadFromXML(pFunctionNode);
			AddFunction(*pFunction);
		}

		cout << "Functions loaded successfully!" << endl;
	}

	void FlameFractal::SaveImageTrace(string sFileName)
	{
		cout << "Saving image trace..." << endl;
		
		// store meta
		string sSaveData = "";
		sSaveData += to_string(m_iWidth) + "\n";
		sSaveData += to_string(m_iHeight) + "\n";
		sSaveData += to_string(m_fTraceX) + "\n";
		sSaveData += to_string(m_fTraceY) + "\n";
		sSaveData += to_string(m_fTraceC) + "\n";

		ProgressBar pBar = ProgressBar(m_vPoints->size() - 1, m_iProgressBarSize);
		
		for (int y = 0; y < m_vPoints->size(); y++)
		{
			pBar.Update(y);
			for (int x = 0; x < (*m_vPoints)[y].size(); x++)
			{
				float fR = (*m_vPoints)[y][x][0];
				float fG = (*m_vPoints)[y][x][1];
				float fB = (*m_vPoints)[y][x][2];
				float fA = (*m_vPoints)[y][x][3];

				sSaveData += to_string(fR) + "," + to_string(fG) + "," + to_string(fB) + "," + to_string(fA) + "\n";
			}
		}
		pBar.Finish();

		cout << "Writing file..." << endl;
		ofstream pFile;
		pFile.open((sFileName + "_trace.dat").c_str());
		pFile << sSaveData << endl;
		pFile.close();

		cout << "Trace saved successfully!" << endl;
	}

	void FlameFractal::LoadImageTrace(string sFileName)
	{
		cout << "Loading image trace..." << endl;

		ifstream pFile;
		pFile.open((sFileName + "_trace.dat").c_str());

		pFile >> m_iWidth;
		pFile >> m_iHeight;
		pFile >> m_fStartX;
		pFile >> m_fStartY;
		pFile >> m_fStartC;

		int iX = 0;
		int iY = 0;

		ProgressBar pBar = ProgressBar(m_iHeight, m_iProgressBarSize);
		
		while (!pFile.eof())
		{
			string sNextLine;
			pFile >> sNextLine;
			//cout << sNextLine << endl;
			
			// split on comma
			vector<float>* vPoint = new vector<float>();
			stringstream ss(sNextLine);
			float fNum;
			while (ss >> fNum)
			{
				vPoint->push_back(fNum);
				if (ss.peek() == ',') { ss.ignore(); }
			}

			(*m_vPoints)[iY][iX] = *vPoint;
			iX++;
			if (iX == m_iWidth) { iX = 0; iY++; pBar.Update(iY); }
			if (iY == m_iHeight) { break; } // TODO: this really shouldn't be necessary, but it is? Double check logic somewhere here!
		}

		pBar.Finish();

		cout << "Image trace loaded!" << endl;
	}

	void FlameFractal::SaveImageData(string sFileName)
	{
		cout << "Saving image data..." << endl;

		ProgressBar pBar = ProgressBar(m_vFinalImage->size() - 1, m_iProgressBarSize);

		string sSaveData = "{\"width\": " + to_string(m_iWidth) + ", \"height\": " + to_string(m_iHeight) + ",";
		sSaveData += "\"pixels\":[";
		for (int y = 0; y < m_vFinalImage->size(); y++)
		{
			pBar.Update(y);
			sSaveData += "[";
			for (int x = 0; x < (*m_vFinalImage)[y].size(); x++)
			{
				int r = (*m_vFinalImage)[y][x][0];
				int g = (*m_vFinalImage)[y][x][1];
				int b = (*m_vFinalImage)[y][x][2];
				int a = (*m_vFinalImage)[y][x][3];

				sSaveData += "[" + to_string(r) + "," + to_string(g) + "," + to_string(b) + "," + to_string(a) + "]";
				if (x < (*m_vFinalImage)[y].size() - 1) { sSaveData += ","; }
			}
			sSaveData += "]";
			if (y < m_vFinalImage->size() - 1) { sSaveData += ","; }
		}
		pBar.Finish();
		sSaveData += "]}";

		cout << "Writing image data to file..." << endl;
		ofstream fFile;
		fFile.open(sFileName);
		fFile << sSaveData;
		fFile.close();
		cout << "Saving complete!" << endl;
	}
}

#endif // FF_CPP
