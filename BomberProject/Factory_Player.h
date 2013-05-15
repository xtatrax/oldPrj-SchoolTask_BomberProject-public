////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Player.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Player ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Magnetic.h"

#define  MGPRM_MAGNETICUM	10  /* 磁界の影響半径( 現在単位 pixel ) */
#define  MGPRM_MAGNETICUM_QUAD ( MGPRM_MAGNETICUM * MGPRM_MAGNETICUM )
#define  PLAYER_SPEED		(   0.08f ) 
#define  PLAYER_BASSROT		( 90.0f ) 


namespace wiz{



//**************************************************************************//
// class ProvisionalPlayer : public MagneticumObject ;
//
// 担当者  : 鴫原 徹
// 用途    : 仮のユーザー設置磁界
//**************************************************************************//
class ProvisionalPlayer : public MagneticumObject{
public:
	//	: 
	ProvisionalPlayer( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
		D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
		Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_MAGNET );
	//	: 
	void Update( UpdatePacket& i_UpdatePacket );
};

// 3D用
//**************************************************************************//
// class ProvisionalPlayer : public MagneticumObject ;
//
// 担当者  : 曳地大洋
// 用途    : 仮のユーザー設置磁界
//**************************************************************************//
class ProvisionalPlayer3D : public MagneticumObject3D{
	Camera*			m_Camera;
	D3DXMATRIX		m_Matrix ;
	D3DXVECTOR3		m_vPos ;
	D3DXQUATERNION	m_vRot ;
	D3DXVECTOR3		m_vScale ;
	float			m_MovePosY;
	bool			m_bLastMouseRB;
	bool			m_bLastMouseLB;
public:
	//	: 
	ProvisionalPlayer3D( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
		D3DXVECTOR3 &vScale, D3DXQUATERNION &vRot, D3DXVECTOR3 &vPos,
		wiz::OBJID id = OBJID_3D_PLAYER );
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

};


//**************************************************************************//
// class PlayerCoil : public MagneticumObject ;
//
// 担当者  : 本多寛之
// 用途    : コイル
//**************************************************************************//
class PlayerCoil : public MagneticumObject3D{

	Cylinder*		m_pCylinder ;

	D3DXMATRIX		m_Matrix ;
	D3DXVECTOR3		m_vPos ;
	D3DXQUATERNION	m_vRot ;
	D3DXVECTOR3		m_vScale ;
	float			m_fMoveDir   ;//角度
	float			m_fMovdSpeed ;//速度
	
	ProvisionalPlayer3D*	m_pPlayer;

	Camera* m_pCamera;


public:
	/////////////////// ////////////////////
	//// 関数名     ：PlayerCoil( 	
	////							LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
	////							float Radius1,float Radius2,float Lenght,
	////							D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
	////							D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
	////							wiz::OBJID id = OBJID_3D_PLAYER)
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：
	//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	////			  :   LPDIRECT3DTEXTURE9 pTexture,  //テクスチャ	
	////		      :   float Radius1						//円の直径1
	////		      :   float Radius2						//円の直径2
	////			  :   flaot Lenght						//高さ
	////			  :   D3DXVECTOR3 &vScale
	////		      :   D3DXVECTOR3 &vRot				//回転角
	////		      :   D3DXVECTOR3 &vPos				//位置
	////              :   D3DCOLORVALUE& Diffuse,		//ディフューズ色
	////              :   D3DCOLORVALUE& Specular,		//スペキュラ色
	////              :   D3DCOLORVALUE& Ambient,		//アンビエント色
	////			  : wiz::OBJID id = OBJID_2D_PLAYER //ID
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹 本多寛之(修正)
	//// 備考       ：
	////            ：
	////
	PlayerCoil(
		LPDIRECT3DDEVICE9 pD3DDevice,
		LPDIRECT3DTEXTURE9 pTexture,
		float Radius1,
		float Radius2,
		float Lenght,
		D3DXVECTOR3 &vScale,	
		D3DXVECTOR3 &vRot,
		D3DXVECTOR3 &vPos,
		D3DCOLORVALUE& Diffuse,
		D3DCOLORVALUE& Specular,
		D3DCOLORVALUE& Ambient,
		wiz::OBJID id = OBJID_3D_PLAYER
	);

	/////////////////////// ////////////////////
	//////// 用途       ：	bool HitTestMultiBox(MultiBox* pBox,size_t& Index,D3DXVECTOR3& Vec,D3DXVECTOR3& ElsePos)
	//////// カテゴリ   ：MultiBoxとの衝突判定
	//////// 用途       ：マルチボックスとの衝突判定
	//////// 引数       ：  bool HitTestMultiBox
	////////				  MultiBox* pBox,	//マルチボックス
	////////				  size_t& Index,	//ヒットしていたらインデックスが戻る
	////////				  D3DXVECTOR3& Vec,         //最近接点
	////////				  D3DXVECTOR3& ElsePos         //一つ前のポジション
	//////// 戻値       ：衝突していればtrue
	////////				ヒットしてたらtrue（インデックスと最近接点を代入）
	//////// 担当者     ：曳地 大洋
	//////// 備考       ：
	bool HitTestWall( OBB, float Index );

	/////////////////// ////////////////////
	//// 関数名     ：void Update( UpdatePacket& i_UpdatePacket )
	//// カテゴリ   ：
	//// 用途       ：
	//// 引数       ：
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	void Update( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// 用途       ：virtual void Draw( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：
	//// 用途       ：
	//// 引数       ：
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
    void Draw(DrawPacket& i_DrawPacket) ;

	/////////////////// ////////////////////
	//// 関数名     ：D3DXVECTOR3 getPos() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：中心座標を獲得
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	D3DXVECTOR3 getPos() const { return m_vPos	;	}	;

	/////////////////// ////////////////////
	//// 関数名     ：D3DXVECTOR3 getSpeed() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：速度を獲得
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	float getSpeed() const { return m_fMovdSpeed	;	}	;

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
