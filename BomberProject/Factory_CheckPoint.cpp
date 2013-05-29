////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_CheckPoint.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_CheckPoint ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_CheckPoint.h"
#include "Factory_Player.h"
#include "BassItems.h"
const float CHECK_POINT_RADIUS = 0.25f ;
const float EFFECT_SIZE	= 2.0f;
D3DCOLORVALUE CHECKPOINTCOLOR = { 1.0f, 1.0f, 1.0f, 1.0f } ;
namespace wiz{

/**************************************************************************
 CheckEffect ��`��
****************************************************************************/
/**************************************************************************
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
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));

	D3DCOLORVALUE Diffuse = {1.0f,1.0f,0.0f,0.0f};
	D3DCOLORVALUE Specular = {0.0f,0.0f,0.0f,0.0f};
	D3DCOLORVALUE Ambient = {1.0f,1.0f,0.0f,0.0f};

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
	for( int i = 1; i <= m_Num; i++ ){
		update( i );

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
void CheckEffect::update( int i ){

	m_vPos.x	= float(i*2-1);

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

	//m_fWide	-= 1;
	if( m_fWide > 0.0f )
		Reduction();
}

/*************************************
�֐����@�F
�p�r�@�@�F�T�C�Y�ύX
�J�e�S���F
�����@�@�F
�߂�l�@�F
�S���ҁ@�F������
���l�@�@�F
*************************************/
void	CheckEffect::Reduction(){
	float	rate = m_fWide / m_fHight;

	m_fWide		-= 0.001f*rate;
	m_fHight	-= 0.001f;
}

/****************************************************************************
****************************************************************************/
CheckPoint::CheckPoint( LPDIRECT3DDEVICE9 pD3DDevice, float fLength, wiz::OBJID id  )
: Cylinder( pD3DDevice, CHECK_POINT_RADIUS, CHECK_POINT_RADIUS, fLength, g_vZero, D3DXVECTOR3( 0.0f,D3DXToRadian( 90.0f )
		   , 0.0f ), CHECKPOINTCOLOR, D3DCOLORVALUE(), CHECKPOINTCOLOR, id, false, NULL, 18) 
, m_pCoil( NULL )
, m_pCamera( NULL )
, m_pEffect( NULL )
, m_ActiveItem( NULL )
, m_Color( CHECKPOINTCOLOR )
, m_Thicken( 1.0f )
, m_Length( fLength )
{
}
CheckPoint::~CheckPoint(){
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
	if( !m_pCoil   ) m_pCoil   = (PlayerCoil*)SearchObjectFromTypeID( i_UpdatePacket.pVec, typeid(PlayerCoil) );
	if( !m_pCamera ) m_pCamera = (    Camera*)SearchObjectFromID( i_UpdatePacket.pVec, OBJID_SYS_CAMERA );
	
	if( m_pCoil && m_ActiveItem < m_ItemContainer.size()){
		float fPosY		= m_ItemContainer[ m_ActiveItem ]->fPosY;
		float fCoilPosY = m_pCoil->getPos().y;
		if(fPosY <= fCoilPosY){
			m_pCoil->setStartPos(m_ItemContainer[ m_ActiveItem ]->vStartPos);
			m_ActiveItem++ ;
			m_pEffect	= new CheckEffect( i_UpdatePacket.pD3DDevice, m_pCoil->getPos(),m_Length,
					i_UpdatePacket.pTxMgr->addTexture( i_UpdatePacket.pD3DDevice, L"media/Textures/particle.png") );
			if(m_ActiveItem <= m_ItemContainer.size()) return ;
		}
	}

	if( m_pEffect != NULL ){
		m_pEffect->Update( i_UpdatePacket );
	}

	Blink();
	m_Color.b = 0;
	m_Material.Diffuse	= m_Color;
	m_Material.Ambient	= m_Color;
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


		float DrawBeginLength = m_pCamera->getPosY() + DRAW_TOLERANCE ;
		if( DrawBeginLength > m_ItemContainer[ m_ActiveItem ]->fPosY ){
			m_BasePos = D3DXVECTOR3( m_pCamera->getAt().x, m_ItemContainer[ m_ActiveItem ]->fPosY,0.0f) ;
			CalcWorldMatrix();
			Cylinder::Draw( i_DrawPacket );
			
			OBB obb = OBB( m_BasePos, m_BaseQt, m_BaseScale );
			//DrawOBB(i_DrawPacket);
			//m_pCoil->HitTestWall();
		}
	}

	if( m_pEffect != NULL ){
		m_pEffect->Draw( i_DrawPacket );
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
			
			CheckPoint* pcp ;
			fpac->m_pVec->push_back(
				pcp = new CheckPoint( fpac->pD3DDevice, 100.0f)
			);
			pcp->add( D3DXVECTOR3(12.0f,45.0f,0.0f) );
			pcp->add( D3DXVECTOR3(5.0f,120.0f,0.0f) );

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
}//end of namespace wiz.