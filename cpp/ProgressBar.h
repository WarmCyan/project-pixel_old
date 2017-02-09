//*************************************************************
//  File: ProgressBar.h
//  Date created: 2/9/2017
//  Date edited: 2/9/2017
//  Author: Nathan Martindale
//  Copyright © 2017 Digital Warrior Labs
//  Description: 
//*************************************************************


#ifndef PROGBAR_H
#define PROGBAR_H

#include <iostream>

using namespace std;

namespace dwl
{
	class ProgressBar
	{
		private:
			//int m_iStep;
			//int m_iPrevStep;
			int m_iTicks;
			int m_iStepSize;

			int m_iSize;
			int m_iTotal;
			
		public:
			ProgressBar(int iTotal, int iSize);

			void Update(int iCount);
	};
}

#endif // PROGBAR_H
