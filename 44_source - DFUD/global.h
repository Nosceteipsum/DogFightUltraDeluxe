////////////////////////////////////////////////////////////////////
//								  //
//	  	    DFUD: Global			  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#if!defined Global_H
#define Global_H 

#include <winsock2.h>

#include <windows.h>
#include <time.h>

#include "resource.h"

#include "engine\CTimer.h"

#include "engine\windows\CRegEdit.h"
#include "engine\windows\CWinSock.h"

#include "engine\opengl\COpenGl_Math.h"
#include "engine\opengl\COpenGl_Texture_TGA.h"
#include "engine\opengl\COpenGl_Font.h"
#include "engine\opengl\COpenGl_Camera.h"
#include "engine\opengl\COpenGl_Window.h"
#include "engine\directx\CDirectX_Sound.h"

#include "source\winmain.h"

#include "source\game\CGameLoader.h"
#include "source\game\CGameMain.h"
#include "source\game\CGameNetWork.h"

#include "source\CGameHandler.h"




#endif