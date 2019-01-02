#include <conio.h>
#include <stdio.h>
#include <windows.h>

int main()
{
bool High_Resolution = false;
bool GetTickCounter  = false;
char Tast	     = 0x00;

while(Tast != 27 && Tast != '9')
  {
  printf("//-----------------------------------//\n");
  printf("--        Welcome to Timer Test      --\n");
  printf("--                                   --\n");
  printf("--  1. Test High-Resolution Counter  --\n");
  printf("--  2. Test GetTickCounter           --\n");
  printf("--                                   --\n");
  printf("--  9. Quit                          --\n");
  printf("--                                   --\n");
  printf("//-----------------------------------//\n\n");

  Tast = getch();

  High_Resolution = false;
  GetTickCounter  = false;
  if(Tast == '1')High_Resolution = true;
  if(Tast == '2')GetTickCounter  = true;

  if(GetTickCounter == true)
    {
    //------------- Init Values ----------------//
    int Start,End,Diferent;

    //------------ Start Counter ---------------//
    Start = GetTickCount();
    printf("Start:     %i\n\n",Start); 

    //-------------   Pause	----------------//
    for(int i = 0;i<=999999;i++){char a = 0x00;a = 1+i;a *= i;}

    //------------- End Counter ----------------//
    End = GetTickCount();
    printf("End:       %i\n\n",End); 

    //------------- Diferent Counter ----------------//
    Diferent = End - Start;
    printf("Different: %i\n\n",Diferent); 
    }
  if(High_Resolution == true)
    {
    //------------- Init Values ----------------//
    LARGE_INTEGER nTime,m_nTimingFreq; 
    QueryPerformanceFrequency(&m_nTimingFreq);
    double Start,End,Diferent;

    //------------ Start Counter ---------------//
    QueryPerformanceCounter(&nTime);
    Start = (double)nTime.QuadPart;
    printf("Start:     %f\n\n",Start); 

    //-------------   Pause	----------------//
    for(int i = 0;i<=999999;i++){char a = 0x00;a = 1+i;a *= i;}

    //------------- End Counter ----------------//
    QueryPerformanceCounter(&nTime);
    End = (double)nTime.QuadPart;
    printf("End:       %f\n\n",End); 

    //------------- Diferent Counter ----------------//
    Diferent = End - Start;

    double fUsed=((double)m_nTimingFreq.QuadPart)/(Diferent);
    Diferent = 1000.0f/fUsed;

    printf("Different: %f\n\n",Diferent); 
    }
  }
return 0;
}