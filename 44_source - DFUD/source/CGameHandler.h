////////////////////////////////////////////////////////////////////
//								  //
//	  	  DFUD: CGameHandler_h			  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#if!defined CGameHandler_H
#define CGameHandler_H

//--------------------------------------------------------//
//--			Struct/classes			--//
//--------------------------------------------------------//

class CGameHandler
{
public:

CGameHandler();
~CGameHandler();

void ServerHandleSyns(SEngine *Engine);
bool ServerHandler(SEngine *Engine);
bool ClientHandler(SEngine *Engine);
void Server_Local_KeyHandle(SEngine *Engine);

bool Main(SEngine *Engine);

void Load(SEngine *Engine);
void UnLoad(SEngine *Engine);

float Sync_Timer;

protected:
private:

bool Status_HeightMap;
bool Status_Timer;
bool Status_NetWork;
bool Status_Font;
};

struct SGame
{
CGameLoader *GameLoader;
CGameMain *GameMain;
CGameNetWork *GameNetWork;
};

//--------------------------------------------------------//
//--			Prototypes			--//
//--------------------------------------------------------//


#endif
