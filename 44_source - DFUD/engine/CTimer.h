////////////////////////////////////////////////////////////////////
//								  //
//			    CTimer			  	  //
//								  //
//	     Made By: Tommy Kobber� Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#if!defined CTimer_H
#define CTimer_H

//----------------------------------//
//--------- Library files ----------//
//----------------------------------//

//----------------------------------//
//------------ Defines -------------//
//----------------------------------//

//----------------------------------//
//--------- Include files ----------//
//----------------------------------//

#include <windows.h>

//----------------------------------//
//------- Prototypes files ---------//
//----------------------------------//

//----------------------------------//
//------------- Class --------------//
//----------------------------------//

class CTimer
{
public:

CTimer();
~CTimer();

void    Reset();
void    Init();
double  GetDeltaMs();
void    Run();

bool  Error_Check         ();
char *Get_Error_Message   ();

LARGE_INTEGER     m_nTimingFreq;

protected:

private:


LARGE_INTEGER     m_nLastTime;
double            DTick;

bool    Error_Detected;
char	Error_Message[50];
};

#endif

