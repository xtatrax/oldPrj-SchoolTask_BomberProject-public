////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Magnetic.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：磁石属性
//					▼
//	namespace wiz;
//		class Factory_Magnetic ;
//
#pragma once


namespace wiz{
namespace bomberobject{

//**************************************************************************//
// class MagneticObject : public PrimitiveCylinder ;
//
// 担当者  : 鴫原 徹
// 用途    : 磁界オブジェクト
//         : コイルオブジェクトやユーザー設置磁界にも応用しています｡
//**************************************************************************//
extern class PlayerCoil ;
class MagneticObject {
//////////
//	: 非公開
private:
	//	: 磁極フラグ
	//	: S極 = POLE_S
	//	: N極 = POLE_N
	POLE			m_bMagnetPole		;
	float			m_fMagneticum		;
	D3DMATERIAL9	m_PoleMaterial		;
//////////
//	: プロテクト
protected:
	void setPoleS(){ m_bMagnetPole = POLE_S  ; setColorS() ; }
	void setPoleN(){ m_bMagnetPole = POLE_N	 ; setColorN() ; }
	void setPole( POLE bPool ){
		     if( bPool == POLE_N ) setPoleN() ;
		else if( bPool == POLE_S ) setPoleS() ;
	}
	
	void setColorS(){
		m_PoleMaterial.Ambient.a = 1.0f ; m_PoleMaterial.Ambient.b = 1.0f ; m_PoleMaterial.Ambient.g = 0.0f ; m_PoleMaterial.Ambient.r = 0.0f ;
		m_PoleMaterial.Diffuse.a = 1.0f ; m_PoleMaterial.Diffuse.b = 1.0f ; m_PoleMaterial.Diffuse.g = 1.0f ; m_PoleMaterial.Diffuse.r = 1.0f ; 
	}
	void setColorN(){
		m_PoleMaterial.Ambient.a = 1.0f ; m_PoleMaterial.Ambient.b = 0.0f ; m_PoleMaterial.Ambient.g = 0.0f ; m_PoleMaterial.Ambient.r = 1.0f ;
		m_PoleMaterial.Diffuse.a = 1.0f ; m_PoleMaterial.Diffuse.b = 1.0f ; m_PoleMaterial.Diffuse.g = 1.0f ; m_PoleMaterial.Diffuse.r = 1.0f ;	
	}
	void setColorSuper(){
		m_PoleMaterial.Ambient.a = 1.0f ; m_PoleMaterial.Ambient.b = 0.0f ; m_PoleMaterial.Ambient.g = 1.0f ; m_PoleMaterial.Ambient.r = 1.0f ;
		m_PoleMaterial.Diffuse.a = 1.0f ; m_PoleMaterial.Diffuse.b = 1.0f ; m_PoleMaterial.Diffuse.g = 1.0f ; m_PoleMaterial.Diffuse.r = 1.0f ;			
	}

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

	bool ChangePole(){
		if( m_bMagnetPole == POLE_S )	{ setPoleN() ; }
		else							{ setPoleS() ; }
		return true ;
	}

//////////
//	: 公開
public:
	/////////////////// ////////////////////
	//// 用途       ：MagneticObject() ;
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：
	//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	////			  :   LPDIRECT3DTEXTURE9 pTexture,  //テクスチャ	
	////              :   wiz::OBJID id = OBJID_3D_MAGNET //ID
	//// 戻値       ：なし
	//// 担当者     ：曳地 大洋
	//// 備考       ：
	////	
	MagneticObject() ;


	/////////////////// ////////////////////
	//// 用途       ：  ~MagneticObject()
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：Player用のコンストラクタ
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////	
	~MagneticObject();

	/////////////////// ////////////////////
	//// 関数名     ：void ChangePole()
	//// カテゴリ   ：ゲッター
	//// 用途       ：磁極を獲得
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：曳地大洋
	//// 備考       ： S極 = POLE_S = false
	////			 ： N極 = POLE_N = true
	POLE  getMagnetPole() const { return m_bMagnetPole	;	}	;

	float getMagneticum() const { return m_fMagneticum*m_fMagneticum  ;	}	;
	D3DMATERIAL9 getMaterial(){
		return m_PoleMaterial ;
	}
};



/**************************************************************************
 class Factory_Magnetic;
 用途: メイン工場クラス
****************************************************************************/
class Factory_Magnetic{
public:
/**************************************************************************
 Factory_Magnetic(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	//Factory_Magnetic(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,TextureManager& TexMgr);
	Factory_Magnetic( FactoryPacket* fpac ) ;
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
~Factory_Magnetic() ;
};
}
//end of namespace bomberobject.
}
//end of namespace wiz.
