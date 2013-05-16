////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：Structs.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：多所で利用される構造体郡
//					▼
//	namespace wiz;
//		struct Command			;
//		struct UpdatePacket		;
//		struct RenderPacket		;
//		struct FactoryPacket	;
//		struct Color			;
//		struct FlexibleVertex	;
//		struct OBB				;
//		struct AABB				;
//		struct Sphere			;
//		struct RENDERSTATE_PARAM	;
//		struct MapPartsStatus			;
//
#pragma once

#include "StdAfx.h"

namespace wiz{
class  Object ; 
class  TextureManager ;
struct CONTROLER_STATE;
namespace functions {
extern void EarnFromMeshOBB(const LPD3DXBASEMESH i_pMesh,D3DXVECTOR3& o_vPos ,D3DXVECTOR3& o_vSize);
}
using namespace functions ;
namespace structs{
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 struct MapPartsStatus;
 用途: 
****************************************************************************/
struct MapPartsStatus{
	DWORD			enClassid ;	//	wiz::CLASSIDで指定してください
	D3DXVECTOR3		vScale    ;
	D3DXVECTOR3		vRot      ;
	D3DXVECTOR3		vPos      ;
	D3DCOLORVALUE   Diffuse   ;
	D3DCOLORVALUE   Specular  ;
	D3DCOLORVALUE   Ambient   ;
	bool			bPool     ;

	//	: オプション
	wstring			sTexturePath	;

	wstring			sFilePath		;
	DWORD			dwMotionNum		;
	float			fTracSpeed		;
	//MapPartsStatus(){};
	//MapPartsStatus(DWORD i_dwClassID, D3DXVECTOR3 i_vScale, D3DXVECTOR3 i_vRot, D3DXVECTOR3 i_vPos,
	//	wstring i_wsPath = L"", wstring i_wsTexPath = L"",
	//	DWORD i_dwMotionNum = 0, float i_fTracSpeed = 1.0f)
	//{
	//	enClassid		= i_dwClassID	;
	//	vScale			= i_vScale		;
	//	vRot			= i_vRot		;
	//	vPos			= i_vPos		;
	//	sFilePath		= i_wsPath		;
	//	sTexturePath	= i_wsTexPath	;
	//	vScale			= i_vScale		;
	//	dwMotionNum		= i_dwMotionNum	;
	//	fTracSpeed		= i_fTracSpeed	;
	//}


};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 struct Command;
 用途: シーン内、ステージ内でやり取りされるコマンド
 ＊コマンド内容の定義は、各コンテンツにまかせる
****************************************************************************/
struct Command{
	DWORD m_Command;	
	DWORD m_Param1;
	DWORD m_Param2;
	Command()
		:m_Command(0),m_Param1(0),m_Param2(0)
	{}
	void Clear(){
		m_Command = m_Param1 = m_Param2 = 0;
	}
	~Command(){
		Clear();
	}
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 class Context;
 用途: シーンデータ構造体
 ユーザーデータは派生クラスを作成して使用する
****************************************************************************/
class Context{
	DWORD m_Command;	
	DWORD m_Param1;
	DWORD m_Param2;
	//タイマー。経過秒を計る
	Timer m_Timer;
	//1回のタイムスパン
	FLOAT m_TimeSpan;
	//ゲームトータル時間
	FLOAT m_TotalTime;
public:
/**************************************************************************
 void ElapsedTime();
 用途: タイマーを進める
 戻り値: なし
***************************************************************************/
	void ElapsedTime(){
		if(m_Timer.IsStopped()){
			//タイマーが止まっていたら動かす
			m_Timer.Start();
		}
		else{
			//タイマーを進める
			m_TimeSpan = m_Timer.GetElapsedTime();
			m_TotalTime += m_TimeSpan;
		}
	}
/**************************************************************************
 FLOAT GetTimeSpan();
 用途: タイムスパンを得る。
 戻り値: タイムスパン
***************************************************************************/
	FLOAT GetTimeSpan(){
		return m_TimeSpan;
	}
/**************************************************************************
 FLOAT GetTotalTime();
 用途: トータル時間を得る。
 戻り値: トータル時間
***************************************************************************/
	FLOAT GetTotalTime(){
		return m_TotalTime;
	}
/**************************************************************************
 void StopTimer();
 用途: タイマーをとめる
 戻り値: なし
***************************************************************************/
	void StopTimer(){
		if(!m_Timer.IsStopped()){
			m_Timer.Stop();
		}
	}
/**************************************************************************
 Context();
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
	Context():m_Timer(),
		m_TimeSpan(0.001f),m_TotalTime(0){
		m_Timer.Start();
	}
/**************************************************************************
 virtual ~Context();
 用途: 仮想デストラクタ
 戻り値: なし
***************************************************************************/
	virtual~Context(){}

	void operator = ( const Command other ) {
		m_Command = other.m_Command ;
		m_Param1  = other.m_Param1  ;
		m_Param2  = other.m_Param2  ;	
	};

};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/


/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//**************************************************************************//
// struct UpdatePacket;
//
// 担当者  : 鴫原 徹
// 用途    : アップデート関数郡に流れるデータ
//**************************************************************************//
struct BassPacket{
	LPDIRECT3DDEVICE9		pD3DDevice	;	// デバイス
	vector<Object*>*		pVec		;	// オブジェコンテナ
	TextureManager*			pTxMgr		;	// テクスチャ管理クラス
	TLIB::Tempus2*			pTime		;	// 時間
	Command*				pCommand	;	// コマンド
	BassPacket()
		:pD3DDevice( NULL )
		,pVec( NULL )
		,pTxMgr( NULL )
		,pTime( NULL )
		,pCommand( NULL )
	
	{}

};
//**************************************************************************//
// struct UpdatePacket;
//
// 担当者  : 鴫原 徹
// 用途    : アップデート関数郡に流れるデータ
//**************************************************************************//
struct UpdatePacket : public BassPacket{
	const CONTROLER_STATE*	pCntlState	;
	UpdatePacket()
		:pCntlState( NULL )
	{
	}

};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//**************************************************************************//
// struct RenderPacket;
//
// 担当者  : 鴫原 徹
// 用途    : レンダー関数群に流れるデータ
//**************************************************************************//
struct RenderPacket : public BassPacket{
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//**************************************************************************//
// struct DrawPacket;
//
// 担当者  : 鴫原 徹
// 用途    : ドロー関数群に流れるデータ
//**************************************************************************//
struct DrawPacket : public BassPacket{
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/


/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//**************************************************************************//
// struct FactoryPacket;
//
// 担当者  : 鴫原 徹
// 用途    : ファクトリーに渡すパケットデータ
//**************************************************************************//
struct FactoryPacket{
	//Device
	LPDIRECT3DDEVICE9 pD3DDevice ;
	//ダイアログステージかどうか
	bool m_IsDialog;
	//配置オブジェクトのポインタのベクトル
	vector<Object*>* m_pVec;
	//テクスチャのポインタのベクトル
	TextureManager* m_pTexMgr;
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

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
	D3DXMATRIX	m_mRot;
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
		//m_Size   = vScale ;
		m_Size   = vScale * 0.5f ;
		D3DXMATRIX mRot   ;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationYawPitchRoll(&mRot,vRot.y,vRot.x,vRot.z);
		m_mRot = mRot ;
		m_Rot[0] = D3DXVECTOR3(mRot._11,mRot._12,mRot._13);
	    m_Rot[1] = D3DXVECTOR3(mRot._21,mRot._22,mRot._23);
	    m_Rot[2] = D3DXVECTOR3(mRot._31,mRot._32,mRot._33);
	};
	OBB(D3DXVECTOR3 vScale,D3DXQUATERNION vQt,D3DXVECTOR3 vPos){
		//衝突判定用のOBBの初期化
		m_Center = vPos   ;
		//m_Size   = vScale ;
		m_Size   = vScale * 0.5f ;
		//vQt		*= vQt ; 
		//D3DXQuaternionNormalize(&vQt,&vQt);

		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationQuaternion(&mRot,&vQt);
		m_mRot = mRot ;
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
		m_mRot = mRot ;
		m_Rot[0] = D3DXVECTOR3(mRot._11,mRot._12,mRot._13);
	    m_Rot[1] = D3DXVECTOR3(mRot._21,mRot._22,mRot._23);
	    m_Rot[2] = D3DXVECTOR3(mRot._31,mRot._32,mRot._33);
	}

};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 struct AABB;
 用途: AABBボリューム境界
****************************************************************************/
struct AABB{
    D3DXVECTOR3 m_Min;     //小さいほうの座標
    D3DXVECTOR3 m_Max;     //大きいほうの座標
	AABB(){}
	AABB(D3DXVECTOR3& Min,D3DXVECTOR3& Max)
		:m_Min(Min),m_Max(Max){}
	AABB(D3DXVECTOR3& Center,FLOAT XSize,FLOAT YSize,FLOAT ZSize){
		FLOAT xh = XSize / 2.0f;
		FLOAT yh = YSize / 2.0f;
		FLOAT zh = ZSize / 2.0f;

		m_Min.x = Center.x - xh;
		m_Max.x = Center.x + xh;

		m_Min.y = Center.y - yh;
		m_Max.y = Center.y + yh;

		m_Min.z = Center.z - zh;
		m_Max.z = Center.z + zh;
	}
	void GetCenter(D3DXVECTOR3& Pos){
		Pos.x = (m_Min.x + m_Max.x) / 2.0f;
		Pos.y = (m_Min.y + m_Max.y) / 2.0f;
		Pos.z = (m_Min.z + m_Max.z) / 2.0f;
	}
	void Move(D3DXVECTOR3& MoveVec){
		m_Min += MoveVec;
		m_Max += MoveVec;
	}
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 struct SPHERE;
 用途: 球データ
****************************************************************************/
struct SPHERE
{
    D3DXVECTOR3 m_Center;	//中心点の座標
    float m_Radius;			//半径
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



}//end of namespace structs.
using namespace structs;
}//end of namespace wiz.
