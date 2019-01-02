////////////////////////////////////////////////////////////////////
//								  //
//	  	  DFUD: CGameHandler_cpp		  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#include "../../global.h"

//--------------------------------------------------------------------------------
char *CGameLoader::Get_Error_Message(){return Error_Message;}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
bool CGameLoader::Error_Check(){return Error_Detected;}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
void CGameLoader::Draw(SEngine *Engine)
//--------------------------------------------------------------------------------
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity();							
glTranslatef(-0.3f,0.0f,-15.0f); 

glBindTexture(GL_TEXTURE_2D,Loader_TGA.texID);
glBegin(GL_QUADS);						
glTexCoord2f(0.0f, 0.0f); glVertex3f(-7.0f,-2.0f,+0.0f);	
glTexCoord2f(1.0f, 0.0f); glVertex3f(+7.0f,-2.0f,+0.0f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(+7.0f,+2.0f,-0.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-7.0f,+2.0f,-0.0f);	
glEnd(); 

if(Engine->Server == true) Engine->OpenGl_Font->glPrint(250,400,"Loading Data...",1);
if(Engine->Server == false)Engine->OpenGl_Font->glPrint(250,400,"Connecting...",1);
}

//--------------------------------------------------------------------------------
void CGameLoader::Load(SEngine *Engine)
//--------------------------------------------------------------------------------
{
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			
glEnable(GL_BLEND);

Loader_TGA.imageData = NULL;

Engine->OpenGl_Texture_TGA->LoadTGA(&Loader_TGA,"data\\loading\\loading.dat",0);
}

//--------------------------------------------------------------------------------
void CGameLoader::UnLoad(SEngine *Engine)
//--------------------------------------------------------------------------------
{
Engine->OpenGl_Texture_TGA->FreeTGA(&Loader_TGA);
}

//--------------------------------------------------------------------------------
CGameLoader::CGameLoader()
//--------------------------------------------------------------------------------
{

}

//--------------------------------------------------------------------------------
CGameLoader::~CGameLoader()
//--------------------------------------------------------------------------------
{
}
