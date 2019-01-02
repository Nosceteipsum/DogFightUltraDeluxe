////////////////////////////////////////////////////////////////////
//								  //
//	  	  DFUD: CGameMain_cpp		  		  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#include "../../global.h"

#define PLAYER_MAXMONEY		     5000
#define PLAYER_MAXPLANE_SPEED         1.0f
#define PLAYER_PLANETURN_SPEED       80.0f
#define PLAYER_MAXPLANE_SMOKE_SPEED   0.10f
#define PLAYER_PARA_SPEED             0.3f
#define PLAYER_MAN_SPEED              0.2f

#define SHOT_SPEED                   3.0f
#define SPEC_SPEED                   2.5f

#define ANIMAL_COW_SPEED              0.4f
#define ANIMAL_SHEEP_SPEED            0.15f
#define ANIMAL_LION_SPEED             0.9f

//------------------------------------------------------------------
CGameMain::CGameMain()
//------------------------------------------------------------------
{
for(char i = 0;i<=11;i++){Player[i].Hits  = 0;
			  Player[i].Active = false;
			  Player[i].Money  = 0;
			  if(i != 0)memcpy(Player[i].Name,"Empty",6);
		          Equip[i].Option_Plane  = 0;
			  Equip[i].Option_Para	 = 0;
			  Equip[i].Option_Shot   = 0;
			  Equip[i].Option_Spec   = 0;
  		         }

Server_Close = false;

FPS_Show = false;
FPS_Second = 1.0f;
FPS_Frames = 0;
FPS_Temp_Frames = 0;

Packet_Count = 0;
Packet_Show  = false;

Ping_Show    = false;

GreenTeam_Score = 0;
RedTeam_Score = 0;

Drugs_Effect = 0.0f;
Drugs_On     = false;

CBot	     = false;
}

//------------------------------------------------------------------
CGameMain::~CGameMain()
//------------------------------------------------------------------
{
}

//------------------------------------------------------------------
void CGameMain::Main(SEngine *Engine)
//------------------------------------------------------------------
{
if(Rules.GameState_Waiting == false)glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
if(Rules.GameState_Waiting == true){return;}

glLoadIdentity();
glColor3f(Color,Color,Color);
glClearColor(0.0f, 0.0f,(0.3f*Color), 0.0f);

gluLookAt(0.0f,0.0f,0.0f-Drugs_Effect,	
	  0.0f,0.0f,-100.0f,	
	  0.0f+Drugs_Effect,1.0f,0.0f);

if(FPS_Show     == true)DrawFPS(Engine);
if(Packet_Show  == true)DrawPacket(Engine);
if(Ping_Show    == true)DrawPing(Engine);
if(Server_Close == true)Draw_ServerClose(Engine);

if(Engine->Keys[VK_F1] == true){FPS_Show = true;}
if(Engine->Keys[VK_F2] == true){FPS_Show = false;}
if(Engine->Keys[VK_F3] == true){Packet_Show = true;}
if(Engine->Keys[VK_F4] == true){Packet_Show = false;}
if(Engine->Keys[VK_F5] == true){Ping_Show = true;}
if(Engine->Keys[VK_F6] == true){Ping_Show = false;}
//if(Engine->Server == true && Engine->Keys[VK_F7] == true && Engine->Game->GameMain->Rules.GameState_Prepare == true && Engine->Game->GameMain->Player[11].Active == false){Player[11].Active = true;Player[11].Dead = false;AI_Active = true;memcpy(Player[11].Name,"A.I",4);}
//if(Engine->Server == true && Engine->Keys[VK_F8] == true && Engine->Game->GameMain->Rules.GameState_Prepare == true){Player[11].Active = false;Player[11].Dead = true;AI_Active = false;memcpy(Player[11].Name,"Empty",6);}
if(Engine->Keys[VK_F7] == true){CBot = true;}
if(Engine->Keys[VK_F8] == true){CBot = false;}

if(Rules.GameState_Prepare == true)
  {
  DrawPlayerName(Engine);
  HandleCountDown(Engine);
  DrawPlane(Engine);
  if(Engine->Server == true)HandleKeys(Engine);
  }

if(Rules.GameState_Buying == true)
  {
  DrawBuyMenu(Engine);
  HandleBuyMenu(Engine);
  if(Engine->Server == true)HandleKeys(Engine);
  }

if(Rules.GameState_Playing == true)
  {
  DrawExplosion(Engine);
  DrawPara(Engine);
  DrawMen(Engine);
  DrawPlane(Engine);
  DrawShot(Engine);
  DrawSpec(Engine);
  DrawParticle(Engine);
  DrawSky(Engine);
  DrawSphere(Engine);

  if(GameOver == false)
    {
    if(Engine->Server == true)HandleKeys(Engine);
    HandleAnimal(Engine);
    HandlePlayers(Engine);
    HandleMen(Engine);
    HandlePara(Engine);
    HandleSky(Engine);
    HandleSphere(Engine);
    HandleRemoteExplosion(Engine);
    if(AI_Active == true)HandleAI(Engine,11);
    if(CBot      == true)HandleAI(Engine,Net_Id);
    MovePlayers(Engine);
    MovePara(Engine);
    MoveShot(Engine);
    MoveSpec(Engine);
    MoveParticle(Engine);
    MoveSky(Engine);
    MoveSphere(Engine);
    Collision_Wall(Engine);
    Collision_Shot(Engine);
    Collision_Spec(Engine);
    Collision_Explosion(Engine);
    Collision_Tiger(Engine);
    Collision_Sky(Engine);
    Collision_Plane(Engine);
    Collision_Tree(Engine);
    HandleDrugs(Engine);
    }
  if(Engine->Server == true)HandleGameOver(Engine);
  HandleExplosion(Engine);
  HandleParticle(Engine);
  }

DrawMap(Engine);
DrawAnimal(Engine);
DrawTree(Engine);

Engine->OpenGl_Window->SwapBuffers_hdc();
}

//------------------------------------------------------------------
void CGameMain::DrawMap(SEngine *Engine)
//------------------------------------------------------------------
{
glPushMatrix();
glTranslatef(8.0f,-6.00f,-15.0f); 

for(char i=0;i<=14;i++)
  {
  if(Rules.Map == 1)glBindTexture(GL_TEXTURE_2D,Tex_Grass1.texID);
  if(Rules.Map == 2)glBindTexture(GL_TEXTURE_2D,Tex_Grass2.texID);
  if(Rules.Map == 3 && Map3_Active[i] == true) glBindTexture(GL_TEXTURE_2D,Tex_Grass3.texID);
  if(Rules.Map == 3 && Map3_Active[i] == false)glBindTexture(GL_TEXTURE_2D,Tex_Grass3D.texID);
  if(Rules.Map == 4)glBindTexture(GL_TEXTURE_2D,Tex_Grass4.texID);

  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.6f,-0.19f,+0.0f);	
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.6f,-0.19f,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.6f,+0.19f,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.6f,+0.19f,-0.0f);	
  glEnd();

  glTranslatef(-1.20f,0.0f,0.0f); 
  }
glPopMatrix();
}

//------------------------------------------------------------------
void CGameMain::LoadTexture(SEngine *Engine)
//------------------------------------------------------------------
{
Tex_Grass1.imageData   = NULL;
Tex_Grass2.imageData   = NULL;
Tex_Grass3.imageData   = NULL;
Tex_Grass3D.imageData  = NULL;
Tex_Grass4.imageData   = NULL;

Tex_Cow_R.imageData    = NULL;
Tex_Lion_R.imageData   = NULL;
Tex_Sheep_R.imageData  = NULL;
Tex_Cow_L.imageData    = NULL;
Tex_Lion_L.imageData   = NULL;
Tex_Sheep_L.imageData  = NULL;
Tex_Cow_D.imageData    = NULL;
Tex_Lion_D.imageData   = NULL;
Tex_Sheep_D.imageData  = NULL;

Tex_Tree1.imageData    = NULL;
Tex_Tree2.imageData    = NULL;
Tex_Tree3.imageData    = NULL;

Tex_Green_Plane.imageData   = NULL;
Tex_Green_Man.imageData     = NULL;
Tex_Green_Para_D.imageData  = NULL;
Tex_Green_Para.imageData    = NULL;
Tex_Red_Plane.imageData     = NULL;
Tex_Red_Man.imageData       = NULL;
Tex_Red_Para_D.imageData    = NULL;
Tex_Red_Para.imageData      = NULL;

Tex_Menu.imageData          = NULL;
Tex_Menu_Selected.imageData = NULL;
Tex_Menu_Bought.imageData   = NULL;

Tex_Shot.imageData          = NULL;
Tex_Spec.imageData          = NULL;
Tex_Sphere.imageData        = NULL;

Tex_Sky.imageData           = NULL;
Tex_Sky_Dark.imageData      = NULL;

Tex_Pointer.imageData       = NULL;

Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Grass1, "data\\map\\Grass1.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Grass2, "data\\map\\Grass2.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Grass3, "data\\map\\Grass3.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Grass3D,"data\\map\\Grass3D.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Grass4, "data\\map\\Grass4.dat",0);

Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Cow_R,   "data\\Animal\\Cow_R.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Lion_R,  "data\\Animal\\Lion_R.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Sheep_R, "data\\Animal\\Sheep_R.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Cow_L,   "data\\Animal\\Cow_L.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Lion_L,  "data\\Animal\\Lion_L.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Sheep_L, "data\\Animal\\Sheep_L.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Cow_D,   "data\\Animal\\Cow_D.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Lion_D,  "data\\Animal\\Lion_D.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Sheep_D, "data\\Animal\\Sheep_D.dat",0);

Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Tree1, "data\\map\\Tree1.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Tree2, "data\\map\\Tree2.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Tree3, "data\\map\\Tree3.dat",0);

Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Green_Plane,  "data\\Player\\Green_Plane.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Green_Man,    "data\\Player\\Green_man.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Green_Para,   "data\\Player\\Green_para.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Green_Para_D, "data\\Player\\Green_para_D.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Red_Plane,    "data\\Player\\Red_Plane.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Red_Man,      "data\\Player\\Red_man.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Red_Para,     "data\\Player\\Red_para.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Red_Para_D,   "data\\Player\\Red_para_D.dat",0);

Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Menu,	       "data\\Game\\Menu.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Menu_Selected,"data\\Game\\Menu_Selected.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Menu_Bought,  "data\\Game\\Menu_Bought.dat",0);

Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Shot,	       "data\\Game\\Shot.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Spec,	       "data\\Game\\Spec.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Sphere,       "data\\Game\\Sphere.dat",0);

Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Sky,	       "data\\Game\\Sky.dat",0);
Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Sky_Dark,     "data\\Game\\Sky_Dark.dat",0);

Engine->OpenGl_Texture_TGA->LoadTGA(&Tex_Pointer,      "data\\Game\\Pointer.dat",0);
}

//------------------------------------------------------------------
void CGameMain::UnLoadTexture(SEngine *Engine)
//------------------------------------------------------------------
{
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Grass1);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Grass2);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Grass3);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Grass3D);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Grass4);

Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Cow_R);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Lion_R);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Sheep_R);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Cow_L);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Lion_L);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Sheep_L);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Cow_D);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Lion_D);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Sheep_D);

Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Tree1);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Tree2);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Tree3);

Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Green_Plane);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Green_Man);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Green_Para);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Green_Para_D);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Red_Plane);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Red_Man);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Red_Para);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Red_Para_D);

Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Menu);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Menu_Selected);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Menu_Bought);

Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Shot);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Spec);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Sphere);

Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Sky);
Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Sky_Dark);

Engine->OpenGl_Texture_TGA->FreeTGA(&Tex_Pointer);
}

//------------------------------------------------------------------
void CGameMain::ResetRound(SEngine *Engine)
//------------------------------------------------------------------
{
int i;

for(i = 0;i<= 199;i++){Particle[i].Life = 0.0f;}

for(i = 0;i<= 11;i++)
  {
  Explo[i].Active	 = false;
  Shot[i].Active	 = false;
  Shot[i].Type		 = 0;
  Spec[i].Active	 = false;
  Spec[i].Type		 = 0;

  Equip[i].Option_Ok	   = false;
  Equip[i].Option_Selected = '3';

  Player[i].Money	 += 300;
  if(Player[i].Dead == false)Player[i].Money	 += 100;
  if(Player[i].Money > PLAYER_MAXMONEY)Player[i].Money = PLAYER_MAXMONEY;

  Player[i].SpecInvert   = false;
  Player[i].SpecBlind    = 0.0f;
  Player[i].SpecSpeedHit = 1.0f;
  Player[i].Dead	 = true;
  if(Player[i].Active == true){Player[i].Dead = false;}
  Player[i].Damage	 = 0;
  Player[i].Key_Down     = false;
  Player[i].Key_Up       = false;
  Player[i].Key_Left     = false;
  Player[i].Key_Right    = false;
  Player[i].Key_Fire     = false;
  Player[i].Key_Spec     = false;
  Player[i].Key_Para     = false;
  Player[i].Pilot	 = true;
  Player[i].Cloak	 = 1.0f;
  Player[i].CloakUp	 = false;

  Player_Para_And_Man[i].IsMan    = false;
  Player_Para_And_Man[i].IsPara   = false;
  Player_Para_And_Man[i].IsSphere = false;
  Player_Para_And_Man[i].ParaDead = false;
  Player_Para_And_Man[i].Rotate   = 0.0f;

  Sphere[i].Active = false;

  if((Equip[i].Option_Plane & 0x04) == 0x04)Player[i].Damage = -1;

  if(i ==  0)Player[0].y  =  5.0f;
  if(i ==  1)Player[1].y  =  5.0f;
  if(i ==  2)Player[2].y  =  3.0f;
  if(i ==  3)Player[3].y  =  3.0f;
  if(i ==  4)Player[4].y  =  1.0f;
  if(i ==  5)Player[5].y  =  1.0f;
  if(i ==  6)Player[6].y  = -1.0f;
  if(i ==  7)Player[7].y  = -1.0f;
  if(i ==  8)Player[8].y  = -3.0f;
  if(i ==  9)Player[9].y  = -3.0f;
  if(i == 10)Player[10].y = -5.0f;
  if(i == 11)Player[11].y = -5.0f;

  if(i ==  0){Player[0].x  =  6.0f;Player[i].Rotate = 90.0f;}
  if(i ==  1){Player[1].x  = -6.0f;Player[i].Rotate = 270.0f;}
  if(i ==  2){Player[2].x  =  6.0f;Player[i].Rotate = 90.0f;}
  if(i ==  3){Player[3].x  = -6.0f;Player[i].Rotate = 270.0f;}
  if(i ==  4){Player[4].x  =  6.0f;Player[i].Rotate = 90.0f;}
  if(i ==  5){Player[5].x  = -6.0f;Player[i].Rotate = 270.0f;}
  if(i ==  6){Player[6].x  =  6.0f;Player[i].Rotate = 90.0f;}
  if(i ==  7){Player[7].x  = -6.0f;Player[i].Rotate = 270.0f;}
  if(i ==  8){Player[8].x  =  6.0f;Player[i].Rotate = 90.0f;}
  if(i ==  9){Player[9].x  = -6.0f;Player[i].Rotate = 270.0f;}
  if(i == 10){Player[10].x =  6.0f;Player[i].Rotate = 90.0f;}
  if(i == 11){Player[11].x = -6.0f;Player[i].Rotate = 270.0f;}

  Player[i].Speed	 = 1.0f;
  }

for(i = 0;i<=14;i++)Map3_Active[i] = true;
Rules.Map		= (rand()%4)+1;
Rules.GameState_Prepare = false;
Rules.GameState_Playing = false;
Rules.GameState_Buying  = true;
Rules.Buy_Counter	= Engine->Setting->Option_BuyTime;
Rules.Buy_Time		= 1.0f;
Rules.Game_Counter	= 2;
Rules.Game_Time		= 1.0f;

Animal.Pointing_Left    = false;
Animal.Dead		= false;
Animal.x		= ((rand()%1400)-700) * 0.01f;
Animal.Tx		= Animal.x;
Animal.Sleep_Pause	= ((float)(rand()%15));

Tree[0].x		= (-100+(+(rand()%900))) * 0.01f;
Tree[1].x		= (+100+(-(rand()%900))) * 0.01f;
Tree[0].Type		= (rand()%4)+1;
Tree[1].Type		= (rand()%4)+1;
Tree[0].Burning		= false;
Tree[1].Burning		= false;

Sky[0].Active		= false;
Sky[1].Active		= false;

Drugs_Effect	= 0.0f;
Drugs_On	= false;
Color		= 1.0f;

NewRound_Count  = 2;
NewRound_Second = 1.0f;

GameOver		= false;

Engine->Game->GameNetWork->Server_SendNewRound(Engine);
}

//------------------------------------------------------------------
void CGameMain::HandleAnimal(SEngine *Engine)
//------------------------------------------------------------------
{
if(Animal.Dead == false && Rules.Map != 3)
  {
  if(Rules.Map == 2) // Hunt Players
    {
    for(char i=0;i<=11;i++)
      {
      if(Player_Para_And_Man[i].IsMan == true)
        {
	Animal.Tx = Player_Para_And_Man[i].x;
	}
      }
    }

  Animal.Sleep_Pause -= 0.001f * (float)Engine->Timer->GetDeltaMs();

  if(Animal.Sleep_Pause <= 0.0f && Engine->Server == true)
    {
    Animal.Tx		= ((rand()%1400)-700) * 0.01f;
    Animal.Sleep_Pause	= ((float)(rand()%15));
    Engine->Game->GameNetWork->Server_SendAnimalDestinate(Engine);
    }

  if(Animal.x < Animal.Tx-0.1f)
    {
    Animal.Pointing_Left = false;
    if(Rules.Map == 1)Animal.x += 0.001f * (float)Engine->Timer->GetDeltaMs() * ANIMAL_COW_SPEED;
    if(Rules.Map == 2)Animal.x += 0.001f * (float)Engine->Timer->GetDeltaMs() * ANIMAL_LION_SPEED;
    if(Rules.Map == 4)Animal.x += 0.001f * (float)Engine->Timer->GetDeltaMs() * ANIMAL_SHEEP_SPEED;
    }

  if(Animal.x > Animal.Tx+0.1f)
    {
    Animal.Pointing_Left = true;
    if(Rules.Map == 1)Animal.x -= 0.001f * (float)Engine->Timer->GetDeltaMs() * ANIMAL_COW_SPEED;
    if(Rules.Map == 2)Animal.x -= 0.001f * (float)Engine->Timer->GetDeltaMs() * ANIMAL_LION_SPEED;
    if(Rules.Map == 4)Animal.x -= 0.001f * (float)Engine->Timer->GetDeltaMs() * ANIMAL_SHEEP_SPEED;
    }
  }
}

//------------------------------------------------------------------
void CGameMain::DrawAnimal(SEngine *Engine)
//------------------------------------------------------------------
{
if(Rules.Map == 3)return;
glPushMatrix();							
glTranslatef(Animal.x,-5.89f,-15.0f); 

if(Rules.Map == 1)
  {
  if(Animal.Pointing_Left == true  && Animal.Dead == false){glBindTexture(GL_TEXTURE_2D,Tex_Cow_L.texID);}
  if(Animal.Pointing_Left == false && Animal.Dead == false){glBindTexture(GL_TEXTURE_2D,Tex_Cow_R.texID);}
  if(Animal.Dead == true){glBindTexture(GL_TEXTURE_2D,Tex_Cow_D.texID);}
  }
if(Rules.Map == 2)
  {
  if(Animal.Pointing_Left == true  && Animal.Dead == false){glBindTexture(GL_TEXTURE_2D,Tex_Lion_L.texID);}
  if(Animal.Pointing_Left == false && Animal.Dead == false){glBindTexture(GL_TEXTURE_2D,Tex_Lion_R.texID);}
  if(Animal.Dead == true){glBindTexture(GL_TEXTURE_2D,Tex_Lion_D.texID);}
  }
if(Rules.Map == 4)
  {
  if(Animal.Pointing_Left == true  && Animal.Dead == false){glBindTexture(GL_TEXTURE_2D,Tex_Sheep_L.texID);}
  if(Animal.Pointing_Left == false && Animal.Dead == false){glBindTexture(GL_TEXTURE_2D,Tex_Sheep_R.texID);}
  if(Animal.Dead == true){glBindTexture(GL_TEXTURE_2D,Tex_Sheep_D.texID);}
  }
glBegin(GL_QUADS);						
glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.13f,-0.13f,+0.0f);	
glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.13f,-0.13f,+0.0f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.13f,+0.13f,-0.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.13f,+0.13f,-0.0f);	
glEnd();
glPopMatrix();
}

//------------------------------------------------------------------
void CGameMain::DrawBuyMenu(SEngine *Engine)
//------------------------------------------------------------------
{
glPushMatrix();							
glTranslatef(0.0f,0.0f,-1.0f); 

glBindTexture(GL_TEXTURE_2D,Tex_Menu.texID);

glBegin(GL_QUADS);						
glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.50f,-0.50f,+0.0f);	
glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.50f,-0.50f,+0.0f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.50f,+0.50f,-0.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.50f,+0.50f,-0.0f);	
glEnd();

char Temp_Text[12];
itoa(Rules.Buy_Counter,Temp_Text,10);
Engine->OpenGl_Font->glPrint(260,395,Temp_Text,0);
itoa(Player[Net_Id].Money,Temp_Text,10);
Engine->OpenGl_Font->glPrint(316,395,Temp_Text,0);
glPopMatrix();

//--------------//
//   Selected   //
//--------------//
glPushMatrix();
glTranslatef(0.0f,0.0f,-1.0f); 

if(Equip[Net_Id].Option_Selected == '3')
  {
  glTranslatef(-0.029f,0.211f,0.0f); 
  }
//----------- Left ------------------//
if(Equip[Net_Id].Option_Selected == 'W')
  {
  glTranslatef(-0.173f,0.039f,0.0f); 
  }
if(Equip[Net_Id].Option_Selected == 'Q')
  {
  glTranslatef(-0.357f,0.039f,0.0f); 
  }
if(Equip[Net_Id].Option_Selected == 'A')
  {
  glTranslatef(-0.357f,-0.065f,0.0f); 
  }
if(Equip[Net_Id].Option_Selected == 'S')
  {
  glTranslatef(-0.173f,-0.065f,0.0f); 
  }
if(Equip[Net_Id].Option_Selected == 'Z')
  {
  glTranslatef(-0.357f,-0.161f,0.0f); 
  }
if(Equip[Net_Id].Option_Selected == 'X')
  {
  glTranslatef(-0.173f,-0.161f,0.0f); 
  }
if(Equip[Net_Id].Option_Selected == 'T')
  {
  glTranslatef(-0.357f,-0.257f,0.0f); 
  }
if(Equip[Net_Id].Option_Selected == 'Y')
  {
  glTranslatef(-0.173f,-0.257f,0.0f); 
  }
//----------- Right ------------------//
if(Equip[Net_Id].Option_Selected == 'E')
  {
  glTranslatef( 0.137f,0.039f,0.0f); 
  }
if(Equip[Net_Id].Option_Selected == 'R')
  {
  glTranslatef( 0.336f,0.039f,0.0f); 
  }
if(Equip[Net_Id].Option_Selected == 'D')
  {
  glTranslatef( 0.137f,-0.065f,0.0f); 
  }
if(Equip[Net_Id].Option_Selected == 'F')
  {
  glTranslatef( 0.336f,-0.065f,0.0f); 
  }
if(Equip[Net_Id].Option_Selected == 'C')
  {
  glTranslatef( 0.137f,-0.161f,0.0f); 
  }
if(Equip[Net_Id].Option_Selected == 'V')
  {
  glTranslatef( 0.336f,-0.161f,0.0f); 
  }
if(Equip[Net_Id].Option_Selected == 'U')
  {
  glTranslatef( 0.137f,-0.257f,0.0f); 
  }
if(Equip[Net_Id].Option_Selected == 'I')
  {
  glTranslatef( 0.336f,-0.257f,0.0f); 
  }


if(Equip[Net_Id].Option_Ok == false)
  {
  glBindTexture(GL_TEXTURE_2D,Tex_Menu_Selected.texID);

  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.13f,-0.06f,+0.0f);	
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.13f,-0.06f,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.13f,+0.06f,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.13f,+0.06f,-0.0f);	
  glEnd();
  }
glPopMatrix();
//--------------//
//    Bought    //
//--------------//

//-------------- Spec ----------------//
if(Equip[Net_Id].Option_Spec != 0)
  {
  if((Equip[Net_Id].Option_Spec & 0x01) == 0x01)
    {
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-1.0f); 
    glTranslatef( 0.336f,0.039f,0.0f); 
    glBindTexture(GL_TEXTURE_2D,Tex_Menu_Bought.texID);
    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.13f,-0.06f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.13f,-0.06f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.13f,+0.06f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.13f,+0.06f,-0.0f);	
    glEnd();
    glPopMatrix();
    }
  if((Equip[Net_Id].Option_Spec & 0x02) == 0x02)
    {
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-1.0f); 
    glTranslatef( 0.336f,-0.065f,0.0f); 
    glBindTexture(GL_TEXTURE_2D,Tex_Menu_Bought.texID);
    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.13f,-0.06f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.13f,-0.06f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.13f,+0.06f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.13f,+0.06f,-0.0f);	
    glEnd();
    glPopMatrix();
    }
  if((Equip[Net_Id].Option_Spec & 0x04) == 0x04)
    {
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-1.0f); 
    glTranslatef( 0.336f,-0.161f,0.0f); 
    glBindTexture(GL_TEXTURE_2D,Tex_Menu_Bought.texID);
    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.13f,-0.06f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.13f,-0.06f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.13f,+0.06f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.13f,+0.06f,-0.0f);	
    glEnd();
    glPopMatrix();
    }
  if((Equip[Net_Id].Option_Spec & 0x08) == 0x08)
    {
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-1.0f); 
    glTranslatef( 0.336f,-0.257f,0.0f); 
    glBindTexture(GL_TEXTURE_2D,Tex_Menu_Bought.texID);
    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.13f,-0.06f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.13f,-0.06f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.13f,+0.06f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.13f,+0.06f,-0.0f);	
    glEnd();
    glPopMatrix();
    }
  }

//-------------- Shot ----------------//
if(Equip[Net_Id].Option_Shot != 0)
  {
  if((Equip[Net_Id].Option_Shot & 0x01) == 0x01)
    {
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-1.0f); 
    glTranslatef( 0.137f,0.039f,0.0f); 
    glBindTexture(GL_TEXTURE_2D,Tex_Menu_Bought.texID);
    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.13f,-0.06f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.13f,-0.06f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.13f,+0.06f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.13f,+0.06f,-0.0f);	
    glEnd();
    glPopMatrix();
    }
  if((Equip[Net_Id].Option_Shot & 0x02) == 0x02)
    {
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-1.0f); 
    glTranslatef( 0.137f,-0.065f,0.0f); 
    glBindTexture(GL_TEXTURE_2D,Tex_Menu_Bought.texID);
    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.13f,-0.06f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.13f,-0.06f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.13f,+0.06f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.13f,+0.06f,-0.0f);	
    glEnd();
    glPopMatrix();
    }
  if((Equip[Net_Id].Option_Shot & 0x04) == 0x04)
    {
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-1.0f); 
    glTranslatef( 0.137f,-0.161f,0.0f); 
    glBindTexture(GL_TEXTURE_2D,Tex_Menu_Bought.texID);
    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.13f,-0.06f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.13f,-0.06f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.13f,+0.06f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.13f,+0.06f,-0.0f);	
    glEnd();
    glPopMatrix();
    }
  if((Equip[Net_Id].Option_Shot & 0x08) == 0x08)
    {
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-1.0f); 
    glTranslatef( 0.137f,-0.257f,0.0f); 
    glBindTexture(GL_TEXTURE_2D,Tex_Menu_Bought.texID);
    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.13f,-0.06f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.13f,-0.06f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.13f,+0.06f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.13f,+0.06f,-0.0f);	
    glEnd();
    glPopMatrix();
    }
  }

//-------------- Para ----------------//
if(Equip[Net_Id].Option_Para != 0)
  {
  if((Equip[Net_Id].Option_Para & 0x01) == 0x01)
    {
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-1.0f); 
    glTranslatef(-0.173f,0.039f,0.0f); 
    glBindTexture(GL_TEXTURE_2D,Tex_Menu_Bought.texID);
    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.13f,-0.06f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.13f,-0.06f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.13f,+0.06f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.13f,+0.06f,-0.0f);	
    glEnd();
    glPopMatrix();
    }
  if((Equip[Net_Id].Option_Para & 0x02) == 0x02)
    {
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-1.0f); 
    glTranslatef(-0.173f,-0.065f,0.0f); 
    glBindTexture(GL_TEXTURE_2D,Tex_Menu_Bought.texID);
    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.13f,-0.06f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.13f,-0.06f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.13f,+0.06f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.13f,+0.06f,-0.0f);	
    glEnd();
    glPopMatrix();
    }
  if((Equip[Net_Id].Option_Para & 0x04) == 0x04)
    {
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-1.0f); 
    glTranslatef(-0.173f,-0.161f,0.0f); 
    glBindTexture(GL_TEXTURE_2D,Tex_Menu_Bought.texID);
    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.13f,-0.06f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.13f,-0.06f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.13f,+0.06f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.13f,+0.06f,-0.0f);	
    glEnd();
    glPopMatrix();
    }
  if((Equip[Net_Id].Option_Para & 0x08) == 0x08)
    {
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-1.0f); 
    glTranslatef(-0.173f,-0.257f,0.0f); 
    glBindTexture(GL_TEXTURE_2D,Tex_Menu_Bought.texID);
    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.13f,-0.06f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.13f,-0.06f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.13f,+0.06f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.13f,+0.06f,-0.0f);	
    glEnd();
    glPopMatrix();
    }
  }

//-------------- Plane ----------------//
if(Equip[Net_Id].Option_Plane != 0)
  {
  if((Equip[Net_Id].Option_Plane & 0x01) == 0x01)
    {
    glPushMatrix();
    glTranslatef(-0.357f,0.039f,-1.0f); 
    glBindTexture(GL_TEXTURE_2D,Tex_Menu_Bought.texID);
    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.13f,-0.06f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.13f,-0.06f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.13f,+0.06f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.13f,+0.06f,-0.0f);	
    glEnd();
    glPopMatrix();
    }
  if((Equip[Net_Id].Option_Plane & 0x02) == 0x02)
    {
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-1.0f); 
    glTranslatef(-0.357f,-0.065f,0.0f); 
    glBindTexture(GL_TEXTURE_2D,Tex_Menu_Bought.texID);
    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.13f,-0.06f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.13f,-0.06f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.13f,+0.06f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.13f,+0.06f,-0.0f);	
    glEnd();
    glPopMatrix();
    }
  if((Equip[Net_Id].Option_Plane & 0x04) == 0x04)
    {
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-1.0f); 
    glTranslatef(-0.357f,-0.161f,0.0f); 
    glBindTexture(GL_TEXTURE_2D,Tex_Menu_Bought.texID);
    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.13f,-0.06f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.13f,-0.06f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.13f,+0.06f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.13f,+0.06f,-0.0f);	
    glEnd();
    glPopMatrix();
    }
  if((Equip[Net_Id].Option_Plane & 0x08) == 0x08)
    {
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-1.0f); 
    glTranslatef(-0.357f,-0.257f,0.0f); 
    glBindTexture(GL_TEXTURE_2D,Tex_Menu_Bought.texID);
    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.13f,-0.06f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.13f,-0.06f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.13f,+0.06f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.13f,+0.06f,-0.0f);	
    glEnd();
    glPopMatrix();
    }
  }
}

//------------------------------------------------------------------
void CGameMain::HandleBuyMenu(SEngine *Engine)
//------------------------------------------------------------------
{
Rules.Buy_Time -= 0.001f * (float)Engine->Timer->GetDeltaMs();
if(Rules.Buy_Time <= 0.0f)
  {
  Rules.Buy_Counter--;
  Rules.Buy_Time = 1.0f;
  }
if(Rules.Buy_Counter < 0)
  {
  Rules.GameState_Buying  = false;
  Rules.GameState_Prepare = true;
  if(Engine->Server == true)Engine->Game->GameNetWork->Server_SendEquip(Engine);
  }

char Ready=0;
for(char i = 0;i<=11;i++){if(Player[i].Active == true && Equip[i].Option_Ok == false && (i != 11 || AI_Active == false))Ready++;}
if(Ready==0){Engine->Game->GameNetWork->Server_SendBuyMenuOK(Engine);Rules.Buy_Counter = -1;}

//-------------------------------- Push ------------------------------//
if(Player[Net_Id].Active == true && Equip[Net_Id].Option_Ok == false && (Player[Net_Id].Key_Fire == true || Player[Net_Id].Key_Spec))
  {
  if(Equip[Net_Id].Option_Selected == '3'){Equip[Net_Id].Option_Ok = true;if(Engine->Server == false){Engine->Game->GameNetWork->Client_SendEquip(Engine,Equip[Net_Id].Option_Selected);}}

  if(Equip[Net_Id].Option_Selected == 'Q' && Player[Net_Id].Money >=  500 && (Equip[Net_Id].Option_Plane & 0x01) != 0x01){Equip[Net_Id].Option_Plane |= 0x01;Player[Net_Id].Money -=  500;if(Engine->Server == false){Engine->Game->GameNetWork->Client_SendEquip(Engine,Equip[Net_Id].Option_Selected);}return;}
  if(Equip[Net_Id].Option_Selected == 'A' && Player[Net_Id].Money >=  800 && (Equip[Net_Id].Option_Plane & 0x02) != 0x02){Equip[Net_Id].Option_Plane |= 0x02;Player[Net_Id].Money -=  800;if(Engine->Server == false){Engine->Game->GameNetWork->Client_SendEquip(Engine,Equip[Net_Id].Option_Selected);}return;}
  if(Equip[Net_Id].Option_Selected == 'Z' && Player[Net_Id].Money >= 1000 && (Equip[Net_Id].Option_Plane & 0x04) != 0x04){Equip[Net_Id].Option_Plane |= 0x04;Player[Net_Id].Money -= 1000;Player[Net_Id].Damage = -1;if(Engine->Server == false){Engine->Game->GameNetWork->Client_SendEquip(Engine,Equip[Net_Id].Option_Selected);}return;}
  if(Equip[Net_Id].Option_Selected == 'T' && Player[Net_Id].Money >= 1400 && (Equip[Net_Id].Option_Plane & 0x08) != 0x08){Equip[Net_Id].Option_Plane |= 0x08;Player[Net_Id].Money -= 1400;if(Engine->Server == false){Engine->Game->GameNetWork->Client_SendEquip(Engine,Equip[Net_Id].Option_Selected);}return;}

  if(Equip[Net_Id].Option_Selected == 'W' && Player[Net_Id].Money >=  400 && (Equip[Net_Id].Option_Para & 0x01) != 0x01){Equip[Net_Id].Option_Para |= 0x01;Player[Net_Id].Money -=  400;if(Engine->Server == false){Engine->Game->GameNetWork->Client_SendEquip(Engine,Equip[Net_Id].Option_Selected);}return;}
  if(Equip[Net_Id].Option_Selected == 'S' && Player[Net_Id].Money >=  700 && (Equip[Net_Id].Option_Para & 0x02) != 0x02){Equip[Net_Id].Option_Para |= 0x02;Player[Net_Id].Money -=  700;if(Engine->Server == false){Engine->Game->GameNetWork->Client_SendEquip(Engine,Equip[Net_Id].Option_Selected);}return;}
  if(Equip[Net_Id].Option_Selected == 'X' && Player[Net_Id].Money >= 1000 && (Equip[Net_Id].Option_Para & 0x04) != 0x04){Equip[Net_Id].Option_Para |= 0x04;Player[Net_Id].Money -= 1000;if(Engine->Server == false){Engine->Game->GameNetWork->Client_SendEquip(Engine,Equip[Net_Id].Option_Selected);}return;}
  if(Equip[Net_Id].Option_Selected == 'Y' && Player[Net_Id].Money >= 1500 && (Equip[Net_Id].Option_Para & 0x08) != 0x08){Equip[Net_Id].Option_Para |= 0x08;Player[Net_Id].Money -= 1500;if(Engine->Server == false){Engine->Game->GameNetWork->Client_SendEquip(Engine,Equip[Net_Id].Option_Selected);}return;}

  if(Equip[Net_Id].Option_Selected == 'E' && Player[Net_Id].Money >=  300 && (Equip[Net_Id].Option_Shot & 0x01) != 0x01){Equip[Net_Id].Option_Shot |= 0x01;Player[Net_Id].Money -=  300;if(Engine->Server == false){Engine->Game->GameNetWork->Client_SendEquip(Engine,Equip[Net_Id].Option_Selected);}return;}
  if(Equip[Net_Id].Option_Selected == 'D' && Player[Net_Id].Money >=  500 && (Equip[Net_Id].Option_Shot & 0x02) != 0x02){Equip[Net_Id].Option_Shot |= 0x02;Player[Net_Id].Money -=  500;if(Engine->Server == false){Engine->Game->GameNetWork->Client_SendEquip(Engine,Equip[Net_Id].Option_Selected);}return;}
  if(Equip[Net_Id].Option_Selected == 'C' && Player[Net_Id].Money >= 1000 && (Equip[Net_Id].Option_Shot & 0x04) != 0x04){Equip[Net_Id].Option_Shot |= 0x04;Player[Net_Id].Money -= 1000;if(Engine->Server == false){Engine->Game->GameNetWork->Client_SendEquip(Engine,Equip[Net_Id].Option_Selected);}return;}
  if(Equip[Net_Id].Option_Selected == 'U' && Player[Net_Id].Money >= 2000 && (Equip[Net_Id].Option_Shot & 0x08) != 0x08){Equip[Net_Id].Option_Shot |= 0x08;Player[Net_Id].Money -= 2000;if(Engine->Server == false){Engine->Game->GameNetWork->Client_SendEquip(Engine,Equip[Net_Id].Option_Selected);}return;}

  if(Equip[Net_Id].Option_Selected == 'R' && Player[Net_Id].Money >=  400 && (Equip[Net_Id].Option_Spec & 0x01) != 0x01){Equip[Net_Id].Option_Spec |= 0x01;Player[Net_Id].Money -=  400;if(Engine->Server == false){Engine->Game->GameNetWork->Client_SendEquip(Engine,Equip[Net_Id].Option_Selected);}return;}
  if(Equip[Net_Id].Option_Selected == 'F' && Player[Net_Id].Money >=  600 && (Equip[Net_Id].Option_Spec & 0x02) != 0x02){Equip[Net_Id].Option_Spec |= 0x02;Player[Net_Id].Money -=  600;if(Engine->Server == false){Engine->Game->GameNetWork->Client_SendEquip(Engine,Equip[Net_Id].Option_Selected);}return;}
  if(Equip[Net_Id].Option_Selected == 'V' && Player[Net_Id].Money >=  900 && (Equip[Net_Id].Option_Spec & 0x04) != 0x04){Equip[Net_Id].Option_Spec |= 0x04;Player[Net_Id].Money -=  900;if(Engine->Server == false){Engine->Game->GameNetWork->Client_SendEquip(Engine,Equip[Net_Id].Option_Selected);}return;}
  if(Equip[Net_Id].Option_Selected == 'I' && Player[Net_Id].Money >= 1600 && (Equip[Net_Id].Option_Spec & 0x08) != 0x08){Equip[Net_Id].Option_Spec |= 0x08;Player[Net_Id].Money -= 1600;if(Engine->Server == false){Engine->Game->GameNetWork->Client_SendEquip(Engine,Equip[Net_Id].Option_Selected);}return;}
  }
//-------------------------------- Down ------------------------------//
if(Player[Net_Id].Key_Down == false)  Equip[Net_Id].Option_Key_Moved_Down  = false;
if(Player[Net_Id].Key_Down == true && Equip[Net_Id].Option_Key_Moved_Down == false)
  {
  Equip[Net_Id].Option_Key_Moved_Down = true;
  if(Equip[Net_Id].Option_Selected == '3'){Equip[Net_Id].Option_Selected = 'W';return;}

  if(Equip[Net_Id].Option_Selected == 'Q'){Equip[Net_Id].Option_Selected = 'A';return;}
  if(Equip[Net_Id].Option_Selected == 'A'){Equip[Net_Id].Option_Selected = 'Z';return;}
  if(Equip[Net_Id].Option_Selected == 'Z'){Equip[Net_Id].Option_Selected = 'T';return;}

  if(Equip[Net_Id].Option_Selected == 'W'){Equip[Net_Id].Option_Selected = 'S';return;}
  if(Equip[Net_Id].Option_Selected == 'S'){Equip[Net_Id].Option_Selected = 'X';return;}
  if(Equip[Net_Id].Option_Selected == 'X'){Equip[Net_Id].Option_Selected = 'Y';return;}

  if(Equip[Net_Id].Option_Selected == 'E'){Equip[Net_Id].Option_Selected = 'D';return;}
  if(Equip[Net_Id].Option_Selected == 'D'){Equip[Net_Id].Option_Selected = 'C';return;}
  if(Equip[Net_Id].Option_Selected == 'C'){Equip[Net_Id].Option_Selected = 'U';return;}

  if(Equip[Net_Id].Option_Selected == 'R'){Equip[Net_Id].Option_Selected = 'F';return;}
  if(Equip[Net_Id].Option_Selected == 'F'){Equip[Net_Id].Option_Selected = 'V';return;}
  if(Equip[Net_Id].Option_Selected == 'V'){Equip[Net_Id].Option_Selected = 'I';return;}
  }
//-------------------------------- Up ------------------------------//
if(Player[Net_Id].Key_Up == false)  Equip[Net_Id].Option_Key_Moved_Up  = false;
if(Player[Net_Id].Key_Up == true && Equip[Net_Id].Option_Key_Moved_Up == false)
  {
  Equip[Net_Id].Option_Key_Moved_Up = true;

  if(Equip[Net_Id].Option_Selected == 'T'){Equip[Net_Id].Option_Selected = 'Z';return;}
  if(Equip[Net_Id].Option_Selected == 'Z'){Equip[Net_Id].Option_Selected = 'A';return;}
  if(Equip[Net_Id].Option_Selected == 'A'){Equip[Net_Id].Option_Selected = 'Q';return;}

  if(Equip[Net_Id].Option_Selected == 'Y'){Equip[Net_Id].Option_Selected = 'X';return;}
  if(Equip[Net_Id].Option_Selected == 'X'){Equip[Net_Id].Option_Selected = 'S';return;}
  if(Equip[Net_Id].Option_Selected == 'S'){Equip[Net_Id].Option_Selected = 'W';return;}

  if(Equip[Net_Id].Option_Selected == 'U'){Equip[Net_Id].Option_Selected = 'C';return;}
  if(Equip[Net_Id].Option_Selected == 'C'){Equip[Net_Id].Option_Selected = 'D';return;}
  if(Equip[Net_Id].Option_Selected == 'D'){Equip[Net_Id].Option_Selected = 'E';return;}

  if(Equip[Net_Id].Option_Selected == 'I'){Equip[Net_Id].Option_Selected = 'V';return;}
  if(Equip[Net_Id].Option_Selected == 'V'){Equip[Net_Id].Option_Selected = 'F';return;}
  if(Equip[Net_Id].Option_Selected == 'F'){Equip[Net_Id].Option_Selected = 'R';return;}

  if(Equip[Net_Id].Option_Selected == 'Q'){Equip[Net_Id].Option_Selected = '3';return;}
  if(Equip[Net_Id].Option_Selected == 'W'){Equip[Net_Id].Option_Selected = '3';return;}
  if(Equip[Net_Id].Option_Selected == 'E'){Equip[Net_Id].Option_Selected = '3';return;}
  if(Equip[Net_Id].Option_Selected == 'R'){Equip[Net_Id].Option_Selected = '3';return;}
  }
//-------------------------------- Left ------------------------------//
if(Player[Net_Id].Key_Left == false)  Equip[Net_Id].Option_Key_Moved_Left  = false;
if(Player[Net_Id].Key_Left == true && Equip[Net_Id].Option_Key_Moved_Left == false)
  {
  Equip[Net_Id].Option_Key_Moved_Left = true;

  if(Equip[Net_Id].Option_Selected == 'R'){Equip[Net_Id].Option_Selected = 'E';return;}
  if(Equip[Net_Id].Option_Selected == 'E'){Equip[Net_Id].Option_Selected = 'W';return;}
  if(Equip[Net_Id].Option_Selected == 'W'){Equip[Net_Id].Option_Selected = 'Q';return;}

  if(Equip[Net_Id].Option_Selected == 'F'){Equip[Net_Id].Option_Selected = 'D';return;}
  if(Equip[Net_Id].Option_Selected == 'D'){Equip[Net_Id].Option_Selected = 'S';return;}
  if(Equip[Net_Id].Option_Selected == 'S'){Equip[Net_Id].Option_Selected = 'A';return;}

  if(Equip[Net_Id].Option_Selected == 'V'){Equip[Net_Id].Option_Selected = 'C';return;}
  if(Equip[Net_Id].Option_Selected == 'C'){Equip[Net_Id].Option_Selected = 'X';return;}
  if(Equip[Net_Id].Option_Selected == 'X'){Equip[Net_Id].Option_Selected = 'Z';return;}

  if(Equip[Net_Id].Option_Selected == 'I'){Equip[Net_Id].Option_Selected = 'U';return;}
  if(Equip[Net_Id].Option_Selected == 'U'){Equip[Net_Id].Option_Selected = 'Y';return;}
  if(Equip[Net_Id].Option_Selected == 'Y'){Equip[Net_Id].Option_Selected = 'T';return;}
  }
//-------------------------------- Right ------------------------------//
if(Player[Net_Id].Key_Right == false)  Equip[Net_Id].Option_Key_Moved_Right  = false;
if(Player[Net_Id].Key_Right == true && Equip[Net_Id].Option_Key_Moved_Right == false)
  {
  Equip[Net_Id].Option_Key_Moved_Right = true;
  if(Equip[Net_Id].Option_Selected == 'Q'){Equip[Net_Id].Option_Selected = 'W';return;}
  if(Equip[Net_Id].Option_Selected == 'W'){Equip[Net_Id].Option_Selected = 'E';return;}
  if(Equip[Net_Id].Option_Selected == 'E'){Equip[Net_Id].Option_Selected = 'R';return;}

  if(Equip[Net_Id].Option_Selected == 'A'){Equip[Net_Id].Option_Selected = 'S';return;}
  if(Equip[Net_Id].Option_Selected == 'S'){Equip[Net_Id].Option_Selected = 'D';return;}
  if(Equip[Net_Id].Option_Selected == 'D'){Equip[Net_Id].Option_Selected = 'F';return;}

  if(Equip[Net_Id].Option_Selected == 'Z'){Equip[Net_Id].Option_Selected = 'X';return;}
  if(Equip[Net_Id].Option_Selected == 'X'){Equip[Net_Id].Option_Selected = 'C';return;}
  if(Equip[Net_Id].Option_Selected == 'C'){Equip[Net_Id].Option_Selected = 'V';return;}

  if(Equip[Net_Id].Option_Selected == 'T'){Equip[Net_Id].Option_Selected = 'Y';return;}
  if(Equip[Net_Id].Option_Selected == 'Y'){Equip[Net_Id].Option_Selected = 'U';return;}
  if(Equip[Net_Id].Option_Selected == 'U'){Equip[Net_Id].Option_Selected = 'I';return;}
  }
}

//------------------------------------------------------------------
void CGameMain::HandleCountDown(SEngine *Engine)
//------------------------------------------------------------------
{
char Active_Players = 0;
for(char i = 0;i<=11;i++){if(Player[i].Active == true)Active_Players++;}
if(Active_Players < 2)Rules.Game_Time = 1.0f;

Rules.Game_Time -= 0.001f * (float)Engine->Timer->GetDeltaMs();
if(Rules.Game_Time <= 0.0f)
  {
  Rules.Game_Counter--;
  Rules.Game_Time = 1.0f;
  }
if(Rules.Game_Counter <= 0)
  {
  Rules.GameState_Prepare = false;
  Rules.GameState_Playing = true;
  }
}
//------------------------------------------------------------------
void CGameMain::DrawPlayerName(SEngine *Engine)
//------------------------------------------------------------------
{
char Temp_Text[12];

//////---------- Green Score ----------/////
glColor3f(0.0f,1.0,0.0);
Engine->OpenGl_Font->glPrint(320,450,"GreenTeam:",0);
itoa(GreenTeam_Score,Temp_Text,10);
Engine->OpenGl_Font->glPrint(420,449,Temp_Text,0);
//////----------  Red Score  ----------/////
glColor3f(1.0f,0.0,0.0);
Engine->OpenGl_Font->glPrint(170,450,"RedTeam:",0);
itoa(RedTeam_Score,Temp_Text,10);
Engine->OpenGl_Font->glPrint(250,449,Temp_Text,0);
//////----------   Green  ----------/////
glColor3f(Color,Color,Color);
//////---------- Player 0 ----------/////
if(Player[0].Active == true)
  {
  Engine->OpenGl_Font->glPrint(410,427,Engine->Game->GameMain->Player[0].Name,0);
  Engine->OpenGl_Font->glPrint(410,410,"Hits:",0);
  itoa(Engine->Game->GameMain->Player[0].Hits,Temp_Text,10);
  Engine->OpenGl_Font->glPrint(460,409,Temp_Text,0);
  }
//////---------- Player 2 ----------/////
if(Player[2].Active == true)
  {
  Engine->OpenGl_Font->glPrint(410,350,Engine->Game->GameMain->Player[2].Name,0);
  Engine->OpenGl_Font->glPrint(410,333,"Hits:",0);
  itoa(Engine->Game->GameMain->Player[2].Hits,Temp_Text,10);
  Engine->OpenGl_Font->glPrint(460,332,Temp_Text,0);
  }
//////---------- Player 4 ----------/////
if(Player[4].Active == true)
  {
  Engine->OpenGl_Font->glPrint(410,273,Engine->Game->GameMain->Player[4].Name,0);
  Engine->OpenGl_Font->glPrint(410,256,"Hits:",0);
  itoa(Engine->Game->GameMain->Player[4].Hits,Temp_Text,10);
  Engine->OpenGl_Font->glPrint(460,255,Temp_Text,0);
  }
//////---------- Player 6 ----------/////
if(Player[6].Active == true)
  {
  Engine->OpenGl_Font->glPrint(410,196,Engine->Game->GameMain->Player[6].Name,0);
  Engine->OpenGl_Font->glPrint(410,179,"Hits:",0);
  itoa(Engine->Game->GameMain->Player[6].Hits,Temp_Text,10);
  Engine->OpenGl_Font->glPrint(460,178,Temp_Text,0);
  }
//////---------- Player 8 ----------/////
if(Player[8].Active == true)
  {
  Engine->OpenGl_Font->glPrint(410,117,Engine->Game->GameMain->Player[8].Name,0);
  Engine->OpenGl_Font->glPrint(410,100,"Hits:",0);
  itoa(Engine->Game->GameMain->Player[8].Hits,Temp_Text,10);
  Engine->OpenGl_Font->glPrint(460, 99,Temp_Text,0);
  }
//////---------- Player 10 ----------/////
if(Player[10].Active == true)
  {
  Engine->OpenGl_Font->glPrint(410,40,Engine->Game->GameMain->Player[10].Name,0);
  Engine->OpenGl_Font->glPrint(410,23,"Hits:",0);
  itoa(Engine->Game->GameMain->Player[10].Hits,Temp_Text,10);
  Engine->OpenGl_Font->glPrint(460,22,Temp_Text,0);
  }
//////----------    Red   ----------/////
//////---------- Player 1 ----------/////
if(Player[1].Active == true)
  {
  Engine->OpenGl_Font->glPrint(110,427,Engine->Game->GameMain->Player[1].Name,0);
  Engine->OpenGl_Font->glPrint(110,410,"Hits:",0);
  itoa(Engine->Game->GameMain->Player[1].Hits,Temp_Text,10);
  Engine->OpenGl_Font->glPrint(160,409,Temp_Text,0);
  }
//////---------- Player 3 ----------/////
if(Player[3].Active == true)
  {
  Engine->OpenGl_Font->glPrint(110,350,Engine->Game->GameMain->Player[3].Name,0);
  Engine->OpenGl_Font->glPrint(110,333,"Hits:",0);
  itoa(Engine->Game->GameMain->Player[3].Hits,Temp_Text,10);
  Engine->OpenGl_Font->glPrint(160,332,Temp_Text,0);
  }
//////---------- Player 5 ----------/////
if(Player[5].Active == true)
  {
  Engine->OpenGl_Font->glPrint(110,273,Engine->Game->GameMain->Player[5].Name,0);
  Engine->OpenGl_Font->glPrint(110,256,"Hits:",0);
  itoa(Engine->Game->GameMain->Player[5].Hits,Temp_Text,10);
  Engine->OpenGl_Font->glPrint(160,255,Temp_Text,0);
  }
//////---------- Player 7 ----------/////
if(Player[7].Active == true)
  {
  Engine->OpenGl_Font->glPrint(110,196,Engine->Game->GameMain->Player[7].Name,0);
  Engine->OpenGl_Font->glPrint(110,179,"Hits:",0);
  itoa(Engine->Game->GameMain->Player[7].Hits,Temp_Text,10);
  Engine->OpenGl_Font->glPrint(160,178,Temp_Text,0);
  }
//////---------- Player 9 ----------/////
if(Player[9].Active == true)
  {
  Engine->OpenGl_Font->glPrint(110,117,Engine->Game->GameMain->Player[9].Name,0);
  Engine->OpenGl_Font->glPrint(110,100,"Hits:",0);
  itoa(Engine->Game->GameMain->Player[9].Hits,Temp_Text,10);
  Engine->OpenGl_Font->glPrint(160, 99,Temp_Text,0);
  }
//////---------- Player 11 ----------/////
if(Player[11].Active == true)
  {
  Engine->OpenGl_Font->glPrint(110,40,Engine->Game->GameMain->Player[11].Name,0);
  Engine->OpenGl_Font->glPrint(110,23,"Hits:",0);
  itoa(Engine->Game->GameMain->Player[11].Hits,Temp_Text,10);
  Engine->OpenGl_Font->glPrint(160,22,Temp_Text,0);
  }
}

//------------------------------------------------------------------
void CGameMain::DrawTree(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=1;i++)
  {
  if(Tree[i].Type == 3 || Rules.Map == 3)continue;
  glPushMatrix();							

  if(Tree[i].Type == 1){glTranslatef(Tree[i].x,-4.77f,-15.0f);glBindTexture(GL_TEXTURE_2D,Tex_Tree1.texID);}
  if(Tree[i].Type == 2){glTranslatef(Tree[i].x,-4.73f,-15.0f);glBindTexture(GL_TEXTURE_2D,Tex_Tree2.texID);}
  if(Tree[i].Type == 4){glTranslatef(Tree[i].x,-4.7f,-15.0f);glBindTexture(GL_TEXTURE_2D,Tex_Tree3.texID);}

  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.9f,-1.3f,+0.0f);	
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.9f,-1.3f,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.9f,+1.3f,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.9f,+1.3f,-0.0f);	
  glEnd();
  glPopMatrix();
  }
}

//------------------------------------------------------------------
void CGameMain::DrawPlane(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=11;i++)
  {
  if(Player[i].Dead == false)
    {
    glPushMatrix();							
    glTranslatef(Player[i].x,Player[i].y,-15.0f);

    if((Equip[i].Option_Plane & 0x02) == 0x02 && i != Net_Id)glColor4f(Color,Color,Color,Player[i].Cloak);
    if((Equip[i].Option_Plane & 0x02) == 0x02 && i == Net_Id)glColor4f(Color,Color,Color,0.5f);

    if(i ==  0)glBindTexture(GL_TEXTURE_2D,Tex_Green_Plane.texID);
    if(i ==  2)glBindTexture(GL_TEXTURE_2D,Tex_Green_Plane.texID);
    if(i ==  4)glBindTexture(GL_TEXTURE_2D,Tex_Green_Plane.texID);
    if(i ==  6)glBindTexture(GL_TEXTURE_2D,Tex_Green_Plane.texID);
    if(i ==  8)glBindTexture(GL_TEXTURE_2D,Tex_Green_Plane.texID);
    if(i == 10)glBindTexture(GL_TEXTURE_2D,Tex_Green_Plane.texID);
    if(i ==  1)glBindTexture(GL_TEXTURE_2D,Tex_Red_Plane.texID);
    if(i ==  3)glBindTexture(GL_TEXTURE_2D,Tex_Red_Plane.texID);
    if(i ==  5)glBindTexture(GL_TEXTURE_2D,Tex_Red_Plane.texID);
    if(i ==  7)glBindTexture(GL_TEXTURE_2D,Tex_Red_Plane.texID);
    if(i ==  9)glBindTexture(GL_TEXTURE_2D,Tex_Red_Plane.texID);
    if(i == 11)glBindTexture(GL_TEXTURE_2D,Tex_Red_Plane.texID);

    glRotatef(Player[i].Rotate+90.0f,0.0f,0.0f,1.0f);
    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.15f,-0.15f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.15f,-0.15f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.15f,+0.15f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.15f,+0.15f,-0.0f);	
    glEnd();

    if((Equip[i].Option_Plane & 0x02) == 0x02)glColor4f(Color,Color,Color,1.0f);
    glPopMatrix();
    }
  }
}
//------------------------------------------------------------------
void CGameMain::DrawParticle(SEngine *Engine)
//------------------------------------------------------------------
{
for(int i=0;i<=199;i++)
  {
  if(Particle[i].Life > 0.0f)
    {
    glPushMatrix();
    if(Particle[i].IsTreeFire  != true)glTranslatef(Particle[i].x,Particle[i].y,-15.0f);
    if(Particle[i].IsTreeFire  == true)glTranslatef(Particle[i].x,Particle[i].y,-14.7f);

    glColor4f(Color,Color,Color,Particle[i].Life);

    if(Particle[i].IsFire  == true)glBindTexture(GL_TEXTURE_2D,Tex_Shot.texID);
    if(Particle[i].IsSmoke == true)glBindTexture(GL_TEXTURE_2D,Tex_Sky.texID);

    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.08f,-0.08f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.08f,-0.08f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.08f,+0.08f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.08f,+0.08f,-0.0f);	
    glEnd();
    glPopMatrix();
    }
  }
glColor4f(Color,Color,Color,1.0f);
}
//------------------------------------------------------------------
void CGameMain::HandleParticle(SEngine *Engine)
//------------------------------------------------------------------
{
bool DamagePlane_Finish[12];
bool DamageTree_Finish[2];
int  i;
char i_Player;

for(i=0;i<=11;i++){DamagePlane_Finish[i] = false;}
DamageTree_Finish[0] = false;DamageTree_Finish[1] = false;

for(i=0;i<=199;i++)
  {
  if(Particle[i].Life > 0.0f)
    {
    Particle[i].Life -= 0.001f * (float)Engine->Timer->GetDeltaMs();
    }
  if(Particle[i].Life <= 0.0f)
    {
    if(Rules.Map != 3 && Tree[0].Type != 3 && Tree[0].Burning == true && DamageTree_Finish[0] == false)
      {
      DamageTree_Finish[0] = true;
      if(rand()%12 == 0)
        {
	Particle[i].x = Tree[0].x+((rand()%180)-90)*0.01f;
	Particle[i].y = -5.3f+((rand()%100))*0.01f;
	Particle[i].Life = (rand()%20*0.01f)+0.8f;
	Particle[i].IsSmoke = false;
	Particle[i].IsFire  = true;
	Particle[i].IsTreeFire = true;
	}
      }
    if(Rules.Map != 3 && Tree[1].Type != 3 && Tree[1].Burning == true && DamageTree_Finish[1] == false)
      {
      DamageTree_Finish[1] = true;
      if(rand()%12 == 0)
        {
	Particle[i].x = Tree[1].x+((rand()%180)-90)*0.01f;
	Particle[i].y = -5.3f+((rand()%100))*0.01f;
	Particle[i].Life = (rand()%20*0.01f)+0.8f;
	Particle[i].IsSmoke = false;
	Particle[i].IsFire  = true;
	Particle[i].IsTreeFire = true;
	}
      }

    for(i_Player = 0;i_Player <= 11;i_Player++)
      {
      if(Player[i_Player].Dead == false && Player[i_Player].Damage == 1 && DamagePlane_Finish[i_Player] == false)
        {
	DamagePlane_Finish[i_Player] = true;
        if(rand()%15 == 0)
          {
	  Particle[i].x = Player[i_Player].x;
	  Particle[i].y = Player[i_Player].y;
	  Particle[i].Life = (rand()%20*0.01f)+0.8f;
	  Particle[i].IsSmoke = true;
	  Particle[i].IsFire  = false;
	  Particle[i].IsTreeFire = false;
	  }
        }
      if(Player[i_Player].Dead == false && Player[i_Player].Damage == 2 && DamagePlane_Finish[i_Player] == false)
        {
	DamagePlane_Finish[i_Player] = true;
        if(rand()%10 == 0)
          {
 	  Particle[i].x = Player[i_Player].x;
	  Particle[i].y = Player[i_Player].y;
	  Particle[i].Life = (rand()%20*0.01f)+0.8f;
	  Particle[i].IsSmoke = false;
	  Particle[i].IsFire  = true;
	  Particle[i].IsTreeFire = false;
	  }
	}
      }
    }
  }
}

//------------------------------------------------------------------
void CGameMain::MoveParticle(SEngine *Engine)
//------------------------------------------------------------------
{
for(int i=0;i<=199;i++)
  {
  if(Particle[i].Life > 0.0f)
    {
    if(Particle[i].IsTreeFire  != true)Particle[i].y -= 0.001f * (float)Engine->Timer->GetDeltaMs() * 0.34f;
    if(Particle[i].IsTreeFire  == true)Particle[i].y += 0.002f * (float)Engine->Timer->GetDeltaMs() * 0.34f;
    }
  }
}

//------------------------------------------------------------------
void CGameMain::DrawMen(SEngine *Engine)
//------------------------------------------------------------------
{
if(Player_Para_And_Man[Net_Id].IsMan == true)
  {
  glPushMatrix();
  glTranslatef(Player_Para_And_Man[Net_Id].x,-5.90f,-15.0f);

  glBindTexture(GL_TEXTURE_2D,Tex_Pointer.texID);

  glRotatef(Player_Para_And_Man[Net_Id].Rotate,0.0f,0.0f,1.0f);

  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.09f,-0.16f,+0.0f);	
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.09f,-0.16f,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.09f,+0.16f,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.09f,+0.16f,-0.0f);	
  glEnd();
  glPopMatrix();
  }

for(char i=0;i<=11;i++)
  {
  if(Player_Para_And_Man[i].IsMan == true)
    {
    glPushMatrix();
    glTranslatef(Player_Para_And_Man[i].x,-5.90f,-15.0f);

    if(i ==  0)glBindTexture(GL_TEXTURE_2D,Tex_Green_Man.texID);
    if(i ==  2)glBindTexture(GL_TEXTURE_2D,Tex_Green_Man.texID);
    if(i ==  4)glBindTexture(GL_TEXTURE_2D,Tex_Green_Man.texID);
    if(i ==  6)glBindTexture(GL_TEXTURE_2D,Tex_Green_Man.texID);
    if(i ==  8)glBindTexture(GL_TEXTURE_2D,Tex_Green_Man.texID);
    if(i == 10)glBindTexture(GL_TEXTURE_2D,Tex_Green_Man.texID);
    if(i ==  1)glBindTexture(GL_TEXTURE_2D,Tex_Red_Man.texID);
    if(i ==  3)glBindTexture(GL_TEXTURE_2D,Tex_Red_Man.texID);
    if(i ==  5)glBindTexture(GL_TEXTURE_2D,Tex_Red_Man.texID);
    if(i ==  7)glBindTexture(GL_TEXTURE_2D,Tex_Red_Man.texID);
    if(i ==  9)glBindTexture(GL_TEXTURE_2D,Tex_Red_Man.texID);
    if(i == 11)glBindTexture(GL_TEXTURE_2D,Tex_Red_Man.texID);

    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.11f,-0.11f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.11f,-0.11f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.11f,+0.11f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.11f,+0.11f,-0.0f);	
    glEnd();
    glPopMatrix();
    }
  }
}

//------------------------------------------------------------------
void CGameMain::DrawPara(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=11;i++)
  {
  if(Player_Para_And_Man[i].IsPara == true)
    {
    glPushMatrix();
    glTranslatef(Player_Para_And_Man[i].x,Player_Para_And_Man[i].y,-15.0f);

    if(Player_Para_And_Man[i].ParaDead == false && (Equip[i].Option_Para & 0x04) == 0x04 && i != Net_Id)glColor4f(Color,Color,Color,Player_Para_And_Man[i].Cloak);
    if(Player_Para_And_Man[i].ParaDead == false && (Equip[i].Option_Para & 0x04) == 0x04 && i == Net_Id)glColor4f(Color,Color,Color,0.5f);

    if(i ==  0 && Player_Para_And_Man[ 0].ParaDead == false)glBindTexture(GL_TEXTURE_2D,Tex_Green_Para.texID);
    if(i ==  2 && Player_Para_And_Man[ 2].ParaDead == false)glBindTexture(GL_TEXTURE_2D,Tex_Green_Para.texID);
    if(i ==  4 && Player_Para_And_Man[ 4].ParaDead == false)glBindTexture(GL_TEXTURE_2D,Tex_Green_Para.texID);
    if(i ==  6 && Player_Para_And_Man[ 6].ParaDead == false)glBindTexture(GL_TEXTURE_2D,Tex_Green_Para.texID);
    if(i ==  8 && Player_Para_And_Man[ 8].ParaDead == false)glBindTexture(GL_TEXTURE_2D,Tex_Green_Para.texID);
    if(i == 10 && Player_Para_And_Man[10].ParaDead == false)glBindTexture(GL_TEXTURE_2D,Tex_Green_Para.texID);
    if(i ==  1 && Player_Para_And_Man[ 1].ParaDead == false)glBindTexture(GL_TEXTURE_2D,Tex_Red_Para.texID);
    if(i ==  3 && Player_Para_And_Man[ 3].ParaDead == false)glBindTexture(GL_TEXTURE_2D,Tex_Red_Para.texID);
    if(i ==  5 && Player_Para_And_Man[ 5].ParaDead == false)glBindTexture(GL_TEXTURE_2D,Tex_Red_Para.texID);
    if(i ==  7 && Player_Para_And_Man[ 7].ParaDead == false)glBindTexture(GL_TEXTURE_2D,Tex_Red_Para.texID);
    if(i ==  9 && Player_Para_And_Man[ 9].ParaDead == false)glBindTexture(GL_TEXTURE_2D,Tex_Red_Para.texID);
    if(i == 11 && Player_Para_And_Man[11].ParaDead == false)glBindTexture(GL_TEXTURE_2D,Tex_Red_Para.texID);
    if(i ==  0 && Player_Para_And_Man[ 0].ParaDead == true)glBindTexture(GL_TEXTURE_2D,Tex_Green_Para_D.texID);
    if(i ==  2 && Player_Para_And_Man[ 2].ParaDead == true)glBindTexture(GL_TEXTURE_2D,Tex_Green_Para_D.texID);
    if(i ==  4 && Player_Para_And_Man[ 4].ParaDead == true)glBindTexture(GL_TEXTURE_2D,Tex_Green_Para_D.texID);
    if(i ==  6 && Player_Para_And_Man[ 6].ParaDead == true)glBindTexture(GL_TEXTURE_2D,Tex_Green_Para_D.texID);
    if(i ==  8 && Player_Para_And_Man[ 8].ParaDead == true)glBindTexture(GL_TEXTURE_2D,Tex_Green_Para_D.texID);
    if(i == 10 && Player_Para_And_Man[10].ParaDead == true)glBindTexture(GL_TEXTURE_2D,Tex_Green_Para_D.texID);
    if(i ==  1 && Player_Para_And_Man[ 1].ParaDead == true)glBindTexture(GL_TEXTURE_2D,Tex_Red_Para_D.texID);
    if(i ==  3 && Player_Para_And_Man[ 3].ParaDead == true)glBindTexture(GL_TEXTURE_2D,Tex_Red_Para_D.texID);
    if(i ==  5 && Player_Para_And_Man[ 5].ParaDead == true)glBindTexture(GL_TEXTURE_2D,Tex_Red_Para_D.texID);
    if(i ==  7 && Player_Para_And_Man[ 7].ParaDead == true)glBindTexture(GL_TEXTURE_2D,Tex_Red_Para_D.texID);
    if(i ==  9 && Player_Para_And_Man[ 9].ParaDead == true)glBindTexture(GL_TEXTURE_2D,Tex_Red_Para_D.texID);
    if(i == 11 && Player_Para_And_Man[11].ParaDead == true)glBindTexture(GL_TEXTURE_2D,Tex_Red_Para_D.texID);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.1f,-0.22f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.1f,-0.22f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.1f,+0.22f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.1f,+0.22f,-0.0f);	
    glEnd();

    if(Player_Para_And_Man[i].ParaDead == false && (Equip[i].Option_Para & 0x04) == 0x04)glColor4f(Color,Color,Color,1.0f);
    glPopMatrix();
    }
  }
}

//------------------------------------------------------------------
void CGameMain::HandleKeys(SEngine *Engine)
//------------------------------------------------------------------
{
if(Engine->Keys[VK_LEFT]    != Engine->Game->GameNetWork->Client_KeyPress_Left
|| Engine->Keys[VK_RIGHT]   != Engine->Game->GameNetWork->Client_KeyPress_Right
|| Engine->Keys[VK_UP]      != Engine->Game->GameNetWork->Client_KeyPress_Up
|| Engine->Keys[VK_DOWN]    != Engine->Game->GameNetWork->Client_KeyPress_Down 
|| Engine->Keys[VK_SPACE]   != Engine->Game->GameNetWork->Client_KeyPress_Fire 
|| Engine->Keys['E']        != Engine->Game->GameNetWork->Client_KeyPress_Para 
|| Engine->Keys[VK_CONTROL] != Engine->Game->GameNetWork->Client_KeyPress_Spec)
  {
  Engine->Game->GameNetWork->Client_KeyPress_Left    = Engine->Keys[VK_LEFT];
  Engine->Game->GameNetWork->Client_KeyPress_Right   = Engine->Keys[VK_RIGHT];
  Engine->Game->GameNetWork->Client_KeyPress_Down    = Engine->Keys[VK_DOWN];
  Engine->Game->GameNetWork->Client_KeyPress_Up      = Engine->Keys[VK_UP];
  Engine->Game->GameNetWork->Client_KeyPress_Fire    = Engine->Keys[VK_SPACE];
  Engine->Game->GameNetWork->Client_KeyPress_Spec    = Engine->Keys[VK_CONTROL];
  Engine->Game->GameNetWork->Client_KeyPress_Para    = Engine->Keys['E'];

  if(Player[0].SpecInvert == false)
    {
    if(Engine->Keys[VK_LEFT]    == true)Engine->Game->GameMain->Player[0].Key_Left  = true;
    if(Engine->Keys[VK_RIGHT]   == true)Engine->Game->GameMain->Player[0].Key_Right = true;
    if(Engine->Keys[VK_UP]      == true)Engine->Game->GameMain->Player[0].Key_Up    = true;
    if(Engine->Keys[VK_DOWN]    == true)Engine->Game->GameMain->Player[0].Key_Down  = true;
    if(Engine->Keys[VK_SPACE]   == true)Engine->Game->GameMain->Player[0].Key_Fire  = true;
    if(Engine->Keys[VK_CONTROL] == true)Engine->Game->GameMain->Player[0].Key_Spec  = true;
    if(Engine->Keys['E']        == true)Engine->Game->GameMain->Player[0].Key_Para  = true;

    if(Engine->Keys[VK_LEFT]    == false)Engine->Game->GameMain->Player[0].Key_Left  = false;
    if(Engine->Keys[VK_RIGHT]   == false)Engine->Game->GameMain->Player[0].Key_Right = false;
    if(Engine->Keys[VK_UP]      == false)Engine->Game->GameMain->Player[0].Key_Up    = false;
    if(Engine->Keys[VK_DOWN]    == false)Engine->Game->GameMain->Player[0].Key_Down  = false;
    if(Engine->Keys[VK_SPACE]   == false)Engine->Game->GameMain->Player[0].Key_Fire  = false;
    if(Engine->Keys[VK_CONTROL] == false)Engine->Game->GameMain->Player[0].Key_Spec  = false;
    if(Engine->Keys['E']        == false)Engine->Game->GameMain->Player[0].Key_Para  = false;
    }
  if(Player[0].SpecInvert == true)
    {
    if(Engine->Keys[VK_LEFT]    == true)Engine->Game->GameMain->Player[0].Key_Right  = true;
    if(Engine->Keys[VK_RIGHT]   == true)Engine->Game->GameMain->Player[0].Key_Left   = true;
    if(Engine->Keys[VK_UP]      == true)Engine->Game->GameMain->Player[0].Key_Down   = true;
    if(Engine->Keys[VK_DOWN]    == true)Engine->Game->GameMain->Player[0].Key_Up     = true;
    if(Engine->Keys[VK_SPACE]   == true)Engine->Game->GameMain->Player[0].Key_Spec   = true;
    if(Engine->Keys[VK_CONTROL] == true)Engine->Game->GameMain->Player[0].Key_Fire   = true;
    if(Engine->Keys['E']        == true)Engine->Game->GameMain->Player[0].Key_Para   = true;

    if(Engine->Keys[VK_LEFT]    == false)Engine->Game->GameMain->Player[0].Key_Right = false;
    if(Engine->Keys[VK_RIGHT]   == false)Engine->Game->GameMain->Player[0].Key_Left  = false;
    if(Engine->Keys[VK_UP]      == false)Engine->Game->GameMain->Player[0].Key_Down  = false;
    if(Engine->Keys[VK_DOWN]    == false)Engine->Game->GameMain->Player[0].Key_Up    = false;
    if(Engine->Keys[VK_SPACE]   == false)Engine->Game->GameMain->Player[0].Key_Spec  = false;
    if(Engine->Keys[VK_CONTROL] == false)Engine->Game->GameMain->Player[0].Key_Fire  = false;
    if(Engine->Keys['E']        == false)Engine->Game->GameMain->Player[0].Key_Para  = false;
    }

  Engine->Game->GameNetWork->Server_SendKeysUpdate(Engine,0);
  }
}

//------------------------------------------------------------------
void CGameMain::MovePlayers(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=11;i++)
  {
  if(Player[i].Dead == false)
    {
    //-------------------------------------------------------//
    //		       Players Plane moving		     //
    //-------------------------------------------------------//
    Player[i].x -= (float(sin(Player[i].Rotate/57.0f))) * Player[i].SpecSpeedHit * Player[i].Speed * 0.0017f * (float)Engine->Timer->GetDeltaMs();
    Player[i].y += (float(cos(Player[i].Rotate/57.0f))) * Player[i].SpecSpeedHit * Player[i].Speed * 0.0017f * (float)Engine->Timer->GetDeltaMs();
    if((Equip[i].Option_Plane & 0x01) == 0x01)Player[i].x -= (float(sin(Player[i].Rotate/57.0f))) * Player[i].SpecSpeedHit * Player[i].Speed * 0.0010f * (float)Engine->Timer->GetDeltaMs();
    if((Equip[i].Option_Plane & 0x01) == 0x01)Player[i].y += (float(cos(Player[i].Rotate/57.0f))) * Player[i].SpecSpeedHit * Player[i].Speed * 0.0010f * (float)Engine->Timer->GetDeltaMs();
    //-------------------------------------------------------//
    //		       Players Plane Stopping		     //
    //-------------------------------------------------------//
    if((Player[i].Speed > 0.15f && Player[i].Rotate < 150 || Player[i].Rotate > 210))(Player[i]).Speed -= (float)Engine->Timer->GetDeltaMs() * 0.0005f;
    //-------------------------------------------------------//
    //		       Players Plane Force Turn		     //
    //-------------------------------------------------------//
    if((Player+i)->Speed < 0.35f)
      {
      if(Player[i].Rotate < 180)Player[i].Rotate += (float)Engine->Timer->GetDeltaMs() * 0.2f;
      if(Player[i].Rotate > 180)Player[i].Rotate -= (float)Engine->Timer->GetDeltaMs() * 0.2f;
      }
    //-------------------------------------------------------//
    //		       Players Plane Turn bettwen 0-360	     //
    //-------------------------------------------------------//
    if(Player[i].Rotate <   0)Player[i].Rotate = 360;
    if(Player[i].Rotate > 360)Player[i].Rotate =   0;
    //-------------------------------------------------------//
    //		       Players Plane Speed-up down	     //
    //-------------------------------------------------------//
    if(Player[i].Rotate > 140 && Player[i].Rotate < 220){Player[i].Speed += (float)Engine->Timer->GetDeltaMs() * 0.0012f;}
    }
  }
}
//------------------------------------------------------------------
void CGameMain::HandlePlayers(SEngine *Engine)
//------------------------------------------------------------------
{
//-------- Plane Controls! --------//
for(char i=0;i<=11;i++)
  {
  if(Player[i].Dead == false && Player[i].Pilot == false && (Equip[i].Option_Para & 0x02) == 0x02)HandleAutoPilot(Engine,i);

  if(Player[i].Cloak > -2.0f && Player[i].CloakUp == false)
    {
    Player[i].Cloak -= 0.001f * (float)Engine->Timer->GetDeltaMs();
    }
  if(Player[i].Cloak <  3.0f && Player[i].CloakUp == true)
    {
    Player[i].Cloak += 0.001f * (float)Engine->Timer->GetDeltaMs();
    }
  if(Player[i].Cloak <= -2.0f && Player[i].CloakUp == false)Player[i].CloakUp = true;
  if(Player[i].Cloak >=  3.0f && Player[i].CloakUp == true )Player[i].CloakUp = false;

  if(Player[i].Pilot == true && Player[i].Dead == false)
    {
    //-------------------------------------------------------//
    //		    KEY_CHECK Player SPEED 		     //
    //-------------------------------------------------------//
    if(Player[i].Damage <= 0)if(Player[i].Key_Up == true && Player[i].Speed <= PLAYER_MAXPLANE_SPEED)Player[i].Speed += 0.00070f * (float)Engine->Timer->GetDeltaMs();
    if(Player[i].Damage == 1)if(Player[i].Key_Up == true && Player[i].Speed <= PLAYER_MAXPLANE_SMOKE_SPEED)Player[i].Speed += 0.00070f * (float)Engine->Timer->GetDeltaMs();
    //-------------------------------------------------------//
    //		    KEY_CHECK Player TURN 		     //
    //-------------------------------------------------------//
    if(Player[i].Damage <= 0)
      {
      if(Player[i].Key_Left  == true && ((Equip[i].Option_Plane & 0x08) != 0x08))Player[i].Rotate += 0.001f  * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      if(Player[i].Key_Right == true && ((Equip[i].Option_Plane & 0x08) != 0x08))Player[i].Rotate -= 0.001f  * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      if(Player[i].Key_Left  == true && ((Equip[i].Option_Plane & 0x08) == 0x08))Player[i].Rotate += 0.0018f * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      if(Player[i].Key_Right == true && ((Equip[i].Option_Plane & 0x08) == 0x08))Player[i].Rotate -= 0.0018f * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      }
    if(Player[i].Damage == 1)
      {
      if(Player[i].Key_Left  == true && ((Equip[i].Option_Plane & 0x08) != 0x08))Player[i].Rotate += 0.0008f * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      if(Player[i].Key_Right == true && ((Equip[i].Option_Plane & 0x08) != 0x08))Player[i].Rotate -= 0.0008f * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      if(Player[i].Key_Left  == true && ((Equip[i].Option_Plane & 0x08) == 0x08))Player[i].Rotate += 0.0012f * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      if(Player[i].Key_Right == true && ((Equip[i].Option_Plane & 0x08) == 0x08))Player[i].Rotate -= 0.0012f * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      }
    if(Player[i].Damage == 2)
      {
      if(Player[i].Key_Left  == true && ((Equip[i].Option_Plane & 0x08) != 0x08))Player[i].Rotate += 0.0003f  * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      if(Player[i].Key_Right == true && ((Equip[i].Option_Plane & 0x08) != 0x08))Player[i].Rotate -= 0.0003f  * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      if(Player[i].Key_Left  == true && ((Equip[i].Option_Plane & 0x08) == 0x08))Player[i].Rotate += 0.00045f * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      if(Player[i].Key_Right == true && ((Equip[i].Option_Plane & 0x08) == 0x08))Player[i].Rotate -= 0.00045f * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      }
    //-------------------------------------------------------//
    //		 KEY_CHECK Player JumpOut Para 		     //
    //-------------------------------------------------------//
    if(Engine->Server == true && Player[i].Key_Para == true && Player[i].y > -3.7f && Player[i].x < 8.1f && Player[i].x > -8.1f)Player_JumpPara(Engine,i);
    //-------------------------------------------------------//
    //		    KEY_CHECK Player Shot 		     //
    //-------------------------------------------------------//
    if(Player[i].Key_Fire == true && Shot[i].Active == false)Player_Fire(Engine,i);
    //-------------------------------------------------------//
    //		    KEY_CHECK Player Spec 		     //
    //-------------------------------------------------------//
    if(Player[i].Key_Spec == true && Spec[i].Active == false)Player_Spec(Engine,i);
    }
  }
}

//------------------------------------------------------------------
void CGameMain::DrawFPS(SEngine *Engine)
//------------------------------------------------------------------
{
FPS_Frames++;
FPS_Second -= 0.001f * (float)Engine->Timer->GetDeltaMs();
if(FPS_Second <= 0.0f)
  {
  FPS_Temp_Frames = FPS_Frames;
  FPS_Frames = 0;
  FPS_Second = 1.0f;
  }
Engine->OpenGl_Font->glPrint(540,450,"FPS: ",0);
char Temp_Text[12];
itoa(FPS_Temp_Frames,Temp_Text,10);
Engine->OpenGl_Font->glPrint(590,450,Temp_Text,0);
}

//------------------------------------------------------------------
void CGameMain::Collision_Wall(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=11;i++)
  {
  //------------------------------------------------------------------
  if(Player[i].Dead == false)
  //------------------------------------------------------------------
    {
    //-------------------------------------------------------//
    //		Player Collision with Left/Right Wall	     //
    //-------------------------------------------------------//
    if(Player[i].x >  8.445f){Player[i].x = -8.44f;}
    if(Player[i].x < -8.445f){Player[i].x =  8.44f;}
    //-------------------------------------------------------//
    //		Player Collision with Up Wall		     //
    //-------------------------------------------------------//
    if(Color >  1.0f)Color = 1.0f;
    if(Player[i].y > 6.3f && Player[i].Pilot == true && i == Net_Id)
      {
      if(Color > -0.0f)Color -= (0.002f * (float)Engine->Timer->GetDeltaMs());
      }
    if(Color <  1.0f)Color += 0.00005f * (float)Engine->Timer->GetDeltaMs();
    if(Player[i].y > 6.8)
      {
      Player[i].Rotate = 180;
      Player[i].Speed = 1.2f;
      }
    //-------------------------------------------------------//
    //		Player Collision with down Wall		     //
    //-------------------------------------------------------//
    if(Engine->Server == true && Player[i].y < -6.0f){Engine->Game->GameNetWork->Server_Collision(Engine,i,i,SERVER_COLLISION_WALL);Plane_Explosion(Engine,i);}
    }
  //------------------------------------------------------------------
  if(Shot[i].Active == true)
  //------------------------------------------------------------------
    {
    //-------------------------------------------------------//
    //		Shot Collision with Left/Right Wall	     //
    //-------------------------------------------------------//
    if(Shot[i].x >  8.445f)Shot[i].Active = false;
    if(Shot[i].x < -8.445f)Shot[i].Active = false;
    //-------------------------------------------------------//
    //		Shot Collision with Up Wall		     //
    //-------------------------------------------------------//
    if(Shot[i].y > 6.7f)Shot[i].Active = false;
    //-------------------------------------------------------//
    //		Shot Collision with down Wall		     //
    //-------------------------------------------------------//
    if(Shot[i].y < -6.0f)Shot[i].Active = false;
    }
  //------------------------------------------------------------------
  if(Spec[i].Active == true)
  //------------------------------------------------------------------
    {
    //-------------------------------------------------------//
    //		Shot Collision with Left/Right Wall	     //
    //-------------------------------------------------------//
    if(Spec[i].x >  8.445f)Spec[i].Active = false;
    if(Spec[i].x < -8.445f)Spec[i].Active = false;
    //-------------------------------------------------------//
    //		Shot Collision with Up Wall		     //
    //-------------------------------------------------------//
    if(Spec[i].y > 6.7f)Spec[i].Active = false;
    //-------------------------------------------------------//
    //		Shot Collision with down Wall		     //
    //-------------------------------------------------------//
    if(Spec[i].y < -6.0f)Spec[i].Active = false;
    }
  //-------------------------------------------------------//
  //		Man Collision with down Wall(ICE)	   //
  //-------------------------------------------------------//
  for(char Ice=0;Ice<=14;Ice++)
    {
    //-----------------  Man  -----------------//
    if(Map3_Active[Ice] == false && Player_Para_And_Man[i].IsMan == true && Rules.Map == 3)
      {
      if(8.0f-(Ice*1.2f) < Player_Para_And_Man[i].x+0.6f && -(Ice*1.2f)+0.6f+8.0f > Player_Para_And_Man[i].x)
        {
        Player_Para_And_Man[i].IsMan = false;
	}   
      }
    //----------------- Sphere -----------------//
    if(Map3_Active[Ice] == false && Player_Para_And_Man[i].IsSphere == true && Rules.Map == 3)
      {
      if(Sphere[i].y <= -5.78f && 8.0f-(Ice*1.2f) < Sphere[i].x+0.6f && -(Ice*1.2f)+0.6f+8.0f > Sphere[i].x)
        {
        Player_Para_And_Man[i].IsSphere = false;
	Sphere[i].Active = false;
	}   
      }
    }
  }
}

//------------------------------------------------------------------
void CGameMain::HandleGameOver(SEngine *Engine)
//------------------------------------------------------------------
{
char Green_Players = 0;
char Red_Players = 0;
char Active_Players = 0;

for(char i = 0;i<=11;i++){if(Player[i].Active == true)Active_Players++;}

if(Player[ 0].Dead == false || (Player_Para_And_Man[ 0].IsPara == true && Player_Para_And_Man[ 0].ParaDead == false) || Player_Para_And_Man[ 0].IsMan == true || Player_Para_And_Man[ 0].IsSphere == true)Green_Players++;
if(Player[ 2].Dead == false || (Player_Para_And_Man[ 2].IsPara == true && Player_Para_And_Man[ 2].ParaDead == false) || Player_Para_And_Man[ 2].IsMan == true || Player_Para_And_Man[ 2].IsSphere == true)Green_Players++;
if(Player[ 4].Dead == false || (Player_Para_And_Man[ 4].IsPara == true && Player_Para_And_Man[ 4].ParaDead == false) || Player_Para_And_Man[ 4].IsMan == true || Player_Para_And_Man[ 4].IsSphere == true)Green_Players++;
if(Player[ 6].Dead == false || (Player_Para_And_Man[ 6].IsPara == true && Player_Para_And_Man[ 6].ParaDead == false) || Player_Para_And_Man[ 6].IsMan == true || Player_Para_And_Man[ 6].IsSphere == true)Green_Players++;
if(Player[ 8].Dead == false || (Player_Para_And_Man[ 8].IsPara == true && Player_Para_And_Man[ 8].ParaDead == false) || Player_Para_And_Man[ 8].IsMan == true || Player_Para_And_Man[ 8].IsSphere == true)Green_Players++;
if(Player[10].Dead == false || (Player_Para_And_Man[10].IsPara == true && Player_Para_And_Man[10].ParaDead == false) || Player_Para_And_Man[10].IsMan == true || Player_Para_And_Man[10].IsSphere == true)Green_Players++;
if(Player[ 1].Dead == false || (Player_Para_And_Man[ 1].IsPara == true && Player_Para_And_Man[ 1].ParaDead == false) || Player_Para_And_Man[ 1].IsMan == true || Player_Para_And_Man[ 1].IsSphere == true)Red_Players++;
if(Player[ 3].Dead == false || (Player_Para_And_Man[ 3].IsPara == true && Player_Para_And_Man[ 3].ParaDead == false) || Player_Para_And_Man[ 3].IsMan == true || Player_Para_And_Man[ 3].IsSphere == true)Red_Players++;
if(Player[ 5].Dead == false || (Player_Para_And_Man[ 5].IsPara == true && Player_Para_And_Man[ 5].ParaDead == false) || Player_Para_And_Man[ 5].IsMan == true || Player_Para_And_Man[ 5].IsSphere == true)Red_Players++;
if(Player[ 7].Dead == false || (Player_Para_And_Man[ 7].IsPara == true && Player_Para_And_Man[ 7].ParaDead == false) || Player_Para_And_Man[ 7].IsMan == true || Player_Para_And_Man[ 7].IsSphere == true)Red_Players++;
if(Player[ 9].Dead == false || (Player_Para_And_Man[ 9].IsPara == true && Player_Para_And_Man[ 9].ParaDead == false) || Player_Para_And_Man[ 9].IsMan == true || Player_Para_And_Man[ 9].IsSphere == true)Red_Players++;
if(Player[11].Dead == false || (Player_Para_And_Man[11].IsPara == true && Player_Para_And_Man[11].ParaDead == false) || Player_Para_And_Man[11].IsMan == true || Player_Para_And_Man[11].IsSphere == true)Red_Players++;

for(i = 0;i<=11;i++)
  {
  if(!(Player[i].Dead == false || (Player_Para_And_Man[i].IsPara == true && Player_Para_And_Man[i].ParaDead == false) || Player_Para_And_Man[i].IsMan == true || Player_Para_And_Man[i].IsSphere == true)){Equip[i].Option_Plane = 0;Equip[i].Option_Para = 0;Equip[i].Option_Shot = 0;Equip[i].Option_Spec = 0;}
  }
if(/*Active_Players >= 2 &&*/ (Red_Players <= 0 || Green_Players <= 0))
  {
  if(GameOver == false)Engine->Game->GameNetWork->Server_GameOver_Packet(Engine);
  GameOver = true;
  NewRound_Second -= 0.001f * (float)Engine->Timer->GetDeltaMs();
  if(NewRound_Second <= 0.0f)
    {
    NewRound_Count--;
    NewRound_Second = 1.0f;
    }
  if(NewRound_Count < 0)
    {
    if(Red_Players <= 0)GreenTeam_Score++;
    if(Green_Players <= 0)RedTeam_Score++;
    Engine->Game->GameNetWork->Server_SendEquip(Engine);
    ResetRound(Engine);
    }
  }
}
//------------------------------------------------------------------
void CGameMain::Plane_Explosion(SEngine *Engine,char Target_Player)
//------------------------------------------------------------------
{
Player[Target_Player].Dead = true;
Explo[Target_Player].Active = true;
Explo[Target_Player].x = Player[Target_Player].x;
Explo[Target_Player].y = Player[Target_Player].y;
Explo[Target_Player].grow = 0.0f;
Engine->DirectX_Sound->Play("data//sound//crash.dat",false);
}
//------------------------------------------------------------------
void CGameMain::HandleAI(SEngine *Engine,char Who)
//------------------------------------------------------------------
{
char Target;

if(Who == 1 || Who == 3 || Who == 5 || Who == 7 || Who == 9 || Who == 11)
  {
  if(Player[ 0].Dead == false)Target =  0;
  if(Player[ 2].Dead == false)Target =  2;
  if(Player[ 4].Dead == false)Target =  4;
  if(Player[ 6].Dead == false)Target =  6;
  if(Player[ 8].Dead == false)Target =  8;
  if(Player[10].Dead == false)Target = 10;
  }
if(Who == 0 || Who == 2 || Who == 4 || Who == 6 || Who == 8 || Who == 10)
  {
  if(Player[ 1].Dead == false)Target =  1;
  if(Player[ 3].Dead == false)Target =  3;
  if(Player[ 5].Dead == false)Target =  5;
  if(Player[ 7].Dead == false)Target =  7;
  if(Player[ 9].Dead == false)Target =  9;
  if(Player[11].Dead == false)Target = 11;
  }

//Player[Who].Key_Right = false;
//Player[Who].Key_Left  = false;
Engine->Keys[VK_LEFT]  =  false;
Engine->Keys[VK_RIGHT] = false;
Engine->Keys['E']      = false;

if(Player_Para_And_Man[Who].IsMan == true)
  {
/*
  Player[Who].Key_Spec = true;
  Player[Who].Key_Fire = true;
  Player[Who].Key_Up   = false;
  Player[Who].Key_Down = false;
*/
  Engine->Keys[VK_CONTROL] = true;
  Engine->Keys[VK_SPACE]   = false;
  if(Engine->Game->GameMain->Rules.GameState_Buying == false)Engine->Keys[VK_SPACE]   = true;
  Engine->Keys[VK_UP]      = false;
  Engine->Keys[VK_DOWN]    = false;

  return;
  }

//Player[Who].Key_Up   = true;
Engine->Keys[VK_UP]    = true;

if(Player[Who].Pilot == false)return;

if(Player[Who].Damage >= 1 && Player[Who].y < -3.5f)Engine->Keys['E']    = true;//Player[Who].Key_Para = true;

if(Player[Who].Speed > 2.1){Engine->Keys[VK_UP] = false;Engine->Keys[VK_RIGHT] = true;/*Player[Who].Key_Up   = false;Player[Who].Key_Right = true;*/return;} // Decrease speed

if(Player[Who].y < -3.6f) // Get Up
  {
  if(Player[Who].Rotate <= 180)Engine->Keys[VK_RIGHT] = true;//Player[Who].Key_Right = true;
  if(Player[Who].Rotate >  180)Engine->Keys[VK_LEFT]  = true;//Player[Who].Key_Left  = true;
  return;
  }
if(Player[Who].y >  5.0f) // Get Down
  {
  if(Player[Who].Rotate <= 180)Engine->Keys[VK_LEFT]  = true;//Player[Who].Key_Left  = true;
  if(Player[Who].Rotate >  180)Engine->Keys[VK_RIGHT] = true;//Player[Who].Key_Right = true;
  return;
  }

//============================//
//Always turn agains the enemy//
//============================//
if((Player[Target].x < Player[Who].x) && (Player[Who].Rotate < 45 || Player[Who].Rotate > 135))
  {
  if(Player[Who].Rotate <    45)Engine->Keys[VK_LEFT] = true;//Player[Who].Key_Left  = true;
  if(Player[Who].Rotate >=  225 && Player[Who].Rotate <=  360)Engine->Keys[VK_LEFT]  = true;//Player[Who].Key_Left = true;
  if(Player[Who].Rotate >   135 && Player[Who].Rotate <=  225)Engine->Keys[VK_RIGHT] = true;//Player[Who].Key_Right = true;
  return;
  }

if((Player[Target].x > Player[Who].x) && (Player[Who].Rotate > 315 || Player[Who].Rotate < 225))
  {
  if(Player[Who].Rotate >  315 || Player[Who].Rotate <  90)Engine->Keys[VK_RIGHT] = true;//Player[Who].Key_Right = true;
  if(Player[Who].Rotate <  225 && Player[Who].Rotate >= 90)Engine->Keys[VK_LEFT]  = true;//Player[Who].Key_Left  = true;
  return;
  }

//============================//
//Always be in the same height//
//============================//

if(Player[Target].y < Player[Who].y-2.0f)
  {
  if(Player[Who].Rotate <= 180)Engine->Keys[VK_LEFT]  = true;//Player[Who].Key_Left  = true;
  if(Player[Who].Rotate >  180)Engine->Keys[VK_RIGHT] = true;//Player[Who].Key_Right = true;
  return;
  }

if(Player[Target].y > Player[Who].y+2.0f)
  {
  if(Player[Who].Rotate <= 180)Engine->Keys[VK_RIGHT] = true;//Player[Who].Key_Right = true;
  if(Player[Who].Rotate >  180)Engine->Keys[VK_LEFT]  = true;//Player[Who].Key_Left  = true;
  return;
  }

//Player[Who].Key_Fire = true;
//Player[Who].Key_Spec = true;

Engine->Keys[VK_SPACE]   = true;
Engine->Keys[VK_CONTROL] = true;
}

//------------------------------------------------------------------
void CGameMain::HandleExplosion(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=11;i++)
  {
  if(Explo[i].Active == true)
    {
    Explo[i].grow += 0.001f * (float)Engine->Timer->GetDeltaMs();
    if(Explo[i].grow > 1.5f)
      {
      Explo[i].Active = false;
      }
    }
  }
}
//------------------------------------------------------------------
void CGameMain::DrawExplosion(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=11;i++)
  {
  if(Explo[i].Active == true)
    {
    glPushMatrix();							
    glTranslatef(Explo[i].x,Explo[i].y,-15.0f); 

    glBindTexture(GL_TEXTURE_2D,Tex_Shot.texID);

    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-Explo[i].grow,-Explo[i].grow,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+Explo[i].grow,-Explo[i].grow,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+Explo[i].grow,+Explo[i].grow,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-Explo[i].grow,+Explo[i].grow,-0.0f);	
    glEnd();
    glPopMatrix();
    }
  }
}
//------------------------------------------------------------------
void CGameMain::Player_JumpPara(SEngine *Engine,char Target_Player)
//------------------------------------------------------------------
{
Player[Target_Player].Pilot = false;

if((Equip[Target_Player].Option_Para & 0x08) == 0x08)
  {
  Player_Para_And_Man[Target_Player].IsSphere = true;
  Sphere[Target_Player].x         = Player[Target_Player].x;
  Sphere[Target_Player].y         = Player[Target_Player].y;
  Sphere[Target_Player].Rotate    = Player[Target_Player].Rotate;
  Sphere[Target_Player].Speed     = Player[Target_Player].Speed;
  Sphere[Target_Player].Active    = true;
  Sphere[Target_Player].Bounce    = 10;
  Sphere[Target_Player].SpeedDown = 0.0f;
  Sphere[Target_Player].Rotating  = 0.0f;
  }

if((Equip[Target_Player].Option_Para & 0x08) != 0x08)
  {
  Player_Para_And_Man[Target_Player].IsPara = true;
  Player_Para_And_Man[Target_Player].x = Player[Target_Player].x;
  Player_Para_And_Man[Target_Player].y = Player[Target_Player].y;
  Player_Para_And_Man[Target_Player].Cloak = 1.0f;
  }

Engine->Game->GameNetWork->Server_SendParaJump(Engine,Target_Player);
}

//------------------------------------------------------------------
void CGameMain::MovePara(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=11;i++)
  {
  if(Player_Para_And_Man[i].IsPara == true)
    {
    Player_Para_And_Man[i].y -= 0.001f * (float)Engine->Timer->GetDeltaMs() * PLAYER_PARA_SPEED;
    if((Equip[i].Option_Para & 0x01) == 0x01)Player_Para_And_Man[i].y -= 0.001f * (float)Engine->Timer->GetDeltaMs() * PLAYER_PARA_SPEED;
    //----------------------- Landing ---------------------//
    if(Player_Para_And_Man[i].y <= -5.8f && Player_Para_And_Man[i].ParaDead == false)
      {
      Player_Para_And_Man[i].IsPara = false;
      Player_Para_And_Man[i].IsMan  = true;
      }
    if(Player_Para_And_Man[i].y <= -5.8f && Player_Para_And_Man[i].ParaDead == true)
      {
      Player_Para_And_Man[i].IsPara = false;
      Player_Para_And_Man[i].IsMan  = false;
      }
    }
  }
}

//------------------------------------------------------------------
void CGameMain::HandleMen(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=11;i++)
  {
  if(Player_Para_And_Man[i].IsMan == true)
    {
    //-------------------------------------------------------//
    //			    Men Move			     //
    //-------------------------------------------------------//
    if(Player[i].Key_Left  == true && Player_Para_And_Man[i].x > -8.1f)Player_Para_And_Man[i].x -= 0.0001f * (float)Engine->Timer->GetDeltaMs();
    if(Player[i].Key_Right == true && Player_Para_And_Man[i].x <  8.1f)Player_Para_And_Man[i].x += 0.0001f * (float)Engine->Timer->GetDeltaMs();
    //-------------------------------------------------------//
    //			    Men Move Gun		     //
    //-------------------------------------------------------//
    if(Player[i].Key_Up   == true && (Player_Para_And_Man[i].Rotate > 225.0f || Player_Para_And_Man[i].Rotate < 190.0f))Player_Para_And_Man[i].Rotate -= 0.1f * (float)Engine->Timer->GetDeltaMs();
    if(Player[i].Key_Down == true && (Player_Para_And_Man[i].Rotate < 115.0f || Player_Para_And_Man[i].Rotate > 190.0f))Player_Para_And_Man[i].Rotate += 0.1f * (float)Engine->Timer->GetDeltaMs();
    //-------------------------------------------------------//
    //		       Men Guns Turn bettwen 0-360	     //
    //-------------------------------------------------------//
    if(Player_Para_And_Man[i].Rotate <   0)Player_Para_And_Man[i].Rotate = 360;
    if(Player_Para_And_Man[i].Rotate > 360)Player_Para_And_Man[i].Rotate =   0;
    //-------------------------------------------------------//
    //				Men Shot 		     //
    //-------------------------------------------------------//
    if(Player[i].Key_Fire == true && Shot[i].Active == false)Man_Fire(Engine,i);
    //-------------------------------------------------------//
    //				Men Spec 		     //
    //-------------------------------------------------------//
    if(Player[i].Key_Spec == true && Spec[i].Active == false)Man_Spec(Engine,i);
    }
  }
}

//------------------------------------------------------------------
void CGameMain::HandleSky(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=1;i++)
  {
  if(Sky[i].Active == true)
    {
    if(Sky[i].x > 10.1 || Sky[i].x < -10.1)
      {
      Sky[i].Active = false;
      }
    }
  if(Engine->Server == true && Sky[i].Active == false)
    {
    if(rand()%1000 == 1)
      {
      char Temp;
      Sky[i].Active = true;
      Sky[i].y      = ((rand()%100)-50)*0.1f;
      Temp = rand()%2;
      if(Temp == 0)
	{
	Sky[i].x          =  10.0f;
	Sky[i].MovingLeft = true;
	}
      if(Temp == 1)
	{
	Sky[i].x          = -10.0f;
	Sky[i].MovingLeft = false;
	}
      Temp = rand()%2;
      if(Temp == 0)Sky[i].IsDark = true;
      if(Temp == 1)Sky[i].IsDark = false;
      Engine->Game->GameNetWork->Server_SendSkyUpdate(Engine);
      return;
      }
    }
  }
}

//------------------------------------------------------------------
void CGameMain::HandlePara(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=11;i++)
  {
  if(Player_Para_And_Man[i].IsPara == true && Player_Para_And_Man[i].ParaDead == false)
    {
    if(Player[i].Key_Left  == true && Player_Para_And_Man[i].x > -8.1f)Player_Para_And_Man[i].x -= 0.0001f * (float)Engine->Timer->GetDeltaMs();
    if(Player[i].Key_Right == true && Player_Para_And_Man[i].x <  8.1f)Player_Para_And_Man[i].x += 0.0001f * (float)Engine->Timer->GetDeltaMs();
    }
  if(Player_Para_And_Man[i].Cloak > 0.0f)
    {
    Player_Para_And_Man[i].Cloak -= 0.001f * (float)Engine->Timer->GetDeltaMs();
    }
  }
}

//------------------------------------------------------------------
void CGameMain::Player_Fire(SEngine *Engine,char Target_Player)
//------------------------------------------------------------------
{
Shot[Target_Player].Active = true;
Shot[Target_Player].x	   = Player[Target_Player].x;
Shot[Target_Player].y	   = Player[Target_Player].y;
Shot[Target_Player].Rotate = Player[Target_Player].Rotate;
Shot[Target_Player].Cloak = 1.0f;
Engine->DirectX_Sound->Play("data//sound//Shot.dat",false);
}

//------------------------------------------------------------------
void CGameMain::Player_Spec(SEngine *Engine,char Target_Player)
//------------------------------------------------------------------
{
Spec[Target_Player].Active = true;
Spec[Target_Player].x	   = Player[Target_Player].x;
Spec[Target_Player].y	   = Player[Target_Player].y;
Spec[Target_Player].Rotate = Player[Target_Player].Rotate;
Engine->DirectX_Sound->Play("data//sound//Spec.dat",false);
}
//------------------------------------------------------------------
void CGameMain::Man_Fire(SEngine *Engine,char Target_Player)
//------------------------------------------------------------------
{
Shot[Target_Player].Active = true;
Shot[Target_Player].x	   = Player_Para_And_Man[Target_Player].x;
Shot[Target_Player].y	   = Player_Para_And_Man[Target_Player].y;
Shot[Target_Player].Rotate = Player_Para_And_Man[Target_Player].Rotate;
Shot[Target_Player].Cloak = 1.0f;
Engine->DirectX_Sound->Play("data//sound//Shot.dat",false);
}

//------------------------------------------------------------------
void CGameMain::Man_Spec(SEngine *Engine,char Target_Player)
//------------------------------------------------------------------
{
Spec[Target_Player].Active = true;
Spec[Target_Player].x	   = Player_Para_And_Man[Target_Player].x;
Spec[Target_Player].y	   = Player_Para_And_Man[Target_Player].y;
Spec[Target_Player].Rotate = Player_Para_And_Man[Target_Player].Rotate;
Engine->DirectX_Sound->Play("data//sound//Spec.dat",false);
}
//------------------------------------------------------------------
void CGameMain::DrawShot(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=11;i++)
  {
  if(Shot[i].Active == true)
    {
    glPushMatrix();
    glTranslatef(Shot[i].x,Shot[i].y,-15.0f);

    if((Equip[i].Option_Shot & 0x02) == 0x02 && i != Net_Id)glColor4f(Color,Color,Color,Shot[i].Cloak);
    if((Equip[i].Option_Shot & 0x02) == 0x02 && i == Net_Id)glColor4f(Color,Color,Color,0.5f);
    if((Equip[i].Option_Shot & 0x04) == 0x04)glColor3f(Color,0.0f,0.0f);
    glBindTexture(GL_TEXTURE_2D,Tex_Shot.texID);

    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.05f,-0.05f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.05f,-0.05f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.05f,+0.05f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.05f,+0.05f,-0.0f);	
    glEnd();
    if((Equip[i].Option_Shot & 0x02) == 0x02 || (Equip[i].Option_Shot & 0x04) == 0x04)glColor4f(Color,Color,Color,1.0f);
    glPopMatrix();
    }
  }
}
//------------------------------------------------------------------
void CGameMain::DrawSky(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=1;i++)
  {
  if(Sky[i].Active == true)
    {
    glPushMatrix();
    glTranslatef(Sky[i].x,Sky[i].y,-15.0f);

    if(Sky[i].IsDark == false)glBindTexture(GL_TEXTURE_2D,Tex_Sky.texID);
    if(Sky[i].IsDark == true )glBindTexture(GL_TEXTURE_2D,Tex_Sky_Dark.texID);

    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.3f,-1.3f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+1.3f,-1.3f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+1.3f,+1.3f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.3f,+1.3f,-0.0f);	
    glEnd();
    glPopMatrix();
    }
  }
}

//------------------------------------------------------------------
void CGameMain::MoveSky(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=1;i++)
  {
  if(Sky[i].Active == true)
    {
    if(Sky[i].MovingLeft == true)
      {
      Sky[i].x -= 0.2f * 0.001f * (float)Engine->Timer->GetDeltaMs();
      }
    if(Sky[i].MovingLeft == false)
      {
      Sky[i].x += 0.2f * 0.001f * (float)Engine->Timer->GetDeltaMs();
      }
    }
  }
}

//------------------------------------------------------------------
void CGameMain::DrawSpec(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=11;i++)
  {
  if(Spec[i].Active == true)
    {
    glPushMatrix();
    glTranslatef(Spec[i].x,Spec[i].y,-15.0f);

    glBindTexture(GL_TEXTURE_2D,Tex_Spec.texID);

    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.05f,-0.05f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.05f,-0.05f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.05f,+0.05f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.05f,+0.05f,-0.0f);	
    glEnd();
    glPopMatrix();
    }
  }
}
//------------------------------------------------------------------
void CGameMain::MoveShot(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=11;i++)
  {
  if(Shot[i].Active == true)
    {
    Shot[i].x -= (float(sin(Shot[i].Rotate/57.0f))) * SHOT_SPEED * 0.0017f * (float)Engine->Timer->GetDeltaMs();
    Shot[i].y += (float(cos(Shot[i].Rotate/57.0f))) * SHOT_SPEED * 0.0017f * (float)Engine->Timer->GetDeltaMs();
    if((Equip[i].Option_Shot & 0x01) == 0x01)Shot[i].x -= (float(sin(Shot[i].Rotate/57.0f))) * SHOT_SPEED * 0.0007f * (float)Engine->Timer->GetDeltaMs();
    if((Equip[i].Option_Shot & 0x01) == 0x01)Shot[i].y += (float(cos(Shot[i].Rotate/57.0f))) * SHOT_SPEED * 0.0007f * (float)Engine->Timer->GetDeltaMs();
    }
  if(Shot[i].Cloak > 0.0f)
    {
    Shot[i].Cloak -= 0.001f * (float)Engine->Timer->GetDeltaMs();
    }
  }
}
//------------------------------------------------------------------
void CGameMain::MoveSpec(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=11;i++)
  {
  if(Spec[i].Active == true)
    {
    Spec[i].x -= (float(sin(Spec[i].Rotate/57.0f))) * SPEC_SPEED * 0.0017f * (float)Engine->Timer->GetDeltaMs();
    Spec[i].y += (float(cos(Spec[i].Rotate/57.0f))) * SPEC_SPEED * 0.0017f * (float)Engine->Timer->GetDeltaMs();
    }
  }
}
//------------------------------------------------------------------
void CGameMain::Collision_Shot(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=11;i++)
  {
  if(Shot[i].Active == true)
    {
    //------------------------------------------------------------------
    //	Player COLLISION!!!
    //------------------------------------------------------------------
    for(char i_Player=0;i_Player<=11;i_Player++)
      {
      //------------------------------------------------------------------
      if(Engine->Server == true && Player[i_Player].Dead == false)
      //------------------------------------------------------------------
        {
	if(Player[i_Player].x < Shot[i].x+0.15f && Player[i_Player].x+0.15f > Shot[i].x)
          {
	  if(Player[i_Player].y < Shot[i].y+0.15f && Player[i_Player].y+0.15f > Shot[i].y)
  	    {
	    if(i != i_Player)
	      {
	      Engine->Game->GameNetWork->Server_Collision(Engine,i,i_Player,SERVER_COLLISION_FIRE);
	      char Temp_Rand = rand()%4;
	      if(Temp_Rand == 0)Engine->DirectX_Sound->Play("data//sound//hit1.dat",false);
	      if(Temp_Rand == 1)Engine->DirectX_Sound->Play("data//sound//hit2.dat",false);
	      if(Temp_Rand == 2)Engine->DirectX_Sound->Play("data//sound//hit3.dat",false);
	      if(Temp_Rand == 3)Engine->DirectX_Sound->Play("data//sound//hit4.dat",false);
	      if((Equip[i].Option_Shot & 0x04) == 0x04)Player[i_Player].Damage++;
	      Player[i_Player].Damage++;
	      Shot[i].Active = false;
	      Player[i].Hits++;
	      Player[i].Money += 75;
	      if(Player[i_Player].Damage >= 3)
		  {
			  Player_JumpPara(Engine,i_Player);
			  Plane_Explosion(Engine,i_Player);
	      }
		}
	    }
	  }
	}
      //------------------------------------------------------------------
      if(Engine->Server == true && Player_Para_And_Man[i_Player].IsPara == true && Player_Para_And_Man[i_Player].ParaDead == false)
      //------------------------------------------------------------------
        {
	if(Player_Para_And_Man[i_Player].x < Shot[i].x+0.1f && Player_Para_And_Man[i_Player].x+0.1f > Shot[i].x)
          {
	  if(Player_Para_And_Man[i_Player].y < Shot[i].y+0.22f && Player_Para_And_Man[i_Player].y+0.22f > Shot[i].y)
  	    {
	    if(i != i_Player)
	      {
	      Engine->Game->GameNetWork->Server_Collision(Engine,i,i_Player,SERVER_COLLISION_PARA_SHOT);
	      Player_Para_And_Man[i_Player].ParaDead = true;
	      Shot[i].Active = false;
	      Player[i].Hits++;
	      Player[i].Money += 75;
	      Engine->DirectX_Sound->Play("data//sound//PlayerHit.dat",false);
	      }
	    }
	  }
	}
      //------------------------------------------------------------------
      if(Engine->Server == true && Player_Para_And_Man[i_Player].IsMan == true)
      //------------------------------------------------------------------
        {
	if(Player_Para_And_Man[i_Player].x < Shot[i].x+0.11f && Player_Para_And_Man[i_Player].x+0.11f > Shot[i].x)
          {
	  if(Player_Para_And_Man[i_Player].y < Shot[i].y+0.33f && Player_Para_And_Man[i_Player].y+0.11f > Shot[i].y)
  	    {
	    if(i != i_Player)
	      {
	      Engine->Game->GameNetWork->Server_Collision(Engine,i,i_Player,SERVER_COLLISION_MAN_SHOT);
	      Player_Para_And_Man[i_Player].IsMan = false;
	      Shot[i].Active = false;
	      Player[i].Hits++;
	      Player[i].Money += 75;
	      Engine->DirectX_Sound->Play("data//sound//PlayerHit.dat",false);
	      }
	    }
	  }
	}
      }
    //------------------------------------------------------------------
    //	Animal COLLISION!!!
    //------------------------------------------------------------------
    if(Animal.Dead == false && Rules.Map != 3)
      {
      if(Animal.x < Shot[i].x+0.15f && Animal.x+0.15f > Shot[i].x)
        {
 	if(-5.89f < Shot[i].y+0.15f && -5.89f+0.15f > Shot[i].y)
	  {
	  Animal.Dead = true;
	  Shot[i].Active = false;
	      Engine->DirectX_Sound->Play("data//sound//PlayerHit.dat",false);
	  }   
	}
      }
    //------------------------------------------------------------------
    //	Tre COLLISION!!!
    //------------------------------------------------------------------
    if(Tree[0].Burning == false && Tree[0].Type != 3 && Rules.Map != 3)
      {
      if(Tree[0].x < Shot[i].x+0.9f && Tree[0].x+0.9f > Shot[i].x)
        {
 	if(-4.73f < Shot[i].y+1.3f && -4.73f+1.3f > Shot[i].y)
	  {
	  Tree[0].Burning = true;
	  Shot[i].Active  = false;
	  }   
	}
      }
    if(Tree[1].Burning == false && Tree[1].Type != 3 && Rules.Map != 3)
      {
      if(Tree[1].x < Shot[i].x+0.9f && Tree[1].x+0.9f > Shot[i].x)
        {
 	if(-4.73f < Shot[i].y+1.3f && -4.73f+1.3f > Shot[i].y)
	  {
	  Tree[1].Burning = true;
	  Shot[i].Active  = false;
	  }   
	}
      }
    //------------------------------------------------------------------
    //	Level3 Ice COLLISION!!!
    //------------------------------------------------------------------
    for(char Ice=0;Ice<=14;Ice++)
      {
      if(Map3_Active[Ice] == true)
        {
        if(8.0f-(Ice*1.2f) < Shot[i].x+0.6f && -(Ice*1.2f)+0.6f+8.0f > Shot[i].x)
          {
 	  if(-5.95f > Shot[i].y)
	    {
	    Map3_Active[Ice] = false;
	    Shot[i].Active = false;
	    }
	  }   
	}
      }
    }
  }
}

//------------------------------------------------------------------
void CGameMain::Collision_Spec(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=11;i++)
  {
  if(Spec[i].Active == true)
    {
    //------------------------------------------------------------------
    //	Player COLLISION!!!
    //------------------------------------------------------------------
    for(char i_Player=0;i_Player<=11;i_Player++)
      {
      //------------------------------------------------------------------
      if(Engine->Server == true && Player[i_Player].Dead == false)
      //------------------------------------------------------------------
        {
	if(Player[i_Player].x < Spec[i].x+0.15f && Player[i_Player].x+0.15f > Spec[i].x)
          {
	  if(Player[i_Player].y < Spec[i].y+0.15f && Player[i_Player].y+0.15f > Spec[i].y)
  	    {
	    if(i != i_Player && Spec[i].Active == true)
	      {
	      Engine->Game->GameNetWork->Server_Collision(Engine,i,i_Player,SERVER_COLLISION_SPEC);
	      Spec[i].Active = false;
	      Engine->DirectX_Sound->Play("data//sound//Spec_hit.dat",false);

	      Player[i_Player].Rotate += 60;
	      Player[i_Player].Speed = 0.0f;

	      if(Player[i_Player].Pilot == true)
		{
	        if((Equip[i].Option_Spec & 0x01) == 0x01)
	          {
	  	  //if(Player[i_Player].SpecSpeedHit > 0.4f)Player[i_Player].SpecSpeedHit -= 0.3f;
		  if(i_Player == Net_Id)Drugs_On = true;
		  }
	        if((Equip[i].Option_Spec & 0x02) == 0x02)
	          {
		  if(Player[i_Player].SpecInvert == true)Player[i_Player].SpecInvert = false;
		  else Player[i_Player].SpecInvert = true;
		  }
	        if((Equip[i].Option_Spec & 0x04) == 0x04)
	          {
		  if(i_Player == Net_Id)Color = -0.7f;
		  }
	        if((Equip[i].Option_Spec & 0x08) == 0x08)
	          {
		  if(Player[i].y > -3.7f && Player[i].x < 8.1f && Player[i].x > -8.1f)Player_JumpPara(Engine,i_Player);
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }
}

//------------------------------------------------------------------
void CGameMain::Collision_Explosion(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=11;i++)
  {
  if(Explo[i].Active == true)
    {
    //------------------------------------------------------------------
    //	Level3 Ice COLLISION!!!
    //------------------------------------------------------------------
    for(char Ice=0;Ice<=14;Ice++)
      {
      if(Map3_Active[Ice] == true)
        {
        if(8.0f-(Ice*1.2f) < Explo[i].x+Explo[i].grow && -(Ice*1.2f)+0.6f+8.0f > Explo[i].x-Explo[i].grow)
          {
 	  if(-5.95f > Explo[i].y-Explo[i].grow)
	    {
	    Map3_Active[Ice] = false;
	    }
	  }   
	}
      }
    //------------------------------------------------------------------
    //	Tre COLLISION!!!
    //------------------------------------------------------------------
    if(Tree[0].Burning == false && Tree[0].Type != 3 && Rules.Map != 3)
      {
      if(Tree[0].x < Explo[i].x+Explo[i].grow && Tree[0].x+0.9f > Explo[i].x-Explo[i].grow)
        {
 	if(-4.73f < Explo[i].y+Explo[i].grow && -4.73f+1.3f > Explo[i].y-Explo[i].grow)
	  {
	  Tree[0].Burning = true;
	  Shot[i].Active  = false;
	  }   
	}
      }
    if(Tree[1].Burning == false && Tree[1].Type != 3 && Rules.Map != 3)
      {
      if(Tree[1].x < Explo[i].x+Explo[i].grow && Tree[1].x+0.9f > Explo[i].x+Explo[i].grow)
        {
 	if(-4.73f < Explo[i].y-Explo[i].grow && -4.73f+1.3f > Explo[i].y-Explo[i].grow)
	  {
	  Tree[1].Burning = true;
	  Shot[i].Active  = false;
	  }   
	}
      }
    //------------------------------------------------------------------
    //	Animal COLLISION!!!
    //------------------------------------------------------------------
    if(Animal.Dead == false && Rules.Map != 3)
      {
      if(Animal.x < Explo[i].x+Explo[i].grow && Animal.x+0.15f > Explo[i].x-Explo[i].grow)
        {
 	if(-5.89f < Explo[i].y+Explo[i].grow && -5.89f+0.15f > Explo[i].y-Explo[i].grow)
	  {
	  Animal.Dead = true;
	  Engine->DirectX_Sound->Play("data//sound//PlayerHit.dat",false);
	  }   
	}
      }
    //------------------------------------------------------------------
    //	Player COLLISION!!!
    //------------------------------------------------------------------
    for(char i_Player=0;i_Player<=11;i_Player++)
      {
      //------------------------------------------------------------------
      if(Engine->Server == true && Player[i_Player].Dead == false)
      //------------------------------------------------------------------
        {
	if(Player[i_Player].x < Explo[i].x+Explo[i].grow && Player[i_Player].x+0.15f > Explo[i].x-Explo[i].grow)
          {
	  if(Player[i_Player].y < Explo[i].y+Explo[i].grow && Player[i_Player].y+0.15f > Explo[i].y-Explo[i].grow)
  	    {
	    if(Player[i_Player].Damage == 0 || Player[i_Player].Damage == 1)
	      {
	      Engine->Game->GameNetWork->Server_Collision(Engine,i,i_Player,SERVER_COLLISION_PLAYER_EXPLO);
              Player[i_Player].Damage = 2;
	      Engine->DirectX_Sound->Play("data//sound//Player_Flame.dat",false); 
	      }
	    }
	  }
	}
      //------------------------------------------------------------------
      if(Engine->Server == true && Player_Para_And_Man[i_Player].IsPara == true && Player_Para_And_Man[i_Player].ParaDead == false)
      //------------------------------------------------------------------
        {
	if(Player_Para_And_Man[i_Player].x < Explo[i].x+Explo[i].grow && Player_Para_And_Man[i_Player].x+0.1f > Explo[i].x-Explo[i].grow)
          {
	  if(Player_Para_And_Man[i_Player].y < Explo[i].y+Explo[i].grow && Player_Para_And_Man[i_Player].y+0.22f > Explo[i].y-Explo[i].grow)
  	    {
            Engine->Game->GameNetWork->Server_Collision(Engine,i,i_Player,SERVER_COLLISION_PARA);
	    Player_Para_And_Man[i_Player].ParaDead = true;
	    Engine->DirectX_Sound->Play("data//sound//PlayerHit.dat",false); 
	    }
	  }
	}
      //------------------------------------------------------------------
      if(Engine->Server == true && Player_Para_And_Man[i_Player].IsMan == true)
      //------------------------------------------------------------------
        {
	if(Player_Para_And_Man[i_Player].x < Explo[i].x+Explo[i].grow && Player_Para_And_Man[i_Player].x+0.11f > Explo[i].x-Explo[i].grow)
          {
	  if(Player_Para_And_Man[i_Player].y < Explo[i].y+Explo[i].grow && Player_Para_And_Man[i_Player].y+0.11f > Explo[i].y-Explo[i].grow)
  	    {
	    Engine->Game->GameNetWork->Server_Collision(Engine,i,i_Player,SERVER_COLLISION_MAN);
	    Player_Para_And_Man[i_Player].IsMan = false;
	    Engine->DirectX_Sound->Play("data//sound//PlayerHit.dat",false);
	    }
	  }
	}
      }
    }
  }
}

//------------------------------------------------------------------
void CGameMain::Collision_Tiger(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i = 0;i <= 11;i++)
  {
  if(Animal.Dead == false && Rules.Map == 2 && Player_Para_And_Man[i].IsMan == true)
    {
    if(Animal.x < Player_Para_And_Man[i].x+0.15f && Animal.x+0.15f > Player_Para_And_Man[i].x)
      {
      Player_Para_And_Man[i].IsMan = false;
      }
    }
  }
}

//------------------------------------------------------------------
void CGameMain::Collision_Sky(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i = 0;i <= 11;i++)
  {
  if(Player[i].Dead == false)
    {
    if(Sky[0].Active == true && Sky[0].IsDark == true && Sky[0].x < Player[i].x+1.0f && Sky[0].x+1.0f > Player[i].x)
      {
      if(Player[i].y < Sky[0].y+1.0f && Player[i].y+1.0f > Sky[0].y)
	{
        if(Player[i].Pilot == true && i == Net_Id && Color > -0.0f){Color -= (0.002f * (float)Engine->Timer->GetDeltaMs());}
	}
      }
    if(Sky[1].Active == true && Sky[1].IsDark == true && Sky[1].x < Player[i].x+1.0f && Sky[1].x+1.0f > Player[i].x)
      {
      if(Player[i].y < Sky[1].y+1.0f && Player[i].y+1.0f > Sky[1].y)
        {
        if(Player[i].Pilot == true && i == Net_Id && Color > -0.0f){Color -= (0.002f * (float)Engine->Timer->GetDeltaMs());}
	}
      }
    }
  }
}

//------------------------------------------------------------------
void CGameMain::Collision_Plane(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=11;i++)
  {
  if(Player[i].Dead == false)
    {
    //------------------------------------------------------------------
    //	Player COLLISION!!!
    //------------------------------------------------------------------
    for(char i_Player=0;i_Player<=11;i_Player++)
      {
      //------------------------------------------------------------------
      if(Engine->Server == true && Player[i_Player].Dead == false)
      //------------------------------------------------------------------
        {
	if(Player[i_Player].x < Player[i].x+0.15f && Player[i_Player].x+0.15f > Player[i].x)
          {
	  if(Player[i_Player].y < Player[i].y+0.15f && Player[i_Player].y+0.15f > Player[i].y)
  	    {
	    if(i != i_Player && (Player[i_Player].Damage != 2 || Player[i_Player].Damage != 2))
	      {
	      Engine->Game->GameNetWork->Server_Collision(Engine,i,i_Player,SERVER_COLLISION_PLAYER);
	      Player[i_Player].Damage = 2;
	      Player[i].Damage	      = 2;
	      Engine->DirectX_Sound->Play("data//sound//Player_Collision.dat",false);
	      }
	    }
	  }
	}
      //------------------------------------------------------------------
      if(Engine->Server == true && Player_Para_And_Man[i_Player].IsPara == true)
      //------------------------------------------------------------------
        {
	if(Player_Para_And_Man[i_Player].ParaDead == false && Player_Para_And_Man[i_Player].x < Player[i].x+0.1f && Player_Para_And_Man[i_Player].x+0.1f > Player[i].x)
          {
	  if(Player_Para_And_Man[i_Player].y < Player[i].y+0.22f && Player_Para_And_Man[i_Player].y+0.22f > Player[i].y)
  	    {
	    if(i != i_Player)
	      {
	      if(Player_Para_And_Man[i_Player].ParaDead == false){Engine->Game->GameNetWork->Server_Collision(Engine,i,i_Player,SERVER_COLLISION_PARA);Player[i].Hits++;Player[i].Money += 75;Engine->DirectX_Sound->Play("data//sound//PlayerHit.dat",false);}
	      Player_Para_And_Man[i_Player].ParaDead = true;
	      //Player[i].Rotate += (rand()%90)-45;
	      //Player[i].Speed = 0.4f;
	      }
	    }
	  }
	}
      //------------------------------------------------------------------
      if(Engine->Server == true && Player_Para_And_Man[i_Player].IsMan == true)
      //------------------------------------------------------------------
        {
	if(Player_Para_And_Man[i_Player].x < Player[i].x+0.11f && Player_Para_And_Man[i_Player].x+0.11f > Player[i].x)
          {
	  if(Player_Para_And_Man[i_Player].y < Player[i].y+0.11f && Player_Para_And_Man[i_Player].y+0.11f > Player[i].y)
  	    {
	    if(i != i_Player)
	      {
	      Engine->Game->GameNetWork->Server_Collision(Engine,i,i_Player,SERVER_COLLISION_MAN);
	      Player_Para_And_Man[i_Player].IsMan = false;
	      Player[i].Hits++;
	      Player[i].Money += 75;
	      Engine->DirectX_Sound->Play("data//sound//PlayerHit.dat",false);
	      }
	    }
	  }
	}
      }
    //------------------------------------------------------------------
    //	Animal COLLISION!!!
    //------------------------------------------------------------------
    if(Animal.Dead == false && Rules.Map != 3)
      {
      if(Animal.x < Player[i].x+0.15f && Animal.x+0.15f > Player[i].x)
        {
 	if(-5.89f < Player[i].y+0.15f && -5.89f+0.15f > Player[i].y)
	  {
	  Animal.Dead = true;
	  Engine->DirectX_Sound->Play("data//sound//PlayerHit.dat",false);
	  }   
	}
      }
    }
  }
}

//------------------------------------------------------------------
void CGameMain::Collision_Tree(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i = 0;i <= 11;i++)
  {
  if(Rules.Map != 3 && Engine->Server == true && Player_Para_And_Man[i].IsPara == true && Player_Para_And_Man[i].ParaDead == false)
    {
    if(Tree[0].Burning == true && Tree[0].Type != 3 && Tree[0].x < Player_Para_And_Man[i].x+0.9f && Tree[0].x+0.9f > Player_Para_And_Man[i].x)
      {
      if(Player_Para_And_Man[i].y < -4.77f+1.22f && Player_Para_And_Man[i].y+1.22f > -4.77f)
  	{
        Engine->Game->GameNetWork->Server_Collision(Engine,i,i,SERVER_COLLISION_PARA);
        Player_Para_And_Man[i].ParaDead = true;
        Engine->DirectX_Sound->Play("data//sound//PlayerHit.dat",false); 
	}
      }
    if(Tree[1].Burning == true && Tree[1].Type != 3 && Tree[1].x < Player_Para_And_Man[i].x+0.9f && Tree[1].x+0.9f > Player_Para_And_Man[i].x)
      {
      if(Player_Para_And_Man[i].y < -4.77f+1.22f && Player_Para_And_Man[i].y+1.22f > -4.77f)
  	{
        Engine->Game->GameNetWork->Server_Collision(Engine,i,i,SERVER_COLLISION_PARA);
        Player_Para_And_Man[i].ParaDead = true;
        Engine->DirectX_Sound->Play("data//sound//PlayerHit.dat",false); 
	}
      }
    }

  if(Rules.Map != 3 && Engine->Server == true && Player[i].Dead == false)
    {
    if(Tree[0].Burning == true && Tree[0].Type != 3 && Tree[0].x < Player[i].x+0.9f && Tree[0].x+0.9f > Player[i].x)
      {
      if(Player[i].y < -4.77f+1.3f && Player[i].y+1.3f > -4.77f && Player[i].Damage == 0)
	{
        Engine->Game->GameNetWork->Server_Collision(Engine,i,i,SERVER_COLLISION_TREE);
        Player[i].Damage = 1;
	Engine->DirectX_Sound->Play("data//sound//Player_Flame.dat",false);
	}
      }
    if(Tree[1].Burning == true && Tree[1].Type != 3 && Tree[1].x < Player[i].x+0.9f && Tree[1].x+0.9f > Player[i].x)
      {
      if(Player[i].y <  -4.77f+1.3f && Player[i].y+1.3f >  -4.77f && Player[i].Damage == 0)
        {
        Engine->Game->GameNetWork->Server_Collision(Engine,i,i,SERVER_COLLISION_TREE);
        Player[i].Damage = 1;
   	Engine->DirectX_Sound->Play("data//sound//Player_Flame.dat",false);
	}
      }
    }
  }
}

//------------------------------------------------------------------
void CGameMain::HandleAutoPilot(SEngine *Engine,char Target_Player)
//------------------------------------------------------------------
{

//-------------------------------------------------------//
//		     AutoPilot Shot 	   		 //
//-------------------------------------------------------//
if(Shot[Target_Player].Active == false && Player_Para_And_Man[Target_Player].IsMan == false)Player_Fire(Engine,Target_Player);
//-------------------------------------------------------//
//		     AutoPilot Spec	 		 //
//-------------------------------------------------------//
if(Spec[Target_Player].Active == false && Player_Para_And_Man[Target_Player].IsMan == false)Player_Spec(Engine,Target_Player);
//-------------------------------------------------------//
//		  AutoPilot SPEED 			 //
//-------------------------------------------------------//
if(Player[Target_Player].Damage <= 0)if(Player[Target_Player].Speed <= PLAYER_MAXPLANE_SPEED)Player[Target_Player].Speed += 0.00070f * (float)Engine->Timer->GetDeltaMs();
if(Player[Target_Player].Damage == 1)if(Player[Target_Player].Speed <= PLAYER_MAXPLANE_SMOKE_SPEED)Player[Target_Player].Speed += 0.00070f * (float)Engine->Timer->GetDeltaMs();
//-------------------------------------------------------//
//		  AutoPilot TURN 			 //
//-------------------------------------------------------//

if(Player[Target_Player].y < -2.0f) // Get Up
  {
  if(Player[Target_Player].Rotate <= 180)
    {
    if(Player[Target_Player].Damage <= 0)
      {
      Player[Target_Player].Rotate -= 0.001f * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      }
    if(Player[Target_Player].Damage == 1)
      {
      Player[Target_Player].Rotate -= 0.0008f * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      }
    if(Player[Target_Player].Damage == 2)
      {
      Player[Target_Player].Rotate -= 0.0003f * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      }
    }
  if(Player[Target_Player].Rotate >  180)
    {
    if(Player[Target_Player].Damage <= 0)
      {
      Player[Target_Player].Rotate += 0.001f * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      }
    if(Player[Target_Player].Damage == 1)
      {
      Player[Target_Player].Rotate += 0.0008f * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      }
    if(Player[Target_Player].Damage == 2)
      {
      Player[Target_Player].Rotate += 0.0003f * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      }
    }
  return;
  }
if(Player[Target_Player].y >  5.0f) // Get Down
  {
  if(Player[Target_Player].Rotate <= 180)
    {
    if(Player[Target_Player].Damage <= 0)
      {
      Player[Target_Player].Rotate += 0.001f * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      }
    if(Player[Target_Player].Damage == 1)
      {
      Player[Target_Player].Rotate += 0.0008f * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      }
    if(Player[Target_Player].Damage == 2)
      {
      Player[Target_Player].Rotate += 0.0003f * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      }
    }
  if(Player[Target_Player].Rotate >  180)
    {
    if(Player[Target_Player].Damage <= 0)
      {
      Player[Target_Player].Rotate -= 0.001f * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      }
    if(Player[Target_Player].Damage == 1)
      {
      Player[Target_Player].Rotate -= 0.0008f * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      }
    if(Player[Target_Player].Damage == 2)
      {
      Player[Target_Player].Rotate -= 0.0003f * (float)Engine->Timer->GetDeltaMs() * PLAYER_PLANETURN_SPEED;
      }
    }
  return;
  }
}

//------------------------------------------------------------------
void CGameMain::DrawPacket(SEngine *Engine)
//------------------------------------------------------------------
{
Engine->OpenGl_Font->glPrint(500,430,"Packets: ",0);
char Temp_Text[12];
itoa(Packet_Count,Temp_Text,10);
Engine->OpenGl_Font->glPrint(590,430,Temp_Text,0);
}

//------------------------------------------------------------------
void CGameMain::Draw_ServerClose(SEngine *Engine)
//------------------------------------------------------------------
{
Engine->OpenGl_Font->glPrint(220,220,"Server disconnected...",0);
}

//------------------------------------------------------------------
void CGameMain::DrawPing(SEngine *Engine)
//------------------------------------------------------------------
{
Engine->OpenGl_Font->glPrint(500,410,"Player1: ",0);
Engine->OpenGl_Font->glPrint(500,390,"Player2: ",0);
Engine->OpenGl_Font->glPrint(500,370,"Player3: ",0);
Engine->OpenGl_Font->glPrint(500,350,"Player4: ",0);
Engine->OpenGl_Font->glPrint(500,330,"Player5: ",0);
Engine->OpenGl_Font->glPrint(500,310,"Player6: ",0);
Engine->OpenGl_Font->glPrint(500,290,"Player7: ",0);
Engine->OpenGl_Font->glPrint(500,270,"Player8: ",0);
Engine->OpenGl_Font->glPrint(500,250,"Player9: ",0);
Engine->OpenGl_Font->glPrint(500,230,"Player10: ",0);
Engine->OpenGl_Font->glPrint(500,210,"Player11: ",0);
Engine->OpenGl_Font->glPrint(500,190,"Player12: ",0);
char Temp_Text[12];

for(char i=0;i<=11;i++)
  {
  sprintf(Temp_Text,"%3.1f",Engine->Game->GameNetWork->Client_Ping_Delay[i]);
//  itoa(Engine->Game->GameNetWork->Client_Ping_Delay[i],Temp_Text,10);
  Engine->OpenGl_Font->glPrint(590,410-(i*20),Temp_Text,0);
  }
}

//------------------------------------------------------------------
void CGameMain::HandleDrugs(SEngine *Engine)
//------------------------------------------------------------------
{
if(Drugs_Effect > 0.0f && Drugs_On == false)Drugs_Effect = 0.0f;
if(Drugs_Effect < 0.0f && Drugs_On == false)
  {
  Drugs_Effect += 0.001f * (float)Engine->Timer->GetDeltaMs();
  }
if(Drugs_On == true)
  {
  Drugs_Effect -= 0.0005f * (float)Engine->Timer->GetDeltaMs();
  if(Drugs_Effect <= -5.0f)Drugs_On = false;
  }
}

//------------------------------------------------------------------
void CGameMain::DrawSphere(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=11;i++)
  {
  if(Sphere[i].Active == true)
    {
    glPushMatrix();
    glTranslatef(Sphere[i].x,Sphere[i].y,-15.0f);
    glRotatef(Sphere[i].Rotating,0.0f,0.0f,1.0f);

    if((Equip[i].Option_Para & 0x04) == 0x04 && i != Net_Id)glColor4f(Color,Color,Color,Player_Para_And_Man[i].Cloak);
    if((Equip[i].Option_Para & 0x04) == 0x04 && i == Net_Id)glColor4f(Color,Color,Color,0.5f);

    glBindTexture(GL_TEXTURE_2D,Tex_Sphere.texID);

    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.10f,-0.10f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.10f,-0.10f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.10f,+0.10f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.10f,+0.10f,-0.0f);	
    glEnd();

    if((Equip[i].Option_Para & 0x04) == 0x04)glColor4f(Color,Color,Color,1.0f);

    glPopMatrix();
    }
  }
}

//------------------------------------------------------------------
void CGameMain::MoveSphere(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=11;i++)
  {
  if(Sphere[i].Active == true)
    {
    Sphere[i].x -= (float(sin(Sphere[i].Rotate/57.0f))) * Sphere[i].Speed * 0.0017f * (float)Engine->Timer->GetDeltaMs();
    Sphere[i].y += 0.1f * Sphere[i].SpeedDown * (float)Engine->Timer->GetDeltaMs();

    Sphere[i].Rotating += 0.1f * (float(sin(Sphere[i].Rotate/57.0f))) * (float)Engine->Timer->GetDeltaMs();
    Sphere[i].SpeedDown -= 0.00008f * (float)Engine->Timer->GetDeltaMs();
    }
  }
}

//------------------------------------------------------------------
void CGameMain::HandleSphere(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=11;i++)
  {
  if(Sphere[i].Active == true)
    {
    if(Player_Para_And_Man[i].Cloak > 0.0f)
      {
      Player_Para_And_Man[i].Cloak -= 0.001f * (float)Engine->Timer->GetDeltaMs();
      }
    if(Sphere[i].Bounce <= 0)
      {
      Sphere[i].Active = false;
      Player_Para_And_Man[i].IsSphere = false;
      Player_Para_And_Man[i].IsMan    = true;
      Player_Para_And_Man[i].x        = Sphere[i].x;
      Player_Para_And_Man[i].y        = Sphere[i].y;
      }
    if(Sphere[i].y <= -5.8f)
      {
      Sphere[i].Bounce--;
      Sphere[i].SpeedDown *= -0.7f;
      Sphere[i].y = -5.78f;
      }
    if(Sphere[i].x < -8.1f)
      {
      Sphere[i].Speed    *= -1.0f;
      Sphere[i].Rotating *= -1.0f;
      Sphere[i].x = -8.08f;
      }
    if(Sphere[i].x >  8.1f)
      {
      Sphere[i].Speed    *= -1.0f;
      Sphere[i].Rotating *= -1.0f;
      Sphere[i].x =  8.08f;
      }
    }
  }
}

//------------------------------------------------------------------
void CGameMain::HandleRemoteExplosion(SEngine *Engine)
//------------------------------------------------------------------
{
for(char i=0;i<=11;i++)
  {
  if(((Equip[i].Option_Shot & 0x08) == 0x08) && Player[i].Key_Fire == false && Shot[i].Active == true)
    {
    Shot[i].Active  = false;
    Explo[i].x      = Shot[i].x;
    Explo[i].y      = Shot[i].y;
    Explo[i].grow   = 0.0f;
    Explo[i].Active = true;
    }
  }
}

