//*************************************************************
//  File: Generator.cpp
//  Date created: 1/28/2017
//  Date edited: 2/21/2017
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
#include "ProgressBar.h"
#include "FunctionGenerator.h"

#define PI 3.14159265

using namespace std;
using namespace dwl;

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

	

	FlameFractal ff = FlameFractal(1000, 1000);

	
	//FlameFractal ff = FlameFractal(3200, 1600);
	/*ff.AddFunction(f0);
	ff.AddFunction(f1);
	ff.AddFunction(f2);
	ff.AddFunction(f5);
	ff.AddFunction(f6);
	ff.AddFunction(f3);*/
	//ff.AddFunction(f4);
	
	int iCollection = 8;
	
	/*FunctionGenerator pGen = FunctionGenerator();
	FFFunction* pF0 = pGen.GenerateFunction();
	ff.AddFunction(*pF0);
	FFFunction* pF1 = pGen.GenerateFunction();
	ff.AddFunction(*pF1);
	FFFunction* pF2 = pGen.GenerateFunction();
	ff.AddFunction(*pF2);
	FFFunction* pF3 = pGen.GenerateFunction();
	ff.AddFunction(*pF3);

	FFFunction* pFSym = pGen.GenerateSymmetryFunction(120);
	pFSym->SetWeight(pF0->GetWeight() + pF1->GetWeight() + pF2->GetWeight() + pF3->GetWeight());
	ff.AddFunction(*pFSym);
	FFFunction* pFSym2 = pGen.GenerateSymmetryFunction(240);
	pFSym2->SetWeight(pF0->GetWeight() + pF1->GetWeight() + pF2->GetWeight() + pF3->GetWeight());
	ff.AddFunction(*pFSym2);*/
	
	
	ff.SetZoom(.4, .4);
	ff.PreparePlot();
	ff.InitializeSolution(); // NOTE: this is where zoom stuff should be set.
	//Zoom factors should be stored with trace!
	ff.LoadFunctionCode("collection/" + to_string(iCollection));
	//ff.LoadImageTrace("collection/" + to_string(iCollection));
	//ff.SaveFunctionCode("collection/" + to_string(iCollection));
	ff.Solve(500000000);
	ff.Render(3.2, 1.0, 0);
	ff.SaveImageTrace("collection/" + to_string(iCollection));
	ff.SaveImageData("imgdata.json");
	system("python3 ./saveaspng.py");
	

	/*int iPart = 1;
	
	// part 1
	if (iPart == 1)
	{
		ff.PreparePlot();
		ff.InitializeSolution();
		ff.Solve(10000000);
		ff.Render(2.2, 1.0, 0);
		ff.SaveImageTrace("Test");
		ff.SaveImageData("imgdata.json");
		ff.SaveFunctionCode("TestFunctions");
		system("python3 ./saveaspng.py");
	}
	
	// part 2
	if (iPart == 2)
	{
		ff.PreparePlot();
		ff.LoadImageTrace("Test");
		ff.Solve(100000000);
		ff.Render(2.2, 1.0, 0);
		ff.SaveImageTrace("Test");
		ff.SaveImageData("imgdata.json");
		system("python3 ./saveaspng.py");
	}*/
	
	//ff.SetBaseImage(100.0f, 0.0f, 0.0f, 255.0f);
	//ff.LoadFunctionCode("Test");
	//ff.SaveImageTrace("Test");
	//ff.LoadImageTrace("Test");

	//SaveImage("imgdata.json", &ff);
	
	
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
