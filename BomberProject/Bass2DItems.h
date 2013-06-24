////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FBassItems.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F�Q�[���̃x�[�X�ɂȂ�A�C�e���Q�̐錾
//					��
//	�v���~�e�B�u���ӂ��R�m��搶�̃\�[�X���Q�l�ɑ��������! 
//
//	namespace wiz;
//
//
#pragma once
#include "Object.h"
#include "TL-String.h"
namespace wiz {

namespace base2Dobject{
class PrimitiveSprite;
extern LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern class MouseUtilityCushion ;
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
class Cursor2D{
	
	static Point		m_vMousePoint	;
	static DWORD		m_tLastTime		;
	const static float	m_fLockTime		;
public:
    static bool			m_bMouseLB		;
    static bool			m_bMouseRB		;
    static bool			m_bMouseMB		;
    static bool			m_bMouseLBLock	;
    static bool			m_bMouseRBLock	;
    static bool			m_bMouseMBLock	;
public:
	friend class DxDevice;
	friend class MouseUtilityCushion ;
	friend static LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static Point getPos();
	static bool getLButtonState(){return m_bMouseLB;};
	static bool getMButtonState(){return m_bMouseMB;};
	static bool getRButtonState(){return m_bMouseRB;};
	static bool pressLorRButton(){return m_bMouseRB || m_bMouseLB;};
	static bool clickLButtonWithLock();
	static bool clickMButtonWithLock();
	static bool clickRButtonWithLock();
	static bool clickLorRButtonWithLock(){return clickLButtonWithLock() || clickRButtonWithLock();};
	static bool isHitSprite(const PrimitiveSprite* i_TargetSprite);
};



/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/


//**************************************************************************
// class PrimitiveSprite ;
//
// �S����  : ���� �O
// �p�r    : �QD���̃X�v���C�g�N���X
//**************************************************************************
class PrimitiveSprite {
	friend class Cursor2D;
protected:
	LPDIRECT3DTEXTURE9	m_pTexture		;	//	: �`�悷��e�N�X�`��
	LPD3DXSPRITE		m_pSprite		;	//	: �`�悷�邽�߂̃X�v���C�g
	D3DXMATRIX			m_mMatrix		;	//	: �}�g���b�N�X (�h���N���X�͂����ɍ��W�f�[�^������)
	D3DXVECTOR3			m_vOffsetPos	;	//	: �e�N�X�`���[�̕`��I�t�Z�b�g(��{�͂O�l�_);
	D3DXVECTOR3			m_vCenter		;	//	: �e�N�X�`���[�̒��S
	RECT*				m_pRect			;	//	: �e�N�X�`���[�̕`��̈�
	Color				m_Color			;
	bool				m_bApplyAspect	;
	//��
	PrimitiveSprite(){};
public:
	D3DXMATRIX getAspectMatrix() const{
		D3DXMATRIX mAll;
		D3DXMATRIX mAspectRate;
		D3DXVECTOR2 AspectRate = DxDevice::getAspectRate();
		D3DXMatrixScaling(&mAspectRate,AspectRate.x,AspectRate.y,1.0f);
		D3DXMatrixMultiply(&mAll,&m_mMatrix,&mAspectRate);
		return mAll ; 
	}
	void setMatrix( D3DXMATRIX i_mMatrix ){ m_mMatrix = i_mMatrix ; }
	D3DXMATRIX getMatrix(  ){ return m_mMatrix  ; }
/////////////////// ////////////////////
//// �֐���     �FPrimitiveSprite(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,RECT* Rect,
////            �F    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,D3DCOLOR color = 0xFFFFFFFF);
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�X�v���C�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	//	: �f�o�C�X
////            �F  LPDIRECT3DTEXTURE9 pTexture,	//	: �e�N�X�`���[�ւ̃|�C���^
////            �F  RECT*			Rect,			//	: �e�N�X�`���̕`��͈�
////            �F  D3DXVECTOR3&	vCenter,		//	: ���S�ʒu
////            �F  D3DXVECTOR3&	vOffsetPos,		//	: ���[�J�����W
////            �F  D3DCOLOR		color			//	: �F
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	PrimitiveSprite(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTexture	,
		const RECT*					Rect		,
		const D3DXVECTOR3&			vCenter		,
		const D3DXVECTOR3&			vOffsetPos	,
		const Color					color		= 0xFFFFFFFF,
		const bool					bApplyAspect= true
	);
/////////////////// ////////////////////
//// �֐���     �Fvirtual ~PrimitiveSprite()
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	virtual ~PrimitiveSprite();
/////////////////// ////////////////////
//// �֐���     �Fvoid Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�X�v���C�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	virtual void Draw(DrawPacket& i_DrawPacket);

	void	setAlpha( BYTE	alpha ){
		m_Color.byteColor.a	= alpha;
	}
	void	setColor( Color	color ){
		m_Color	= color;
	}

	void setCenter(D3DXVECTOR3 i_vCenter){
		m_vCenter = i_vCenter;
	}
};

//**************************************************************************
// class SpriteObject : public Object ,public PrimitiveSprite ;
//
// �S����  : ���� �O
// �p�r    : �X�v���C�g���Ƃ肠�����`�悷�邽�߂̃N���X
//           ���̓�������Ȃ��Ƃ肠�����X�v���C�g��`�悵�������ɂ�������
//**************************************************************************
class SpriteObject : public Object ,public PrimitiveSprite{
public:
/////////////////// ////////////////////
//// �֐���     �FSpriteObject(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
////            �F    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect,
////            �F    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�X�v���C�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  LPDIRECT3DTEXTURE9 pTexture     // �\��t�������e�N�X�`��
////            �F  D3DXVECTOR3 &vScale             // �傫��
////            �F  D3DXVECTOR3 &vRot               // �O����]
////            �F  D3DXVECTOR3 &vPos               // �ݒu���W
////            �F  RECT* pRect                     // �`�悵�����͈�(NULL�őS�̂�`��)
////            �F  D3DXVECTOR3& vCenter            // ���S
////            �F  D3DXVECTOR3& vOffsetPos         // �I�t�Z�b�g���W
////            �F  Color color = 0xFFFFFFFF        // �F
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	SpriteObject(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTexture	,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const RECT*					pRect		,
		const D3DXVECTOR3&			vCenter		,
		const D3DXVECTOR3&			vOffsetPos	,
		const Color					color		= 0xFFFFFFFF		,
		const wiz::OBJID			id			= OBJID_UI_SPRITE	,
		const bool					bApplyAspect= true
	);
/////////////////// ////////////////////
//// �֐���     �F~SpriteObject();
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	virtual ~SpriteObject();
/////////////////// ////////////////////
//// �֐���     �Fvoid Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�X�v���C�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	virtual void Draw(DrawPacket& i_DrawPacket);

	void setTexture(LPDIRECT3DTEXTURE9&	i_pTexture){
		m_pTexture = i_pTexture;
	}
};

//**************************************************************************
// 
//
// �S����  : ���� �O
// �p�r    : 
//           
//**************************************************************************
class RenderTargetSprite : public PrimitiveSprite, public Object{
	LPDIRECT3DSURFACE9	m_sfRenderTarget	,	//	�F�f�[�^
						m_sfRenderTargetZ	;	//	�y�l
	Size				m_ClientSize		;
public:
	RenderTargetSprite(BassPacket* i_BassPacket, UINT i_Width, UINT i_Height, wiz::OBJID id = OBJID_SYS_RENDERTARGET);
/////////////////// ////////////////////
//// �p�r       �Fvirtual void TargetRender( LPDIRECT3DDEVICE9 pD3DDevice
////            �F      vector<Object*>& Vec)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�I�u�W�F�N�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,               // �I�u�W�F�N�g�̔z��
////            �F  Command i_DrawPacket.pCommand                         // �R�}���h
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F�p���������̂ł��K���Ƃ���`�����Ȃ��Ă��ǂ�
////            �F
////
	virtual void TargetRender( RenderPacket& i_RenderPacket );
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
	void Draw(DrawPacket& i_DrawPacket);
};

}//end of namespace base2Dobject.
using namespace base2Dobject;
}//end of namespace wiz.
