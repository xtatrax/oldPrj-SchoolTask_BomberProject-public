////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：Function.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：グローバルな関数群のインライン定義
//					▼
//	namespace wiz;
//		class DxException : public exception ;
//		template<typename T> inline void SafeDelete(T*& p)    ;
//		template<typename T> inline void SafeDeleteArr(T*& p) ;
//		template<typename T> inline void SafeRelease(T*& p)   ;
//		inline D3DXVECTOR3 MatrixCalculator(D3DXMATRIX& i_m4x4 , D3DXVECTOR3& i_v1x3) ;
//		inline void EarnFromMeshOBB(const LPD3DXBASEMESH i_pMesh,D3DXVECTOR3& o_vPos ,D3DXVECTOR3& o_vSize);
//		class  HitTest ;
//		inline DWORD BYTE4toDWORD(BYTE* byteBuf,BYTE arraySize)    ;
//		inline float BYTE4toFLOATfor(BYTE* byteBuf,BYTE arraySize) ;
//		inline void MeshTransformer(LPD3DXBASEMESH i_pMesh,D3DXMATRIX& i_mMatrix) ;
//		inline float Jump(float fHight,float fVTime,float fNowTime); ;
//		inline float Jump(float fHight,float fVTime,float fOneOldTime,float fNowTime) ;
//		class GetClientSize ;
//
#pragma once

#include "StdAfx.h"

namespace wiz{

extern class Object ;

namespace functions{

#define TL_SQUARE(n)							((n)*(n))
#define TL_PI									(3.1415926535897932384626433832795028841971)
#define TL_RAD(degree)							((degree) * TL_PI / 180.0f)
#define TL_DEG(radian)							((radian) * 180.0 / TL_PI)
#define TL_DISTANCE2D(   PointAX, PointAY,   PointBX, PointBY)						sqrt(TL_SQUARE((PointBX)  - (PointAX))  + TL_SQUARE((PointBY) - (PointAY)))
#define TL_SQDISTANCE2D( PointAX, PointAY,   PointBX, PointBY)						 abs(TL_SQUARE((PointBX)  - (PointAX))  + TL_SQUARE((PointBY) - (PointAY)))
#define TL_DISTANCE3D(   PointAX, PointAY, PointAZ,   PointBX, PointBY, PointBZ)	sqrt(TL_SQUARE((PointBX)  - (PointAX))  + TL_SQUARE((PointBY) - (PointAY))  + TL_SQUARE((PointBZ) - (PointAZ)))
#define TL_SQDISTANCE3D( PointAX, PointAY, PointAZ,   PointBX, PointBY, PointBZ)	 abs(TL_SQUARE((PointBX)  - (PointAX))  + TL_SQUARE((PointBY) - (PointAY))  + TL_SQUARE((PointBZ) - (PointAZ)))

//************************************************//
//class DxException : public exception
//
// 担当者  : なし(山ノ井先生のひな形より)
// 目的    : STL例外から派生したクラス
//************************************************//
class DxException : public exception{
    //メッセージ変数
    wstring m_Message;
public:
/////////////////// ////////////////////
//// 関数名     ：DxException(const wchar_t* m1,const wchar_t* m2)
//// カテゴリ   ：コンストラクタ
//// 用途       ：コンストラクタ
//// 引数       ：  const wchar_t* m1,  //第1メッセージ
////            ：  const wchar_t* m2   //第2メッセージ
//// 戻値       ：メッセージ文字列のポインタ
//// 担当       ：なし(山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
    DxException(const wchar_t* m1,const wchar_t* m2){
        m_Message = m1;
        m_Message += L"\r\n";
        m_Message += m2;
    }
/////////////////// ////////////////////
//// 関数名     ：const wchar_t* what_w() const throw()
//// カテゴリ   ：公開メンバ関数
//// 用途       ：メッセージの取得
//// 引数       ：なし
//// 戻値       ：メッセージ文字列のポインタ
//// 担当       ：なし(山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
    const wchar_t* what_w() const throw(){
        return m_Message.c_str();
    }
};



/////////////////// ////////////////////
//// 関数名     ：inline D3DXVECTOR3 MatrixCalculator(D3DXMATRIX& i_m4x4 , D3DXVECTOR3& i_v1x3)
//// カテゴリ   ：グリーバル関数
//// 用途       ：三次元ベクトルの行列変換を行う
//// 引数       ：  const D3DXMATRIX&  i_m4x4    //  : 計算に使う行列データ
////            ：  const D3DXVECTOR3& i_v1x3    //  : 変換させたい座標データ
//// 戻値       ：変換されたベクトル
//// 担当       ：鴫原 徹
//// 備考       ：敵
////            ：
////
inline D3DXVECTOR3 MatrixCalculator(const D3DXMATRIX& i_m4x4 ,const D3DXVECTOR3& i_v1x3){
	D3DXVECTOR3 res;

	res.x		= (i_m4x4._11 * i_v1x3.x) + (i_m4x4._21 * i_v1x3.y) + (i_m4x4._31 * i_v1x3.z) + (i_m4x4._41 * 1);
	res.y		= (i_m4x4._12 * i_v1x3.x) + (i_m4x4._22 * i_v1x3.y) + (i_m4x4._32 * i_v1x3.z) + (i_m4x4._42 * 1);
	res.z		= (i_m4x4._13 * i_v1x3.x) + (i_m4x4._23 * i_v1x3.y) + (i_m4x4._33 * i_v1x3.z) + (i_m4x4._43 * 1);
	//float alpha = (i_m4x4._14 * i_v1x3.x) + (i_m4x4._24 * i_v1x3.y) + (i_m4x4._34 * i_v1x3.z) + (i_m4x4._44 * 1);
	
	return res;
};

/////////////////// ////////////////////
//// 関数名     ：inline void EarnFromMeshOBB(const LPD3DXBASEMESH i_pMesh,
////            ：      D3DXVECTOR3& o_vPos ,D3DXVECTOR3& o_vSize)
//// カテゴリ   ：グリーバル関数
//// 用途       ：メッシュデータの大きさと中心座標を獲得する
//// 引数       ：  const LPD3DXBASEMESH i_pMesh    //  : 元になるメッシュ
////            ：  D3DXVECTOR3& o_vPos             //  : メッシュの中心点を返すためのポインタ
////            ：  D3DXVECTOR3& o_vSize            //  : メッシュの大きさを返すためのポインタ
//// 担当       ：鴫原 徹
//// 戻値       ：なし(後ろ二つの引数へ返す)
//// 備考       ：Pos  = MaxPosとMinPosの間の点
////            ：Size = MaxPosからMinPosの距離/2
////
inline void EarnFromMeshOBB(const LPD3DXBASEMESH i_pMesh,D3DXVECTOR3& o_vPos ,D3DXVECTOR3& o_vSize){
	//頂点取り出し
	//LPDIRECT3DVERTEXBUFFER9 VertexBuffer;			// 頂点バッファ-
	const DWORD vSize = i_pMesh->GetNumBytesPerVertex();	// 頂点のバイト数
	const DWORD vNum  = i_pMesh->GetNumVertices();		// 頂点個数
	DWORD fvf   = i_pMesh->GetFVF();				// 頂点フォーマット
	//i_pMesh->GetVertexBuffer(&VertexBuffer);		// バッファーの獲得
	PBYTE Vertex;
	i_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&Vertex);
	//BYTE* Vertex = new BYTE[vSize*vNum];			// 計算用頂点バッファ-
	//VertexBuffer->Lock(0,0,(void**)&Vertex,0);		// 頂点ロック

	D3DXVECTOR3 Min = g_vMax;		//	: 最大点バッファ 
	D3DXVECTOR3 Max = g_vMin;		//	: 最小点バッファ
	for(DWORD i = 0 ; i < vNum ; i++){
		FlexibleVertex fvBuf(Vertex+(vSize*i),fvf);			//	: 先頭アドレス + ( 1頂点のサイズ * 頂点番 )
		if(fvBuf.pos->x > Max.x) Max.x = fvBuf.pos->x ;
		if(fvBuf.pos->y > Max.y) Max.y = fvBuf.pos->y ;
		if(fvBuf.pos->z > Max.z) Max.z = fvBuf.pos->z ;
		if(fvBuf.pos->x < Min.x) Min.x = fvBuf.pos->x ;
		if(fvBuf.pos->y < Min.y) Min.y = fvBuf.pos->y ;
		if(fvBuf.pos->z < Min.z) Min.z = fvBuf.pos->z ;
	}
	o_vPos = ( Min + Max ) / 2;
	o_vSize = ( Max - Min ) / 2;
	//VertexBuffer->Unlock();
	//*/

};


//**************************************************************************
// class HitTest;
//
// 担当者  : 鴫原 徹(山ノ井先生のひな形より)
// 用途    : 衝突判定用のユーティリティ
// 　    　　static呼び出しをする
//****************************************************************************/
class HitTest{
/////////////////// ////////////////////
//// 関数名     ：static void ClosestPtPointOBB(const D3DXVECTOR3& point,
////            ：    const OBB& obb, D3DXVECTOR3& retvec)
//// カテゴリ   ：静的非公開メンバ関数
//// 用途       ：pointから見たOBBの最近接点を得る
//// 引数       ：	const D3DXVECTOR3& point,   // 基準点
////            ：  const OBB& obb,             // OBB
////            ：  D3DXVECTOR3& retvec         // 最近接点を返す参照
//// 戻値       ：なし（retvecに最近接点が代入される）
//// 担当       ：なし(山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
	static void ClosestPtPointOBB(const D3DXVECTOR3& point,const OBB& obb, D3DXVECTOR3& retvec){
		D3DXVECTOR3 d = point - obb.m_Center;
		retvec = obb.m_Center;
		float dist;
		for(int i = 0; i < 3; i++)
		{
			dist = D3DXVec3Dot(&d, &obb.m_Rot[i]);
			if(dist > obb.m_Size[i])
			{
				dist = obb.m_Size[i];
			}
			if(dist < -obb.m_Size[i])
			{
				dist = -obb.m_Size[i];
			}
			retvec +=  dist * obb.m_Rot[i];
		}
	}
public:
	HitTest(){}
	~HitTest(){}
/////////////////// ////////////////////
//// 関数名     ：static bool Sphere_Sphere(const Sphere& sp1,const Sphere& sp2)
//// カテゴリ   ：静的公開メンバ関数
//// 用途       ：pointから見たOBBの最近接点を得る
//// 引数       ：  const Sphere& sp1       //球１
////            ：  const Sphere& sp2       //球２
//// 戻値       ：衝突していればtrue
//// 担当       ：なし(山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
	static bool Sphere_Sphere(const Sphere& sp1,const Sphere& sp2){
		D3DXVECTOR3 d = sp1.m_Center - sp2.m_Center;
		float dist2 = D3DXVec3Dot(&d,&d);
		float radiussum = sp1.m_Radius + sp2.m_Radius;
		return dist2 <= radiussum * radiussum;
	}
/////////////////// ////////////////////
//// 関数名     ：static bool AABB_OBB(const AABB& aabb,const OBB& obb)
//// カテゴリ   ：静的公開メンバ関数
//// 用途       ：AABBとOBBとの衝突判定
//// 引数       ：  const AABB& aabb   // AABB
////            ：  const OBB&  obb    // OBB
//// 戻値       ：衝突していればtrue
//// 担当       ：鴫原 徹
//// 備考       ：
////            ：
////
	static bool AABB_OBB(const AABB& aabb,const OBB& obb){
		D3DXVECTOR3 l = aabb.m_Center - obb.m_Center;
		D3DXVECTOR3 s = aabb.m_Size + obb.m_Size;
		if(fabs(l.x) < s.x && fabs(l.y) < s.y && fabs(l.z) < s.z )
			return true ;
		else
			return false ;

	}
/////////////////// ////////////////////
//// 関数名     ：static bool AABB_AABB(const AABB& aabb,const AABB& obb)
//// カテゴリ   ：静的公開メンバ関数
//// 用途       ：AABBとAABBとの衝突判定
//// 引数       ：  const AABB& aabb1   // AABB
////            ：  const AABB& aabb2   // AABB
//// 戻値       ：衝突していればtrue
//// 担当       ：鴫原 徹
//// 備考       ：
////            ：
////
	static bool AABB_AABB(const AABB& aabb1,const AABB& aabb2){
		//if(abs(aabb))
		return false ;
	}
/////////////////// ////////////////////
//// 関数名     ：static bool OBB_Sphere(const Sphere& sp,const OBB& obb,D3DXVECTOR3& retvec)
//// カテゴリ   ：静的公開メンバ関数
//// 用途       ：OBBと球との衝突判定
//// 引数       ：  const Sphere& sp		// 球
////            ：  const OBB&    obb		// OBB
////            ：  D3DXVECTOR3&  retvec	// 最近接点が代入される参照
//// 戻値       ：衝突していればtrue（retvecに最近接点が代入される）
//// 担当       ：なし(山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
	static bool OBB_Sphere(const Sphere& sp,const OBB& obb,D3DXVECTOR3& retvec){
        ClosestPtPointOBB(sp.m_Center,obb,retvec);
        D3DXVECTOR3 v = retvec - sp.m_Center;
        return D3DXVec3Dot(&v,&v) <= sp.m_Radius * sp.m_Radius;
	}
/////////////////// ////////////////////
//// 関数名     ：static bool OBB_OBB(const OBB& obb1,const OBB& obb2)
//// カテゴリ   ：静的公開メンバ関数
//// 用途       ：OBBとOBBとの衝突判定
//// 引数       ：  const OBB& obb1
////            ：  const OBB& obb2
//// 戻値       ：衝突していればtrue
//// 担当       ：なし(山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
	static bool OBB_OBB(const OBB& obb1,const OBB& obb2){
		const float EPSILON = 1.175494e-37f;
		float R[3][3], AbsR[3][3];
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				R[i][j] = D3DXVec3Dot(&obb1.m_Rot[i], &obb2.m_Rot[j]);
				AbsR[i][j] = fabsf(R[i][j]) + EPSILON;
			}
		}
		D3DXVECTOR3 t = obb2.m_Center - obb1.m_Center;
		t = D3DXVECTOR3(D3DXVec3Dot(&t, &obb1.m_Rot[0]),
						D3DXVec3Dot(&t, &obb1.m_Rot[1]),
						D3DXVec3Dot(&t, &obb1.m_Rot[2]));
		//軸L=A0, L=A1, L=A2判定
		float ra, rb;
		for(int i = 0; i < 3; i++){
			ra = obb1.m_Size[i];
			rb = obb2.m_Size[0] * AbsR[i][0] + obb2.m_Size[1] * AbsR[i][1] + obb2.m_Size[2] * AbsR[i][2];
			if(fabsf(t[i]) > ra + rb){
				return false;
			}
		}
		//軸L=B0, L=B1, L=B2判定
		for(int i = 0; i < 3; i++){
			ra = obb1.m_Size[0] * AbsR[0][i] + obb1.m_Size[1] * AbsR[1][i] + obb1.m_Size[2] * AbsR[2][i];
			rb = obb2.m_Size[i];
			if(fabsf(t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i]) > ra + rb){
				return false;
			}
		}
		//軸L=A0 X B0判定
		ra = obb1.m_Size[1] * AbsR[2][0] + obb1.m_Size[2] * AbsR[1][0];
		rb = obb2.m_Size[1] * AbsR[0][2] + obb2.m_Size[2] * AbsR[0][1];
		if(fabsf(t[2] * R[1][0] - t[1] * R[2][0]) > ra + rb){
			return false;
		}
		//軸L=A0 X B1判定
		ra = obb1.m_Size[1] * AbsR[2][1] + obb1.m_Size[2] * AbsR[1][1];
		rb = obb2.m_Size[0] * AbsR[0][2] + obb2.m_Size[2] * AbsR[0][0];
		if(fabsf(t[2] * R[1][1] - t[1] * R[2][1]) > ra + rb){
			return false;
		}
		//軸L=A0 X B2判定
		ra = obb1.m_Size[1] * AbsR[2][2] + obb1.m_Size[2] * AbsR[1][2];
		rb = obb2.m_Size[0] * AbsR[0][1] + obb2.m_Size[1] * AbsR[0][0];
		if(fabsf(t[2] * R[1][2] - t[1] * R[2][2]) > ra + rb){
			return false;
		}
		//軸L=A1 X B0判定
		ra = obb1.m_Size[0] * AbsR[2][0] + obb1.m_Size[2] * AbsR[0][0];
		rb = obb2.m_Size[1] * AbsR[1][2] + obb2.m_Size[2] * AbsR[1][1];
		if(fabsf(t[0] * R[2][0] - t[2] * R[0][0]) > ra + rb){
			return false;
		}
		//軸L=A1 X B1判定
		ra = obb1.m_Size[0] * AbsR[2][1] + obb1.m_Size[2] * AbsR[0][1];
		rb = obb2.m_Size[0] * AbsR[1][2] + obb2.m_Size[2] * AbsR[1][0];
		if(fabsf(t[0] * R[2][1] - t[2] * R[0][1]) > ra + rb){
			return false;
		}
		//軸L=A1 X B2判定
		ra = obb1.m_Size[0] * AbsR[2][2] + obb1.m_Size[2] * AbsR[0][2];
		rb = obb2.m_Size[0] * AbsR[1][1] + obb2.m_Size[1] * AbsR[1][0];
		if(fabsf(t[0] * R[2][2] - t[2] * R[0][2]) > ra + rb){
			return false;
		}
		//軸L=A2 X B0判定
		ra = obb1.m_Size[0] * AbsR[1][0] + obb1.m_Size[1] * AbsR[0][0];
		rb = obb2.m_Size[1] * AbsR[2][2] + obb2.m_Size[2] * AbsR[2][1];
		if(fabsf(t[1] * R[0][0] - t[0] * R[1][0]) > ra + rb){
			return false;
		}
		//軸L=A2 X B1判定
		ra = obb1.m_Size[0] * AbsR[1][1] + obb1.m_Size[1] * AbsR[0][1];
		rb = obb2.m_Size[0] * AbsR[2][2] + obb2.m_Size[2] * AbsR[2][0];
		if(fabsf(t[1] * R[0][1] - t[0] * R[1][1]) > ra + rb){
			return false;
		}
		//軸L=A2 X B2判定
		ra = obb1.m_Size[0] * AbsR[1][2] + obb1.m_Size[1] * AbsR[0][2];
		rb = obb2.m_Size[0] * AbsR[2][1] + obb2.m_Size[1] * AbsR[2][0];
		if(fabsf(t[1] * R[0][2] - t[0] * R[1][2]) > ra + rb){
			return false;
		}
		return true;
	}
/////////////////// ////////////////////
//// 関数名     ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当       ：
//// 備考       ：D3DXIntersect
////            ：第１  |  検査対象のメッシュ
////            ：第２  |  キャラクターの位置(レイの開始点)
////            ：第３  |  キャラクターの移動方向(レイの方向)
////            ：第４  |  あたったかどうか
////            ：第５  |  レイの開始点に最も近い面のインデックスへのポインタ
////            ：第６  |  重心ヒット座標 ∪ へのポインタ
////            ：第７  |  重心ヒット座標 ∨ へのポインタ
////            ：第８  |  衝突地点までの長さ
////            ：第９  |  インフォ??
////            ：第10  |  9の配列数
////
	static bool Intersect(
		LPD3DXBASEMESH i_pMesh,
        CONST D3DXVECTOR3 *i_pRayPos,
        CONST D3DXVECTOR3 *i_pRayDir, 
        DWORD   *o_pFaceIndex,        // index of closest face intersected
        FLOAT   *o_pU,                // Barycentric Hit Coordinates    
        FLOAT   *o_pV,                // Barycentric Hit Coordinates
        FLOAT   *o_pDist,             // Ray-Intersection Parameter Distance
        LPD3DXBUFFER *o_ppAllHits,    // Array of D3DXINTERSECTINFOs for all hits (not just closest) 
        DWORD   *o_pCountOfHits)
	{
		BOOL flg = false;
		D3DXIntersect(i_pMesh,i_pRayPos,i_pRayDir,&flg,o_pFaceIndex,o_pU,o_pV,o_pDist,o_ppAllHits,o_pCountOfHits);
		return flg == TRUE;
	}
/////////////////// ////////////////////
//// 関数名     ：bool GetCollisionJudge(LPD3DXMESH mesh,D3DXVECTOR3 point,D3DXVECTOR3 direction,D3DXMATRIX mat,float distance)
//// カテゴリ   ：
//// 用途       ：凹凸のあるメッシュの当たり判定
//// 引数       ：
//// 戻値       ：
//// 担当       ：拾い物(未検証)
//// 備考       ：
////            ：まだ使わないでください
////
	bool GetCollisionJudge(LPD3DXMESH mesh,D3DXVECTOR3 point,D3DXVECTOR3 direction,D3DXMATRIX mat,float distance){
		float dis;
		BOOL judge;
		D3DXMATRIX matI;
		D3DXMatrixInverse(&matI,NULL,&mat);
		D3DXVECTOR3 pointI,directionI;
		D3DXVec3TransformCoord(&pointI,&point,&matI);
		D3DXVec3TransformCoord(&directionI,&direction,&matI);
		D3DXIntersect(mesh,&pointI,&directionI,&judge,NULL,NULL,NULL,&dis,NULL,NULL);
		if(judge){
			if(dis<distance){
				return true;
			}else{
				return false;
			}
		}else{
			return false;
		}
}

};
/////////////////// ////////////////////
//// 関数名     ：inline DWORD BYTE4toDWORD(BYTE* byteBuf,BYTE arraySize/* MAX = 4*/)
//// カテゴリ   ：グローバル関数
//// 用途       ：
//// 引数       ：  BYTE* byteBuf
////            ：  BYTE  arraySize
//// 戻値       ：
//// 担当       ：
//// 備考       ：
////            ：
////
inline DWORD BYTE4toDWORD(BYTE* byteBuf,BYTE arraySize/* MAX = 4*/){
	union BYTE4toDWORD{
		BYTE  uniByte[4];
		DWORD uniDword;
	}buf;
	for(BYTE i = 0; i < arraySize ;i++){
		buf.uniByte[i] = byteBuf[i];
	};
	return buf.uniDword;
};
/////////////////// ////////////////////
//// 関数名     ：inline float BYTE4toFLOATfor(BYTE* byteBuf,BYTE arraySize/* MAX = 4*/)
//// カテゴリ   ：グローバル関数
//// 用途       ：
//// 引数       ：  BYTE* byteBuf
////            ：  BYTE  arraySize
//// 戻値       ：
//// 担当       ：
//// 備考       ：
////            ：
////
inline float BYTE4toFLOATfor(BYTE* byteBuf,BYTE arraySize/* MAX = 4*/){
	union BYTE4toDWORD{
		BYTE  uniByte[4];
		float uniFloat;
	}buf;
	for(BYTE i = 0; i < arraySize ;i++){
		buf.uniByte[i] = byteBuf[i];
	};
	return buf.uniFloat;
};
/////////////////// ////////////////////
//// 関数名     ：inline void MeshTransformer(LPD3DXBASEMESH io_pMesh,D3DXMATRIX& i_mMatrix)
//// カテゴリ   ：グローバル関数
//// 用途       ：マトリックスを使ってメッシュを変形させる
//// 引数       ：  LPD3DXBASEMESH io_pMesh     // 変形させたいメッシュ
////            ：  D3DXMATRIX&    i_mMatrix    // 計算に使う行列
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：
////            ：
////
inline void MeshTransformer(LPD3DXBASEMESH io_pMesh,D3DXMATRIX& i_mMatrix){
	//頂点取り出し
	LPDIRECT3DVERTEXBUFFER9 VertexBuffer;			// 頂点バッファ-
	const DWORD vSize = io_pMesh->GetNumBytesPerVertex();	// 頂点のバイト数
	const DWORD vNum  = io_pMesh->GetNumVertices();		// 頂点個数
	DWORD fvf   = io_pMesh->GetFVF();				// 頂点フォーマット
	io_pMesh->GetVertexBuffer(&VertexBuffer);		// バッファーの獲得
	BYTE* Vertex = new BYTE[vSize*vNum];			// 計算用頂点バッファ-
	VertexBuffer->Lock(0,0,(void**)&Vertex,0);		// 頂点ロック

	for(DWORD i = 0 ; i < vNum ; i++){
		FlexibleVertex fvBuf(Vertex+(vSize*i),fvf);
		*fvBuf.pos = MatrixCalculator(i_mMatrix , *fvBuf.pos);
		int dummy ;
		dummy = 1;
	}
	
	VertexBuffer->Unlock();
	//*/
	/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
	/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
	/*★*☆*★*☆*★*☆*                                      *☆*★*☆*★*☆*★*/
	/*★*☆*★*☆*★*☆*                                      *☆*★*☆*★*☆*★*/
	/*★*☆*★*☆*★*☆*       デリート しなくていいの？      *☆*★*☆*★*☆*★*/
	/*★*☆*★*☆*★*☆*                                      *☆*★*☆*★*☆*★*/
	/*★*☆*★*☆*★*☆*                                      *☆*★*☆*★*☆*★*/
	/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
	/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
}

/////////////////// ////////////////////
//// 関数名     ：inline float Jump(float fHight,float fVTime,float fNowTime)
//// カテゴリ   ：グローバル関数
//// 用途       ：
//// 引数       ：
////            ：
//// 戻値       ：
//// 担当       ：
//// 備考       ：
////            ：
////
inline float Jump(float fHight,float fVTime,float fNowTime){
	return ( fHight / pow( fVTime, 2 ) ) * pow( fNowTime - fVTime, 2) + fHight ;
}
/////////////////// ////////////////////
//// 関数名     ：inline float Jump(float fHight,float fVTime,float fOneOldTime,float fNowTime)
//// カテゴリ   ：グローバル関数
//// 用途       ：
//// 引数       ：
////            ：
//// 戻値       ：
//// 担当       ：
//// 備考       ：
////            ：
////
inline float Jump(float fHight,float fVTime,float fOneOldTime,float fNowTime){
	return Jump(fHight,fVTime,fNowTime) - Jump(fHight,fVTime,fOneOldTime);
}
//**************************************************************************
// class __GetClientSize;
//
// 担当者  : 
// 用途    : 
// 　    　　
//****************************************************************************/
class __GetClientSize{
	static Rect				m_MainWindowRect;	// ゲーム画面の描画領域
public:
	__GetClientSize(Rect& i_Rect){
		m_MainWindowRect = i_Rect ;
	}
	static Rect getSize(){
		return m_MainWindowRect;
	}
};
inline Rect GetClientSize(){
	return __GetClientSize::getSize();
}

/////////////////// ////////////////////
//// 関数名     ：inline void SetRenderState(const LPDIRECT3DDEVICE9 i_pDevice, RENDERSTATE_PARAM& i_Param)
//// カテゴリ   ：グローバル関数
//// 用途       ：レンダー設定の書き換え
//// 引数       ：    const LPDIRECT3DDEVICE9 i_pDevice      //  デバイス
////            ：    RENDERSTATE_PARAM&      io_Param       //  レンダータイプとデータ
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：io_Param の値を設定
////            ：
////
inline void SetRenderState(const LPDIRECT3DDEVICE9 i_pDevice, RENDERSTATE_PARAM& i_Param) {
	i_pDevice->SetRenderState(i_Param.renderType,i_Param.value);
};
/////////////////// ////////////////////
//// 関数名     ：inline void ChangeRenderState(const LPDIRECT3DDEVICE9 i_pDevice, RENDERSTATE_PARAM& io_Param)
//// カテゴリ   ：グローバル関数
//// 用途       ：レンダー設定の書き換えと保持
//// 引数       ：    const LPDIRECT3DDEVICE9 i_pDevice      //  デバイス
////            ：    RENDERSTATE_PARAM&      io_Param       //  レンダータイプとデータ
//// 戻値       ：なし(io_Paramに値を返す)
//// 担当       ：鴫原 徹
//// 備考       ：io_Param の値を設定
////            ：元の値を io_Paramへ代入して返す
////
inline void ChangeRenderState(const LPDIRECT3DDEVICE9 i_pDevice, RENDERSTATE_PARAM& io_Param){
	DWORD		dwSaveState;
	i_pDevice->GetRenderState(io_Param.renderType,&dwSaveState);
	i_pDevice->SetRenderState(io_Param.renderType,io_Param.value);
	io_Param.value = dwSaveState;
};

/////////////////// ////////////////////
//// 関数名     ：inline void SetRenderStateArray(const LPDIRECT3DDEVICE9 i_pDevice,RENDERSTATE_PARAM* i_pParam)
//// カテゴリ   ：グローバル関数
//// 用途       ：レンダー設定群の書き換え
//// 引数       ：    const LPDIRECT3DDEVICE9 i_pDevice      //  デバイス
////            ：    RENDERSTATE_PARAM*      i_pParam       //  レンダータイプとデータの配列
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：i_pParam の最後には必ず { D3DRS_FORCE_DWORD , NULL } を指定してください
////            ：
inline void SetRenderStateArray(const LPDIRECT3DDEVICE9 i_pDevice,RENDERSTATE_PARAM* i_pParam){
	for(WORD i = 0 ; i_pParam[i].renderType != D3DRS_FORCE_DWORD ; i++){
		SetRenderState(i_pDevice , i_pParam[i]);
	}
};

/////////////////// ////////////////////
//// 関数名     ：inline void ChangeRenderStateArray(const LPDIRECT3DDEVICE9 i_pDevice,RENDERSTATE_PARAM* io_pParam)
//// カテゴリ   ：グローバル関数
//// 用途       ：レンダー設定群の書き換えと保持
//// 引数       ：    const LPDIRECT3DDEVICE9 i_pDevice      //  デバイス
////            ：    RENDERSTATE_PARAM*      io_Param       //  レンダータイプとデータの配列
//// 戻値       ：なし(io_pParamに値を返す)
//// 担当       ：鴫原 徹
//// 備考       ：io_pParam の値を設定
////            ：元の値を io_Paramへ代入して返す
//// 備考       ：i_pParam の最後には必ず { D3DRS_FORCE_DWORD , NULL } を指定してください
////            ：
inline void ChangeRenderStateArray(const LPDIRECT3DDEVICE9 i_pDevice,RENDERSTATE_PARAM* io_pParam){
	for(WORD i = 0 ; io_pParam[i].renderType != D3DRS_FORCE_DWORD ; i++){
		ChangeRenderState(i_pDevice , io_pParam[i]);
	}
};


/////////////////// ////////////////////
//// 関数名     ：inline Object* SearchObjectFromOBJID(vector<Object*>* i_pVec,DWORD i_dwID, vector<Object*>* o_pVec = NULL)
//// カテゴリ   ：グローバル関数
//// 用途       ：OBJIDを元にオブジェクトを探す
//// 引数       ：    vector<Object*>*   i_pVec     //   [in] 対象オブジェクトが格納されているvector<>へのポインタ
////            ：    DWORD              i_dwID     //   [in] 検索対象のID
////            ：    vector<Object*>*   o_pVec	    //  [out] (Option) 発見したオブジェクト一覧 ( 
//// 戻値       ：一番最初に発見したオブジェクトへのポインタ
//// 担当       ：鴫原 徹
//// 備考       ：現在SearchObjectFromTypeIDでも同じようなことはできますが原則SearchObjectFromOBJIDを利用してください
////            ：
////            ：
////            ：
inline Object* SearchObjectFromID(vector<Object*>* i_pVec,DWORD i_dwID, vector<Object*>* o_pVec = NULL){

	vector<Object*>::size_type	sz = i_pVec->size(),
								 i = 0 ;
	for( i = 0; i < sz ; i++ ){
		if( (*i_pVec)[i]->getID() == i_dwID ) {
			if( o_pVec )
				(*o_pVec).push_back( (*i_pVec)[i] );
			else
				return  (*i_pVec)[i] ;
		}
	}
	if( o_pVec && o_pVec->size() ){
		return (*o_pVec)[0] ;
	}else{
		return NULL;
	}
};

/////////////////// ////////////////////
//// 関数名     ：inline Object* SearchObjectFromTypeID(vector<Object*>* i_pVec,DWORD i_dwID, vector<Object*>* o_pVec = NULL)
//// カテゴリ   ：グローバル関数
//// 用途       ：OBJIDを元にオブジェクトを探す
//// 引数       ：    vector<Object*>*   i_pVec     //   [in] 対象オブジェクトが格納されているvector<>へのポインタ
////            ：    DWORD              i_dwID     //   [in] 検索対象のID
////            ：    vector<Object*>*   o_pVec	    //  [out] (Option) 発見したオブジェクト一覧 ( 
//// 戻値       ：一番最初に発見したオブジェクトへのポインタ
//// 担当       ：鴫原 徹
//// 備考       ：
////            ：
////            ：
////            ：
inline Object* SearchObjectFromTypeID(vector<Object*>* i_pVec,const type_info& i_typeinfo, vector<Object*>* o_pVec = NULL){

	vector<Object*>::size_type	sz = i_pVec->size(),
								 i = 0 ;
	const type_info& info = typeid( *( *i_pVec )[ i ] );
	for( i = 0; i < sz ; i++ ){
		if( info == i_typeinfo ) {
			if( o_pVec )
				(*o_pVec).push_back( (*i_pVec)[i] );
			else
				return  (*i_pVec)[i] ;
		}
	}
	if( o_pVec && o_pVec->size() ){
		return (*o_pVec)[0] ;
	}else{
		return NULL;
	}
};


////////////////////////////////////////
////// Non-environment-dependent ///////
////////////////////////////////////////



///////// /////////
//BOOL ArcMove(float *x ,float *y , float Distance, float Degree);
//
//基準点(x,y)からDegree度,Distance距離離れたところに
//ポイント(x,y)を移動させる
//
//引数：
//	float *x：移動させたいx座標
//	float *y：移動させたいy座標
//	float Distance：
//
inline bool ArcMove( D3DXVECTOR3& Pos , float Distance, float Degree){
    Pos.x = Distance  *  cosf((float)TL_RAD(Degree)) ;
    Pos.y = Distance  *  sinf((float)TL_RAD(Degree)) ;

    return true;
}



///////// /////////
//float TurnAngle(float *Angle, float Turn);
//
//Angleを0°～360°に収まるようにTurn度分変更する
//
//引数：
//	float *Angle：	変更すべきデータへのポインタ
//	float Turn：	変更したい角度
//
//返り値：変更後の角度(同じ値が第一引数にも返される)
//
//オーバー防止に一応
//
inline float TurnAngle(float *Angle, float Turn){
    if(*Angle +Turn >= 360){
        *Angle = (*Angle +Turn)  - 360;		//360度を超えた時
        while(*Angle >= 360) *Angle -= 360;	//角度の範囲内に収まるように一周分を引く
    }
    else if(*Angle +Turn < 0){
        *Angle = (*Angle +Turn)+360;		//0度を下回った時
        while(*Angle <= 0) *Angle += 360;	//角度の範囲内に収まるように一周分を足す
    }else{
        *Angle += Turn;//
    }
    return *Angle;
}

///////// /////////
//inline float VectorLength( float X, float Y );
// ベクトルの長さを計算する
//
inline double TwoPointToBassLength( D3DXVECTOR3& i_Vec1, D3DXVECTOR3& i_Vec2 ){
	return TL_SQUARE( i_Vec2.x - i_Vec1.x )  + TL_SQUARE( i_Vec2.y - i_Vec1.y ) ;
}

///////// /////////
//inline float VectorLength( float X, float Y );
// ベクトルの長さを計算する
//
inline double VectorLength( D3DXVECTOR3& i_Vec1 ){
	double ret = ( i_Vec1.x * i_Vec1.x ) + ( i_Vec1.y * i_Vec1.y ) ;
	return pow( ret , 0.5 );
}

///////// /////////
//inline float VectorLength( float X, float Y );
// ベクトルの長さを計算する
//
inline double VectorProduct( D3DXVECTOR3& i_Vec1, D3DXVECTOR3& i_Vec2 ){
	return i_Vec1.x * i_Vec2.x + i_Vec1.y * i_Vec2.y ;
}
///////// /////////
//inline float VectorLength( float X, float Y );
// ベクトルの長さを計算する
//
//
inline double GetCosineTheta( D3DXVECTOR3& i_Vec1, D3DXVECTOR3& i_Vec2 ){
	double buf1 = VectorProduct( i_Vec1 , i_Vec2 ) ;
	double buf2 = VectorLength( i_Vec1 ) ;
	double buf3 = VectorLength( i_Vec2 ) ;
	double ret  = buf1 / ( buf2 * buf3 ) ;
	return ret ;
}
///////// /////////
//inline float VectorLength( float X, float Y );
// ベクトルの長さを計算する
//
//
inline D3DXVECTOR3& TwoPoint2Vector( D3DXVECTOR3& i_Vec1, D3DXVECTOR3& i_Vec2 ){
	return  D3DXVECTOR3( i_Vec2.x - i_Vec1.x , i_Vec2.y - i_Vec1.y , 0 ) ;
}

///////// /////////
//double ThreePoint2Radian(double P1x,double P1y,double P2x,double P2y,double P3x,double P3y);
//
//引数：
//	double P1x：点１のＸ座標値
//	double P1y：点１のＹ座標値
//	double P2x：点２のＸ座標値
//	double P2y：点２のＹ座標値
//	double P3x：点３のＸ座標値
//	double P3y：点３のＹ座標値
//戻り値：∠P1P2P3のラジアン角
//
inline double ThreePoint2Radian(D3DXVECTOR3& i_Vec1, D3DXVECTOR3& i_Vec2, D3DXVECTOR3& i_Vec3){
	//double vAx , vAy , vBx, vBy ;
	//TwoPoint2Vector( vAx , vAy, P2x, P2y, P1x, P1y);
	//TwoPoint2Vector( vBx , vBy, P2x, P2y, P3x, P3y);
	D3DXVECTOR3 vPosA = TwoPoint2Vector( i_Vec2 , i_Vec1 ) ;
	D3DXVECTOR3 vPosB = TwoPoint2Vector( i_Vec2 , i_Vec3 ) ;
	double buf = GetCosineTheta( vPosA , vPosB ) ;
	double ret = acos( buf );
    return ret ;
};

///////// /////////
//float ThreePoint2Radian(float P1x,float P1y,float P2x,float P2y,float P3x,float P3y);
//
//引数：
//	float P1x：点１のＸ座標値
//	float P1y：点１のＹ座標値
//	float P2x：点２のＸ座標値
//	float P2y：点２のＹ座標値
//	float P3x：点３のＸ座標値
//	float P3y：点３のＹ座標値
//戻り値：∠P1P2P3のディグリー角
//
inline float ThreePoint2Degree(D3DXVECTOR3& i_Vec1, D3DXVECTOR3& i_Vec2, D3DXVECTOR3& i_Vec3){
	float ret = (float)TL_DEG(ThreePoint2Radian( i_Vec1, i_Vec2, i_Vec3));
    return ret ;
};


///////// /////////
//float ThreePoint2Radian(float P1x,float P1y,float P2x,float P2y,float P3x,float P3y);
//
//引数：
//	float P1x：点１のＸ座標値
//	float P1y：点１のＹ座標値
//	float P2x：点２のＸ座標値
//	float P2y：点２のＹ座標値
//戻り値：∠P1P2P3のラジアン角
//
inline double TwoPoint2Radian(D3DXVECTOR3& i_Vec1, D3DXVECTOR3& i_Vec2){
	double ret =  ThreePoint2Radian( i_Vec1, i_Vec2, D3DXVECTOR3( i_Vec2.x + 1 , i_Vec2.y , 0 ) );
    return ret ;
};

///////// /////////
//float ThreePoint2Radian(float P1x,float P1y,float P2x,float P2y,float P3x,float P3y);
//
//引数：
//	float P1x：点１のＸ座標値
//	float P1y：点１のＹ座標値
//	float P2x：点２のＸ座標値
//	float P2y：点２のＹ座標値
//戻り値：∠P1P2P3のディグリー角
//
inline float TwoPoint2Degree(D3DXVECTOR3& i_Vec1, D3DXVECTOR3& i_Vec2){

	float ret = 0 ; 
	if( i_Vec1.y >= i_Vec2.y )
		ret = ThreePoint2Degree( i_Vec1, i_Vec2, D3DXVECTOR3( i_Vec2.x + 1 , i_Vec2.y , 0 ) ) ;
	else
	    ret = ( 180 - ThreePoint2Degree( i_Vec1, i_Vec2, D3DXVECTOR3( i_Vec2.x + 1 , i_Vec2.y , 0 ) ) ) + 180;
	return ret;
};




///////// /////////
//inline double TwoPointToBassLength( double P1x,double P1y,double P2x,double P2y );
// ルートを取る前の二点間の距離を計算
//
inline double TwoPointToBassLength( double P1x,double P1y,double P2x,double P2y ){
	return TL_SQUARE( P2x - P1x )  + TL_SQUARE( P2y * P1y ) ;
}

///////// /////////
//inline float VectorLength( float X, float Y );
// ベクトルの長さを計算する
//
inline double VectorLength( double X, double Y ){
	return pow( ( X * X ) + ( Y * Y ), 0.5 );
}

///////// /////////
//inline double VectorProduct(double P1x,double P1y,double P2x,double P2y);
// ベクトルの内積を計算する
//
inline double VectorProduct(double P1x,double P1y,double P2x,double P2y){
	return P1x * P2x + P1y * P2y ;
}
///////// /////////
//inline double GetCosineTheta(double P1x,double P1y,double P2x,double P2y);
// これをacos()すると角度が出る
//
//
inline double GetCosineTheta(double P1x,double P1y,double P2x,double P2y){
	return VectorProduct(P1x,P1y,P2x,P2y) / ( VectorLength(P1x,P1y) * VectorLength(P2x,P2y) ) ;
}
///////// /////////
//inline void TwoPoint2Vector( double &retX, double &retY, double P1x,double P1y,double P2x,double P2y);
// ベクトルの長さを計算する
//
//
inline void TwoPoint2Vector( double &retX, double &retY, double P1x,double P1y,double P2x,double P2y){
	retX = P2x - P1x;
	retY = P2y - P1y;
}
///////// /////////
//inline void TwoPointLength( double &retX, double &retY, double P1x,double P1y,double P2x,double P2y);
// ベクトルの長さを計算する
//
//
inline void TwoPointLength( double &retX, double &retY, double P1x,double P1y,double P2x,double P2y){
	retX = P2x - P1x;
	retY = P2y - P1y;
}

///////// /////////
//double ThreePoint2Radian(double P1x,double P1y,double P2x,double P2y,double P3x,double P3y);
//
//引数：
//	double P1x：点１のＸ座標値
//	double P1y：点１のＹ座標値
//	double P2x：点２のＸ座標値
//	double P2y：点２のＹ座標値
//	double P3x：点３のＸ座標値
//	double P3y：点３のＹ座標値
//戻り値：∠P1P2P3のラジアン角
//
inline double ThreePoint2Radian(double P1x,double P1y,double P2x,double P2y,double P3x,double P3y){
	double vAx , vAy , vBx, vBy ;
	TwoPoint2Vector( vAx , vAy, P2x, P2y, P1x, P1y);
	TwoPoint2Vector( vBx , vBy, P2x, P2y, P3x, P3y);
    return acos(GetCosineTheta(vAx , vAy , vBx, vBy));
};

///////// /////////
//float ThreePoint2Radian(float P1x,float P1y,float P2x,float P2y,float P3x,float P3y);
//
//引数：
//	float P1x：点１のＸ座標値
//	float P1y：点１のＹ座標値
//	float P2x：点２のＸ座標値
//	float P2y：点２のＹ座標値
//	float P3x：点３のＸ座標値
//	float P3y：点３のＹ座標値
//戻り値：∠P1P2P3のディグリー角
//
inline float ThreePoint2Degree(float P1x,float P1y,float P2x,float P2y,float P3x,float P3y){
    return (float)TL_DEG(ThreePoint2Radian( P1x, P1y, P2x, P2y, P3x, P3y));
};


///////// /////////
//float ThreePoint2Radian(float P1x,float P1y,float P2x,float P2y,float P3x,float P3y);
//
//引数：
//	float P1x：点１のＸ座標値
//	float P1y：点１のＹ座標値
//	float P2x：点２のＸ座標値
//	float P2y：点２のＹ座標値
//戻り値：∠P1P2P3のラジアン角
//
inline double TwoPoint2Radian(double P1x,double P1y,double P2x,double P2y){
    return ThreePoint2Radian( P1x, P1y, P2x, P2y, P2x + 1 , P2y );
};

///////// /////////
//float ThreePoint2Radian(float P1x,float P1y,float P2x,float P2y,float P3x,float P3y);
//
//引数：
//	float P1x：点１のＸ座標値
//	float P1y：点１のＹ座標値
//	float P2x：点２のＸ座標値
//	float P2y：点２のＹ座標値
//戻り値：∠P1P2P3のディグリー角
//
inline float TwoPoint2Degree(float P1x,float P1y,float P2x,float P2y){
	if( P1y >= P2y )
	    return ThreePoint2Degree( P1x, P1y, P2x, P2y, P2x - 1 , P2y );
	else
	    return ( 180 - ThreePoint2Degree( P1x, P1y, P2x, P2y, P2x - 1 , P2y ) ) + 180;
};


}//end of namespace functions.
using namespace functions ;
}//end of namespace wiz.
