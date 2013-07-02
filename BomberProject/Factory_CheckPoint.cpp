////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_CheckPoint.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	���p��			�F�{�� ���V
//	�ҏW			�F���� ��
//	�����ް��Ɣ��l	�F�`�F�b�N�|�C���g
//					��
//	namespace wiz;
//		namespace bomberobject;
//			class CheckEffect         : public PrimitiveBox	;
//			class CheckPoint          : public Cylinder		;
//			class Factory_CheckPoint  ;
//

//////////
//	: ��{�̃C���N���[�h
#include "StdAfx.h"
#include "Factory_CheckPoint.h"
//	: ��{�̃C���N���[�h
//////////

//////////
//	: �ǉ��̃C���N���[�h
//	: �ǉ��̃C���N���[�h
//////////



const float CHECK_POINT_RADIUS = 0.25f ;
const D3DXVECTOR3 CHECK_POINT_CHAR_SIZE = D3DXVECTOR3(1.0f,1.0f,0.0f);
D3DCOLORVALUE CHECKPOINTCOLOR = { 0.5f, 1.0f, 0.5f, 0.5f } ;
D3DCOLORVALUE CHECKPOINTCOLOR_CHAR = { 1.0f, 1.0f, 1.0f, 1.0f } ;

const	float	CHECKPOINT_CHAR_DOWNSPEED	= 20.0f;
const	float	CHECKPOINT_CHAR_RATE_Y		= (1.0f/CHECK_POINT_CHAR_SIZE.y);
const	float	CHECKPOINT_CHAR_RATE_X		= (1.0f/CHECK_POINT_CHAR_SIZE.x);

namespace wiz{
namespace bomberobject{

///**************************************************************************
// CheckEffect ��`��
//****************************************************************************/
///************************************************************************class MouseCursor : public Box , public  PrimitiveSprite{
//**
// CheckEffect::CheckEffect(
//	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
//	LPTATRATEXTURE pTexture,	//�e�N�X�`��
//	wiz::OBJID id					//�I�u�W�F�N�g�̎��
//);
// �p�r: �R���X�g���N�^
// �߂�l: �Ȃ�
// �S���F������
//***************************************************************************/
CheckEffect::CheckEffect(LPDIRECT3DDEVICE9 pD3DDevice,
						D3DXVECTOR3 vPos,
						float		fLength,
						LPTATRATEXTURE pTexture,wiz::OBJID id)
	:PrimitiveBox(pD3DDevice,
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					id,
					pTexture)
,m_bVanish(false)
,m_pCoil( NULL )
,m_vPointScale( g_vZero )
,m_vPointPos( g_vZero )
{
	D3DXMatrixIdentity( &m_Matrix );
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));

	D3DCOLORVALUE Diffuse	= {0.0f,0.0f,0.0f,0.0f};
	D3DCOLORVALUE Specular	= {0.0f,0.0f,0.0f,0.0f};
	D3DCOLORVALUE Ambient	= {0.5f,1.0f,0.5f,0.0f};

	m_Material.Diffuse	= Diffuse;
	m_Material.Specular	= Specular;
	m_Material.Ambient	= Ambient;

	LPDIRECT3DVERTEXBUFFER9 pVB = 0;
	CommonMeshVertex* pVer = 0;
	m_pMesh->GetVertexBuffer(&pVB);
	pVB->Lock(0,0,(VOID**)&pVer,0);
	DWORD vsize = m_pMesh->GetNumVertices();
	for(DWORD n = 0;n < vsize;n++){ //���_�̐����擾����
		//�@���ƒ��_����uv�l�𓾂�
		BoxVecNomalUV(pVer[n].vec,pVer[n].normal,pVer[n].tu,pVer[n].tv);
	}
	pVB->Unlock();
	SafeRelease( pVB );
	//SafeDelete( pVer );

	for( int i = 0; i < DRAWING_NUMBER; i++ )
		addEffect( float(i*2), vPos.y );
	Debugger::DBGWRITINGLOGTEXT::addStr(L"CheckEffect::CheckEffect OK\n");
}

/********************************
�f�X�g���N�^
********************************/
CheckEffect::~CheckEffect(){
	m_pCoil = NULL;
	SafeDeletePointerMap( m_ItemMap_Target );
	m_ItemMap_Target.clear();
}

/*********************************
�ǉ�
*********************************/
void	CheckEffect::addEffect( float i_vPosX, float i_vPosY){
	EffectItem*	pItem	= new EffectItem;

	pItem->m_vPos		= D3DXVECTOR3( i_vPosX, i_vPosY, 0.0f );
	pItem->m_vScale		= D3DXVECTOR3( EFFECT_SIZE*4, EFFECT_SIZE, 1.0f );
	pItem->m_fInitPosX	= i_vPosX;
	pItem->m_bStart		= false;

	m_ItemMap_Target.insert(multimap<float,EffectItem*>::value_type(pItem->m_vPos.y,pItem));

}

/////////////////// ////////////////////
//// �p�r       �Fvoid Draw( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
////            �F  �� Tempus2*            i_DrawPacket.GetTime()	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
//// �ߒl       �F����
//// �S����     �F������
//// ���l       �F
void CheckEffect::Draw(DrawPacket& i_DrawPacket)
{
	multimap<float,EffectItem*>::iterator it = m_ItemMap_Target.begin();
	while(it != m_ItemMap_Target.end()){
		update( it->second->m_vPos , it->second->m_fInitPosX, it->second->m_vScale, it->second->m_bStart,i_DrawPacket);
		setMatrix( it->second->m_vPos, it->second->m_vScale );
		setTexDraw(i_DrawPacket);
		++it;
	}
}

/*********************************************************************
�G�t�F�N�g���ЂƂ����`��
*********************************************************************/
void	CheckEffect::PointDraw(DrawPacket &i_DrawPacket){
	if( m_vPointScale.x < EFFECT_SIZE*3 )
		Expansion();
	//m_vPointScale.x	= EFFECT_SIZE*3;
	//m_vPointScale.y	= EFFECT_SIZE*3;
	setMatrix( m_vPointPos, m_vPointScale );
	setTexDraw(i_DrawPacket);
}

/**********************************************************
**********************************************************/
void	CheckEffect::setTexDraw(DrawPacket& i_DrawPacket){
	//�e�N�X�`��������ꍇ
	if(m_pTexture){
		DWORD wkdword;
		//���݂̃e�N�X�`���X�e�[�^�X�𓾂�
		i_DrawPacket.GetDevice()->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
		//�X�e�[�W�̐ݒ�
		i_DrawPacket.GetDevice()->SetTexture(0,m_pTexture->getTexture());
		//�f�t�B�[�Y�F�ƃe�N�X�`�����|�����킹��ݒ�
		i_DrawPacket.GetDevice()->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
		i_DrawPacket.GetDevice()->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		i_DrawPacket.GetDevice()->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

		//i_DrawPacket.GetDevice()->SetFVF(PlateFVF);
		// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
		i_DrawPacket.GetDevice()->SetTransform(D3DTS_WORLD, &m_Matrix);
		//�R�������b�V����Draw()���Ă�
		CommonMesh::Draw(i_DrawPacket);
		i_DrawPacket.GetDevice()->SetTexture(0,0);
		//�X�e�[�W�����ɖ߂�
		i_DrawPacket.GetDevice()->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	}
	else{
	//�e�N�X�`�����Ȃ��ꍇ
		// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
		i_DrawPacket.GetDevice()->SetTransform(D3DTS_WORLD, &m_Matrix);
		//�R�������b�V����Draw()���Ă�
		CommonMesh::Draw(i_DrawPacket);
	}
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
//// �S����     �F������
//// ���l       �F
////            �F
////
void CheckEffect::update( D3DXVECTOR3& o_vPos, float i_fInitPosX , D3DXVECTOR3& o_vScale, bool& o_bStart,DrawPacket& i_DrawPacket){

	if( !m_pCoil   ) m_pCoil   = (PlayerCoil*)i_DrawPacket.SearchObjectFromID( OBJID_3D_COIL );
	//�X�^�[�g�ʒu�ɃG�t�F�N�g���o����
	if( o_bStart ){
		if( o_vScale.x > 0.0f && o_vScale.y > 0.0f ){
			if( m_pCoil != NULL ){
				Pos_Update(o_vPos.x);
			}
			Reduction( o_vScale );	//�k��
			m_bVanish	= false;
		}
		else	ResetState( o_vPos, i_fInitPosX, o_vScale, o_bStart );
	}

}

/*******************************************************
�}�g���b�N�X�̐ݒ�
*******************************************************/
void	CheckEffect::setMatrix( const D3DXVECTOR3 i_vPos, const D3DXVECTOR3 i_vScale ){
	//�v�Z��Update��
	//�g��k��
	D3DXMATRIX mScale;
	D3DXMatrixIdentity(&mScale);
	D3DXMatrixScaling( &mScale, i_vScale.x, i_vScale.y, 1.0f );
	//��]
	D3DXMATRIX mRot;
	D3DXMatrixIdentity(&mRot);
	//�ړ��p
	D3DXMATRIX mMove;
	D3DXMatrixIdentity(&mMove);
	D3DXMatrixTranslation(&mMove,i_vPos.x,i_vPos.y,i_vPos.z);
	//�~�b�N�X�s��
	m_Matrix	= mScale * mRot * mMove;
}

/************************************
�֐����@�Fvoid Pos_Update( int i )
�p�r�@�@�F�`��ʒu�̍X�V
�J�e�S���F
�����@�@�Fint i     //�ύX�������G�t�F�N�g�̎w��
�߂�l�@�F
�S���ҁ@�F������
���l�@�@�F
************************************/
void	CheckEffect::Pos_Update( float& o_fPosX ){
	float	MigrationRate	= m_pCoil->getStartPos().x - o_fPosX;
	//�`�悷�ׂ��ʒu���Z�o
	o_fPosX	+= MigrationRate/10.0f + 0.2f;
	if( MigrationRate > 0.0f ){
		o_fPosX	+= MigrationRate/10.0f + 0.2f;
		if( m_pCoil->getStartPos().x - o_fPosX < 0.0f )
			o_fPosX	= m_pCoil->getStartPos().x;
	}
	else if( MigrationRate < 0.0f ){
		o_fPosX	+= MigrationRate/10.0f - 0.2f;
		if( m_pCoil->getStartPos().x - o_fPosX > 0.0f )
			o_fPosX	= m_pCoil->getStartPos().x;
	}

}

/*************************************
�֐����@�Fvoid	CheckEffect::Reduction()
�p�r�@�@�F�T�C�Y�k��
�J�e�S���F�֐�
�����@�@�F�Ȃ�
�߂�l�@�F�Ȃ�
�S���ҁ@�F������
���l�@�@�F
*************************************/
void	CheckEffect::Reduction( D3DXVECTOR3& o_vScale ){
	o_vScale.x	-= 0.2f;
	o_vScale.y	-= 0.05f;
}

/*************************************
�֐����@�Fvoid	CheckEffect::Expansion()
�p�r�@�@�F�T�C�Y�g��i�g�嗦�͏c�������j
�J�e�S���F�֐�
�����@�@�F�Ȃ�
�߂�l�@�F�Ȃ�
�S���ҁ@�F������
���l�@�@�F
*************************************/
void	CheckEffect::Expansion(){
	m_vPointScale.x	+= 0.08f;
	m_vPointScale.y	+= 0.08f;
}

/************************************************
�������̃��Z�b�g
************************************************/
void	CheckEffect::ResetState( D3DXVECTOR3& o_vPos, float i_fInitPosX, D3DXVECTOR3& o_vScale, bool& o_bStart ){

	o_bStart		= false;
	m_bVanish		= true;
	o_vScale.x		= EFFECT_SIZE*4 ;
	o_vScale.y		= EFFECT_SIZE;
	m_vPointScale	= g_vZero;
	o_vPos.x		= i_fInitPosX;
	o_vPos.y		= m_fPosY;
}

/************************************************************************
�S�ẴG�t�F�N�g�ɃA�j���[�V�����J�n�t���O�����Ă�
************************************************************************/
void	CheckEffect::setStart( bool i_bStart ){
	multimap<float,EffectItem*>::iterator it = m_ItemMap_Target.begin();
	while(it != m_ItemMap_Target.end()){
		it->second->m_bStart	= i_bStart;
		++it;
	}
}
/**************************************************************
�`�F�b�N�G�t�F�N�g��Y���W�����ʒu
**************************************************************/
void	CheckEffect::setInitPosY(float posY){

	multimap<float,EffectItem*>::iterator it = m_ItemMap_Target.begin();
	while(it != m_ItemMap_Target.end()){
		it->second->m_vPos.y	= posY;
		++it;
	}
}

/******************************************
�`�F�b�N�|�C���g�̕`��ʒu�X�V�iY���W�j
******************************************/
void	CheckEffect::setPosY(float posY){
	m_fPosY	= posY;
}

/****************************************************************************
CheckPoint ��`��
****************************************************************************/
CheckPoint::CheckPoint( LPDIRECT3DDEVICE9 pD3DDevice, float fLength,LPTATRATEXTURE pTexture,LPTATRATEXTURE pTexture2,LPTATRATEXTURE pTexture3, wiz::OBJID id  )
:Object( id )
,m_Effect(pD3DDevice, g_vZero, fLength, pTexture)
,m_PintMark(pD3DDevice, pTexture2, CHECK_POINT_CHAR_SIZE, g_vZero, g_vZero,&Rect( 0, 0, 512, 64 ), D3DXVECTOR3( 256.0f, 32.0f, 0.0f ), D3DXVECTOR3( 0.0f, -87.0f, 0.0f ))
,m_pCoil( NULL )
,m_pCamera( NULL )
,m_ActiveItem( NULL )
,m_pTime( NULL )
,m_Color( CHECKPOINTCOLOR )
,m_Thicken( 1.0f )
,m_Length( fLength )
,m_pTextureLast( pTexture3 )
,m_bPlayerPass( false )
,m_bFirstRead( true )
{
	Debugger::DBGWRITINGLOGTEXT::addStr(L"CheckPoint::CheckPoint OK\n");
}
CheckPoint::~CheckPoint(){
	m_pCoil		= NULL ;
	m_pCamera	= NULL ;
	m_pTime		= NULL ;
	SafeDeletePointerContainer( m_ItemContainer ) ;
	m_ItemContainer.clear();
}
/////////////////// ////////////////////
//// �p�r       �Fvirtual void Update( UpdatePacket& i_UpdatePacket )
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�I�u�W�F�N�g���X�V
//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
////            �F  ��       Command            pCommand        // �R�}���h
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F�p���������̂ł��K���Ƃ���`�����Ȃ��Ă��ǂ�
////            �F
////
void CheckPoint::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pTime )		m_pTime	= ( TimeScore* )i_UpdatePacket.SearchObjectFromID( OBJID_UI_TIME );
	if( !m_pCoil   )	m_pCoil	= (PlayerCoil*)i_UpdatePacket.SearchObjectFromID( OBJID_3D_COIL	) ;
	if( !m_pCamera ){
		m_pCamera = (    Camera*)i_UpdatePacket.SearchObjectFromID( OBJID_SYS_CAMERA ) ;
		m_fInitPosY	= 	m_pCamera->getPosY();
	}

	float	fTexPosY	= m_pCamera->getPosY() - m_fInitPosY;
	//�S�Ẵ`�F�b�N�|�C���g��ʂ��Ă��Ȃ����������
	if( m_pCoil && m_ActiveItem < m_ItemContainer.size()){

		setTexPos( m_ActiveItem, fTexPosY );

		if( m_bFirstRead ){
			m_Effect.setInitPosY(m_ItemContainer[ m_ActiveItem ]->fPosY);
			m_bFirstRead	= false;
		}

		PlayerPass(i_UpdatePacket);
		//�R�C�����`�F�b�N�|�C���g��ʉ߂�����
		if( m_bPlayerPass ){
			if( m_ActiveItem < m_ItemContainer.size() ){
				//�G�t�F�N�g�̍X�V***********************************************

				m_Effect.setPointPos( m_pCoil->getStartPos() );				//���A�n�_�̈ʒu��n��
				m_Effect.setPosY( m_ItemContainer[ m_ActiveItem ]->fPosY );	//�`�F�b�N�|�C���g�̈ʒu��n��
				m_Effect.setStart( true );									//�A�j���[�V�������J�n
				
				//******************************************************************
			}
			m_bPlayerPass	= false;
		}

	}
	else{
		setTexPos( m_ActiveItem-1, fTexPosY );	//�Ō�܂ł�������e�N�X�`�����W�̍X�V���P�O�ŌŒ�
	}

};

/////////////////// ////////////////////
//// �p�r       �Fvirtual void Draw( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F�������z�֐�
//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
////            �F  �� Tempus2*            i_DrawPacket.GetTime()	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
//// �ߒl       �F����
//// �S����     �F���� �O �{�����V(�ҏW)
//// ���l       �F
////            �F
////
void CheckPoint::Draw( DrawPacket& i_DrawPacket ){
	if( m_pCamera && m_ActiveItem < m_ItemContainer.size()){
		//	: �J����������
		//	: �`��Ώۂ�����
		float DrawBeginLength = m_pCamera->getPosY() + DRAW_TOLERANCE ;
		if( DrawBeginLength > m_ItemContainer[ m_ActiveItem ]->fPosY ){
			//	: ��ʂ̒��ɂ���
			
			//	:�@���b�Z�[�W�H��`��
			m_PintMark.Draw(i_DrawPacket);

		}

		Debugger::DBGSTR::addStr(L"m_ActiveItem = %d\n",m_ActiveItem);
	}
	else/* if(m_ActiveItem == m_ItemContainer.size()-1)*/{
		m_PintMark.Draw(i_DrawPacket);
	}

	//�`�F�b�N�|�C���g�̕`��
	m_Effect.Draw( i_DrawPacket );
	//��x�ł��`�F�b�N�|�C���g��ʉ߂��������
	//���A�n�_�̕`��
	if(m_Effect.getVanish())	m_Effect.PointDraw( i_DrawPacket );
		
};

/*************************************************
�R�C�����`�F�b�N�|�C���g��ʉ߂�����
*************************************************/
void	CheckPoint::PlayerPass(UpdatePacket &i_UpdatePacket){

	float fPosY		= m_ItemContainer[ m_ActiveItem ]->fPosY;
	float fCoilPosY = m_pCoil->getPos().y;

	if(fPosY <= fCoilPosY){
		m_pCoil->setStartPos(m_ItemContainer[ m_ActiveItem ]->vStartPos);
		m_ActiveItem++;
		m_pCoil->setRecordTime();
		m_pTime->setTime();
		if(m_ActiveItem == m_ItemContainer.size()-1){
			m_PintMark.setTexture(m_pTextureLast);
			m_PintMark.setCenter(D3DXVECTOR3( 128.0f, 32.0f, 0.0f ));
		}
		m_bPlayerPass	= true;	//�ʉ߃t���O�����Ă�
		i_UpdatePacket.SearchWaveAndPlay( RCTEXT_SOUND_SE_CHECKPOINT );
	}
}

/*************************************************
�����e�N�X�`���̍��W�w��
*************************************************/
void	CheckPoint::setTexPos( size_t i_ActiveItem, float fTexPosY ){
	float	wide	= 0;
	float	height	= 0;
	//CHECK POINT �e�N�X�`��*************************************************************
	wide	= BASE_CLIENT_WIDTH / 50 * m_ItemContainer[ i_ActiveItem ]->vStartPos.x * CHECKPOINT_CHAR_RATE_X;
	height	= ( (m_ItemContainer[ i_ActiveItem ]->vStartPos.y - fTexPosY)
									* CHECKPOINT_CHAR_DOWNSPEED - BASE_CLIENT_HEIGHT ) * (-1.0f) * CHECKPOINT_CHAR_RATE_Y;
	D3DXMATRIX mTexMatrix, mScale, mRot, mPos;
	D3DXMatrixScaling(&mScale,CHECK_POINT_CHAR_SIZE.x,CHECK_POINT_CHAR_SIZE.y,CHECK_POINT_CHAR_SIZE.z);
	D3DXMatrixRotationZ(&mRot,D3DXToRadian(0));
	D3DXMatrixTranslation(&mPos, wide,height,0.0f);
	mTexMatrix	= mPos*mScale*mRot;
	m_PintMark.setMatrix( mTexMatrix );
	//*************************************************************************************
}

/**************************************************************************
 Factory_CheckPoint ��`��
****************************************************************************/
/**************************************************************************
 Factory_CheckPoint::Factory_CheckPoint(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_CheckPoint::Factory_CheckPoint(FactoryPacket* fpac){
		try{

			D3DCOLORVALUE Diffuse = {1.0f,0.0f,0.0f,1.0f};
			D3DCOLORVALUE Specular = {1.0f,0.0f,0.0f,1.0f};
			D3DCOLORVALUE Ambient = {1.0f,0.0f,0.0f,1.0f};
			
			//CheckPoint* pcp ;
			//fpac->m_pVec->push_back(
			//	pcp = new CheckPoint( fpac->pD3DDevice, 100.0f, fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"particle.png" ),)
			//);
			//pcp->add( D3DXVECTOR3(12.0f,45.0f,0.0f) );
			//pcp->add( D3DXVECTOR3(5.0f,120.0f,0.0f) );

		}
		
		catch(...){
			//��throw
			throw;
		}
	}

/**************************************************************************
 Factory_CheckPoint::~Factory_CheckPoint();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_CheckPoint::~Factory_CheckPoint(){
//�Ȃɂ����Ȃ�
	}
}//end of namespace bomberobject.
}//end of namespace wiz.