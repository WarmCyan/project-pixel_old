//*************************************************************
//  File: ProgressBar.cpp
//  Date created: 2/9/2017
//  Date edited: 7/15/2017
//  Author: Nathan Martindale
//  Copyright © 2017 Digital Warrior Labs
//  Description: Class for displaying task progress on a single line
//*************************************************************

#ifndef PROGBAR_CPP
#define PROGBAR_CPP

#include "ProgressBar.h"

namespace dwl
{
	ProgressBar::ProgressBar(int iTotal, int iSize)
	{
		m_iTotal = iTotal;
		m_iSize = iSize;
		m_iTicks = 0;

		// account for extra characters
		m_iSize -= 6;

		// determine step size
		m_fStepSize = (float)m_iSize / (float)m_iTotal;


		m_iSize = ceil(m_fStepSize * iTotal);

		this->Update(0);
		
		//cout << "Step size: " << m_fStepSize << endl; // DEBUG
		//cout << "Total: " << m_iTotal << endl; // DEBUG
		//cout << "Size: " << m_iSize << endl; // DEBUG

		// set up the end points
		//cout << m_sEndCharacter;
		//for (int i = 0; i < m_iSize - 2; i++) { cout << " "; }
		//cout << m_sEndCharacter << endl;
	}

	void ProgressBar::Update(int iCount)
	{
		m_iTicks = 0;
		int iTickCount = (int)(ceil(iCount * m_fStepSize));
		int iPercentage = ceil(((float)iCount / (float)m_iTotal)*100);
		
		// print percentage
		cout << "\r" << iPercentage << "%";
		if (iPercentage < 10) { cout << "  "; }
		else if (iPercentage < 100) { cout << " "; }
		
		cout << m_sEndCharacter;

		while (m_iTicks < iTickCount)
		{
			cout << m_sTickCharacter;
			m_iTicks++;
		}
		while (m_iTicks < m_iSize)
		{
			cout << " ";
			m_iTicks++;
			
		}
		
		
		cout << m_sEndCharacter << flush;
		/*if (m_iTicks >= m_iSize) 
		{ 
			cout << iCount << " : " << m_iTotal;
			cout << endl; 
		}*/
		/*if (iCount >= m_iTotal)
		{
			cout << endl;
		}*/
	}

	void ProgressBar::Finish()
	{
		cout << endl;
	}
}

#endif // PROGBAR_CPP
