////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Continue.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F������
//	�����ް��Ɣ��l	�F�R���e�j���[
//					��
//	namespace wiz;
//		class Reply ;
//		class Dead ;
//		class Continue ;
//

//////////
//	: ��{�̃C���N���[�h
#include "StdAfx.h"
#include "Factory_Continue.h"

//	: ��{�̃C���N���[�h
//////////
//////////
//	: �ǉ��̃C���N���[�h
//	: �ǉ��̃C���N���[�h
//////////


namespace wiz{
namespace bomberobject{

/************************************************************************
Reply ��`��
************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FReply(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,DWORD next,
////            �F    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect,
////            �F    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�^�C�g���֖߂�̍Ċm�F
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
Reply::Reply(const LPDIRECT3DDEVICE9 pD3DDevice,const  LPDIRECT3DTEXTURE9 pTexture,const bool mark,
		const D3DXVECTOR3 &vScale,const D3DXVECTOR3 &vRot,const D3DXVECTOR3 &vPos,
		const RECT *pRect,const  D3DXVECTOR3 &vCenter,const  D3DXVECTOR3 &vOffsetPos,const  Color color)
:SpriteObject( pD3DDevice, pTexture, vScale, vRot, vPos, pRect, vCenter, vOffsetPos, color )
,m_vPos(		vPos	)
,m_bMark(		mark	)
,m_bPushRock(	false	)
,m_bWhichDraw(	false	)
,m_iTime(		0		)
,m_bPush(		false	)
,m_bSelect(		false	)
,m_pCoil(		NULL	)
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

Reply::~Reply(){
	m_pCoil		= NULL;
}
/////////////////// ////////////////////
//// �֐���     �Fvoid Reply::Draw( DrawPacket& i_DrawPacket)
//// �J�e�S��   �F�֐�
//// �p�r       �F�X�v���C�g��`��
//// ����       �FDrawPacket& i_DrawPacket    //�������̃f�[�^
//// �ߒl       �F�Ȃ�
//// �S����     �F������
//// ���l       �F
////            �F
////
void Reply::Draw(DrawPacket& i_DrawPacket)
{
	//	: �`��͐e�N���X�ɔC����
	SpriteObject::Draw(i_DrawPacket);
};

/////////////////// ////////////////////
//// �֐���     �Fvoid Reply::Update( UpdatePacket& i_UpdatePacket)
//// �J�e�S��   �F�֐�
//// �p�r       �F�f�[�^�̍X�V
//// ����       �FUpdatePacket& i_UpdatePacket    //�������̃f�[�^
//// �ߒl       �F�Ȃ�
//// �S����     �F������
//// ���l       �F
////            �F
////
void Reply::Update(UpdatePacket& i_UpdatePacket)
{
	if( !m_pCoil )		m_pCoil		= (PlayerCoil*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_3D_COIL);
	if( Cursor2D::isHitSprite( this ) ){
		if( Cursor2D::getLButtonState()/* || Cursor2D::getRButtonState()*/ ){
			if( m_bPushRock ){
				if( m_bMark ){
					i_UpdatePacket.pCommand->m_Command	= GM_OPENSTAGE_RESULT;
					i_UpdatePacket.pCommand->m_Param1	= m_pCoil->getDeadCount();
					i_UpdatePacket.pCommand->m_Param2	= m_pCoil->getMaxPos();
				}
				else{
					m_bWhichDraw	= true;
				}
				if( !m_bPush ){
					i_UpdatePacket.SearchSoundAndPlay( RCTEXT_SOUND_SE_ENTER );
				}
				m_bPush		= true;
				m_bPushRock	= false;
			}
		}
		else	m_bPushRock	= true;
		m_Color	= 0xFFFFFFFF;
		if( !m_bSelect ){
			m_bSelect = true;
			i_UpdatePacket.SearchSoundAndPlay( RCTEXT_SOUND_SE_SELECT );
		}
	}
	else{
		//	: �}�E�X���摜�͈̔͊O�ɂ���Ƃ�
		m_Color	= 0xA0FFFFFF;
		m_bSelect = false;
		if( Cursor2D::getLButtonState() )	m_bPushRock	= false;
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

/************************************************************************
Dead ��`��
************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FDead(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
////            �F    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect,
////            �F    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F���S���ɕ\�����镶��
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
Dead::Dead(	const LPDIRECT3DDEVICE9 pD3DDevice,const  LPDIRECT3DTEXTURE9 pTexture,
			const LPDIRECT3DTEXTURE9 pDeadCountTex, const  LPDIRECT3DTEXTURE9 pCountCharTex,const int iDeadCount,
			const D3DXVECTOR3 &vScale,const D3DXVECTOR3 &vRot,const D3DXVECTOR3 &vPos,
			const RECT *pRect,const  D3DXVECTOR3 &vCenter,const  D3DXVECTOR3 &vOffsetPos,const  Color color)
:SpriteObject( pD3DDevice, pTexture, vScale, vRot, vPos, pRect, vCenter, vOffsetPos, color )
,m_iTime(0)
,m_pDeadScore( NULL )
,m_pDeadCountChar( NULL )
{
	try{
		//	: �����}�g���b�N�X���v�Z
		D3DXMATRIX mScale,mRot,mPos;
		D3DXMatrixScaling(&mScale,vScale.x,vScale.y,vScale.z);
		D3DXMatrixRotationYawPitchRoll(&mRot,vRot.y,vRot.x,vRot.z);
		D3DXMatrixTranslation(&mPos,vPos.x,vPos.y,vPos.z);
		m_mMatrix = mScale * mRot * mPos ;

		float	wide	= BASE_CLIENT_WIDTH/2;
		float	height	= BASE_CLIENT_HEIGHT/2;
		int		iCount	= iDeadCount+1;

		D3DXVECTOR3	vScoreScale		= D3DXVECTOR3( 1.0f, 1.0f, 0.0f );
		D3DXVECTOR3	vScorePos		= D3DXVECTOR3( wide+40.0f*vScoreScale.x, height-32.0f*vScoreScale.y+65.0f, 0.0f );
		D3DXVECTOR3	vCountCharScale	= D3DXVECTOR3( 0.6f, 2.0f, 0.0f );
		D3DXVECTOR3	vCountCharPos	= D3DXVECTOR3( wide-256-40, height, 0.0f );

		m_pDeadScore			= new Score( pD3DDevice, pDeadCountTex, vScoreScale, vScorePos, iCount, &Rect( 0, 0, 512, 64 ) );
		m_pDeadCountChar		= new SpriteObject( pD3DDevice, pCountCharTex, vCountCharScale, g_vZero, vCountCharPos, NULL, g_vZero,g_vZero );

	}
	catch(...){
		SafeRelease(m_pSprite);
		//�ăX���[
		throw;
	}
};

/************************************
�f�X�g���N�^
************************************/
Dead::~Dead(){
	SAFE_DELETE(m_pDeadScore);
	SAFE_DELETE(m_pDeadCountChar);
}
/////////////////// ////////////////////
//// �֐���     �Fvoid Dead::Draw( DrawPacket& i_DrawPacket)
//// �J�e�S��   �F�֐�
//// �p�r       �F�X�v���C�g��`��
//// ����       �FDrawPacket& i_DrawPacket    //�������̃f�[�^
//// �ߒl       �F�Ȃ�
//// �S����     �F������
//// ���l       �F
////            �F
////
void Dead::Draw(DrawPacket& i_DrawPacket)
{
	//	: �`��͐e�N���X�ɔC����
	SpriteObject::Draw( i_DrawPacket );

	if( m_pDeadScore )		m_pDeadScore->Draw( i_DrawPacket );
	if( m_pDeadCountChar )	m_pDeadCountChar->Draw( i_DrawPacket );
};

/////////////////// ////////////////////
//// �֐���     �Fvoid Dead::Update( UpdatePacket& i_UpdatePacket)
//// �J�e�S��   �F�֐�
//// �p�r       �F�f�[�^�̍X�V
//// ����       �FUpdatePacket& i_UpdatePacket    //�������̃f�[�^
//// �ߒl       �F�Ȃ�
//// �S����     �F������
//// ���l       �F
////            �F
////
void Dead::Update(UpdatePacket& i_UpdatePacket)
{
	if( m_iTime > 60 ){
		m_Color.byteColor.a	-= 5;
		if( m_Color.byteColor.a <= 5)
			m_Color.byteColor.a	= 0;

	}
	m_iTime++;

	if( m_pDeadScore ){
		m_pDeadScore->setAlpha( m_Color.byteColor.a );
		m_pDeadScore->Update( i_UpdatePacket );
	}
	if( m_pDeadCountChar ){
		m_pDeadCountChar->setAlpha( m_Color.byteColor.a );
	}
};

/************************************************************************
Continue ��`��
************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FContinue(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,DWORD next,
////            �F    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect,
////            �F    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�R���e�j���[���邩�m�F
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
Continue::Continue(const LPDIRECT3DDEVICE9 pD3DDevice,const  LPDIRECT3DTEXTURE9 pTexture_Answer,
		const LPDIRECT3DTEXTURE9 pTexture_Rethinking, const LPDIRECT3DTEXTURE9 pTexture_Continue,
		const bool mark,const D3DXVECTOR3 &vScale,const D3DXVECTOR3 &vRot,const D3DXVECTOR3 &vPos,
		const RECT *pRect,const  D3DXVECTOR3 &vCenter,const  D3DXVECTOR3 &vOffsetPos,const  Color color)
:SpriteObject( pD3DDevice, pTexture_Answer, vScale, vRot, vPos, pRect, vCenter, vOffsetPos, color )
,m_vPos( vPos )
,m_bMark( mark )
,m_pCoil( NULL )
,m_pReply_Yes( NULL )
,m_pReply_No( NULL )
,m_pRethinking( NULL )
,m_pContinueChar( NULL )
,m_bPushRock( false )
,m_bWhichDraw( true )
,m_pRethinkingTex(pTexture_Rethinking)
,m_pAnswerTex(pTexture_Answer)
,m_pContinueTex( pTexture_Continue )
,m_iTime( 0 )
,m_bPush( false )
,m_bSelect( false )
{
	try{
		//	: �����}�g���b�N�X���v�Z
		D3DXMATRIX mScale,mRot,mPos;
		D3DXMatrixScaling(&mScale,vScale.x,vScale.y,vScale.z);
		D3DXMatrixRotationYawPitchRoll(&mRot,vRot.y,vRot.x,vRot.z);
		D3DXMatrixTranslation(&mPos,vPos.x,vPos.y,vPos.z);
		m_mMatrix = mScale * mRot * mPos ;

		float	wide	= BASE_CLIENT_WIDTH/2;
		float	height	= BASE_CLIENT_HEIGHT/2;

		//Continue���S�̍쐬
		m_pContinueChar	= new SpriteObject( pD3DDevice, m_pContinueTex, D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),g_vZero,
									D3DXVECTOR3( wide-256.0f,height-200.0f,0.0f ), Rect( 0, 0, 512, 64 ), g_vZero, g_vZero );

		m_pRethinking	= new SpriteObject( pD3DDevice, m_pRethinkingTex, D3DXVECTOR3(1.0f,1.0f,0.0f), g_vZero,
										D3DXVECTOR3( wide-256.0f,height-200.0f,0.0f ),Rect( 0,0,512,64 ), g_vZero, g_vZero  );
		m_pReply_Yes	= new Reply(  pD3DDevice, m_pAnswerTex, true, D3DXVECTOR3(1.0f,1.0f,0.0f), g_vZero,
										D3DXVECTOR3( wide-128.0f,height-50.0f,0.0f ),Rect( 0,0,256,64 ), g_vZero, g_vZero  );
		m_pReply_No		= new Reply(  pD3DDevice, m_pAnswerTex, false, D3DXVECTOR3(1.0f,1.0f,0.0f), g_vZero,
										D3DXVECTOR3( wide-128.0f,height+100.0f,0.0f ),Rect( 256,0,512,64 ), g_vZero, g_vZero  );

	}
	catch(...){
		SafeRelease(m_pSprite);
		//�ăX���[
		throw;
	}
};

/**********************************************
�f�X�g���N�^
**********************************************/
Continue::~Continue(){
	SAFE_DELETE( m_pReply_Yes );
	SAFE_DELETE( m_pReply_No );
	SAFE_DELETE( m_pRethinking );
	SAFE_DELETE( m_pContinueChar );
}

/////////////////// ////////////////////
//// �֐���     �Fvoid Continue::Draw( DrawPacket& i_DrawPacket)
//// �J�e�S��   �F�֐�
//// �p�r       �F�X�v���C�g��`��
//// ����       �FDrawPacket& i_DrawPacket    //�������̃f�[�^
//// �ߒl       �F�Ȃ�
//// �S����     �F������
//// ���l       �F
////            �F
////
void Continue::Draw(DrawPacket& i_DrawPacket)
{
	if( m_bWhichDraw ){
		if( m_pContinueChar != NULL )
			m_pContinueChar->Draw(i_DrawPacket);
		//	: �`��͐e�N���X�ɔC����
		SpriteObject::Draw(i_DrawPacket);
	}else{
		if( m_pRethinking != NULL )
			m_pRethinking->Draw(i_DrawPacket);
		if( m_pReply_Yes != NULL )
			m_pReply_Yes->Draw(i_DrawPacket);
		if( m_pReply_No != NULL )
			m_pReply_No->Draw(i_DrawPacket);
	}
};

/////////////////// ////////////////////
//// �֐���     �Fvoid Continue::Update( UpdatePacket& i_UpdatePacket)
//// �J�e�S��   �F�֐�
//// �p�r       �F�f�[�^�̍X�V
//// ����       �FUpdatePacket& i_UpdatePacket    //�������̃f�[�^
//// �ߒl       �F�Ȃ�
//// �S����     �F������
//// ���l       �F
////            �F
////
void Continue::Update(UpdatePacket& i_UpdatePacket)
{
	if( m_bWhichDraw ){
		if( !m_pCoil ) m_pCoil = (PlayerCoil*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_3D_COIL);
		if( Cursor2D::isHitSprite( this ) ){
			if( Cursor2D::getLButtonState()/* || Cursor2D::getRButtonState()*/ ){
				if( m_bPushRock ){
					if( m_bMark )
						m_pCoil->setReadyContinue(true);
					else{
						if( m_pReply_No != NULL){
							m_pReply_No->setWhichDraw( false );
						}
						m_bWhichDraw	= false;
					}
					//	: �}�E�X�̍��{�^���������ꂽ
					
					if( !m_bPush ){
						i_UpdatePacket.SearchSoundAndPlay( RCTEXT_SOUND_SE_ENTER );
					}
					m_bPush		= true;
					m_bPushRock	= false;
				}
			}
			else	m_bPushRock	= true;
			m_Color	= 0xFFFFFFFF;
			if( !m_bSelect ){
				m_bSelect = true;
				i_UpdatePacket.SearchSoundAndPlay( RCTEXT_SOUND_SE_SELECT );
			}
		}
		else{
			//	: �}�E�X���摜�͈̔͊O�ɂ���Ƃ�
			m_Color	= 0xA0FFFFFF;
			m_bSelect = false;
			if( Cursor2D::getLButtonState() )	m_bPushRock	= false;
			else				m_bPushRock	= true;
		}
	}
	else{
		if( m_pRethinking != NULL )
			m_pRethinking->Update( i_UpdatePacket );
		if( m_pReply_Yes != NULL )
			m_pReply_Yes->Update( i_UpdatePacket );
		if( m_pReply_No != NULL ){
			m_pReply_No->Update( i_UpdatePacket );
			m_bWhichDraw	= m_pReply_No->getWhichDraw();
		}
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

}
}