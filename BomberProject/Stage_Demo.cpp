////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FStage_Demo.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F������
//	�����ް��Ɣ��l	�F�^�C�g���X�e�[�W
//					��
//	namespace wiz;
//		class DemoStage : public Stage ;
//
#include "StdAfx.h"
#include "Stage_Demo.h"
#include "Factory_Demo.h"

namespace wiz{
using namespace bomberobject;

/**************************************************************************
 DemoStage ��`��
****************************************************************************/
/**************************************************************************
 DemoStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//�f�o�C�X
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
DemoStage::DemoStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* pStage)
	:MenuStage(pD3DDevice,pStage)

{
	try{
		FactoryPacket FPac(pD3DDevice,this->m_IsDialog,&Command(),this);
		Factory_Demo  Dfac(&FPac,&Command());
	}
	catch(...){
		Clear();
		//�ăX���[
		throw;
	}
}
/**************************************************************************
DemoStage();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
DemoStage::~DemoStage(){
	//Debugger::DBGWRITINGLOGTEXT::addStr(L"DemoStage::~DemoStage()\n");
}

}
//end of namespace wiz.
