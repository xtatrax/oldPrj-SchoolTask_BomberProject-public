////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Load.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F���[�h�t�@�N�g���[
//					��
//	namespace wiz;
//		class Load ;
//		class Factory_Load ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Load.h"
#include "BassItems.h"

namespace wiz{
	namespace bomberobject{

/************************************************************************
Load ��`��
************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FLoad(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,DWORD next,
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
//// �S����     �F������
//// ���l       �F
////            �F
////
Load::Load(const LPDIRECT3DDEVICE9 pD3DDevice,const LPDIRECT3DTEXTURE9 pTexture,
		const D3DXVECTOR3 &vScale,const D3DXVECTOR3 &vRot,const D3DXVECTOR3 &vPos,
		const RECT *pRect, const D3DXVECTOR3 &vCenter,const D3DXVECTOR3 &vOffsetPos,const Color color)
:SpriteObject( pD3DDevice, pTexture, vScale, vRot, vPos, pRect, vCenter, vOffsetPos, color )
,m_vPos( vPos )
,m_pSound( NULL )
,m_iTime( 0 )
,m_fRate( 1.0f )
,m_iPtn( 0 )
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
//// �֐���     �Fvoid Load::Draw( DrawPacket& i_DrawPacket)
//// �J�e�S��   �F�֐�
//// �p�r       �F�X�v���C�g��`��
//// ����       �FDrawPacket& i_DrawPacket    //�������̃f�[�^
//// �ߒl       �F�Ȃ�
//// �S����     �F������
//// ���l       �F
////            �F
////
void Load::Draw(DrawPacket& i_DrawPacket)
{
	//	: �`��͐e�N���X�ɔC����
	SpriteObject::Draw(i_DrawPacket);
};

/////////////////// ////////////////////
//// �֐���     �Fvoid Load::Update( UpdatePacket& i_UpdatePacket)
//// �J�e�S��   �F�֐�
//// �p�r       �F�f�[�^�̍X�V
//// ����       �FUpdatePacket& i_UpdatePacket    //�������̃f�[�^
//// �ߒl       �F�Ȃ�
//// �S����     �F������
//// ���l       �F
////            �F
////
void Load::Update(UpdatePacket& i_UpdatePacket)
{
	m_pRect->top	= m_iPtn	*128;
	m_pRect->bottom	= (m_iPtn+1)*128;

	if( m_iTime%20 == 0 )
	m_iPtn++;
	m_iPtn	%= 4;

	m_iTime++;
	if( m_iTime > 240 )
		i_UpdatePacket.pCommand->m_Command	= GM_OPENSTAGE_PLAY;
};

/**************************************************************************
 Factory_Load ��`��
****************************************************************************/
/**************************************************************************
 Factory_Load::Factory_Load(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Load::Factory_Load(FactoryPacket* fpac){
	try{
		
		fpac->m_pVec->push_back(
			new	Load(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"NOW_LOADING3.png" ),
				D3DXVECTOR3(0.5f,0.5f,0.0f),
				g_vZero,
				D3DXVECTOR3( 300.0f, 300.0f, 0.0f ),
				Rect( 0, 0, 1024, 128 ),
				g_vZero,
				g_vZero,
				0xFFFFFFFF
			)
		);


		//Sound* pSound = NULL;
		//fpac->m_pVec->push_back(
		//	pSound = new Sound( 
		//		RCTEXT_SOUND_WAVEBANK,
		//		RCTEXT_SOUND_SOUNDBANK,
		//		OBJID_SYS_SOUND
		//	)
		//);
		//pSound->SearchSoundAndPlay( RCTEXT_SOUND_BGM_TITLE );

	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 Factory_Load::~Factory_Load();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Load::~Factory_Load(){
    //�Ȃɂ����Ȃ�
}

}
//end of namespace bomberobject.
}
//end of namespace wiz.
