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
LineCursor::LineCursor( LPDIRECT3DDEVICE9 pD3DDevice ){

	UINT iVertexSize = 0;

	//	: ���_�o�b�t�@�̐����i����ł���̈�̃T�C�Y�A�f�[�^�̈����A���_�f�[�^�̒��g�A���_�f�[�^���Ǘ����郁�����A�������ꂽ�o�b�t�@�������A�h���X���A���Ă���j�j
	pD3DDevice->CreateVertexBuffer( Vertex::getSize() * iVertexSize , D3DUSAGE_WRITEONLY, Vertex::getFVF(), D3DPOOL_MANAGED, &m_pVertexBuffer, NULL );
	m_pVertexBuffer->Lock( 0, 0, (void**)&m_pVertex ,0 );	//	: ���_�f�[�^�̃A�h���X���擾����ƂƂ��ɁA�f�[�^�ւ̃A�N�Z�X���J�n����	


	m_pVertex[ 0 ] = Vertex(D3DXVECTOR3( 0.0f , 0.0f , 0.0f ) , 0xFFFFFFFF );
	m_pVertex[ 1 ] = Vertex(D3DXVECTOR3( 0.2f , 1.0f , 0.0f ) , 0xFFFFFFFF );
	m_pVertex[ 2 ] = Vertex(D3DXVECTOR3( 0.2f , 1.0f , 0.0f ) , 0xFFFFFFFF );
	m_pVertex[ 3 ] = Vertex(D3DXVECTOR3( 1.0f , 1.0f , 0.0f ) , 0xFFFFFFFF );


	m_pVertexBuffer->Unlock();



}
/******************************************************************************
void VertexLineState::Draw(
	LPDIRECT3DDEVICE9 pD3DDevice ,	//�f�o�C�X
	const D3DXMATRIX& i_Matrix		//�`�悵�����v���[�g�̔z��
	)
�p�r : �����`�̃v���[�g��`��
�߂�l : �Ȃ�
******************************************************************************/
void LineCursor::Draw(LPDIRECT3DDEVICE9 pD3DDevice , const D3DXMATRIX& i_Matrix )
{
	 pD3DDevice->SetRenderState( D3DRS_LIGHTING , FALSE );

	//if( m_pTexture ) pD3DDevice->SetTexture( 0 , m_pTexture->getTexture() );			//	: �e�N�X�`����ݒ�iNULL �̏ꍇ�̓e�N�X�`�������j

	 //���[���h�ϊ��s���ݒ�
	pD3DDevice->SetTransform( D3DTS_WORLD , &i_Matrix );								//�ϊ��ςݒ��_�̏ꍇ�͖��������

	//	: ���_�o�b�t�@��p���ă��f����`�悷��
	pD3DDevice->SetStreamSource( 0, m_pVertexBuffer , 0 , Vertex::getSize() );		//	: �`��ΏۂƂȂ钸�_�o�b�t�@��ݒ�
	pD3DDevice->SetFVF( Vertex::getFVF() );											//	: ���_�f�[�^�̌`����ݒ�
	//pD3DDevice->DrawPrimitive( m_PrimitiveType , 0, m_iDrawPrimitiveVertexNum );	//	: ���_�f�[�^�̕`��i�`��̎d���A�`��J�n�ʒu�A�v���~�e�B�u���j


	pD3DDevice->SetTexture( 0 , NULL );												//	: �e�N�X�`����ݒ�iNULL �̏ꍇ�̓e�N�X�`�������j
	pD3DDevice->SetRenderState( D3DRS_LIGHTING , TRUE );

}


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
MouseCursor::MouseCursor( LPDIRECT3DDEVICE9 pD3DDevice, TextureManager* m_pTexMgr)
:Box( pD3DDevice, D3DXVECTOR3( 1.0f, 1.0f, 1.0f), g_vZero, g_vZero, COLOR2D3DCOLORVALUE(0x0FFFFF0F), COLOR2D3DCOLORVALUE(0x0FFFFF0F), COLOR2D3DCOLORVALUE(0x0FFFFF0F),  OBJID_SYS_CURSOR, false, m_pTexMgr->addTexture( pD3DDevice, L"Field.png" ) )
,PrimitiveSprite(pD3DDevice, m_pTexMgr->addTexture( pD3DDevice, L"CARSOL.tga" ), NULL, D3DXVECTOR3( 92.0f, 67.0f, 0.0f ), g_vZero)
,m_Ptn(0)
,m_MovePosY(0)
,m_pCamera( NULL )
{

	D3DXVECTOR3 vScale = D3DXVECTOR3(0.5f,0.5f,0.0f);
	D3DXMatrixScaling( &m_mScale, vScale.x, vScale.y, vScale.z );

	Box::SetBaseScale( D3DXVECTOR3( (float)MGPRM_MAGNETICUM*2, (float)MGPRM_MAGNETICUM*2, 0.0f) );


	m_pCursorLine = new NameLineEffect( pD3DDevice, NULL, 1);
	m_pCursorLine->AddNameLineEffect( pD3DDevice, g_vZero, g_vOne);
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
	m_MovePosY = 0 ;
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

	//	: �J�[�\���̐ݒ�
	//	: �}�E�X�̃N���C�A���g���W���l��
	GetCursorPos( &m_v2DPos ) ;
	ScreenToClient( g_hWnd , &m_v2DPos) ;
	
	//	: ���W�̍X�V
	D3DXMATRIX mPos ;
	D3DXMatrixTranslation( &mPos, (float)m_v2DPos.x, (float)m_v2DPos.y, 0.0f);

	//	: �s��̎Z�o
	m_mMatrix = m_mScale * mPos ;



	UpdateCursor();
	m_pCursorLine->setPos(m_v3DPos);

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
	m_pCursorLine->Draw(i_DrawPacket.pD3DDevice,*i_DrawPacket.pVec,NULL,*i_DrawPacket.pCommand);
	//PrimitiveSprite::Draw(i_DrawPacket);
	Box::Draw(i_DrawPacket);
}

void MouseCursor::UpdateCursor(){
	if( m_pCamera ){

		float fYPosCorrection = 10.0f ;
		//	: �}�E�X���W�̂R�c�ϊ�
		m_v3DPos = D3DXVECTOR3( 
			(float)m_v2DPos.x / DRAW_CLIENT_MAGNIFICATION - MAGNETIC_RADIUS ,
			(( STANDARD_WINDOW_HEIGHT - m_v2DPos.y ) - UI_HEIGHT ) / DRAW_CLIENT_MAGNIFICATION -
											MAGNETIC_RADIUS +  m_pCamera->getPosY() - fYPosCorrection  ,
			0.0f
		);
		SetBasePos( m_v3DPos );

		Debugger::DBGSTR::addStr( L" Pos( %f, %f, %f )\n" , m_v3DPos.x , m_v3DPos.y, m_v3DPos.z ) ;

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
Factory_Cursor::Factory_Cursor(FactoryPacket* fpac){
	try{

 		D3DCOLORVALUE MouseDiffuse = {0.7f,0.7f,0.7f,0.0f};
		D3DCOLORVALUE MouseSpecular = {0.0f,0.0f,0.0f,0.0f};
		D3DCOLORVALUE MouseAmbient = {0.5f,0.5f,0.5f,0.0f};

		fpac->m_pVec->push_back(
			new MouseCursor( 
						fpac->pD3DDevice,
						fpac->m_pTexMgr
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