////////////////////////////////////////////////////////////////////
//								  //
//	  	  DFUD: CGameLoader_h			  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#if!defined CGameLoader_H
#define CGameLoader_H

//--------------------------------------------------------//
//--			Struct/classes			--//
//--------------------------------------------------------//

class CGameLoader
{
public:

CGameLoader();
~CGameLoader();

bool  Error_Check         ();
char *Get_Error_Message   ();

void Draw(SEngine *Engine);
void Load(SEngine *Engine);
void UnLoad(SEngine *Engine);

protected:
private:

TextureImageTGA Loader_TGA;

bool    Error_Detected;
char	Error_Message[50];
};

//--------------------------------------------------------//
//--			Prototypes			--//
//--------------------------------------------------------//


#endif
