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
MouseCursor::MouseCursor(
						 LPDIRECT3DDEVICE9 pD3DDevice,
						 LPDIRECT3DTEXTURE9 pTexture,
						 D3DXVECTOR3	   &vScale,
						 D3DXVECTOR3	   &vPos,
						 wiz::OBJID id)					 
:PrimitiveBox(pD3DDevice,
			  D3DCOLORVALUE(),
			  D3DCOLORVALUE(),
			  D3DCOLORVALUE(),
			  id,
		      pTexture)
,m_pMouseTex( pTexture )
,m_Ptn(0)
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
	m_pCamera = NULL;

}

///////////////////// ////////////////////
////// �p�r       �FMouseCursor(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_3D_WALL);
////// �J�e�S��   �F�R���X�g���N�^
////// �p�r       �F�֐�
////// ����       �F�Ȃ�
////// �ߒl       �F�Ȃ�
////// �S����     �F���� �O
////// ���l       �F
//void MouseCursor::UpdateTargetItem(){
	
	
//}

	
//bool MouseCursor::HitTest2DRectAndCircle(D3DXVECTOR3& i_vPos, float i_fRadius)
//{
//	//float fTH = 150 ;
//	//float fTW =  20 ;
//	//if( abs(m_vPos.x - i_vPos.x) < fTW + i_fRadius &&
//	//	abs(m_vPos.y - i_vPos.y) < fTH + i_fRadius ){
//	//	return true ;
//	//}
//	return false ;
//}

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
	//multimap<float,WallItem*>::iterator it = m_ItemMap_Target.begin();
	//while(it != m_ItemMap_Target.end()){
	//	++it;
	//}
	//multimap<float,PolyItem*>::iterator it2 = m_ItemMap_Poly.begin();
	//while(it2 != m_ItemMap_Poly.end()){
	//	//�e�N�X�`��������ꍇ
	//	if(m_pMouseTex){
	//		m_pTexture	= m_pMouseTex;
	//		DWORD wkdword;
	//		//���݂̃e�N�X�`���X�e�[�^�X�𓾂�
	//		i_DrawPacket.pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
	//		//�X�e�[�W�̐ݒ�
	//		i_DrawPacket.pD3DDevice->SetTexture(0,m_pTexture);
	//		//�f�t�B�[�Y�F�ƃe�N�X�`�����|�����킹��ݒ�
	//		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
	//		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	//		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

	//		//i_DrawPacket.pD3DDevice->SetFVF(PlateFVF);
	//		// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
	//		i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it2->second->m_Matrix);
	//		//�R�������b�V����Draw()���Ă�
	//		CommonMesh::Draw(i_DrawPacket);
	//		i_DrawPacket.pD3DDevice->SetTexture(0,0);
	//		//�X�e�[�W�����ɖ߂�
	//		i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	//	}
	//	else{
	//	//�e�N�X�`�����Ȃ��ꍇ
	//		// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
	//		i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it2->second->m_Matrix);
	//		//�R�������b�V����Draw()���Ă�
	//		CommonMesh::Draw(i_DrawPacket);
	//	}

	//	++it2;
	//}
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
//// �S����     �F�{�����V
//// ���l       �F
////            �F
////
void MouseCursor::Update( UpdatePacket& i_UpdatePacket ){
	if(m_pCamera == NULL){
		m_pCamera = (Camera*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CAMERA);
	}
	//if(m_pPlayerCoil == NULL){
	//	m_pPlayerCoil = (PlayerCoil*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(PlayerCoil));
	//}

	//m_ItemMap_Target.clear();
	//multimap<float,WallItem*>::iterator it = m_ItemMap_All.begin();
	//while(it != m_ItemMap_All.end()){
	//	if( ( +(it->first - m_pCamera->getEye().y) <= DRAWING_RANGE) && ( +(it->first - m_pCamera->getEye().y) >= -DRAWING_RANGE ) ){
	//		m_ItemMap_Target.insert(multimap<float,WallItem*>::value_type(it->second->m_vPos.y,it->second));
	//	}
	//	++it;
	//}

	//multimap<float,CursorItem*>::iterator it2 = m_ItemMap_Target.begin();
	//while(it2 != m_ItemMap_Target.end()){
	//	//�v�Z��Update��
	//	//�g��k��
	//	D3DXMATRIX mScale;
	//	D3DXMatrixIdentity(&mScale);
	//	D3DXMatrixScaling(&mScale,
	//		it2->second->m_vScale.x,it2->second->m_vScale.y,it2->second->m_vScale.z);
	//	//��]
	//	D3DXMATRIX mRot;
	//	D3DXMatrixIdentity(&mRot);
	//	D3DXMatrixRotationQuaternion(&mRot,&it2->second->m_vRot);
	//	//�ړ��p
	//	D3DXMATRIX mMove;
	//	D3DXMatrixIdentity(&mMove);
	//	D3DXMatrixTranslation(&mMove,
	//		it2->second->m_vPos.x,it2->second->m_vPos.y,it2->second->m_vPos.z);
	//	//�~�b�N�X�s��
	//	it2->second->m_Matrix = mScale * mRot * mMove;
	//	//�}�e�B���A���ݒ�
	//	m_Material = it2->second->m_Material;

	//	++it2;
	//}

	//multimap<float,PolyItem*>::iterator it3 = m_ItemMap_Poly.begin();
	//while(it3 != m_ItemMap_Poly.end()){
	//	//�v�Z��Update��
	//	//�g��k��
	//	D3DXMATRIX mScale;
	//	D3DXMatrixIdentity(&mScale);
	//	D3DXMatrixScaling(&mScale,
	//		it3->second->m_vScale.x,it3->second->m_vScale.y,0.0f);
	//	//��]
	//	D3DXMATRIX mRot;
	//	D3DXMatrixIdentity(&mRot);
	//	D3DXMatrixRotationQuaternion(&mRot,&it3->second->m_vRot);
	//	//�ړ��p
	//	D3DXMATRIX mMove;
	//	D3DXMatrixIdentity(&mMove);
	//	D3DXMatrixTranslation(&mMove,
	//		it3->second->m_vPos.x,it3->second->m_vPos.y,it3->second->m_vPos.z);
	//	//�~�b�N�X�s��
	//	it3->second->m_Matrix = mScale * mRot * mMove;
	//	//�}�e�B���A���ݒ�
	//	m_Material = it3->second->m_Material;

	//	++it3;
	//}

	//**************************************************************************************
	LPDIRECT3DVERTEXBUFFER9 pVB = 0;
	CommonMeshVertex* pVer = 0;
	m_pMesh->GetVertexBuffer(&pVB);
	pVB->Lock(0,0,(VOID**)&pVer,0);
	DWORD vsize = m_pMesh->GetNumVertices();
	for(DWORD n = 0;n < vsize;n++){ //���_�̐����擾����
		//�@���ƒ��_����uv�l�𓾂�
		BoxVecNomal2UV_1_4(pVer[n].vec,pVer[n].normal,m_Ptn,pVer[n].tu,pVer[n].tv);
	}
	pVB->Unlock();
	//***********************************************************************************

	++m_Ptn;
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
						fpac->m_pTexMgr->addTexture(fpac->pD3DDevice, L"MouseCursor.png"),
						D3DXVECTOR3(90.0f,0.0f,0.0f),
						D3DXVECTOR3(10.0f,10.0f,0.0f)
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
//end of namespace wiz.