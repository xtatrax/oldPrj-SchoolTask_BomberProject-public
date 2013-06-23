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
const float EFFECT_SIZE	= 2.0f;
const D3DXVECTOR3 CHECK_POINT_CHAR_SIZE = D3DXVECTOR3(1.0f,1.0f,0.0f);
D3DCOLORVALUE CHECKPOINTCOLOR = { 0.5f, 1.0f, 0.5f, 0.5f } ;
D3DCOLORVALUE CHECKPOINTCOLOR_CHAR = { 1.0f, 1.0f, 1.0f, 1.0f } ;

const	float	CHECKPOINT_CHAR_DOWNSPEED	= 20.0f;
const	float	CHECKPOINT_CHAR_RATE_Y		= (1.0f/CHECK_POINT_CHAR_SIZE.y);
const	float	CHECKPOINT_CHAR_RATE_X		= (1.0f/CHECK_POINT_CHAR_SIZE.x);

namespace wiz{
namespace bomberobject{

/**************************************************************************
 CheckEffect ��`��
****************************************************************************/
/************************************************************************class MouseCursor : public Box , public  PrimitiveSprite{
**
 CheckEffect::CheckEffect(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	LPDIRECT3DTEXTURE9 pTexture,	//�e�N�X�`��
	wiz::OBJID id					//�I�u�W�F�N�g�̎��
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
 �S���F������
***************************************************************************/
CheckEffect::CheckEffect(LPDIRECT3DDEVICE9 pD3DDevice,
						D3DXVECTOR3 vPos,
						float		fLength,
						LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id)
	:PrimitiveBox(pD3DDevice,
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					id,
					pTexture)
,m_vPos( vPos )
,m_Num( (int)(fLength) )
,m_fWide( EFFECT_SIZE*4 )
,m_fHight( EFFECT_SIZE )
,m_bMark( false )
,m_bStart( false )
,m_bCreating( true )
,m_pCoil( NULL )
{
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

	for( int i = 0; i < DRAWING_NUMBER; i++ ){
		m_fPosXArr[i]	= float(i*2);
	}
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
//// �S����     �F������
//// ���l       �F
void CheckEffect::Draw(DrawPacket& i_DrawPacket)
{
	//�`�悷�����ݒ�
	int	num	= 0;
	if( m_bMark )
		num	= 1;
	else
		num	= DRAWING_NUMBER;

	for( int i = 0; i < num; i++ ){
		//update�ŕ`��ʒu������
		update( i ,i_DrawPacket);

		//�e�N�X�`��������ꍇ
		if(m_pTexture){
			DWORD wkdword;
			//���݂̃e�N�X�`���X�e�[�^�X�𓾂�
			i_DrawPacket.pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
			//�X�e�[�W�̐ݒ�
			i_DrawPacket.pD3DDevice->SetTexture(0,m_pTexture);
			//�f�t�B�[�Y�F�ƃe�N�X�`�����|�����킹��ݒ�
			i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
			i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
			i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

			//i_DrawPacket.pD3DDevice->SetFVF(PlateFVF);
			// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_Matrix);
			//�R�������b�V����Draw()���Ă�
			CommonMesh::Draw(i_DrawPacket);
			i_DrawPacket.pD3DDevice->SetTexture(0,0);
			//�X�e�[�W�����ɖ߂�
			i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
		}
		else{
		//�e�N�X�`�����Ȃ��ꍇ
			// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_Matrix);
			//�R�������b�V����Draw()���Ă�
			CommonMesh::Draw(i_DrawPacket);
		}
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
void CheckEffect::update( int i ,DrawPacket& i_DrawPacket){

	if( !m_pCoil   ) m_pCoil   = (PlayerCoil*)SearchObjectFromID( i_DrawPacket.pVec, OBJID_3D_COIL );
	//�X�^�[�g�ʒu�ɃG�t�F�N�g���o����
	if( !m_bMark ){
		if( m_fWide > 0.0f ){
			if( m_bStart ){
				if( m_pCoil != NULL ){
					Pos_Update(i);
				}
				Reduction();
			}
		}
		else{
			m_bMark	= true;
			m_Material.Ambient.r	= 0;
			m_Material.Ambient.g	= 0;
			m_Material.Ambient.b	= 0;
		}
		m_vPos.x	= m_fPosXArr[i];
	}
	else{
		if( m_pCoil != NULL )
			m_vPos	= m_pCoil->getStartPos();
		if( m_fWide < EFFECT_SIZE*3 )
			Expansion();
	}
	//�v�Z��Update��
	//�g��k��
	D3DXMATRIX mScale;
	D3DXMatrixIdentity(&mScale);
	D3DXMatrixScaling( &mScale, m_fWide, m_fHight, 0.0f );
	//��]
	D3DXMATRIX mRot;
	D3DXMatrixIdentity(&mRot);
	//�ړ��p
	D3DXMATRIX mMove;
	D3DXMatrixIdentity(&mMove);
	D3DXMatrixTranslation(&mMove,m_vPos.x,m_vPos.y,m_vPos.z);
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
void	CheckEffect::Pos_Update( int i ){
	float	MigrationRate	= m_pCoil->getStartPos().x - m_fPosXArr[i];
	//�`�悷�ׂ��ʒu���Z�o
	m_fPosXArr[i]	+= MigrationRate/10.0f + 0.2f;
	if( MigrationRate > 0.0f ){
		m_fPosXArr[i]	+= MigrationRate/10.0f + 0.2f;
		if( m_pCoil->getStartPos().x - m_fPosXArr[i] < 0.0f )
			m_fPosXArr[i]	= m_pCoil->getStartPos().x;
	}
	else if( MigrationRate < 0.0f ){
		m_fPosXArr[i]	+= MigrationRate/10.0f - 0.2f;
		if( m_pCoil->getStartPos().x - m_fPosXArr[i] > 0.0f )
			m_fPosXArr[i]	= m_pCoil->getStartPos().x;
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
void	CheckEffect::Reduction(){
	float	rate = m_fWide / m_fHight;

	m_fWide		-= 0.002f*rate;
	m_fHight	-= 0.002f;
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
	m_fWide		+= 0.08f;
	m_fHight	+= 0.08f;

	//float rate	= (EFFECT_SIZE*3) / 0.04f;

	//m_Material.Ambient.r	+= rate;
	//m_Material.Ambient.g	+= rate;
	//m_Material.Ambient.b	+= rate;
	m_Material.Ambient		=  CHECKPOINTCOLOR;
}

/****************************************************************************
CheckPoint ��`��
****************************************************************************/
CheckPoint::CheckPoint( LPDIRECT3DDEVICE9 pD3DDevice, float fLength,LPDIRECT3DTEXTURE9 pTexture,LPDIRECT3DTEXTURE9 pTexture2,LPDIRECT3DTEXTURE9 pTexture3, wiz::OBJID id  )
: Cylinder( pD3DDevice, CHECK_POINT_RADIUS, CHECK_POINT_RADIUS, fLength, g_vZero, D3DXVECTOR3( 0.0f,D3DXToRadian( 90.0f )
		   , 0.0f ), CHECKPOINTCOLOR_CHAR, D3DCOLORVALUE(), CHECKPOINTCOLOR_CHAR, id, false, NULL, 18) 
, m_pCoil( NULL )
, m_pCamera( NULL )
, m_ActiveItem( NULL )
, m_pTime( NULL )
, m_Color( CHECKPOINTCOLOR )
, m_Thicken( 1.0f )
, m_Length( fLength )
, m_pTexture( pTexture )
,m_pTexturePoint( pTexture2 )
, m_pTextureLast( pTexture3 ) 
{
	m_pEffect	= new CheckEffect( pD3DDevice, g_vZero, fLength, pTexture );
	m_pEffect2	= NULL;
	//m_pPintMark = new Box(pD3DDevice,CHECK_POINT_CHAR_SIZE,g_vZero,g_vZero,CHECKPOINTCOLOR, D3DCOLORVALUE(), CHECKPOINTCOLOR,OBJID_3D_BOX,false,pTexture2);
	m_pPintMark = new SpriteObject( pD3DDevice, pTexture2, CHECK_POINT_CHAR_SIZE, g_vZero, g_vZero,
									Rect( 0, 0, 512, 64 ), D3DXVECTOR3( 256.0f, 32.0f, 0.0f ), D3DXVECTOR3( 0.0f, -87.0f, 0.0f ));
}
CheckPoint::~CheckPoint(){
	m_pCoil		= NULL ;
	m_pCamera	= NULL ;
	m_pTime		= NULL ;
	SAFE_DELETE( m_pEffect );
	SAFE_DELETE( m_pEffect2 );
	m_pPintMark	= NULL;
	SafeDeletePointerContainer( m_ItemContainer ) ;
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
	if( !m_pTime )		m_pTime	= ( TimeScore* )SearchObjectFromID( i_UpdatePacket.pVec, OBJID_UI_TIME );
	if( !m_pCoil   )	m_pCoil	= (PlayerCoil*)SearchObjectFromID( i_UpdatePacket.pVec, OBJID_3D_COIL	) ;
	if( !m_pCamera ){
		m_pCamera = (    Camera*)SearchObjectFromID( i_UpdatePacket.pVec, OBJID_SYS_CAMERA ) ;
		m_fInitPosY	= 	m_pCamera->getPosY();
	}
	//if( m_ActiveItem >= m_ItemContainer.size() ){
	//	m_ActiveItem = m_ItemContainer.size() -1;
	//}
	float	wide	= 0;
	float	height	= 0;
	if( m_pCoil && m_ActiveItem < m_ItemContainer.size()){
		float fPosY		= m_ItemContainer[ m_ActiveItem ]->fPosY;
		float fCoilPosY = m_pCoil->getPos().y;

		float	fTexPosY	= m_pCamera->getPosY() - m_fInitPosY;

		//CHECK POINT �e�N�X�`��*************************************************************
		//float	wide;
		//if(m_ActiveItem == m_ItemContainer.size()-1){
		//	wide	= BASE_CLIENT_WIDTH / 50 * m_ItemContainer[ m_ActiveItem ]->vStartPos.x * CHECKPOINT_CHAR_RATE_X;
		//}else{
		//	wide	= BASE_CLIENT_WIDTH / 50 * m_ItemContainer[ m_ActiveItem ]->vStartPos.x * CHECKPOINT_CHAR_RATE_X;
		//}
		wide	= BASE_CLIENT_WIDTH / 50 * m_ItemContainer[ m_ActiveItem ]->vStartPos.x * CHECKPOINT_CHAR_RATE_X;
		height	= ( (m_ItemContainer[ m_ActiveItem ]->vStartPos.y - fTexPosY)
										* CHECKPOINT_CHAR_DOWNSPEED - BASE_CLIENT_HEIGHT ) * (-1.0f) * CHECKPOINT_CHAR_RATE_Y;
		Debugger::DBGSTR::addStr(L" �Ȃ�%d\n",m_ActiveItem);
		Debugger::DBGSTR::addStr(L" �܂�����%d\n",m_ItemContainer.size());
		D3DXMATRIX mTexMatrix, mScale, mRot, mPos;
		D3DXMatrixScaling(&mScale,CHECK_POINT_CHAR_SIZE.x,CHECK_POINT_CHAR_SIZE.y,CHECK_POINT_CHAR_SIZE.z);
		D3DXMatrixRotationZ(&mRot,D3DXToRadian(0));
		D3DXMatrixTranslation(&mPos, wide,height,0.0f);
		mTexMatrix	= mPos*mScale*mRot;
		m_pPintMark->setMatrix( mTexMatrix );
		//*************************************************************************************

		if(fPosY <= fCoilPosY){
			m_pCoil->setStartPos(m_ItemContainer[ m_ActiveItem ]->vStartPos);
			m_ActiveItem++;
			m_pCoil->setRecordTime();
			m_pTime->setTime();
			if(m_ActiveItem == m_ItemContainer.size()-1){
				m_pPintMark->setTexture(m_pTextureLast);
				m_pPintMark->setCenter(D3DXVECTOR3( 128.0f, 32.0f, 0.0f ));
			}
			if( m_pEffect != NULL ){
				if( m_pEffect2 != NULL ){
					if( m_pEffect->getMark() ){
						m_pEffect2->setStart(true);
					}
					else{
						m_pEffect->setStart(true);
					}
				}
				else{
					m_pEffect->setStart(true);
				}
			}
			i_UpdatePacket.SearchWaveAndPlay( RCTEXT_SOUND_SE_CHECKPOINT );
			if(m_ActiveItem >= m_ItemContainer.size()) return ;
			fPosY		= m_ItemContainer[ m_ActiveItem ]->fPosY;
		}


		D3DXVECTOR3	pos	= D3DXVECTOR3(0.0f,m_ItemContainer[ m_ActiveItem ]->fPosY,0.0f);
		if( m_pEffect != NULL ){
			if( !(m_pEffect->getStart()) ){
				m_pEffect->setPosY( m_ItemContainer[ m_ActiveItem ]->fPosY );
		}else{
				if( m_pEffect->getCreating() ){
					m_pEffect2	= new CheckEffect( i_UpdatePacket.pD3DDevice, 
								pos, m_Length, m_pTexture);
					m_pEffect->setCreating( false );
				}
			}
			m_pEffect->Update( i_UpdatePacket );
		}

		if( m_pEffect2 != NULL ){
			if( !(m_pEffect2->getStart()) )
				m_pEffect2->setPosY( m_ItemContainer[ m_ActiveItem ]->fPosY );
			else{
				if( m_pEffect2->getCreating() ){
					m_pEffect	= new CheckEffect( i_UpdatePacket.pD3DDevice, 
								pos, m_Length, m_pTexture);
					m_pEffect2->setCreating( false );
				}
			}
			m_pEffect2->Update( i_UpdatePacket );
		}
	}
	else{
		wide	= BASE_CLIENT_WIDTH / 50 * m_ItemContainer[ m_ActiveItem-1 ]->vStartPos.x * CHECKPOINT_CHAR_RATE_X;
		height	= ( (m_ItemContainer[ m_ActiveItem-1 ]->vStartPos.y - (m_pCamera->getPosY() - m_fInitPosY))
										* CHECKPOINT_CHAR_DOWNSPEED - BASE_CLIENT_HEIGHT ) * (-1.0f) * CHECKPOINT_CHAR_RATE_Y;
		D3DXMATRIX mTexMatrix, mScale, mRot, mPos;
		D3DXMatrixScaling(&mScale,CHECK_POINT_CHAR_SIZE.x,CHECK_POINT_CHAR_SIZE.y,CHECK_POINT_CHAR_SIZE.z);
		D3DXMatrixRotationZ(&mRot,D3DXToRadian(0));
		D3DXMatrixTranslation(&mPos, wide,height,0.0f);
		mTexMatrix	= mPos*mScale*mRot;
		m_pPintMark->setMatrix( mTexMatrix );

	}

	//Blink();
};

/////////////////// ////////////////////
//// �p�r       �Fvirtual void Draw( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F�������z�֐�
//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
////            �F  �� Tempus2*            i_DrawPacket.pTime	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
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
			
			//	
			m_BasePos = D3DXVECTOR3( m_pCamera->getAt().x, m_ItemContainer[ m_ActiveItem ]->fPosY,0.0f) ;

			//	:�@���b�Z�[�W�H��`��
			m_pPintMark->Draw(i_DrawPacket);

			//	:�@Matrix�̌v�Z
			CalcWorldMatrix();
			//Cylinder::Draw( i_DrawPacket );
		}

		Debugger::DBGSTR::addStr(L"m_ActiveItem = %d\n",m_ActiveItem);
	}
	else/* if(m_ActiveItem == m_ItemContainer.size()-1)*/{
		Debugger::DBGSTR::addStr(L"m_ActiveItem = %d\n",m_ActiveItem);
		Debugger::DBGSTR::addStr(L"�炷��");
		m_pPintMark->Draw(i_DrawPacket);
	}

	if( m_pEffect != NULL ){
		m_pEffect->Draw( i_DrawPacket );
	}
	if( m_pEffect2 != NULL ){
		m_pEffect2->Draw( i_DrawPacket );
	}
};

/////////////////// ////////////////////
//// �p�r       �Fvirtual void Blink()
//// �J�e�S��   �F�������z�֐�
//// �p�r       �F�I�u�W�F�N�g�𖾖ł���
//// ����       �F�Ȃ��@
//// �ߒl       �F����
//// �S����     �F������
//// ���l       �F
////            �F
////
void	CheckPoint::Blink(){
	m_Color.a	-=	0.03f * m_Thicken + 0.01f;

	if( m_Color.a < 0.3f ){
		m_Color.a	 =  0.3f;
		m_Thicken	*= -1.0f;
	}
	else if( m_Color.a > 0.9f ){
		m_Color.a	 =  0.9f;
		m_Thicken	*= -1.0f;
	}
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