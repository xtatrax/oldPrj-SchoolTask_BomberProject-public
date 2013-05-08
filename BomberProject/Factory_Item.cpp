////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Item.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F�A�C�e���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Item ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Item.h"
#include "Factory_Player.h"
#include "BassItems.h"

namespace wiz{

	Item::Item(FactoryPacket* fpac,LPDIRECT3DTEXTURE9 pTexture, wiz::OBJID id)
	:PrimitiveSphere(fpac->pD3DDevice,
						D3DCOLORVALUE(),
						D3DCOLORVALUE(),
						D3DCOLORVALUE(),pTexture)

{
	try{
		D3DXMatrixIdentity(&m_mMatrix);
        // D3DMATERIAL9�\���̂�0�ŃN���A
        ::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
	}
	catch(...){
		//�ăX���[
		throw;
	}
}

Item::~Item(){
}

/********************************************
	�p�r�F�`��
********************************************/
void	Item::Draw(DrawPacket &i_DrawPacket){
	// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
	i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);
	CommonMesh::Draw(i_DrawPacket);
}

void	Item::Update(UpdatePacket& i_UpdatePacket){
	//�R�C���̃|�C���^���擾
	vector<Object*> Vec	= 	*(i_UpdatePacket.pVec);
	PlayerCoil*	pc	= NULL;
	Bar*		br	= NULL;
	vector<Object*>::size_type sz2 = Vec.size();
	for(vector<Object*>::size_type i = 0;i < sz2;i++){
		const type_info& info = typeid(*(Vec[i]));
		if(info == typeid(PlayerCoil)){
			pc = dynamic_cast<PlayerCoil*>(Vec[i]);
			break;
		}
	}
	for(vector<Object*>::size_type i = 0;i < sz2;i++){
		const type_info& info = typeid(*(Vec[i]));
		if(info == typeid(Bar)){
			br = dynamic_cast<Bar*>(Vec[i]);
			break;
		}
	}

	D3DXVECTOR3	cPos	= pc->getPos();	//�R�C���̈ʒu�擾

	vector<BallItem>::size_type sz = m_ItemVec.size();
	for(vector<BallItem>::size_type i = 0; i < sz; i++){

		D3DXVECTOR3	vTargetDir	= cPos - m_ItemVec[i]->m_Pos ;		//	: ��������Ώۂ܂ł̃x�N�g�����Z�o

		double dirX = vTargetDir.x * vTargetDir.x;
		double dirY = vTargetDir.y * vTargetDir.y;
		float fDistance	 = (float)sqrt(dirX + dirY);	//	: �����ƑΏۂ܂ł̋��������߂�

		//������100���Ȃ��Ȃ����Ă���
		if( fDistance < 100.0f ){
			m_ItemVec[i]->m_Pos	+= vTargetDir*0.0005f;

			if( m_ItemVec[i]->m_Pos == cPos ){
				br->Recovery();
				SAFE_DELETE( this->m_ItemVec[i] );
			}
		}
		//�ړ��p
		D3DXMATRIX mMove, mScale;
		D3DXMatrixIdentity(&mMove);
		D3DXMatrixTranslation(&mMove,
			m_ItemVec[i]->m_Pos.x,m_ItemVec[i]->m_Pos.y,m_ItemVec[i]->m_Pos.z);
		D3DXMatrixScaling(&mScale,
			m_ItemVec[i]->m_Size.x,m_ItemVec[i]->m_Size.y,m_ItemVec[i]->m_Size.z);

		//�}�e�B���A���ݒ�
		m_Material = m_ItemVec[i]->m_Material;
		m_mMatrix	= mScale * mMove;
	}
}

/***********************************************
	�p�r�F�ǉ�
***********************************************/
void	Item::addItem(D3DXVECTOR3 pos, D3DXVECTOR3 size,
					  D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient)
{
	try{
		BallItem* bItem = new BallItem;
		bItem->m_Pos = pos;
		bItem->m_Size = size;
        // D3DMATERIAL9�\���̂�0�ŃN���A
        ::ZeroMemory(&bItem->m_Material,sizeof(D3DMATERIAL9));
		bItem->m_Material.Diffuse = Diffuse;
		bItem->m_Material.Specular = Specular;
		bItem->m_Material.Ambient = Ambient;

		m_ItemVec.push_back(bItem);
	}
	catch(...){
		throw;
	}
}

/***************************************
	�p�r�F�R�C���ɋz���t��
***************************************/
void	Item::Suction(){
}

/**************************************************************************
 Bar ��`��
***************************************************************************/
Bar::Bar(
	LPDIRECT3DDEVICE9 pD3DDevice,				//	: �f�o�C�X
	LPDIRECT3DTEXTURE9 pTex,			//	: �R�A������Texture
	D3DXVECTOR3 &vScale,						//	: �L�k
	D3DXVECTOR3 &vRot,							//	: ��]
	D3DXVECTOR3 &vPos,							//	: �ʒu
	D3DXVECTOR3 &vDirOffset,					//	: ������\���O�p�̕`��I�t�Z�b�g
	RECT* vRect,							//	: �`��͈�
	wiz::OBJID id 								//	: ID
)
:SpriteObject(pD3DDevice,pTex,vScale,vRot,vPos,
	vRect,g_vZero,vDirOffset,0xFFFFFFFF,id),m_Time(0)

{
}

void Bar::Recovery(){
	if(m_pRect->right<500){
		m_pRect->right	+= 5;
		if(m_pRect->right>500)
			m_pRect->right	= 500;
	}
}

void Bar::Consume(){
	if(m_pRect->right > 0){
		m_pRect->right	-= 3;
		if(m_pRect->right > 0){
			m_pRect->right	= 0;
		}
	}
}

void Bar::Draw(DrawPacket& i_DrawPacket){
	//Recovery();
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
        D3DCOLORVALUE BallDiffuse = {1.0f,1.0f,1.0f,1.0f};
        D3DCOLORVALUE BallSpecular = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE BallAmbient = {0.5f,0.5f,0.0f,1.0f};
		Item*	it	=	new	Item(fpac,NULL,OBJID_UNK);

		it->addItem(D3DXVECTOR3(-1.0f,0.0f,0.0f),
					D3DXVECTOR3(1.0f,1.0f,1.0f),
					BallDiffuse,
					BallSpecular,
					BallAmbient);
		fpac->m_pVec->push_back(it);

		fpac->m_pVec->push_back(
			new Bar(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"front_bar.png" ),
				D3DXVECTOR3(0.8f,0.8f,1.0f),
				g_vZero,
				D3DXVECTOR3(300.0f,450.0f,0.0f),
				g_vZero,
				Rect(0,0,200,50)
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
