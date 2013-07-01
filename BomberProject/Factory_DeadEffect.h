////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_DeadEffect.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤涼
//	内包ﾃﾞｰﾀと備考	：爆散エフェクト
//					▼
//	namespace wiz;
//		class DeadEffect ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Coil.h"

namespace wiz{
namespace bomberobject{

extern class PlayerCoil ;
const int PARTICLS_NUM	= 50;
//const int PARTICLS_NUM_ENEMY = 20; 

/**************************************************************************
class DeadEffect;

用途　：説明文の挿入
担当者：佐藤涼
**************************************************************************/
class DeadEffect : public PrimitiveBox{

	struct EffectItem{
		D3DXVECTOR3		m_vPos	;
		float			m_fDir	;

		EffectItem(){}
		virtual ~EffectItem(){}
	};

	multimap<float,EffectItem*>		m_ItemMap_Target	;	//描画対象のWallItem

public:
	/////////////////// ////////////////////
	//// 用途       ：Description(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_3D_WALL);
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：
	//// 引数       ：LPDIRECT3DDEVICE9 pD3DDevice //デバイス
	////			  : LPDIRECT3DTEXTURE9 pTexture  //テクスチャ
	////			  : pTexture,wiz::OBJID id = OBJID_3D_WALL //ID
	//// 戻値       ：無し
	//// 担当者     ：佐藤涼
	//// 備考       ：
	DeadEffect(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3			vPos,
				wiz::OBJID id = OBJID_3D_DEADEFFECT
				);

	~DeadEffect();

	void	addEffect( D3DXVECTOR3 vPos,float fDir );
	/////////////////// ////////////////////
	//// 用途       ：void Draw( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：関数
	//// 用途       ：オブジェクトをディスプレイに表示する
	//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
	////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
	////            ：  ├ Tempus2*            i_DrawPacket.pTime	   // 時間を管理するクラスへのポインター
	////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
	//// 戻値       ：無し
	//// 担当者     ：佐藤涼
	//// 備考       ：
	void Draw( DrawPacket& i_DrawPacket );

	/////////////////// ////////////////////
	//// 用途       ：void update( int i )
	//// カテゴリ   ：関数
	//// 用途       ：オブジェクトを更新
	//// 引数       ：
	//// 戻値       ：無し
	//// 担当者     ：佐藤涼
	//// 備考       ：
	////            ：
	////
	void Update( UpdatePacket& i_UpdatePacket );

	void	setMatrix(D3DXVECTOR3 vPos);
	void	setPos( D3DXVECTOR3 i_vPos );

	float	getColor(){
		return	m_Material.Ambient.r;
	}
};

/**************************************************************************
class Factory_DeadEffct;

用途　：メイン工場クラス
担当者：佐藤涼
****************************************************************************/
class Factory_DeadEffect{
public:
/**************************************************************************
 Factory_DeadEffct(FactoryPacket* fpac);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_DeadEffect(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Factory_DeadEffect();
};

}
}