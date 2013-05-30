////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Gage.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼 本多寛之(編集)
//	内包ﾃﾞｰﾀと備考	：ゲージファクトリー
//					▼
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

用途　：スーパーモード用のゲージ
担当者：佐藤涼 本多寛之(編集)
*************************************************/
class Gage : public SpriteObject{
	Rect	m_Rect;
	Rect	m_Rect2;
public:
	Gage(
		LPDIRECT3DDEVICE9 pD3DDevice,	//	: デバイス
		LPDIRECT3DTEXTURE9 pTex,		//	: コア部分のTexture
		D3DXVECTOR3 &vScale,			//	: 伸縮
		D3DXVECTOR3 &vRot,				//	: 回転
		D3DXVECTOR3 &vPos,				//	: 位置
		D3DXVECTOR3 &vDirOffset,		//	: 描画オフセット
		RECT* vRect  = NULL,				//	: 描画範囲
		RECT* vRect2 = NULL,				//	: 描画範囲
		wiz::OBJID id	=OBJID_UI_GAUGE	//	: ID
	);

	void	Recovery( int i_iValue, int i_iMaxValue );	//	: エネルギーの回復
	void	Consume( int i_iValue );	//	: エネルギーの消費
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

用途　：スーパーモード用のゲージ
担当者：佐藤涼 本多寛之(編集)
*************************************************/
class SuperGage : public Gage{
public:
	SuperGage(
		LPDIRECT3DDEVICE9 pD3DDevice,	//	: デバイス
		LPDIRECT3DTEXTURE9 pTex,		//	: コア部分のTexture
		D3DXVECTOR3 &vScale,			//	: 伸縮
		D3DXVECTOR3 &vRot,				//	: 回転
		D3DXVECTOR3 &vPos,				//	: 位置
		RECT* vRect  = NULL,			//	: 描画範囲
		RECT* vRect2 = NULL,			//	: 描画範囲
		wiz::OBJID id	=OBJID_UI_GAUGE		//	: ID
	);

    void	Draw(DrawPacket& i_DrawPacket) ;
};

/************************************************
class MagneticGage_N : public Gage

用途　：N磁界用のゲージ
担当者：本多寛之
*************************************************/
class MagneticGage_N : public Gage{
public:
	MagneticGage_N(
		LPDIRECT3DDEVICE9	pD3DDevice,			//	: デバイス
		LPDIRECT3DTEXTURE9	pTex,				//	: コア部分のTexture
		D3DXVECTOR3			&vScale,			//	: 伸縮
		D3DXVECTOR3			&vRot,				//	: 回転
		D3DXVECTOR3			&vPos,				//	: 位置
		RECT*				vRect	= NULL,		//	: 描画範囲
		RECT*				vRect2	= NULL,		//	: 描画範囲
		wiz::OBJID			id		= OBJID_UI_GAUGE	//	: ID
	);

    void	Draw(DrawPacket& i_DrawPacket) ;
};

/************************************************
class MagneticGage_S : public Gage

用途　：S磁界用のゲージ
担当者：本多寛之
*************************************************/
class MagneticGage_S : public Gage{
public:
	MagneticGage_S(
		LPDIRECT3DDEVICE9	pD3DDevice,			//	: デバイス
		LPDIRECT3DTEXTURE9	pTex,				//	: コア部分のTexture
		D3DXVECTOR3			&vScale,			//	: 伸縮
		D3DXVECTOR3			&vRot,				//	: 回転
		D3DXVECTOR3			&vPos,				//	: 位置
		RECT*				vRect	= NULL,		//	: 描画範囲
		RECT*				vRect2	= NULL,		//	: 描画範囲
		wiz::OBJID			id		= OBJID_UI_GAUGE	//	: ID
	);

    void	Draw(DrawPacket& i_DrawPacket) ;
};

/**************************************************************************
 class Factory_Gage;

 用途　：メイン工場クラス
 担当者：佐藤涼 
****************************************************************************/
class Factory_Gage{
	public:
	/**************************************************************************
	 Factory_Item(FactoryPacket* fpac);
	 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
	 戻り値: なし
	***************************************************************************/
		Factory_Gage(FactoryPacket* fpac);
	/**************************************************************************
	 ~MyFactory();
	 用途: デストラクタ
	 戻り値: なし
	***************************************************************************/
		~Factory_Gage();
	};
}
//end of namespace wiz.
