////////////////////////////////////////////////////////////////////
//								  //
//	  	  DFUD: CGameNetWork_cpp		  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#include "../../global.h"

//------------------------------------------------------------------
CGameNetWork::CGameNetWork()
//------------------------------------------------------------------
{
for(char i = 0;i<=11;i++){Client_Ping_Delay[i] = 0;Player_Ready_To_Next_Packet[i] = true;}

Send_CLIENT_JOIN_PACKET = 0;
Send_CLIENT_KEYS_PACKET = 0;
Send_CLIENT_BUY_PACKET = 0;
Send_CLIENT_QUIT_PACKET = 0;
Send_CLIENT_PING_RESOND_PACKET = 0;
Send_SERVER_WELCOME = 0;
Send_SERVER_BROADCAST_WELCOME = 0;
Send_SERVER_RESETROUND = 0;
Send_SERVER_BUYMENU_STATUS_OK = 0;
Send_SERVER_ANIMAL_MOVE = 0;
Send_SERVER_SKY_UPDATE = 0;
Send_SERVER_NO_ROOM = 0;
Send_SERVER_KEYS_UPDATE = 0;
Send_SERVER_SYNC_PACKET = 0;
Send_SERVER_GAME_OVER = 0;
Send_SERVER_EQUIP_PACKET = 0;
Send_SERVER_QUIT_PACKET = 0;
Send_SERVER_COLLISION_FIRE = 0;
Send_SERVER_COLLISION_SPEC = 0;
Send_SERVER_COLLISION_MAN = 0;
Send_SERVER_COLLISION_PARA = 0;
Send_SERVER_COLLISION_PLAYER = 0;
Send_SERVER_COLLISION_MAN_SHOT = 0;
Send_SERVER_COLLISION_PARA_SHOT = 0;
Send_SERVER_COLLISION_PLAYER_EXPLO = 0;
Send_SERVER_COLLISION_WALL = 0;
Send_SERVER_COLLISION_TREE = 0;
Send_SERVER_PARA_PACKET    = 0;

Get_CLIENT_JOIN_PACKET = 0;
Get_CLIENT_KEYS_PACKET = 0;
Get_CLIENT_BUY_PACKET = 0;
Get_CLIENT_QUIT_PACKET = 0;
Get_CLIENT_PING_RESOND_PACKET = 0;
Get_SERVER_WELCOME = 0;
Get_SERVER_BROADCAST_WELCOME = 0;
Get_SERVER_RESETROUND = 0;
Get_SERVER_BUYMENU_STATUS_OK = 0;
Get_SERVER_ANIMAL_MOVE = 0;
Get_SERVER_SKY_UPDATE = 0;
Get_SERVER_NO_ROOM = 0;
Get_SERVER_KEYS_UPDATE = 0;
Get_SERVER_SYNC_PACKET = 0;
Get_SERVER_GAME_OVER = 0;
Get_SERVER_EQUIP_PACKET = 0;
Get_SERVER_QUIT_PACKET = 0;
Get_SERVER_COLLISION_FIRE = 0;
Get_SERVER_COLLISION_SPEC = 0;
Get_SERVER_COLLISION_MAN = 0;
Get_SERVER_COLLISION_PARA = 0;
Get_SERVER_COLLISION_PLAYER = 0;
Get_SERVER_COLLISION_MAN_SHOT = 0;
Get_SERVER_COLLISION_PARA_SHOT = 0;
Get_SERVER_COLLISION_PLAYER_EXPLO = 0;
Get_SERVER_COLLISION_WALL = 0;
Get_SERVER_COLLISION_TREE = 0;
Get_SERVER_PARA_PACKET = 0;
}

//------------------------------------------------------------------
CGameNetWork::~CGameNetWork()
//------------------------------------------------------------------
{
FILE *File_Pointer;
File_Pointer = fopen("Packets.txt","w");

fwrite("===--- Dog Fight Ultra Deluxe ---===",1,36,File_Pointer);
fwrite("\n\n",1,2,File_Pointer);

/////////////////////////////////////////////////////////
//--------------    Server Packets    -----------------//
/////////////////////////////////////////////////////////

fwrite("--Status Server--",1,17,File_Pointer);
fwrite("\n\n",1,2,File_Pointer);

fwrite("Packes-Recv: ",1,13,File_Pointer);// Recv - packes
fwrite("\n",1,1,File_Pointer);

fwrite("CLIENT_JOIN_PACKET:            ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_CLIENT_JOIN_PACKET);
fwrite("\n",1,1,File_Pointer);

fwrite("CLIENT_KEYS_PACKET:            ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_CLIENT_KEYS_PACKET);
fwrite("\n",1,1,File_Pointer);

fwrite("CLIENT_BUY_PACKET:             ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_CLIENT_BUY_PACKET);
fwrite("\n",1,1,File_Pointer);

fwrite("CLIENT_QUIT_PACKET:            ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_CLIENT_QUIT_PACKET);
fwrite("\n",1,1,File_Pointer);

fwrite("CLIENT_PING_RESOND_PACKET:     ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_CLIENT_PING_RESOND_PACKET);
fwrite("\n\n",1,2,File_Pointer);

fwrite("Packes-Send: ",1,13,File_Pointer);// Send - packes
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_WELCOME:                ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_SERVER_WELCOME);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_BROADCAST_WELCOME:      ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_SERVER_BROADCAST_WELCOME);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_RESETROUND:             ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_SERVER_RESETROUND);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_BUYMENU_STATUS_OK:      ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_SERVER_BUYMENU_STATUS_OK);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_ANIMAL_MOVE:            ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_SERVER_ANIMAL_MOVE);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_SKY_UPDATE:             ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_SERVER_SKY_UPDATE);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_NO_ROOM:                ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_SERVER_NO_ROOM);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_KEYS_UPDATE:            ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_SERVER_KEYS_UPDATE);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_SYNC_PACKET:            ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_SERVER_SYNC_PACKET);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_GAME_OVER:              ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_SERVER_GAME_OVER);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_EQUIP_PACKET:           ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_SERVER_EQUIP_PACKET);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_QUIT_PACKET:            ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_SERVER_QUIT_PACKET);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_COLLISION_FIRE:         ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_SERVER_COLLISION_FIRE);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_COLLISION_SPEC:         ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_SERVER_COLLISION_SPEC);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_COLLISION_MAN:          ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_SERVER_COLLISION_MAN);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_COLLISION_PARA:         ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_SERVER_COLLISION_PARA);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_COLLISION_PLAYER:       ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_SERVER_COLLISION_PLAYER);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_COLLISION_MAN_SHOT:     ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_SERVER_COLLISION_MAN_SHOT);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_COLLISION_PARA_SHOT:    ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_SERVER_COLLISION_PARA_SHOT);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_COLLISION_PLAYER_EXPLO: ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_SERVER_COLLISION_PLAYER_EXPLO);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_COLLISION_WALL:         ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_SERVER_COLLISION_WALL);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_COLLISION_TREE:         ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_SERVER_COLLISION_TREE);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_PARA_PACKET:            ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_SERVER_PARA_PACKET);
fwrite("\n",1,1,File_Pointer);

/////////////////////////////////////////////////////////
//--------------    Clients Packets    ----------------//
/////////////////////////////////////////////////////////

fwrite("--Status Client--",1,17,File_Pointer);
fwrite("\n\n",1,2,File_Pointer);

fwrite("Packes-Send: ",1,13,File_Pointer);// Recv - packes
fwrite("\n",1,1,File_Pointer);

fwrite("CLIENT_JOIN_PACKET:            ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_CLIENT_JOIN_PACKET);
fwrite("\n",1,1,File_Pointer);

fwrite("CLIENT_KEYS_PACKET:            ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_CLIENT_KEYS_PACKET);
fwrite("\n",1,1,File_Pointer);

fwrite("CLIENT_BUY_PACKET:             ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_CLIENT_BUY_PACKET);
fwrite("\n",1,1,File_Pointer);

fwrite("CLIENT_QUIT_PACKET:            ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_CLIENT_QUIT_PACKET);
fwrite("\n",1,1,File_Pointer);

fwrite("CLIENT_PING_RESOND_PACKET:     ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Send_CLIENT_PING_RESOND_PACKET);
fwrite("\n\n",1,2,File_Pointer);

fwrite("Packes-Recv: ",1,13,File_Pointer);// Send - packes
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_WELCOME:                ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_SERVER_WELCOME);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_BROADCAST_WELCOME:      ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_SERVER_BROADCAST_WELCOME);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_RESETROUND:             ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_SERVER_RESETROUND);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_BUYMENU_STATUS_OK:      ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_SERVER_BUYMENU_STATUS_OK);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_ANIMAL_MOVE:            ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_SERVER_ANIMAL_MOVE);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_SKY_UPDATE:             ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_SERVER_SKY_UPDATE);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_NO_ROOM:                ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_SERVER_NO_ROOM);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_KEYS_UPDATE:            ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_SERVER_KEYS_UPDATE);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_SYNC_PACKET:            ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_SERVER_SYNC_PACKET);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_GAME_OVER:              ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_SERVER_GAME_OVER);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_EQUIP_PACKET:           ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_SERVER_EQUIP_PACKET);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_QUIT_PACKET:            ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_SERVER_QUIT_PACKET);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_COLLISION_FIRE:         ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_SERVER_COLLISION_FIRE);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_COLLISION_SPEC:         ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_SERVER_COLLISION_SPEC);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_COLLISION_MAN:          ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_SERVER_COLLISION_MAN);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_COLLISION_PARA:         ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_SERVER_COLLISION_PARA);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_COLLISION_PLAYER:       ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_SERVER_COLLISION_PLAYER);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_COLLISION_MAN_SHOT:     ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_SERVER_COLLISION_MAN_SHOT);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_COLLISION_PARA_SHOT:    ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_SERVER_COLLISION_PARA_SHOT);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_COLLISION_PLAYER_EXPLO: ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_SERVER_COLLISION_PLAYER_EXPLO);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_COLLISION_WALL:         ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_SERVER_COLLISION_WALL);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_COLLISION_TREE:         ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_SERVER_COLLISION_TREE);
fwrite("\n",1,1,File_Pointer);

fwrite("SERVER_PARA_PACKET:            ",1,31,File_Pointer);fprintf(File_Pointer,"%i",Get_SERVER_PARA_PACKET);
fwrite("\n",1,1,File_Pointer);

fclose(File_Pointer);
}

//------------------------------------------------------------------
void CGameNetWork::Server_NetWork_Handle(SEngine *Engine)
//------------------------------------------------------------------
{
Server_GetData(Engine);
}

//------------------------------------------------------------------
void CGameNetWork::Server_GetData(SEngine *Engine)
//------------------------------------------------------------------
{
while(Engine->WinSock->Server_CheckObject() == true)
  {
  Engine->Game->GameMain->Packet_Count++;
  char DataRecv[200];
  Engine->WinSock->Server_GetData(DataRecv);

  //----------------------------------------------------------------
  if(DataRecv[0] == CLIENT_JOIN_PACKET) // Client Join
  //----------------------------------------------------------------
    {
    Get_CLIENT_JOIN_PACKET++;
    bool FreeSpot_Found = false;
    for(char i=1;i<=11;i++)
      {
      if(FreeSpot_Found == false && Engine->Game->GameMain->Player[i].Active == false)
        {
	FreeSpot_Found = true;
	Engine->Game->GameMain->Player[i].Active = true;
	if(Engine->Game->GameMain->Rules.GameState_Prepare == true || Engine->Game->GameMain->Rules.GameState_Buying == true)Engine->Game->GameMain->Player[i].Dead = false;
	memcpy(Engine->Game->GameMain->Player[i].Name,DataRecv+1,70);

	Send_SERVER_WELCOME++;
	char Temp_Packet[2];
	Temp_Packet[0] = SERVER_WELCOME;
	Temp_Packet[1] = i;
	Engine->WinSock->Server_SendData(Temp_Packet,2);
	Engine->WinSock->Server_SaveIP(i);

	Server_SendNameBroadCast(Engine);
	if(Engine->Game->GameMain->Rules.GameState_Prepare == true || Engine->Game->GameMain->Rules.GameState_Buying == true)Engine->Game->GameMain->ResetRound(Engine);
	Engine->DirectX_Sound->Play("data//sound//Player_Join.dat",false);
	}
      }
    if(FreeSpot_Found == false)
      {
      Send_SERVER_NO_ROOM++;
      char Temp_Packet[1];
      Temp_Packet[0] = SERVER_NO_ROOM;
      Engine->WinSock->Server_SendData(Temp_Packet,1);
      }
    }
  //----------------------------------------------------------------
  if(DataRecv[0] == CLIENT_BUY_PACKET) // Client Quit
  //----------------------------------------------------------------
    {
    Get_CLIENT_BUY_PACKET++;
    if(DataRecv[2] == '3')Engine->Game->GameMain->Equip[DataRecv[1]].Option_Ok = true;

    if(DataRecv[2] == 'Q' && Engine->Game->GameMain->Player[DataRecv[1]].Money >=  500 && (Engine->Game->GameMain->Equip[DataRecv[1]].Option_Plane & 0x01) != 0x01){Engine->Game->GameMain->Equip[DataRecv[1]].Option_Plane |= 0x01;Engine->Game->GameMain->Player[DataRecv[1]].Money -=  500;return;}
    if(DataRecv[2] == 'A' && Engine->Game->GameMain->Player[DataRecv[1]].Money >=  800 && (Engine->Game->GameMain->Equip[DataRecv[1]].Option_Plane & 0x02) != 0x02){Engine->Game->GameMain->Equip[DataRecv[1]].Option_Plane |= 0x02;Engine->Game->GameMain->Player[DataRecv[1]].Money -=  800;return;}
    if(DataRecv[2] == 'Z' && Engine->Game->GameMain->Player[DataRecv[1]].Money >= 1000 && (Engine->Game->GameMain->Equip[DataRecv[1]].Option_Plane & 0x04) != 0x04){Engine->Game->GameMain->Equip[DataRecv[1]].Option_Plane |= 0x04;Engine->Game->GameMain->Player[DataRecv[1]].Money -= 1000;Engine->Game->GameMain->Player[DataRecv[1]].Damage = -1;return;}
    if(DataRecv[2] == 'T' && Engine->Game->GameMain->Player[DataRecv[1]].Money >= 1400 && (Engine->Game->GameMain->Equip[DataRecv[1]].Option_Plane & 0x08) != 0x08){Engine->Game->GameMain->Equip[DataRecv[1]].Option_Plane |= 0x08;Engine->Game->GameMain->Player[DataRecv[1]].Money -= 1400;return;}

    if(DataRecv[2] == 'W' && Engine->Game->GameMain->Player[DataRecv[1]].Money >=  400 && (Engine->Game->GameMain->Equip[DataRecv[1]].Option_Para & 0x01) != 0x01){Engine->Game->GameMain->Equip[DataRecv[1]].Option_Para |= 0x01;Engine->Game->GameMain->Player[DataRecv[1]].Money -=  400;return;}
    if(DataRecv[2] == 'S' && Engine->Game->GameMain->Player[DataRecv[1]].Money >=  700 && (Engine->Game->GameMain->Equip[DataRecv[1]].Option_Para & 0x02) != 0x02){Engine->Game->GameMain->Equip[DataRecv[1]].Option_Para |= 0x02;Engine->Game->GameMain->Player[DataRecv[1]].Money -=  700;return;}
    if(DataRecv[2] == 'X' && Engine->Game->GameMain->Player[DataRecv[1]].Money >= 1000 && (Engine->Game->GameMain->Equip[DataRecv[1]].Option_Para & 0x04) != 0x04){Engine->Game->GameMain->Equip[DataRecv[1]].Option_Para |= 0x04;Engine->Game->GameMain->Player[DataRecv[1]].Money -= 1000;return;}
    if(DataRecv[2] == 'Y' && Engine->Game->GameMain->Player[DataRecv[1]].Money >= 1500 && (Engine->Game->GameMain->Equip[DataRecv[1]].Option_Para & 0x08) != 0x08){Engine->Game->GameMain->Equip[DataRecv[1]].Option_Para |= 0x08;Engine->Game->GameMain->Player[DataRecv[1]].Money -= 1500;return;}

    if(DataRecv[2] == 'E' && Engine->Game->GameMain->Player[DataRecv[1]].Money >=  300 && (Engine->Game->GameMain->Equip[DataRecv[1]].Option_Shot & 0x01) != 0x01){Engine->Game->GameMain->Equip[DataRecv[1]].Option_Shot |= 0x01;Engine->Game->GameMain->Player[DataRecv[1]].Money -=  300;return;}
    if(DataRecv[2] == 'D' && Engine->Game->GameMain->Player[DataRecv[1]].Money >=  500 && (Engine->Game->GameMain->Equip[DataRecv[1]].Option_Shot & 0x02) != 0x02){Engine->Game->GameMain->Equip[DataRecv[1]].Option_Shot |= 0x02;Engine->Game->GameMain->Player[DataRecv[1]].Money -=  500;return;}
    if(DataRecv[2] == 'C' && Engine->Game->GameMain->Player[DataRecv[1]].Money >= 1000 && (Engine->Game->GameMain->Equip[DataRecv[1]].Option_Shot & 0x04) != 0x04){Engine->Game->GameMain->Equip[DataRecv[1]].Option_Shot |= 0x04;Engine->Game->GameMain->Player[DataRecv[1]].Money -= 1000;return;}
    if(DataRecv[2] == 'U' && Engine->Game->GameMain->Player[DataRecv[1]].Money >= 2000 && (Engine->Game->GameMain->Equip[DataRecv[1]].Option_Shot & 0x08) != 0x08){Engine->Game->GameMain->Equip[DataRecv[1]].Option_Shot |= 0x08;Engine->Game->GameMain->Player[DataRecv[1]].Money -= 2000;return;}

    if(DataRecv[2] == 'R' && Engine->Game->GameMain->Player[DataRecv[1]].Money >=  400 && (Engine->Game->GameMain->Equip[DataRecv[1]].Option_Spec & 0x01) != 0x01){Engine->Game->GameMain->Equip[DataRecv[1]].Option_Spec |= 0x01;Engine->Game->GameMain->Player[DataRecv[1]].Money -=  400;return;}
    if(DataRecv[2] == 'F' && Engine->Game->GameMain->Player[DataRecv[1]].Money >=  600 && (Engine->Game->GameMain->Equip[DataRecv[1]].Option_Spec & 0x02) != 0x02){Engine->Game->GameMain->Equip[DataRecv[1]].Option_Spec |= 0x02;Engine->Game->GameMain->Player[DataRecv[1]].Money -=  600;return;}
    if(DataRecv[2] == 'V' && Engine->Game->GameMain->Player[DataRecv[1]].Money >=  900 && (Engine->Game->GameMain->Equip[DataRecv[1]].Option_Spec & 0x04) != 0x04){Engine->Game->GameMain->Equip[DataRecv[1]].Option_Spec |= 0x04;Engine->Game->GameMain->Player[DataRecv[1]].Money -=  900;return;}
    if(DataRecv[2] == 'I' && Engine->Game->GameMain->Player[DataRecv[1]].Money >= 1600 && (Engine->Game->GameMain->Equip[DataRecv[1]].Option_Spec & 0x08) != 0x08){Engine->Game->GameMain->Equip[DataRecv[1]].Option_Spec |= 0x08;Engine->Game->GameMain->Player[DataRecv[1]].Money -= 1600;return;}
    }
  //----------------------------------------------------------------
  if(DataRecv[0] == CLIENT_QUIT_PACKET) // Client Quit
  //----------------------------------------------------------------
    {
    Get_CLIENT_QUIT_PACKET++;
    if(DataRecv[1] != 0)
      {
      Engine->Game->GameMain->Player[DataRecv[1]].Active = false;
      Engine->Game->GameMain->Player[DataRecv[1]].Hits = 0;
      Engine->Game->GameMain->Player[DataRecv[1]].Money = 0;
      memcpy(Engine->Game->GameMain->Player[DataRecv[1]].Name,"Empty\0",7);
      Server_SendNameBroadCast(Engine);
      }
    }

  //----------------------------------------------------------------
  if(DataRecv[0] == CLIENT_PING_RESOND_PACKET) // Client Ping Time Calculate
  //----------------------------------------------------------------
    {
    Get_CLIENT_PING_RESOND_PACKET++;
    QueryPerformanceCounter(&Client_Ping_Temp);
    Client_Ping_Got_Packet[DataRecv[1]] = (double)Client_Ping_Temp.QuadPart;
    Client_Ping_Delay[DataRecv[1]] = Client_Ping_Got_Packet[DataRecv[1]] - Client_Ping_Send_Packet[DataRecv[1]];

    double fUsed=((double)Engine->Timer->m_nTimingFreq.QuadPart)/(Client_Ping_Delay[DataRecv[1]]);
    Client_Ping_Delay[DataRecv[1]] = 1000.0f/fUsed;
    Client_Ping_Delay[DataRecv[1]] = Client_Ping_Delay[DataRecv[1]] / 2; // Get the ping for server to client, instead of server to client to server.

    Player_Ready_To_Next_Packet[DataRecv[1]] = true;
    }

  //----------------------------------------------------------------
  if(DataRecv[0] == CLIENT_KEYS_PACKET) // Client Keys Control
  //----------------------------------------------------------------
    {
    Get_CLIENT_KEYS_PACKET++;
    if(Engine->Game->GameMain->Player[DataRecv[1]].SpecInvert == false)
      {
      if((DataRecv[2] & 0x01) == 0x00)Engine->Game->GameMain->Player[DataRecv[1]].Key_Left = false;
      else Engine->Game->GameMain->Player[DataRecv[1]].Key_Left = true;

      if((DataRecv[2] & 0x02) == 0x00)Engine->Game->GameMain->Player[DataRecv[1]].Key_Right = false;
      else Engine->Game->GameMain->Player[DataRecv[1]].Key_Right = true;

      if((DataRecv[2] & 0x04) == 0x00)Engine->Game->GameMain->Player[DataRecv[1]].Key_Up = false;
      else Engine->Game->GameMain->Player[DataRecv[1]].Key_Up = true;

      if((DataRecv[2] & 0x08) == 0x00)Engine->Game->GameMain->Player[DataRecv[1]].Key_Down = false;
      else Engine->Game->GameMain->Player[DataRecv[1]].Key_Down = true;

      if((DataRecv[2] & 0x10) == 0x00)Engine->Game->GameMain->Player[DataRecv[1]].Key_Fire = false;
      else Engine->Game->GameMain->Player[DataRecv[1]].Key_Fire = true;

      if((DataRecv[2] & 0x20) == 0x00)Engine->Game->GameMain->Player[DataRecv[1]].Key_Spec = false;
      else Engine->Game->GameMain->Player[DataRecv[1]].Key_Spec = true;

      if((DataRecv[2] & 0x40) == 0x00)Engine->Game->GameMain->Player[DataRecv[1]].Key_Para = false;
      else Engine->Game->GameMain->Player[DataRecv[1]].Key_Para = true;
      }
   if(Engine->Game->GameMain->Player[DataRecv[1]].SpecInvert == true)
      {
      if((DataRecv[2] & 0x01) == 0x00)Engine->Game->GameMain->Player[DataRecv[1]].Key_Right = false;
      else Engine->Game->GameMain->Player[DataRecv[1]].Key_Right = true;

      if((DataRecv[2] & 0x02) == 0x00)Engine->Game->GameMain->Player[DataRecv[1]].Key_Left = false;
      else Engine->Game->GameMain->Player[DataRecv[1]].Key_Left = true;

      if((DataRecv[2] & 0x04) == 0x00)Engine->Game->GameMain->Player[DataRecv[1]].Key_Down = false;
      else Engine->Game->GameMain->Player[DataRecv[1]].Key_Down = true;

      if((DataRecv[2] & 0x08) == 0x00)Engine->Game->GameMain->Player[DataRecv[1]].Key_Up = false;
      else Engine->Game->GameMain->Player[DataRecv[1]].Key_Up = true;

      if((DataRecv[2] & 0x10) == 0x00)Engine->Game->GameMain->Player[DataRecv[1]].Key_Spec = false;
      else Engine->Game->GameMain->Player[DataRecv[1]].Key_Spec = true;

      if((DataRecv[2] & 0x20) == 0x00)Engine->Game->GameMain->Player[DataRecv[1]].Key_Fire = false;
      else Engine->Game->GameMain->Player[DataRecv[1]].Key_Fire = true;

      if((DataRecv[2] & 0x40) == 0x00)Engine->Game->GameMain->Player[DataRecv[1]].Key_Para = false;
      else Engine->Game->GameMain->Player[DataRecv[1]].Key_Para = true;
      }
    Server_SendKeysUpdate(Engine,DataRecv[1]);
    }
  }
}

//------------------------------------------------------------------
void CGameNetWork::Client_NetWork_Handle(SEngine *Engine)
//------------------------------------------------------------------
{
Client_GetData(Engine);
Client_SendData(Engine);
}

//------------------------------------------------------------------
void CGameNetWork::Client_GetData(SEngine *Engine)
//------------------------------------------------------------------
{

while(Engine->WinSock->Client_CheckObject() == true)
  {
  Engine->Game->GameMain->Packet_Count++;
  char *GetData = Engine->WinSock->Client_RecvData();
  //----------------------------------------------------------------
  if(GetData[0] == SERVER_QUIT_PACKET) // Get ID Number
  //----------------------------------------------------------------
    {
    Get_SERVER_QUIT_PACKET++;
    Engine->Game->GameMain->GameOver     = true;
    Engine->Game->GameMain->Server_Close = true;
    }

  //----------------------------------------------------------------
  if(GetData[0] == SERVER_WELCOME) // Get ID Number
  //----------------------------------------------------------------
    {
    Get_SERVER_WELCOME++;
    Engine->Game->GameMain->Net_Id = GetData[1];
    Engine->OpenGl_Window->SwapBuffers_hdc();
    Engine->OpenGl_Font->glPrint(220,380,"Waiting for server...",1);
    Engine->OpenGl_Window->SwapBuffers_hdc();
    }
  //----------------------------------------------------------------
  if(GetData[0] == SERVER_PARA_PACKET) // Player Jump out in Para
  //----------------------------------------------------------------
    {
    Get_SERVER_PARA_PACKET++;
    Engine->Game->GameMain->Player[GetData[1]].Pilot		   = false;

    if((Engine->Game->GameMain->Equip[GetData[1]].Option_Para & 0x08) == 0x08)
      {
      Engine->Game->GameMain->Player_Para_And_Man[GetData[1]].IsSphere = true;
      Engine->Game->GameMain->Sphere[GetData[1]].x         = Engine->Game->GameMain->Player[GetData[1]].x;
      Engine->Game->GameMain->Sphere[GetData[1]].y         = Engine->Game->GameMain->Player[GetData[1]].y;
      Engine->Game->GameMain->Sphere[GetData[1]].Rotate    = Engine->Game->GameMain->Player[GetData[1]].Rotate;
      Engine->Game->GameMain->Sphere[GetData[1]].Speed     = Engine->Game->GameMain->Player[GetData[1]].Speed;
      Engine->Game->GameMain->Sphere[GetData[1]].Active    = true;
      Engine->Game->GameMain->Sphere[GetData[1]].Bounce    = 10;
      Engine->Game->GameMain->Sphere[GetData[1]].SpeedDown = 0.0f;
      Engine->Game->GameMain->Sphere[GetData[1]].Rotating  = 0.0f;
      }
    if((Engine->Game->GameMain->Equip[GetData[1]].Option_Para & 0x08) != 0x08)
      {
      Engine->Game->GameMain->Player_Para_And_Man[GetData[1]].IsPara = true;
      Engine->Game->GameMain->Player_Para_And_Man[GetData[1]].x	   = Engine->Game->GameMain->Player[GetData[1]].x;
      Engine->Game->GameMain->Player_Para_And_Man[GetData[1]].y	   = Engine->Game->GameMain->Player[GetData[1]].y;
      Engine->Game->GameMain->Player_Para_And_Man[GetData[1]].Cloak  = 1.0f;
      }
    }
  //----------------------------------------------------------------
  if(GetData[0] == SERVER_NO_ROOM) // Server is Full
  //----------------------------------------------------------------
    {
    Get_SERVER_NO_ROOM++;
    MessageBox(NULL,"Error","Server is full...",MB_OK);
    }
  //----------------------------------------------------------------
  if(GetData[0] == SERVER_EQUIP_PACKET) // Equip thing
  //----------------------------------------------------------------
    {
    Get_SERVER_EQUIP_PACKET++;
    for(char i=0;i<=11;i++)
      {
      Engine->Game->GameMain->Equip[i].Option_Plane = GetData[1+(i*4)];
      Engine->Game->GameMain->Equip[i].Option_Para  = GetData[2+(i*4)];
      Engine->Game->GameMain->Equip[i].Option_Shot  = GetData[3+(i*4)];
      Engine->Game->GameMain->Equip[i].Option_Spec  = GetData[4+(i*4)];
      }
    }
  //----------------------------------------------------------------
  if(GetData[0] == SERVER_COLLISION_SPEC) // Hit By Spec
  //----------------------------------------------------------------
    {
    Get_SERVER_COLLISION_SPEC++;
    Engine->DirectX_Sound->Play("data//sound//Spec_hit.dat",false);
    Engine->Game->GameMain->Spec[GetData[1]].Active = false;

    Engine->Game->GameMain->Player[GetData[2]].Rotate += 60;
    Engine->Game->GameMain->Player[GetData[2]].Speed = 0.0f;

    if(Engine->Game->GameMain->Player[GetData[2]].Pilot == true)
      {
      if((Engine->Game->GameMain->Equip[GetData[1]].Option_Spec & 0x01) == 0x01)
        {
        //if(Engine->Game->GameMain->Player[GetData[2]].SpecSpeedHit > 0.4f)Engine->Game->GameMain->Player[GetData[2]].SpecSpeedHit -= 0.3f;
        if(GetData[2] == Engine->Game->GameMain->Net_Id)Engine->Game->GameMain->Drugs_On = true;
        }
      if((Engine->Game->GameMain->Equip[GetData[1]].Option_Spec & 0x02) == 0x02)
        {
        if(Engine->Game->GameMain->Player[GetData[2]].SpecInvert == true)Engine->Game->GameMain->Player[GetData[2]].SpecInvert = false;
        else Engine->Game->GameMain->Player[GetData[2]].SpecInvert = true;
        }
      if((Engine->Game->GameMain->Equip[GetData[1]].Option_Spec & 0x04) == 0x04)
        {
        if(GetData[2] == Engine->Game->GameMain->Net_Id)Engine->Game->GameMain->Color = -0.7f;
        }
      if((Engine->Game->GameMain->Equip[GetData[1]].Option_Spec & 0x08) == 0x08)
        {
	// Server send a packet if the player eject out in para
        }
      }
    }
  //----------------------------------------------------------------
  if(GetData[0] == SERVER_COLLISION_FIRE) // Hit By Fire
  //----------------------------------------------------------------
    {
    Get_SERVER_COLLISION_FIRE++;
    char Temp_Rand = rand()%4;
    if(Temp_Rand == 0)Engine->DirectX_Sound->Play("data//sound//hit1.dat",false);
    if(Temp_Rand == 1)Engine->DirectX_Sound->Play("data//sound//hit2.dat",false);
    if(Temp_Rand == 2)Engine->DirectX_Sound->Play("data//sound//hit3.dat",false);
    if(Temp_Rand == 3)Engine->DirectX_Sound->Play("data//sound//hit4.dat",false);
    if((Engine->Game->GameMain->Equip[GetData[1]].Option_Shot & 0x04) == 0x04)Engine->Game->GameMain->Player[GetData[2]].Damage++;
    Engine->Game->GameMain->Player[GetData[2]].Damage++;
    Engine->Game->GameMain->Shot[GetData[1]].Active = false;
    Engine->Game->GameMain->Player[GetData[1]].Hits++;
    Engine->Game->GameMain->Player[GetData[1]].Money += 75;
    if(Engine->Game->GameMain->Player[GetData[2]].Damage >= 3)Engine->Game->GameMain->Plane_Explosion(Engine,GetData[2]);
    }
  //----------------------------------------------------------------
  if(GetData[0] == SERVER_COLLISION_PARA_SHOT) // Hit By Fire
  //----------------------------------------------------------------
    {
    Get_SERVER_COLLISION_PARA_SHOT++;
    Engine->Game->GameMain->Player_Para_And_Man[GetData[2]].ParaDead = true;
    Engine->Game->GameMain->Shot[GetData[1]].Active = false;
    Engine->Game->GameMain->Player[GetData[1]].Hits++;
    Engine->Game->GameMain->Player[GetData[1]].Money += 75;
    Engine->DirectX_Sound->Play("data//sound//PlayerHit.dat",false);
    }
  //----------------------------------------------------------------
  if(GetData[0] == SERVER_COLLISION_MAN_SHOT) // Hit By Fire
  //----------------------------------------------------------------
    {
    Get_SERVER_COLLISION_MAN_SHOT++;
    Engine->Game->GameMain->Player_Para_And_Man[GetData[2]].IsMan = false;
    Engine->Game->GameMain->Shot[GetData[1]].Active = false;
    Engine->Game->GameMain->Player[GetData[1]].Hits++;
    Engine->Game->GameMain->Player[GetData[1]].Money += 75;
    Engine->DirectX_Sound->Play("data//sound//PlayerHit.dat",false);
    }
  //----------------------------------------------------------------
  if(GetData[0] == SERVER_COLLISION_PARA) // PARA Hit 
  //----------------------------------------------------------------
    {
    Get_SERVER_COLLISION_PARA++;
    Engine->Game->GameMain->Player_Para_And_Man[GetData[2]].ParaDead = true;
    Engine->DirectX_Sound->Play("data//sound//PlayerHit.dat",false); 
    }
  //----------------------------------------------------------------
  if(GetData[0] == SERVER_COLLISION_MAN) // MAN Hit
  //----------------------------------------------------------------
    {
    Get_SERVER_COLLISION_MAN++;
    Engine->Game->GameMain->Player_Para_And_Man[GetData[2]].IsMan = false;
    Engine->DirectX_Sound->Play("data//sound//PlayerHit.dat",false);
    }
  //----------------------------------------------------------------
  if(GetData[0] == SERVER_COLLISION_PLAYER_EXPLO) // Player hit by explo
  //----------------------------------------------------------------
    {
    Get_SERVER_COLLISION_PLAYER_EXPLO++;
    Engine->Game->GameMain->Player[GetData[2]].Damage = 2;
    Engine->DirectX_Sound->Play("data//sound//Player_Flame.dat",false); 
    }
  //----------------------------------------------------------------
  if(GetData[0] == SERVER_COLLISION_PLAYER) // Player hit by explo
  //----------------------------------------------------------------
    {
    Get_SERVER_COLLISION_PLAYER++;
    Engine->DirectX_Sound->Play("data//sound//Player_Collision.dat",false);
    Engine->Game->GameMain->Player[GetData[1]].Damage = 2;
    Engine->Game->GameMain->Player[GetData[2]].Damage = 2;
    }
  //----------------------------------------------------------------
  if(GetData[0] == SERVER_COLLISION_WALL) // Player hit by explo
  //----------------------------------------------------------------
    {
    Get_SERVER_COLLISION_WALL++;
    Engine->Game->GameMain->Plane_Explosion(Engine,GetData[2]);
    }
  //----------------------------------------------------------------
  if(GetData[0] == SERVER_COLLISION_TREE) // Player hit by explo
  //----------------------------------------------------------------
    {
    Get_SERVER_COLLISION_TREE++;
    if(Engine->Game->GameMain->Player[GetData[2]].Dead == false){if(Engine->Game->GameMain->Player[GetData[2]].Damage == 0)Engine->Game->GameMain->Player[GetData[2]].Damage = 1;}
    Engine->DirectX_Sound->Play("data//sound//Player_Flame.dat",false);
    }
  //----------------------------------------------------------------
  if(GetData[0] == SERVER_BUYMENU_STATUS_OK) // Round over
  //----------------------------------------------------------------
    {
    Get_SERVER_BUYMENU_STATUS_OK++;
    Engine->Game->GameMain->Rules.Buy_Counter = -1;
    }
  //----------------------------------------------------------------
  if(GetData[0] == SERVER_BROADCAST_WELCOME) // Get Names
  //----------------------------------------------------------------
    {
    Get_SERVER_BROADCAST_WELCOME++;
    for(int i = 0;i<=11;i++)
      {
      memcpy(Engine->Game->GameMain->Player[i].Name,GetData+1+(i*70),69);
      }
    Engine->DirectX_Sound->Play("data//sound//Player_Join.dat",false);
    }
  //----------------------------------------------------------------
  if(GetData[0] == SERVER_SYNC_PACKET)    // Get Syns packet
  //----------------------------------------------------------------
    {
    Send_CLIENT_PING_RESOND_PACKET++;
    Get_SERVER_SYNC_PACKET++;

    char Temp_Respond_Packet[2];
    Temp_Respond_Packet[0] = CLIENT_PING_RESOND_PACKET;
    Temp_Respond_Packet[1] = Engine->Game->GameMain->Net_Id;
    Engine->WinSock->Client_SendData(Temp_Respond_Packet,2);

//-------------------- Keys Update ---------------------------//
    for(int i = 0;i<=11;i++)
      {
      if((GetData[i+1] & 0x01) == 0x00)Engine->Game->GameMain->Player[i].Key_Left = false;
      else Engine->Game->GameMain->Player[i].Key_Left = true;

      if((GetData[i+1] & 0x02) == 0x00)Engine->Game->GameMain->Player[i].Key_Right = false;
      else Engine->Game->GameMain->Player[i].Key_Right = true;

      if((GetData[i+1] & 0x04) == 0x00)Engine->Game->GameMain->Player[i].Key_Up = false;
      else Engine->Game->GameMain->Player[i].Key_Up = true;

      if((GetData[i+1] & 0x08) == 0x00)Engine->Game->GameMain->Player[i].Key_Down = false;
      else Engine->Game->GameMain->Player[i].Key_Down = true;

      if((GetData[i+1] & 0x10) == 0x00)Engine->Game->GameMain->Player[i].Key_Fire = false;
      else Engine->Game->GameMain->Player[i].Key_Fire = true;

      if((GetData[i+1] & 0x20) == 0x00)Engine->Game->GameMain->Player[i].Key_Spec = false;
      else Engine->Game->GameMain->Player[i].Key_Spec = true;

      if((GetData[i+1] & 0x40) == 0x00)Engine->Game->GameMain->Player[i].Key_Para = false;
      else Engine->Game->GameMain->Player[i].Key_Para = true;
      }
//--------------------- Sync Update -------------------------//
    long TempLong;
    short  TempInt;
    for(i = 0;i<=11;i++)
      {
      memcpy(&TempLong,GetData+12+1+(i*21),4);
      Engine->Game->GameMain->Player[i].x	 = (float)(TempLong * 0.000001f);
      memcpy(&TempLong,GetData+12+5+(i*21),4);
      Engine->Game->GameMain->Player[i].y	 = (float)(TempLong * 0.000001f);
      memcpy(&TempInt, GetData+12+9+(i*21),2);
      Engine->Game->GameMain->Player[i].Rotate	 = (float)(TempInt * 0.1f);

      memcpy(&TempLong,GetData+12+11+(i*21),4);
      Engine->Game->GameMain->Player_Para_And_Man[i].x	    = (float)(TempLong * 0.000001f);
      memcpy(&TempLong,GetData+12+15+(i*21),4);
      Engine->Game->GameMain->Player_Para_And_Man[i].y	    = (float)(TempLong * 0.000001f);
      memcpy(&TempInt, GetData+12+19+(i*21),2);
      Engine->Game->GameMain->Player_Para_And_Man[i].Rotate = (float)(TempInt * 0.1f);
      }
    }
  //----------------------------------------------------------------
  if(GetData[0] == SERVER_GAME_OVER) // GameOver Packet
  //----------------------------------------------------------------
    {
    Get_SERVER_GAME_OVER++;
    Engine->Game->GameMain->GameOver = true;
    }
  //----------------------------------------------------------------
  if(GetData[0] == SERVER_KEYS_UPDATE) // Get keys handle
  //----------------------------------------------------------------
    {
    Get_SERVER_KEYS_UPDATE++;
    if((GetData[2] & 0x01) == 0x00)Engine->Game->GameMain->Player[GetData[1]].Key_Left = false;
    else Engine->Game->GameMain->Player[GetData[1]].Key_Left = true;

    if((GetData[2] & 0x02) == 0x00)Engine->Game->GameMain->Player[GetData[1]].Key_Right = false;
    else Engine->Game->GameMain->Player[GetData[1]].Key_Right = true;

    if((GetData[2] & 0x04) == 0x00)Engine->Game->GameMain->Player[GetData[1]].Key_Up = false;
    else Engine->Game->GameMain->Player[GetData[1]].Key_Up = true;

    if((GetData[2] & 0x08) == 0x00)Engine->Game->GameMain->Player[GetData[1]].Key_Down = false;
    else Engine->Game->GameMain->Player[GetData[1]].Key_Down = true;

    if((GetData[2] & 0x10) == 0x00)Engine->Game->GameMain->Player[GetData[1]].Key_Fire = false;
    else Engine->Game->GameMain->Player[GetData[1]].Key_Fire = true;

    if((GetData[2] & 0x20) == 0x00)Engine->Game->GameMain->Player[GetData[1]].Key_Spec = false;
    else Engine->Game->GameMain->Player[GetData[1]].Key_Spec = true;

    if((GetData[2] & 0x40) == 0x00)Engine->Game->GameMain->Player[GetData[1]].Key_Para = false;
    else Engine->Game->GameMain->Player[GetData[1]].Key_Para = true;

    if(Engine->Game->GameMain->Player[GetData[1]].Pilot == true)
      {
      long TempLong;
      memcpy(&TempLong,GetData+3,4);
      Engine->Game->GameMain->Player[GetData[1]].x	 = (float)(TempLong * 0.000001f);
      memcpy(&TempLong,GetData+7,4);
      Engine->Game->GameMain->Player[GetData[1]].y	 = (float)(TempLong * 0.000001f);
      memcpy(&TempLong,GetData+11,4);
      Engine->Game->GameMain->Player[GetData[1]].Rotate	 = (float)(TempLong * 0.000001f);
      }
    if(Engine->Game->GameMain->Player[GetData[1]].Pilot == false)
      {
      long TempLong;
      memcpy(&TempLong,GetData+3,4);
      Engine->Game->GameMain->Player_Para_And_Man[GetData[1]].x	 = (float)(TempLong * 0.000001f);
      memcpy(&TempLong,GetData+7,4);
      Engine->Game->GameMain->Player_Para_And_Man[GetData[1]].y	 = (float)(TempLong * 0.000001f);
      memcpy(&TempLong,GetData+11,4);
      Engine->Game->GameMain->Player_Para_And_Man[GetData[1]].Rotate = (float)(TempLong * 0.000001f);
      }
    }
  //----------------------------------------------------------------
  if(GetData[0] == SERVER_ANIMAL_MOVE) // Animal Move
  //----------------------------------------------------------------
    {
    Get_SERVER_ANIMAL_MOVE++;
    short TempInt;
    memcpy(&TempInt,GetData+1,2);
    Engine->Game->GameMain->Animal.Tx		 = (float)(TempInt * 0.001f);
    }
  //----------------------------------------------------------------
  if(GetData[0] == SERVER_SKY_UPDATE) // Sky Update
  //----------------------------------------------------------------
    {
    Get_SERVER_SKY_UPDATE++;

    short TempInt = 0x00;
    if((GetData[1] & 0x04) == 0)Engine->Game->GameMain->Sky[0].MovingLeft = false;
    else Engine->Game->GameMain->Sky[0].MovingLeft = true;
    if((GetData[1] & 0x08) == 0)Engine->Game->GameMain->Sky[1].MovingLeft = false;
    else Engine->Game->GameMain->Sky[1].MovingLeft = true;
    if((GetData[1] & 0x10) == 0)Engine->Game->GameMain->Sky[0].IsDark = false;
    else Engine->Game->GameMain->Sky[0].IsDark     = true;
    if((GetData[1] & 0x20) == 0)Engine->Game->GameMain->Sky[1].IsDark = false;
    else Engine->Game->GameMain->Sky[1].IsDark     = true;

    if(Engine->Game->GameMain->Sky[0].Active == false && Engine->Game->GameMain->Sky[0].MovingLeft == true  && (GetData[1] & 0x01) == 0x01)
     {
     Engine->Game->GameMain->Sky[0].x          =  10.0f;
     }
    if(Engine->Game->GameMain->Sky[0].Active == false && Engine->Game->GameMain->Sky[0].MovingLeft == false && (GetData[1] & 0x01) == 0x01)
     {
     Engine->Game->GameMain->Sky[0].x          =  -10.0f;  
     }
    if(Engine->Game->GameMain->Sky[1].Active == false && Engine->Game->GameMain->Sky[1].MovingLeft == true  && (GetData[1] & 0x02) == 0x02)
     {
     Engine->Game->GameMain->Sky[1].x          =  10.0f;
     }
    if(Engine->Game->GameMain->Sky[1].Active == false && Engine->Game->GameMain->Sky[1].MovingLeft == false && (GetData[1] & 0x02) == 0x02)
     {
     Engine->Game->GameMain->Sky[1].x          =  -10.0f;  
     }

    if((GetData[1] & 0x01) == 0)Engine->Game->GameMain->Sky[0].Active = false;
    else Engine->Game->GameMain->Sky[0].Active     = true;
    if((GetData[1] & 0x02) == 0)Engine->Game->GameMain->Sky[1].Active = false;
    else Engine->Game->GameMain->Sky[1].Active     = true;

    memcpy(&TempInt,GetData+2,2);
    Engine->Game->GameMain->Sky[0].y		 = (float)(TempInt * 0.01f);
    memcpy(&TempInt,GetData+4,2);
    Engine->Game->GameMain->Sky[1].y		 = (float)(TempInt * 0.01f);
    }
  //----------------------------------------------------------------
  if(GetData[0] == SERVER_RESETROUND) // New_Round
  //----------------------------------------------------------------
    {
    Get_SERVER_RESETROUND++;
    int i;
    short TempInt;

    Engine->Game->GameMain->Rules.Map         = GetData[1];
    Engine->Game->GameMain->Tree[0].Type      = GetData[2];
    Engine->Game->GameMain->Tree[1].Type      = GetData[3];
    Engine->Game->GameMain->Rules.Buy_Counter = GetData[4];

    for(i = 0;i<=11;i++)
      {
      if(GetData[5+i] == 0)Engine->Game->GameMain->Player[i].Active = false;
      else Engine->Game->GameMain->Player[i].Active = true;
      }
    memcpy(&TempInt,GetData+17,2);
    Engine->Game->GameMain->Animal.x		 = (float)(TempInt * 0.001f);
    memcpy(&TempInt,GetData+19,2);
    Engine->Game->GameMain->Animal.Sleep_Pause	 = (float)(TempInt * 0.001f);
    memcpy(&TempInt,GetData+21,2);
    Engine->Game->GameMain->Tree[0].x		 = (float)(TempInt * 0.001f);
    memcpy(&TempInt,GetData+23,2);
    Engine->Game->GameMain->Tree[1].x		 = (float)(TempInt * 0.001f);

    memcpy(&TempInt,GetData+25,2);
    Engine->Game->GameMain->RedTeam_Score	 = TempInt;
    memcpy(&TempInt,GetData+27,2);
    Engine->Game->GameMain->GreenTeam_Score	 = TempInt;

    for(i = 0;i<=11;i++)
      {
      memcpy(&TempInt,GetData+29+(i*2),2);
      Engine->Game->GameMain->Player[i].Hits	 = TempInt;
      }
    memcpy(&TempInt,GetData+53,2);
    Engine->Game->GameMain->Player[Engine->Game->GameMain->Net_Id].Money = TempInt;
    //--------------------------- Normal Reset ------------------------------//
    for(i = 0;i<= 199;i++){Engine->Game->GameMain->Particle[i].Life = 0.0f;}
    for(i = 0;i<= 11;i++)
      {
      Engine->Game->GameMain->Explo[i].Active	   = false;
      Engine->Game->GameMain->Shot[i].Active	   = false;
      Engine->Game->GameMain->Shot[i].Type	   = 0;
      Engine->Game->GameMain->Spec[i].Active	   = false;
      Engine->Game->GameMain->Spec[i].Type	   = 0;
      Engine->Game->GameMain->Equip[i].Option_Ok   = false;
      Engine->Game->GameMain->Equip[i].Option_Selected = '3';
      Engine->Game->GameMain->Player[i].SpecInvert   = false;
      Engine->Game->GameMain->Player[i].SpecBlind    = 0.0f;
      Engine->Game->GameMain->Player[i].SpecSpeedHit = 1.0f;
      Engine->Game->GameMain->Player[i].Dead	     = true;
      if(Engine->Game->GameMain->Player[i].Active == true){Engine->Game->GameMain->Player[i].Dead = false;}
      Engine->Game->GameMain->Player[i].Damage	 = 0;
      Engine->Game->GameMain->Player[i].Key_Down     = false;
      Engine->Game->GameMain->Player[i].Key_Up       = false;
      Engine->Game->GameMain->Player[i].Key_Left     = false;
      Engine->Game->GameMain->Player[i].Key_Right    = false;
      Engine->Game->GameMain->Player[i].Key_Fire     = false;
      Engine->Game->GameMain->Player[i].Key_Spec     = false;
      Engine->Game->GameMain->Player[i].Key_Para     = false;
      Engine->Game->GameMain->Player[i].Pilot	 = true;
      Engine->Game->GameMain->Player[i].Cloak	 = 1.0f;
      Engine->Game->GameMain->Player[i].CloakUp	 = false;
      Engine->Game->GameMain->Player_Para_And_Man[i].IsSphere = false;
      Engine->Game->GameMain->Player_Para_And_Man[i].IsMan    = false;
      Engine->Game->GameMain->Player_Para_And_Man[i].IsPara   = false;
      Engine->Game->GameMain->Player_Para_And_Man[i].ParaDead = false;
      Engine->Game->GameMain->Player_Para_And_Man[i].Rotate   = 0.0f;
      Engine->Game->GameMain->Sphere[i].Active   = false;

      if((Engine->Game->GameMain->Equip[i].Option_Plane & 0x04) == 0x04)Engine->Game->GameMain->Player[i].Damage = -1;

      if(i ==  0)Engine->Game->GameMain->Player[0].y  =  5.0f;
      if(i ==  1)Engine->Game->GameMain->Player[1].y  =  5.0f;
      if(i ==  2)Engine->Game->GameMain->Player[2].y  =  3.0f;
      if(i ==  3)Engine->Game->GameMain->Player[3].y  =  3.0f;
      if(i ==  4)Engine->Game->GameMain->Player[4].y  =  1.0f;
      if(i ==  5)Engine->Game->GameMain->Player[5].y  =  1.0f;
      if(i ==  6)Engine->Game->GameMain->Player[6].y  = -1.0f;
      if(i ==  7)Engine->Game->GameMain->Player[7].y  = -1.0f;
      if(i ==  8)Engine->Game->GameMain->Player[8].y  = -3.0f;
      if(i ==  9)Engine->Game->GameMain->Player[9].y  = -3.0f;
      if(i == 10)Engine->Game->GameMain->Player[10].y = -5.0f;
      if(i == 11)Engine->Game->GameMain->Player[11].y = -5.0f;
      if(i ==  0){Engine->Game->GameMain->Player[0].x  =  6.0f;Engine->Game->GameMain->Player[i].Rotate = 90.0f;}
      if(i ==  1){Engine->Game->GameMain->Player[1].x  = -6.0f;Engine->Game->GameMain->Player[i].Rotate = 270.0f;}
      if(i ==  2){Engine->Game->GameMain->Player[2].x  =  6.0f;Engine->Game->GameMain->Player[i].Rotate = 90.0f;}
      if(i ==  3){Engine->Game->GameMain->Player[3].x  = -6.0f;Engine->Game->GameMain->Player[i].Rotate = 270.0f;}
      if(i ==  4){Engine->Game->GameMain->Player[4].x  =  6.0f;Engine->Game->GameMain->Player[i].Rotate = 90.0f;}
      if(i ==  5){Engine->Game->GameMain->Player[5].x  = -6.0f;Engine->Game->GameMain->Player[i].Rotate = 270.0f;}
      if(i ==  6){Engine->Game->GameMain->Player[6].x  =  6.0f;Engine->Game->GameMain->Player[i].Rotate = 90.0f;}
      if(i ==  7){Engine->Game->GameMain->Player[7].x  = -6.0f;Engine->Game->GameMain->Player[i].Rotate = 270.0f;}
      if(i ==  8){Engine->Game->GameMain->Player[8].x  =  6.0f;Engine->Game->GameMain->Player[i].Rotate = 90.0f;}
      if(i ==  9){Engine->Game->GameMain->Player[9].x  = -6.0f;Engine->Game->GameMain->Player[i].Rotate = 270.0f;}
      if(i == 10){Engine->Game->GameMain->Player[10].x =  6.0f;Engine->Game->GameMain->Player[i].Rotate = 90.0f;}
      if(i == 11){Engine->Game->GameMain->Player[11].x = -6.0f;Engine->Game->GameMain->Player[i].Rotate = 270.0f;}
      Engine->Game->GameMain->Player[i].Speed	 = 1.0f;
      }
    for(i = 0;i<=14;i++)Engine->Game->GameMain->Map3_Active[i] = true;

    Engine->Game->GameMain->Rules.GameState_Waiting = false;
    Engine->Game->GameMain->Rules.GameState_Prepare = false;
    Engine->Game->GameMain->Rules.GameState_Playing = false;
    Engine->Game->GameMain->Rules.GameState_Buying  = true;
    Engine->Game->GameMain->Rules.Buy_Time		= 1.0f;
    Engine->Game->GameMain->Rules.Game_Counter	        = 2;
    Engine->Game->GameMain->Rules.Game_Time		= 1.0f;

    Engine->Game->GameMain->Animal.Pointing_Left    = false;
    Engine->Game->GameMain->Animal.Dead		    = false;
    Engine->Game->GameMain->Animal.Tx		 = Engine->Game->GameMain->Animal.x;
    Engine->Game->GameMain->Tree[0].Burning		= false;
    Engine->Game->GameMain->Tree[1].Burning		= false;
    Engine->Game->GameMain->Sky[0].Active		= false;
    Engine->Game->GameMain->Sky[1].Active		= false;
    Engine->Game->GameMain->Color			= 1.0f;
    Engine->Game->GameMain->Drugs_Effect		= 0.0f;
    Engine->Game->GameMain->Drugs_On			= false;
    Engine->Game->GameMain->NewRound_Count		= 2;
    Engine->Game->GameMain->NewRound_Second		= 1.0f;
    Engine->Game->GameMain->GameOver			= false;
    }
  GetData[0] = 0;
  }
}

//------------------------------------------------------------------
void CGameNetWork::Client_SendData(SEngine *Engine)
//------------------------------------------------------------------
{
//----------------- KeyBoard Check ------------------------------//
if(Engine->Keys[VK_LEFT]    != Client_KeyPress_Left
|| Engine->Keys[VK_RIGHT]   != Client_KeyPress_Right
|| Engine->Keys[VK_UP]      != Client_KeyPress_Up
|| Engine->Keys[VK_DOWN]    != Client_KeyPress_Down 
|| Engine->Keys[VK_SPACE]   != Client_KeyPress_Fire 
|| Engine->Keys['E']        != Client_KeyPress_Para 
|| Engine->Keys[VK_CONTROL] != Client_KeyPress_Spec)
  {
  char Temp = 0;
  char Data[3];
  if(Engine->Keys[VK_LEFT])			{Temp |= 0x01;}
  if(Engine->Keys[VK_RIGHT])			{Temp |= 0x02;}
  if(Engine->Keys[VK_UP])			{Temp |= 0x04;}
  if(Engine->Keys[VK_DOWN])			{Temp |= 0x08;}
  if(Engine->Keys[VK_SPACE])			{Temp |= 0x10;}
  if(Engine->Keys[VK_CONTROL])			{Temp |= 0x20;}
  if(Engine->Keys['E'])				{Temp |= 0x40;}

  Client_KeyPress_Left    = Engine->Keys[VK_LEFT];
  Client_KeyPress_Right   = Engine->Keys[VK_RIGHT];
  Client_KeyPress_Down 	  = Engine->Keys[VK_DOWN];
  Client_KeyPress_Up 	  = Engine->Keys[VK_UP];
  Client_KeyPress_Fire    = Engine->Keys[VK_SPACE];
  Client_KeyPress_Spec    = Engine->Keys[VK_CONTROL];
  Client_KeyPress_Para    = Engine->Keys['E'];

  Data[0] = CLIENT_KEYS_PACKET;
  Data[1] = Engine->Game->GameMain->Net_Id;
  Data[2] = Temp;

  Engine->WinSock->Client_SendData(Data,3);

  Send_CLIENT_KEYS_PACKET++;
  }
}

//------------------------------------------------------------------
void CGameNetWork::Server_SendKeysUpdate(SEngine *Engine,char Player)
//------------------------------------------------------------------
{
if(Engine->Game->GameMain->Rules.GameState_Buying == true ||
(Engine->Game->GameMain->Player[Player].Key_Fire  == true && Engine->Game->GameMain->Shot[Player].Active == false) ||
(Engine->Game->GameMain->Player[Player].Key_Spec  == true && Engine->Game->GameMain->Spec[Player].Active == false) ||
(Engine->Game->GameMain->Player[Player].Key_Para  == true))
{
char Data_Packet[13],Temp,i;

Data_Packet[0] = SERVER_KEYS_UPDATE;

Temp = 0x00;
if(Engine->Game->GameMain->Player[Player].Key_Left  == true){Temp |= 0x01;}
if(Engine->Game->GameMain->Player[Player].Key_Right == true){Temp |= 0x02;}
if(Engine->Game->GameMain->Player[Player].Key_Up    == true){Temp |= 0x04;}
if(Engine->Game->GameMain->Player[Player].Key_Down  == true){Temp |= 0x08;}
if(Engine->Game->GameMain->Player[Player].Key_Fire  == true){Temp |= 0x10;}
if(Engine->Game->GameMain->Player[Player].Key_Spec  == true){Temp |= 0x20;}
if(Engine->Game->GameMain->Player[Player].Key_Para  == true){Temp |= 0x40;}

Data_Packet[1] = Player;
Data_Packet[2] = Temp;

if(Engine->Game->GameMain->Player[Player].Pilot == true)
  {
  long TempLong;
  TempLong           = (long)(((Engine->Game->GameMain->Player[Player].x)) * 1000000);
  memcpy(Data_Packet+3,&TempLong,4); 
  TempLong           = (long)(((Engine->Game->GameMain->Player[Player].y)) * 1000000);
  memcpy(Data_Packet+7,&TempLong,4);
  TempLong           = (long)(((Engine->Game->GameMain->Player[Player].Rotate)) * 1000000);
  memcpy(Data_Packet+11,&TempLong,4);
  }

if(Engine->Game->GameMain->Player[Player].Pilot == false)
  {
  long TempLong;
  TempLong           = (long)(((Engine->Game->GameMain->Player_Para_And_Man[Player].x)) * 1000000);
  memcpy(Data_Packet+3,&TempLong,4); 
  TempLong           = (long)(((Engine->Game->GameMain->Player_Para_And_Man[Player].y)) * 1000000);
  memcpy(Data_Packet+7,&TempLong,4);
  TempLong           = (long)(((Engine->Game->GameMain->Player_Para_And_Man[Player].Rotate)) * 1000000);
  memcpy(Data_Packet+11,&TempLong,4);
  }

for(i = 1;i<=11;i++)
  {
  if(Engine->Game->GameMain->Player[i].Active == true)
    {
    Engine->WinSock->Server_LoadIP(i);
    Engine->WinSock->Server_SendData(Data_Packet,15);
    Send_SERVER_KEYS_UPDATE++;
    }
  }
}
}
//------------------------------------------------------------------
void CGameNetWork::Server_SendNameBroadCast(SEngine *Engine)
//------------------------------------------------------------------
{
char Data_Packet[845];
int  i;

for(i = 0;i<=11;i++)
  {
  Data_Packet[0] = SERVER_BROADCAST_WELCOME;
  memcpy(Data_Packet+1+(i*70),Engine->Game->GameMain->Player[i].Name,69);
  }
for(i = 1;i<=11;i++)
  {
  if(Engine->Game->GameMain->Player[i].Active == true)
    {
    Engine->WinSock->Server_LoadIP(i);
    Engine->WinSock->Server_SendData(Data_Packet,845);
    Send_SERVER_BROADCAST_WELCOME++;
    }
  }
}
//------------------------------------------------------------------
void CGameNetWork::Server_SendAnimalDestinate(SEngine *Engine)
//------------------------------------------------------------------
{
char Data_Packet[4];
int TempInt,i;
Data_Packet[0] = SERVER_ANIMAL_MOVE;

TempInt           = (short)(((Engine->Game->GameMain->Animal.Tx)) * 1000);
memcpy(Data_Packet+ 1,&TempInt,2); 

for(i = 1;i<=11;i++)
  {
  if(Engine->Game->GameMain->Player[i].Active == true)
    {
    Engine->WinSock->Server_LoadIP(i);
    Engine->WinSock->Server_SendData(Data_Packet,3);
    Send_SERVER_ANIMAL_MOVE++;
    }
  }
}
//------------------------------------------------------------------
void CGameNetWork::Server_SendNewRound(SEngine *Engine)
//------------------------------------------------------------------
{
char Data_Packet[60],i;
int  TempInt;

Data_Packet[0] = SERVER_RESETROUND;
Data_Packet[1] = Engine->Game->GameMain->Rules.Map;
Data_Packet[2] = Engine->Game->GameMain->Tree[0].Type;
Data_Packet[3] = Engine->Game->GameMain->Tree[1].Type;
Data_Packet[4] = Engine->Setting->Option_BuyTime;
for(i = 0;i<=11;i++)
  {
  if(Engine->Game->GameMain->Player[i].Active == true)Data_Packet[5+i] = 1;
  else Data_Packet[5+i] = 0;
  }

TempInt           = (short)(((Engine->Game->GameMain->Animal.x)) * 1000);
memcpy(Data_Packet+ 17 ,&TempInt,2); 
TempInt           = (short)(((Engine->Game->GameMain->Animal.Sleep_Pause)) * 1000);
memcpy(Data_Packet+ 19 ,&TempInt,2); 
TempInt           = (short)(((Engine->Game->GameMain->Tree[0].x)) * 1000);
memcpy(Data_Packet+ 21 ,&TempInt,2); 
TempInt           = (short)(((Engine->Game->GameMain->Tree[1].x)) * 1000);
memcpy(Data_Packet+ 23,&TempInt,2); 
TempInt           = (short) Engine->Game->GameMain->RedTeam_Score;
memcpy(Data_Packet+ 25,&TempInt,2); 
TempInt           = (short) Engine->Game->GameMain->GreenTeam_Score;
memcpy(Data_Packet+ 27,&TempInt,2); 

for(i = 0;i<=11;i++)
  {
  TempInt           = (short) Engine->Game->GameMain->Player[i].Hits ;
  memcpy(Data_Packet+ 29+(i*2),&TempInt,2); 
  }

for(i = 1;i<=11;i++)
  {
  if(Engine->Game->GameMain->Player[i].Active == true)
    {
    TempInt           = (short)Engine->Game->GameMain->Player[i].Money;
    memcpy(Data_Packet+ 53,&TempInt,2); 

    Engine->WinSock->Server_LoadIP(i);
    Engine->WinSock->Server_SendData(Data_Packet,55);
    Send_SERVER_RESETROUND++;   
    }
  }
}
//------------------------------------------------------------------
void CGameNetWork::Server_SendSkyUpdate(SEngine *Engine)
//------------------------------------------------------------------
{
char Data_Packet[7];
int TempInt,i;
Data_Packet[0] = SERVER_SKY_UPDATE;

Data_Packet[1] = 0x00;
if(Engine->Game->GameMain->Sky[0].Active     == true)Data_Packet[1] |= 0x01;
if(Engine->Game->GameMain->Sky[1].Active     == true)Data_Packet[1] |= 0x02;
if(Engine->Game->GameMain->Sky[0].MovingLeft == true)Data_Packet[1] |= 0x04;
if(Engine->Game->GameMain->Sky[1].MovingLeft == true)Data_Packet[1] |= 0x08;
if(Engine->Game->GameMain->Sky[0].IsDark     == true)Data_Packet[1] |= 0x10;
if(Engine->Game->GameMain->Sky[1].IsDark     == true)Data_Packet[1] |= 0x20;

TempInt           = (short)(((Engine->Game->GameMain->Sky[0].y)) * 100);
memcpy(Data_Packet+ 2,&TempInt,2); 
TempInt           = (short)(((Engine->Game->GameMain->Sky[1].y)) * 100);
memcpy(Data_Packet+ 4,&TempInt,2); 

for(i = 1;i<=11;i++)
  {
  if(Engine->Game->GameMain->Player[i].Active == true)
    {
    Engine->WinSock->Server_LoadIP(i);
    Engine->WinSock->Server_SendData(Data_Packet,6);
    Send_SERVER_SKY_UPDATE++;
    }
  }
}

//------------------------------------------------------------------
void CGameNetWork::Server_SendBuyMenuOK(SEngine *Engine)
//------------------------------------------------------------------
{
char Data_Packet[1];
Data_Packet[0] = SERVER_BUYMENU_STATUS_OK;
for(char i = 1;i<=11;i++)
  {
  if(Engine->Game->GameMain->Player[i].Active == true)
    {
    Engine->WinSock->Server_LoadIP(i);
    Engine->WinSock->Server_SendData(Data_Packet,1);
    Send_SERVER_BUYMENU_STATUS_OK++;
    }
  }
}

//------------------------------------------------------------------
void CGameNetWork::Server_SendEquip(SEngine *Engine)
//------------------------------------------------------------------
{
char Data_Packet[50];

Data_Packet[0] = SERVER_EQUIP_PACKET;

for(char i=0;i<=11;i++)
  {
  Data_Packet[1+(i*4)] = Engine->Game->GameMain->Equip[i].Option_Plane;
  Data_Packet[2+(i*4)] = Engine->Game->GameMain->Equip[i].Option_Para;
  Data_Packet[3+(i*4)] = Engine->Game->GameMain->Equip[i].Option_Shot;
  Data_Packet[4+(i*4)] = Engine->Game->GameMain->Equip[i].Option_Spec;
  }
for(i = 1;i<=11;i++)
  {
  if(Engine->Game->GameMain->Player[i].Active == true)
    {
    Engine->WinSock->Server_LoadIP(i);
    Engine->WinSock->Server_SendData(Data_Packet,49);
    Send_SERVER_EQUIP_PACKET++;
    }
  }
}

//------------------------------------------------------------------
void CGameNetWork::Server_SendSync(SEngine *Engine)
//------------------------------------------------------------------
{
char Data_Packet[312],i;
long TempLong;
int  TempInt;
char Active_Players = 0;

for(i=11;i>=0;i--)
{
	if(i >= 12 || Engine->Game->GameMain->Player[i].Active == true){break;}

	if(Engine->Game->GameMain->Player[i].Active == false)
	{
		Active_Players = i;
	}
}

Data_Packet[0] = SERVER_SYNC_PACKET;

/**************************************/
/*   Optimicing networks code so      */
/*   sync only send timer...	      */
/*				      */
/**************************************/

/**************************************/
/*   Optimicing networks code so      */
/*   fewer players means fewer bytes  */
/*   send across the net	      */
/**************************************/

for(i=0;i<=11;i++)
  {
  char Temp = 0x00;
  if(Engine->Game->GameMain->Player[i].Key_Left  == true){Temp |= 0x01;}
  if(Engine->Game->GameMain->Player[i].Key_Right == true){Temp |= 0x02;}
  if(Engine->Game->GameMain->Player[i].Key_Up    == true){Temp |= 0x04;}
  if(Engine->Game->GameMain->Player[i].Key_Down  == true){Temp |= 0x08;}
  if(Engine->Game->GameMain->Player[i].Key_Fire  == true){Temp |= 0x10;}
  if(Engine->Game->GameMain->Player[i].Key_Spec  == true){Temp |= 0x20;}
  if(Engine->Game->GameMain->Player[i].Key_Para  == true){Temp |= 0x40;}
  Data_Packet[1+i] = Temp;
  }

for(i=0;i<=Active_Players;i++)
  {
  TempLong           = (long)(((Engine->Game->GameMain->Player[i].x)) * 1000000);
  memcpy(Data_Packet+  13+(i*21),&TempLong,4); 
  TempLong           = (long)(((Engine->Game->GameMain->Player[i].y)) * 1000000);
  memcpy(Data_Packet+  17+(i*21),&TempLong,4); 
  TempInt           = (short)(((Engine->Game->GameMain->Player[i].Rotate)) * 10);
  memcpy(Data_Packet+  21+(i*21),&TempInt,2); 

  TempLong           = (long)(((Engine->Game->GameMain->Player_Para_And_Man[i].x)) * 1000000);
  memcpy(Data_Packet+  23+(i*21),&TempLong,4); 
  TempLong           = (long)(((Engine->Game->GameMain->Player_Para_And_Man[i].y)) * 1000000);
  memcpy(Data_Packet+  27+(i*21),&TempLong,4); 
  TempInt           = (short)(((Engine->Game->GameMain->Player_Para_And_Man[i].Rotate)) * 10);
  memcpy(Data_Packet+  31+(i*21),&TempInt,2); 
  }

for(i = 1;i<=11;i++)
  {
  if(Engine->Game->GameMain->Player[i].Active == true && Player_Ready_To_Next_Packet[i] == true)
    {
    Engine->WinSock->Server_LoadIP(i);
    Player_Ready_To_Next_Packet[i] = false;

    QueryPerformanceCounter(&Client_Ping_Temp);
    Client_Ping_Send_Packet[i] = (double)Client_Ping_Temp.QuadPart;
    Engine->WinSock->Server_SendData(Data_Packet,14+((Active_Players++)*21));
    Send_SERVER_SYNC_PACKET++;
    }
  }
//------ Reset Wait on Ping packet -----//
if(Send_SERVER_SYNC_PACKET % 20 == 0){for(i = 1;i<=11;i++){Player_Ready_To_Next_Packet[i] = true;}}
//////////////////////////////////////////
}

//------------------------------------------------------------------
void CGameNetWork::Server_GameOver_Packet(SEngine *Engine)
//------------------------------------------------------------------
{
char Data_Packet[1];
Data_Packet[0] = SERVER_GAME_OVER;
for(char i = 1;i<=11;i++)
  {
  if(Engine->Game->GameMain->Player[i].Active == true)
    {
    Engine->WinSock->Server_LoadIP(i);
    Engine->WinSock->Server_SendData(Data_Packet,1);
    Send_SERVER_GAME_OVER++;
    }
  }
}

//------------------------------------------------------------------
void CGameNetWork::Client_SendEquip(SEngine *Engine,char Buy)
//------------------------------------------------------------------
{
char Data_Packet[3];
Data_Packet[0] = CLIENT_BUY_PACKET;
Data_Packet[1] = Engine->Game->GameMain->Net_Id;
Data_Packet[2] = Buy;
Engine->WinSock->Client_SendData(Data_Packet,3);
Send_CLIENT_BUY_PACKET++;
}

//------------------------------------------------------------------
void CGameNetWork::Server_Collision(SEngine *Engine,char source,char target,char type)
//------------------------------------------------------------------
{
char Data_Packet[3];
Data_Packet[0] = type;
Data_Packet[1] = source;
Data_Packet[2] = target;

for(char i = 1;i<=11;i++)
  {
  if(Engine->Game->GameMain->Player[i].Active == true)
    {
    Engine->WinSock->Server_LoadIP(i);
    Engine->WinSock->Server_SendData(Data_Packet,3);

    if(SERVER_COLLISION_FIRE         == type)Send_SERVER_COLLISION_FIRE++;
    if(SERVER_COLLISION_SPEC         == type)Send_SERVER_COLLISION_SPEC++;
    if(SERVER_COLLISION_MAN          == type)Send_SERVER_COLLISION_MAN++;
    if(SERVER_COLLISION_PARA         == type)Send_SERVER_COLLISION_PARA++;
    if(SERVER_COLLISION_PLAYER       == type)Send_SERVER_COLLISION_PLAYER++;
    if(SERVER_COLLISION_MAN_SHOT     == type)Send_SERVER_COLLISION_MAN_SHOT++;
    if(SERVER_COLLISION_PARA_SHOT    == type)Send_SERVER_COLLISION_PARA_SHOT++;
    if(SERVER_COLLISION_PLAYER_EXPLO == type)Send_SERVER_COLLISION_PLAYER_EXPLO++;
    if(SERVER_COLLISION_WALL         == type)Send_SERVER_COLLISION_WALL++;
    if(SERVER_COLLISION_TREE         == type)Send_SERVER_COLLISION_TREE++;
    }
  }
}

//------------------------------------------------------------------
void CGameNetWork::Server_SendParaJump(SEngine *Engine,char Player)
//------------------------------------------------------------------
{
char Data_Packet[2];

Data_Packet[0] = SERVER_PARA_PACKET;
Data_Packet[1] = Player;

for(char i = 1;i<=11;i++)
  {
  if(Engine->Game->GameMain->Player[i].Active == true)
    {
    Engine->WinSock->Server_LoadIP(i);
    Engine->WinSock->Server_SendData(Data_Packet,2);
    Send_SERVER_PARA_PACKET++;
    }
  }
}
