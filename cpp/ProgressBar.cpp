#ifndef PROGBAR_CPP
#define PROGBAR_CPP

#include "ProgressBar.h"


namesapce dwl
{
	ProgressBar::ProgressBar(int iTotal, int iSize)
	{
		m_iTotal = iTotal;
		m_iSize = iSize;

		// determine step size
		m_iStepSize = m_iTotal / m_iSize;

		// set up the end points
		cout << ".";
		for (int i = 0; i < m_iSize - 1; i++) { cout << " "; }
		cout << "." << endl;
	}

	void ProgressBar::Update(int iCount)
	{
		int iTickCount = (int)iCount * m_iStepSize;
		while (iTickCount < m_iTicks)
		{
			cout << "|";
			iTickCount++;
		}
	}
}

#endif // PROGBAR_CPP
