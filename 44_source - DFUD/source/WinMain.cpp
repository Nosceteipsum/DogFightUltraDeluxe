////////////////////////////////////////////////////////////////////
//								  //
//	  	  DFUD: WinMain_cpp			  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#include "../global.h"

//------------------------------------//
//--	      Global Data	    --//
////////////////////////////////////////

SEngine        *Engine;

//------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hinstance,HINSTANCE hprevinstance,LPSTR lpcmdline,int nshowcmd)
//------------------------------------------------------------------
{
Engine 	        = new SEngine;

DialogBox(hinstance,MAKEINTRESOURCE(IDD_MAIN)  ,NULL,Window_Main);

if(Engine->Exit == false)
  {
  int x,y,bits;
  bool Fullscreen = 0;
  MSG Msg;

  if(Engine->Setting->FullScreen == 1)Fullscreen = 1;
  if(Engine->Setting->Resolution == 0){x =  640;y =  480;bits=16;}
  if(Engine->Setting->Resolution == 1){x =  640;y =  480;bits=32;}
  if(Engine->Setting->Resolution == 2){x =  800;y =  600;bits=16;}
  if(Engine->Setting->Resolution == 3){x =  800;y =  600;bits=32;}
  if(Engine->Setting->Resolution == 4){x = 1024;y =  768;bits=16;}
  if(Engine->Setting->Resolution == 5){x = 1024;y =  768;bits=32;}
  if(Engine->Setting->Resolution == 6){x = 1280;y = 1024;bits=16;}
  if(Engine->Setting->Resolution == 7){x = 1280;y = 1024;bits=32;}

  Engine->GameHandler        = new CGameHandler;
  Engine->WinSock            = new CWinSock;
  Engine->Game               = new SGame;
  Engine->Game->GameMain     = new CGameMain;
  Engine->Game->GameNetWork  = new CGameNetWork;
  Engine->Timer              = new CTimer;

  Engine->OpenGl_Window      = new COpenGl_Window;
  Engine->OpenGl_Texture_TGA = new COpenGl_Texture_TGA;
  Engine->OpenGl_Font        = new COpenGl_Font;
  Engine->OpenGl_Camera      = new COpenGl_Camera;
  Engine->DirectX_Sound	     = new CDirectX_Sound;

  bool Temp_FullScreen = 0;
  if(Engine->Setting->FullScreen == 1)Temp_FullScreen = 1;

  Engine->OpenGl_Window->CreateGLWindow("DFUD",x,y,bits,Temp_FullScreen,hinstance,&Engine->hwnd_opengl);
  Engine->GameHandler->Load(Engine);

  if(Engine->Server == true)
    {
    Engine->Game->GameMain->Net_Id = 0;
    Engine->Game->GameMain->Player[0].Active = true;
    memcpy(Engine->Game->GameMain->Player[0].Name,Engine->Setting->Name,70);
    Engine->WinSock->Server_StartServer(Engine->Setting->Option_UdpPort);
    Engine->Game->GameMain->ResetRound(Engine);
    Engine->GameHandler->Sync_Timer = 0.01f * (float)Engine->Setting->Option_SyncTime;
    Engine->Game->GameMain->Rules.GameState_Waiting = false;
    }

  if(Engine->Server == false)
    {
    Engine->WinSock->Client_Init();
    Engine->WinSock->Client_Connect(Engine->Setting->Ip,Engine->Setting->UdpPort_Client);
    if(Engine->WinSock->Client_CheckForError() == true){MessageBox(NULL,"DFUD: Unable to connect...","Error",MB_OK);Engine->Exit = true;}
    else
      {
      char Temp_Packet[76];
      Temp_Packet[0] = CLIENT_JOIN_PACKET;
      memcpy(Temp_Packet+1,Engine->Setting->Name,70);
      Engine->WinSock->Client_SendData(Temp_Packet,75);
      Engine->Game->GameNetWork->Send_CLIENT_JOIN_PACKET++;
      if(Engine->WinSock->Client_CheckForError() == true){MessageBox(NULL,"DFUD: Unable to send data...","Error",MB_OK);Engine->Exit = true;}
      Engine->Game->GameMain->Rules.GameState_Waiting = true;
      }
    }

  while(Engine->Exit == false && Engine->OpenGl_Window->Error_Check() == false)
    { 
    if(PeekMessage(&Msg,Engine->hwnd_opengl,0,0,PM_REMOVE))
      {
      TranslateMessage(&Msg);
      DispatchMessage(&Msg);
      }
    Engine->Exit = Engine->GameHandler->Main(Engine);
    }

  if(Engine->Server == false && Engine->WinSock->Client_CheckForError() == false)
    {
    char Temp_Packet[2];
    Temp_Packet[0] = CLIENT_QUIT_PACKET;
    Temp_Packet[1] = Engine->Game->GameMain->Net_Id;
    Engine->WinSock->Client_SendData(Temp_Packet,2);
    Engine->Game->GameNetWork->Send_CLIENT_QUIT_PACKET++;
    }
  if(Engine->Server == true && Engine->WinSock->Client_CheckForError() == false)
    {
    char Temp_Packet[1];
    Temp_Packet[0] = SERVER_QUIT_PACKET;

    for(char i = 1;i<=11;i++)
      {
      if(Engine->Game->GameMain->Player[i].Active == true)
        {
        Engine->WinSock->Server_LoadIP(i);
        Engine->WinSock->Server_SendData(Temp_Packet,1);
	Engine->Game->GameNetWork->Send_SERVER_QUIT_PACKET++;
        }
      }
    }

  Engine->Error_Check();

  Engine->OpenGl_Window->KillGlWindow(Engine->hwnd_opengl,hinstance);
  Engine->Game->GameMain->UnLoadTexture(Engine);

  if(Engine->Server == false)Engine->WinSock->Client_ShutDown();
  if(Engine->Server == true )Engine->WinSock->Server_DeInit();

  delete Engine->Game->GameNetWork;
  delete Engine->Game->GameMain;
  delete Engine->Game;
  delete Engine->Timer;
  delete Engine->OpenGl_Font;
  delete Engine->OpenGl_Camera;
  delete Engine->OpenGl_Texture_TGA;
  delete Engine->DirectX_Sound;

  delete Engine->WinSock;
  delete Engine->OpenGl_Window;
  delete Engine->GameHandler;
  }

delete Engine;

return 0;
}

//--------------------------------------------------------
int CALLBACK Window_Main(HWND hwnd,UINT msg,WPARAM wParam, LPARAM lParam)
//--------------------------------------------------------
{
switch(msg)
  {
  case WM_INITDIALOG:
    {
    SendMessage(hwnd,WM_SETICON,ICON_SMALL,(LPARAM)LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON1)));
    SendMessage(hwnd,WM_SETICON,ICON_BIG,(LPARAM)LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON1)));

    PostMessage(GetDlgItem(hwnd,IDC_NAME),EM_SETLIMITTEXT,70,0);
    PostMessage(GetDlgItem(hwnd,IDC_IP),EM_SETLIMITTEXT,19,0);
    PostMessage(GetDlgItem(hwnd,IDC_UDPPORT_CLIENT),EM_SETLIMITTEXT,5,0);

    SendDlgItemMessage(hwnd,IDC_RESOLUTION,CB_ADDSTRING,0,(LPARAM)" 640*480*16");
    SendDlgItemMessage(hwnd,IDC_RESOLUTION,CB_ADDSTRING,0,(LPARAM)" 800*600*16");
    SendDlgItemMessage(hwnd,IDC_RESOLUTION,CB_ADDSTRING,0,(LPARAM)"1024*768*16");
    SendDlgItemMessage(hwnd,IDC_RESOLUTION,CB_ADDSTRING,0,(LPARAM)"1280*1024*16");

    SendDlgItemMessage(hwnd,IDC_RESOLUTION,CB_ADDSTRING,0,(LPARAM)" 640*480*32");
    SendDlgItemMessage(hwnd,IDC_RESOLUTION,CB_ADDSTRING,0,(LPARAM)" 800*600*32");
    SendDlgItemMessage(hwnd,IDC_RESOLUTION,CB_ADDSTRING,0,(LPARAM)"1024*768*32");
    SendDlgItemMessage(hwnd,IDC_RESOLUTION,CB_ADDSTRING,0,(LPARAM)"1280*1024*32");

    memcpy(Engine->Setting->Name,"Death Knight",20);
    memcpy(Engine->Setting->Ip,"www.logicwork.net",20);
    Engine->Setting->FullScreen = 1;
    Engine->Setting->Resolution = 4;
    Engine->Setting->UdpPort_Client = 5002;

    Engine->RegEdit->LoadText("DFUD","Name",             Engine->Setting->Name,70);
    Engine->RegEdit->LoadText("DFUD","Ip",               Engine->Setting->Ip,20);
    Engine->RegEdit->LoadNumber("DFUD","FullScreen",    &Engine->Setting->FullScreen);
    Engine->RegEdit->LoadNumber("DFUD","Resolution",    &Engine->Setting->Resolution);
    Engine->RegEdit->LoadNumber("DFUD","UdpPort_Client",&Engine->Setting->UdpPort_Client);

    char Temp_Text[12];
    itoa(Engine->Setting->UdpPort_Client,Temp_Text,10);

    SetDlgItemText(hwnd,IDC_UDPPORT_CLIENT,Temp_Text);
    SetDlgItemText(hwnd,IDC_NAME,Engine->Setting->Name);
    SetDlgItemText(hwnd,IDC_IP,  Engine->Setting->Ip);
    if(Engine->Setting->FullScreen == 1)CheckDlgButton(hwnd,IDC_FULLSCREEN,BST_CHECKED);
    if(Engine->Setting->FullScreen == 0)CheckDlgButton(hwnd,IDC_FULLSCREEN,BST_UNCHECKED);
    SendDlgItemMessage(hwnd,IDC_RESOLUTION,CB_SETCURSEL,Engine->Setting->Resolution, 0 );

    return true;
    }
  break;

  case WM_CLOSE:
    {
    Engine->Setting->Resolution = (char)SendDlgItemMessage(hwnd,IDC_RESOLUTION,CB_GETCURSEL, 0, 0 );

    if(BST_CHECKED == IsDlgButtonChecked(hwnd,IDC_FULLSCREEN)){Engine->Setting->FullScreen = 1;}
    else {Engine->Setting->FullScreen = 0;}

    GetDlgItemText(hwnd,IDC_NAME,Engine->Setting->Name,70);
    GetDlgItemText(hwnd,IDC_IP,Engine->Setting->Ip,20);
    char Temp_Text[12];
    GetDlgItemText(hwnd,IDC_UDPPORT_CLIENT,Temp_Text,6);
    Engine->Setting->UdpPort_Client = atoi(Temp_Text);

    Engine->RegEdit->SaveText("DFUD","Name",		      Engine->Setting->Name,70);
    Engine->RegEdit->SaveText("DFUD","Ip",		      Engine->Setting->Ip,19);
    Engine->RegEdit->SaveNumber("DFUD","FullScreen",    (char *)Engine->Setting->FullScreen);
    Engine->RegEdit->SaveNumber("DFUD","Resolution",    (char *)Engine->Setting->Resolution);
    Engine->RegEdit->SaveNumber("DFUD","UdpPort_Client",(char *)Engine->Setting->UdpPort_Client);
    EndDialog(hwnd,0);

    return false;
    }
  break;

  case WM_COMMAND:
    {
    if(wParam == IDC_QUIT)
      {
      SendMessage(hwnd,WM_CLOSE,NULL,NULL);
      }

    if(wParam == IDC_SERVER)
      {
      DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_SERVER_OPTION),NULL,Window_AdvServer);
      if(Engine->Server == true)
        {
        Engine->Exit   = false;
        Engine->Server = true;
        SendMessage(hwnd,WM_CLOSE,NULL,NULL);
	}
      }

    if(wParam == IDC_CLIENT)
      {
      Engine->Exit   = false;
      Engine->Server = false;
      SendMessage(hwnd,WM_CLOSE,NULL,NULL);
      }

    }

  default:
  return false;
  break;
  }
return false;
}

//------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam, LPARAM lParam)
//------------------------------------------------------------------
{
switch(msg)
  {
  case WM_DESTROY:
    {
    Engine->Exit = true;
    PostQuitMessage(0);
    return 0;
    }
  break;

  case WM_CREATE:
    {
    SendMessage(hwnd,WM_SETICON,ICON_SMALL,(LPARAM)LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON1)));
    SendMessage(hwnd,WM_SETICON,ICON_BIG,(LPARAM)LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON1)));
    }
  break;

  case WM_KEYDOWN:
    {
    Engine->Keys[wParam] = true;				
    return 0;				
    }
  break;

  case WM_KEYUP:
    {
    Engine->Keys[wParam] = false;				
    return 0;					
    }
  break;

  default:
  return DefWindowProc(hwnd,msg,wParam,lParam);   
  break;
  }

return 0;
}

//------------------------------------------------------------------
SEngine::SEngine()
//------------------------------------------------------------------
{
Setting = new SSetting;
RegEdit = new CRegEdit;

Exit    = true;
Server  = false;
for(int i=0;i<=255;i++)Keys[i] = false;
}

//------------------------------------------------------------------
SEngine::~SEngine()
//------------------------------------------------------------------
{
delete Engine->RegEdit;
delete Engine->Setting;
}

//------------------------------------------------------------------
void SEngine::Error_Check()
//------------------------------------------------------------------
  {
  if(Engine->OpenGl_Window->Error_Check()      == true)MessageBox(NULL,Engine->OpenGl_Window->Get_Error_Message(),"Error",MB_OK);
  if(Engine->OpenGl_Camera->Error_Check()      == true)MessageBox(NULL,Engine->OpenGl_Camera->Get_Error_Message(),"Error",MB_OK);

  if(Engine->OpenGl_Font->Error_Check()        == true)MessageBox(NULL,Engine->OpenGl_Font->Get_Error_Message(),"Error",MB_OK);
  if(Engine->OpenGl_Camera->Error_Check()      == true)MessageBox(NULL,Engine->OpenGl_Camera->Get_Error_Message(),"Error",MB_OK);
  if(Engine->Timer->Error_Check()	       == true)MessageBox(NULL,Engine->Timer->Get_Error_Message(),"Error",MB_OK);
  if(Engine->OpenGl_Texture_TGA->Error_Check() == true)MessageBox(NULL,Engine->OpenGl_Texture_TGA->Get_Error_Message(),"Error",MB_OK);
  if(Engine->WinSock->Error_Check()	       == true)MessageBox(NULL,Engine->WinSock->Get_Error_Message(),"Error",MB_OK);
  if(Engine->DirectX_Sound->Error_Check()      == true)MessageBox(NULL,Engine->DirectX_Sound->Get_Error_Message(),"Error",MB_OK);
  }
//--------------------------------------------------------
int CALLBACK Window_AdvServer(HWND hwnd,UINT msg,WPARAM wParam, LPARAM lParam)
//--------------------------------------------------------
{
switch(msg)
  {
  case WM_INITDIALOG:
  {
  SendMessage(hwnd,WM_SETICON,ICON_SMALL,(LPARAM)LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON1)));
  SendMessage(hwnd,WM_SETICON,ICON_BIG,(LPARAM)LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON1)));

  PostMessage(GetDlgItem(hwnd,IDC_SYNCTIME),EM_SETLIMITTEXT,3,0);
  PostMessage(GetDlgItem(hwnd,IDC_BUYTIME),EM_SETLIMITTEXT,2,0);
  PostMessage(GetDlgItem(hwnd,IDC_UDPPORT),EM_SETLIMITTEXT,5,0);

  Engine->Setting->Option_SyncTime = 50;
  Engine->Setting->Option_BuyTime  = 5;
  Engine->Setting->Option_UdpPort  = 5002;

  Engine->RegEdit->LoadNumber("DFUD","SyncTime",&Engine->Setting->Option_SyncTime);
  Engine->RegEdit->LoadNumber("DFUD","BuyTime",&Engine->Setting->Option_BuyTime);
  Engine->RegEdit->LoadNumber("DFUD","UdpPort",&Engine->Setting->Option_UdpPort);

  Engine->Setting->Option_SyncTime = 50;

  char Temp_Text[12];

  itoa(Engine->Setting->Option_SyncTime,Temp_Text,10);
  SetDlgItemText(hwnd,IDC_SYNCTIME,Temp_Text);
  itoa(Engine->Setting->Option_BuyTime,Temp_Text,10);
  SetDlgItemText(hwnd,IDC_BUYTIME,Temp_Text);
  itoa(Engine->Setting->Option_UdpPort,Temp_Text,10);
  SetDlgItemText(hwnd,IDC_UDPPORT,Temp_Text);

  return true;
  }
  break;

  case WM_CLOSE:

  EndDialog(hwnd,0);

  return false;
  break;

  case WM_COMMAND:
    {
    if(wParam == IDC_LAUNCH)
      {
      char Temp_Text[12];

      GetDlgItemText(hwnd,IDC_SYNCTIME,(char *)Temp_Text,4);
      Engine->Setting->Option_SyncTime = atoi(Temp_Text);
      Engine->RegEdit->SaveNumber("DFUD","SyncTime",(char *)Engine->Setting->Option_SyncTime);
      GetDlgItemText(hwnd,IDC_BUYTIME,(char *)Temp_Text,3);
      Engine->Setting->Option_BuyTime = atoi(Temp_Text);
      Engine->RegEdit->SaveNumber("DFUD","BuyTime",(char *)Engine->Setting->Option_BuyTime);
      GetDlgItemText(hwnd,IDC_UDPPORT,(char *)Temp_Text,7);
      Engine->Setting->Option_UdpPort = atoi(Temp_Text);
      Engine->RegEdit->SaveNumber("DFUD","UdpPort",(char *)Engine->Setting->Option_UdpPort);

      Engine->Server = true;
      SendMessage(hwnd,WM_CLOSE,NULL,NULL);
      }
    if(wParam == IDC_BACK)
      {
      SendMessage(hwnd,WM_CLOSE,NULL,NULL);
      }
    }
  default:
  return false;
  break;
  }
return false;
}