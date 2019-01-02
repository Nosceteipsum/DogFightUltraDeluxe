////////////////////////////////////////////////////////////////////
//								  //
//			DirectX_Sound			  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#if!defined CDirectX_Sound_H
#define CDirectX_Sound_H

//----------------------------------//
//--------- Library files ----------//
//----------------------------------//

#pragma comment(linker, "/defaultlib:DxErr8.lib")  
#pragma comment(linker, "/defaultlib:dxguid.lib") 

//----------------------------------//
//------------ Defines -------------//
//----------------------------------//

//----------------------------------//
//--------- Include files ----------//
//----------------------------------//

/*
#include <basetsd.h>
#include <DMUtil.h> // Sound
#include <DXUtil.h> // Sound
#include <dxerr8.h>
*/

//----------------------------------//
//------- Prototypes files ---------//
//----------------------------------//

//----------------------------------//
//--------- Class / Struct ---------//
//----------------------------------//

class CDirectX_Sound
{
public:

CDirectX_Sound();
~CDirectX_Sound();

void Play(char *Path,bool Loop);
void Init();
void Deinit();				

bool   Error_Check        ();
char  *Get_Error_Message  ();

protected:
private:

//CMusicSegment    *Sound;
//CMusicManager    *MusicManager;
bool    Error_Detected;
char	Error_Message[50];
};

#endif

