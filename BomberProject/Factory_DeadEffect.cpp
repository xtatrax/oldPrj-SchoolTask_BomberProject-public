////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_DeadEffect.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F������
//	�����ް��Ɣ��l	�F���U�G�t�F�N�g
//					��
//	namespace wiz;
//		class DeadEffect ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "BassItems.h"
#include "Factory_Wall.h"
namespace wiz{
namespace bomberobject{

/**************************************************************************
 DeadEffect ��`��
****************************************************************************/
/**************************************************************************
 DeadEffect::DeadEffect(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	LPTATRATEXTURE pTexture,	//�e�N�X�`��
	wiz::OBJID id					//�I�u�W�F�N�g�̎��
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
 �S���F������
***************************************************************************/
DeadEffect::DeadEffect(LPDIRECT3DDEVICE9	pD3DDevice,
						LPTATRATEXTURE	pTexture,
						D3DXVECTOR3			vPos,
						wiz::OBJID			id	)
	:PrimitiveBox(pD3DDevice,
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					id,
					pTexture)
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));

	D3DCOLORVALUE Diffuse = {0.0f,0.0f,0.0f,0.0f};
	D3DCOLORVALUE Specular = {0.0f,0.0f,0.0f,0.0f};
	D3DCOLORVALUE Ambient = {1.0f,1.0f,1.0f,1.0f};

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

	for( int i = 0; i < PARTICLS_NUM; i++ ){
		this->addEffect( vPos, i*(360.0f/PARTICLS_NUM) );
	}

}

/*********************************
�f�X�g���N�^
*********************************/
DeadEffect::~DeadEffect(){
	SafeDeletePointerMap( m_ItemMap_Target );
	m_ItemMap_Target.clear();
}

/*********************************
�ǉ�
*********************************/
void	DeadEffect::addEffect( D3DXVECTOR3 vPos, float fDir){
	EffectItem*	pItem	= new EffectItem();

	pItem->m_vPos	= vPos;
	pItem->m_fDir	= fDir;

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
void DeadEffect::Draw(DrawPacket& i_DrawPacket)
{
	multimap<float,EffectItem*>::iterator it = m_ItemMap_Target.begin();
	while(it != m_ItemMap_Target.end()){

		setMatrix( it->second->m_vPos );
		PrimitiveBox::CalcWorldMatrix();
		PrimitiveBox::Draw(i_DrawPacket);

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
void DeadEffect::Update( UpdatePacket& i_UpdatePacket ){

	const float ColorRate	= 0.003f;

	multimap<float,EffectItem*>::iterator it = m_ItemMap_Target.begin();
	while(it != m_ItemMap_Target.end()){

		float	fDirZ	= it->second->m_fDir;
		if( fDirZ >= 180.0f ){
			fDirZ	-= 180.0f;
		}
		it->second->m_vPos.x	+= cosf( it->second->m_fDir )*2;
		it->second->m_vPos.y	+= sinf( it->second->m_fDir )*2;
		it->second->m_vPos.z	+= cosf( fDirZ )*5;

		it++;
	}

	if( m_Material.Ambient.r > 0 ){
		m_Material.Ambient.r	-= ColorRate;
		m_Material.Ambient.g	-= ColorRate;
		m_Material.Ambient.b	-= ColorRate;
	}
	else{
		m_Material.Ambient.r	= 0;
		m_Material.Ambient.g	= 0;
		m_Material.Ambient.b	= 0;
	}
}

/****************************************************
�}�g���b�N�X�̐ݒ�
****************************************************/
void	DeadEffect::setMatrix( D3DXVECTOR3 vPos ){

	PrimitiveBox::SetBasePos(vPos);
	D3DXVECTOR3 vScale(0.8f, 0.8f, 0.0f);
	PrimitiveBox::SetBaseScale(vScale);
}

/****************************************************
���W�̐ݒ�
****************************************************/
void	DeadEffect::setPos( D3DXVECTOR3 i_vPos ){
	multimap<float,EffectItem*>::iterator it = m_ItemMap_Target.begin();
	while(it != m_ItemMap_Target.end()){

		it->second->m_vPos	= i_vPos;
		++it;
	}

	m_Material.Ambient.r	= 255;
	m_Material.Ambient.g	= 255;
	m_Material.Ambient.b	= 255;
}

/**************************************************************************
 Factory_DeadEffct ��`��
****************************************************************************/
/**************************************************************************
 Factory_DeadEffct::Factory_DeadEffct(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_DeadEffect::Factory_DeadEffect(FactoryPacket* fpac)
{
	try{

		//float	wide	= BASE_CLIENT_WIDTH/2;
		//float	height	= BASE_CLIENT_HEIGHT/2;

		//D3DXVECTOR3	vScale	= D3DXVECTOR3( 0.5f, 0.5f, 0.0f );
		//D3DXVECTOR3	vPos	= D3DXVECTOR3( (wide-512.0f*vScale.x), (height-256.0f*vScale.y-100), 0.0f );
		//LPTATRATEXTURE pTex;
		//pTex = fpac->AddTexture(L"DeadPerticul.png");
		//DeadEffect* dEffect	=	new DeadEffect( fpac->GetDevice(), pTex, g_vZero );
		////for( int i = 0; i < PARTICLS_NUM; i++ ){
		////	dEffect->addEffect( i*(360.0f/PARTICLS_NUM) );
		////}
		//fpac->AddObject(dEffect);


	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 Factory_DeadEffct::~Factory_DeadEffct();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_DeadEffect::~Factory_DeadEffect(){
    //�Ȃɂ����Ȃ�
}

}
}