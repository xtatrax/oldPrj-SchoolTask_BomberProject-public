////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Title.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F�^�C�g���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Title ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Title.h"
#include "BassItems.h"

namespace wiz{
/************************************************************************
Title_Select ��`��
************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FTitle_Select(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,DWORD next,
////            �F    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect,
////            �F    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�X�v���C�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  LPDIRECT3DTEXTURE9 pTexture     // �\��t�������e�N�X�`��
////            �F  DWORD next                      // ���̉��
////            �F  D3DXVECTOR3 &vScale             // �傫��
////            �F  D3DXVECTOR3 &vRot               // �O����]
////            �F  D3DXVECTOR3 &vPos               // �ݒu���W
////            �F  RECT* pRect                     // �`�悵�����͈�(NULL�őS�̂�`��)
////            �F  D3DXVECTOR3& vCenter            // ���S
////            �F  D3DXVECTOR3& vOffsetPos         // �I�t�Z�b�g���W
////            �F  Color color = 0xFFFFFFFF        // �F
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
Title_Select::Title_Select(LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture, DWORD next,
		D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
		RECT *pRect, D3DXVECTOR3 &vCenter, D3DXVECTOR3 &vOffsetPos, Color color)
:SpriteObject( pD3DDevice, pTexture, vScale, vRot, vPos, pRect, vCenter, vOffsetPos, color )
,m_vPos( vPos )
,m_dNext( next )
{
	try{
		//	: �����}�g���b�N�X���v�Z
		D3DXMATRIX mScale,mRot,mPos;
		D3DXMatrixScaling(&mScale,vScale.x,vScale.y,vScale.z);
		D3DXMatrixRotationYawPitchRoll(&mRot,vRot.y,vRot.x,vRot.z);
		D3DXMatrixTranslation(&mPos,vPos.x,vPos.y,vPos.z);
		m_mMatrix = mScale * mRot * mPos ;
	}
	catch(...){
		SafeRelease(m_pSprite);
		//�ăX���[
		throw;
	}
};

/////////////////// ////////////////////
//// �֐���     �Fvoid Title_Select::Draw( DrawPacket& i_DrawPacket)
//// �J�e�S��   �F�֐�
//// �p�r       �F�X�v���C�g��`��
//// ����       �FDrawPacket& i_DrawPacket    //�������̃f�[�^
//// �ߒl       �F�Ȃ�
//// �S����     �F������
//// ���l       �F
////            �F
////
void Title_Select::Draw(DrawPacket& i_DrawPacket)
{
	//	: �`��͐e�N���X�ɔC����
	SpriteObject::Draw(i_DrawPacket);
};

/////////////////// ////////////////////
//// �֐���     �Fvoid Title_Select::Update( UpdatePacket& i_UpdatePacket)
//// �J�e�S��   �F�֐�
//// �p�r       �F�f�[�^�̍X�V
//// ����       �FUpdatePacket& i_UpdatePacket    //�������̃f�[�^
//// �ߒl       �F�Ȃ�
//// �S����     �F������
//// ���l       �F
////            �F
////
void Title_Select::Update(UpdatePacket& i_UpdatePacket)
{
  //�}�E�X�p�f�[�^*************************
	Point MousePos ;
	GetCursorPos( &MousePos ) ;
	ScreenToClient( g_hWnd , &MousePos) ;
  //*****************************************
	if( g_bMouseLB/* || g_bMouseRB*/ ){
		if( (MousePos.x > m_vPos.x && MousePos.x < ( m_vPos.x + m_pRect->right )) 
			&& (MousePos.y > m_vPos.y && MousePos.y < ( m_vPos.y + m_pRect->bottom )) ){
			//�I�΂ꂽ��ʂւƂ�
			i_UpdatePacket.pCommand->m_Command	= m_dNext;
		}
	}
};

/**************************************************************************
 Factory_Title ��`��
****************************************************************************/
/**************************************************************************
 Factory_Title::Factory_Title(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Title::Factory_Title(FactoryPacket* fpac){
	try{
		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, /*L"Lightning.tga"*/L"title.png" ),
				g_vOne,
				g_vZero,
				D3DXVECTOR3( 240.0f, 100.0f, 0.0f ),
				//D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
				NULL,
				g_vZero,
				g_vZero,
				0xFFFFFFFF
				)
		);

		//START
		fpac->m_pVec->push_back(
			new Title_Select(
					fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Title_Start.png" ),
					GM_OPENSTAGE_PLAY,
					g_vOne,
					g_vZero,
					D3DXVECTOR3( 300.0f, 250.0f, 0.0f ),
					Rect( 0, 0, 340, 50 ),
					g_vZero,
					g_vZero,
					0xFFFFFFFF
				)
		);

		//EXIT
		fpac->m_pVec->push_back(
			new Title_Select(
					fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Title_Exit.png" ),
					GM_EXIT,
					g_vOne,
					g_vZero,
					D3DXVECTOR3( 350.0f, 400.0f, 0.0f ),
					Rect( 0, 0, 225, 50 ),
					g_vZero,
					g_vZero,
					0xFFFFFFFF
				)
		);
	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 Factory_Title::~Factory_Title();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Title::~Factory_Title(){
    //�Ȃɂ����Ȃ�
}

}
//end of namespace wiz.
