#ifndef PROGBAR_H
#define PROGBAR_H

#include <isotream>

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
			ProgressBar(int iTotal);

			void Update(int iCount);
	}
}

#endif // PROGBAR_H
