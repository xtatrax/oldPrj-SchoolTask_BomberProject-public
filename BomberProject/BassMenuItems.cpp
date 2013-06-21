////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FBassMenuItems.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F
//	�����ް��Ɣ��l	�F���j���[�̕��i�Q
//					��
//	namespace wiz;
//		class Button;
//		class ButtonSprite : public SpriteObject;
//
#include "StdAfx.h"
#include "BassMenuItems.h"

namespace wiz{
namespace menuobject{


ButtonSprite::ButtonSprite(
		const LPDIRECT3DDEVICE9		pD3DDevice		,
		const LPDIRECT3DTEXTURE9	pTexture		,
		const D3DXVECTOR3			vScalse			,
		const D3DXVECTOR3			vRot			,
		const D3DXVECTOR3			vPos			,
		const RECT*					pRect			,
		const D3DXVECTOR3			vCenter			,
		const D3DXVECTOR3			vOffset			,
		const Color					dwSelectColor	,
		const Color					dwUnSelectColor	,
		const char*					sSelectSound	,
		const char*					sDecisionSound	,
		const float					fWaitTime		,
		const Command				Com				,
		const DWORD					dwIndex			,
		const wiz::OBJID			id				,
		const bool					bApplyAspect	
)
:m_ButtonState(Com,dwIndex)
,SpriteObject(pD3DDevice,pTexture,vScalse,vRot,vPos,pRect,vCenter,vOffset,dwUnSelectColor,id ,bApplyAspect)
,m_SelectColor(dwSelectColor)
,m_UnSelectColor(dwUnSelectColor)
,m_sSelectSound(sSelectSound)
,m_sDecisionSound(sDecisionSound)
,m_bIsPlaySelectSound(false)
,m_fWaitTime(fWaitTime)
,m_fTimeAccumulator(0)
,m_bIsSelectWait(false)
{
	try{
	}
	catch(...){
		//�ăX���[
		throw;
	}


}
ButtonSprite::~ButtonSprite(){};
/////////////////// ////////////////////
//// �֐���     �Fvoid ButtonSprite::Update(LPDIRECT3DDEVICE9 pD3DDevice,Tempus2* i_DrawPacket.pTime,
////            �F      vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& i_DrawPacket.pCommand)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�I�u�W�F�N�g���X�V
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,               // �I�u�W�F�N�g�̔z��
////            �F  const CONTROLER_STATE* pCntlState   // �R���g���[���̃X�e�[�^�X
////            �F  Command i_DrawPacket.pCommand       // �R�}���h
//// �ߒl       �F����
//// ���l       �F
////            �F
////
void ButtonSprite::Update(UpdatePacket& i_UpdatePacket){

	if( Cursor2D::isHitSprite(this) ){
		m_ButtonState.setMouseSelect(true);
		if( !m_bIsPlaySelectSound  ){
			i_UpdatePacket.SearchSoundAndPlay( m_sSelectSound );
			m_bIsPlaySelectSound = true;
		}
	}
	else{
		m_ButtonState.setMouseSelect(false);
		m_bIsPlaySelectSound = false;
	}

	if(m_ButtonState.getSelect()){
		m_Color = m_SelectColor;
		if(m_ButtonState.getPressed()){
			i_UpdatePacket.SearchSoundAndPlay(m_sDecisionSound);
			m_bIsSelectWait = true ;
		}
	}else{
		m_Color = m_UnSelectColor;
	}
	if( m_bIsSelectWait && (m_fTimeAccumulator += (float)i_UpdatePacket.pTime->getElapsedTime()) >= m_fWaitTime ){
			*i_UpdatePacket.pCommand = m_ButtonState.CommandIssue();
			m_bIsSelectWait = false ;
			m_fTimeAccumulator = 0 ;
			m_ButtonState.setPressed(false);
	}
};


/////////////////// ////////////////////
//// �֐���     �Fvoid ButtonSprite::Draw(LPDIRECT3DDEVICE9 pD3DDevice,Tempus2* i_DrawPacket.pTime,
////            �F      vector<Object*>& Vec,Command& i_DrawPacket.pCommand)
//// �J�e�S��   �F�������z�֐�
//// �p�r       �F�I�u�W�F�N�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,               // �I�u�W�F�N�g�̔z��
////            �F  Command i_DrawPacket.pCommand                         // �R�}���h
//// �ߒl       �F����
//// ���l       �F
////            �F
////
void ButtonSprite::Draw(DrawPacket& i_DrawPacket){
	if(m_ButtonState.getSelect()){
		m_Color = m_SelectColor;
		if(m_ButtonState.getPressed()){
			i_DrawPacket.SearchSoundAndPlay(m_sDecisionSound);
			m_bIsSelectWait = true ;
			*i_DrawPacket.pCommand = m_ButtonState.CommandIssue();
		}
	}else{
		m_Color = m_UnSelectColor;
	}
	SpriteObject::Draw(i_DrawPacket);
};

}//end of namespace menuobject.
}//end of namespace wiz.
