////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Sound.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F�A�C�e���t�@�N�g���[
//					��
//	namespace wiz;
//		class GoalObject;
//		class Factory_Sound ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"

namespace wiz{
namespace system{

/**************************************************************************
 class Sound: public Object;
 �p�r: �T�E���h�N���X
****************************************************************************/
class _Sound : public Object{
protected:
	class MyQue{
		XACTINDEX CueNum	;
		IXACT3Cue *m_pCue	;
	};

protected:
	IXACT3Engine* m_pEngine;
	XACT_NOTIFICATION_CALLBACK m_fnNotificationCallback;
	//�ʒm�p�̃R�[���o�b�N�֐�
	IXACT3WaveBank* m_pWaveBank;
	IXACT3SoundBank* m_pSoundBank;
	VOID* m_pbWaveBank; // Handle to wave bank data.  Its memory mapped so call UnmapViewOfFile() upon cleanup to release file
	VOID* m_pbSoundBank; // Pointer to sound bank data.  Call delete on it when the sound bank is destroyed
	wstring m_WavBankFileName;
	wstring m_SoundBankFileName;


	IXACT3Cue *m_pCue[0xFF];

/**************************************************************************
 void CreateInctance();
 �p�r: �C���X�^���X�̍\�z
 �߂�l: �Ȃ��B�i��O��throw�����j
***************************************************************************/
	void CreateInctance();
public:
/**************************************************************************
 Sound(
 const wchar_t* pWavBankFileName,		//Wav�o���N�̃t�@�C����
 const wchar_t* pSoundBankFileName = 0,	//Sound�o���N�̃t�@�C�����i�I�v�V�����j
 XACT_NOTIFICATION_CALLBACK fnNotificationCallback = 0	//�ʒm�p�R�[���o�b�N�֐��̃|�C���^
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	_Sound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName ,wiz::OBJID id,
		XACT_NOTIFICATION_CALLBACK fnNotificationCallback = 0);
/**************************************************************************
 virtual ~Sound();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	virtual ~_Sound();
/**************************************************************************
	virtual void ReleaseObj();
 �p�r: �f�o�C�X�r���ɂ�郊�\�[�X�̊J���i���z�֐��j
 �߂�l: �Ȃ��B
 ���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
***************************************************************************/
	virtual void ReleaseObj();
/**************************************************************************
	virtual void ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
 �p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
 �߂�l: �Ȃ��B
 ���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Context& Data					//���[�U�[�f�[�^
 );
 �p�r: �I�u�W�F�N�g��`��i�������z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw( DrawPacket& i_DrawPacket );
};
namespace Avoidance{
class OneSound : public _Sound{
	XACTINDEX i_iSoundNum ;
public:
	OneSound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,PCSTR pSoundName,wiz::OBJID id);
	OneSound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,const XACTINDEX iSoundNum,wiz::OBJID id);
	void PlaySound(BYTE count = 0);

};
}

class Sound : public _Sound{

	typedef  map< PCSTR , XACTINDEX > SOUNDLISTMAP;
	SOUNDLISTMAP  m_SoundMap ;
	SOUNDLISTMAP  m_WaveMap ;
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
	bool SearchSoundMap(PCSTR  pSoundName , XACTINDEX& o_SoundNum);

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
	bool SearchSoundBank(PCSTR  pSoundName , XACTINDEX& o_SoundNum);

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
	bool SearchWaveMap( PCSTR  pWaveName , XACTINDEX& o_WaveNum );

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
	bool SearchWaveBank(PCSTR  pWaveName , XACTINDEX& o_WaveNum);


public:

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
	Sound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName ,wiz::OBJID id);
	
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
	void Update( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// �p�r       �F
	//// �J�e�S��   �F
	//// �p�r       �F
	//// ����       �F
	//// �ߒl       �F
	//// �S����     �F���� �O
	//// ���l       �FBGM���Đ�����Ƃ��ɂ͂�����𗘗p���Ă�������
	////            �F
	////
	bool SearchSoundAndPlay(PCSTR pSoundName);
	
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
	bool SearchWaveAndPlay(PCSTR pSoundName, BYTE count = 0);

	void SearchSoundAndStop(PCSTR pSoundName);
	void SearchWaveAndStop(PCSTR pSoundName);
	void SoundStop(PCSTR pSoundName);

};

/**************************************************************************
class Factory_Sound;

�p�r�@�F���C���H��N���X
�S���ҁF������
****************************************************************************/
class Factory_Sound{
public:
/**************************************************************************
 Factory_Sound(FactoryPacket* fpac);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_Sound(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Factory_Sound();
};

}
//end of namespace system.
//using namespace system;
}
//end of namespace wiz.
