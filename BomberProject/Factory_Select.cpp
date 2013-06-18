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
//                                 NORMAL                                      //
/////////////////////////////////////////////////////////////////////////////////
		//��
		fpac->AddButton(
			new ButtonSprite(
				fpac->pD3DDevice,	
				fpac->AddTexture(L"NORMAL002.tga"),
				g_vOne,
				g_vZero,
				D3DXVECTOR3(404.5f, 150.0f, 0.0f),
				Rect(0,0,215,26),
				g_vZero,
				g_vZero,
				0xFF00AA55,
				0xFF008833,
				RCTEXT_SOUND_SE_SELECT,
				RCTEXT_SOUND_SE_ENTER,
				Command( GM_OPENSTAGE_LOAD_PLAY, 3, 0 ),
				0
			)
		);
		//��
		fpac->AddButton(
			new ButtonSprite(
				fpac->pD3DDevice,	
				fpac->AddTexture(L"NORMAL001.tga"),
				g_vOne,
				g_vZero,
				D3DXVECTOR3(404.5f, 150.0f, 0.0f),
				Rect(0,0,215,26),
				g_vZero,
				g_vZero,
				0xFF00FFFF,
				0xFF0000DD,
				RCTEXT_SOUND_SE_SELECT,
				RCTEXT_SOUND_SE_ENTER,
				Command( GM_OPENSTAGE_LOAD_PLAY, 3, 0 ),
				1
			)
		);
/////////////////////////////////////////////////////////////////////////////////
//                                  HARD                                       //
/////////////////////////////////////////////////////////////////////////////////
		//��
		fpac->AddButton(
			new ButtonSprite(
				fpac->pD3DDevice,	
				fpac->AddTexture(L"HARD002.tga"),
				g_vOne,
				g_vZero,
				D3DXVECTOR3(440.0f, 300.0f, 0.0f),
				Rect(0,0,144,26),
				g_vZero,
				g_vZero,
				0xFF00AA55,
				0xFF008833,
				RCTEXT_SOUND_SE_SELECT,
				RCTEXT_SOUND_SE_ENTER,
				Command( GM_OPENSTAGE_LOAD_PLAY, 4, 0 ),
				2
			)
		);
		//�I�����W
		fpac->AddButton(
			new ButtonSprite(
				fpac->pD3DDevice,	
				fpac->AddTexture(L"HARD001.tga"),
				g_vOne,
				g_vZero,
				D3DXVECTOR3(440.0f, 300.0f, 0.0f),
				Rect(0,0,144,26),
				g_vZero,
				g_vZero,
				0xFFFFCC00,
				0xFFDD3300,
				RCTEXT_SOUND_SE_SELECT,
				RCTEXT_SOUND_SE_ENTER,
				Command( GM_OPENSTAGE_LOAD_PLAY, 4, 0 ),
				3
			)
		);
/////////////////////////////////////////////////////////////////////////////////
//                                 EXTRA                                       //
/////////////////////////////////////////////////////////////////////////////////
		//��
		fpac->AddButton(
			new ButtonSprite(
				fpac->pD3DDevice,	
				fpac->AddTexture(L"EXTRA002.tga"),
				g_vOne,
				g_vZero,
				D3DXVECTOR3(422.5f, 450.0f, 0.0f),
				Rect(0,0,179,26),
				g_vZero,
				g_vZero,
				0xFF00AA55,
				0xFF008833,
				RCTEXT_SOUND_SE_SELECT,
				RCTEXT_SOUND_SE_ENTER,
				Command( GM_OPENSTAGE_LOAD_PLAY, 5, 0 ),
				4
			)
		);
		//��
		fpac->AddButton(
			new ButtonSprite(
				fpac->pD3DDevice,	
				fpac->AddTexture(L"EXTRA001.tga"),
				g_vOne,
				g_vZero,
				D3DXVECTOR3(422.5f, 450.0f, 0.0f),
				Rect(0,0,179,26),
				g_vZero,
				g_vZero,
				0xFFFF5555,
				0xFF880000,
				RCTEXT_SOUND_SE_SELECT,
				RCTEXT_SOUND_SE_ENTER,
				Command( GM_OPENSTAGE_LOAD_PLAY, 5, 0 ),
				5
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