////////////////////////////////////////////////////////////////////
//								  //
//	  	     DFUD: WinMain_h   			  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#if!defined WinMain_H
#define WinMain_H

//--------------------------------------------------------//
//--			Prototypes			--//
//--------------------------------------------------------//

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int);
int CALLBACK Window_Main(HWND,UINT,WPARAM,LPARAM);
int CALLBACK Window_AdvServer(HWND,UINT,WPARAM,LPARAM);

class CGameHandler;
struct SGame;

//--------------------------------------------------------//
//--			Struct/classes			--//
//--------------------------------------------------------//

struct SSetting
{
int FullScreen;
int Resolution;
int Option_BuyTime;
int Option_UdpPort;
int Option_SyncTime;
char Name[75];
char Ip[22];
int UdpPort_Client;
};

class SEngine
{
public:

SEngine();
~SEngine();

void Error_Check();

SSetting        *Setting;

HWND	        hwnd_opengl;
bool 		Keys[256],Exit,Server;
MSG		Msg;

COpenGl_Window      *OpenGl_Window;
COpenGl_Camera      *OpenGl_Camera;
COpenGl_Font        *OpenGl_Font;
COpenGl_Texture_TGA *OpenGl_Texture_TGA;
CDirectX_Sound	    *DirectX_Sound;
CRegEdit            *RegEdit;
CWinSock	    *WinSock;
CTimer              *Timer;
CGameHandler        *GameHandler;
SGame	            *Game;
};


#endif
