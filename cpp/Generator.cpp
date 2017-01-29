//*************************************************************
//  File: Generator.cpp
//  Date created: 1/28/2017
//  Date edited: 1/28/2017
//  Author: Nathan Martindale
//  Copyright © 2017 Digital Warrior Labs
//  Description: 
//*************************************************************


#include <iostream>

#include "Function.h"

using namespace std;
using namespace dwl;


int main()
{
	cout << "hello world!" << endl;


	FFFunction f = FFFunction();
	f.SetVariationWeight(FFFunction::VAR_LINEAR, 1.0f);
	cout << "Running function..." << endl;
	vector<float> result = f.Run(1.0, 1.0);

	for (int i = 0; i < result.size(); i++)
	{
		cout << result[i] << endl;
	}

	
	return 0;
}
