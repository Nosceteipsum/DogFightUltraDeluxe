////////////////////////////////////////////////////////////////////
//								  //
//	  	  DFUD: CGameMain_h			  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#if!defined CGameMain_H
#define CGameMain_H

//--------------------------------------------------------//
//--			Struct/classes			--//
//--------------------------------------------------------//

struct SSphere
{
float x,y,Rotate,Speed,SpeedDown,Rotating;
bool Active;
char Bounce;
};

struct SSky
{
float x,y;
bool MovingLeft;
bool IsDark;
bool Active;
};

struct SParticle
{
float x,y,Life;
bool IsSmoke;
bool IsFire;
bool IsTreeFire;
};

struct SEquip
{
char Option_Plane;
char Option_Para;
char Option_Shot;
char Option_Spec;
bool Option_Ok;
char Option_Selected;
bool Option_Key_Moved_Left;
bool Option_Key_Moved_Right;
bool Option_Key_Moved_Up;
bool Option_Key_Moved_Down;
};

struct SExplo
{
float x,y,grow;
bool Active;
};

struct SShot
{
float x,y,Rotate,Cloak;
bool Active;
char Type;
};

struct SSpec
{
float x,y,Rotate;
bool Active;
char Type;
};

struct STree
{
float x;
char Type;
bool Burning;
};

struct SAnimal
{
float x,Tx;
float Sleep_Pause;

bool Dead;
bool Pointing_Left;
};

struct SPlayer_Para_And_Man
{
float x,y,Rotate,Cloak;
bool IsSphere;
bool IsPara;
bool IsMan;
bool ParaDead;
};

struct SPlayer
{
float x,y,Rotate,Speed,SpecSpeedHit,Cloak;
bool Key_Left,
     Key_Right,
     Key_Up,
     Key_Down,
     Key_Fire,
     Key_Spec,
     Key_Para;

int  Hits;
int  Money;

char Damage; // 0: Normal  1: Smoke/halv-Engine  2: Fire/No-Engine
bool CloakUp;
bool Dead;
bool Active;
bool Pilot;
bool SpecInvert;
float SpecBlind;
char Name[75];
};

struct SRules
{
char Map;
bool GameState_Playing;
bool GameState_Buying;
bool GameState_Prepare;
bool GameState_Waiting;

float Buy_Time;
char  Buy_Counter;

char   Game_Counter;
float  Game_Time;
};

class CGameMain
{
public:

CGameMain();
~CGameMain();

void Main(SEngine *Engine);

void DrawMap(SEngine *Engine);
void DrawPlane(SEngine *Engine);
void DrawAnimal(SEngine *Engine);
void DrawBuyMenu(SEngine *Engine);
void DrawPlayerName(SEngine *Engine);
void DrawTree(SEngine *Engine);
void DrawPara(SEngine *Engine);
void DrawMen(SEngine *Engine);
void DrawFPS(SEngine *Engine);
void DrawExplosion(SEngine *Engine);
void DrawShot(SEngine *Engine);
void DrawSpec(SEngine *Engine);
void DrawParticle(SEngine *Engine);
void DrawSky(SEngine *Engine);
void DrawPacket(SEngine *Engine);
void Draw_ServerClose(SEngine *Engine);
void DrawPing(SEngine *Engine);
void DrawSphere(SEngine *Engine);

void MoveParticle(SEngine *Engine);
void MoveShot(SEngine *Engine);
void MovePara(SEngine *Engine);
void MoveSpec(SEngine *Engine);
void MoveSky(SEngine *Engine);
void MovePlayers(SEngine *Engine);
void MoveSphere(SEngine *Engine);

void HandleAnimal(SEngine *Engine);
void HandleBuyMenu(SEngine *Engine);
void HandleCountDown(SEngine *Engine);
void HandlePlayers(SEngine *Engine);
void HandleMen(SEngine *Engine);
void HandlePara(SEngine *Engine);
void HandleKeys(SEngine *Engine);
void HandleGameOver(SEngine *Engine);
void HandleAI(SEngine *Engine,char Who);
void HandleExplosion(SEngine *Engine);
void HandleParticle(SEngine *Engine);
void HandleSky(SEngine *Engine);
void HandleAutoPilot(SEngine *Engine,char Target_Player);
void HandleDrugs(SEngine *Engine);
void HandleSphere(SEngine *Engine);
void HandleRemoteExplosion(SEngine *Engine);

void Collision_Wall(SEngine *Engine);
void Collision_Shot(SEngine *Engine);
void Collision_Spec(SEngine *Engine);
void Collision_Explosion(SEngine *Engine);
void Collision_Tiger(SEngine *Engine);
void Collision_Sky(SEngine *Engine);
void Collision_Plane(SEngine *Engine);
void Collision_Tree(SEngine *Engine);

void Man_Spec(SEngine *Engine,char Target_Player);
void Man_Fire(SEngine *Engine,char Target_Player);
void Player_Spec(SEngine *Engine,char Target_Player);
void Player_Fire(SEngine *Engine,char Target_Player);
void Player_JumpPara(SEngine *Engine,char Target_Player);
void Plane_Explosion(SEngine *Engine,char Target_Player);

void LoadTexture(SEngine *Engine);
void UnLoadTexture(SEngine *Engine);
void ResetRound(SEngine *Engine);

SRules Rules;
SPlayer Player[12];
SSphere Sphere[12];
SPlayer_Para_And_Man Player_Para_And_Man[12];
SAnimal Animal;
STree Tree[2];
SExplo Explo[12];
SShot Shot[12];
SSpec Spec[12];
SEquip Equip[12];
SParticle Particle[200];
SSky Sky[2];

int GreenTeam_Score;
int RedTeam_Score;

bool   GameOver;
char   Net_Id;

float NewRound_Second;
char  NewRound_Count;
float Color;
bool  Map3_Active[15];

int   Packet_Count;
bool  Packet_Show;

bool  Server_Close;
bool  Ping_Show;

float Drugs_Effect;
bool  Drugs_On;

bool  CBot;

protected:
private:

TextureImageTGA Tex_Grass1;
TextureImageTGA Tex_Grass2;
TextureImageTGA Tex_Grass3;
TextureImageTGA Tex_Grass3D;
TextureImageTGA Tex_Grass4;

TextureImageTGA Tex_Cow_L;
TextureImageTGA Tex_Sheep_L;
TextureImageTGA Tex_Lion_L;
TextureImageTGA Tex_Cow_R;
TextureImageTGA Tex_Sheep_R;
TextureImageTGA Tex_Lion_R;
TextureImageTGA Tex_Cow_D;
TextureImageTGA Tex_Sheep_D;
TextureImageTGA Tex_Lion_D;

TextureImageTGA Tex_Tree1;
TextureImageTGA Tex_Tree2;
TextureImageTGA Tex_Tree3;

TextureImageTGA Tex_Green_Plane;
TextureImageTGA Tex_Green_Man;
TextureImageTGA Tex_Green_Para;
TextureImageTGA Tex_Green_Para_D;
TextureImageTGA Tex_Red_Plane;
TextureImageTGA Tex_Red_Man;
TextureImageTGA Tex_Red_Para;
TextureImageTGA Tex_Red_Para_D;

TextureImageTGA Tex_Menu;
TextureImageTGA Tex_Menu_Selected;
TextureImageTGA Tex_Menu_Bought;

TextureImageTGA Tex_Shot;
TextureImageTGA Tex_Spec;
TextureImageTGA Tex_Sphere;

TextureImageTGA Tex_Sky;
TextureImageTGA Tex_Sky_Dark;

TextureImageTGA Tex_Pointer;

bool  FPS_Show;
float FPS_Second;
int   FPS_Frames,FPS_Temp_Frames;

bool  AI_Active;
};

//--------------------------------------------------------//
//--			Prototypes			--//
//--------------------------------------------------------//


#endif
