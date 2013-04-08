////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：DxDevice.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：グローバルな関数群のインライン定義
//					▼
//	namespace wiz;
//		struct FlexibleVertex ;
//		struct OBB  ;
//		struct AABB      ;
//		struct Sphere        ;
//		struct RENDERSTATE_PARAM ;
//		struct ObjeData    ;
//
#pragma once

#include "StdAfx.h"

namespace wiz{
class Object ; 
class TextureManager ;

extern void EarnFromMeshOBB(const LPD3DXBASEMESH i_pMesh,D3DXVECTOR3& o_vPos ,D3DXVECTOR3& o_vSize);
namespace structs{
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//**************************************************************************//
// struct FactoryPacket;
//
// 担当者  : 鴫原 徹
// 用途    : ファクトリーに渡すパケットデータ
//**************************************************************************//
struct FactoryPacket{
	//ダイアログステージかどうか
	bool m_IsDialog;
	//配置オブジェクトのポインタのベクトル
	vector<Object*> m_Vec;
	//テクスチャのポインタのベクトル
	TextureManager* m_pTexMgr;
};
//**************************************************************************
// union Color;
//
// 担当者  : 鴫原 徹
// 用途    : DWORDColorを管理しやすくする
//**************************************************************************
union Color {
	DWORD dwColor;
	struct {BYTE b , g , r , a ;}byteColor;
	Color(){};
	Color(DWORD Color):dwColor(Color){};
	Color(BYTE A ,BYTE R ,BYTE G , BYTE B )
	{ byteColor.a = A;byteColor.r = R;byteColor.g = G;byteColor.b = B;};
	Color& operator = (DWORD other){ dwColor = other ; return *this; };
};

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//**************************************************************************//
// struct FlexibleVertex;
//
// 担当者  : 鴫原 徹
// 用途    : フレキシブルな頂点を扱う
//**************************************************************************//
struct FlexibleVertex{
	D3DXVECTOR3 *pos;
	float       *rhw;
	float		*blend1;
	float		*blend2;
	float		*blend3;
	D3DXVECTOR3 *normal;
	float		*pointSize;
	DWORD		*diffuse;
	DWORD		*specular;
	//D3DXVECTOR4	*TexSet1;
	//D3DXVECTOR4	*TexSet2;
	//D3DXVECTOR4	*TexSet3;
	//D3DXVECTOR4	*TexSet4;
	//D3DXVECTOR4	*TexSet5;
	//D3DXVECTOR4	*TexSet6;
	//D3DXVECTOR4	*TexSet7;
	//D3DXVECTOR4	*TexSet8;
	FlexibleVertex(BYTE* vBuffer,DWORD FVF)
		:pos(NULL),rhw(NULL),blend1(NULL),blend2(NULL),blend3(NULL)
		,normal(NULL),pointSize(NULL),diffuse(NULL),specular(NULL)
	{
		BYTE floatByteNum  = 4;
		BYTE DwordByteNum  = 4;
		BYTE VectorByteNum = floatByteNum*3;
		BYTE Address = 0;

		//////////
		//	: 頂点ポインタ
		pos = ( D3DXVECTOR3* )  vBuffer;
		Address += VectorByteNum;

		//////////
		//	: RHWポインタ
		if( FVF & D3DFVF_XYZRHW ){
			rhw = ( float* )( vBuffer + Address );
			Address += VectorByteNum + floatByteNum;
		}

		//////////
		//	: ベータ1
		if( FVF & D3DFVF_XYZB1  ){
			blend1 = ( float* )( vBuffer + Address );
			Address +=  floatByteNum;
		}

		//////////
		//	: ベータ2
		if( FVF & D3DFVF_XYZB2  ){
			blend1 = ( float* )( vBuffer + Address );
			Address +=  floatByteNum;
			blend2 = ( float* )( vBuffer + Address );
			Address +=  floatByteNum;
		}

		//////////
		//	: ベータ3
		if( FVF & D3DFVF_XYZB3  ){
			blend1 = ( float* )( vBuffer + Address );
			Address +=  floatByteNum;
			blend2 = ( float* )( vBuffer + Address );
			Address +=  floatByteNum;
			blend3 = ( float* )( vBuffer + Address );
			Address +=  floatByteNum;
		}

		//////////
		//	: ノーマル
		if( FVF & D3DFVF_NORMAL ){
			normal = ( D3DXVECTOR3* )( vBuffer + Address );
			Address +=  VectorByteNum;
		}

		//////////
		//	: ポイントサイズ
		if( FVF & D3DFVF_PSIZE ){
			pointSize = ( float* )( vBuffer + Address );
			Address +=  floatByteNum;
		}

		//////////
		//	: ディフューズ
		if( FVF & D3DFVF_DIFFUSE  ){
			diffuse = ( DWORD* )( vBuffer + Address );
			Address +=  DwordByteNum;
		}

		//////////
		//	: スペキュラー
		if( FVF & D3DFVF_SPECULAR  ){
			specular = ( DWORD* )( vBuffer + Address ); 
			Address +=  DwordByteNum;
		}
	}
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//**************************************************************************//
// struct OBB;
//
// 担当者  : なし(山ノ井先生のひな形より)
// 用途    : OBBボリューム境界
//**************************************************************************//
struct OBB{
    D3DXVECTOR3 m_Center;   //中心点の座標
    D3DXVECTOR3 m_Rot[3];   //XYZ の各座標軸の傾きを表す方向ベクトル
    D3DXVECTOR3 m_Size;     //OBB の各座標軸に沿った長さの半分（中心点から面までの長さ）
	OBB():m_Center(g_vZero),m_Size(g_vOne){
		m_Rot[0] = g_vZero;
		m_Rot[1] = g_vZero;
		m_Rot[2] = g_vZero;
	};
	OBB(D3DXVECTOR3 vScale,D3DXVECTOR3 vRot,D3DXVECTOR3 vPos){
		//衝突判定用のOBBの初期化
		m_Center = vPos   ;
		m_Size   = vScale ;
		D3DXMATRIX mRot   ;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationYawPitchRoll(&mRot,vRot.y,vRot.x,vRot.z);
		m_Rot[0] = D3DXVECTOR3(mRot._11,mRot._12,mRot._13);
	    m_Rot[1] = D3DXVECTOR3(mRot._21,mRot._22,mRot._23);
	    m_Rot[2] = D3DXVECTOR3(mRot._31,mRot._32,mRot._33);
	};
	OBB(LPD3DXMESH pMesh){
		//衝突判定用のOBBの初期化
		EarnFromMeshOBB(pMesh,m_Center,m_Size);
		D3DXMATRIX mRot   ;
		D3DXMatrixIdentity(&mRot);
		m_Rot[0] = D3DXVECTOR3(mRot._11,mRot._12,mRot._13);
	    m_Rot[1] = D3DXVECTOR3(mRot._21,mRot._22,mRot._23);
	    m_Rot[2] = D3DXVECTOR3(mRot._31,mRot._32,mRot._33);
	};
	void setRot(D3DXVECTOR3 vRot){
		D3DXMATRIX mRot   ;
		D3DXMatrixIdentity(&mRot);
		m_Rot[0] = D3DXVECTOR3(mRot._11,mRot._12,mRot._13);
	    m_Rot[1] = D3DXVECTOR3(mRot._21,mRot._22,mRot._23);
	    m_Rot[2] = D3DXVECTOR3(mRot._31,mRot._32,mRot._33);
	}

};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//**************************************************************************//
// struct AABB;
//
// 担当者  : 鴫原 徹
// 用途    : AABBボリューム境界
//**************************************************************************//
struct AABB{
    D3DXVECTOR3 m_Center;     //中心点の座標
    D3DXVECTOR3 m_Size;       //OBB の各座標軸に沿った長さの半分（中心点から面までの長さ）
	AABB():m_Center(g_vZero),m_Size(g_vOne){
	};
	AABB(D3DXVECTOR3 vScale,D3DXVECTOR3 vRot,D3DXVECTOR3 vPos){
		//衝突判定用のOBBの初期化
		m_Center = vPos   ;
		m_Size   = vScale ;
	};
	AABB(LPD3DXMESH pMesh){
		EarnFromMeshOBB(pMesh,m_Center,m_Size);
	};
	
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//**************************************************************************//
// struct Sphere;
//
// 担当者  : なし(山ノ井先生のひな形より)
// 用途    : 球データ
//**************************************************************************//
struct Sphere
{
    D3DXVECTOR3 m_Center;
    float m_Radius;
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//**************************************************************************//
// struct RENDERSTATE_PARAM;
//
// 担当者  : 鴫原 徹
// 用途    : レンダータイプとデータのセットを記憶しておきたい!
//
//**************************************************************************//
struct RENDERSTATE_PARAM{
	D3DRENDERSTATETYPE	renderType;
	DWORD				value;
	//RENDERSTATE_PARAM(){};
	//RENDERSTATE_PARAM(D3DRENDERSTATETYPE i_RenderType, DWORD i_dwValue)
	//	:renderType(i_RenderType), value(i_dwValue){};
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 class Stage;
 用途: ゲームをステージ単位で管理するクラス
****************************************************************************/
struct ObjeData{
	int			m_iObjeType		;
	wstring		m_sFilePath		;
	wstring		m_sTexturePath	;
	D3DXVECTOR3	m_vScale		;
	DWORD		m_dwMotionNum	;
	float		m_fTracSpeed	;
	ObjeData(){};
	ObjeData(int iType, wstring wsPath, wstring wsTexPath,
		D3DXVECTOR3 vScale, DWORD dwMotionNum, float fTracSpeed)
	{
		m_iObjeType		= iType			;
		m_sFilePath		= wsPath		;
		m_sTexturePath	= wsTexPath		;
		m_vScale		= vScale		;
		m_dwMotionNum	= dwMotionNum	;
		m_fTracSpeed	= fTracSpeed	;
	}
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/


}//end of namespace structs.
using namespace structs;
}//end of namespace wiz.
