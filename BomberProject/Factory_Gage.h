////////////////////////////// //////////////////////////////
//	vWFNg	FBomberProject
//	t@C¼		FFactory_Gage.h
//	J­Â«		FMSVC++ 2008
//	ÅK^u		F4
//	SÒ			F²¡@Á {½°V(ÒW)
//	àïÃÞ°ÀÆõl	FQ[Wt@Ng[
//					¥
//	namespace wiz;
//		class Gage;
//		class SuperGage;
//		class MagneticGage_N;
//		class MagneticGage_S;
//		class Factory_Item ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"

const	int		SUPER_GAGE_MAX		= 512;
const	int		MAGNETIC_GAGE_MAX	= 256;

namespace wiz{

/************************************************
class Gage : public SpriteObject

pr@FX[p[[hpÌQ[W
SÒF²¡Á {½°V(ÒW)
*************************************************/
class Gage : public SpriteObject{
	Rect	m_Rect;
	Rect	m_Rect2;
public:
	Gage(
		LPDIRECT3DDEVICE9 pD3DDevice,	//	: foCX
		LPDIRECT3DTEXTURE9 pTex,		//	: RAªÌTexture
		D3DXVECTOR3 &vScale,			//	: Lk
		D3DXVECTOR3 &vRot,				//	: ñ]
		D3DXVECTOR3 &vPos,				//	: Êu
		D3DXVECTOR3 &vDirOffset,		//	: `æItZbg
		RECT* vRect  = NULL,				//	: `æÍÍ
		RECT* vRect2 = NULL,				//	: `æÍÍ
		wiz::OBJID id	=OBJID_UI_GAUGE	//	: ID
	);

	void	Recovery( int i_iValue, int i_iMaxValue );	//	: GlM[Ìñ
	void	Consume( int i_iValue );	//	: GlM[ÌÁï
    void	Draw(DrawPacket& i_DrawPacket) ;
	
	RECT getRect2()const{
		return m_Rect2;
	}

	void setRect2_Right(int i_iValue){
		m_Rect2.right = i_iValue;
	}
};

/************************************************
class SuperGage : public SpriteObject

pr@FX[p[[hpÌQ[W
SÒF²¡Á {½°V(ÒW)
*************************************************/
class SuperGage : public Gage{
public:
	SuperGage(
		LPDIRECT3DDEVICE9 pD3DDevice,	//	: foCX
		LPDIRECT3DTEXTURE9 pTex,		//	: RAªÌTexture
		D3DXVECTOR3 &vScale,			//	: Lk
		D3DXVECTOR3 &vRot,				//	: ñ]
		D3DXVECTOR3 &vPos,				//	: Êu
		RECT* vRect  = NULL,			//	: `æÍÍ
		RECT* vRect2 = NULL,			//	: `æÍÍ
		wiz::OBJID id	=OBJID_UI_GAUGE		//	: ID
	);

    void	Draw(DrawPacket& i_DrawPacket) ;
};

/************************************************
class MagneticGage_N : public Gage

pr@FN¥EpÌQ[W
SÒF{½°V
*************************************************/
class MagneticGage_N : public Gage{
public:
	MagneticGage_N(
		LPDIRECT3DDEVICE9	pD3DDevice,			//	: foCX
		LPDIRECT3DTEXTURE9	pTex,				//	: RAªÌTexture
		D3DXVECTOR3			&vScale,			//	: Lk
		D3DXVECTOR3			&vRot,				//	: ñ]
		D3DXVECTOR3			&vPos,				//	: Êu
		RECT*				vRect	= NULL,		//	: `æÍÍ
		RECT*				vRect2	= NULL,		//	: `æÍÍ
		wiz::OBJID			id		= OBJID_UI_GAUGE	//	: ID
	);

    void	Draw(DrawPacket& i_DrawPacket) ;
};

/************************************************
class MagneticGage_S : public Gage

pr@FS¥EpÌQ[W
SÒF{½°V
*************************************************/
class MagneticGage_S : public Gage{
public:
	MagneticGage_S(
		LPDIRECT3DDEVICE9	pD3DDevice,			//	: foCX
		LPDIRECT3DTEXTURE9	pTex,				//	: RAªÌTexture
		D3DXVECTOR3			&vScale,			//	: Lk
		D3DXVECTOR3			&vRot,				//	: ñ]
		D3DXVECTOR3			&vPos,				//	: Êu
		RECT*				vRect	= NULL,		//	: `æÍÍ
		RECT*				vRect2	= NULL,		//	: `æÍÍ
		wiz::OBJID			id		= OBJID_UI_GAUGE	//	: ID
	);

    void	Draw(DrawPacket& i_DrawPacket) ;
};

/**************************************************************************
 class Factory_Gage;

 pr@FCHêNX
 SÒF²¡Á 
****************************************************************************/
class Factory_Gage{
	public:
	/**************************************************************************
	 Factory_Item(FactoryPacket* fpac);
	 pr: RXgN^iTvIuWFNgðzñÉÇÁ·éj
	 ßèl: Èµ
	***************************************************************************/
		Factory_Gage(FactoryPacket* fpac);
	/**************************************************************************
	 ~MyFactory();
	 pr: fXgN^
	 ßèl: Èµ
	***************************************************************************/
		~Factory_Gage();
	};
}
//end of namespace wiz.
