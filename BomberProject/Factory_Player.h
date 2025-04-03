////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Player.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	引継ぎ			：曳地 大洋
//	└→			：本多 寛之
//	内包データと備考	：プレイヤーが誘導する物体
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
#include "Factory_MagnetField.h"

const int	START_EFFECTIVE_RANGE		= 12;
const int 	START_EFFECTIVE_RANGE_QUAD	= (START_EFFECTIVE_RANGE * START_EFFECTIVE_RANGE);
const float	PLAYER_RECOVERY_POINT		= 0.008f;
const float	PLAYER_CONSUME_POIMT		= 0.006f;
const float	PLAYER_INVOCATION_POINT		= 0.100f;
const float MAGNET_FIELD_ALPHA			= 0.2f;


namespace wiz{
namespace bomberobject{

extern class	MagneticGage_N	;
extern class	MagneticGage_S	;

//**************************************************************************//
// class ProvisionalPlayer : public MagneticumObject ;
//
// 担当者  : 鴫原 徹
// 用途    : 仮のユーザー設置磁界
//**************************************************************************//
//class ProvisionalPlayer : public MagneticumObject{
//public:
//	//	: 
//	ProvisionalPlayer( LPDIRECT3DDEVICE9 pD3DDevice, LPTATRATEXTURE pTexture,
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
class ProvisionalPlayer3D : public MagnetField{
	MouseCursor*	m_pCursor		;
	Camera*			m_Camera		;
	PlayerCoil*		m_pPlayerCoil	;
	MagneticGage_N* m_pMGage_N		;
	MagneticGage_S* m_pMGage_S		;
	D3DXMATRIX		m_Matrix		;
	bool			m_bLastMouseRB	;
	bool			m_bLastMouseLB	;
	bool			m_bDrawing		;
	bool			m_bPlaySound	;
	bool			m_bChangeFirst	;
	//struct PolyItem{
	//	LPTATRATEXTURE m_pTexture;
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
	ProvisionalPlayer3D( LPDIRECT3DDEVICE9 pD3DDevice, LPTATRATEXTURE pTexture, LPTATRATEXTURE pTexture2,
		D3DXVECTOR3 &vScale, D3DXQUATERNION &vRot, D3DXVECTOR3 &vPos,
		wiz::OBJID id = OBJID_3D_USERMAGNET );
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
		if( Cursor2D::pressLorRButton() ){ 
			return m_vPos	;
		}else{
			return g_vMin	;
		}
	}	;

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
//end of namespace bomberobject.
}
//end of namespace wiz.
