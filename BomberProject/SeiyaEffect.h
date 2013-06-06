/********************************************************************
Effect.h

class Object т-class Effect 宣言部т-class ThreeDimensionsEffect		宣言部
			  |						|		∟class BlockBreakEffect	宣言部
			  |						∟class TwoDimensionsEffect			宣言部
			  |								
			　|-class XMeshEffect	宣言部
			  |
			  ∟class LineEffect	宣言部
********************************************************************/
#pragma once

#include "StdAfx.h"
#include "Object.h"

namespace wiz{
namespace seiyasource{
/**************************************************************************
inline D3DXMATRIX CreateMatrix(
	const D3DXVECTOR3& i_vPos	,	//位置
	const D3DXVECTOR3& i_vSize	,	//大きさ
	const D3DXVECTOR3& i_vRot		//回転
	);
用途 : 位置、大きさ、回転からマトリックスを作成する
戻り値 : なし
**************************************************************************/
inline D3DXMATRIX CreateMatrix(const D3DXVECTOR3& i_vPos , const D3DXVECTOR3& i_vSize , const D3DXVECTOR3& i_vRot)
{
	D3DXMATRIX	mTrans , mScale , mRot ;
	D3DXMatrixTranslation( &mTrans , i_vPos.x , i_vPos.y , i_vPos.z );
	D3DXMatrixScaling( &mScale , i_vSize.x , i_vSize.y , i_vSize.z ) ;
	D3DXMatrixRotationYawPitchRoll( &mRot , D3DXToRadian( i_vRot.y ) ,D3DXToRadian( i_vRot.x ) , D3DXToRadian( i_vRot.z ) );

	return mScale * mRot * mTrans ;

}

//LineEffect用の形を指定する列挙
enum VertexStyle {
	VS_Triangle ,	//三角形
	VS_Square	,	//四角形
	VS_Circle	,	//丸
	VS_Cross	,	//十字
	VS_NameLine	,	//ネーム描画用の線
	VS_Line			//直線
};
/****************************************************************************
class DeviceRenderState 宣言部
用途 : レンダーステートの変更時使用するクラス
***************************************************************************/

class DeviceRenderState{
	//レンダーステート設定用構造体
	struct RENDERSTATE_PARAM 
	{
		D3DRENDERSTATETYPE	type ;
		DWORD				value ;
		/*********************************************************************
		RENDERSTATE_PARAM(
			const D3DRENDERSTATETYPE i_type,
			const DWORD i_value
			)
		用途 : コンストラクタ
		戻り値 : なし
		**********************************************************************/
		RENDERSTATE_PARAM(const D3DRENDERSTATETYPE i_type,const DWORD i_value)
			:type(i_type),value(i_value){}

	};
	
	//変更したいRenderStateの値を入れる
	vector<RENDERSTATE_PARAM> m_RPVec ;

public:
/***********************************************************
void ChangeRenderState(
	const LPDIRECT3DDEVICE9 i_pDevice,	//デバイス
	);
用途 : レンダーステート変更
戻り値 : なし
***********************************************************/
void ChangeRenderState(const LPDIRECT3DDEVICE9 i_pDevice)
{

	vector<RENDERSTATE_PARAM>::size_type RPsz = m_RPVec.size();
	for(vector<RENDERSTATE_PARAM>::size_type i = 0 ; i < RPsz ; i++){
		DWORD dwSaveState;

		i_pDevice->GetRenderState(m_RPVec[i].type,&dwSaveState);		//現在ステータスをもらう
		i_pDevice->SetRenderState(m_RPVec[i].type,m_RPVec[i].value);	//指定したステータスに変更する

		m_RPVec[i].value = dwSaveState ;								//変更前のステータスを入れる
	}
}


/***********************************************************************
void ChangeRS_PointSprite(
	const float					i_fSize  //ポイントスプライトのサイズ
) ;
用途: ポイントスプライトを描画できるようにレンダーステートを変更
戻り値: なし
************************************************************************/
void ChangeRS_PointSprite(const float i_fSize)
{
	// ポイントスプライトの設定
	m_RPVec.push_back(RENDERSTATE_PARAM(D3DRS_POINTSPRITEENABLE	,TRUE				)	);
	m_RPVec.push_back(RENDERSTATE_PARAM(D3DRS_POINTSCALEENABLE	,TRUE				)	);
	m_RPVec.push_back(RENDERSTATE_PARAM(D3DRS_POINTSIZE			,*(DWORD*)&i_fSize	)	);

}

/***********************************************************************
void ChangeRS_ALPHABLENDENABLE_Black() ;
用途: 加算合成をできるようにレンダーステートを変更
戻り値: なし
************************************************************************/
void ChangeRS_ALPHABLENDENABLE_Black()
{
	//加算合成に設定
	m_RPVec.push_back(RENDERSTATE_PARAM(D3DRS_ALPHABLENDENABLE		,TRUE					)	);
	m_RPVec.push_back(RENDERSTATE_PARAM(D3DRS_SRCBLEND				,D3DBLEND_ONE			)	);
	m_RPVec.push_back(RENDERSTATE_PARAM(D3DRS_DESTBLEND				,D3DBLEND_ONE			)	);

	//重なっていてもzバッファの表示をする
	m_RPVec.push_back(RENDERSTATE_PARAM( D3DRS_ZWRITEENABLE			, FALSE			) );	

}

/***********************************************************************
void ChangeRS_ALPHABLENDENABLE_Skeleton() ;
用途: 透明になるようにレンダーステートを変更
戻り値: なし
************************************************************************/
void ChangeRS_ALPHABLENDENABLE_Skeleton()
{
	//透明
	m_RPVec.push_back(RENDERSTATE_PARAM(D3DRS_ALPHABLENDENABLE		,TRUE					) );
	m_RPVec.push_back(RENDERSTATE_PARAM(D3DRS_DESTBLEND				, D3DBLEND_INVSRCALPHA	) );
	m_RPVec.push_back(RENDERSTATE_PARAM( D3DRS_ZWRITEENABLE			, FALSE					) );	

}

/***********************************************************************
void SetDeviceRenderState(
		const D3DRENDERSTATETYPE i_type,
		const DWORD i_value
		);
用途 : レンダーステートの変更内容をm_RSVecに入れる
戻り値 : なし
***********************************************************************/
void SetDeviceRenderState(const D3DRENDERSTATETYPE i_type,const DWORD i_value)
{
	m_RPVec.push_back(RENDERSTATE_PARAM(i_type, i_value ) );
}


};

/*****************************************************************
static Vertex
用途:3D視点頂点データ 
******************************************************************/
struct Vertex
{
D3DXVECTOR3 m_vPos ;	//ゲーム画面での位置
DWORD		m_dwColor ;	//色
D3DXVECTOR2 m_vTex ;	//読み込み画像の位置

public :

/***************************************************************
vertex()
用途：引数付きコンストラクタ
戻り値:なし
****************************************************************/
Vertex()
:m_vPos(D3DXVECTOR3(0.0f,0.0f,0.0f)),m_dwColor(0xFFFFFFFF),m_vTex(D3DXVECTOR2(0.0f,0.0f)){}

/***************************************************************
vertex( 
	D3DXVECTOR3 i_vPos ,	//ゲーム画面での位置
	DWORD		i_dwColor,  //色
	D3DXVECTOR2 i_vTex		//読み込み画像の位置
)
用途：引数付きコンストラクタ
戻り値:なし
****************************************************************/
Vertex(	D3DXVECTOR3 i_vPos, DWORD i_dwColor, D3DXVECTOR2 i_vTex )
	:m_vPos(i_vPos),m_dwColor(i_dwColor),m_vTex(i_vTex){}

/***************************************************************
~Vertex()
用途：デストラクタ
戻り値:なし
****************************************************************/
~Vertex(){}

/**********************************************************************
static DWORD Vertex::getFVF()
用途:アクセッサ(ゲッター)
戻り値: FVF
**********************************************************************/
static DWORD Vertex::getFVF()
{
	return D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 ;
}
/**********************************************************************
static DWORD Vertex::getSize()
用途:アクセッサ(ゲッター)
戻り値: Vertexのデータ量
**********************************************************************/
static DWORD Vertex::getSize()
{
	return sizeof(Vertex) ;
}

};

/*****************************************************************************
struct VertexLineState	宣言部
用途 :  3次元座標上の頂点描画処理を行う
******************************************************************************/
struct VertexLineState
{
	D3DPRIMITIVETYPE		m_PrimitiveType				;	//どの描画をするか
	int						m_iDrawPrimitiveVertexNum	;	//DrawPrimitiveに使用する頂点数
	Vertex*					m_pVertex					;	//頂点データのポインタ
	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer				;	//バッファ
	LPDIRECT3DTEXTURE9*		m_pTexture					;	//テクスチャ
	int						m_iVertexNum				;	//頂点数

	/******************************************************************************
	VertexLineState()
	用途 : コンストラクタ
	戻り値 : なし
	******************************************************************************/
	VertexLineState();

	/******************************************************************************
	VertexLineState::VertexLineState(
			LPDIRECT3DDEVICE9 pD3DDevice ,	//デバイス 
			const wchar_t* i_pFilename		//ファイル名
		)
	用途 : コンストラクタ
	戻り値 : なし
	******************************************************************************/
	VertexLineState(LPDIRECT3DDEVICE9 pD3DDevice , const wchar_t* i_pFilename );

	/******************************************************************************
	~VertexLineState()
	用途 : デストラクタ
	戻り値 : なし
	******************************************************************************/
	~VertexLineState();

	/******************************************************************************
	void SetVertex(
		LPDIRECT3DDEVICE9	pD3DDevice ,	//デバイス
		VertexStyle			i_Style			//Objectの形
		D3DPRIMITIVETYPE	i_PrimitiveType	//描画方法
	);
	用途 : 引数に応じた形を作る
	戻り値 : なし
	******************************************************************************/
	void SetVertex( LPDIRECT3DDEVICE9 pD3DDevice , VertexStyle i_Style  , D3DPRIMITIVETYPE	i_PrimitiveType) ;

	/******************************************************************************
	void SetDownColor( 
		DWORD i_dwColor	//セットしたい色
	) ;
	用途 : 色の変更
	戻り値 : なし
	******************************************************************************/
	void SetDownColor( DWORD i_dwColor ) ;

	/******************************************************************************
	void setVertexPos(
		vector<D3DXVECTOR3*> i_vPosVec	変更したいLineのポジション
	);
	用途 : 頂点の位置を変更する
	戻り値 : なし
	******************************************************************************/
	void setVertexPos( vector<D3DXVECTOR3*> i_vPosVec );

	/******************************************************************************
	void Draw(
		LPDIRECT3DDEVICE9 pD3DDevice ,	//デバイス
		const D3DXMATRIX& i_Matrix		//描画したいプレートの配列
		)
	用途 : 正方形のプレートを描画
	戻り値 : なし
	******************************************************************************/
	void Draw(LPDIRECT3DDEVICE9 pD3DDevice , const D3DXMATRIX& i_Matrix ) ;

};

/*****************************************************************
static Vertex
用途:2D視点の頂点データ 
******************************************************************/
struct Vertexrhw{
D3DXVECTOR3 m_vPos ;	//ゲーム画面での位置
float		m_float		;
DWORD		m_dwColor ;	//色
D3DXVECTOR2 m_vTex ;	//読み込み画像の位置

public :

/***************************************************************
VertexBackGround()
用途：コンストラクタ
戻り値:なし
****************************************************************/
Vertexrhw(){}

/***************************************************************
VertexBackGround( 
	D3DXVECTOR3 i_vPos ,	//ゲーム画面での位置
	DWORD		i_dwColor,  //色
	D3DXVECTOR2 i_vTex		//読み込み画像の位置
)
用途：引数付きコンストラクタ
戻り値:なし
****************************************************************/
Vertexrhw(	D3DXVECTOR3 i_vPos, DWORD i_dwColor, D3DXVECTOR2 i_vTex )
	:m_vPos(i_vPos),m_float(1.0f),m_dwColor(i_dwColor),m_vTex(i_vTex){}

/****************************************************************
~Vertexrhw()
用途 : デストラクタ 
戻り値 : なし
****************************************************************/
~Vertexrhw()
{
}

/**********************************************************************
static DWORD getRHWFVF()
用途:アクセッサ(ゲッター)
戻り値: FVF
**********************************************************************/
static DWORD getRHWFVF()
{
	return  D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 ;
}
/**********************************************************************
static DWORD getRHWSize()
用途:アクセッサ(ゲッター)
戻り値: Vertexrhwのデータ量
**********************************************************************/
static DWORD getRHWSize()
{
	return sizeof( Vertexrhw ) ;
}

};


/******************************************************************************
struct VertexRHWState	宣言部
用途 : 正方形のテクスチャを描画
******************************************************************************/
struct VertexrhwState
{
	static const int		MAXDEGREES	= 360			;	//ディグリ角の最大数
	static const int		VERTEXNUM	= 4				;

	Vertexrhw*				m_pVertexrhw				;	//頂点データのポインタ
	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer				;	//バッファ
	D3DXVECTOR2				m_vTexSize					;	//Rect使用時1枚の大きさ

	/******************************************************************************
	VertexState::VertexrhwState()
	用途 : コンストラクタ
	戻り値 : なし
	******************************************************************************/
	VertexrhwState();

	/******************************************************************************
	VertexState::VertexrhwState(
			LPDIRECT3DDEVICE9 pD3DDevice ,	//デバイス 
		)
	用途 : コンストラクタ
	戻り値 : なし
	******************************************************************************/
	VertexrhwState(LPDIRECT3DDEVICE9 pD3DDevice );

	/******************************************************************************
	~VertexrhwState()
	用途 : デストラクタ
	戻り値 : なし
	******************************************************************************/
	~VertexrhwState();

	/******************************************************************************
	void VertexTransForm(
		const D3DXVECTOR3&	i_vPos  ,	//位置
		const D3DXVECTOR3&	i_vSize ,	//大きさ
		int 				i_fRotZ		//回転
		);
	用途 : 各ステータスから位置を設定する
	戻り値 : なし
	******************************************************************************/
	void VertexTransForm(const D3DXVECTOR3& i_vPos , const D3DXVECTOR3& i_vSize , int i_iRotZ );

	/******************************************************************************
	void VertexRect(
		const D3DXVECTOR2&	i_vTexMaxSize ,	//テクスチャ全体の大きさ
		const D3DXVECTOR2&	i_vSetTexSize ,	//テクスチャの描画したい範囲(大きさ)
		int					i_iRectNum		//レクトの位置
	);
	用途 : 元のテクスチャから描画する範囲を指定する
	戻り値 : なし
	******************************************************************************/
	void VertexRect(const D3DXVECTOR2& i_vTexMaxSize , const D3DXVECTOR2& i_vSetTexSize , int i_iRectNum );

	/******************************************************************************
	void SetColor( 
		DWORD i_dwColor	//セットしたい色
	) ;
	用途 : 色の変更
	戻り値 : なし
	******************************************************************************/
	void SetColor( DWORD i_dwColor ) ;

	/*****************************************************************************
	void UpDate()
	用途 : データの更新
	戻り値 : なし
	*****************************************************************************/
	void UpDate() ; 

	/******************************************************************************
	void Draw(
		LPDIRECT3DDEVICE9 pD3DDevice ,	//デバイス
		)
	用途 : 正方形のプレートを描画
	戻り値 : なし
	******************************************************************************/
	void Draw(LPDIRECT3DDEVICE9 pD3DDevice ) ;

};


/*********************************************************************
class Effect : public Object	宣言部
用途 : 演出用エフェクトの元クラス
*********************************************************************/
class Effect //: public Object
{
protected:
	/*********************************************************************
	clear()
	用途 : 削除処理
	戻り値: なし
	*********************************************************************/
	void clear() ;

	float				m_fEffectSize				;	//エフェクトの大きさ
	LPDIRECT3DTEXTURE9	m_pTexture					;	// テクスチャ
	static const int	m_iVerticesMaxSize = 3500	;	//一つのパーティクルの最大描画数

public:
/*********************************************************************
Effect(
	LPDIRECT3DDEVICE9	pD3DDevice,			//デバイス
	const wchar_t*		i_filename,			//画像のファイル名
	DWORD				i_Decolorisation	//抜きたい色
	float				i_fSize				//エフェクトの大きさ
	)
用途: コンストラクタ
戻り値: なし
*********************************************************************/
Effect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,DWORD i_Decolorisation,float i_fSize) ;

/*********************************************************************
~Effect()
用途: デストラクタ
戻り値: なし
*********************************************************************/
~Effect();

};


/*********************************************************************
class ThreeDimensionsEffect : public Effect	宣言部
用途 : 3次元座標用エフェクトのクラス
*********************************************************************/
class ThreeDimensionsEffect : public Effect
{
protected:
	/*********************************************************************
	struct PointSpriteVertex
	用途 : パーティクルの頂点データ
	*********************************************************************/
	struct PointSpriteVertex
	{
		D3DXVECTOR3 m_vPos ;		//頂点の位置
		//色の共用体
		union	{
			DWORD	m_dwColor ;
			struct {
				BYTE	b, g, r, a ;
			}m_Color ;
		};
		/*********************************************************************
		PointSpriteVertex();
		用途 : デフォルトコンストラクタ
		戻り値 : なし
		*********************************************************************/
		PointSpriteVertex()
			:m_vPos(D3DXVECTOR3(0.0f,0.0f,0.0f)),m_dwColor(0xFFFFFFFF){}

		/*********************************************************************
		PointSpriteVertex(
				const D3DXVECTOR3& i_vPos,	//位置
				DWORD i_dwColor				//色
				);
		用途 : 引数付きコンストラクタ
		戻り値 : なし
		*********************************************************************/
		PointSpriteVertex(  const D3DXVECTOR3& i_vPos, DWORD i_dwColor )
			:m_vPos(i_vPos),m_dwColor(i_dwColor){}

		/*********************************************************************
		PointSpriteVertex(
				const D3DXVECTOR3&	i_vPos,		//位置
				BYTE				i_byBlue,	//青色
				BYTE				i_byGreen,	//緑色
				BYTE				i_byRed,	//赤色
				BYTE				i_byAlpha	//透明度
				);
		用途 : 引数付きコンストラクタ
		戻り値 : なし
		*********************************************************************/
		PointSpriteVertex(  const D3DXVECTOR3& i_vPos,
			BYTE i_byBlue, BYTE i_byGreen, BYTE i_byRed, BYTE i_byAlpha) ;

		/*********************************************************************
		void setState(
			const D3DXVECTOR3& i_vPos,
			DWORD i_dwColor
			) ;
		用途 : ステータスを入れる
		戻り値 : なし
		*********************************************************************/
		void setState(const D3DXVECTOR3& i_vPos, DWORD i_dwColor) ;
	};

public:
	/**********************************************************************
	ThreeDimensionsEffect(
		LPDIRECT3DDEVICE9	pD3DDevice,			//デバイス
		const wchar_t*		i_filename			//画像のファイル名
		DWORD				i_Decolorisation,	//抜きたい色
		float				i_fSize				//エフェクトの大きさ
		)
	用途: コンストラクタ
	戻り値: なし
	*********************************************************************/
	ThreeDimensionsEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,DWORD i_Decolorisation,float i_fSize);

	/*********************************************************************
	~ThreeDimensionsEffect()
	用途: デストラクタ
	戻り値: なし
	*********************************************************************/
	~ThreeDimensionsEffect(){}

	/*********************************************************************
	void AddThreeDimensionsEffectt(
					const D3DXVECTOR3&	i_vSize,			//大きさ
					const D3DXVECTOR3&	i_vPos,				//位置
					const D3DXVECTOR3&	i_vDir,				//移動方向
					float				i_fSpeed			//速さ
					BYTE				i_byBlue	= 0xFF,	//青色
					BYTE				i_byGreen	= 0xFF,	//緑色
					BYTE				i_byRed		= 0xFF,	//赤色
					BYTE				i_byAlpha	= 0xFF	//透明度
					);
	用途: 各エフェクトオブジェクトの作成
	戻り値: なし
	************************************************************************/
	void AddThreeDimensionsEffect(const D3DXVECTOR3& i_vSize,const D3DXVECTOR3& i_vPos,const D3DXVECTOR3& i_vDir, float i_fSpeed,
				   BYTE i_byBlue = 0xFF, BYTE i_byGreen = 0xFF, BYTE i_byRed = 0xFF, BYTE i_byAlpha = 0xFF);


	/*********************************************************************
	void VerticesRender(
			LPDIRECT3DDEVICE9 pD3DDevice				//デバイス
			const PointSpriteRHWVertex* pPSRHWVertex	//バーテックスの配列
			);
	用途 : 描画処理
	戻り値 : なし
	*********************************************************************/
	void VerticesRender(LPDIRECT3DDEVICE9 pD3DDevice,const PointSpriteVertex* pPSVertex,unsigned int VertexSize) ;

	/*********************************************************************
	static DWORD getSPSize()
	用途:アクセッサ(ゲッター)
	戻り値: 3次元用パーティクルのVertexのデータ量
	*********************************************************************/
	DWORD getSPSize()
	{
		return sizeof(PointSpriteVertex);
	}
	/*********************************************************************
	static DWORD getSPFVF()
	用途:アクセッサ(ゲッター)
	戻り値: 3次元用パーティクルのFVF
	*********************************************************************/
	DWORD	getSPFVF()
	{
		return D3DFVF_XYZ | D3DFVF_DIFFUSE ;	
	}

};


/***********************************************************
class BreakEffect : public ThreeDimensionsEffect
用途 : 破壊時のエフェクト
***********************************************************/
class BreakEffect : public ThreeDimensionsEffect
{

	PointSpriteVertex	m_DrawVertices[m_iVerticesMaxSize]	;	//描画用頂点の配列
	int					m_iDrawVerticesNumber				;	//合計の頂点データ数をカウントする変数

	/***********************************************************
	struct EffectState
	用途 : 頂点データを変更するための構造体
	***********************************************************/
	struct EffectState
	{
		int						m_iLifeTime	;	//飛び散っている時間

		//エフェクト一つのパラメータ
		struct EffectParam{
			D3DXVECTOR3				m_vDir		;	//方向
			float					m_fSpeed	;	//スピード

		/*******************************************************
		EffectParam(
			const D3DXVECTOR3&	i_vDir ,		//方向
			const D3DXVECTOR3&	i_fSpeed,		//スピード
			)
		用途 : コンストラクタ
		戻り値 : なし
		*******************************************************/
		EffectParam(const D3DXVECTOR3& i_vDir , float i_fSpeed)
			:m_vDir(i_vDir),m_fSpeed(i_fSpeed){}
		};

		list<EffectParam>		m_EffectParams	;	//頂点データのパラメータ
		list<PointSpriteVertex>	m_Vertices		;	//頂点データ

		/*******************************************************
		EffectState(
			int					i_iVertexSize,		//頂点データの数
			float				i_vPos,				//位置
			)
		用途 : コンストラクタ
		戻り値 : なし
		*******************************************************/
		EffectState(int i_iVertexSize, const D3DXVECTOR3& i_vPos);

		/*****************************************************************
		bool Move(
			Command				i_Com			//コマンド
		)
		用途 : Particleの動きを行い削除処理の場合はtrueを返す
		戻り値 : なし
		*****************************************************************/
		bool Move( Command& i_Com ) ; 
	};

	list<EffectState*>			m_Statelist ;	// ステータス変更用の配列

public:
	/**********************************************************************
	BreakEffect(
		LPDIRECT3DDEVICE9	pD3DDevice,			//デバイス
		const wchar_t*		i_filename,			//画像のファイル名
		DWORD				i_Decolorisation,	//抜きたい色
		float				i_fSize				//エフェクトの大きさ
		)
	用途: コンストラクタ
	戻り値: なし
	***********************************************************************/
	BreakEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,DWORD i_Decolorisation,float i_fSize) ;

	/***********************************************************************
	~BreakEffect()
	用途: デストラクタ
	戻り値: なし
	***********************************************************************/
	~BreakEffect(){}

	/***********************************************************************
	void AddBreakEffect(
					const D3DXVECTOR3& i_vPos,	//位置
					);
	用途: ブロック破壊時のエフェクトオブジェクトの作成
	戻り値: なし
	************************************************************************/
	void AddBreakEffect(const D3DXVECTOR3& i_vPos);

	/******************************************************************
	virtualvoid Transform(
		LPDIRECT3DDEVICE9		pD3DDevice	,	//デバイス
		const CONTROLER_STATE*	pCntlState	,	//コントローラのステータス
		vector<Object*>&		i_Vec		,	//オブジェクトの配列
		Command&				i_Com			//コマンド
	) ;
	用途 : シーンの変化
	戻り値 : なし
	******************************************************************/
	 virtual void Transform( LPDIRECT3DDEVICE9 pD3DDevice , const CONTROLER_STATE* pCntlState ,vector<Object*> i_ObjectVec ,Command& i_Com) ;

	/*****************************************************************
	 virtual void Draw(
		LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
		vector<Object*>& i_Vec,				//オブジェクトの配列
		const CONTROLER_STATE* pCntlState   //コントローラのステータス
		Command i_Com						//コマンド
	 );
	 用途: オブジェクトを描画
	 戻り値: なし。
	*****************************************************************/
		virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& i_Vec,
								const CONTROLER_STATE* pCntlState,Command& i_Com );
};

/***********************************************************
class BossHitDownEffect : public ThreeDimensionsEffect
用途 : ボスがダメージを受けるときのエフェクト
***********************************************************/
class BossHitDownEffect : public ThreeDimensionsEffect
{
	/***********************************************************
	struct BossHitDownEffectState
	用途 : 頂点データを変更するための構造体
	***********************************************************/
	struct BossHitDownEffectState
	{
		int					m_iLife			; //表示時間
		float				m_fSize			; //大きさ
		PointSpriteVertex	m_Vertex		; //頂点データ

		/*******************************************************
		BossHitDownEffectState(
			const D3DXVECTOR3&	i_vPos,		//位置
			float				i_fSize,	//大きさ
			int					i_iLife,	//表示時間
			DWORD				i_dwColor	//色
			)
		用途 : コンストラクタ
		戻り値 : なし
		*******************************************************/
		BossHitDownEffectState( const D3DXVECTOR3& i_vPos,float i_fSize , int i_iLife, DWORD i_dwColor);

		/*****************************************************************
		bool Move()
		用途 : Particleの動きを行い削除処理の場合はtrueを返す
		戻り値 : なし
		*****************************************************************/
		bool Move() ;
	};

	list<BossHitDownEffectState*>			m_Statelist ;	// ステータス変更用の配列

public:
	/**********************************************************************
	BossHitDownEffect(
		LPDIRECT3DDEVICE9	pD3DDevice,			//デバイス
		const wchar_t*		i_filename,			//画像のファイル名
		DWORD				i_Decolorisation,	//抜きたい色
		float				i_fSize				//エフェクトの大きさ
		)
	用途: コンストラクタ
	戻り値: なし
	***********************************************************************/
	BossHitDownEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,DWORD i_Decolorisation,float i_fSize) ;

	/***********************************************************************
	~BossHitDownEffect()
	用途: デストラクタ
	戻り値: なし
	***********************************************************************/
	~BossHitDownEffect(){}

	/***********************************************************************
	void BossHitDownEffect::AddBossHitDownEffect(
					const D3DXVECTOR3&	i_vPos,			//位置
					int					i_iLifeTime,	//描画時間
					DWORD				i_dxColor,		//色
					Command&			i_Com			//コマンド
					);
	用途: ブロック破壊時のエフェクトオブジェクトの作成
	戻り値: なし
	************************************************************************/
	void AddBossHitDownEffect(const D3DXVECTOR3& i_vPos,int i_iLifeTime,DWORD i_dxColor ,Command& i_Com ) ;

};

/***********************************************************
class RHWEffect : public Effect
用途 : 2次元用エフェクト
***********************************************************/
class RHWEffect : public Effect
{
protected:
	struct PointSpriteRHWVertex
	{
		D3DXVECTOR3 m_vPos ;
		float		m_fRhw	;
		union	{
			DWORD	m_dwColor ;
			struct {
				BYTE	b, g, r, a ;
			}m_Color ;
		};
		/***************************************************************
		PointSpriteRHWVertex();
		用途 : コンストラクタ
		戻り値 : なし
		***************************************************************/
		PointSpriteRHWVertex()
			:m_vPos(D3DXVECTOR3(0.0f,0.0f,0.0f)),m_fRhw(1.0f),m_dwColor(0xFFFFFFFF){}

		/***************************************************************
		PointSpriteRHWVertex(
				const D3DXVECTOR3& i_vPos,	//位置
				DWORD i_dwColor				//色
				);
		用途 : コンストラクタ
		戻り値 : なし
		***************************************************************/
		PointSpriteRHWVertex(  const D3DXVECTOR3& i_vPos, DWORD i_dwColor )
			:m_vPos(i_vPos),m_fRhw(1.0f),m_dwColor(i_dwColor){}

		/***************************************************************
		PointSpriteRHWVertex(
				const D3DXVECTOR3&	i_vPos,		//位置
				BYTE				i_byBlue,	//青色
				BYTE				i_byGreen,	//緑色
				BYTE				i_byRed,	//赤色
				BYTE				i_byAlpha	//透明度
				);
		用途 : コンストラクタ
		戻り値 : なし
		***************************************************************/
		PointSpriteRHWVertex(  const D3DXVECTOR3& i_vPos,
			BYTE i_byBlue, BYTE i_byGreen, BYTE i_byRed, BYTE i_byAlpha)
			:m_vPos(i_vPos),m_fRhw(1.0f)
		{
			m_Color.b = i_byBlue	;
			m_Color.g = i_byGreen	;
			m_Color.r = i_byRed		;
			m_Color.a = i_byAlpha	;
		}

		/**************************************************************
		void setState(
			const D3DXVECTOR3& i_vPos,
			DWORD i_dwColor
			) ;
		用途 : ステータスを入れる
		戻り値 : なし
		**************************************************************/
		void setState(const D3DXVECTOR3& i_vPos, DWORD i_dwColor) ;
	};
public:
/**********************************************************************
RHWEffect(
	LPDIRECT3DDEVICE9	pD3DDevice,			//デバイス
	const wchar_t*		i_filename,			//画像のファイル名
	DWORD				i_Decolorisation,	//抜きたい色
	float				i_fSize				//エフェクトの大きさ
	)
用途: コンストラクタ
戻り値: なし
***********************************************************************/
RHWEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,DWORD i_Decolorisation,float i_fSize);

/***********************************************************************
~RHWEffect()
用途: デストラクタ
戻り値: なし
***********************************************************************/
~RHWEffect(){}

/*********************************************************************
void RHWVerticesRender(
		LPDIRECT3DDEVICE9 pD3DDevice				//デバイス
		const PointSpriteRHWVertex* pPSRHWVertex	//バーテックスの配列
		);
用途 : 描画処理
戻り値 : なし
*********************************************************************/
void RHWVerticesRender(LPDIRECT3DDEVICE9 pD3DDevice,const PointSpriteRHWVertex* pPSRHWVertex,unsigned int VertexSize) ;


/**********************************************************************
static DWORD getSPRHWSize()
用途:アクセッサ(ゲッター)
戻り値: スプライトポイントRHW用Vertexのデータ量
**********************************************************************/
	DWORD getSPRHWSize()
	{
		return sizeof(PointSpriteRHWVertex);
	}
/**********************************************************************
static DWORD getSPRHWFVF()
用途:アクセッサ(ゲッター)
戻り値: スプライトポイントRHW用FVF
**********************************************************************/
	DWORD	getSPRHWFVF()
	{
		return D3DFVF_XYZRHW | D3DFVF_DIFFUSE ;	//必要な頂点情報は座標と色のデータだけ持っている
	}
};

/***********************************************************
class ScaleEffect : public RHWEffect
用途 : 大きさの変動するエフェクト
***********************************************************/
class ScaleEffect : public RHWEffect
{
protected:

	PointSpriteRHWVertex* m_pPSVertexrhw ;

public:
	/**********************************************************************
	RHWEffect(
		LPDIRECT3DDEVICE9	pD3DDevice,			//デバイス
		const wchar_t*		i_filename,			//画像のファイル名
		const D3DXVECTOR3&	i_vPos			,	//位置を設定
		float				i_fSize				//エフェクトの大きさ
		)
	用途: コンストラクタ
	戻り値: なし
	***********************************************************************/
	ScaleEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,
		const D3DXVECTOR3& i_vPos ,float i_fSize);

	/***********************************************************************
	~ScaleEffect()
	用途: デストラクタ
	戻り値: なし
	***********************************************************************/
	~ScaleEffect() ;

	/******************************************************************
	virtualvoid Transform(
		LPDIRECT3DDEVICE9		pD3DDevice	,	//デバイス
		const CONTROLER_STATE*	pCntlState	,	//コントローラのステータス
		vector<Object*>&		i_Vec		,	//オブジェクトの配列
		Command&				i_Com			//コマンド
	) ;
	用途 : シーンの変化
	戻り値 : なし
	******************************************************************/
	 virtual void Transform( LPDIRECT3DDEVICE9 pD3DDevice , const CONTROLER_STATE* pCntlState ,vector<Object*> i_ObjectVec ,Command& i_Com) ;

	/*****************************************************************
	 virtual void Draw(
		LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
		vector<Object*>& i_Vec,				//オブジェクトの配列
		const CONTROLER_STATE* pCntlState   //コントローラのステータス
		Command i_Com						//コマンド
	 );
	 用途: オブジェクトを描画
	 戻り値: なし。
	*****************************************************************/
		virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& i_Vec,
								const CONTROLER_STATE* pCntlState,Command& i_Com );

};

/***********************************************************
class ExtinguishEffect : public RHWEffect	宣言部
用途 : 消滅時のエフェクト
***********************************************************/
class ExtinguishEffect : public RHWEffect
{
	
public:

	static const int	MAXDEGREES = 360 ;	//ディグリ角の最大数

protected:
	float					m_fRadSinArray[MAXDEGREES] ;
	float					m_fRadCosArray[MAXDEGREES] ;

	PointSpriteRHWVertex	m_DrawVertices[m_iVerticesMaxSize]	;		//描画用配列
	int						m_iVerticesSize						;		//描画頂点の数

	/***********************************************************
	struct ExtinguishEffectState	宣言部
	用途 : 頂点データを変更するための構造体
	***********************************************************/
	struct ExtinguishEffectState
	{
		float						m_fLangth	;	//中心からの距離
		D3DXVECTOR3					m_vCenter	;	//飛び散るパーティクルの中心
		int  						m_iRad		;	//角度
		int 						m_iRadSpeed ;	//回転する速さ
		float						m_fSpeed	;	//スピード
		int							m_iLifeTime	;	//飛び散っている時間
		list<PointSpriteRHWVertex>	m_Vertices  ;	//頂点データ

		/*******************************************************
		ExtinguishEffectState( 
			float				i_fSpeed,			//スピード
			const D3DXVECTOR3&	i_vPos,				//位置
			int 				i_iRadSpeed,		//回転の速さ
			int					i_iLifeTime,		//表示時間
			int					i_iParticleSize,	//パーティクルの数
			DWORD				i_dwColor,			//色
			)
		用途 : コンストラクタ
		戻り値 : なし
		*******************************************************/
		ExtinguishEffectState(float i_fSpeed,const D3DXVECTOR3& i_vPos, int i_iRadSpeed , int i_iLifeTime ,int i_iParticleSize,DWORD i_dwColor );

		/*******************************************************
		ExtinguishEffectState( 
			float				i_fSpeed,			//スピード
			const D3DXVECTOR3&	i_vPos,				//位置
			int 				i_iRadSpeed,		//回転の速さ
			int					i_iLifeTime,		//表示時間
			int					i_iParticleSize,	//パーティクルの数
			BYTE				i_byBlue,			//青色
			BYTE				i_byGreen,			//緑色
			BYTE				i_byRed,			//赤色
			BYTE				i_byAlpha			//透明度
			)
		用途 : コンストラクタ
		戻り値 : なし
		*******************************************************/
		ExtinguishEffectState(float i_fSpeed,const D3DXVECTOR3& i_vPos,int i_iRadSpeed , int i_iLifeTime ,int i_iParticleSize,BYTE i_byBlue, BYTE i_byGreen, BYTE i_byRed, BYTE i_byAlpha);

		/*****************************************************************
		bool Move(
			const float* i_fRadSinArray,	//Sinの配列を入れる
			const float* i_fRadCosArray		//Cosの配列を入れる
		)
		用途 : Particleの動きを行い削除処理の場合はtrueを返す
		戻り値 : なし
		*****************************************************************/
		bool Move(const float* i_fRadSinArray,const float* i_fRadCosArray) ; 
	};

	list<ExtinguishEffectState*>			m_Statelist ;	// ステータス変更用の配列

public:
	/**********************************************************************
	ExtinguishEffect(
		LPDIRECT3DDEVICE9	pD3DDevice,			//デバイス
		const wchar_t*		i_filename,			//画像のファイル名
		DWORD				i_Decolorisation	//抜きたい色
		float				i_fSize				//エフェクトの大きさ
		)
	用途: コンストラクタ
	戻り値: なし
	***********************************************************************/
	ExtinguishEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,DWORD i_Decolorisation,float i_fSize) ;

	/***********************************************************************
	~ExtinguishEffect()
	用途: デストラクタ
	戻り値: なし
	***********************************************************************/
	~ExtinguishEffect(){}

	/***********************************************************************
	void AddExtinguishEffect(
					const D3DXVECTOR3,	i_vPos,					//位置
					float				i_fSpeed,				//スピード
					int 				i_iRotSpeed,			//回転の速さ
					int					i_iLifeTime,			//表示時間
					int					i_iParticleSize			//パーティクルの数
					BYTE				i_bBlue		= 0xFF,		//青色
					BYTE				i_bGreen	= 0xFF,		//緑色
					BYTE				i_bRed		= 0xFF,		//赤色
					BYTE				i_bAlpha	= 0xFF		//透明色
				);
	用途: ゲージの段階が上がった時に発生するエフェクトオブジェクトの作成
	戻り値: なし
	************************************************************************/
	void AddExtinguishEffect(const D3DXVECTOR3 i_vPos,float i_fSpeed,int i_iRotSpeed , int i_iLifeTime,
					   int i_iParticleSize, BYTE i_bBlue = 0xFF,BYTE i_bGreen = 0xFF, BYTE i_bRed = 0xFF,BYTE i_bAlpha = 0xFF);

	/*********************************************************************
	bool Move(
		list<EffectState*>::iterator	it,				//現在のイテレーター
		const D3DXVECTOR3&				i_vHammerPos	//ハンマーの位置
		);
	用途 : エフェクトの動き
	戻り値 :	真だった場合、現在のイテレーターを削除,
				偽だった場合、次のイテレーターへ
	*********************************************************************/
	bool Move(list<ExtinguishEffectState*>::iterator it,const D3DXVECTOR3& i_vHammerPos);

	/******************************************************************
	virtualvoid Transform(
		LPDIRECT3DDEVICE9		pD3DDevice	,	//デバイス
		const CONTROLER_STATE*	pCntlState	,	//コントローラのステータス
		vector<Object*>&		i_Vec		,	//オブジェクトの配列
		Command&				i_Com			//コマンド
	) ;
	用途 : シーンの変化
	戻り値 : なし
	******************************************************************/
	 virtual void Transform( LPDIRECT3DDEVICE9 pD3DDevice , const CONTROLER_STATE* pCntlState ,vector<Object*> i_ObjectVec ,Command& i_Com) ;

	/*****************************************************************
	 virtual void Draw(
		LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
		vector<Object*>& i_Vec,				//オブジェクトの配列
		const CONTROLER_STATE* pCntlState   //コントローラのステータス
		Command i_Com						//コマンド
	 );
	 用途: オブジェクトを描画
	 戻り値: なし。
	*****************************************************************/
		virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& i_Vec,
								const CONTROLER_STATE* pCntlState,Command& i_Com );

};

/*******************************************************************
class LineEffect : public Object	宣言部
用途 :	線のエフェクトの描画
*******************************************************************/
class LineEffect //: public Object
{

	/***************************************************************
	struct LineEffectGroup	宣言部
	用途 : 線エフェクトを管理する構造体
	***************************************************************/
	struct LineEffectGroup{

		float				m_fRotZSpeed;		//	回転速度
		float				m_fScale	;		//	拡大縮小の値
		int					m_iLifeTime ;		//	出現している時間

		/***************************************************************
		struct LineEffectState	宣言部
		用途 : 線エフェクトを管理するステータス
		***************************************************************/
		struct LineEffectState 
		{
			VertexLineState*	m_VLState	;
			D3DXVECTOR3			m_vPos		;
			D3DXVECTOR3			m_vRot		;
			D3DXVECTOR3			m_vSize		;
			D3DXMATRIX			m_Matrix	;

			/***********************************************************
			LineEffectState(
				LPDIRECT3DDEVICE9	pD3DDevice	,	//デバイス
				const D3DXVECTOR3&	i_vPos		,	//位置
				const D3DXVECTOR3&	i_vSize		,	//大きさ
				const D3DXVECTOR3&	i_vRot		,	//回転度
				VertexStyle			i_VertexStyle,	//線の形 
			);
			用途 : コンストラクタ
			戻り値 : なし
			***********************************************************/
			LineEffectState(LPDIRECT3DDEVICE9 pD3DDevice , const D3DXVECTOR3& i_vPos ,
				const D3DXVECTOR3& i_vSize , const D3DXVECTOR3& i_vRot , VertexStyle i_VertexStyle ) ;

		};

		vector<LineEffectState*>	m_StateVec ;

		/**************************************************************
		LineEffectGroup(
			float				i_fRotZSpeed,	//	回転速度
			float				i_fScaling		//	拡大縮小の値
			int					i_iLifeTime		//出現している時間
		);
		用途 : コンストラクタ
		戻り値 : なし
		**************************************************************/
		LineEffectGroup( float i_fRotZSpeed ,float i_fScaling , int i_iLifeTime ) ;

		/**************************************************************
		void Move( 
			Command& i_Com		//コマンド
		);
		用途 : 動作
		戻り値 : なし
		**************************************************************/
		void Move( Command& i_Com ) ;

		/*************************************************************
		void Draw( 
			LPDIRECT3DDEVICE9 pD3DDevice	//デバイス
		)
		用途 : 
		戻り値 : 
		*************************************************************/
		void Draw( LPDIRECT3DDEVICE9 pD3DDevice );

	};
	
	vector<LineEffectGroup*>	m_StateVec ;

public :

	/******************************************************************
	LineEffect() ;
	用途 : コンストラクタ
	戻り値 : なし
	******************************************************************/
	LineEffect()	;

	/******************************************************************
	~LineEffect();
	用途 : デストラクタ
	戻り値 : なし
	******************************************************************/
	~LineEffect();

	/******************************************************************
	void AddLineEffect(
		LPDIRECT3DDEVICE9	pD3DDevice	,	//デバイス
		const D3DXVECTOR3&	i_vPos		,	//位置
		const D3DXVECTOR3&	i_vSize		,	//大きさ
		const D3DXVECTOR3&	i_vRot			//回転度
		VertexStyle			i_VertexStyle	//線の形 
		float				i_fRotZSpeed,	//	回転速度
		float				i_fScaling		//	拡大縮小の値
		int					i_iLifeTime		//出現している時間
		int					i_iLineNumber	//線の本数
	);
	用途 : ラインエフェクトの追加
	戻り値 : なし
	******************************************************************/
	void AddLineEffect( LPDIRECT3DDEVICE9 pD3DDevice , const D3DXVECTOR3& i_vPos ,const D3DXVECTOR3& i_vSize , 
		const D3DXVECTOR3& i_vRot , VertexStyle i_VertexStyle ,float i_fRotZSpeed ,float i_fScaling , int i_iLifeTime , int i_iLineNumber);

	/******************************************************************
	virtualvoid Transform(
		LPDIRECT3DDEVICE9		pD3DDevice	,	//デバイス
		const CONTROLER_STATE*	pCntlState	,	//コントローラのステータス
		vector<Object*>&		i_Vec		,	//オブジェクトの配列
		Command&				i_Com			//コマンド
	) ;
	用途 : シーンの変化
	戻り値 : なし
	******************************************************************/
	 virtual void Transform( LPDIRECT3DDEVICE9 pD3DDevice , const CONTROLER_STATE* pCntlState ,vector<Object*> i_ObjectVec ,Command& i_Com) ;

	/*****************************************************************
	 virtual void Draw(
		LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
		vector<Object*>& i_Vec,				//オブジェクトの配列
		const CONTROLER_STATE* pCntlState   //コントローラのステータス
		Command i_Com						//コマンド
	 );
	 用途: オブジェクトを描画
	 戻り値: なし。
	*****************************************************************/
		virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& i_Vec,
								const CONTROLER_STATE* pCntlState,Command& i_Com );

//------------------------------アクセッサ-------------------------------------------

	/***************************************************************************
	D3DXVECTOR3 StarFragment::getPos(
		int i_iVecNum	//配列内での添え字
	) ;
	用途 : 位置を返す
	戻り値 : 指定された添え字のObjectの位置を返す
	***************************************************************************/
	D3DXVECTOR3 getPos( int i_iVecNum ) ;

	/**************************************************************************
	const int getObjectVecSize() const ;
	用途 : オブジェクトの数を把握する
	戻り値 : このクラスで管理しているObjectの数
	**************************************************************************/
	const int getObjectVecSize() const ;

	
};


/*******************************************************************
class NameLineEffect : public Object	宣言部
用途 :	名前の線のエフェクトの描画
*******************************************************************/
class NameLineEffect : public ThreeDimensionsEffect
{
	PointSpriteVertex	m_DrawVertices[m_iVerticesMaxSize]	;	//描画用頂点の配列
	int					m_iDrawVerticesNumber				;	//合計の頂点データ数をカウントする変数

	/***************************************************************
	struct NameLineEffectState	宣言部
	用途 : 線エフェクトを管理するステータス
	***************************************************************/
	struct NameLineEffectState 
	{
		PointSpriteVertex*	m_pPointSprite;
		VertexLineState*	m_pVLState	;
		D3DXVECTOR3			m_vPos		;
		D3DXVECTOR3			m_vSize		;
		D3DXMATRIX			m_Matrix	;

		/***********************************************************
		NameLineEffectState(
			LPDIRECT3DDEVICE9	pD3DDevice	,	//デバイス
			const D3DXVECTOR3&	i_vPos		,	//位置
			const D3DXVECTOR3&	i_vSize		,	//大きさ
			const D3DXVECTOR3&	i_vRot		,	//回転度
			VertexStyle			i_VertexStyle,	//線の形 
		);
		用途 : コンストラクタ
		戻り値 : なし
		***********************************************************/
		NameLineEffectState(LPDIRECT3DDEVICE9 pD3DDevice , const D3DXVECTOR3& i_vPos ,
			const D3DXVECTOR3& i_vSize , const D3DXVECTOR3& i_vRot , VertexStyle i_VertexStyle ) ;

		/************************************************************
		~NameLineEffectState();
		用途 : デストラクタ
		戻り値 : なし
		************************************************************/
		~NameLineEffectState();

		/**************************************************************
		void Move( 
			Command& i_Com		//コマンド
		);
		用途 : 動作
		戻り値 : なし
		**************************************************************/
		void Move( Command& i_Com ) ;

	};

	vector<NameLineEffectState*>	m_StateVec ;

public :

	/******************************************************************
	NameLineEffect(
		LPDIRECT3DDEVICE9	pD3DDevice,			//デバイス
		const wchar_t*		i_filename			//画像のファイル名
		float				i_fSize				//エフェクトの大きさ
	) ;
	用途 : コンストラクタ
	戻り値 : なし
	******************************************************************/
	NameLineEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,float i_fSize)	;

	/******************************************************************
	~NameLineEffect();
	用途 : デストラクタ
	戻り値 : なし
	******************************************************************/
	~NameLineEffect();

	/******************************************************************
	void AddNameLineEffect(
		LPDIRECT3DDEVICE9	pD3DDevice	,	//デバイス
		const D3DXVECTOR3&	i_vPos		,	//位置
		const D3DXVECTOR3&	i_vSize		,	//大きさ
	);
	用途 : ラインエフェクトの追加
	戻り値 : なし
	******************************************************************/
	void AddNameLineEffect( LPDIRECT3DDEVICE9 pD3DDevice , const D3DXVECTOR3& i_vPos ,const D3DXVECTOR3& i_vSize );

	/******************************************************************
	virtualvoid Transform(
		LPDIRECT3DDEVICE9		pD3DDevice	,	//デバイス
		const CONTROLER_STATE*	pCntlState	,	//コントローラのステータス
		vector<Object*>&		i_Vec		,	//オブジェクトの配列
		Command&				i_Com			//コマンド
	) ;
	用途 : シーンの変化
	戻り値 : なし
	******************************************************************/
	 virtual void Transform( LPDIRECT3DDEVICE9 pD3DDevice , const CONTROLER_STATE* pCntlState ,vector<Object*> i_ObjectVec ,Command& i_Com) ;

	/*****************************************************************
	 virtual void Draw(
		LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
		vector<Object*>& i_Vec,				//オブジェクトの配列
		const CONTROLER_STATE* pCntlState   //コントローラのステータス
		Command i_Com						//コマンド
	 );
	 用途: オブジェクトを描画
	 戻り値: なし。
	*****************************************************************/
	void Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& i_Vec,
								const CONTROLER_STATE* pCntlState,Command& i_Com );

//-------------------------------アクセッサ------------------------------------------

	/****************************************************************
	void setPos( 
		const vector<D3DXVECTOR3*>& i_vPosVec //指定したいポジションの配列
	);
	用途 : 渡されたポジションの数だけ位置をセットする
	戻り値 : なし
	****************************************************************/
	void setPos( const D3DXVECTOR3& i_vPosVec ); 
};
}
using namespace seiyasource;
}