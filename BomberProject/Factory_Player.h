////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Player.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹 曳地大洋(編集) 本多寛之(編集)
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Player ;
//
#pragma once

#include "StdAfx.h"
#include "Factory_Coil.h"
#include "Factory_Magnetic.h"
#include "Factory_Gage.h"
#include "Factory_Sound.h"

const int	START_EFFECTIVE_RANGE		= 12;
const int 	START_EFFECTIVE_RANGE_QUAD	= (START_EFFECTIVE_RANGE * START_EFFECTIVE_RANGE);
const int	PLAYER_RECOVERY_POINT		= 1;
const int	PLAYER_CONSUME_POIMT		= 1;
const int	PLAYER_INVOCATION_POINT		= 40;

namespace wiz{


//**************************************************************************//
// class ProvisionalPlayer : public MagneticumObject ;
//
// 担当者  : 鴫原 徹
// 用途    : 仮のユーザー設置磁界
//**************************************************************************//
//class ProvisionalPlayer : public MagneticumObject{
//public:
//	//	: 
//	ProvisionalPlayer( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
//		D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
//		Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_MAGNET );
//	//	: 
//	void Update( UpdatePacket& i_UpdatePacket );
//};

// 3D用
//**************************************************************************//
// class ProvisionalPlayer3D : public MagneticumObject ;
//
// 担当者  : 曳地大洋
// 用途    : 仮のユーザー設置磁界
//**************************************************************************//
class ProvisionalPlayer3D : public MagneticumObject3D{
	Camera*			m_Camera;
	PlayerCoil*		m_pPlayerCoil;
	Sound*			m_pSound;
	MagneticGage_N* m_pMGage_N;
	MagneticGage_S* m_pMGage_S;
	D3DXMATRIX		m_Matrix ;
	D3DXVECTOR3		m_vPos ;
	D3DXQUATERNION	m_vRot ;
	D3DXVECTOR3		m_vScale ;
	float			m_MovePosY;
	bool			m_bLastMouseRB;
	bool			m_bLastMouseLB;
	bool			m_bDrawing;
	COIL_STATE		m_enumCoilState;
	//struct PolyItem{
	//	LPDIRECT3DTEXTURE9 m_pTexture;
	//	D3DMATERIAL9   m_Material;
	//	D3DXMATRIX	   m_Matrix;
	//	D3DXVECTOR3    m_vScale ;
	//	D3DXVECTOR3	   m_vPos ;
	//	D3DXQUATERNION m_vRot;
	//	virtual ~PolyItem(){}
	//};
	//PolyItem				m_Item_Poly;

public:
	//	: 
	ProvisionalPlayer3D( FactoryPacket* fpac, LPDIRECT3DTEXTURE9 pTexture, LPDIRECT3DTEXTURE9 pTexture2,
		D3DXVECTOR3 &vScale, D3DXQUATERNION &vRot, D3DXVECTOR3 &vPos,
		wiz::OBJID id = OBJID_3D_PLAYER );
	/////////////////// ////////////////////
	//// 関数名     ：~ProvisionalPlayer3D();
	//// カテゴリ   ：デストラクタ
	//// 用途       ：破棄
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	~ProvisionalPlayer3D();
	//	:
	void Draw( DrawPacket& i_DrawPacket );
	//	: 
	void Update( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// 関数名     ：D3DXVECTOR3 getPos() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：中心座標を獲得
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	D3DXVECTOR3 getPos() const {
		if( g_bMouseLB || g_bMouseRB ){ 
			return m_vPos	;
		}else{
			return g_vMin	;
		}
	}	;

	/////////////////// ////////////////////
	//// 関数名     ：float getMoveY() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：m_MovePosYを獲得
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	float getMoveY() const { return m_MovePosY	;	}	;

	/****************************************
	関数名　：bool	getDrawing()
	カテゴリ：関数
	用途　　：描画フラグの取得
	引数　　：なし
	戻り値　：描画しているかのフラグ
	担当　　：佐藤涼
	備考　　：
	****************************************/
	bool	getDrawing(){
		return	m_bDrawing;
	}
	/////////////////// ////////////////////
	//// 関数名     ：void setState( COIL_STATE i_State )
	//// カテゴリ   ：セッター
	//// 用途       ：状態を変更
	//// 引数       ：COIL_STATE i_State
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	void setState( COIL_STATE i_State ){ m_enumCoilState = i_State; }	;
};

/************************************************************************
class MagneticField : public Cylinder

担当者	: 佐藤涼
用途	: 磁界の範囲
************************************************************************/
class	MagneticField : public Cylinder{
	POLE		m_Pole;	//磁界の極：t=S極, f=N極
	bool		m_bEffect;
	D3DXVECTOR3	m_vNormalSize;
	D3DXMATRIX	m_mMatrix;
public:
	MagneticField(LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
		D3DXVECTOR3 &vScale, D3DXQUATERNION &vRot, D3DXVECTOR3 &vPos,bool bEffect);
    void	Draw(DrawPacket& i_DrawPacket) ;
	void	Update(UpdatePacket& i_UpdatePacket);

	void	setPole( POLE pole ){
		m_Pole	= pole;
	}
	POLE	getPole(){
		return	m_Pole;
	}
};


/**************************************************************************
 class Factory_Player;
 用途: メイン工場クラス
****************************************************************************/
class Factory_Player{
public:
/**************************************************************************
 Factory_Player(
	FactoryPacket* fpac //パケットデータ
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_Player( FactoryPacket* fpac );
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Factory_Player();
};
}
//end of namespace wiz.
