////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Item.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F�A�C�e���t�@�N�g���[
//					��
//	namespace wiz;
//		class Item ;
//		class Bar ;
//		class Factory_Item ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "BassItems.h"
#include "Factory_Item.h"
#include "Factory_Player.h"

namespace wiz{




/**************************************************************************
 Gage ��`��
***************************************************************************/
/************************************************************************
 �֐���     �FGage::Gage(
                LPDIRECT3DDEVICE9 pD3DDevice,
                LPDIRECT3DTEXTURE9 pTex,
                D3DXVECTOR3 &vScale,
                D3DXVECTOR3 &vRot,
                D3DXVECTOR3 &vPos,
                D3DXVECTOR3 &vDirOffset,
                RECT* vRect,
                wiz::OBJID id
				)
�J�e�S���F�R���X�g���N�^
�p�r�@�@�FLPDIRECT3DDEVICE9 pD3DDevice   // �f�o�C�X
�����@�@�FLPDIRECT3DTEXTURE9 pTex        // �e�N�X�`���\
�@�@�@�@�FD3DXVECTOR3 &vScale            // �L�k
�@�@�@�@�FD3DXVECTOR3 &vRot              // ��]
�@�@�@�@�FD3DXVECTOR3 &vPos              // �ʒu
�@�@�@�@�FD3DXVECTOR3 &vDirOffset        // �`��I�t�Z�b�g
�@�@�@�@�FRECT* vRect                    // �`��͈�
�@�@�@�@�FRECT* vRect2                   // �`��͈�
�@�@�@�@�Fwiz::OBJID id                  // ID
�߂�l�@�F
�S���ҁ@�F������
���l�@�@�F
*************************************************************************/
Gage::Gage(
	LPDIRECT3DDEVICE9 pD3DDevice,
	LPDIRECT3DTEXTURE9 pTex,
	D3DXVECTOR3 &vScale,
	D3DXVECTOR3 &vRot,
	D3DXVECTOR3 &vPos,
	D3DXVECTOR3 &vDirOffset,
	RECT* vRect,
	RECT* vRect2,
	wiz::OBJID id
)
:SpriteObject(pD3DDevice,pTex,vScale,vRot,vPos,
	vRect,g_vZero,vDirOffset,0xFFFFFFFF,id)
,m_Rect( vRect )
,m_Rect2( vRect2 )

{
}

/****************************************
�֐����@�@�Fvoid Gage::Recovery()
�J�e�S���@�F�֐�
�p�r�@�@�@�F�G�l���M�[�[�U
�����@�@�@�Fint i_iValue		//���炷�l
         �@�Fint i_iMaxValue	//�Q�[�W�̍ő�l
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
*****************************************/
void Gage::Recovery( int i_iValue, int i_iMaxValue ){
	if(m_Rect2.right < i_iMaxValue){
		m_pRect->right	+= i_iValue;
		if( m_Rect2.right > i_iMaxValue )
			m_pRect->right	= i_iMaxValue;
	}
}
/*****************************************
 �֐����@�@�Fvoid Gage::Consume()
 �J�e�S���@�F�֐�
 �p�r�@�@�@�F�G�l���M�[����
 �����@�@�@�F
 �߂�l�@�@�F
 �S���ҁ@�@�F������
 ���l�@�@�@�F
 *****************************************/
void Gage::Consume( int i_iValue ){
	if(m_Rect2.right > 0){
		m_Rect2.right	-= i_iValue;
		if(m_Rect2.right < 0){
			m_Rect2.right	= 0;
		}
	}
}

/**************************************************************
�֐����@�@�Fvoid Gage::Draw(DrawPacket &i_DrawPacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�I�u�W�F�N�g�̕`��
�����@�@�@�FDrawPacket &i_DrawPacket    //�`��p�̃f�[�^�������
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
***************************************************************/
void Gage::Draw(DrawPacket& i_DrawPacket){
	//�g�̕`��
	m_pRect	= m_Rect;
	SpriteObject::Draw( i_DrawPacket );
	//�Q�[�W�̕`��
	m_pRect	= m_Rect2;
	SpriteObject::Draw( i_DrawPacket );
}

/**************************************************************************
 SuperGage ��`��
***************************************************************************/
/************************************************************************
 �֐���     �FSuperGage::SuperGage(
                LPDIRECT3DDEVICE9 pD3DDevice,
                LPDIRECT3DTEXTURE9 pTex,
                D3DXVECTOR3 &vScale,
                D3DXVECTOR3 &vRot,
                D3DXVECTOR3 &vPos,
                D3DXVECTOR3 &vDirOffset,
                RECT* vRect,
                wiz::OBJID id
				)
�J�e�S���F�R���X�g���N�^
�p�r�@�@�FLPDIRECT3DDEVICE9 pD3DDevice   // �f�o�C�X
�����@�@�FLPDIRECT3DTEXTURE9 pTex        // �e�N�X�`���\
�@�@�@�@�FD3DXVECTOR3 &vScale            // �L�k
�@�@�@�@�FD3DXVECTOR3 &vRot              // ��]
�@�@�@�@�FD3DXVECTOR3 &vPos              // �ʒu
�@�@�@�@�FD3DXVECTOR3 &vDirOffset        // �`��I�t�Z�b�g
�@�@�@�@�FRECT* vRect                    // �`��͈�
�@�@�@�@�FRECT* vRect2                   // �`��͈�
�@�@�@�@�Fwiz::OBJID id                  // ID
�߂�l�@�F
�S���ҁ@�F������
���l�@�@�F
*************************************************************************/
SuperGage::SuperGage(
	LPDIRECT3DDEVICE9 pD3DDevice,
	LPDIRECT3DTEXTURE9 pTex,
	D3DXVECTOR3 &vScale,
	D3DXVECTOR3 &vRot,
	D3DXVECTOR3 &vPos,
	RECT* vRect,
	RECT* vRect2,
	wiz::OBJID id
)
:Gage(pD3DDevice,pTex,vScale,vRot,vPos,g_vZero,
	vRect,vRect2)
{
}

/**************************************************************
�֐����@�@�Fvoid SuperGage::Draw(DrawPacket &i_DrawPacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�I�u�W�F�N�g�̕`��
�����@�@�@�FDrawPacket &i_DrawPacket    //�`��p�̃f�[�^�������
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
***************************************************************/
void SuperGage::Draw(DrawPacket& i_DrawPacket){
	Gage::Draw( i_DrawPacket );
}

/**************************************************************************
 MagneticGage_N ��`��
***************************************************************************/
/************************************************************************
 �֐���     �FMagneticGage_N::MagneticGage_N(
                LPDIRECT3DDEVICE9 pD3DDevice,
                LPDIRECT3DTEXTURE9 pTex,
                D3DXVECTOR3 &vScale,
                D3DXVECTOR3 &vRot,
                D3DXVECTOR3 &vPos,
                D3DXVECTOR3 &vDirOffset,
                RECT* vRect,
                wiz::OBJID id
				)
�J�e�S���F�R���X�g���N�^
�p�r�@�@�FLPDIRECT3DDEVICE9 pD3DDevice   // �f�o�C�X
�����@�@�FLPDIRECT3DTEXTURE9 pTex        // �e�N�X�`���\
�@�@�@�@�FD3DXVECTOR3 &vScale            // �L�k
�@�@�@�@�FD3DXVECTOR3 &vRot              // ��]
�@�@�@�@�FD3DXVECTOR3 &vPos              // �ʒu
�@�@�@�@�FRECT* vRect                    // �`��͈�
�@�@�@�@�FRECT* vRect2                   // �`��͈�
�@�@�@�@�Fwiz::OBJID id                  // ID
�߂�l�@�F
�S���ҁ@�F������
���l�@�@�F
*************************************************************************/
MagneticGage_N::MagneticGage_N(
	LPDIRECT3DDEVICE9	pD3DDevice,
	LPDIRECT3DTEXTURE9	pTex,
	D3DXVECTOR3			&vScale,
	D3DXVECTOR3			&vRot,
	D3DXVECTOR3			&vPos,
	RECT*				vRect,
	RECT*				vRect2,
	wiz::OBJID			id
)
:Gage(pD3DDevice,pTex,vScale,vRot,vPos,g_vZero,
	  vRect,vRect2)

{
}

/**************************************************************
�֐����@�@�Fvoid MagneticGage::Draw(DrawPacket &i_DrawPacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�I�u�W�F�N�g�̕`��
�����@�@�@�FDrawPacket &i_DrawPacket    //�`��p�̃f�[�^�������
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
***************************************************************/
void MagneticGage_N::Draw(DrawPacket& i_DrawPacket){
	Gage::Draw( i_DrawPacket );
}

/**************************************************************************
 MagneticGage_S ��`��
***************************************************************************/
/************************************************************************
 �֐���     �FMagneticGage_S::MagneticGage_S(
                LPDIRECT3DDEVICE9 pD3DDevice,
                LPDIRECT3DTEXTURE9 pTex,
                D3DXVECTOR3 &vScale,
                D3DXVECTOR3 &vRot,
                D3DXVECTOR3 &vPos,
                D3DXVECTOR3 &vDirOffset,
                RECT* vRect,
                wiz::OBJID id
				)
�J�e�S���F�R���X�g���N�^
�p�r�@�@�FLPDIRECT3DDEVICE9 pD3DDevice   // �f�o�C�X
�����@�@�FLPDIRECT3DTEXTURE9 pTex        // �e�N�X�`���\
�@�@�@�@�FD3DXVECTOR3 &vScale            // �L�k
�@�@�@�@�FD3DXVECTOR3 &vRot              // ��]
�@�@�@�@�FD3DXVECTOR3 &vPos              // �ʒu
�@�@�@�@�FRECT* vRect                    // �`��͈�
�@�@�@�@�FRECT* vRect2                   // �`��͈�
�@�@�@�@�Fwiz::OBJID id                  // ID
�߂�l�@�F
�S���ҁ@�F������
���l�@�@�F
*************************************************************************/
MagneticGage_S::MagneticGage_S(
	LPDIRECT3DDEVICE9	pD3DDevice,
	LPDIRECT3DTEXTURE9	pTex,
	D3DXVECTOR3			&vScale,
	D3DXVECTOR3			&vRot,
	D3DXVECTOR3			&vPos,
	RECT*				vRect,
	RECT*				vRect2,
	wiz::OBJID			id
)
:Gage(pD3DDevice,pTex,vScale,vRot,vPos,g_vZero,
	  vRect,vRect2)

{
}

/**************************************************************
�֐����@�@�Fvoid MagneticGage::Draw(DrawPacket &i_DrawPacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�I�u�W�F�N�g�̕`��
�����@�@�@�FDrawPacket &i_DrawPacket    //�`��p�̃f�[�^�������
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
***************************************************************/
void MagneticGage_S::Draw(DrawPacket& i_DrawPacket){
	Gage::Draw( i_DrawPacket );
}

/**************************************************************************
 Item ��`��
****************************************************************************/
/***************************************************************************
�֐����@�@�@�FItem( FactoryPacket* fpac,
                      LPDIRECT3DTEXTURE9 pTexture,
                      wiz::OBJID id )
�J�e�S���@�@�F�R���X�g���N�^
�p�r�@�@�@�@�F
�����@�@�@�@�FFactoryPacket* fpac           // : �f�o�C�X�Ȃ�
�@�@�@�@�@�@�FLPDIRECT3DTEXTURE9 pTexture   // : �e�N�X�`���\
�@�@�@�@�@�@�Fwiz::OBJID id                 // : ID
�߂�l�@�@�@�F
�S���ҁ@�@�@�F������
���l�@�@�@�@�F
****************************************************************************/
Item::Item(FactoryPacket* fpac,LPDIRECT3DTEXTURE9 pTexture, wiz::OBJID id)
	:PrimitiveSphere(fpac->pD3DDevice,
						D3DCOLORVALUE(),
						D3DCOLORVALUE(),
						D3DCOLORVALUE(),
						pTexture
	)
	,m_pPlayerCoil(NULL)
	,m_pSuperGage(NULL)
{
	try{
		//D3DXMatrixIdentity(&m_mMatrix);
        // D3DMATERIAL9�\���̂�0�ŃN���A
        ::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
	}
	catch(...){
		//�ăX���[
		throw;
	}
}
/////////////////// ////////////////////
//// �֐���     �F~Item();
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F�j��
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
Item::~Item(){
	SafeDeletePointerMap( m_ItemMap_All );	
}

/**************************************************************
�֐����@�@�Fvoid Item::Draw(DrawPacket &i_DrawPacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�I�u�W�F�N�g�̕`��
�����@�@�@�FDrawPacket &i_DrawPacket          // �`��p�̂������
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
***************************************************************/
void	Item::Draw(DrawPacket &i_DrawPacket){
	multimap<float,BallItem*>::iterator it = m_ItemMap_All.begin();
	while(it != m_ItemMap_All.end()){
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
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it->second->m_mMatrix);
			//�R�������b�V����Draw()���Ă�
			CommonMesh::Draw(i_DrawPacket);
			i_DrawPacket.pD3DDevice->SetTexture(0,0);
			//�X�e�[�W�����ɖ߂�
			i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
		}
		else{
		//�e�N�X�`�����Ȃ��ꍇ
			// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it->second->m_mMatrix);
			//�R�������b�V����Draw()���Ă�
			CommonMesh::Draw(i_DrawPacket);
		}
		++it;
	}
}

/*******************************************************************
�֐����@�@�Fvoid Item::Update(UpdatePacket& i_UpdatePacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�f�[�^�X�V
�����@�@�@�FUpdatePacket& i_UpdatePacket  // �X�V�p�f�[�^�������
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
********************************************************************/
void	Item::Update(UpdatePacket& i_UpdatePacket)
{
	vector<Object*>	Vec	= *(i_UpdatePacket.pVec);

	if( !m_pPlayerCoil ) m_pPlayerCoil	= (PlayerCoil*)SearchObjectFromTypeID(&Vec,typeid(PlayerCoil));
	if( !m_pSuperGage )	 m_pSuperGage	= (SuperGage*)SearchObjectFromTypeID(&Vec,typeid(SuperGage));

	//�R�C���̈ʒu�擾
	D3DXVECTOR3	cPos	= m_pPlayerCoil->getPos();

	Debugger::DBGSTR::addStr(L"ItemAll = %d\n",m_ItemMap_All.size());
	multimap<float,BallItem*>::iterator it = m_ItemMap_All.begin();
	while(it != m_ItemMap_All.end()){
		if(m_pPlayerCoil->getState() == COIL_STATE_MOVE && !m_pPlayerCoil->getSuperMode()){
			//	: ��������Ώۂ܂ł̃x�N�g�����Z�o
			D3DXVECTOR3	vTargetDir	= cPos - (it->second->m_Pos) ;

			//	: �����ƑΏۂ܂ł̋��������߂�
			double dirX = vTargetDir.x * vTargetDir.x;
			double dirY = vTargetDir.y * vTargetDir.y;
			it->second->m_fDistance	 = (float)sqrt(dirX + dirY);

			//������5�ȓ��Ȃ����Ă���
			if( it->second->m_fDistance < SuctionArea ){
				it->second->m_Pos	+= vTargetDir/**SpeedRate*/ * m_pPlayerCoil->getSpeed();

				//�v���C���[�ƌ���Ȃ��߂��Ȃ�����A����
				if( it->second->m_fDistance < VanishArea ){
					//�G�l���M�[��
					m_pSuperGage->Recovery(RECOVERY_POINT,GAGE_MAX);
					SafeDelete( it->second );
					it = m_ItemMap_All.erase( it );
					continue;
				}
			}
			//�Q�[�W���ő�ɂȂ�����R�C���𖳓G��Ԃ�
			if(m_pSuperGage->getRect2().right >= GAGE_MAX){
				m_pPlayerCoil->setSuperMode(true);	
			}
		}
		//�ړ��p
		D3DXMATRIX mMove, mScale;
		D3DXMatrixIdentity(&mMove);
		D3DXMatrixTranslation(&mMove,
			it->second->m_Pos.x,it->second->m_Pos.y,it->second->m_Pos.z);
		D3DXMatrixScaling(&mScale,
			it->second->m_Size.x,it->second->m_Size.y,it->second->m_Size.z);

		//�}�e�B���A���ݒ�
		m_Material = it->second->m_Material;
		it->second->m_mMatrix	= mScale * mMove;

		it++;
	}
	if(m_pPlayerCoil->getState() == COIL_STATE_MOVE && m_pPlayerCoil->getSuperMode()){
		static float s_fTimeTotal = 0.0f;
		s_fTimeTotal += (float)GAGE_MAX / (float)COIL_SUPER_MODE_TIME * (float)i_UpdatePacket.pTime->getElapsedTime();
		if(s_fTimeTotal >= 1.0f){
			m_pSuperGage->Consume((int)s_fTimeTotal);
			s_fTimeTotal -= (int)s_fTimeTotal;
		}
	}
}

/***********************************************
�֐����@�Fvoid Item::addItem(
                      D3DXVECTOR3 pos,
                      D3DXVECTOR3 size,
                      D3DCOLORVALUE Diffuse,
                      D3DCOLORVALUE Specular, 
                      D3DCOLORVALUE Ambient)
�J�e�S���F�֐�
�p�r�@�@�F�A�C�e���̒ǉ�
�����@�@�FD3DXVECTOR3 pos          //�`��ʒu
�@�@�@�@�FD3DXVECTOR3 size         //�傫��
�@�@�@�@�FD3DCOLORVALUE Diffuse    //
�@�@�@�@�FD3DCOLORVALUE Specular   //
�@�@�@�@�FD3DCOLORVALUE Ambient    //
�߂�l�@�F
�S���ҁ@�F������
���l�@�@�F
***********************************************/
void	Item::addItem(D3DXVECTOR3 pos, D3DXVECTOR3 size,
					  D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient)
{
	try{
		BallItem* bItem = new BallItem;
		bItem->m_Pos = pos;
		bItem->m_Size = size;
		bItem->m_fDistance = 6.0f;
        // D3DMATERIAL9�\���̂�0�ŃN���A
        ::ZeroMemory(&bItem->m_Material,sizeof(D3DMATERIAL9));
		bItem->m_Material.Diffuse = Diffuse;
		bItem->m_Material.Specular = Specular;
		bItem->m_Material.Ambient = Ambient;

		m_ItemMap_All.insert(multimap<float,BallItem*>::value_type(bItem->m_Pos.y,bItem));
	}
	catch(...){
		throw;
	}
}

/**************************************************************************
 Factory_Item ��`��
****************************************************************************/
/**************************************************************************
�֐����@�@�FFactory_Item::Factory_Item( FactoryPacket* fpac );
�J�e�S���@�F�R���X�g���N�^
�p�r�@�@�@�F
�����@�@�@�FFactoryPacket* fpac     // �������̃f�[�^
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
***************************************************************************/
Factory_Item::Factory_Item(FactoryPacket* fpac){
	try{
        D3DCOLORVALUE BallDiffuse = {0.0f,0.7f,0.7f,1.0f};
        D3DCOLORVALUE BallSpecular = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE BallAmbient = {0.0f,0.7f,0.7f,1.0f};
		Item*	it	=	new	Item(fpac,NULL,OBJID_UNK);
		for(int i = 0; i < 7; i++){
			for(int j = 0; j < 50; j++){
				it->addItem(D3DXVECTOR3((float(i)*5.0f+float(rand()%100*0.05f))+1.5f,
										(float(j)*2.75f+float(rand()%100*0.05f))+1.5f,0.0f),
							D3DXVECTOR3(0.5f,0.5f,0.5f),
							BallDiffuse,
							BallSpecular,
							BallAmbient);
			}
		}
		fpac->m_pVec->push_back(it);

		//�X�[�p�[���[�h�p�Q�[�W
		fpac->m_pVec->push_back(
			new SuperGage(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Gauge_Super.png" ),
				D3DXVECTOR3(1.0f,1.0f,0.0f),
				g_vZero,
				D3DXVECTOR3(144.0f,550.0f,0.0f),
				Rect(0,0,512,32),
				Rect(0,32,0,256)
			)
		);

		//���EN�p�Q�[�W
		fpac->m_pVec->push_back(
			new MagneticGage_N(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Gauge_N.png" ),
				D3DXVECTOR3(1.0f,1.0f,0.0f),
				g_vZero,
				D3DXVECTOR3(120.0f,500.0f,0.0f),
				Rect(0,0,256,32),
				Rect(0,32,256,64)
			)
		);
		//���E�pS�Q�[�W
		fpac->m_pVec->push_back(
			new MagneticGage_S(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Gauge_S.png" ),
				D3DXVECTOR3(1.0f,1.0f,0.0f),
				g_vZero,
				D3DXVECTOR3(420.0f,500.0f,0.0f),
				Rect(0,0,256,32),
				Rect(0,32,256,64)
			)
		);
	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 �֐����@�@�FFactory_Item::~Factory_Item();
 �J�e�S���@�F�f�X�g���N�^
 �p�r�@�@�@�F
 �����@�@�@�F
 �߂�l�@�@�F
 �S���ҁ@�@�F������
 ���l�@�@�@�F
***************************************************************************/
Factory_Item::~Factory_Item(){
    //�Ȃɂ����Ȃ�
}

}
//end of namespace wiz.
