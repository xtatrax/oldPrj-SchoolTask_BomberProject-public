////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_CheckPoint.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	引継ぎ			：本多 寛之
//	├─            ：佐藤 涼
//	└─            ：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：チェックポイント
//					▼
//	namespace wiz;
//		namespace bomberobject;
//			class CheckEffect         : public PrimitiveBox	;
//			class CheckPoint          : public Cylinder		;
//			class Factory_CheckPoint  ;
//
#pragma once
//////////
//	: インクルード
#include "Factory_Coil.h"
#include "BassItems.h"
#include "Factory_Score.h"
//	: インクルード
//////////
namespace wiz{
namespace bomberobject{

const	int		DRAWING_NUMBER	= 26;
const	float	EFFECT_SIZE		= 5.0f;
//************************************************//
//class RestartPoint :public Box
//
// 担当者  : 鴫原 徹
// 目的    : STL例外から派生したクラス
//************************************************//
class RestartPoint :public Box{
	float m_fSize ;
public:
	RestartPoint(
		const LPDIRECT3DDEVICE9	pD3DDevice	,
		const LPTATRATEXTURE	pPointTex
	);
	/////////////////// ////////////////////
	//// 関数名     ：virtual void Update( UpdatePacket& i_UpdatePacket )
	//// 用途       ：
	//// カテゴリ   ：仮想関数
	//// 用途       ：オブジェクトを更新
	//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
	////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
	////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
	////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
	////            ：  └       Command            pCommand        // コマンド
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：継承したものでも必ずとも定義をしなくても良い
	////            ：
	////
    virtual void Update( UpdatePacket& i_UpdatePacket );
	/////////////////// ////////////////////
	//// 用途       ：virtual void Draw( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：純粋仮想関数
	//// 用途       ：オブジェクトをディスプレイに表示する
	//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
	////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
	////            ：  ├ Tempus2*            i_DrawPacket.GetTime()	   // 時間を管理するクラスへのポインター
	////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹 本多寛之(編集)
	//// 備考       ：
	////            ：
	////
	void Draw( DrawPacket& i_DrawPacket );


	void ChangePoint( D3DXVECTOR3& i_vNewPos ){
		m_BasePos	= i_vNewPos	;
		m_BasePos.z = 0.01f		;
		m_fSize		= 0.0f		;
	}
};

//************************************************//
//class CheckPoint : public Box
//
// 担当者  : 鴫原 徹
// 引継ぎ  : 本多 寛之
// ├─    : 佐藤 涼
// └─    : 鴫原 徹
// 目的    : STL例外から派生したクラス
//************************************************//
class CheckPoint : public Box{
protected:
	//	: 振る舞いの状態
	enum BEHAVIORSTATE{
		BEHAVIORSTATE_WAIT		,
		BEHAVIORSTATE_REDUCTION	,
		BEHAVIORSTATE_LAST		,
	};
	//	: 仕事の状態
	enum WORKSTATE{
		WORKSTATE_UNFINSHED		,
		WORKSTATE_COMPLETION	,
	};
	struct ITEM{
		float			fPosY		;
		DWORD			dwThisPoint	;
		D3DXVECTOR3		vStartPos	;
		ITEM(D3DXVECTOR3 i_vPos, DWORD dwPoint)
			:fPosY( i_vPos.y ),vStartPos(i_vPos)
		{}
	};
	D3DXVECTOR3				m_vLineScale		;
	D3DXVECTOR3				m_vStringScale		;
	typedef vector< ITEM* > ITEMCONTAINER		;
	LPTATRATEXTURE			m_pTxLine			;
	LPTATRATEXTURE			m_pTxCheckString	;
	LPTATRATEXTURE			m_pTxLastString		;
	ITEMCONTAINER			m_ItemContainer		;	//	: チェックポイントを格納している配列
	size_t					m_ActiveItem		;	//	: 次のチェックポイント
	BEHAVIORSTATE			m_enumNowState		;	//	: 現在の状態
	float					m_fBassLength		;	//	: チェックポイントバーの元の長さ
	float					m_fReductionTime	;	//	: 縮小する速さ
	Camera*					m_pCamera			;	//	: 
	PlayerCoil*				m_pCoil				;	//	: 通過を確認するためにポインターを保持
	TimeScore*				m_pTime				;	//	: 時間をリセットするためポインターを保持
	RestartPoint*			m_pRestartPoint		;	//	: リスタートポイント

	/////////////////// ////////////////////
	//// 関数名     ：
	//// カテゴリ   ：メンバ関数
	//// 用途       ：
	//// 引数       ：
	////            ：
	//// 戻値       ：
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	void SetTarget();

	/////////////////// ////////////////////
	//// 関数名     ：
	//// カテゴリ   ：メンバ関数
	//// 用途       ：
	//// 引数       ：
	////            ：
	//// 戻値       ：
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	void RemoveTarget();

public:
	/////////////////// ////////////////////
	//// 関数名     ：
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：
	//// 引数       ：
	////            ：
	//// 戻値       ：
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	CheckPoint( LPDIRECT3DDEVICE9 pD3DDevice,
				float			fLength,
				LPTATRATEXTURE	pLineTex				,
				LPTATRATEXTURE	pCheckPointStringTex	,
				LPTATRATEXTURE	pLastStingTex			,
				wiz::OBJID		id = OBJID_SYS_CHECKPOINT );
	/////////////////// ////////////////////
	//// 関数名     ：
	//// カテゴリ   ：デストラクタ
	//// 用途       ：
	//// 引数       ：
	////            ：
	//// 戻値       ：
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	~CheckPoint();
	/////////////////// ////////////////////
	//// 関数名     ：virtual void Update( UpdatePacket& i_UpdatePacket )
	//// 用途       ：
	//// カテゴリ   ：仮想関数
	//// 用途       ：オブジェクトを更新
	//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
	////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
	////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
	////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
	////            ：  └       Command            pCommand        // コマンド
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：継承したものでも必ずとも定義をしなくても良い
	////            ：
	////
    virtual void Update( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// 関数名     ：
	//// カテゴリ   ：メンバ関数
	//// 用途       ：
	//// 引数       ：
	////            ：
	//// 戻値       ：
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	void PlayerPass(UpdatePacket& i_UpdatePacket);

	/////////////////// ////////////////////
	//// 関数名     ：
	//// カテゴリ   ：メンバ関数
	//// 用途       ：
	//// 引数       ：
	////            ：
	//// 戻値       ：
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	WORKSTATE Reduction(UpdatePacket& i_UpdatePacket);

	/////////////////// ////////////////////
	//// 関数名     ：virtual void Draw( DrawPacket& i_DrawPacket )
	//// 用途       ：
	//// カテゴリ   ：純粋仮想関数
	//// 用途       ：オブジェクトをディスプレイに表示する
	//// 引数       ：  DrawPacket& i_DrawPacket						// 画面描画時に必要なデータ群 ↓内容下記
	////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice				// IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  ├ vector<Object*>&    Vec						// オブジェクトの配列
	////            ：  ├ Tempus2*            i_DrawPacket.GetTime()	// 時間を管理するクラスへのポインター
	////            ：  └ Command             i_DrawPacket.pCommand	// コマンド
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：継承するものは何れかのレベルで必ず定義をすること｡
	////            ：
	////
    virtual void Draw( DrawPacket& i_DrawPacket ) ;

	/////////////////// ////////////////////
	//// 関数名     ：
	//// カテゴリ   ：メンバ関数
	//// 用途       ：
	//// 引数       ：
	////            ：
	//// 戻値       ：
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	void DrawLine( DrawPacket& i_DrawPacket );

	/////////////////// ////////////////////
	//// 関数名     ：virtual void Draw( DrawPacket& i_DrawPacket )
	//// 用途       ：
	//// カテゴリ   ：メンバ関数
	//// 用途       ：チェックポイントを追加
	//// 引数       ：
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	void add(D3DXVECTOR3 i_vPos){
		//m_vPos	= i_vPos;
		m_ItemContainer.push_back( new ITEM( i_vPos , m_ItemContainer.size() +1) );
	}

	/////////////////// ////////////////////
	//// 関数名     ：
	//// 用途       ：メンバ関数
	//// カテゴリ   ：
	//// 用途       ：
	//// 引数       ：
	//// 戻値       ：
	//// 担当者     ：
	//// 備考       ：
	////            ：
	////
	D3DXVECTOR3 getThisPosition(DWORD Point){
		//	: 
		if( m_ItemContainer.size() < Point ) Point = m_ItemContainer.size()-1 ;
		//m_ActiveItem = Point ;
		return m_ItemContainer[Point]->vStartPos ;
	};

	/////////////////// ////////////////////
	//// 関数名     ：
	//// 用途       ：メンバ関数
	//// カテゴリ   ：
	//// 用途       ：
	//// 引数       ：
	//// 戻値       ：
	//// 担当者     ：
	//// 備考       ：
	////            ：
	////
	D3DXVECTOR3 getLastPosition(){
		return m_ItemContainer[m_ItemContainer.size()-1]->vStartPos ;
	};

	/////////////////// ////////////////////
	//// 関数名     ：
	//// 用途       ：メンバ関数
	//// カテゴリ   ：
	//// 用途       ：
	//// 引数       ：
	//// 戻値       ：
	//// 担当者     ：
	//// 備考       ：
	////            ：
	////
	size_t getActiveItem(){
		return m_ActiveItem ;
	}
	/////////////////// ////////////////////
	//// 関数名     ：
	//// 用途       ：メンバ関数
	//// カテゴリ   ：
	//// 用途       ：
	//// 引数       ：
	//// 戻値       ：
	//// 担当者     ：
	//// 備考       ：
	////            ：
	////
	bool ActiveIsLast(){
		return m_ActiveItem >= m_ItemContainer.size()-1;
	}

	void	EffectCreate(LPDIRECT3DDEVICE9 pD3DDevice);
	void	setTexPos( size_t i_ActiveItem, float fTexPosY );
};

/**************************************************************************
 class Factory_CheckPoint;
 用途: メイン工場クラス
****************************************************************************/
class Factory_CheckPoint{
public:
/**************************************************************************
 Factory_CheckPoint(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr			//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_CheckPoint(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Factory_CheckPoint();
};
}
//end of namespace bomberobject.
}
//end of namespace wiz.
