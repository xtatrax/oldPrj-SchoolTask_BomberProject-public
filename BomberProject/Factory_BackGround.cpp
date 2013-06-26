////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_BackGround.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F������
//	�����ް��Ɣ��l	�F�R���e�j���[
//					��
//	namespace wiz;
//		class Reply ;
//		class Dead ;
//		class Continue ;
//

//////////
//	: ��{�̃C���N���[�h
#include "StdAfx.h"
#include "Factory_BackGround.h"

//	: ��{�̃C���N���[�h
//////////
//////////
//	: �ǉ��̃C���N���[�h
//	: �ǉ��̃C���N���[�h
//////////


namespace wiz{
namespace bomberobject{

BackGround::BackGround(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3 vScalse,LPDIRECT3DTEXTURE9 pTextuer)
:Box( pD3DDevice, vScalse,
	 D3DXVECTOR3(vScalse.x/2,0.0f,0.3f), g_vZero,
	 getD3DCOLORVALUE(1.0f,1.0f,1.0f,1.0f),
	 getD3DCOLORVALUE(0.0f,0.0f,0.0f,0.0f),
	 getD3DCOLORVALUE(1.0f,1.0f,1.0f,1.0f),
	 OBJID_3D_BACKGROUND,
	 false,
	 pTextuer
	 )
,m_pCamera(NULL)
,m_uiYNum(0){
	
}
/////////////////// ////////////////////
//// �p�r       �Fvoid update( UpdatePacket& i_UpdatePacket )
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g���X�V
//// ����       �F
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
void BackGround::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCamera ) m_pCamera = (Camera*) SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CAMERA);
	if( !m_pCamera ){ Debugger::DBGWRITINGLOGTEXT::OutputSystemLog(L"BackGround::Update(�ǎ�)��Camera���������܂���ł���><\n"); return ;}
	float fEyePos = m_pCamera->getPosY();
	this->m_BasePos;
	if( fEyePos > this->m_BasePos.y + this->m_Size.y ){
		this->m_BasePos.y += this->m_Size.y ;
	}
	Debugger::DBGSTR::addStr(L"Y = %f\n",this->m_BasePos.y);
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
//// �S����     �F���� �O
//// ���l       �F
void BackGround::Draw( DrawPacket& i_DrawPacket ){
	if( !m_pCamera ){ Debugger::DBGWRITINGLOGTEXT::OutputSystemLog(L"BackGround::Draw(�ǎ�)��Camera���������܂���ł���><\n"); return ;}

	D3DXVECTOR3 vWorkPos = this->m_BasePos;

	Box::CalcWorldMatrix();
	Box::Draw(i_DrawPacket);

	this->SetBasePos(D3DXVECTOR3(vWorkPos.x,vWorkPos.y + this->m_Size.y ,vWorkPos.z));
	Box::CalcWorldMatrix();
	Box::Draw(i_DrawPacket);

	this->SetBasePos(vWorkPos);
}
Factory_BG::Factory_BG(FactoryPacket *fpac){

	fpac->AddObject( new BackGround(fpac->pD3DDevice,D3DXVECTOR3(50.0f,90.0f,0.0f), fpac->AddTexture(L"BackStage.png")) );
}
}
}