////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Title.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F�^�C�g���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Title ;
//
#pragma once

const D3DXVECTOR3 MAGNET_FIELD_POS_1 = D3DXVECTOR3( 230.0f, 370.0f, 0.0f );
const D3DXVECTOR3 MAGNET_FIELD_POS_2 = D3DXVECTOR3( 290.0f, 460.0f, 0.0f );
const D3DXVECTOR3 MAGNET_FIELD_POS_3 = D3DXVECTOR3( 170.0f, 460.0f, 0.0f );

namespace wiz{
namespace bomberobject{

/*************************************************************************
class ClickChar  public SpriteObject

�S���ҁF������
�p�r�@�F�N���b�N�𑣂�
*************************************************************************/
class	ClickChar	: public SpriteObject{
	MouseCursor*	m_pCursor;
	D3DXVECTOR3		m_vPos;
	D3DXVECTOR3		m_vScale;
	D3DXVECTOR3		m_vOffsetPos;
public:
	ClickChar(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTexture	,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const RECT*					pRect		,
		const D3DXVECTOR3&			vOffsetPos
	);
	~ClickChar();
	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
};

/*************************************************************************
class Title_Select  public SpriteObject

�S���ҁF������
�p�r�@�F�^�C�g����ʂ̃{�^��
*************************************************************************/
class	Title_Select	: public SpriteObject{
	D3DXVECTOR3		m_vPos		;
	DWORD			m_dNext		;
	int				m_iTime		;
	bool			m_bPush		;
	bool			m_bPushRock	;
	bool			m_bSelect	;
	bool			m_bCanSelect;
public:
	Title_Select(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTexture	,
		const DWORD					next		,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const RECT*					pRect		,
		const D3DXVECTOR3&			vCenter		,
		const D3DXVECTOR3&			vOffsetPos	,
		const Color					color		= 0xFFFFFFFF,
		bool						bCanSelect	= true
	);
	~Title_Select();
	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);

	void	setCanSelect( bool b ){
		m_bCanSelect	= b;
	}
};

/*************************************************************************
class MagnetFieldMini  public SpriteObject

�S���ҁF�{�����V
�p�r�@�F���E
*************************************************************************/
class	MagnetFieldMini	: public SpriteObject{
	LPDIRECT3DTEXTURE9 m_pTextureN;
	LPDIRECT3DTEXTURE9 m_pTextureS;
	D3DXVECTOR3		m_vPos;
	D3DXVECTOR3		m_vScale;
	D3DXVECTOR3		m_vRot;
	float			m_fRotZ;
	int				m_iNowPosNum;
	POLE			m_bMagnetPole;
public:
	MagnetFieldMini(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTextureN	,
		const LPDIRECT3DTEXTURE9	pTextureS	,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const D3DXVECTOR3&			vCenter		,
		const RECT*					pRect		
	);
	~MagnetFieldMini();
	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
	float	getRotZ(){
		return m_fRotZ;
	}
	D3DXVECTOR3 getPos(){
		return m_vPos;
	}
	int getNowPosNum(){
		return m_iNowPosNum;
	}
	void setNowPos(int i_iNum);
};

/*************************************************************************
class Coil  public SpriteObject

�S���ҁF�{�����V
�p�r�@�F�R�C��
*************************************************************************/
class	Coil	: public SpriteObject{
	MagnetFieldMini*	m_pMagnetField;
	LPDIRECT3DTEXTURE9 m_pTextureN;
	LPDIRECT3DTEXTURE9 m_pTextureS;
	D3DXVECTOR3		m_vPos;
	D3DXVECTOR3		m_vScale;
	D3DXVECTOR3		m_vRot;
	float			m_fRotZ;
	POLE			m_bMagnetPole;
public:
	Coil(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTextureN	,
		const LPDIRECT3DTEXTURE9	pTextureS	,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const D3DXVECTOR3&			vCenter		,
		const RECT*					pRect		
	);
	~Coil();
	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
	float	getRotZ(){
		return m_fRotZ;
	}
	D3DXVECTOR3 getPos(){
		return m_vPos;
	}
};

/**************************************************************************
class Factory_Title;

�p�r�@�F���C���H��N���X
�S���ҁF������
****************************************************************************/
class Factory_Title{
public:
/**************************************************************************
 Factory_Title(FactoryPacket* fpac);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_Title(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Factory_Title();
};

}
//end of namespace bomberobject.
}
//end of namespace wiz.
