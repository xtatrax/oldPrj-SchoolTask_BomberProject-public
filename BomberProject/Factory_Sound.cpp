////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Sound.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F�A�C�e���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Sound ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Sound.h"
#include "BassItems.h"

namespace wiz{
namespace system{

/**************************************************************************
 _Sound ��`��
****************************************************************************/

/**************************************************************************
 void _Sound::CreateInctance();
 �p�r: �C���X�^���X�̍\�z
 �߂�l: �Ȃ��B�i��O��throw�����j
***************************************************************************/
void _Sound::CreateInctance(){
	ReleaseObj();
	try{
		HANDLE hFile;
		DWORD dwFileSize;
		HANDLE hMapFile;
		//��������new���ăf�[�^�쐬����ꍇ�ȉ��̕ϐ����K�v
		//DWORD dwBytesRead;

		//�f�o�b�O���͈ȉ���true�ɂ���
		bool bDebugMode = false;
		DWORD dwCreationFlags = 0;
		if( bDebugMode ) dwCreationFlags |= XACT_FLAG_API_DEBUG_MODE;
		if(FAILED(XACT3CreateEngine( dwCreationFlags, &m_pEngine ))){
			// ���������s
			throw BaseException(
				L"�T�E���h�G���W���\�z�Ɏ��s���܂����B",
				L"_Sound::CreateInctance()"
				);
		}
		// Initialize & create the XACT runtime 
		XACT_RUNTIME_PARAMETERS xrParams = {0};
		//�R�[���o�b�N�֐��̎w��
		if(m_fnNotificationCallback){
			xrParams.fnNotificationCallback = m_fnNotificationCallback;
		}
		xrParams.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
		if(FAILED(m_pEngine->Initialize( &xrParams ))){
			// ���������s
			throw BaseException(
				L"�T�E���h�G���W���������Ɏ��s���܂����B",
				L"_Sound::CreateInctance()"
				);
		}
		//Wav�o���N�̍쐬
		if(m_WavBankFileName != L""){
			hFile = CreateFile(m_WavBankFileName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
			if( hFile != INVALID_HANDLE_VALUE ){
				dwFileSize = GetFileSize( hFile, NULL );
				if( dwFileSize != -1 ){
					hMapFile = CreateFileMapping( hFile, NULL, PAGE_READONLY, 0, dwFileSize, NULL );
					if( hMapFile ){
						m_pbWaveBank = MapViewOfFile( hMapFile, FILE_MAP_READ, 0, 0, 0 );
						if(m_pbWaveBank){
							if(FAILED(m_pEngine->CreateInMemoryWaveBank(m_pbWaveBank, dwFileSize, 0,
								0, &m_pWaveBank))){
								CloseHandle( hMapFile );
								CloseHandle( hFile );
								// ���������s
								throw BaseException(
									L"Wav�o���N�n���h���������Ɏ��s���܂����B",
									L"_Sound::CreateInctance()"
									);
							}
						}
						CloseHandle( hMapFile ); // pbWaveBank maintains a handle on the file so close this unneeded handle
					}
				}
				CloseHandle( hFile ); // pbWaveBank maintains a handle on the file so close this unneeded handle
			}
			else{
				// ���������s
				throw BaseException(
					L"�E�F�u�o���N�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B",
					L"_Sound::CreateInctance()"
					);
			}
		}
		//_Sound�o���N�̍쐬
		if(m_SoundBankFileName != L""){
			hFile = CreateFile(m_SoundBankFileName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
			if( hFile != INVALID_HANDLE_VALUE )
			{
				dwFileSize = GetFileSize( hFile, NULL );
				if( dwFileSize != -1 )
				{

					hMapFile = CreateFileMapping( hFile, NULL, PAGE_READONLY, 0, dwFileSize, NULL );
					if( hMapFile ){
						m_pbSoundBank = MapViewOfFile( hMapFile, FILE_MAP_READ, 0, 0, 0 );
						if(m_pbSoundBank){
							if(FAILED(m_pEngine->CreateSoundBank(m_pbSoundBank, dwFileSize, 0,
								0, &m_pSoundBank))){
								CloseHandle( hMapFile );
								CloseHandle( hFile );
								// ���������s
								throw BaseException(
									L"_Sound�o���N�n���h���������Ɏ��s���܂����B",
									L"_Sound::CreateInctance()"
									);
							}
						}
						CloseHandle( hMapFile ); // pbWaveBank maintains a handle on the file so close this unneeded handle
					}

					// Allocate the data here and free the data when recieving the sound bank destroyed notification
					//�ȉ��̂悤�Ƀ�������new���č쐬���邱�Ƃ��ł���iWavBank�����l�j
					//m_pbSoundBank = new BYTE[dwFileSize];
					//if(m_pbSoundBank)
					//{
					//	if( 0 != ReadFile( hFile,m_pbSoundBank, dwFileSize, &dwBytesRead, NULL ) )
					//	{
					//		if(FAILED(m_pEngine->CreateSoundBank(m_pbSoundBank, dwFileSize, 0,
					//			0, &m_pSoundBank))){
					//			CloseHandle( hFile );
					//			// ���������s
					//			throw BaseException(
					//				L"_Sound�o���N�n���h���������Ɏ��s���܂����B",
					//				L"_Sound::CreateInctance()"
					//				);

					//		}
					//	}
					//}


				}
				CloseHandle( hFile );
			}
			else{
				// ���������s
				throw BaseException(
					L"�T�E���h�o���N�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B",
					L"_Sound::CreateInctance()"
					);
			}
		}
	}
	catch(...){
		ReleaseObj();
		//��throw
		throw;
	}
}


/**************************************************************************
 _Sound::_Sound(
 const wchar_t* pWavBankFileName,		//Wav�o���N�̃t�@�C����
 const wchar_t* pSoundBankFileName = 0,	//_Sound�o���N�̃t�@�C�����i�I�v�V�����j
 XACT_NOTIFICATION_CALLBACK fnNotificationCallback = 0	//�ʒm�p�R�[���o�b�N�֐��̃|�C���^
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
_Sound::_Sound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,wiz::OBJID id,
		XACT_NOTIFICATION_CALLBACK fnNotificationCallback)
:Object( id ),
m_pEngine(0),m_fnNotificationCallback(fnNotificationCallback),
m_pWaveBank(0),m_pSoundBank(0),m_pbWaveBank(0),m_pbSoundBank(0),
m_WavBankFileName(L""),
m_SoundBankFileName(L"")
{
	try{
		if(!pWavBankFileName){
			// ���������s
			throw BaseException(
				L"WAV�o���N�t�@�C�����w�肳��Ă܂���B",
				L"_Sound::_Sound()"
				);
		}
		m_WavBankFileName = pWavBankFileName;
		if( pSoundBankFileName ){
			m_SoundBankFileName = pSoundBankFileName;
		}
		CreateInctance();
	}
	catch(exception& e){
		ReleaseObj();
		::MessageBoxA(
			wiz::DxDevice::m_hWnd,
			e.what(),
			"�G���[",
			MB_OK);
	}
	catch(...){
		ReleaseObj();

		::MessageBoxA(
			NULL,
			"_Sound�Ŗ��m�̃G���[",
			"�G���[",
			MB_OK);
		//��throw
	}
}
/**************************************************************************
 virtual _Sound::~_Sound();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
_Sound::~_Sound(){
	ReleaseObj();
}

/**************************************************************************
 virtual void _Sound::ReleaseObj();
 �p�r: �f�o�C�X�r���ɂ�郊�\�[�X�̊J���i���z�֐��j
 �߂�l: �Ȃ��B
 ���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
***************************************************************************/
void _Sound::ReleaseObj(){
    if(m_pEngine){
        m_pEngine->ShutDown();
		SafeRelease(m_pEngine);
    }
	//new�Ńf�[�^���擾�����ꍇ�͈ȉ��̂悤��delete����
	//SafeDeleteArr(m_pbSoundBank);
	if(m_pbSoundBank){
        UnmapViewOfFile(m_pbSoundBank);
	}
    m_pbSoundBank = 0;
	if(m_pbWaveBank){
        UnmapViewOfFile(m_pbWaveBank);
	}
    m_pbWaveBank = 0;
}

/**************************************************************************
	virtual void _Sound::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
 �p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
 �߂�l: �Ȃ��B
 ���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
***************************************************************************/
void _Sound::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//�T�E���h�͕\���f�o�C�X�Ɋ֌W�Ȃ��̂ŉ������Ȃ�
}

/**************************************************************************
 virtual void _Sound::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Context& Data					//���[�U�[�f�[�^
 );
 �p�r: �I�u�W�F�N�g��`��i�������z�֐��j���̃N���X�ł͉������Ȃ�
 �߂�l: �Ȃ��B
***************************************************************************/
void _Sound::Draw( DrawPacket& i_DrawPacket ){
	//�T�E���h�G���W���ɍ�Ǝ��Ԃ�^����
	m_pEngine && m_pEngine->DoWork();
}

namespace Avoidance{

/**************************************************************************
 OneSound ��`��
****************************************************************************/
OneSound::OneSound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,PCSTR pSoundName,wiz::OBJID id)
:_Sound(pWavBankFileName, pSoundBankFileName, id )
{
	if(m_pEngine && m_pWaveBank && m_pSoundBank){
		i_iSoundNum = m_pWaveBank->GetWaveIndex( pSoundName );
	}
}
OneSound::OneSound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,const XACTINDEX iSoundNum,wiz::OBJID id)
:_Sound(pWavBankFileName, pSoundBankFileName, id )
{
	if(m_pEngine && m_pWaveBank && m_pSoundBank){
		i_iSoundNum = iSoundNum ;
	}
}
void OneSound::PlaySound(BYTE count){
	/*/
	if(m_pWaveBank){
		m_pWaveBank->Play(i_iSoundNum, XACT_FLAG_UNITS_MS,0,count,NULL);
	}
	/*/
	if(m_pSoundBank){
		m_pSoundBank->Play(i_iSoundNum, 0,0 ,NULL );
	}
	//*/
}

}

/**************************************************************************
 Sound ��`��
****************************************************************************/
//-----------//
//	����J   //
//-----------//

/////////////////// ////////////////////
//// �p�r       �Fbool Sound::SearchSoundMap( PCSTR  i_pSoundName , XACTINDEX& o_SoundNum ) ;
//// �J�e�S��   �F�T�[�`���[
//// �p�r       �F�T�E���h�}�b�v����w�肳�ꂽ����T���o��
//// ����       �F  PCSTR         i_pSoundName        //  : [ IN  ]������
////            �F  XACTINDEX&    o_SoundNum          //  : [ OUT ]�������������ԍ�
//// �ߒl       �Ftrue   : ��������
////            �Ffalse  : �o���Ȃ�����
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
bool Sound::SearchSoundMap( PCSTR  pSoundName , XACTINDEX& o_SoundNum ) {
	if( m_SoundMap.count(  pSoundName ) ){	//	: �}�b�v���ɂ��łɓo�^�͂��邩
		o_SoundNum = m_SoundMap[ pSoundName ] ;
		return true ;
	}
	return false ;
}

/////////////////// ////////////////////
//// �p�r       �F
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
bool Sound::SearchSoundBank(PCSTR  pSoundName , XACTINDEX& o_SoundNum){
	//	: �T�E���h�t�@�C�����ɂ͓o�^����Ă��邩
	XACTINDEX SoundNum = m_pSoundBank->GetCueIndex( pSoundName ) ;
	if( SoundNum != XACTINDEX_INVALID ){
		//	: �T�E���h�}�b�v�֓o�^
		m_SoundMap.insert( SOUNDLISTMAP::value_type( pSoundName, SoundNum) );
		o_SoundNum = SoundNum ;
		return true ;

	}
	return false ;
}


/////////////////// ////////////////////
//// �p�r       �F
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
bool Sound::SearchWaveMap( PCSTR  pWaveName , XACTINDEX& o_WaveNum ) {
	if( m_WaveMap.count(  pWaveName ) ){	//	: �}�b�v���ɂ��łɓo�^�͂��邩
		o_WaveNum = m_WaveMap[ pWaveName ] ;
		return true ;
	}
	return false ;
}

/////////////////// ////////////////////
//// �p�r       �F
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
bool Sound::SearchWaveBank(PCSTR  pWaveName , XACTINDEX& o_WaveNum){
	//	: �T�E���h�t�@�C�����ɂ͓o�^����Ă��邩
	XACTINDEX WaveNum = m_pWaveBank->GetWaveIndex( pWaveName ) ;
	if( WaveNum != XACTINDEX_INVALID ){
		//	: �T�E���h�}�b�v�֓o�^
		m_WaveMap.insert( SOUNDLISTMAP::value_type( pWaveName, WaveNum) );
		o_WaveNum = WaveNum ;
		return true ;

	}
	return false ;
}


//-----------//
//	 ���J    //
//-----------//

/////////////////// ////////////////////
//// �p�r       �F
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
Sound::Sound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName ,wiz::OBJID id)
:_Sound(pWavBankFileName, pSoundBankFileName, id )
{
}

/////////////////// ////////////////////
//// �p�r       �F
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
void Sound::Update( UpdatePacket& i_UpdatePacket ){
#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )
	if( GetAsyncKeyState( MYVK_DEBUG_SWITCHING_SOUND ) )
		DxDevice::SwitchingSoundOnOff();
	if( DxDevice::getIsPlaySound() )
		Debugger::DBGSTR::addStrTop( L"[F6]Sound ON\n" );
	else
		Debugger::DBGSTR::addStrTop( L"[F6]Sound OFF\n" );
	
#endif
}

/////////////////// ////////////////////
//// �p�r       �F
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
bool Sound::SearchSoundAndPlay(PCSTR pSoundName){

	//	: �ʂ��->�K�b
	if( this != NULL && DxDevice::getIsPlaySound() && m_pEngine && m_pWaveBank && m_pSoundBank ){
		XACTINDEX SoundNum ;
		if(SearchSoundMap( pSoundName, SoundNum ) || SearchSoundBank( pSoundName, SoundNum ) ){
			m_pSoundBank->Play( SoundNum, 0,0 ,NULL );
			return true ;
		}
	}

	return false ;
}

/////////////////// ////////////////////
//// �p�r       �F
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
bool Sound::SearchWaveAndPlay(PCSTR pWaveName, BYTE count){

	//	: �ʂ��->�K�b
	if( DxDevice::getIsPlaySound() && m_pEngine && m_pWaveBank && m_pSoundBank ){
		XACTINDEX WaveNum ;
		if(SearchWaveMap( pWaveName, WaveNum ) || SearchWaveBank( pWaveName, WaveNum ) ){
			m_pWaveBank->Play( WaveNum, XACT_FLAG_UNITS_MS, 0, count, NULL );
		}
	}

	return false ;
}

void	Sound::SearchSoundAndStop(PCSTR pWaveName){
	if( m_pEngine && m_pWaveBank && m_pSoundBank ){
		XACTINDEX SoundNum ;
		if(SearchSoundMap( pWaveName, SoundNum ) || SearchSoundBank( pWaveName, SoundNum ) ){
			m_pSoundBank->Stop( SoundNum, true );
		}
	}
}

void	Sound::SearchWaveAndStop(PCSTR pWaveName){
	if( m_pEngine && m_pWaveBank && m_pSoundBank ){
		XACTINDEX WaveNum ;
		if(SearchWaveMap( pWaveName, WaveNum ) || SearchWaveBank( pWaveName, WaveNum ) ){
			m_pWaveBank->Stop( WaveNum, true );
		}
	}
}

void	Sound::SoundStop(PCSTR pWaveName){
	if( m_pEngine && m_pWaveBank && m_pSoundBank ){
		XACTINDEX WaveNum ;
		if(SearchWaveMap( pWaveName, WaveNum ) || SearchWaveBank( pWaveName, WaveNum ) ){
			m_pWaveBank->Stop( WaveNum, true );
		}
		XACTINDEX SoundNum ;
		if(SearchSoundMap( pWaveName, SoundNum ) || SearchSoundBank( pWaveName, SoundNum ) ){
			m_pSoundBank->Stop( SoundNum, true );
		}
	}
}

/**************************************************************************
 Factory_Sound ��`��
****************************************************************************/
/**************************************************************************
 Factory_Sound::Factory_Sound(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Sound::Factory_Sound(FactoryPacket* fpac){
	try{
		//	:BGM-TITLE----------:�^�C�g����ʂŗ����BGM

	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 Factory_Sound::~Factory_Sound();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Sound::~Factory_Sound(){
    //�Ȃɂ����Ȃ�
}

}
//end of namespace system.
//using namespace system;
}
//end of namespace wiz.
