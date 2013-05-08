////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Enemy.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：斎藤　謙吾
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Wall ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"

namespace wiz{
	namespace baseobject{

	class EnemySphere : public PrimitiveSphere {

		struct  SphereVertex{
			D3DXVECTOR3 vec;
			D3DXVECTOR3 n;
			FLOAT       tu,tv;
		};

		//PrimitiveSphere用のFVFをDIrectXAPIに渡すときのパラメータ
		enum { BallFVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
			LPDIRECT3DTEXTURE9 m_pTexture;

	//Enemy用		
	/////////////////// ////////////////////
	//// 関数名     ：void Vec2UV(float x,float y,float z,float r,float& u,float& v );
	//// カテゴリ   ：メンバ関数
	//// 用途       ：VectorをUとVにコンバート
	//// 引数       ：  float x     //xの値
	////            ：  float y     //yの値
	////            ：  float z     //zの値
	////            ：  float r     //球の半径
	////            ：  float& u    //変換するu（テクスチャ上のU座標）
	////            ：  float& v    //変換するv（テクスチャ上のV座標）
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹(山ノ井先生のひな形より)
	//// 備考       ：float& uとfloat& vに変換後の値を代入
	////            ：
	////
			void Vec2UV(float x,float y,float z,float r,float& u,float& v);
	/////////////////// ////////////////////
	//// 関数名     ：void CreateSphere(LPDIRECT3DDEVICE9 pD3DDevice)
	//// カテゴリ   ：関数
	//// 用途       ：球を生成
	//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
	//// 戻値       ：なし
	//// 担当者     ： (山ノ井先生のひな形より)
	//// 備考       ：float& uとfloat& vに変換後の値を代入
	////            ：
	////
		void CreateSphere(LPDIRECT3DDEVICE9 pD3DDevice);
	protected:
	/////////////////// ////////////////////
	//// 関数名     ：EnemySphere(LPDIRECT3DDEVICE9 pD3DDevice,D3DCOLORVALUE& Diffuse,
	////            ：  D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,LPDIRECT3DTEXTURE9 pTexture = 0);
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：球体を作成
	//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9インターフェイスへのポインタ
	////            ：  D3DCOLORVALUE& Diffuse,         //ディフューズ色
	////            ：  D3DCOLORVALUE& Specular,            //スペキュラ色
	////            ：  D3DCOLORVALUE& Ambient,          //アンビエント色
	////            ：  LPDIRECT3DTEXTURE9 pTexture = 0	//テクスチャを張るときは指定
	//// 戻値       ：なし（失敗時は例外をthrow）
	//// 担当者     ： (山ノ井先生のひな形より)
	//// 備考       ：PrimitiveSphereの派生型
	////           ：
	////
		EnemySphere(LPDIRECT3DDEVICE9 pD3DDevice,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
			LPDIRECT3DTEXTURE9 pTexture = 0 , wiz::OBJID id = OBJID_3D_ENEMY);


	/////////////////// ////////////////////
	//// 関数名     ：~EnemySphere();
	//// カテゴリ   ：デストラクタ
	//// 用途       ：球体を破棄
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当者     ： (山ノ井先生のひな形より)
	//// 備考       ：PrimitiveSphereの派生型
	////            ：
	////
		virtual ~EnemySphere();

	/////////////////// ////////////////////
	//// 関数名     ：void Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
	//// カテゴリ   ：仮想関数
	//// 用途       ：球体を描画
	//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  vector<Object*>& Vec,				//オブジェクトの配列
	//// 戻値       ：なし
	//// 担当者     ： (山ノ井先生のひな形より)
	//// 備考       ：
	////            ：
	////
		virtual void Draw(DrawPacket& i_DrawPacket) ;
	};

	}//end of namespace baseobject.
	using namespace baseobject;
}//end of namespace wiz.