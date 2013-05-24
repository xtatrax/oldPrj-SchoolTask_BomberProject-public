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
/**************************************************************************
 Sound ��`��
****************************************************************************/

/**************************************************************************
 void Sound::CreateInctance();
 �p�r: �C���X�^���X�̍\�z
 �߂�l: �Ȃ��B�i��O��throw�����j
***************************************************************************/
void Sound::CreateInctance(){
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
				L"Sound::CreateInctance()"
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
				L"Sound::CreateInctance()"
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
									L"Sound::CreateInctance()"
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
					L"Sound::CreateInctance()"
					);
			}
		}
		//Sound�o���N�̍쐬
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
									L"Sound�o���N�n���h���������Ɏ��s���܂����B",
									L"Sound::CreateInctance()"
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
					//				L"Sound�o���N�n���h���������Ɏ��s���܂����B",
					//				L"Sound::CreateInctance()"
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
					L"Sound::CreateInctance()"
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
 Sound::Sound(
 const wchar_t* pWavBankFileName,		//Wav�o���N�̃t�@�C����
 const wchar_t* pSoundBankFileName = 0,	//Sound�o���N�̃t�@�C�����i�I�v�V�����j
 XACT_NOTIFICATION_CALLBACK fnNotificationCallback = 0	//�ʒm�p�R�[���o�b�N�֐��̃|�C���^
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Sound::Sound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,wiz::OBJID id,
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
				L"Sound::Sound()"
				);
		}
		m_WavBankFileName = pWavBankFileName;
		if( pSoundBankFileName ){
			m_SoundBankFileName = pSoundBankFileName;
		}
		CreateInctance();
	}
	catch(...){
		ReleaseObj();
		//��throw
		throw;
	}
}
/**************************************************************************
 virtual Sound::~Sound();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Sound::~Sound(){
	ReleaseObj();
}

/**************************************************************************
	virtual void Sound::ReleaseObj();
 �p�r: �f�o�C�X�r���ɂ�郊�\�[�X�̊J���i���z�֐��j
 �߂�l: �Ȃ��B
 ���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
***************************************************************************/
void Sound::ReleaseObj(){
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
	virtual void Sound::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
 �p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
 �߂�l: �Ȃ��B
 ���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
***************************************************************************/
void Sound::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//�T�E���h�͕\���f�o�C�X�Ɋ֌W�Ȃ��̂ŉ������Ȃ�
}

/**************************************************************************
 virtual void Sound::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Context& Data					//���[�U�[�f�[�^
 );
 �p�r: �I�u�W�F�N�g��`��i�������z�֐��j���̃N���X�ł͉������Ȃ�
 �߂�l: �Ȃ��B
***************************************************************************/
void Sound::Draw( DrawPacket& i_DrawPacket ){
	//�T�E���h�G���W���ɍ�Ǝ��Ԃ�^����
	m_pEngine->DoWork();
}
/**************************************************************************
 OneSound ��`��
****************************************************************************/
OneSound::OneSound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,PCSTR pSoundName,wiz::OBJID id)
:Sound(pWavBankFileName, pSoundBankFileName, id )
{
	if(m_pEngine && m_pWaveBank && m_pSoundBank){
		i_iSoundNum = m_pWaveBank->GetWaveIndex( pSoundName );
	}
}
OneSound::OneSound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,const XACTINDEX iSoundNum,wiz::OBJID id)
:Sound(pWavBankFileName, pSoundBankFileName, id )
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

		fpac->m_pVec->push_back(
			new OneSound(
				L"media/Sound/MagneticaWave.xwb",
				L"media/Sound/MagneticaSound.xsb",
				"bgm001",
				OBJID_SOUND_BGM_TITLE
			)
		);
		fpac->m_pVec->push_back(
			new OneSound(
				L"media/Sound/MagneticaWave.xwb",
				L"media/Sound/MagneticaSound.xsb",
				"bgm002",
				OBJID_SOUND_BGM_PLAY
			)
		);

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


//end of namespace wiz.
