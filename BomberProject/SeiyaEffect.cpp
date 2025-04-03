/********************************************************************
Effect.cpp

class Object т-class Effect 定義部т-class ThreeDimensionsEffect		定義部
			  |						|		∟class BlockBreakEffect	定義部
			  |						∟class TwoDimensionsEffect			定義部
			  |								
			　|- class XMeshEffect	定義部
			  |
			  ∟ class LineEffect	定義部 

********************************************************************/


#include "StdAfx.h"
#include "Object.h"
#include "SeiyaEffect.h"
#include "TL-String.h"
//#include "UI.h"


namespace wiz{
/*****************************************************************************
struct VertexLineState	宣言部
用途 : 3次元座標上の頂点描画処理を行う
******************************************************************************/

/******************************************************************************
VertexLineState::VertexLineState()
用途 : コンストラクタ
戻り値 : なし
******************************************************************************/
VertexLineState::VertexLineState()
{
}

/******************************************************************************
VertexLineState::VertexLineState(
		LPDIRECT3DDEVICE9 pD3DDevice ,	//デバイス 
		const wchar_t* i_pFilename		//ファイル名
	)
用途 : コンストラクタ
戻り値 : なし
******************************************************************************/
VertexLineState::VertexLineState(LPDIRECT3DDEVICE9 pD3DDevice , const wchar_t* i_pFilename )
:m_iDrawPrimitiveVertexNum( 0 ) , m_pVertexBuffer( 0 ) , m_pVertex( 0 ) ,
m_PrimitiveType( D3DPT_TRIANGLESTRIP ) , m_iVertexNum( 0 )
{
	m_pVertexBuffer	= NULL ;
	m_pVertex =NULL ;
	//if( i_pFilename )	m_pTexture = new Texture(pD3DDevice,i_pFilename);
	//else				m_pTexture = 0 ;

}
/******************************************************************************
VertexLineState::~VertexLineState()
用途 : デストラクタ
戻り値 : なし
******************************************************************************/
VertexLineState::~VertexLineState()
{
	SafeDelete( m_pTexture ) ;
	SafeRelease( m_pVertexBuffer );
}

/******************************************************************************
void VertexLineState::SetVertex(
	LPDIRECT3DDEVICE9	pD3DDevice ,	//デバイス
	VertexStyle			i_Style			//Objectの形
);
用途 : 引数に応じた形を作る
戻り値 : なし
******************************************************************************/
void VertexLineState::SetVertex( LPDIRECT3DDEVICE9 pD3DDevice , VertexStyle i_Style , D3DPRIMITIVETYPE i_PrimitiveType )
{
	
	D3DXVECTOR3 vHafeSize = D3DXVECTOR3( 1.0f , 1.0f , 0.0f ) / 2 ;	//半分の大きさ

	int iVertexSize = 0 ;	//頂点の数を入れる

	//各スタイルの頂点数
	const int c_iTriangle	= 4 ;	//三角形
	const int c_iSquare		= 5 ;	//四角形
	const int c_iCircle		= 7 ;	//円
	const int c_iCross		= 4 ;	//十字
	const int c_iLine		= 2 ;	//線

	switch( i_Style ) {
		case VS_Triangle :
			iVertexSize					= c_iTriangle	 ;
			m_iDrawPrimitiveVertexNum	= c_iTriangle - 1;
			break ;
		case VS_Square :
			iVertexSize					= c_iSquare		;
			m_iDrawPrimitiveVertexNum	= c_iSquare - 1 ;
			break ;
		case VS_Circle :
			iVertexSize					= c_iCircle		;
			m_iDrawPrimitiveVertexNum	= c_iCircle	- 1 ;
			break ;
		//二つの線を引く時に使用
		case VS_Cross :
		case VS_NameLine :
			iVertexSize					= c_iCross		;
			m_iDrawPrimitiveVertexNum	= c_iCross / 2	;
			break ;
		case VS_Line :
			iVertexSize					= c_iLine		;
			m_iDrawPrimitiveVertexNum	= c_iLine - 1	;
			break ;
	}

	float iRotSize = 360.0f / m_iDrawPrimitiveVertexNum ;	
	m_iVertexNum = iVertexSize ;

	//	: 頂点バッファの生成（内包できる領域のサイズ、データの扱い、頂点データの中身、頂点データを管理するメモリ、生成されたバッファを示すアドレスが帰ってくる））
	pD3DDevice->CreateVertexBuffer( Vertex::getSize() * iVertexSize , D3DUSAGE_WRITEONLY, Vertex::getFVF(), D3DPOOL_MANAGED, &m_pVertexBuffer, NULL );
	m_pVertexBuffer->Lock( 0, 0, (void**)&m_pVertex ,0 );	//	: 頂点データのアドレスを取得するとともに、データへのアクセスを開始する	

	switch( i_Style ){

		case VS_Circle :
		case VS_Square :
		case VS_Triangle :
			for ( int i = 0 ; i < iVertexSize ; i++ )
				m_pVertex[ i ]	= Vertex( D3DXVECTOR3(  cosf( D3DXToRadian( iRotSize * i ) ) , sinf(D3DXToRadian( iRotSize * i ) ) , 0.0f )	, 0xFFFFFFFF, D3DXVECTOR2(0.5f,0.0f) );
			//プリミティブを入れる
			m_PrimitiveType = i_PrimitiveType ;
			break ;

		case VS_Cross :

			m_pVertex[ 0 ] = Vertex(D3DXVECTOR3( 0.5f , 0.0f , 0.0f ) , 0xFFFFFFFF , D3DXVECTOR2(0.0f ,0.0f) );
			m_pVertex[ 1 ] = Vertex(D3DXVECTOR3( -0.5f , 0.0f , 0.0f ) , 0xFFFFFFFF , D3DXVECTOR2(0.0f ,0.0f) );
			m_pVertex[ 2 ] = Vertex(D3DXVECTOR3( 0.0f , 0.5f , 0.0f ) , 0xFFFFFFFF , D3DXVECTOR2(0.0f ,0.0f) );
			m_pVertex[ 3 ] = Vertex(D3DXVECTOR3( 0.0f , -0.5f , 0.0f ) , 0xFFFFFFFF , D3DXVECTOR2(0.0f ,0.0f) );
			
			m_PrimitiveType = D3DPT_LINELIST ;
			break ;

		case VS_NameLine :

			m_pVertex[ 0 ] = Vertex(D3DXVECTOR3( 0.0f , 0.0f , 0.0f ) , 0xFFFFFFFF , D3DXVECTOR2(0.0f ,0.0f) );
			m_pVertex[ 1 ] = Vertex(D3DXVECTOR3( 0.2f , 1.0f , 0.0f ) , 0xFFFFFFFF , D3DXVECTOR2(0.0f ,0.0f) );
			m_pVertex[ 2 ] = Vertex(D3DXVECTOR3( 0.2f , 1.0f , 0.0f ) , 0xFFFFFFFF , D3DXVECTOR2(0.0f ,0.0f) );
			m_pVertex[ 3 ] = Vertex(D3DXVECTOR3( 1.0f , 1.0f , 0.0f ) , 0xFFFFFFFF , D3DXVECTOR2(0.0f ,0.0f) );
			
			m_PrimitiveType = D3DPT_LINELIST ;
			break ;

		case VS_Line :
			m_pVertex[ 0 ] = Vertex(D3DXVECTOR3( 0.0f , 0.0f , 0.0f ) , 0xFFFFFFFF , D3DXVECTOR2(0.0f ,0.0f) );
			m_pVertex[ 1 ] = Vertex(D3DXVECTOR3( 1.0f , 0.0f , 0.0f ) , 0xFFFFFFFF , D3DXVECTOR2(0.0f ,0.0f) );
			
			m_PrimitiveType = D3DPT_LINELIST ;
			break ;
	};

	m_pVertexBuffer->Unlock();
}

/******************************************************************************
void VertexrhwState::SetDownColor( 
	DWORD i_dwColor	//セットしたい色
) ;
用途 : 色の変更
戻り値 : なし
******************************************************************************/
void VertexLineState::SetDownColor( DWORD i_dwColor )
{
	//データを変更
	for( int i = 0 ; i <m_iVertexNum  ; i++ )
		m_pVertex[ i ].m_dwColor -= i_dwColor ;

	m_pVertexBuffer->Lock( 0, 0, (void**)&m_pVertex ,0 );	//	: 頂点データのアドレスを取得するとともに、データへのアクセスを開始する	
	
	for ( int i = 0 ; i < m_iVertexNum ; i++ )
		m_pVertex[ i ]	= Vertex( m_pVertex[i].m_vPos , m_pVertex[i].m_dwColor , m_pVertex[i].m_vTex);

	m_pVertexBuffer->Unlock();

}

/******************************************************************************
void VertexLineState::setVertexPos(
	vector<D3DXVECTOR3*> i_vPosVec変更したいLineのポジション
);
用途 : 頂点の位置を変更する
戻り値 : なし
******************************************************************************/
void VertexLineState::setVertexPos( vector<D3DXVECTOR3*> i_vPosVec )
{
	try{
		int iLoadPosSize = i_vPosVec.size();
		int iVertexSize	 = m_iVertexNum ;

		if( iLoadPosSize != iVertexSize ){
			#ifdef _DEBUG
				throw BaseException(	L"設定したい位置の数が違います"	,
									L"VertexLineState::setVertexPos()");
			#else
				return ;
			#endif
		}else{
			for(int i = 0 ; i < iLoadPosSize ; i++ ){
				m_pVertex[ i ].m_vPos = *i_vPosVec[ i ] ;
			}
			m_pVertexBuffer->Lock( 0, 0, (void**)&m_pVertex ,0 );	//	: 頂点データのアドレスを取得するとともに、データへのアクセスを開始する	
			
			for ( int i = 0 ; i < m_iVertexNum ; i++ )
				m_pVertex[ i ]	= Vertex( m_pVertex[i].m_vPos , m_pVertex[i].m_dwColor , m_pVertex[i].m_vTex);

			m_pVertexBuffer->Unlock();
		}

	}catch(...){
		throw ;
	}
}


/******************************************************************************
void VertexLineState::Draw(
	LPDIRECT3DDEVICE9 pD3DDevice ,	//デバイス
	const D3DXMATRIX& i_Matrix		//描画したいプレートの配列
	)
用途 : 正方形のプレートを描画
戻り値 : なし
******************************************************************************/
void VertexLineState::Draw(LPDIRECT3DDEVICE9 pD3DDevice , const D3DXMATRIX& i_Matrix )
{
	 pD3DDevice->SetRenderState( D3DRS_LIGHTING , FALSE );

	//if( m_pTexture ) pD3DDevice->SetTexture( 0 , m_pTexture->getTexture() );			//	: テクスチャを設定（NULL の場合はテクスチャ無し）

	 //ワールド変換行列を設定
	pD3DDevice->SetTransform( D3DTS_WORLD , &i_Matrix );								//変換済み頂点の場合は無視される

	//	: 頂点バッファを用いてモデルを描画する
	pD3DDevice->SetStreamSource( 0, m_pVertexBuffer , 0 , Vertex::getSize() );		//	: 描画対象となる頂点バッファを設定
	pD3DDevice->SetFVF( Vertex::getFVF() );											//	: 頂点データの形式を設定
	pD3DDevice->DrawPrimitive( m_PrimitiveType , 0, m_iDrawPrimitiveVertexNum );	//	: 頂点データの描画（描画の仕方、描画開始位置、プリミティブ数）


	pD3DDevice->SetTexture( 0 , NULL );												//	: テクスチャを設定（NULL の場合はテクスチャ無し）
	pD3DDevice->SetRenderState( D3DRS_LIGHTING , TRUE );

}


/*********************************************************************
class Effect : public Object	定義部
用途 : 演出用エフェクトの元クラス
*********************************************************************/

/*********************************************************************
Effect::clear()
用途 : 削除処理
戻り値: なし
*********************************************************************/
void Effect::clear()
{
	SafeRelease(m_pTexture);
}

/*********************************************************************
Effect::Effect(
	LPDIRECT3DDEVICE9	pD3DDevice,			//デバイス
	const wchar_t*		i_filename,			//画像のファイル名
	DWORD				i_Decolorisation,	//抜きたい色
	float				i_fSize				//エフェクトの大きさ
	)
用途: コンストラクタ
戻り値: なし
*********************************************************************/
Effect::Effect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,DWORD i_Decolorisation,float i_fSize)
:m_fEffectSize(i_fSize)
{
	if( i_filename ){
		int Decolorisations[4] ;
		// 0 = アルファ値 , 1 = 赤 , 2 = 緑 , 3 = 青
		for(int i = 0 ; i < 4 ; i++){
			Decolorisations[i] = i_Decolorisation & 0x000000FF ;
			i_Decolorisation = i_Decolorisation >> 8 ;		//1色分シフト
		}

		//D3DXCreateTextureFromFileEx(
		//	pD3DDevice,
		//	i_filename,			         // ファイル名
		//	0,
		//	0,
		//	0,
		//	0,
		//	D3DFMT_A1R5G5B5,                // 色抜きを可能に
		//	D3DPOOL_MANAGED,
		//	D3DX_FILTER_LINEAR,
		//	D3DX_FILTER_LINEAR,
		//	D3DCOLOR_ARGB(Decolorisations[0], Decolorisations[1], Decolorisations[2], Decolorisations[3]),  // 指定された色を透過色とする
		//	NULL,
		//	NULL,
		//	&m_pTexture                   // テクスチャ名
		//);
	}else{
		m_pTexture = 0 ;
	}
}

/*********************************************************************
Effect::~Effect()
用途: デストラクタ
戻り値: なし
*********************************************************************/
Effect::~Effect()
{
	clear() ;
}

/*********************************************************************
class ThreeDimensionsEffect : public Effect	定義部
用途 : 3次元座標のエフェクト描画クラス
*********************************************************************/

/*********************************************************************
ThreeDimensionsEffect::PointSpriteVertex::PointSpriteVertex(
		const D3DXVECTOR3&	i_vPos,		//位置
		BYTE				i_byBlue,	//青色
		BYTE				i_byGreen,	//緑色
		BYTE				i_byRed,	//赤色
		BYTE				i_byAlpha	//透明度
		);
用途 : 引数付きコンストラクタ
戻り値 : なし
*********************************************************************/
ThreeDimensionsEffect::PointSpriteVertex::PointSpriteVertex(  const D3DXVECTOR3& i_vPos,
	BYTE i_byBlue, BYTE i_byGreen, BYTE i_byRed, BYTE i_byAlpha)
	:m_vPos(i_vPos)
{
	m_Color.b = i_byBlue	;
	m_Color.g = i_byGreen	;
	m_Color.r = i_byRed		;
	m_Color.a = i_byAlpha	;
}

/*********************************************************************
void ThreeDimensionsEffect::PointSpriteVertex::setState(
	const D3DXVECTOR3&	i_vPos,		//位置
	DWORD				i_dwColor	//色
	) ;
用途 : ステータスを入れる
戻り値 : なし
*********************************************************************/
void ThreeDimensionsEffect::PointSpriteVertex::setState(const D3DXVECTOR3& i_vPos, DWORD i_dwColor)
{
	m_vPos		= i_vPos ;
	m_dwColor	= i_dwColor ;
}

/*********************************************************************
ThreeDimensionsEffect::ThreeDimensionsEffect(
	LPDIRECT3DDEVICE9	pD3DDevice,			//デバイス
	const wchar_t*		i_filename,			//画像のファイル名
	DWORD				i_Decolorisation,	//抜きたい色
	float				i_fSize				//エフェクトの大きさ
	)
用途: コンストラクタ
戻り値: なし
*********************************************************************/
ThreeDimensionsEffect::ThreeDimensionsEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,DWORD i_Decolorisation,float i_fSize)
	:Effect(pD3DDevice,i_filename,i_Decolorisation,i_fSize)
{
}

/*********************************************************************
void ThreeDimensionsEffect::VerticesRender(
		LPDIRECT3DDEVICE9 pD3DDevice		,	//デバイス
		const PointSpriteVertex* pPSVertex	,	//バーテックスの配列
		unsigned int VertexSize					//現在保持している頂点データの数
		);
用途 : 描画処理
戻り値 : なし
*********************************************************************/
void ThreeDimensionsEffect::VerticesRender(LPDIRECT3DDEVICE9 pD3DDevice,const PointSpriteVertex* pPSVertex,unsigned int VertexSize)
{
	//上限を設定
	if(VertexSize <= 0 ) VertexSize = 0 ;
	else if(VertexSize > m_iVerticesMaxSize) VertexSize = m_iVerticesMaxSize ;
	////描画処理
	pD3DDevice->SetFVF( getSPFVF() );
	pD3DDevice->SetTexture(0,m_pTexture);
	pD3DDevice->DrawPrimitiveUP( D3DPT_POINTLIST,VertexSize,pPSVertex, getSPSize() ) ;

}

/***********************************************************
class RHWEffect : public Effect	定義部
用途 : スクリーン座標用のエフェクトを描画
***********************************************************/

/**********************************************************************
RHWEffect::RHWEffect(
	LPDIRECT3DDEVICE9	pD3DDevice,			//デバイス
	const wchar_t*		i_filename,			//画像のファイル名
	DWORD				i_Decolorisation,	//抜きたい色
	float				i_fSize				//エフェクトの大きさ
	)
用途: コンストラクタ
戻り値: なし
***********************************************************************/
RHWEffect::RHWEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,DWORD i_Decolorisation,float i_fSize)
	:Effect(pD3DDevice,i_filename,i_Decolorisation,i_fSize){}

/*********************************************************************
void RHWEffect::RHWVerticesRender(
		LPDIRECT3DDEVICE9			pD3DDevice	,	//デバイス
		const PointSpriteRHWVertex* pPSRHWVertex,	//バーテックスの配列
		unsigned int				VertexSize		//現在保持している頂点データの数
		);
用途 : 描画処理
戻り値 : なし
*********************************************************************/
void RHWEffect::RHWVerticesRender(LPDIRECT3DDEVICE9 pD3DDevice,const PointSpriteRHWVertex* pPSRHWVertex,unsigned int VertexSize)
{
	//上限を設定
	if(VertexSize <= 0 ) VertexSize = 0 ;
	else if(VertexSize > m_iVerticesMaxSize) VertexSize = m_iVerticesMaxSize ;
	//描画処理
	pD3DDevice->SetFVF( getSPRHWFVF() );
	pD3DDevice->SetTexture(0,m_pTexture);
	pD3DDevice->DrawPrimitiveUP( D3DPT_POINTLIST,VertexSize,pPSRHWVertex, getSPRHWSize() ) ;

}

/***********************************************************
class ScaleEffect : public RHWEffect	定義部
用途 : スクリーン座標用のエフェクトを描画
***********************************************************/

/**********************************************************************
ScaleEffect::ScaleEffect(
	LPDIRECT3DDEVICE9	pD3DDevice,			//デバイス
	const wchar_t*		i_filename,			//画像のファイル名
	const D3DXVECTOR3&	i_vPos			,	//位置を設定
	float				i_fSize				//エフェクトの大きさ
	)
用途: コンストラクタ
戻り値: なし
***********************************************************************/
ScaleEffect::ScaleEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,
						 const D3DXVECTOR3& i_vPos , float i_fSize)
	:RHWEffect(pD3DDevice,i_filename,0x00000000,i_fSize)
{
	m_pPSVertexrhw = new PointSpriteRHWVertex(i_vPos ,0xFFFFFFFF );
}

/***********************************************************************
ScaleEffect::~ScaleEffect()
用途: デストラクタ
戻り値: なし
***********************************************************************/
ScaleEffect::~ScaleEffect()
{
	SafeDelete( m_pPSVertexrhw );
}

/******************************************************************
virtualvoid ScaleEffect::Transform(
	LPDIRECT3DDEVICE9		pD3DDevice	,	//デバイス
	const CONTROLER_STATE*	pCntlState	,	//コントローラのステータス
	vector<Object*>&		i_Vec		,	//オブジェクトの配列
	Command&				i_Com			//コマンド
) ;
用途 : シーンの変化
戻り値 : なし
******************************************************************/
void ScaleEffect::Transform( LPDIRECT3DDEVICE9 pD3DDevice , const CONTROLER_STATE* pCntlState ,vector<Object*> i_ObjectVec ,Command& i_Com)
 {
	 m_fEffectSize++ ;
 }

/*****************************************************************
 virtual void ScaleEffect::Draw(
	LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
	vector<Object*>& i_Vec,				//オブジェクトの配列
	const CONTROLER_STATE* pCntlState   //コントローラのステータス
	Command i_Com						//コマンド
 );
 用途: オブジェクトを描画
 戻り値: なし。
*****************************************************************/
void ScaleEffect::Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& i_Vec,
							const CONTROLER_STATE* pCntlState,Command& i_Com )
{


	//レンダーステートを変更させるためのクラスを宣言
	DeviceRenderState drs = DeviceRenderState() ;

	drs.SetDeviceRenderState(D3DRS_LIGHTING, FALSE );	//ライティングモードをFALSEに設定
	drs.ChangeRS_PointSprite(m_fEffectSize);			//描画方法をポイントスプライトに設定
	drs.ChangeRS_ALPHABLENDENABLE_Black();				//加算合成の設定
	drs.ChangeRenderState(pD3DDevice);					//上記の設定にレンダーステートを変更する

	RHWVerticesRender(pD3DDevice , m_pPSVertexrhw , 1 );

	drs.ChangeRenderState(pD3DDevice);					//上記の設定にレンダーステートを変更する

}



/***********************************************************
class ExtinguishEffect : public RHWEffect	定義部
用途 : 消滅時のエフェクト
***********************************************************/

/***********************************************************
struct ExtinguishEffectState	定義部
用途 : 頂点データを変更するための構造体
***********************************************************/

/*******************************************************
ExtinguishEffect::ExtinguishEffectState::ExtinguishEffectState( 
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
ExtinguishEffect::ExtinguishEffectState::ExtinguishEffectState(float i_fSpeed,const D3DXVECTOR3& i_vPos, int i_iRadSpeed , int i_iLifeTime ,int i_iParticleSize,DWORD i_dwColor )
	:m_fSpeed(i_fSpeed), m_iLifeTime(i_iLifeTime),m_vCenter(i_vPos),m_fLangth(0),m_iRadSpeed(i_iRadSpeed),m_iRad(0)
{
	for(int i = 0 ; i < i_iParticleSize ; i++) m_Vertices.push_back( PointSpriteRHWVertex(i_vPos,i_dwColor) ) ;
}

/*******************************************************
ExtinguishEffect::ExtinguishEffectState::ExtinguishEffectState( 
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
ExtinguishEffect::ExtinguishEffectState::ExtinguishEffectState(float i_fSpeed,const D3DXVECTOR3& i_vPos,int i_iRadSpeed , int i_iLifeTime ,int i_iParticleSize,BYTE i_byBlue, BYTE i_byGreen, BYTE i_byRed, BYTE i_byAlpha)
	:m_fSpeed(i_fSpeed), m_iLifeTime(i_iLifeTime),m_vCenter(i_vPos),m_fLangth(0),m_iRadSpeed(i_iRadSpeed),m_iRad(0)
{
	for(int i = 0 ; i < i_iParticleSize ; i++) m_Vertices.push_back( PointSpriteRHWVertex(i_vPos,i_byBlue,i_byGreen,i_byRed,i_byAlpha) ) ;
}

/*****************************************************************
bool ExtinguishEffect::ExtinguishEffectState::Move(
	const float* i_fRadSinArray,	//Sinの配列を入れる
	const float* i_fRadCosArray		//Cosの配列を入れる
)
用途 : Particleの動きを行い削除処理の場合はtrueを返す
戻り値 : なし
*****************************************************************/
bool ExtinguishEffect::ExtinguishEffectState::Move(const float* i_fRadSinArray,const float* i_fRadCosArray)
{
	//作業用変数
	int iRad = m_iRad ;

	//ループ用頂点データ
	list<PointSpriteRHWVertex>::iterator it  = m_Vertices.begin() ;
	list<PointSpriteRHWVertex>::iterator end = m_Vertices.end()   ;

	//頂点データのループ
	for(; it != end ; it++){
		//角度が360度を超えないように処理
		iRad %= MAXDEGREES ;

		//透明色に変更するための変数
		BYTE DownColor = 0x00000000 ;
		if(m_iLifeTime >= 1 )DownColor = ( ( m_iLifeTime - 1 ) * (*it).m_Color.a ) / m_iLifeTime ;

		D3DXVECTOR3	 g_vDir = D3DXVECTOR3(i_fRadCosArray[iRad],i_fRadSinArray[iRad],0.0f);

		//頂点の移動方向を正規化
		D3DXVec3Normalize(&g_vDir,&g_vDir);

		//位置の設定
		(*it).m_vPos	= m_vCenter + g_vDir * m_fLangth ;
		iRad += MAXDEGREES / m_Vertices.size() ;

		//色を変更
		(*it).m_Color.r = DownColor ;
		(*it).m_Color.g = DownColor ;
		(*it).m_Color.b = DownColor ;
		(*it).m_Color.a = DownColor ;
	}
	//もし表示時間が０になったら
	if( m_iLifeTime < 0 )	return true ;
	else					m_iLifeTime-- ;

	m_fLangth += m_fSpeed;
	m_iRad += m_iRadSpeed ;
	return false ;
}

/**********************************************************************
ExtinguishEffect::ExtinguishEffect(
	LPDIRECT3DDEVICE9	pD3DDevice,			//デバイス
	const wchar_t*		i_filename,			//画像のファイル名
	DWORD				i_Decolorisation,	//抜きたい色
	float				i_fSize				//エフェクトの大きさ
	)
用途: コンストラクタ
戻り値: なし
***********************************************************************/
ExtinguishEffect::ExtinguishEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,DWORD i_Decolorisation,float i_fSize)
	:RHWEffect(pD3DDevice,i_filename,i_Decolorisation,i_fSize),m_iVerticesSize( 0 )
{
	for(int i = 0 ; i < MAXDEGREES ; i++){
		m_fRadCosArray[i] = cosf(D3DXToRadian(i));
		m_fRadSinArray[i] = sinf(D3DXToRadian(i));
	}

	ZeroMemory( m_DrawVertices , sizeof(m_DrawVertices) ) ;

}

/***********************************************************************
void ExtinguishEffect::AddExtinguishEffect(
				const D3DXVECTOR3,	i_vPos,					//位置
				float				i_fSpeed,				//スピード
				int 				i_iRotSpeed,			//回転の速さ
				int					i_iParticleSize,		//パーティクルの数
				int					i_iLifeTime,			//表示時間
				BYTE				i_bBlue		= 0xFF,		//青色
				BYTE				i_bGreen	= 0xFF,		//緑色
				BYTE				i_bRed		= 0xFF,		//赤色
				BYTE				i_bAlpha	= 0xFF		//透明色
			);
用途: ゲージの段階が上がった時に発生するエフェクトオブジェクトの作成
戻り値: なし
************************************************************************/
void ExtinguishEffect::AddExtinguishEffect(const D3DXVECTOR3 i_vPos,float i_fSpeed,int i_iRotSpeed , int i_iLifeTime ,int i_iParticleSize, BYTE i_bBlue,BYTE i_bGreen, BYTE i_bRed,BYTE i_bAlpha)
{
	ExtinguishEffectState* State  = new ExtinguishEffectState( i_fSpeed,i_vPos,i_iRotSpeed,i_iLifeTime,i_iParticleSize,i_bBlue,i_bGreen,i_bRed,i_bAlpha) ;
	m_Statelist.push_back(State);

}

/******************************************************************
virtualvoid ExtinguishEffect::Transform(
	LPDIRECT3DDEVICE9		pD3DDevice	,	//デバイス
	const CONTROLER_STATE*	pCntlState	,	//コントローラのステータス
	vector<Object*>&		i_Vec		,	//オブジェクトの配列
	Command&				i_Com			//コマンド
) ;
用途 : シーンの変化
戻り値 : なし
******************************************************************/
void ExtinguishEffect::Transform( LPDIRECT3DDEVICE9 pD3DDevice , const CONTROLER_STATE* pCntlState ,vector<Object*> i_ObjectVec ,Command& i_Com)
{
	try{

		list<ExtinguishEffectState*>::iterator		StateIt = m_Statelist.begin() ;		//描画システムのステータス
		list<ExtinguishEffectState*>::iterator		endIt	= m_Statelist.end() ;		//ループの終わり

		//描画ループ
		while(StateIt != endIt){

			//一つのパーティクルを動かし、削除する場合に真が返ってくる
			bool DeleteFlg = (*StateIt)->Move(m_fRadSinArray,m_fRadCosArray) ;		

			//削除処理
			if(DeleteFlg){

				StateIt = m_Statelist.erase(StateIt);
				continue ;
			
			}
			
			//頂点データの変数
			list<PointSpriteRHWVertex>::iterator it  = (*StateIt)->m_Vertices.begin() ;	
			list<PointSpriteRHWVertex>::iterator end = (*StateIt)->m_Vertices.end()   ;	

			//パーティクルを描画するための頂点データを設定する
			for(  ; it != end ;  it++){

				//描画する頂点数の合計が最大値を超えてない場合
				if(m_iVerticesSize < m_iVerticesMaxSize ){
					//頂点を描画用配列に設定する
					m_DrawVertices[m_iVerticesSize] = (*it) ;
					m_iVerticesSize++ ;

				//超えた場合
				}else{
					//デバック用
					throw BaseException(L"Particleの上限を超えました",
						L"ExtinguishEffect::Draw()");
					//Release用
					//break ;

				}

			}

			StateIt++ ;	//次のパーティクルに進める
		}

	}
	catch(...){
		throw ;
	}
}

/*****************************************************************
 virtual void ExtinguishEffect::Draw(
	LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
	vector<Object*>& i_Vec,				//オブジェクトの配列
	const CONTROLER_STATE* pCntlState   //コントローラのステータス
	Command i_Com						//コマンド
 );
 用途: オブジェクトを描画
 戻り値: なし。
*****************************************************************/
void ExtinguishEffect::Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& i_Vec,
							const CONTROLER_STATE* pCntlState,Command& i_Com )
{
	try{
		//レンダーステートを変更させるためのクラスを宣言
		DeviceRenderState drs = DeviceRenderState() ;

		drs.SetDeviceRenderState(D3DRS_LIGHTING, FALSE );	//ライティングモードをFALSEに設定
		drs.ChangeRS_PointSprite(m_fEffectSize);			//描画方法をポイントスプライトに設定
		drs.ChangeRS_ALPHABLENDENABLE_Black();				//加算合成の設定

		drs.ChangeRenderState(pD3DDevice);					//上記の設定にレンダーステートを変更する

		//パーティクルの描画
		RHWVerticesRender(pD3DDevice,m_DrawVertices,m_iVerticesSize);

		//レンダーステートの変更
		drs.ChangeRenderState(pD3DDevice);

		//頂点数をゼロに戻す
		m_iVerticesSize = 0 ;

	}
	catch(...){
		throw ;
	}
}






/***********************************************************
class BreakEffect : public ThreeDimensionsEffect
用途 : 破壊されたときのエフェクト
***********************************************************/

/*******************************************************
BreakEffect::EffectState::EffectState(
	int					i_iVertexSize,		//頂点データの数
	float				i_vPos,				//位置
	)
用途 : コンストラクタ
戻り値 : なし
*******************************************************/
BreakEffect::EffectState::EffectState(int i_iVertexSize, const D3DXVECTOR3& i_vPos)
:m_iLifeTime(0)
{
	const int c_iDirType = 4 ;

	D3DXVECTOR3 DirVec[c_iDirType] = {
		D3DXVECTOR3(1.0f,1.0f,0.0f),
		D3DXVECTOR3(-1.0f,1.0f ,0.0f),
		D3DXVECTOR3(1.0f,-1.0f,0.0f),
		D3DXVECTOR3(-1.0f,-1.0f ,0.0f)
	};

	for(int i = 0 ; i < i_iVertexSize ; i++){

		float fSpeed =  ( rand() % 3 ) * 0.1f  + 0.03f ; 
		float DirX = ( rand() % 10 ) * 0.05f + 0.1f;
		float DirY = ( rand() % 10 ) * 0.05f + 0.1f;
		
		D3DXVECTOR3 Dir = D3DXVECTOR3( DirX , DirY , 0.0f ) ;
		Dir.x *= DirVec[ i % c_iDirType ].x ;
		Dir.y *= DirVec[ i % c_iDirType ].y ; 

		m_Vertices.push_back(PointSpriteVertex(i_vPos,0xFF,0xFF,0xFF,0xFF));
		m_EffectParams.push_back( EffectParam(Dir,fSpeed) );
	}
}


/*****************************************************************
bool BreakEffect::EffectState::Move(
		Command				i_Com			//コマンド
)
用途 : Particleの動きを行い削除処理の場合はtrueを返す
戻り値 : なし
*****************************************************************/
bool BreakEffect::EffectState::Move( Command& i_Com )
{

	//飛び散っている時間
	const int c_iDeadTime = 50 ;

	//頂点データのイテレータの宣言
	list<PointSpriteVertex>::iterator VertexIt	= m_Vertices.begin();
	list<PointSpriteVertex>::iterator end		= m_Vertices.end()  ;

	//移動パラメータのイテレータの宣言
	list<EffectParam>::iterator ParamIt = m_EffectParams.begin() ;

	//頂点データを移動されるループ
	while(VertexIt != end){

		 (*ParamIt).m_fSpeed -=  (*ParamIt).m_fSpeed / c_iDeadTime ;

		(*VertexIt).m_vPos +=  (*ParamIt).m_vDir *  (*ParamIt).m_fSpeed ;		//移動処理
		(*VertexIt).m_Color.r += 10 ;											//色の変更

		//各データを次に進める
		ParamIt++	;
		VertexIt++	;
	}

	m_iLifeTime++ ;

	//削除したい場合はtrueを返す
	if(m_iLifeTime < c_iDeadTime )	return false ;
	else							return true  ;
}

/**********************************************************************
BreakEffect::BreakEffect(
	LPDIRECT3DDEVICE9	pD3DDevice,			//デバイス
	const wchar_t*		i_filename,			//画像のファイル名
	DWORD				i_Decolorisation,	//抜きたい色
	float				i_fSize				//エフェクトの大きさ
	)
用途: コンストラクタ
戻り値: なし
***********************************************************************/
BreakEffect::BreakEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,DWORD i_Decolorisation,float i_fSize)
:ThreeDimensionsEffect(pD3DDevice,i_filename,i_Decolorisation,i_fSize),m_iDrawVerticesNumber( 0 )
{
	for(int i = 0 ; i < m_iVerticesMaxSize ; i++ )
		m_DrawVertices[i] = PointSpriteVertex(D3DXVECTOR3(0.0f,0.0f,0.0f),0xFFFFFFFF) ;
}

/***********************************************************************
void BreakEffect::AddBreakEffect(
				const D3DXVECTOR3& i_vPos,	//位置
				);
用途: ブロック破壊時のエフェクトオブジェクトの作成
戻り値: なし
************************************************************************/
void BreakEffect::AddBreakEffect(const D3DXVECTOR3& i_vPos)
{
	const int c_VertexSize = 5 ;

	EffectState*		State  = new EffectState( c_VertexSize , i_vPos ) ;
	m_Statelist.push_back(State);

}

/******************************************************************
virtual void BreakEffect::Transform(
	LPDIRECT3DDEVICE9		pD3DDevice	,	//デバイス
	const CONTROLER_STATE*	pCntlState	,	//コントローラのステータス
	vector<Object*>&		i_Vec		,	//オブジェクトの配列
	Command&				i_Com			//コマンド
) ;
用途 : シーンの変化
戻り値 : なし
******************************************************************/
void BreakEffect::Transform( LPDIRECT3DDEVICE9 pD3DDevice , const CONTROLER_STATE* pCntlState ,vector<Object*> i_ObjectVec ,Command& i_Com)
{


	//描画用iteratorの宣言
	list<EffectState*>::iterator		StateIt  = m_Statelist.begin() ;
	//ループ用イテレータの宣言
	list<EffectState*>::iterator		endIt = m_Statelist.end() ;

	for(int i = 0 ; StateIt != endIt ; i++ ){

		//移動処理
		bool DeleteFlg = (*StateIt)->Move( i_Com );

		//削除処理
		if(DeleteFlg){

			StateIt  = m_Statelist.erase(StateIt) ;

		}else{

			//配列に入れる頂点データ
			list<PointSpriteVertex>::iterator it  = (*StateIt)->m_Vertices.begin() ;
			list<PointSpriteVertex>::iterator end = (*StateIt)->m_Vertices.end() ;

			//配列に描画されるバーテックスのデータを入れる
			for( ; it != end ; it++ ){
				m_DrawVertices[m_iDrawVerticesNumber] = (*it) ;
				m_iDrawVerticesNumber++ ;
			}

			//イテレータを次に進める
			StateIt++  ;
		}

	}

}

/*****************************************************************
 virtual void BreakEffect::Draw(
	LPDIRECT3DDEVICE9		pD3DDevice	,	//IDirect3DDevice9 インターフェイスへのポインタ
	vector<Object*>&		i_Vec		,	//オブジェクトの配列
	const CONTROLER_STATE*	pCntlState	,	//コントローラのステータス
	Command					i_Com			//コマンド
 );
 用途: オブジェクトを描画
 戻り値: なし。
*****************************************************************/
void BreakEffect::Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& i_Vec,
							const CONTROLER_STATE* pCntlState,Command& i_Com )
{

	//レンダーステートを変更させるためのクラスを宣言
	DeviceRenderState drs = DeviceRenderState() ;
	drs.SetDeviceRenderState(D3DRS_LIGHTING, FALSE );	//ライティングモードをFALSE
	drs.ChangeRS_PointSprite(m_fEffectSize);
	drs.ChangeRS_ALPHABLENDENABLE_Black();
	drs.ChangeRenderState(pD3DDevice);

	//マトリックスの設定
	D3DXMATRIX Matrix ;
	D3DXMatrixIdentity(&Matrix);		
	pD3DDevice->SetTransform(D3DTS_WORLD,&Matrix);

	//パーティクルの描画
	VerticesRender(pD3DDevice,m_DrawVertices,m_iDrawVerticesNumber);

	//レンダーステートの変更
	drs.ChangeRenderState(pD3DDevice);

	//頂点数をゼロに戻す
	m_iDrawVerticesNumber = 0 ;
	//頂点データの配列をリセットする
	ZeroMemory( m_DrawVertices , sizeof( m_DrawVertices ));

}


/*******************************************************************
class LineEffect : public Object 定義部
用途 :	線エフェクトの描画
*******************************************************************/

/*******************************************************************
class LineEffect::LineEffectGroup::LineEffectState  定義部
用途 : 線エフェクトを管理するステータス
*******************************************************************/
/***********************************************************
LineEffect::LineEffectGroup::LineEffectState::LineEffectState(
	LPDIRECT3DDEVICE9	pD3DDevice	,	//デバイス
	const D3DXVECTOR3&	i_vPos		,	//位置
	const D3DXVECTOR3&	i_vSize		,	//大きさ
	const D3DXVECTOR3&	i_vRot			//回転度
	VertexStyle			i_VertexStyle	//線の形
);
用途 : コンストラクタ
戻り値 : なし
***********************************************************/
LineEffect::LineEffectGroup::LineEffectState::LineEffectState(LPDIRECT3DDEVICE9 pD3DDevice , const D3DXVECTOR3& i_vPos ,
	const D3DXVECTOR3& i_vSize , const D3DXVECTOR3& i_vRot , VertexStyle i_VertexStyle )
:m_vPos( i_vPos ),m_vSize( i_vSize ),m_vRot( i_vRot )
{

	m_VLState = new VertexLineState(pD3DDevice , 0 );
	m_VLState->SetVertex(pD3DDevice , i_VertexStyle , D3DPT_LINESTRIP );

}

/***************************************************************
struct LineEffect::LineEffectGroup	定義部
用途 : 線エフェクトを管理する構造体
***************************************************************/
/**************************************************************
LineEffect::LineEffectGroup::LineEffectGroup(
	float				i_fRotZSpeed,	//	回転速度
	float				i_fScaling		//	拡大縮小の値
	int					i_iLifeTime		//出現している時間
);
用途 : コンストラクタ
戻り値 : なし
**************************************************************/
LineEffect::LineEffectGroup::LineEffectGroup( float i_fRotZSpeed ,float i_fScaling , int i_iLifeTime )
:m_fRotZSpeed( i_fRotZSpeed ) , m_fScale( i_fScaling ),m_iLifeTime( i_iLifeTime )
{
}

/**************************************************************
void LineEffect::LineEffectGroup::Move( 
	Command& i_Com		//コマンド
);
用途 : 動作
戻り値 : なし
**************************************************************/
void LineEffect::LineEffectGroup::Move( Command& i_Com )
{
	float fRotZSpeed	= m_fRotZSpeed	 ;		//	回転速度
	DWORD dwDownColor	= 0x00000D2B	 ;		//	色の変位
	vector<LineEffectState*>::size_type i	= 0 ;
	vector<LineEffectState*>::size_type end	= m_StateVec.size() ;

	for( i = 0 ; i < end ; i++){
		m_StateVec[ i ]->m_vRot.z	+= fRotZSpeed	;
		m_StateVec[ i ]->m_vSize.x	+= m_fScale		;
		m_StateVec[ i ]->m_vSize.y	+= m_fScale		;
		m_StateVec[ i ]->m_Matrix = CreateMatrix( m_StateVec[i]->m_vPos , m_StateVec[i]->m_vSize , m_StateVec[i]->m_vRot );

		m_StateVec[ i ]->m_VLState->SetDownColor( dwDownColor );
		fRotZSpeed *= -1 ;	//回転方向を反転させる
	}

	m_iLifeTime-- ;
	
}

/*************************************************************
void LineEffect::LineEffectGroup::Draw( 
	LPDIRECT3DDEVICE9 pD3DDevice	//デバイス
)
用途 : 
戻り値 : 
*************************************************************/
void LineEffect::LineEffectGroup::Draw( LPDIRECT3DDEVICE9 pD3DDevice )
{
	vector<LineEffectState*>::size_type i	= 0 ;
	vector<LineEffectState*>::size_type end	= m_StateVec.size() ;

	for( i = 0 ; i < end ; i++){
		m_StateVec[ i ]->m_VLState->Draw(pD3DDevice , m_StateVec[ i ]->m_Matrix ) ;
	}

}


/******************************************************************
LineEffect::LineEffect() ;
用途 : コンストラクタ
戻り値 : なし
******************************************************************/
LineEffect::LineEffect( )
{
}

/******************************************************************
LineEffect::~LineEffect();
用途 : デストラクタ
戻り値 : なし
******************************************************************/
LineEffect::~LineEffect()
{
}

/******************************************************************
void LineEffect::AddLineEffect(
	LPDIRECT3DDEVICE9 pD3DDevice	,	//デバイス
	const D3DXVECTOR3&	i_vPos		,	//位置
	const D3DXVECTOR3&	i_vSize		,	//大きさ
	const D3DXVECTOR3&	i_vRot		,	//回転度
	VertexStyle			i_VertexStyle	//線の形
	float				i_fRotZSpeed,	//	回転速度
	float				i_fScaling	,	//	拡大縮小の値
	int					i_iLifeTime	,	//出現している時間
	int					i_iLineNumber	//線の本数
);
用途 : ラインエフェクトの追加
戻り値 : なし
******************************************************************/
void LineEffect::AddLineEffect( LPDIRECT3DDEVICE9 pD3DDevice , const D3DXVECTOR3& i_vPos ,const D3DXVECTOR3& i_vSize ,
							   const D3DXVECTOR3& i_vRot , VertexStyle i_VertexStyle ,float i_fRotZSpeed ,float i_fScaling , int i_iLifeTime , int i_iLineNumber)
{

	D3DXVECTOR3 vRot			= i_vRot	;					//回転用の作業領域
	float		fRotZ			= 15.0f	/ i_iLineNumber;	//エフェクト一つ後にずらす回転度数
	const float	fSize			= 0.25f		;					//生成時の大きさをずらす用の変数

	LineEffectGroup* LEG = new LineEffectGroup( i_fRotZSpeed , i_fScaling , i_iLifeTime);

	//エフェクトの生成ループ
	for(int i = 0 ; i < i_iLineNumber ; i++ ){

		D3DXVECTOR3 wvSize = i_vSize + D3DXVECTOR3( (i * fSize) / ((i_iLineNumber - i) * fSize ) , (i * fSize) / ((i_iLineNumber - i) * fSize) , 0.0f )  ; 

		LEG->m_StateVec.push_back(new LineEffectGroup::LineEffectState(
										pD3DDevice , i_vPos , wvSize , vRot ,
										i_VertexStyle ) );
		vRot.z += fRotZ ;
	}

	m_StateVec.push_back( LEG );
}

/******************************************************************
virtual void LineEffect::Transform(
	LPDIRECT3DDEVICE9		pD3DDevice	,	//デバイス
	const CONTROLER_STATE*	pCntlState	,	//コントローラのステータス
	vector<Object*>&		i_Vec		,	//オブジェクトの配列
	Command&				i_Com			//コマンド
) ;
用途 : シーンの変化
戻り値 : なし
******************************************************************/
void LineEffect::Transform( LPDIRECT3DDEVICE9 pD3DDevice , const CONTROLER_STATE* pCntlState ,vector<Object*> i_ObjectVec ,Command& i_Com)
{
	vector<LineEffectGroup*>::size_type i	= 0 ;
	vector<LineEffectGroup*>::size_type end	= m_StateVec.size() ;

	for( i = 0 ; i < end ; i++){
		m_StateVec[ i ]->Move(i_Com) ;
	}

}

/*****************************************************************
 virtual void LineEffect::Draw(
	LPDIRECT3DDEVICE9		pD3DDevice	,	//IDirect3DDevice9 インターフェイスへのポインタ
	vector<Object*>&		i_Vec		,	//オブジェクトの配列
	const CONTROLER_STATE*	pCntlState	,	//コントローラのステータス
	Command					i_Com			//コマンド
 );
 用途: オブジェクトを描画
 戻り値: なし。
*****************************************************************/
void LineEffect::Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& i_Vec,
							const CONTROLER_STATE* pCntlState,Command& i_Com )
{
	vector<LineEffectGroup*>::iterator it ;
	vector<LineEffectGroup*>::iterator end	= m_StateVec.end() ;

	for( it = m_StateVec.begin() ; it != end ; ){

		//描画処理
		(*(it))->Draw(pD3DDevice);

		if((*(it))->m_iLifeTime > 0 ){
	
			it++ ;

		//もしライフタイムがなくなったら削除する
		}else{

			it	= m_StateVec.erase( it );
			end = m_StateVec.end() ;
		}

	}

}

/***************************************************************************
D3DXVECTOR3 LineEffect::getPos(
	int i_iVecNum	//配列内での添え字
) ;
用途 : 位置を返す
戻り値 : 指定された添え字のObjectの位置を返す
***************************************************************************/
D3DXVECTOR3 LineEffect::getPos( int i_iVecNum )
{
	int iMaxSize = m_StateVec.size() ;
	if( i_iVecNum > iMaxSize ) i_iVecNum %= iMaxSize ;

	return m_StateVec[ i_iVecNum ]->m_StateVec[ 0 ]->m_vPos ;
}

/**************************************************************************
const int LineEffect::getObjectVecSize() const ;
用途 : オブジェクトの数を把握する
戻り値 : このクラスで管理しているObjectの数
**************************************************************************/
const int LineEffect::getObjectVecSize() const
{
	return m_StateVec.size() ;
}

/*******************************************************************
class NameLineEffect : public Object 定義部
用途 :	名前の線エフェクトの描画
*******************************************************************/

/*******************************************************************
class NameLineEffect::NameLineEffectState  定義部
用途 : 線エフェクトを管理するステータス
*******************************************************************/
/***********************************************************
NameLineEffect::NameLineEffectGroup::NameLineEffectState::NameLineEffectState(
	LPDIRECT3DDEVICE9	pD3DDevice	,	//デバイス
	const D3DXVECTOR3&	i_vPos		,	//位置
	const D3DXVECTOR3&	i_vSize		,	//大きさ
	const D3DXVECTOR3&	i_vRot			//回転度
	VertexStyle			i_VertexStyle	//線の形
);
用途 : コンストラクタ
戻り値 : なし
***********************************************************/
NameLineEffect::NameLineEffectState::NameLineEffectState(LPDIRECT3DDEVICE9 pD3DDevice , const D3DXVECTOR3& i_vPos ,
	const D3DXVECTOR3& i_vSize , const D3DXVECTOR3& i_vRot , VertexStyle i_VertexStyle )
:m_vPos( i_vPos ),m_vSize( i_vSize )
{

	m_pVLState = new VertexLineState(pD3DDevice , 0 );
	m_pVLState->SetVertex(pD3DDevice , i_VertexStyle , D3DPT_LINESTRIP );

	m_pPointSprite = new PointSpriteVertex( g_vZero , 0xFFFFFFFF) ;
}

/************************************************************
NameLineEffect::NameLineEffectState::~NameLineEffectState();
用途 : デストラクタ
戻り値 : なし
************************************************************/
NameLineEffect::NameLineEffectState::~NameLineEffectState()
{
	SafeDelete( m_pVLState );
	SafeDelete( m_pPointSprite );
}

/**************************************************************
void NameLineEffect::NameLineEffectState::Move( 
	Command& i_Com		//コマンド
);
用途 : 動作
戻り値 : なし
**************************************************************/
void NameLineEffect::NameLineEffectState::Move( Command& i_Com )
{
	m_Matrix = CreateMatrix( m_vPos , m_vSize , g_vZero ) ;
	D3DXVECTOR3 vOffsetPos = m_vSize ;
	vOffsetPos.x *=  0.9f	;
	vOffsetPos.y += vOffsetPos.y * 0.5f ;
	m_pPointSprite->m_vPos = m_vPos + vOffsetPos ;
}

/******************************************************************
NameLineEffect::NameLineEffect(
	LPDIRECT3DDEVICE9	pD3DDevice,			//デバイス
	const wchar_t*		i_filename			//画像のファイル名
	float				i_fSize				//エフェクトの大きさ
) ;
用途 : コンストラクタ
戻り値 : なし
******************************************************************/
NameLineEffect::NameLineEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,float i_fSize)
:ThreeDimensionsEffect( pD3DDevice , i_filename , 0x00000000 , i_fSize ),m_iDrawVerticesNumber(0)
{
	ZeroMemory(m_DrawVertices , sizeof(m_DrawVertices) )	;
				

}

/******************************************************************
NameLineEffect::~NameLineEffect();
用途 : デストラクタ
戻り値 : なし
******************************************************************/
NameLineEffect::~NameLineEffect()
{
}

/******************************************************************
void NameLineEffect::AddNameLineEffect(
	LPDIRECT3DDEVICE9 pD3DDevice	,	//デバイス
	const D3DXVECTOR3&	i_vPos		,	//位置
	const D3DXVECTOR3&	i_vSize		,	//大きさ
);
用途 : ラインエフェクトの追加
戻り値 : なし
******************************************************************/
void NameLineEffect::AddNameLineEffect( LPDIRECT3DDEVICE9 pD3DDevice , const D3DXVECTOR3& i_vPos ,const D3DXVECTOR3& i_vSize )
{
	m_StateVec.push_back(new NameLineEffectState(pD3DDevice , i_vPos , i_vSize ,g_vZero ,VS_NameLine ) );
}

/******************************************************************
virtual void NameLineEffect::Transform(
	LPDIRECT3DDEVICE9		pD3DDevice	,	//デバイス
	const CONTROLER_STATE*	pCntlState	,	//コントローラのステータス
	vector<Object*>&		i_Vec		,	//オブジェクトの配列
	Command&				i_Com			//コマンド
) ;
用途 : シーンの変化
戻り値 : なし
******************************************************************/
void NameLineEffect::Transform( LPDIRECT3DDEVICE9 pD3DDevice , const CONTROLER_STATE* pCntlState ,vector<Object*> i_ObjectVec ,Command& i_Com)
{
	vector<NameLineEffectState*>::size_type i	= 0 ;
	vector<NameLineEffectState*>::size_type end	= m_StateVec.size() ;

	for( i = 0 ; i < end ; i++){
		m_StateVec[ i ]->Move(i_Com) ;
		m_DrawVertices[m_iDrawVerticesNumber] = *( m_StateVec[ i ]->m_pPointSprite ) ;
		m_iDrawVerticesNumber++ ;
	}

}

/*****************************************************************
 virtual void NameLineEffect::Draw(
	LPDIRECT3DDEVICE9		pD3DDevice	,	//IDirect3DDevice9 インターフェイスへのポインタ
	vector<Object*>&		i_Vec		,	//オブジェクトの配列
	const CONTROLER_STATE*	pCntlState	,	//コントローラのステータス
	Command					i_Com			//コマンド
 );
 用途: オブジェクトを描画
 戻り値: なし。
*****************************************************************/
void NameLineEffect::Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& i_Vec,
							const CONTROLER_STATE* pCntlState,Command& i_Com )
{

	vector<NameLineEffectState*>::iterator it ;
	vector<NameLineEffectState*>::iterator end	= m_StateVec.end() ;


	//線の描画
	for( it = m_StateVec.begin() ; it != end ; ){

		//描画処理
		(*(it))->m_pVLState->Draw(pD3DDevice,(*it)->m_Matrix);
		//if((*(it))->m_iLifeTime > 0 ){
	
		//	it++ ;

		////もしライフタイムがなくなったら削除する
		//}else{

		//	it	= m_StateVec.erase( it );
		//	end = m_StateVec.end() ;
		//}
		it++ ;

	}
	D3DXMATRIX mMatrix ;
	D3DXMatrixIdentity( &mMatrix );
	pD3DDevice->SetTransform( D3DTS_WORLD , &mMatrix );

	//名前の描画
	//レンダーステートを変更させるためのクラスを宣言
	DeviceRenderState drs = DeviceRenderState() ;
	drs.SetDeviceRenderState(D3DRS_LIGHTING, FALSE );	//ライティングモードをFALSE
	drs.ChangeRS_PointSprite(m_fEffectSize);
	drs.ChangeRS_ALPHABLENDENABLE_Black();
	drs.ChangeRenderState(pD3DDevice);
	//パーティクルの描画
	VerticesRender(pD3DDevice,m_DrawVertices,m_iDrawVerticesNumber);
	//レンダーステートの変更
	drs.ChangeRenderState(pD3DDevice);

	//頂点数をゼロに戻す
	m_iDrawVerticesNumber = 0 ;
	//頂点データの配列をリセットする
	ZeroMemory( m_DrawVertices , sizeof( m_DrawVertices ));


}

/****************************************************************
void NameLineEffect::setPos( 
	const vector<D3DXVECTOR3*>& i_vPosVec //指定したいポジションの配列
);
用途 : 渡されたポジションの数だけ位置をセットする
戻り値 : なし
****************************************************************/
void NameLineEffect::setPos( const D3DXVECTOR3& i_vPosVec )
{

	!m_StateVec.empty() && ( m_StateVec[0]->m_vPos  = i_vPosVec ) ;
}

}
