////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Description.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F�����t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Description ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Description.h"
#include "Factory_Wall.h"

namespace wiz{

/**************************************************************************
 StartSprite ��`��
**************************************************************************/
/**************************************************************************
 StartSprite(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 �p�r�@�F�R���X�g���N�^
 �߂�l�F�Ȃ�
 �S���ҁF������
***************************************************************************/
StartSprite::StartSprite(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				Rect*		Rect)
:SpriteObject( pD3DDevice, pTexture, vScale, g_vZero, vPos, Rect, g_vZero, g_vZero, 0x00FFFFFF )
,m_vPos( vPos )
,m_vScale( vScale )
,m_vRelayPosY( vPos.y + 40.0f )
,m_iTime( 0 )
,m_bFirst( true )
,m_pCoil( NULL )
{
}

/**************************************************************************
 ~StartSprite()
 �p�r�@�F�f�X�g���N�^
 �߂�l�F�Ȃ�
 �S���ҁF������
***************************************************************************/
StartSprite::~StartSprite()
{
	m_pCoil	= NULL;
}

/**************************************************************************
 �֐����FDraw( DrawPacket& i_DrawPacket )
 �p�r�@�F�`��
 �����@�FDrawPacket& i_DrawPacket
 �߂�l�F�Ȃ�
 �S���ҁF������
***************************************************************************/
void	StartSprite::Draw( DrawPacket& i_DrawPacket )
{
	SpriteObject::Draw( i_DrawPacket );
}

/**************************************************************************
 �֐����FUpdate( UpdatePacket& i_UpdatePacket )
 �p�r�@�F�X�V
 �����@�FUpdatePacket& i_UpdatePacket
 �߂�l�F�Ȃ�
 �S���ҁF������
***************************************************************************/
void	StartSprite::Update( UpdatePacket& i_UpdatePacket )
{
	if(m_pCoil == NULL){
		m_pCoil = (PlayerCoil*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(PlayerCoil));
	}

	int		rate	= 0;
	BYTE	ChangeAlpha	= (255/40);

	if( m_vRelayPosY > m_vPos.y ){
		m_vPos.y	+= 1.0f;
		rate		 = 1;
	}
	else if( m_vRelayPosY == m_vPos.y ){
		rate	= 0;
		++m_iTime;
		if( m_iTime > 20 )
			m_vPos.y	+= 1.0f;
	}
	else if( m_vRelayPosY < m_vPos.y ){
		rate	= -1;
		m_vPos.y	+= 1.0f;
	}

	if( rate == 1 ){
		if( m_Color.byteColor.a >= 250 )
			m_Color.byteColor.a	 = 255;
		else
			m_Color.byteColor.a	+= ChangeAlpha;
	}
	else if( rate == -1 ){
		if( m_Color.byteColor.a <= 5 ){
			m_Color.byteColor.a	 = 0;
			++m_iTime;
			if( m_iTime > 40 ){
				if( m_bFirst ){
					m_pCoil->setState( COIL_STATE_START );
					m_bFirst	= false;
				}
			}
		}
		else
			m_Color.byteColor.a	-= ChangeAlpha;
	}

	D3DXMATRIX mScale,mRot,mPos;
	D3DXMatrixScaling(&mScale,m_vScale.x,m_vScale.y,m_vScale.z);
	D3DXMatrixTranslation(&mPos,m_vPos.x,m_vPos.y,m_vPos.z);
	m_mMatrix = mScale * mPos ;
}

/**************************************************************************
 Description ��`��
****************************************************************************/
/**************************************************************************
 Description::Description(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	LPDIRECT3DTEXTURE9 pTexture,	//�e�N�X�`��
	wiz::OBJID id					//�I�u�W�F�N�g�̎��
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
 �S���F������
***************************************************************************/
Description::Description( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture, wiz::OBJID id)
	:PrimitiveBox(pD3DDevice,
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					id,
					pTexture)
	,m_pCamera( NULL )
	,m_pCoil( NULL )
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));

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
//// �p�r       �F~Description;
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F
//// ����       �F
//// �ߒl       �F����
//// �S����     �F���� �g�I��
//// ���l       �F
Description::~Description(){
	m_pCamera  = NULL ;
	m_pCoil    = NULL ;
	SafeDeletePointerMap( m_ItemMap_Desc );
	m_ItemMap_Desc.clear();
	m_ItemMap_Target.clear();
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
void Description::Draw(DrawPacket& i_DrawPacket)
{
	multimap<float,DescItem*>::iterator it = m_ItemMap_Target.begin();
	while(it != m_ItemMap_Target.end()){
		if(it->second->m_bDisplay){
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
				i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it->second->m_Matrix);
				//�R�������b�V����Draw()���Ă�
				CommonMesh::Draw(i_DrawPacket);
				i_DrawPacket.pD3DDevice->SetTexture(0,0);
				//�X�e�[�W�����ɖ߂�
				i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
			}
			else{
			//�e�N�X�`�����Ȃ��ꍇ
				// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
				i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it->second->m_Matrix);
				//�R�������b�V����Draw()���Ă�
				CommonMesh::Draw(i_DrawPacket);
			}
		}
		++it;
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
void Description::Update( UpdatePacket& i_UpdatePacket ){
	if(m_pCamera == NULL){
		m_pCamera = (Camera*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CAMERA);
	}
	if(m_pCoil == NULL){
		m_pCoil = (PlayerCoil*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(PlayerCoil));
	}

	m_ItemMap_Target.clear();
	multimap<float,DescItem*>::iterator it = m_ItemMap_Desc.begin();
	while(it != m_ItemMap_Desc.end()){
		if( ( +(it->first - m_pCamera->getEye().y) <= DRAWING_RANGE) && ( +(it->first - m_pCamera->getEye().y) >= -DRAWING_RANGE ) ){
			m_ItemMap_Target.insert(multimap<float,DescItem*>::value_type(it->second->m_vPos.y,it->second));
		}
		++it;
	}

	multimap<float,DescItem*>::iterator it2 = m_ItemMap_Target.begin();
	while(it2 != m_ItemMap_Target.end()){

		//*******************************************************
		//�`�悷�邩�ۂ�
		COIL_STATE Buf = m_pCoil->getState() ;
		if( ( Buf == it2->second->m_State )
							&& it2->second->m_bCanDisplay ){
			it2->second->m_bDisplay	= true;
		}
		else if( it2->second->m_bDisplay ){
			it2->second->m_bDisplay		= false;
			it2->second->m_bCanDisplay	= false;
		}
		//********************************************************

		//�v�Z��Update��
		//�g��k��
		D3DXMATRIX mScale;
		D3DXMatrixIdentity(&mScale);
		D3DXMatrixScaling(&mScale,
			it2->second->m_vScale.x,it2->second->m_vScale.y,it2->second->m_vScale.z);
		//��]
		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationQuaternion(&mRot,&it2->second->m_vRot);
		//�ړ��p
		D3DXMATRIX mMove;
		D3DXMatrixIdentity(&mMove);
		D3DXMatrixTranslation(&mMove,
			it2->second->m_vPos.x,it2->second->m_vPos.y,it2->second->m_vPos.z);
		//�~�b�N�X�s��
		it2->second->m_Matrix = mScale * mRot * mMove;
		//�}�e�B���A���ݒ�
		m_Material = it2->second->m_Material;

		++it2;
	}
}

/////////////////// ////////////////////
//// �p�r       �Fvoid AddDesc( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F�֐�
//// �p�r       �FDesc�̒ǉ�
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
////		    �F  D3DXVECTOR3 &vScale				//�g��k��
////		    �F  D3DXVECTOR3 &vRot				//��]�p
////		    �F  D3DXVECTOR3 &vPos				//�ʒu
////            �F  D3DCOLORVALUE& Diffuse,			//�f�B�t���[�Y�F
////            �F  D3DCOLORVALUE& Specular,		//�X�y�L�����F
////            �F  D3DCOLORVALUE& Ambient,			//�A���r�G���g�F
//// �ߒl       �F����
//// �S����     �F������
//// ���l       �F
void Description::AddDesc(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,COIL_STATE state,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
{
	DescItem* pItem = new DescItem;
	pItem->m_vScale = vScale;
	pItem->m_vPos	= vPos;
	pItem->m_State	= state;
	pItem->m_bCanDisplay	= true;
	pItem->m_bDisplay		= false;
    ::ZeroMemory(&pItem->m_Material,sizeof(D3DMATERIAL9));
	pItem->m_Material.Diffuse = Diffuse;
	pItem->m_Material.Specular = Specular;
	pItem->m_Material.Ambient = Ambient;
	//��]�̏�����
	D3DXQuaternionRotationYawPitchRoll(&pItem->m_vRot,
			D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z));

	m_ItemMap_Desc.insert(multimap<float,DescItem*>::value_type(pItem->m_vPos.y,pItem));
}

/**************************************************************************
 Factory_Result ��`��
****************************************************************************/
/**************************************************************************
 Factory_Result::Factory_Description(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Description::Factory_Description(FactoryPacket* fpac){
	try{
 		D3DCOLORVALUE DescDiffuse = {1.0f,1.0f,1.0f,0.0f};
		D3DCOLORVALUE DescSpecular = {0.0f,0.0f,0.0f,0.0f};
		D3DCOLORVALUE DescAmbient = {1.0f,1.0f,1.0f,0.0f};

		Description* Desc = new Description(fpac->pD3DDevice,
			fpac->m_pTexMgr->addTexture(fpac->pD3DDevice,L"setumei_Start.png"));

		Desc->AddDesc(D3DXVECTOR3(10.0f,4.0f,0.0f),
					  D3DXVECTOR3(0.0f,0.0f,0.0f),
					  D3DXVECTOR3(10.0f,16.0f,-0.5f),
					  COIL_STATE_START,
					  DescDiffuse,
					  DescSpecular,
					  DescAmbient);

		fpac->m_pVec->push_back(Desc);

		//�X�^�[�g���S
		fpac->m_pVec->push_back(
			new StartSprite(
					fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"StartRogo.png" ),
					D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),
					D3DXVECTOR3( 300.0f, 200.0f, 0.0f ),
					&Rect( 0, 0, 240, 64 )
			)	
		);

	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 Factory_Result::~Factory_Description();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Description::~Factory_Description(){
    //�Ȃɂ����Ȃ�
}

}


//end of namespace wiz.
