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
#include "Factory_Item.h"
#include "Factory_Player.h"
#include "BassItems.h"

namespace wiz{
/**************************************************************************
 Item ��`��
****************************************************************************/
/***************************************************************************
�֐���     �FItem( FactoryPacket* fpac,			//	: �f�o�C�X�Ȃ�
					 LPDIRECT3DTEXTURE9 pTexture,	//	: �e�N�X�`���\
					 wiz::OBJID id )				//	: ID
�p�r       �F�R���X�g���N�^
****************************************************************************/
Item::Item(FactoryPacket* fpac,LPDIRECT3DTEXTURE9 pTexture, wiz::OBJID id)
	:PrimitiveSphere(fpac->pD3DDevice,
						D3DCOLORVALUE(),
						D3DCOLORVALUE(),
						D3DCOLORVALUE(),pTexture)

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

/**************************************************************
�֐���     �Fvoid	 Item::Draw(DrawPacket &i_DrawPacket)
�p�r       �F�I�u�W�F�N�g�̕`��
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
�֐���     �Fvoid	 Item::Update(UpdatePacket& i_UpdatePacket)
�p�r       �F�f�[�^�X�V
********************************************************************/
void	Item::Update(UpdatePacket& i_UpdatePacket)
{
	vector<Object*> Vec	= 	*(i_UpdatePacket.pVec);
	PlayerCoil*	pc	= NULL;
	Bar*		br	= NULL;
	vector<Object*>::size_type sz2 = Vec.size();
	//�R�C���̃|�C���^���擾
	for(vector<Object*>::size_type i = 0;i < sz2;i++){
		const type_info& info = typeid(*(Vec[i]));
		if(info == typeid(PlayerCoil)){
			pc = dynamic_cast<PlayerCoil*>(Vec[i]);
			break;
		}
	}
	//�o�[�̃|�C���^���擾
	for(vector<Object*>::size_type i = 0;i < sz2;i++){
		const type_info& info = typeid(*(Vec[i]));
		if(info == typeid(Bar)){
			br = dynamic_cast<Bar*>(Vec[i]);
			break;
		}
	}
	//�R�C���̈ʒu�擾
	D3DXVECTOR3	cPos	= pc->getPos();

	multimap<float,BallItem*>::iterator it = m_ItemMap_All.begin();
	while(it != m_ItemMap_All.end()){
		//	: ��������Ώۂ܂ł̃x�N�g�����Z�o
		D3DXVECTOR3	vTargetDir	= cPos - (it->second->m_Pos) ;

		//	: �����ƑΏۂ܂ł̋��������߂�
		double dirX = vTargetDir.x * vTargetDir.x;
		double dirY = vTargetDir.y * vTargetDir.y;
		it->second->m_fDistance	 = (float)sqrt(dirX + dirY);

		//Debugger::DBGSTR::addStr(L"ItemAll = %d\n",m_ItemMap_All.size());
		//������5�ȓ��Ȃ����Ă���
		if( it->second->m_fDistance < SuctionArea ){
			it->second->m_Pos	+= vTargetDir*SpeedRate;

			//�v���C���[�ƌ���Ȃ��߂��Ȃ�����A����
			if( it->second->m_fDistance < VanishArea ){
				//�G�l���M�[��
				br->Recovery();
				SafeDelete( it->second );
				it = m_ItemMap_All.erase( it );
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
}

/***********************************************
�֐��� : void	Item::addItem(
					D3DXVECTOR3 pos,		//	: �`��ʒu
					D3DXVECTOR3 size,		//	: �L�k
					D3DCOLORVALUE Diffuse,	//	: 
					D3DCOLORVALUE Specular,	//	: 
					D3DCOLORVALUE Ambient)	//	: 
�p�r   : �A�C�e���̒ǉ�
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
 Bar ��`��
***************************************************************************/
/************************************************************************
 �֐���     �FBar::Bar(
				LPDIRECT3DDEVICE9 pD3DDevice,	//	: �f�o�C�X
				LPDIRECT3DTEXTURE9 pTex,		//	: �e�N�X�`���\
				D3DXVECTOR3 &vScale,			//	: �L�k
				D3DXVECTOR3 &vRot,				//	: ��]
				D3DXVECTOR3 &vPos,				//	: �ʒu
				D3DXVECTOR3 &vDirOffset,		//	: �`��I�t�Z�b�g
				RECT* vRect,					//	: �`��͈�
				wiz::OBJID id 					//	: ID
				)
�p�r       �F�R���X�g���N�^
*************************************************************************/
Bar::Bar(
	LPDIRECT3DDEVICE9 pD3DDevice,
	LPDIRECT3DTEXTURE9 pTex,
	D3DXVECTOR3 &vScale,
	D3DXVECTOR3 &vRot,
	D3DXVECTOR3 &vPos,
	D3DXVECTOR3 &vDirOffset,
	RECT* vRect,
	wiz::OBJID id
)
:SpriteObject(pD3DDevice,pTex,vScale,vRot,vPos,
	vRect,g_vZero,vDirOffset,0xFFFFFFFF,id),m_Time(0)

{
}

/****************************************
�֐���     �Fvoid Bar::Recovery()
�p�r       �F�G�l���M�[��
*****************************************/
void Bar::Recovery(){
	if(m_pRect->right<500){
		m_pRect->right	+= 5;
		if(m_pRect->right>500)
			m_pRect->right	= 500;
	}
}
/*****************************************
 �֐���     �Fvoid Bar::Consume()
 �p�r       �F�G�l���M�[����
 *****************************************/
void Bar::Consume(){
	if(m_pRect->right > 0){
		m_pRect->right	-= 3;
		if(m_pRect->right > 0){
			m_pRect->right	= 0;
		}
	}
}

/**************************************************************
�֐���     �Fvoid	 Item::Draw(DrawPacket &i_DrawPacket)
�p�r       �F�I�u�W�F�N�g�̕`��
***************************************************************/
void Bar::Draw(DrawPacket& i_DrawPacket){
	if(m_pRect->right != 500)
		m_Time	+= 1;

	if(m_Time >= 60){
		m_pRect->right	+= 1;
		m_Time	= 0;
	}
	SpriteObject::Draw( i_DrawPacket );
}

/**************************************************************************
 Factory_Item ��`��
****************************************************************************/
/**************************************************************************
 Factory_Item::Factory_Item(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Item::Factory_Item(FactoryPacket* fpac){
	try{
        D3DCOLORVALUE BallDiffuse = {0.0f,0.7f,0.7f,1.0f};
        D3DCOLORVALUE BallSpecular = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE BallAmbient = {0.0f,0.7f,0.7f,1.0f};
		Item*	it	=	new	Item(fpac,NULL,OBJID_UNK);
		for(int i = 0; i < 7; i++){
			for(int j = 0; j < 7; j++){
				it->addItem(D3DXVECTOR3((float(i)*5.0f+float(rand()%100*0.05f))+1.5f,
										(float(j)*2.75f+float(rand()%100*0.05f))+1.5f,0.0f),
							D3DXVECTOR3(0.5f,0.5f,0.5f),
							BallDiffuse,
							BallSpecular,
							BallAmbient);
			}
		}
		fpac->m_pVec->push_back(it);

		fpac->m_pVec->push_back(
			new Bar(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"front_bar.png" ),
				D3DXVECTOR3(0.8f,0.8f,1.0f),
				g_vZero,
				D3DXVECTOR3(300.0f,450.0f,0.0f),
				g_vZero,
				Rect(0,0,200,20)
			)
		);
	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 Factory_Item::~Factory_Item();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Item::~Factory_Item(){
    //�Ȃɂ����Ȃ�
}

}
//end of namespace wiz.
