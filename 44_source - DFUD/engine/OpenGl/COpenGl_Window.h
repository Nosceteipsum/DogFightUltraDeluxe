////////////////////////////////////////////////////////////////////
//								  //
//			OpenGl Window			  	  //
//								  //
//	     Made By: Tommy Kobber� Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#if!defined COpenGl_Window_H
#define COpenGl_Window_H

//----------------------------------//
//--------- Library files ----------//
//----------------------------------//

#pragma comment(linker, "/defaultlib:OpenGl32.lib")

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

LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam, LPARAM lParam);

//----------------------------------//
//------------- Class --------------//
//----------------------------------//

class COpenGl_Window
{
public:

COpenGl_Window();
~COpenGl_Window();

void   CreateGLWindow     (char *,int,int,int,bool,HINSTANCE,HWND *);
void   KillGlWindow       (HWND ,HINSTANCE);
void   SwapBuffers_hdc    ();

LPPOINT GetCursorPosition  ();
void    SetCursorPosition  (int,int);

bool   Error_Check        ();
char  *Get_Error_Message  ();

protected:
private:

HGLRC	hRC;
HDC	hDC;	

LPPOINT Mouse_Point;  

bool    Error_Detected;
char	Error_Message[50];
};
#endif

