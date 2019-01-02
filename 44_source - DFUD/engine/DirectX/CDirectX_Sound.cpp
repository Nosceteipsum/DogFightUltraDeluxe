////////////////////////////////////////////////////////////////////
//								  //
//			DirectX Sound			  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#include "CDirectX_Sound.h"

//--------------------------------------------------------------------------------
char *CDirectX_Sound::Get_Error_Message(){return Error_Message;}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
bool CDirectX_Sound::Error_Check(){return Error_Detected;}
//--------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
CDirectX_Sound::CDirectX_Sound()
//----------------------------------------------------------------------------------------------
{

}
//----------------------------------------------------------------------------------------------
CDirectX_Sound::~CDirectX_Sound()
//----------------------------------------------------------------------------------------------
{

}

//----------------------------------------------------------------------------------------------
void CDirectX_Sound::Deinit()
//----------------------------------------------------------------------------------------------
{
//delete MusicManager;
}

//----------------------------------------------------------------------------------------------
void CDirectX_Sound::Init()
//----------------------------------------------------------------------------------------------
{
/*
if(Error_Detected == true)return;

try
  {
  MusicManager = NULL;
  Sound	     = NULL;

  MusicManager = new CMusicManager();
  MusicManager->Initialize(NULL);
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in CDirectX_Sound::Init",45);
  }
*/
}
//----------------------------------------------------------------------------------------------
void CDirectX_Sound::Play(char *Path,bool Loop)
//----------------------------------------------------------------------------------------------
{
/*
if(Error_Detected == true)return;

try
  {
  MusicManager->CreateSegmentFromFile( &Sound,Path);

  if(Sound == NULL)return;
  if(Loop == false){Sound->SetRepeats(1) ;Sound->Play(DMUS_SEGF_SECONDARY);}
  if(Loop == true ){Sound->SetRepeats(30);Sound->Play(DSBPLAY_LOOPING);}
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in CDirectX_Sound::Play",45);
  }
*/
}
/*
//----------------------------------------------------------------------------------------------
//		Direct X Utilies Code
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
VOID DXUtil_Trace(TCHAR* strMsg,... )
//----------------------------------------------------------------------------------------------
{
UNREFERENCED_PARAMETER(strMsg);
}

//-----------------------------------------------------------------------------
// Name: DXUtil_ConvertAnsiStringToWide()
// Desc: This is a UNICODE conversion utility to convert a CHAR string into a
//       WCHAR string. cchDestChar defaults -1 which means it 
//       assumes strDest is large enough to store strSource
//-----------------------------------------------------------------------------
VOID DXUtil_ConvertAnsiStringToWide( WCHAR* wstrDestination, const CHAR* strSource,int cchDestChar)
{
if(wstrDestination==NULL || strSource==NULL)return;
if(cchDestChar == -1)cchDestChar = strlen(strSource)+1;

MultiByteToWideChar(CP_ACP,0,strSource,-1,wstrDestination,cchDestChar-1);
wstrDestination[cchDestChar-1] = 0;
}

//-----------------------------------------------------------------------------
// Name: DXUtil_ConvertGenericStringToWide()
// Desc: This is a UNICODE conversion utility to convert a TCHAR string into a
//       WCHAR string. cchDestChar defaults -1 which means it 
//       assumes strDest is large enough to store strSource
//-----------------------------------------------------------------------------
VOID DXUtil_ConvertGenericStringToWide( WCHAR* wstrDestination, const TCHAR* tstrSource,int cchDestChar)
{
if( wstrDestination==NULL || tstrSource==NULL || cchDestChar == 0)return;
#ifdef _UNICODE
if( cchDestChar == -1 )
  {
  wcscpy( wstrDestination, tstrSource );
  }
else
  {
  wcsncpy( wstrDestination, tstrSource, cchDestChar );
  wstrDestination[cchDestChar-1] = L'\0';
  }
#else
DXUtil_ConvertAnsiStringToWide( wstrDestination, tstrSource, cchDestChar );
#endif
}

//-----------------------------------------------------------------------------
// Name: CMusicManager::CMusicManager()
// Desc: Constructs the class
//-----------------------------------------------------------------------------
CMusicManager::CMusicManager()
{
m_pLoader       = NULL;
m_pPerformance  = NULL;
   
HRESULT hr = CoInitialize(NULL);
m_bCleanupCOM = SUCCEEDED(hr);
}

//-----------------------------------------------------------------------------
// Name: CMusicManager::~CMusicManager()
// Desc: Destroys the class
//-----------------------------------------------------------------------------
CMusicManager::~CMusicManager()
{
SAFE_RELEASE( m_pLoader ); 

if(m_pPerformance)
  {
  m_pPerformance->Stop( NULL, NULL, 0, 0 );
  m_pPerformance->CloseDown();
  SAFE_RELEASE( m_pPerformance );
  }
if(m_bCleanupCOM)CoUninitialize();
}

//-----------------------------------------------------------------------------
// Name: CMusicManager::Initialize()
// Desc: Inits DirectMusic using a standard audio path
//-----------------------------------------------------------------------------
HRESULT CMusicManager::Initialize( HWND hWnd, DWORD dwPChannels, DWORD dwDefaultPathType )
{
HRESULT hr;

if(FAILED(hr = CoCreateInstance(CLSID_DirectMusicLoader,NULL,CLSCTX_INPROC,IID_IDirectMusicLoader8, (void**)&m_pLoader)))return DXTRACE_ERR( TEXT("CoCreateInstance"), hr);
if(FAILED(hr = CoCreateInstance(CLSID_DirectMusicPerformance,NULL,CLSCTX_INPROC,IID_IDirectMusicPerformance8,(void**)&m_pPerformance)))return DXTRACE_ERR(TEXT("CoCreateInstance"),hr);

if(FAILED(hr = m_pPerformance->InitAudio(NULL,NULL,hWnd,dwDefaultPathType,dwPChannels,DMUS_AUDIOF_ALL,NULL)))
  {
  if(hr == DSERR_NODRIVER)
    {
    DXTRACE("Warning: No sound card found\n");
    return hr;
    }
  return DXTRACE_ERR( TEXT("InitAudio"), hr );
  }
return S_OK;
}
//-----------------------------------------------------------------------------
// Name: CMusicSegment::Play()
// Desc: Plays the sound using voice management flags.  Pass in DSBPLAY_LOOPING
//       in the dwFlags to loop the sound
//-----------------------------------------------------------------------------
HRESULT CMusicSegment::Play( DWORD dwFlags, IDirectMusicAudioPath8* pAudioPath )
{
if(m_pSegment == NULL || m_pPerformance == NULL)return CO_E_NOTINITIALIZED;
if(!m_bDownloaded)return E_FAIL;
if(pAudioPath == NULL && m_pEmbeddedAudioPath != NULL)pAudioPath = m_pEmbeddedAudioPath;
return m_pPerformance->PlaySegmentEx(m_pSegment,0,NULL,dwFlags,0,0,NULL,pAudioPath);
}
//-----------------------------------------------------------------------------
// Name: CMusicSegment::SetRepeats()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CMusicSegment::SetRepeats( DWORD dwRepeats )
{
if(m_pSegment == NULL)return CO_E_NOTINITIALIZED;
return m_pSegment->SetRepeats(dwRepeats);
}
//-----------------------------------------------------------------------------
// Name: CMusicManager::CreateSegmentFromFile()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CMusicManager::CreateSegmentFromFile(CMusicSegment** ppSegment, 
                                              TCHAR* strFileName, 
                                              BOOL bDownloadNow,
                                              BOOL bIsMidiFile)
{
HRESULT               hr;
IDirectMusicSegment8* pSegment = NULL;
WCHAR wstrFileName[MAX_PATH]; // DMusic only takes wide strings
DXUtil_ConvertGenericStringToWide(wstrFileName,strFileName);

if(FAILED(hr = m_pLoader->LoadObjectFromFile(CLSID_DirectMusicSegment,IID_IDirectMusicSegment8,wstrFileName,(LPVOID*)&pSegment)))
  {
  if(hr == DMUS_E_LOADER_FAILEDOPEN)return hr;
  return DXTRACE_ERR(TEXT("LoadObjectFromFile"),hr);
  }
*ppSegment = new CMusicSegment(m_pPerformance,m_pLoader,pSegment);
if(!*ppSegment)return E_OUTOFMEMORY;

if(bIsMidiFile)
  {
  if(FAILED(hr = pSegment->SetParam(GUID_StandardMIDIFile,0xFFFFFFFF,0,0,NULL)))return DXTRACE_ERR(TEXT("SetParam"),hr);
  }
if(bDownloadNow)
  {
  if(FAILED(hr = (*ppSegment)->Download()))return DXTRACE_ERR(TEXT("Download"),hr);
  }
return S_OK;
}
//-----------------------------------------------------------------------------
// Name: CMusicSegment::Download()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CMusicSegment::Download( IDirectMusicAudioPath8* pAudioPath )
{
HRESULT hr;
if(m_pSegment == NULL)return CO_E_NOTINITIALIZED;

if(pAudioPath == NULL)
  {
  if(m_pEmbeddedAudioPath)hr = m_pSegment->Download(m_pEmbeddedAudioPath);
  else hr = m_pSegment->Download( m_pPerformance );
  }
else
  {
  hr = m_pSegment->Download( pAudioPath );
  }
if(SUCCEEDED(hr))m_bDownloaded = TRUE;

return hr;
}
//-----------------------------------------------------------------------------
// Name: CMusicSegment::CMusicSegment()
// Desc: Constructs the class
//-----------------------------------------------------------------------------
CMusicSegment::CMusicSegment( IDirectMusicPerformance8* pPerformance, 
                              IDirectMusicLoader8*      pLoader,
                              IDirectMusicSegment8*     pSegment )
{
m_pPerformance          = pPerformance;
m_pLoader               = pLoader;
m_pSegment              = pSegment;
m_pEmbeddedAudioPath    = NULL;
m_bDownloaded           = FALSE;
    
IUnknown* pConfig = NULL;
if(SUCCEEDED(m_pSegment->GetAudioPathConfig(&pConfig)))
  {
  m_pPerformance->CreateAudioPath(pConfig,TRUE,&m_pEmbeddedAudioPath);
  SAFE_RELEASE(pConfig);
  } 
}
//-----------------------------------------------------------------------------
// Name: CMusicSegment::~CMusicSegment()
// Desc: Destroys the class
//-----------------------------------------------------------------------------
CMusicSegment::~CMusicSegment()
{
if(m_pSegment)
  {
  if(m_pLoader)m_pLoader->ReleaseObjectByUnknown( m_pSegment );
  if(m_bDownloaded)
    {
    if(m_pEmbeddedAudioPath)m_pSegment->Unload(m_pEmbeddedAudioPath);
    else m_pSegment->Unload( m_pPerformance );
    }
  SAFE_RELEASE(m_pEmbeddedAudioPath); 
  SAFE_RELEASE(m_pSegment); 
  }
m_pPerformance = NULL;
}
*/