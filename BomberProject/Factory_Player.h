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

#define  MGPRM_MAGNETICUM	200  /* 磁界の影響半径( 現在単位 pixel ) */
#define  MGPRM_MAGNETICUM_QUAD ( MGPRM_MAGNETICUM * MGPRM_MAGNETICUM )
#define  PLAYER_SPEED		(   0.5f ) 
#define  PLAYER_BASSROT		( 270.0f ) 


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
		Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_PLAYER );
	//	: 
	void Update( UpdatePacket& i_UpdatePacket );
};


//**************************************************************************//
// class PlayerCoil : public MagneticumObject ;
//
// 担当者  : 鴫原 徹
// 用途    : コイル
//**************************************************************************//
class PlayerCoil : public MagneticumObject{


	//	: コイルの方向指標用パーツ
	SpriteObject*		m_pDirParts		;

	//PrimitiveCylinder*			m_pDirParts3D;
	Cylinder*			m_pDirParts3D;

	//	: 
	ProvisionalPlayer*	m_pPlayer		;

	float		m_fMoveDir   ;//角度
	float       m_fMovdSpeed ;//速度

	//仮
	//Color			m_Color;
	//bool			m_bMagnetPole ;
	//void setPoleS(){ m_bMagnetPole = POLE_S  ; m_Color = 0xFF0000FF	; } ;
	//void setPoleN(){ m_bMagnetPole = POLE_N	 ; m_Color = 0xFFFF0000	; } ;
	/////////////////// ////////////////////
	//// 関数名     ：void ChangePole()
	//// カテゴリ   ：非公開アクセッサ
	//// 用途       ：磁極を反転させる
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 備考       ： 磁極フラグとカラーを変更する
	////            ：
	////
	//	bool ChangePole(){
	//		if( m_bMagnetPole == POLE_S )	{ setPoleN() ; }
	//		else							{ setPoleS() ; }
	//		return true ;
	//	}

public:
/////////////////// ////////////////////
//// 関数名     ：PlayerCoil( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
////            ：    D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
////            ：    Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_PLAYER )
//// カテゴリ   ：コンストラクタ
//// 用途       ：
//// 引数       ：
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：
////            ：
////
	PlayerCoil(
		LPDIRECT3DDEVICE9 pD3DDevice,				//	: デバイス
		LPDIRECT3DTEXTURE9 pCoreTexture,			//	: コア部分のTexture
		LPDIRECT3DTEXTURE9 pDirTexture,				//	: 方向を表す三角のてくすたー
		D3DXVECTOR3 &vScale,						//	: 伸縮
		D3DXVECTOR3 &vRot,							//	: 回転
		D3DXVECTOR3 &vPos,							//	: 位置
		D3DXVECTOR3 &vDirOffset,					//	: 方向を表す三角の描画オフセット
		RECT* pCoreRect = NULL,						//	: 描画範囲
		RECT* pDirRect = NULL,						//	: 描画範囲
		wiz::OBJID id = OBJID_3D_PLAYER				//	: ID
	);

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
	D3DXVECTOR3 getPos() const { return m_pDirParts3D->getPos()	;	}	;


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
