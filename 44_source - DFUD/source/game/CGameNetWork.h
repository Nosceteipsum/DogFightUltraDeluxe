////////////////////////////////////////////////////////////////////
//								  //
//	  	  DFUD: CGameNetWork_h			  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#if!defined CGameNetWork_H
#define CGameNetWork_H

//--------------------------------------------------------//
//--			  Defines			--//
//--------------------------------------------------------//

#define CLIENT_JOIN_PACKET		    1
#define CLIENT_KEYS_PACKET		    2
#define CLIENT_BUY_PACKET		    3
#define CLIENT_QUIT_PACKET		    4
#define CLIENT_PING_RESOND_PACKET	    5

#define SERVER_WELCOME			    1
#define SERVER_BROADCAST_WELCOME	    2
#define SERVER_RESETROUND		    3
#define SERVER_BUYMENU_STATUS_OK	    4
#define SERVER_ANIMAL_MOVE		    5
#define SERVER_SKY_UPDATE		    6
#define SERVER_NO_ROOM			    7
#define SERVER_KEYS_UPDATE		    8
#define SERVER_SYNC_PACKET		    9
#define SERVER_GAME_OVER		    10
#define SERVER_EQUIP_PACKET		    11
#define SERVER_QUIT_PACKET		    22
#define SERVER_PARA_PACKET		    23

#define SERVER_COLLISION_FIRE		    12
#define SERVER_COLLISION_SPEC		    13
#define SERVER_COLLISION_MAN		    14
#define SERVER_COLLISION_PARA		    15
#define SERVER_COLLISION_PLAYER		    16
#define SERVER_COLLISION_MAN_SHOT	    17
#define SERVER_COLLISION_PARA_SHOT	    18
#define SERVER_COLLISION_PLAYER_EXPLO	    19
#define SERVER_COLLISION_WALL		    20
#define SERVER_COLLISION_TREE		    21

//--------------------------------------------------------//
//--			Prototypes			--//
//--------------------------------------------------------//

//--------------------------------------------------------//
//--			Struct/classes			--//
//--------------------------------------------------------//

class CGameNetWork
{
public:

CGameNetWork();
~CGameNetWork();

void Server_NetWork_Handle(SEngine *Engine);
void Server_GetData(SEngine *Engine);
void Server_SendKeysUpdate(SEngine *Engine,char Player);
void Server_SendNameBroadCast(SEngine *Engine);
void Server_SendNewRound(SEngine *Engine);
void Server_SendBuyMenuOK(SEngine *Engine);
void Server_SendAnimalDestinate(SEngine *Engine);
void Server_SendSkyUpdate(SEngine *Engine);
void Server_SendEquip(SEngine *Engine);
void Server_SendSync(SEngine *Engine);
void Server_SendParaJump(SEngine *Engine,char Player);
void Server_GameOver_Packet(SEngine *Engine);
void Server_Collision(SEngine *Engine,char source,char target,char type);

void Client_NetWork_Handle(SEngine *Engine);
void Client_GetData(SEngine *Engine);
void Client_SendData(SEngine *Engine);
void Client_SendEquip(SEngine *Engine,char Buy);

bool Client_KeyPress_Left;
bool Client_KeyPress_Right;
bool Client_KeyPress_Up;
bool Client_KeyPress_Down;
bool Client_KeyPress_Fire;
bool Client_KeyPress_Spec;
bool Client_KeyPress_Para;

bool Player_Ready_To_Next_Packet[12];

double Client_Ping_Delay[12];
double Client_Ping_Got_Packet[12];
double Client_Ping_Send_Packet[12];
LARGE_INTEGER Client_Ping_Temp;

int Send_CLIENT_JOIN_PACKET;
int Send_CLIENT_KEYS_PACKET;
int Send_CLIENT_BUY_PACKET;
int Send_CLIENT_QUIT_PACKET;
int Send_CLIENT_PING_RESOND_PACKET;
int Send_SERVER_WELCOME;
int Send_SERVER_BROADCAST_WELCOME;
int Send_SERVER_RESETROUND;
int Send_SERVER_BUYMENU_STATUS_OK;
int Send_SERVER_ANIMAL_MOVE;
int Send_SERVER_SKY_UPDATE;
int Send_SERVER_NO_ROOM;
int Send_SERVER_KEYS_UPDATE;
int Send_SERVER_SYNC_PACKET;
int Send_SERVER_GAME_OVER;
int Send_SERVER_EQUIP_PACKET;
int Send_SERVER_QUIT_PACKET;
int Send_SERVER_COLLISION_FIRE;
int Send_SERVER_COLLISION_SPEC;
int Send_SERVER_COLLISION_MAN;
int Send_SERVER_COLLISION_PARA;
int Send_SERVER_COLLISION_PLAYER;
int Send_SERVER_COLLISION_MAN_SHOT;
int Send_SERVER_COLLISION_PARA_SHOT;
int Send_SERVER_COLLISION_PLAYER_EXPLO;
int Send_SERVER_COLLISION_WALL;
int Send_SERVER_COLLISION_TREE;
int Send_SERVER_PARA_PACKET;

int Get_CLIENT_JOIN_PACKET;
int Get_CLIENT_KEYS_PACKET;
int Get_CLIENT_BUY_PACKET;
int Get_CLIENT_QUIT_PACKET;
int Get_CLIENT_PING_RESOND_PACKET;
int Get_SERVER_WELCOME;
int Get_SERVER_BROADCAST_WELCOME;
int Get_SERVER_RESETROUND;
int Get_SERVER_BUYMENU_STATUS_OK;
int Get_SERVER_ANIMAL_MOVE;
int Get_SERVER_SKY_UPDATE;
int Get_SERVER_NO_ROOM;
int Get_SERVER_KEYS_UPDATE;
int Get_SERVER_SYNC_PACKET;
int Get_SERVER_GAME_OVER;
int Get_SERVER_EQUIP_PACKET;
int Get_SERVER_QUIT_PACKET;
int Get_SERVER_COLLISION_FIRE;
int Get_SERVER_COLLISION_SPEC;
int Get_SERVER_COLLISION_MAN;
int Get_SERVER_COLLISION_PARA;
int Get_SERVER_COLLISION_PLAYER;
int Get_SERVER_COLLISION_MAN_SHOT;
int Get_SERVER_COLLISION_PARA_SHOT;
int Get_SERVER_COLLISION_PLAYER_EXPLO;
int Get_SERVER_COLLISION_WALL;
int Get_SERVER_COLLISION_TREE;
int Get_SERVER_PARA_PACKET;

protected:
private:
};




#endif
