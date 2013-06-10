////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_CheckPoint.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹 本多寛之(編集)
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_CheckPoint ;
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
const int PARTICLS_NUM_ENEMY = 20; 

/**************************************************************************
class DeadEffect;

用途　：説明文の挿入
担当者：佐藤涼
**************************************************************************/
class DeadEffect : public PrimitiveBox{
	D3DXMATRIX		m_Matrix;
	D3DXVECTOR3		m_vPos ;
	float			m_fLife;
	float			m_fDir;
	float			m_fSpeed;
	float			m_fAccele;
	int				m_iDirZ;

	PlayerCoil*		m_pCoil;
	Camera*			m_pCamera;
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
	DeadEffect(LPDIRECT3DDEVICE9 pD3DDevice,
				D3DXVECTOR3	vPos,
				float		vDir,
				LPDIRECT3DTEXTURE9 pTexture,
				wiz::OBJID id = OBJID_3D_WALL
				);

	~DeadEffect();
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

	float	getColor(){
		return	m_Material.Ambient.r;
	}
};

}
}