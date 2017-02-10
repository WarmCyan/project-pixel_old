//*************************************************************
//  File: ProgressBar.cpp
//  Date created: 2/9/2017
//  Date edited: 2/9/2017
//  Author: Nathan Martindale
//  Copyright © 2017 Digital Warrior Labs
//  Description: 
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

		// determine step size
		m_fStepSize = (float)m_iSize / (float)m_iTotal;


		m_iSize = m_fStepSize * iTotal;
		
		//cout << "Step size: " << m_fStepSize << endl; // DEBUG
		//cout << "Total: " << m_iTotal << endl; // DEBUG
		//cout << "Size: " << m_iSize << endl; // DEBUG

		// set up the end points
		cout << ".";
		for (int i = 0; i < m_iSize - 2; i++) { cout << " "; }
		cout << "." << endl;
	}

	void ProgressBar::Update(int iCount)
	{
		int iTickCount = (int)iCount * m_fStepSize;
		//cout << "iTickCount: " << iTickCount << endl; // DEBUG
		//cout << "m_iTicks: " << m_iTicks << endl; // DEBUG
		while (m_iTicks < iTickCount)
		{
			cout << "|";
			m_iTicks++;
		}
		if (m_iTicks == m_iSize) { cout << endl; }
	}
}

#endif // PROGBAR_CPP
