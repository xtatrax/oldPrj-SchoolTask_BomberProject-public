////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Select.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Select ;
//
#include "StdAfx.h"
#include "Factory_Select.h"
#include "Factory_Cursor.h"
#include "Factory_CustomButtonA.h"
#include "Factory_SelectInformation.h"

namespace wiz{
namespace bomberobject{


//class TestBehavior : public Behavior{
//public:
//	TestBehavior()
//		:Behavior(OBJID_BEHAVIOR_TEST)
//	{}
//	/////////////////// ////////////////////
//	//// �p�r       �Fvirtual void Update( UpdatePacket& i_UpdatePacket )
//	//// �J�e�S��   �F���z�֐�
//	//// �p�r       �F�I�u�W�F�N�g���X�V
//	//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
//	////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
//	////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
//	////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
//	////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
//	////            �F  ��       Command            pCommand        // �R�}���h
//	//// �ߒl       �F����
//	//// �S����     �F���� �O
//	//// ���l       �F�p���������̂ł��K���Ƃ���`�����Ȃ��Ă��ǂ�
//	////            �F
//	////
//    void Update( UpdatePacket& i_UpdatePacket ){
//		if( Cursor2D::clickLorRButtonWithLock() )
//			(i_UpdatePacket.pCommand->m_Command = GM_CHANGE_PARENTSTAGE) ;
//	};
//};
	
/**************************************************************************
 Factory_Select ��`��
****************************************************************************/
/**************************************************************************
 Factory_Select::Factory_Select(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Select::Factory_Select(FactoryPacket* fpac ){
	try{

/////////////////////////////////////////////////////////////////////////////////
//                           �����p�̃e�N�X�`��                          //
/////////////////////////////////////////////////////////////////////////////////
		fpac->m_pVec->push_back(
			new SelectInformation(
					fpac->pD3DDevice,						//���}�E�X�������̏�ɂ���Ƃ��\������摜
					fpac->AddTexture(L"Select_blue.png"),	//�g�O
					fpac->AddTexture(L"Select_Green.png"),	//NORMAL
					fpac->AddTexture(L"Select_Orenge.png"),	//HARD
					fpac->AddTexture(L"Select_Pink.png"),	//EXTRA
					D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),
					g_vZero,
					D3DXVECTOR3( 50.0f, 50.0f, 0.0f ),
					Rect( 0, 0, 512, 512 ),
					g_vZero,
					g_vZero,
					0xFFFFFFFF
			)
		);
/////////////////////////////////////////////////////////////////////////////////
//                                 NORMAL                                      //
/////////////////////////////////////////////////////////////////////////////////
		fpac->AddButton(
			new CustomButtonA(
				fpac->pD3DDevice,
				fpac->AddTexture(L"NORMAL002.tga"),
				fpac->AddTexture(L"NORMAL001.tga"),
				D3DXVECTOR3( 1.8f,1.8f,0.0f ),
				g_vZero,
				D3DXVECTOR3(980.0f, 300.0f, 0.0f),
				Rect(0,0,220,30),
				Rect(0,0,220,30),
				D3DXVECTOR3( 220.0f,0.0f,0.0f ),
				g_vZero,
				0xFF00AA55,
				0xFF008833,
				0xFF00FFFF,
				0xFF0000DD,
				RCTEXT_SOUND_SE_SELECT,
				RCTEXT_SOUND_SE_ENTER,
				1.0f,
				Command( GM_OPENSTAGE_LOAD_PLAY, 3, 0 ),
				0,
				OBJID_UI_BUTTON_NORMAL
			)
		);
/////////////////////////////////////////////////////////////////////////////////
//                                  HARD                                       //
/////////////////////////////////////////////////////////////////////////////////
		fpac->AddButton(
			new CustomButtonA(
				fpac->pD3DDevice,	
				fpac->AddTexture(L"HARD002.tga"),
				fpac->AddTexture(L"HARD001.tga"),
				D3DXVECTOR3( 1.8f,1.8f,0.0f ),
				g_vZero,
				D3DXVECTOR3(980.0f, 375.0f, 0.0f),
				Rect(0,0,148,30),
				Rect(0,0,148,30),
				D3DXVECTOR3( 148.0f,0.0f,0.0f ),
				g_vZero,
				0xFF00AA55,
				0xFF008833,
				0xFFFFCC00,
				0xFFDD3300,
				RCTEXT_SOUND_SE_SELECT,
				RCTEXT_SOUND_SE_ENTER,
				1.0f,
				Command( GM_OPENSTAGE_LOAD_PLAY, 4, 0 ),
				1,
				OBJID_UI_BUTTON_HARD
			)
		);
/////////////////////////////////////////////////////////////////////////////////
//                                 EXTRA                                       //
/////////////////////////////////////////////////////////////////////////////////
		fpac->AddButton(
			new CustomButtonA(
				fpac->pD3DDevice,	
				fpac->AddTexture(L"EXTRA002.tga"),
				fpac->AddTexture(L"EXTRA001.tga"),
				D3DXVECTOR3( 1.8f,1.8f,0.0f ),
				g_vZero,
				D3DXVECTOR3(900.0f, 450.0f, 0.0f),
				Rect(0,0,179,26),
				Rect(0,0,179,26),
				g_vZero,
				g_vZero,
				0xFF00AA55,
				0xFF008833,
				0xFFFF5555,
				0xFF880000,
				RCTEXT_SOUND_SE_SELECT,
				RCTEXT_SOUND_SE_ENTER,
				1.0f,
				Command( GM_OPENSTAGE_LOAD_PLAY, 5, 0 ),
				2,
				OBJID_UI_BUTTON_EXTRA
			)
		);
		float	fLineLength	= 550.0f;
		float	fPointSize	= 0.25f;
		Factory_Cursor	MCfac( fpac, fLineLength, fPointSize )  ;
	}
	catch(LoaderException& e){
		throw LoaderException(
				e.what_w(),
				L"��Factory_Select::Factory_Select()"
				);
	}
	catch(...){
		//��throw
		throw;
	}
}
/**************************************************************************
 Factory_Select::~Factory_Select();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Select::~Factory_Select(){
	//�Ȃɂ����Ȃ�
}


}


//end of namespace bomberobject.
}
//end of namespace wiz.