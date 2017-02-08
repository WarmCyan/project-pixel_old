//*************************************************************
//  File: Generator.cpp
//  Date created: 1/28/2017
//  Date edited: 1/29/2017
//  Author: Nathan Martindale
//  Copyright © 2017 Digital Warrior Labs
//  Description: 
//*************************************************************


#include <iostream>

#include <random>
#include <cmath>
#include <vector>
#include <string>
//#include <cstdlib>
//#include <ctime>

#include <fstream>

#include "Function.h"
#include "FlameFractal.h"

#define PI 3.14159265

using namespace std;
using namespace dwl;

void SaveImage(string sFileName, FlameFractal* pFractal);


int main()
{
	cout << "hello world!" << endl;

	// set up functions
	FFFunction f0 = FFFunction();
	f0.SetMatrixCoefficients({ 0.9f, 0.0f, 0.0f, 0.0f, 0.9f, 0.0f });
	f0.SetVariationWeight(FFFunction::VAR_LINEAR, 0.1f);
	f0.SetVariationWeight(FFFunction::VAR_SINUSOIDAL, 0.1f);
	f0.SetVariationWeight(FFFunction::VAR_SPHERICAL, 0.7f);
	f0.SetVariationWeight(FFFunction::VAR_SWIRL, 0.1f);
	f0.SetColor(1.0f);
	f0.SetWeight(1.0f);
	
	FFFunction f1 = FFFunction();
	f1.SetMatrixCoefficients({ 0.5f, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f });
	f1.SetVariationWeight(FFFunction::VAR_LINEAR, 0.4f);
	f1.SetVariationWeight(FFFunction::VAR_SINUSOIDAL, 0.6f);
	f1.SetVariationWeight(FFFunction::VAR_SWIRL, 0.2f);
	f1.SetColor(0.5f);
	f1.SetWeight(0.5f);

	FFFunction f2 = FFFunction();
	f2.SetMatrixCoefficients({ 0.5f, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f });
	f2.SetVariationWeight(FFFunction::VAR_SINUSOIDAL, 0.5f);
	f2.SetVariationWeight(FFFunction::VAR_SPHERICAL, 0.3f);
	f2.SetVariationWeight(FFFunction::VAR_SWIRL, 0.2f);
	f2.SetColor(0.0f);
	f2.SetWeight(1.0f);
	
	FFFunction f5 = FFFunction();
	f5.SetMatrixCoefficients({ 1.1f, 0.0f, 0.0f, 0.0f, 1.1f, 0.0f });
	f5.SetVariationWeight(FFFunction::VAR_SINUSOIDAL, 1.0f);
	f5.SetVariationWeight(FFFunction::VAR_SPHERICAL, 0.3f);
	f5.SetVariationWeight(FFFunction::VAR_SWIRL, 0.2f);
	f5.SetVariationWeight(FFFunction::VAR_LINEAR, 0.5f);
	f5.SetColor(0.4f);
	f5.SetWeight(2.0f);
	
	FFFunction f6 = FFFunction();
	//f6.SetMatrixCoefficients({ 0.2f, 0.0f, 0.2f, 0.0f, 0.2f, 0.2f });
	f6.SetMatrixCoefficients({ 0.4f, 0.2f, 0.2f, 0.2f, 0.4f, 0.2f });
	f6.SetVariationWeight(FFFunction::VAR_SPHERICAL, 0.3f);
	f6.SetVariationWeight(FFFunction::VAR_LINEAR, 0.5f);
	f6.SetColor(0.9f);
	f6.SetWeight(1.0f);
	
	FFFunction f3 = FFFunction();
	f3.SetMatrixCoefficients({ (float)cos(180*PI/180), (float)sin(180*PI/180), 0.0f, -(float)sin(180*PI/180), (float)cos(120*PI/180), 0.0f });
	f3.SetVariationWeight(FFFunction::VAR_LINEAR, 0.8f);
	f3.SetVariationWeight(FFFunction::VAR_SWIRL, 0.2f);
	f3.SetVariationWeight(FFFunction::VAR_SINUSOIDAL, 0.4f);
	f3.SetColor(0.7f);
	f3.SetWeight(5.0f);

	/*FFFunction f3 = FFFunction();
	f3.SetMatrixCoefficients({ (float)cos(120*PI/180), (float)sin(120*PI/180), 0.0f, -(float)sin(120*PI/180), (float)cos(120*PI/180), 0.0f });
	f3.SetVariationWeight(FFFunction::VAR_LINEAR, 1.0f);
	f3.SetColor(0.7f);
	f3.SetWeight(3.0f);
	f3.SetSymmetry(true);
	
	FFFunction f4 = FFFunction();
	f4.SetMatrixCoefficients({ (float)cos(240*PI/180), (float)sin(240*PI/180), 0.0f, -(float)sin(240*PI/180), (float)cos(240*PI/180), 0.0f });
	f4.SetVariationWeight(FFFunction::VAR_LINEAR, 1.0f);
	f4.SetColor(0.7f);
	f4.SetWeight(3.0f);
	f4.SetSymmetry(true);*/


	//FlameFractal ff = FlameFractal(1000, 1000);
	FlameFractal ff = FlameFractal(3200, 1600);
	ff.AddFunction(f0);
	ff.AddFunction(f1);
	ff.AddFunction(f2);
	ff.AddFunction(f5);
	ff.AddFunction(f6);
	ff.AddFunction(f3);
	//ff.AddFunction(f4);

	
	//ff.LoadFunctionCode("Test");
	ff.Solve(1000000);
	//ff.Render(2.2, 1.0, 0);
	ff.SaveImageTrace("Test");

	//SaveImage("imgdata.json", &ff);
	//system("python3 ./saveaspng.py");
	
	
	/*random_device rd;
	srand(rd());
	float fRandom = ((float) rand()) / (float) RAND_MAX;

	cout << "Random: " << fRandom << endl;*/


	//FFFunction f = FFFunction();
	//f.SetVariationWeight(FFFunction::VAR_LINEAR, 1.0f);
	//cout << "Running function..." << endl;
	////vector<float> result = f.Run(1.0, 1.0);
	//f.Run(1.0, 1.0);
	//float x = f.GetResultX();
	//float y = f.GetResultY();
	//cout << "x: " << x << " y: " << y << endl;

	//for (int i = 0; i < result.size(); i++)
	//{
		//cout << result[i] << endl;
	//}

	
	return 0;
}

void SaveImage(string sFileName, FlameFractal* pFractal)
{
	vector<vector<vector<int> > >* vImage = pFractal->GetImage();
	int iWidth = pFractal->GetWidth();
	int iHeight = pFractal->GetHeight();
	//cout << iWidth << endl;
	
	string sSaveData = "{\"width\": " + to_string(iWidth) + ", \"height\": " + to_string(iHeight) + ",";
	sSaveData += "\"pixels\":[";
	for (int y = 0; y < vImage->size(); y++)
	{
		sSaveData += "[";
		for (int x = 0; x  < (*vImage)[y].size(); x++)
		{
			int r = (*vImage)[y][x][0];
			int g = (*vImage)[y][x][1];
			int b = (*vImage)[y][x][2];
			int a = (*vImage)[y][x][3];
			
			//cout << r << endl;
			
			sSaveData += "[" + to_string(r) + "," + to_string(g) + "," + to_string(b) + "," + to_string(a) + "]";

			if (x < (*vImage)[y].size() - 1) { sSaveData += ","; }
		}
		sSaveData += "]";
		if (y < vImage->size() - 1) { sSaveData += ","; }
	}
	sSaveData += "]}";

	cout << "Saving image data..." << endl;
	ofstream fFile;
	fFile.open(sFileName);
	fFile << sSaveData;
	fFile.close();
	cout << "Saving complete!" << endl;
	
	//cout << sSaveData << endl;
}
