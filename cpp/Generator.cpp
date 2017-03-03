//*************************************************************
//  File: Generator.cpp
//  Date created: 1/28/2017
//  Date edited: 3/2/2017
//  Author: Nathan Martindale
//  Copyright © 2017 Digital Warrior Labs
//  Description: 
//*************************************************************


#include <iostream>

#include <cmath>
#include <vector>
#include <string>

#include <fstream>
#include <sstream>

#include "FlameFractal.h"
#include "FunctionGenerator.h"

using namespace std;
using namespace dwl;

void REPL();
int HandleCommand(string sCommand);

FlameFractal* pFractal = new FlameFractal(0,0);
int iCollection = 22;
string sErrorMsg = "";

int main()
{

	REPL();
	return 0;
	
	FlameFractal ff = FlameFractal(1000, 1000);
	
	int iCollection = 22;

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
	
	// colors
	//ff.SetColorRamp({0.0f, 1.0f}, {{1.0f, 1.0f, 1.0f}, {0.0f, 0.5f, 1.0f}}); // nice blue!
	//ff.SetColorRamp({0.0f, 1.0f}, {{1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.5f}}); // greeen?
	//ff.SetColorRamp({0.0f, 0.5f, 1.0f}, {{1.0f, 1.0f, 0.0f}, {0.5f, 0.5f, 0.5f}, {0.7f, 0.4f, 1.0f}}); // TTU!
	//ff.SetColorRamp({0.0f, 0.15f, 0.3f, 0.55f, 0.7f, 1.0f}, {{1.0f, 0.0f, 0.0f}, {1.0f, 0.5f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.5f, 1.0f}, {0.8f, 0.2f, 1.0f}});
	//ff.SetColorRamp({0.0f, 1.0f}, {{1.0f, 1.0f, 1.0f}, {0.7f, 0.4f, 1.0f}}); // purple
	//ff.SetColorRamp({0.0f, 1.0f}, {{1.0f, 1.0f, 1.0f}, {0.5f, 0.2f, 0.7f}}); // deep purple
	ff.SetColorRamp({0.0f, 0.5f, 1.0f}, {{0.0f, 0.5f, 1.0f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.2f, 0.7f}}); // purple'n blue
	

	ff.SetZoom(.4, .4);
	ff.PreparePlot();
	ff.InitializeSolution(); 

	ff.LoadFunctionCode("collection/" + to_string(iCollection));
	//ff.LoadImageTrace("collection/" + to_string(iCollection));
	//ff.SaveFunctionCode("collection/" + to_string(iCollection));
	
	ff.Solve(10000000);
	//ff.SaveImageTrace("collection/" + to_string(iCollection));
	
	// render
	ff.Render(2.8, 1.2, 0);
	ff.SaveImageData("imgdata.json");
	system("python3 ./saveaspng.py");
	string sCopyCommand = "copy \"./render.png\" \"./collection/" + to_string(iCollection) + "_render.png\""; // TODO: make cross platform!!
	system(sCopyCommand.c_str());
	

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

void REPL()
{
	int iResult = 0;
	while (iResult != 2)
	{
		cout << "Pixel> ";
		string sCommand = "";
		//cin >> sCommand;
		getline(cin, sCommand);
		iResult = HandleCommand(sCommand);
		if (iResult == 1) { cout << "ERROR: " << sErrorMsg << endl; }
	}
}

// 0 = normal, 1 = error, 2 = exit
int HandleCommand(string sCommand)
{
	cout << "" << sCommand << endl;

	// split on space (black magic split)
	stringstream ss(sCommand);
	istream_iterator<string> begin(ss);
	istream_iterator<string> end;
	vector<string> vParts(begin, end);
	
	if (vParts[0] == "exit")
	{
		cout << "Have a nice day!" << endl;
		return 2;
	}
	else if (vParts[0] == "init")
	{
		if (vParts.size() != 3) 
		{ 
			sErrorMsg = "Bad arguments!\nFORMAT: init [WIDTH] [HEIGHT]";
			return 1;
		}
		//float fWidth = (float)vParts[1];
		//float fHeight = (float)vParts[2];
		int iWidth = stoi(vParts[1]);
		int iHeight = stoi(vParts[2]);
		cout << "Parsed " << "[Width: " << iWidth << "] [Height: " << iHeight << "]" << endl;
		
		delete pFractal;
		pFractal = new FlameFractal(iWidth, iHeight);
		pFractal->PreparePlot();
		
		return 0;
	}
	else if (vParts[0] == "zoom")
	{
		if (vParts.size() != 3) 
		{ 
			sErrorMsg = "Bad arguments!\nFORMAT: zoom [XSCALAR] [YSCALAR]";
			return 1;
		}
		//float fWidth = (float)vParts[1];
		//float fHeight = (float)vParts[2];
		float fX = stof(vParts[1]);
		float fY = stof(vParts[2]);
		cout << "Parsed " << "[X: " << fX << "] [Y: " << fY << "]" << endl;
		
		pFractal->SetZoom(fX, fY);
		
		return 0;
	}
	else if (vParts[0] == "echo") // for debugging use!
	{
		cout << endl << "========================================" << endl << endl;
		for (int i = 1; i < vParts.size(); i++)
		{
			cout << vParts[i] << " ";
		}
		cout << endl << endl << "========================================" << endl << endl;
		return 0;
	}

	
	sErrorMsg = "Unrecognized command!";
	return 1;
}
