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
#include "Factory_Scroll.h"
#include "BassItems.h"

namespace wiz{
	namespace bomberobject{

const	float	SCALE_RATE	=	1.4f;

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
Title_Select::Title_Select(const LPDIRECT3DDEVICE9 pD3DDevice,const LPDIRECT3DTEXTURE9 pTexture,const DWORD next,
		const D3DXVECTOR3 &vScale,const D3DXVECTOR3 &vRot,const D3DXVECTOR3 &vPos,
		const RECT *pRect,const D3DXVECTOR3 &vCenter,const D3DXVECTOR3 &vOffsetPos,const Color color)
:SpriteObject( pD3DDevice, pTexture, vScale, vRot, vPos, pRect, vCenter, vOffsetPos, color )
,m_vPos( vPos )
,m_dNext( next )
,m_pSound( NULL )
,m_iTime( 0 )
,m_bPush( false )
,m_bPushRock( false )
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
	if( m_pSound == NULL )
		m_pSound = (Sound*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(Sound));
  //�}�E�X�p�f�[�^*************************
	Point MousePos ;
	GetCursorPos( &MousePos ) ;
	ScreenToClient( g_hWnd , &MousePos) ;
  //*****************************************
	if( (MousePos.x > m_vPos.x && MousePos.x < ( m_vPos.x + (m_pRect->right*SCALE_RATE) )) 
		&& (MousePos.y > m_vPos.y && MousePos.y < ( m_vPos.y + (m_pRect->bottom*SCALE_RATE) )) ){
		if( g_bMouseLB/* || g_bMouseRB*/ ){
			if( m_bPushRock ){
				if( !m_bPush ){
					//if( m_pSound != NULL )
						m_pSound->SearchWaveAndPlay( RCTEXT_SOUND_SE_ENTER );
				}
				m_bPush		= true;
				m_bPushRock	= false;
			}
		}
		else m_bPushRock	= true;
			m_Color	= 0xFF88FFFF;
			if( !m_bSelect ){
				m_bSelect = true;
				m_pSound->SearchWaveAndPlay( RCTEXT_SOUND_SE_SELECT );
			}
			
		
	}
	else{
		m_Color	= 0xFF8888FF;
		m_bSelect = false;

		if( g_bMouseLB )	m_bPushRock	= false;
		else				m_bPushRock	= true;
	}
	if( m_bPush ){
		m_iTime++;
		if( m_iTime > 30 ){
			//�I�΂ꂽ��ʂւƂ�
			i_UpdatePacket.pCommand->m_Command	= m_dNext;
			m_bPush = false ;
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
		



	 

		 Factory_Scroll		Ffac( fpac );
		
		
		
		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, /*L"Lightning.tga"*/L"Title_Name005_02.tga" ),
				D3DXVECTOR3(SCALE_RATE,SCALE_RATE,0.0f),
				g_vZero,
				D3DXVECTOR3( 165.0f, 40.0f, 0.0f ),
				//D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
				NULL,
				g_vZero,
				g_vZero,
				0xFF00FFFF
				)
		);
				fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, /*L"Lightning.tga"*/L"Title_Name005_01.tga" ),
				D3DXVECTOR3(SCALE_RATE,SCALE_RATE,0.0f),
				g_vZero,
				D3DXVECTOR3( 165.0f, 40.0f, 0.0f ),
				//D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
				NULL,
				g_vZero,
				g_vZero,
				0xFFFF8800
				)
		);

		//START
		fpac->m_pVec->push_back(
			new Title_Select(
					fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Title_Start.tga" ),
					GM_OPENSTAGE_PLAY,
					D3DXVECTOR3(SCALE_RATE,SCALE_RATE,0.0f),
					g_vZero,
					D3DXVECTOR3( 150.0f, 421.0f, 0.0f ),
					Rect( 0, 0, 168, 42 ),
					g_vZero,
					g_vZero,
					0xFFFFFFFF
				)
		);

		//EXIT
		fpac->m_pVec->push_back(
			new Title_Select(
					fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Title_Exit.tga" ),
					GM_EXIT,
					D3DXVECTOR3(SCALE_RATE,SCALE_RATE,0.0f),
					g_vZero,
					D3DXVECTOR3( 660.0f, 420.0f, 0.0f ),
					Rect( 0, 0, 126, 42 ),
					g_vZero,
					g_vZero,
					0xFFFFFFFF
				)
		);

		Sound* pSound = NULL;
		fpac->m_pVec->push_back(
			pSound = new Sound( 
				RCTEXT_SOUND_WAVEBANK,
				RCTEXT_SOUND_SOUNDBANK,
				OBJID_SYS_SOUND
			)
		);
		pSound->SearchSoundAndPlay( RCTEXT_SOUND_BGM_TITLE );

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
//end of namespace bomberobject.
}
//end of namespace wiz.
