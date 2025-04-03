////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Description.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼
//	内包データと備考	：説明ファクトリー
//					▼
//	namespace wiz;
//		class Factory_Description ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Coil.h"

namespace wiz{
namespace bomberobject{

/**************************************************************************
class ModeChangeChar;

用途　：開始時のスタート文
担当者：佐藤涼
**************************************************************************/
class ModeChangeChar : public SpriteObject{
	bool	m_bAllDraw;
	bool	m_bAnimeDir;
	float	m_fInterval;
	Rect	m_BaseRect;
public:
	ModeChangeChar(LPDIRECT3DDEVICE9	pD3DDevice,
				LPTATRATEXTURE	pTexture,
				D3DXVECTOR3	&vScale,
				Rect*	Rect	= NULL	);

	~ModeChangeChar();
	void	Draw( DrawPacket& i_DrawPacket );
	void	Update( UpdatePacket& i_UpdatePacket );

	void	setStart(){
		m_bAllDraw		= false	;
		m_bAnimeDir		= true	;
		m_fInterval		= 0.0f	;
		m_vOffsetPos.x	= 0.0f	;
		m_pRect->right	= 0		;
	}
};

/**************************************************************************
class StartSprite;

用途　：開始時のスタート文
担当者：佐藤涼
**************************************************************************/
class StartSprite : public SpriteObject{
	D3DXVECTOR3	m_vPos;
	D3DXVECTOR3	m_vStartPos;
	D3DXVECTOR3	m_vScale;
	float		m_vRelayPosY;
	int			m_iTime;
	PlayerCoil*	m_pCoil;
	COIL_STATE	m_State;
	bool		m_bFirst;
	bool		m_bSecond;
public:
	StartSprite(LPDIRECT3DDEVICE9	pD3DDevice,
				LPTATRATEXTURE	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				Rect*	Rect	= NULL);

	~StartSprite();
	void	Draw( DrawPacket& i_DrawPacket );
	void	Update( UpdatePacket& i_UpdatePacket );

	void	ReStart(){
		m_iTime		= 0;
		m_vPos		= m_vStartPos;
		m_bSecond	= true;
		m_Color.byteColor.a	= 0;
		m_State		= COIL_STATE_CONTINUE;
	}
};

/**************************************************************************
class Description;

用途　：説明文の挿入
担当者：佐藤涼
**************************************************************************/
class Description : public PrimitiveBox{
	Camera*			m_pCamera;
	PlayerCoil*		m_pCoil;
	struct DescItem{
		D3DMATERIAL9	m_Material;
		D3DXMATRIX		m_Matrix;
		D3DXVECTOR3		m_vScale ;
		D3DXVECTOR3		m_vPos ;
		D3DXQUATERNION	m_vRot;
		COIL_STATE		m_State;
		bool			m_bCanDisplay;
		bool			m_bDisplay;
		virtual ~DescItem(){}
	};

	//map<オブジェクトのポジション,WallItem>
	multimap<float,DescItem*> m_ItemMap_Desc;	//全てのDescItem
	multimap<float,DescItem*> m_ItemMap_Target; //描画対象のDescItem
public:
	/////////////////// ////////////////////
	//// 用途       ：Description(	LPDIRECT3DDEVICE9 pD3DDevice,LPTATRATEXTURE pTexture,wiz::OBJID id = OBJID_3D_WALL);
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：
	//// 引数       ：LPDIRECT3DDEVICE9 pD3DDevice //デバイス
	////			  : LPTATRATEXTURE pTexture  //テクスチャ
	////			  : pTexture,wiz::OBJID id = OBJID_3D_WALL //ID
	//// 戻値       ：なし
	//// 担当者     ：佐藤涼
	//// 備考       ：
	Description(LPDIRECT3DDEVICE9 pD3DDevice,
				LPTATRATEXTURE pTexture,
				wiz::OBJID id = OBJID_3D_WALL
				);

	/////////////////// ////////////////////
	//// 用途       ：~Description;
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：
	//// 引数       ：
	//// 戻値       ：なし
	//// 担当者     ：鴫原 トオル
	//// 備考       ：
	~Description();

	/////////////////// ////////////////////
	//// 用途       ：void Draw( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：関数
	//// 用途       ：オブジェクトをディスプレイに表示する
	//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
	////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
	////            ：  ├ Tempus2*            i_DrawPacket.GetTime()	   // 時間を管理するクラスへのポインター
	////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
	//// 戻値       ：なし
	//// 担当者     ：佐藤涼
	//// 備考       ：
	void Draw( DrawPacket& i_DrawPacket );

	/////////////////// ////////////////////
	//// 用途       ：void Update( UpdatePacket& i_UpdatePacket )
	//// カテゴリ   ：関数
	//// 用途       ：オブジェクトを更新
	//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
	////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
	////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
	////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
	////            ：  └       Command            pCommand        // コマンド
	//// 戻値       ：なし
	//// 担当者     ：佐藤涼
	//// 備考       ：
	////            ：
	////
	void Update( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// 用途       ：void AddDesc( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：関数
	//// 用途       ：Descの追加
	//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9インターフェイスへのポインタ
	////		    ：  D3DXVECTOR3 &vScale				//拡大縮小
	////		    ：  D3DXVECTOR3 &vRot				//回転角
	////		    ：  D3DXVECTOR3 &vPos				//位置
	////            ：  D3DCOLORVALUE& Diffuse,			//ディフューズ色
	////            ：  D3DCOLORVALUE& Specular,		//スペキュラ色
	////            ：  D3DCOLORVALUE& Ambient,			//アンビエント色
	//// 戻値       ：なし
	//// 担当者     ：佐藤涼
	//// 備考       ：
	void AddDesc(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,COIL_STATE state,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient);

};

/**************************************************************************
class Factory_Description;

用途　：メイン工場クラス
担当者：佐藤涼
****************************************************************************/
class Factory_Description{
public:
/**************************************************************************
 Factory_Description(FactoryPacket* fpac);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_Description(FactoryPacket* fpac);
/**************************************************************************
 ~Factory_Description();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Factory_Description();
};

}
//end of namespace bomberobject.
}
//end of namespace wiz.
