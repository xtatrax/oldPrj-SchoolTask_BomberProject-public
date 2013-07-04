////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_MagnetField.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	引継ぎ			：曳地 大洋
//	└→			：本多 寛之
//	内包ﾃﾞｰﾀと備考	：磁界範囲の可視化Object
//					▼
//	namespace wiz;
//		class Factory_MagnetField ;
//
#pragma once
#include "Factory_Magnetic.h"

namespace wiz{
namespace bomberobject{

extern class MagneticGage_N;
extern class MagneticGage_S;


class MagnetFieldCircle{
	struct Vertex
	{
		D3DXVECTOR3 vPos ;
		DWORD dwColor ;

		Vertex(): vPos( 0.0f, 0.0f, 0.0f ), dwColor( 0xFFFFFFFF ){ }
		Vertex( const D3DXVECTOR3& i_vPos, DWORD i_dwColor ): vPos( i_vPos ), dwColor( i_dwColor ){	}
		static size_t getSize()	{	return sizeof( Vertex );	}
		static DWORD getFVF(){return D3DFVF_XYZ | D3DFVF_DIFFUSE ;}
	};
	static DWORD						m_dwMyInstance	;
	static LPDIRECT3DVERTEXBUFFER9		m_pVertexBuffer	;	//バッファ
	static DWORD						m_dwVertexQty	;
	D3DXMATRIX					m_mMatrix		;
	DWORD						m_dwColor_N		;
	DWORD						m_dwColor_S		;

public:
	MagnetFieldCircle(LPDIRECT3DDEVICE9 pD3DDevice );
	~MagnetFieldCircle();
	void Draw(DrawPacket& i_DrawPacket);
	void setMatrix(D3DXMATRIX& i_mMatrix){
		m_mMatrix = i_mMatrix;
	}
	void setPole(POLE pl){
		Vertex* m_pVertex;
		m_pVertexBuffer->Lock( 0, 0, (void**)&m_pVertex ,0 );	//	: 頂点データのアドレスを取得するとともに、データへのアクセスを開始する	


		if( pl == POLE_S ){
			m_pVertex[ 0 ].dwColor = m_dwColor_S;
			for ( DWORD i = 1 ; i <= m_dwVertexQty  ; i++ ){
				m_pVertex[ i ].dwColor = m_dwColor_S;
			}
		}else{
			m_pVertex[ 0 ].dwColor = m_dwColor_N;
			for ( DWORD i = 1 ; i <= m_dwVertexQty  ; i++ ){
				m_pVertex[ i ].dwColor = m_dwColor_N;
			}
		
		}
		m_pVertexBuffer->Unlock();
	}

	void	setColor( POLE pl, DWORD i_dwColor){
		if( pl == POLE_S ){
			m_dwColor_S	= i_dwColor;
		}else{		
			m_dwColor_N	= i_dwColor;
		}
	}

	void	ResetColor(){
		m_dwColor_S	= 0x3F0000FF;
		m_dwColor_N	= 0x3FFF0000;
	}
};

//3D変換用
//**************************************************************************//
// class MagnetField : public PrimitiveCylinder ;
//
// 担当者  : 曳地 大洋
// 編集    : 鴫原 徹(大幅改良)
//         : 本多 寛之
// 用途    : 磁界オブジェクト
//         : コイルオブジェクトやユーザー設置磁界にも応用しています｡
//**************************************************************************//
extern class PlayerCoil ;
class MagnetField : public Object, public MagneticObject{

//////////
//	: プロテクト
protected:
	Camera*				m_pCamera			;
	PlayerCoil*			m_pCoil				;
	MagneticGage_N*		m_pPole_N			;
	MagneticGage_S*		m_pPole_S			;
	MagnetFieldCircle	m_MagneticField		;
	D3DXVECTOR3			m_vPos				;
	float				m_fEffectSizeRate	;
	bool				m_bPtn				;
	int					m_iFlashingInterval	;

protected:


//////////
//	: 公開
public:
	/////////////////// ////////////////////
	//// 用途       ：MagnetField(
	///										LPDIRECT3DDEVICE9 pD3DDevice,
	///										LPDIRECT3DTEXTURE9 pTexture,
	///										wiz::OBJID id = OBJID_3D_MAGNET
	///										) ;
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：
	//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	////			  :   LPDIRECT3DTEXTURE9 pTexture,  //テクスチャ	
	////              :   wiz::OBJID id = OBJID_3D_MAGNET //ID
	//// 戻値       ：無し
	//// 担当者     ：曳地 大洋
	//// 備考       ：
	////	
	MagnetField(
		LPDIRECT3DDEVICE9 pD3DDevice,
		wiz::OBJID id 
		) ;



	/////////////////// ////////////////////
	//// 用途       ：  ~MagnetField()
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：Player用のコンストラクタ
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////	
	~MagnetField();

	/////////////////// ////////////////////
	//// 用途       ：void Draw( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：関数
	//// 用途       ：オブジェクトをディスプレイに表示する
	//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
	////			 ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
	////             ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
	////             ：  ├ Tempus2*            i_DrawPacket.GetTime()	   // 時間を管理するクラスへのポインター
	////             ：  └ Command             i_DrawPacket.pCommand   // コマンド
	//// 戻値       ：無し
	//// 担当者     ：曳地 大洋
	//// 備考       ：
	////
	void Draw( DrawPacket& i_DrawPacket );

	/////////////////// ////////////////////
	//// 用途       ：void Update( UpdatePacket& i_UpdatePacket )
	//// カテゴリ   ：関数
	//// 用途       ：オブジェクトを更新
	//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
	////			  ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
	////              ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
	////              ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
	////              ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
	////              ：  └       Command            pCommand        // コマンド
	//// 戻値       ：無し
	//// 担当者     ：曳地 大洋
	//// 備考       ：
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
		return m_vPos			;	
	}	;

	void HitTest();

	/////////////////// ////////////////////
	//// 関数名     ：multimap<float, Magnet3DItem*> getMapTarget() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：m_ItemMap_Targetを獲得
	//// 引数       ：なし
	//// 戻値       ：m_ItemMap_Target
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	//multimap<float, Magnet3DItem*> getMapTarget() const{
	//	return m_ItemMap_Target;
	//}
	void	Flashing( UpdatePacket& i_UpdatePacket, POLE i_Pole );
	void	Reset(){
		m_MagneticField.ResetColor();
	}
};

class StaticMagnetField : public MagnetField {
protected:
	struct Magnet3DItem{
		//	: 座標
		D3DXVECTOR3		m_vPos ;
		POLE			m_bMagnetPole ;
		float			m_fMapKey	;
		bool			m_bHidden	;
		virtual ~Magnet3DItem(){}
	};


	//map<オブジェクトのポジション, Magnet3DItem>
	typedef multimap<float, Magnet3DItem*>	ALLCONTAINER		;
	typedef list<Magnet3DItem*>				TARGETCONTAINER		;
	ALLCONTAINER		m_ItemMap_All		;
	TARGETCONTAINER		m_ItemMap_Target	;


public:
	StaticMagnetField(
		LPDIRECT3DDEVICE9 pD3DDevice,
		wiz::OBJID id 
	);
	~StaticMagnetField();
	/////////////////// ////////////////////
	//// 用途       ：void Update( UpdatePacket& i_UpdatePacket )
	//// カテゴリ   ：関数
	//// 用途       ：オブジェクトを更新
	//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
	////			  ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
	////              ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
	////              ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
	////              ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
	////              ：  └       Command            pCommand        // コマンド
	//// 戻値       ：無し
	//// 担当者     ：曳地 大洋
	//// 備考       ：
	void Update( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// 用途       ：void Draw( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：関数
	//// 用途       ：オブジェクトをディスプレイに表示する
	//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
	////			 ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
	////             ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
	////             ：  ├ Tempus2*            i_DrawPacket.GetTime()	   // 時間を管理するクラスへのポインター
	////             ：  └ Command             i_DrawPacket.pCommand   // コマンド
	//// 戻値       ：無し
	//// 担当者     ：曳地 大洋
	//// 備考       ：
	////
	void Draw( DrawPacket& i_DrawPacket );
	/////////////////// ////////////////////
	//// 用途       ：void AddMagnetic( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：関数
	//// 用途       ：マグネットの追加
	//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9インターフェイスへのポインタ
	////		    ：  D3DXVECTOR3 &vScale				//拡大縮小
	////		    ：  D3DXVECTOR3 &vRot				//回転角
	////		    ：  D3DXVECTOR3 &vPos				//位置
	////            ：  D3DCOLORVALUE& Diffuse,			//ディフューズ色
	////            ：  D3DCOLORVALUE& Specular,		//スペキュラ色
	////            ：  D3DCOLORVALUE& Ambient,			//アンビエント色
	//// 戻値       ：無し
	//// 担当者     ：曳地 大洋
	//// 備考       ：
	////
	void AddMagnetic(
		D3DXVECTOR3 &vPos,
		POLE		vPole,
		D3DCOLORVALUE& Diffuse,
		D3DCOLORVALUE& Speular,
		D3DCOLORVALUE& Ambient
	) ;
	
	/////////////////// ////////////////////
	//// 用途       ：bool CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos ) const
	//// カテゴリ   ：関数
	//// 用途       ：距離を判定
	//// 引数       ：D3DXVECTOR3& i_vMagneticFieldPos //磁界の位置 
	////　　　　　　：D3DXVECTOR3& i_vCoilPos          //コイルの位置
	////　　　　　　：float        i_iBorder           //判定する値
	//// 戻値       ：true , false
	//// 担当者     ：本多寛之
	//// 備考       ：
	//bool CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos, float i_iBorder ) const;
	
	void setDrawTarget();

	void HitTest();
};

/**************************************************************************
 class Factory_MagnetField;
 用途: メイン工場クラス
****************************************************************************/
class Factory_MagnetField{
public:
/**************************************************************************
 Factory_MagnetField(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	//Factory_MagnetField(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,TextureManager& TexMgr);
	Factory_MagnetField( FactoryPacket* fpac ) ;
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
~Factory_MagnetField() ;
};
}
//end of namespace bomberobject.
}
//end of namespace wiz.
