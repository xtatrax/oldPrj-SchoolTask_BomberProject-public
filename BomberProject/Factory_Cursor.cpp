////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Mouse.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�g�n ��m
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Mouse ;
//

#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Cursor.h"

namespace wiz{
namespace bomberobject{

/**************************************************************************
 MouseCursor ��`��
****************************************************************************/
/**************************************************************************
 MouseCursor::MouseCursor(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	LPDIRECT3DTEXTURE9 pTexture,	//�e�N�X�`��
	wiz::OBJID id					//�I�u�W�F�N�g�̎��
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
 �S���F�{�����V
***************************************************************************/
MouseCursor::MouseCursor( LPDIRECT3DDEVICE9 pD3DDevice, TextureManager* m_pTexMgr, float fLineLength, float fPointSize)
:Box( pD3DDevice, D3DXVECTOR3( 1.0f, 1.0f, 1.0f), g_vZero, g_vZero, COLOR2D3DCOLORVALUE(0x0FFFFF0F), COLOR2D3DCOLORVALUE(0x0FFFFF0F), COLOR2D3DCOLORVALUE(0x0FFFFF0F),  OBJID_SYS_CURSOR, false, m_pTexMgr->addTexture( pD3DDevice, L"Field.png" ) )
,PrimitiveSprite(pD3DDevice, m_pTexMgr->addTexture( pD3DDevice, L"CARSOL.tga" ), NULL, D3DXVECTOR3( 92.0f, 67.0f, 0.0f ), g_vZero)
,m_Ptn(0)
,m_MovePosY(0)
,m_pCamera( NULL )
,m_pLine( NULL )
,m_pLine2( NULL )
,m_pTorus( NULL )
,m_fTorusMagnification(0)
{

	D3DXVECTOR3 vScale = D3DXVECTOR3(0.5f,0.5f,0.0f);
	D3DXMatrixScaling( &m_mScale, vScale.x, vScale.y, vScale.z );

	Box::SetBaseScale( D3DXVECTOR3( (float)MGPRM_MAGNETICUM*2, (float)MGPRM_MAGNETICUM*2, 0.0f) );
	
	const	D3DXVECTOR3	vDir	= D3DXVECTOR3( cosf( D3DXToRadian(-55.0f) ), sinf( D3DXToRadian(-55.0f) ), 0.0f );
	const	D3DXVECTOR3	vDir2	= D3DXVECTOR3( cosf( D3DXToRadian(0.0f) ), sinf( D3DXToRadian(0.0f) ), 0.0f );
	const	float		fRange	= 100.0f;

	//m_vScale	= D3DXVECTOR3( 0.125f, 0.125f, 0.0f );
	m_vScale	= D3DXVECTOR3( fPointSize, fPointSize, 0.0f );
	m_pSelectPos	= new SpriteObject( pD3DDevice, m_pTexMgr->addTexture( pD3DDevice, L"point.png" ), m_vScale,
										g_vZero, g_vZero, NULL, D3DXVECTOR3( 16.0f, 16.0f, 0.0f ), g_vZero );

	m_pLine			= new Line( g_vZero, vDir, fRange, 0xFFFFFF00 );
	m_pLine2		= new Line( m_pLine->getEndPos(), vDir2, fLineLength, 0xFFFFFF00 );

	m_pTorus	= new Torus(
		pD3DDevice,
		0.01f,
		1.0f,
		g_vZero,
		g_vZero,
		COLOR2D3DCOLORVALUE(0x80FFFFFF),
		COLOR2D3DCOLORVALUE(0x80FFFFFF),
		COLOR2D3DCOLORVALUE(0x80FFFFFF),
		OBJID_UNK,
		false,
		NULL,
		36,
		150
	);
	
}

/////////////////// ////////////////////
//// �p�r       �F~MouseCursor();
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F
//// ����       �F
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F
MouseCursor::~MouseCursor(){
	m_MovePosY	= 0 ;
	SafeDelete( m_pLine	 )	;
	SafeDelete( m_pLine2 )	;
	SafeDelete( m_pTorus )	;
	SafeDelete( m_pSelectPos )	;
}


/////////////////// ////////////////////
//// �p�r       �Fvoid Update( UpdatePacket& i_UpdatePacket )
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g���X�V
//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
////            �F  ��       Command            pCommand        // �R�}���h
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
void MouseCursor::Update( UpdatePacket& i_UpdatePacket ){
	if(m_pCamera == NULL){
		m_pCamera = (Camera*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CAMERA);
		m_pCamera && (m_MovePosY	= m_pCamera->getPosY());
	}

	static float s_fTimeCount = 0.0f;

	Update2DPos();

	//	: ���W�̍X�V
	D3DXMATRIX mPos ;
	D3DXMatrixTranslation( &mPos, (float)m_v2DPos.x, (float)m_v2DPos.y, 0.0f);

	//	: �s��̎Z�o
	m_mMatrix = m_mScale * mPos ;

	Update3DPos();

	m_pLine->setMatrix( m_mMatrix );
	m_pLine2->setMatrix( m_mMatrix );

	D3DXMATRIX mPos2, mScale, mRot;

	D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y, m_vScale.z );
	m_mMatrix = mScale * mPos ;
	m_pSelectPos->setMatrix( m_mMatrix );

	D3DXMatrixTranslation(&mPos2, m_v3DPos.x, m_v3DPos.y, m_v3DPos.z);
	D3DXMatrixScaling(&mScale, m_fTorusMagnification,m_fTorusMagnification,0.0f);
	D3DXMatrixRotationZ(&mRot, 0.0f);
	m_pTorus->CalcMatrix(mPos2, mScale, mRot);

	if(m_fTorusMagnification >= CURSOR_FIELD_LENGHT){
		m_fTorusMagnification = CURSOR_FIELD_LENGHT;
		s_fTimeCount += (float)i_UpdatePacket.pTime->getElapsedTime();
		if(s_fTimeCount >= CURSOR_FIELD_TIME){		
			m_fTorusMagnification = 0.0f;
			s_fTimeCount		  = 0.0f;
		}
	}
	else{
		m_fTorusMagnification += CURSOR_FIELD_LENGHT * i_UpdatePacket.pTime->getElapsedTime();
	}

	++m_Ptn;
}

/////////////////// ////////////////////
//// �p�r       �Fvoid Draw( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
////            �F  �� Tempus2*            i_DrawPacket.pTime	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
//// �ߒl       �F����
//// �S����     �F�{�����V
//// ���l       �F
void MouseCursor::Draw(DrawPacket& i_DrawPacket)
{
	//PrimitiveSprite::Draw(i_DrawPacket);
	//Box::Draw(i_DrawPacket);
	m_pLine->draw(i_DrawPacket.pD3DDevice);
	m_pLine2->draw(i_DrawPacket.pD3DDevice);
	m_pSelectPos->Draw(i_DrawPacket);
	if(m_pCamera)m_pTorus->Draw(i_DrawPacket);
}
void MouseCursor::Update2DPos(){
	//	: �J�[�\���̐ݒ�
	//	: �}�E�X�̃N���C�A���g���W���l��
	GetCursorPos( &m_v2DPos ) ;
	ScreenToClient( wiz::DxDevice::m_hWnd , &m_v2DPos) ;

	
}
void MouseCursor::Update3DPos(){
	if( m_pCamera ){

		float fYPosCorrection = 10.0f ;
		//	: �}�E�X���W�̂R�c�ϊ�
		m_v3DPos = D3DXVECTOR3( 
			(float)m_v2DPos.x / DRAW_CLIENT_MAGNIFICATION - MAGNETIC_RADIUS ,
			(( STANDARD_WINDOW_HEIGHT - m_v2DPos.y ) - UI_HEIGHT ) / DRAW_CLIENT_MAGNIFICATION -
											MAGNETIC_RADIUS +  m_pCamera->getPosY() - fYPosCorrection  , 0.0f
		);
		SetBasePos( m_v3DPos );


		Box::CalcWorldMatrix();
	}
}
/**************************************************************************
 Factory_Cursor ��`��
****************************************************************************/
/**************************************************************************
 Factory_Cursor::Factory_Cursor(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Cursor::Factory_Cursor(FactoryPacket* fpac, float fLineLength, float fPointSize){
	try{

 		D3DCOLORVALUE MouseDiffuse = {0.7f,0.7f,0.7f,0.0f};
		D3DCOLORVALUE MouseSpecular = {0.0f,0.0f,0.0f,0.0f};
		D3DCOLORVALUE MouseAmbient = {0.5f,0.5f,0.5f,0.0f};

		fpac->m_pVec->push_back(
			new MouseCursor( 
						fpac->pD3DDevice,
						fpac->m_pTexMgr,
						fLineLength,
						fPointSize
			)
		);

	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 Factory_Cursor::~Factory_Cursor();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Cursor::~Factory_Cursor(){
    //�Ȃɂ����Ȃ�
}

}
//end of namespace bomberobject.
}
//end of namespace wiz.