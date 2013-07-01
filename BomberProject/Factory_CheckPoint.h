////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_CheckPoint.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	引継ぎ			：本多 寛之
//	編集			：佐藤 涼
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
const	float	EFFECT_SIZE		= 2.0f;
/**************************************************************************
class CheckEffect;

用途　：説明文の挿入
担当者：佐藤涼
**************************************************************************/
class CheckEffect : public PrimitiveBox{
	D3DXMATRIX		m_Matrix;
	bool			m_bVanish;		//消えたフラグ
	PlayerCoil*		m_pCoil;
	float			m_fPosY;		//棒状の描画すべき位置
	D3DXVECTOR3		m_vPointScale;	//ポイント状のサイズ
	D3DXVECTOR3		m_vPointPos;	//ポイント状の描画位置

	struct EffectItem{
		D3DXVECTOR3		m_vPos		;	//エフェクトの描画位置
		D3DXVECTOR3		m_vScale	;	//エフェクトの大きさ
		float			m_fInitPosX	;	//エフェクトの初期位置
		bool			m_bStart	;	//アニメーションの開始フラグ

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
	CheckEffect(LPDIRECT3DDEVICE9 pD3DDevice,
				D3DXVECTOR3		vPos,
				float			fLength,
				LPDIRECT3DTEXTURE9 pTexture,
				wiz::OBJID id = OBJID_3D_WALL
				);
	
	~CheckEffect();

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

	void PointDraw( DrawPacket& i_DrawPacket );

	void setTexDraw(DrawPacket& i_DrawPacket);

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
	void update( D3DXVECTOR3& o_vPos , float i_fInitPosX, D3DXVECTOR3& o_vScale, bool& o_bStart, DrawPacket& i_DrawPacket);

	void	addEffect( float i_vPosX, float i_vPosY);
	void	setMatrix( const D3DXVECTOR3 i_vPos, const D3DXVECTOR3 i_vScale );
///************************************
//関数名　：void Pos_Update( int i )
//用途　　：描画位置の更新
//カテゴリ：
//引数　　：int i     //変更したいエフェクトの指定
//戻り値　：
//担当者　：佐藤涼
//備考　　：
//************************************/
	void	Pos_Update( float& i_fPosX );
///*************************************
//関数名　：void	Reduction()
//用途　　：サイズ縮小
//カテゴリ：
//引数　　：
//戻り値　：
//担当者　：佐藤涼
//備考　　：
//*************************************/
	void	Reduction( D3DXVECTOR3& o_vScale );

///*************************************
//関数名　：void Expansion()
//用途　　：サイズ拡大（拡大率は縦横等価）
//カテゴリ：
//引数　　：
//戻り値　：
//担当者　：佐藤涼
//備考　　：
//*************************************/
	void	Expansion();

///*****************************************
//エフェクトの状態を初期に戻す
//*****************************************/
	void	ResetState( D3DXVECTOR3& o_vPos, float i_fInitPosX, D3DXVECTOR3& o_vScale, bool& o_bStart );

///*************************************
//関数名　：void setPosY( float posY )
//用途　　：Y座標のみ変更
//カテゴリ：
//引数　　：float posY   //変更後Y座標
//戻り値　：
//担当者　：佐藤涼
//備考　　：
//*************************************/
	void	setInitPosY( float posY );

	void	setPosY( float posY );

	void	setPointPos( const D3DXVECTOR3& pos ){
		m_vPointPos	= pos;
	}

///******************************************
//関数名　：void setStart( bool i_bStart )
//用途　　：アニメーション
//カテゴリ：
//引数　　：bool i_bStart    //アニメーション開始フラグ
//戻り値　：
//担当者　：佐藤涼
//備考　　：
//******************************************/
	void	setStart(bool i_bStart);

///******************************************
//関数名　：bool getMark()
//用途　　：中途開始地点の描画をしているか
//カテゴリ：
//引数　　：
//戻り値　：bool値　中途開始地点の描画をしているか
//担当者　：佐藤涼
//備考　　：
//******************************************/
	bool	getVanish(){
		return	m_bVanish;
	}

};

/******************************************************:
******************************************************/
class CheckPoint : public Object{
protected:
	struct ITEM{
		float			fPosY		;
		DWORD			dwThisPoint	;
		D3DXVECTOR3		vStartPos	;
		ITEM(D3DXVECTOR3 i_vPos, DWORD dwPoint)
			:fPosY( i_vPos.y ),vStartPos(i_vPos)
		{}
	};
	typedef vector< ITEM* > ITEMCONTAINER	;
	ITEMCONTAINER			m_ItemContainer ;
	size_t					m_ActiveItem    ;
	Camera*					m_pCamera		;
	PlayerCoil*				m_pCoil			;
	CheckEffect*			m_pEffect		;
	D3DCOLORVALUE			m_Color			;
	float					m_Thicken		;
	float					m_Length		;
	LPDIRECT3DTEXTURE9		m_pTexture		;
	LPDIRECT3DTEXTURE9		m_pTexturePoint	;
	LPDIRECT3DTEXTURE9		m_pTextureLast	;
	D3DXVECTOR3				m_vPos			;
	SpriteObject*			m_pPintMark		;
	TimeScore*				m_pTime			;
	float					m_fInitPosY		;
	bool					m_bPlayerPass	;
	bool					m_bFirstRead	;
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
	CheckPoint( LPDIRECT3DDEVICE9 pD3DDevice,
				float fLength,
				LPDIRECT3DTEXTURE9 pTexture,
				LPDIRECT3DTEXTURE9 pTexture2, 
				LPDIRECT3DTEXTURE9 pTexture3, 
				wiz::OBJID id = OBJID_SYS_CHECKPOINT );
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
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：継承したものでも必ずとも定義をしなくても良い
	////            ：
	////
    virtual void Update( UpdatePacket& i_UpdatePacket );

	void PlayerPass(UpdatePacket& i_UpdatePacket);
	/////////////////// ////////////////////
	//// 関数名     ：virtual void Draw( DrawPacket& i_DrawPacket )
	//// 用途       ：
	//// カテゴリ   ：純粋仮想関数
	//// 用途       ：オブジェクトをディスプレイに表示する
	//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
	////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
	////            ：  ├ Tempus2*            i_DrawPacket.pTime	   // 時間を管理するクラスへのポインター
	////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：継承するものは何れかのレベルで必ず定義をすること｡
	////            ：
	////
    virtual void Draw( DrawPacket& i_DrawPacket ) ;
	/////////////////// ////////////////////
	//// 関数名     ：virtual void Draw( DrawPacket& i_DrawPacket )
	//// 用途       ：
	//// カテゴリ   ：
	//// 用途       ：チェックポイントを追加
	//// 引数       ：
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	void add(D3DXVECTOR3 i_vPos){
		m_vPos	= i_vPos;
		m_ItemContainer.push_back( new ITEM( i_vPos , m_ItemContainer.size() +1) );
	}

	/////////////////// ////////////////////
	//// 関数名     ：
	//// 用途       ：
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
		m_ActiveItem = Point ;
		return m_ItemContainer[Point]->vStartPos ;
	};

	/////////////////// ////////////////////
	//// 関数名     ：
	//// 用途       ：
	//// カテゴリ   ：
	//// 用途       ：
	//// 引数       ：
	//// 戻値       ：
	//// 担当者     ：
	//// 備考       ：
	////            ：
	////
	D3DXVECTOR3 getLastPosition(){
		//if( m_ItemContainer.size() < Point ) Point = m_ItemContainer.size() ;
		//m_ActiveItem = Point ;
		return m_ItemContainer[m_ItemContainer.size()-1]->vStartPos ;
	};
	/////////////////// ////////////////////
	//// 関数名     ：
	//// 用途       ：
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
