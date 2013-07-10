////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
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
#pragma once
#include "BassItems.h"
#include "Bass2DItems.h"
#include "Factory_Sound.h"

namespace wiz{

namespace menuobject{


class ButtonSprite : public SpriteObject{
protected:
	Button			m_ButtonState			;
	Color			m_SelectColor			;
	Color			m_UnSelectColor			;
	const char*		m_sSelectSound			;
	const char*		m_sDecisionSound		;
	float			m_fWaitTime				;
	float			m_fTimeAccumulator		;
	bool			m_bIsSelectWait			;
	bool			m_bIsPlaySelectSound	;
	bool			m_bKillAfterIssuing		;
public:
	ButtonSprite(
		const LPDIRECT3DDEVICE9		pD3DDevice			,
		const LPTATRATEXTURE	pTexture			,
		const D3DXVECTOR3			vScalse				,
		const D3DXVECTOR3			vRot				,
		const D3DXVECTOR3			vPos				,
		const Rect*					pRect				,
		const D3DXVECTOR3			vCenter				,
		const D3DXVECTOR3			vOffset				,
		const Color					dwSelectColor		,
		const Color					dwUnSelectColor		,
		const char*					sSelectSound		,
		const char*					sDecisionSound		,
		const float					fWaitTime			,
		const Command				Com					,
		const wiz::OBJID			id					= OBJID_UI_SPRITEBUTTON	,
		const bool					bKillAfterIssuing	= false					,
		const bool					bApplyAspect		= true
	);
	virtual ~ButtonSprite();
/////////////////// ////////////////////
//// �p�r       �Fvirtual void Update( LPDIRECT3DDEVICE9 pD3DDevice
////            �F  vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�I�u�W�F�N�g���X�V
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,               // �I�u�W�F�N�g�̔z��
////            �F  const CONTROLER_STATE* pCntlState   // �R���g���[���̃X�e�[�^�X
////            �F  Command Com                         // �R�}���h
//// �ߒl       �F�Ȃ�
//// ���l       �F
////            �F
////
    virtual void Update(UpdatePacket& i_UpdatePacket);

/////////////////// ////////////////////
//// �p�r       �Fvirtual void Update( LPDIRECT3DDEVICE9 pD3DDevice
////            �F  vector<Object*>& Vec)
//// �J�e�S��   �F�������z�֐�
//// �p�r       �F�I�u�W�F�N�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,               // �I�u�W�F�N�g�̔z��
////            �F  Command Com                         // �R�}���h
//// �ߒl       �F�Ȃ�
//// ���l       �F
////            �F
////
    virtual void Draw(DrawPacket& i_DrawPacket) ;

	Button* getButtonP(){ return &m_ButtonState;}
	void setWaitTime( float fTime ){
		m_fWaitTime = fTime ;
	}

} ;
}//end of namespace menuobject.
using namespace menuobject ;
}//end of namespace wiz.
