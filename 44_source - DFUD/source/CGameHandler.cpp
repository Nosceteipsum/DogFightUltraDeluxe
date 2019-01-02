////////////////////////////////////////////////////////////////////
//								  //
//	  	  DFUD: CGameHandler_cpp		  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#include "../global.h"

//------------------------------------------------------------------
CGameHandler::CGameHandler()
//------------------------------------------------------------------
{

}

//------------------------------------------------------------------
CGameHandler::~CGameHandler()
//------------------------------------------------------------------
{

}

//------------------------------------------------------------------
bool CGameHandler::Main(SEngine *Engine)
//------------------------------------------------------------------
{
bool Status_Exit = false;

Engine->Timer->Run();

if(Engine->Keys[VK_ESCAPE] == true){return true;}

if(Engine->Server == true) {Status_Exit = ServerHandler(Engine);}
if(Engine->Server == false){Status_Exit = ClientHandler(Engine);}

return Status_Exit;
}

//------------------------------------------------------------------
bool CGameHandler::ServerHandler(SEngine *Engine)
//------------------------------------------------------------------
{
Engine->Game->GameMain->Main(Engine);
Engine->Game->GameNetWork->Server_NetWork_Handle(Engine);
ServerHandleSyns(Engine);

return false;
}

//------------------------------------------------------------------
bool CGameHandler::ClientHandler(SEngine *Engine)
//------------------------------------------------------------------
{

if(Engine->WinSock->Client_CheckForError() == true)return true;
Engine->Game->GameMain->Main(Engine);
Engine->Game->GameNetWork->Client_NetWork_Handle(Engine);
Engine->Game->GameNetWork->Client_NetWork_Handle(Engine);

return false;
}

//------------------------------------------------------------------
void CGameHandler::UnLoad(SEngine *Engine)
//------------------------------------------------------------------
{

Engine->Game->GameLoader->UnLoad(Engine);
delete Engine->Game->GameLoader;
Engine->Game->GameLoader = NULL;

}

//------------------------------------------------------------------
void CGameHandler::Load(SEngine *Engine)
//------------------------------------------------------------------
{

Engine->Game->GameLoader   = new CGameLoader;
Engine->Game->GameLoader->Load(Engine);

Engine->OpenGl_Font->LoadGLFont("data\\font\\font.dat");
Engine->OpenGl_Font->BuildFont();

if(Engine->Setting->Resolution == 0)Engine->OpenGl_Camera->ReSizeGLScene( 640, 480);
if(Engine->Setting->Resolution == 1)Engine->OpenGl_Camera->ReSizeGLScene( 640, 480);
if(Engine->Setting->Resolution == 2)Engine->OpenGl_Camera->ReSizeGLScene( 800, 600);
if(Engine->Setting->Resolution == 3)Engine->OpenGl_Camera->ReSizeGLScene( 800, 600);
if(Engine->Setting->Resolution == 4)Engine->OpenGl_Camera->ReSizeGLScene(1024, 768);
if(Engine->Setting->Resolution == 5)Engine->OpenGl_Camera->ReSizeGLScene(1024, 768);
if(Engine->Setting->Resolution == 6)Engine->OpenGl_Camera->ReSizeGLScene(1280,1024);
if(Engine->Setting->Resolution == 7)Engine->OpenGl_Camera->ReSizeGLScene(1280,1024);
Engine->OpenGl_Camera->InitGL_Values();

Engine->Game->GameLoader->Draw(Engine);
Engine->OpenGl_Window->SwapBuffers_hdc();

Engine->Game->GameMain->LoadTexture(Engine);
UnLoad(Engine);
Engine->DirectX_Sound->Init();

glClearColor(0.0f, 0.0f, 0.3f, 0.0f);

glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			
glEnable(GL_BLEND);										
glAlphaFunc(GL_GREATER,0.1f);							
glEnable(GL_ALPHA_TEST);								
glEnable(GL_TEXTURE_2D);								
glEnable(GL_CULL_FACE);	

srand( (unsigned)time( NULL ) );

Engine->Timer->Init();
}

//------------------------------------------------------------------
void CGameHandler::ServerHandleSyns(SEngine *Engine)
//------------------------------------------------------------------
{
Sync_Timer -= 0.001f * (float)Engine->Timer->GetDeltaMs();
if(Sync_Timer <= 0.0f)
  {
  Sync_Timer = 0.001f * (float)Engine->Setting->Option_SyncTime;
  Engine->Game->GameNetWork->Server_SendSync(Engine);
  }
}