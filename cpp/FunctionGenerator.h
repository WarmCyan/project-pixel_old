//*************************************************************
//  File: FunctionGenerator.h
//  Date created: 2/19/2017
//  Date edited: 2/19/2017
//  Author: Nathan Martindale
//  Copyright © 2017 Digital Warrior Labs
//  Description: 
//*************************************************************

#ifndef FF_FUNCTION_GENERATOR_H
#define FF_FUNCTION_GENERATOR_H

#include "Function.h"
#include <random>

namespace dwl
{
	class FunctionGenerator
	{
		private:	
			float RandomFloat();
			
		public:
			FFFunction* GenerateFunction();
	};
}


#endif
