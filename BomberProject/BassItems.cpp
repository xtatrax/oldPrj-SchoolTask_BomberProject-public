////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：BassItems.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包ﾃﾞｰﾀと備考	：ゲームのベースになるアイテム群の宣言
//					▼
//	プリミティブ周辺を山ノ井先生のソースを参考に大改造する! 
//
//	namespace wiz;
//		union Color                :				# DWORD表記カラーを使いやすくしてみた(使いやすいと思うよ多分…)
//		class Camera               : public Object ;		# カメラ
//		class Guide                : public Object ;		# ガイドライン
//		class CommonMesh           ;						# メッシュを扱うときに継承すると便利なクラス
//		class MultiCommonMesh      : public CommonMesh ;	# 似たような動作をする異なる形状のメッシュを作りたい時に継承すると便利なクラス
//		class LoadMeshFromX        : public CommonMesh ;	#
//		class ThinPlate            ;						# 薄い板のようなものを作るときに継承すると便利なクラス
//		class PrimitiveSprite      ;						# 2次元的なUIを作るときに継承すると便利なクラス
//		class PrimitiveBox         : public CommonMesh      ;		# 立方体状の物を作るときに継承すると便利なクラス
//		class PrimitiveMultiBox    : public PrimitiveBox    ;		# 複数の似たような動作をする立方体を作るときに継承すると便利なクラス
//		class PrimitiveSphere      : public CommonMesh      ;		# 球状の物を作るときに継承すると便利なクラス
//		class PrimitiveMultiSphere : public PrimitiveSphere ;		# 複数の似たような動作をする球体を作るときに継承すると便利なクラス
//		class BoxObject            : public PrimitiveBox    , public Object          ;		# 簡単なボックスを作るクラス
//		class SpriteObject         : public Object          , public PrimitiveSprite ;		# 簡単なスプライトを作るクラス
//
//
#include "StdAfx.h"
#include "BassItems.h"

namespace wiz {

namespace baseitems{

/**************************************************************************
 CommonMesh 実体
***************************************************************************/
/**************************************************************************
 ユーティリティ関数（static関数）
****************************************************************************/
/**************************************************************************
 static void PolygonVec2UV(
	float x,	//xの値
	float y,	//yの値
	float z,	//zの値
	float r,	//ポリゴンの半径
	float& u,	//変換するu（テクスチャ上のU座標）
	float& v	//変換するv（テクスチャ上のV座標）
	);
 用途: PolygonのVectorからUとVを作り出す
 戻り値: なし
 float& uとfloat& vに変換後の値を代入
***************************************************************************/
void CommonMesh::PolygonVec2UV(float x,float y,float z,float r,float& u,float& v){
	u = (x + r ) / (2.0f * r);
	v = 1.0f - (y + r ) / (2.0f * r);
}
/**************************************************************************
 static void CommonMesh::BoxVecNomal2UV(
	D3DXVECTOR3 vec,	//頂点
	D3DXVECTOR3 normal,	//法線
	float& u,	//変換するu（テクスチャ上のU座標）
	float& v	//変換するv（テクスチャ上のV座標）
	);
 用途: BoxのVectorと法線からUとVを作り出す
 すべての面に同じテクスチャを展開する場合
 戻り値: なし
 float& uとfloat& vに変換後の値を代入
***************************************************************************/
void CommonMesh::BoxVecNomal2UV(D3DXVECTOR3 vec,D3DXVECTOR3 normal,float& u,float& v){
	if((normal.x < 0 && vec.y > 0 &&  vec.z > 0) 
		|| (normal.x > 0 && vec.y > 0 &&  vec.z < 0)
		|| (normal.z < 0 && vec.y > 0 &&  vec.x < 0)
		|| (normal.z > 0 && vec.y > 0 &&  vec.x > 0)
		|| (normal.y > 0 && vec.x < 0 &&  vec.z > 0)
		|| (normal.y < 0 && vec.x < 0 &&  vec.z < 0)){
			u = 0;
			v = 0;
	}
	else if((normal.x < 0 && vec.y < 0 &&  vec.z > 0) 
		|| (normal.x > 0 && vec.y < 0 &&  vec.z < 0)
		|| (normal.z < 0 && vec.y < 0 &&  vec.x < 0)
		|| (normal.z > 0 && vec.y < 0 &&  vec.x > 0)
		|| (normal.y > 0 && vec.x < 0 &&  vec.z < 0)
		|| (normal.y < 0 && vec.x < 0 &&  vec.z > 0)){
		u = 0;
		v = 1.0f;
	}
	else if((normal.x < 0 && vec.y > 0 &&  vec.z < 0) 
		|| (normal.x > 0 && vec.y > 0 &&  vec.z > 0)
		|| (normal.z < 0 && vec.y > 0 &&  vec.x > 0)
		|| (normal.z > 0 && vec.y > 0 &&  vec.x < 0)
		|| (normal.y > 0 && vec.x > 0 &&  vec.z > 0)
		|| (normal.y < 0 && vec.x > 0 &&  vec.z < 0)){
		u = 1.0f;
		v = 0.0f;
	}
	else{
		u = 1.0f;
		v = 1.0f;
	}
}

/**************************************************************************
 static void CommonMesh::BoxVecNomal2UV_6_1(
	D3DXVECTOR3 vec,	//頂点
	D3DXVECTOR3 normal,	//法線
	float& u,	//変換するu（テクスチャ上のU座標）
	float& v	//変換するv（テクスチャ上のV座標）
	);
 用途: BoxのVectorと法線からUとVを作り出す
 テクスチャが1×6の画像になってる場合
 戻り値: なし
 float& uとfloat& vに変換後の値を代入
***************************************************************************/
void CommonMesh::BoxVecNomal2UV_6_1(D3DXVECTOR3 vec,D3DXVECTOR3 normal,float& u,float& v){
	float u_prim = 1.0f / 6.0f;
	if(normal.z < 0){ //0面
		if(vec.x < 0 && vec.y > 0 && vec.z < 0){//左上
			u = 0.0f;
			v = 0.0f;
		}
		else if(vec.x > 0 && vec.y > 0 && vec.z < 0){//右上
			u = u_prim * 1.0f;
			v = 0.0f;
		}
		else if(vec.x > 0 && vec.y < 0 && vec.z < 0){//右下
			u = u_prim * 1.0f;
			v = 1.0f;
		}
		else{ //左下
			u = 0;
			v = 1.0f;
		}
	}
	if(normal.x > 0){ //1面（右側面）
		if(vec.x > 0 && vec.y > 0 && vec.z < 0){//左上
			u = u_prim * 1.0f;
			v = 0.0f;
		}
		else if(vec.x > 0 && vec.y > 0 && vec.z > 0){//右上
			u = u_prim * 2.0f;
			v = 0.0f;
		}
		else if(vec.x > 0 && vec.y < 0 && vec.z > 0){//右下
			u = u_prim * 2.0f;
			v = 1.0f;
		}
		else{ //左下
			u = u_prim * 1.0f;
			v = 1.0f;
		}
	}
	if(normal.z > 0){ //2面（裏面）
		if(vec.x > 0 && vec.y > 0 && vec.z > 0){//左上
			u = u_prim * 2.0f;
			v = 0.0f;
		}
		else if(vec.x < 0 && vec.y > 0 && vec.z > 0){//右上
			u = u_prim * 3.0f;
			v = 0.0f;
		}
		else if(vec.x < 0 && vec.y < 0 && vec.z > 0){//右下
			u = u_prim * 3.0f;
			v = 1.0f;
		}
		else{ //左下
			u = u_prim * 2.0f;
			v = 1.0f;
		}
	}
	if(normal.x < 0){ //3面（左側面）
		if(vec.x < 0 && vec.y > 0 && vec.z > 0){//左上
			u = u_prim * 3.0f;
			v = 0.0f;
		}
		else if(vec.x < 0 && vec.y > 0 && vec.z < 0){//右上
			u = u_prim * 4.0f;
			v = 0.0f;
		}
		else if(vec.x < 0 && vec.y < 0 && vec.z < 0){//右下
			u = u_prim * 4.0f;
			v = 1.0f;
		}
		else{ //左下
			u = u_prim * 3.0f;
			v = 1.0f;
		}
	}
	if(normal.y > 0){ //4面（上面）
		if(vec.x < 0 && vec.y > 0 && vec.z > 0){//左上
			u = u_prim * 4.0f;
			v = 0.0f;
		}
		else if(vec.x > 0 && vec.y > 0 && vec.z > 0){//右上
			u = u_prim * 5.0f;
			v = 0.0f;
		}
		else if(vec.x > 0 && vec.y > 0 && vec.z < 0){//右下
			u = u_prim * 5.0f;
			v = 1.0f;
		}
		else{ //左下
			u = u_prim * 4.0f;
			v = 1.0f;
		}
	}
	if(normal.y < 0){ //5面（下面）
		if(vec.x < 0 && vec.y < 0 && vec.z < 0){//左上
			u = u_prim * 5.0f;
			v = 0.0f;
		}
		else if(vec.x > 0 && vec.y < 0 && vec.z < 0){//右上
			u = 1.0f; // u_prim * 6.0f;
			v = 0.0f;
		}
		else if(vec.x > 0 && vec.y < 0 && vec.z > 0){//右下
			u = 1.0f; //u_prim * 6.0f;
			v = 1.0f;
		}
		else{ //左下
			u = u_prim * 5.0f;
			v = 1.0f;
		}
	}
}

/**************************************************************************
 static void CommonMesh::SphereVec2UV(
	float x,	//xの値
	float y,	//yの値
	float z,	//zの値
	float r,	//球の半径
	float& u,	//変換するu（テクスチャ上のU座標）
	float& v	//変換するv（テクスチャ上のV座標）
	);
 用途: SphereのVectorからUとVを作り出す
 戻り値: なし
 float& uとfloat& vに変換後の値を代入
***************************************************************************/
void CommonMesh::SphereVec2UV(float x,float y,float z,float r,float& u,float& v){
	float q;
	float q2;
	q = atan2(z,x);
	if(q < 0){
		q += 2.0f * D3DX_PI;
	}
	u = q / (2.0f * D3DX_PI);
	q2 = asin(y / r);
	v = (1.0f - q2 / (D3DX_PI / 2.0f)) / 2.0f;
	if( u > 1.0f){
		u = 1.0f;
	}
	if( v > 1.0f){
		v = 1.0f;
	}
}

/**************************************************************************
 static void CommonMesh::WrapVec2UV(
	float x,	//xの値
	float y,	//yの値
	float z,	//zの値
	float& u,	//変換するu（テクスチャ上のU座標）
	float& v,	//変換するv（テクスチャ上のV座標）
	bool IsYWrap = true		//Y軸でくるむかZ軸でくるむか
	);
 用途: ラッピングすべきメッシュのVectorからUとVを作り出す
 戻り値: なし
 float& uとfloat& vに変換後の値を代入
***************************************************************************/
void CommonMesh::WrapVec2UV(float x,float y,float z,float& u,float& v,bool IsYWrap){
	float q;
	float q2;
	if(IsYWrap){
		q = atan2(z,x);
	}
	else{
		q = atan2(y,x);
	}
	if(q < 0){
		q += 2.0f * D3DX_PI;
	}
	u = q / (2.0f * D3DX_PI);
	D3DXVECTOR3 vec(x,y,z);
	FLOAT r = D3DXVec3Length(&vec);
	if(IsYWrap){
		q2 = asin(y / r);
	}
	else{
		q2 = asin(z / r);
	}
	v = (1.0f - q2 / (D3DX_PI / 2.0f)) / 2.0f;
	if( u > 1.0f){
		u = 1.0f;
	}
	if( v > 1.0f){
		v = 1.0f;
	}
}


/**************************************************************************
 static void CommonMesh::TorusVec2UV(
	float x,	//xの値
	float y,	//yの値
	float z,	//zの値
	float inr,	//トーラスの内径
	float outr,	//トーラスの外径
	float& u,	//変換するu（テクスチャ上のU座標）
	float& v	//変換するv（テクスチャ上のV座標）
	);
 用途: TorusのVectorからUとVを作り出す
 戻り値: なし
 float& uとfloat& vに変換後の値を代入
***************************************************************************/
void CommonMesh::TorusVec2UV(float x,float y,float z,float inr,float outr,float& u,float& v){
	float q;
	float q2;
	q = atan2(y,x);
	if(q < 0){
		q += 2.0f * D3DX_PI;
	}
	u = q / (2.0f * D3DX_PI);
	//原点からの距離を計算
	float outr2 = sqrtf(x * x + y * y);
	q2 = acos(z / inr);
	if(outr2 >= outr){
		//外形より外側
		q2 = (2 *D3DX_PI) -  q2;
	}
	v = q2 / (D3DX_PI * 2.0f);
	if( u > 1.0f){
		u = 1.0f;
	}
	if( v > 1.0f){
		v = 1.0f;
	}
}
/**************************************************************************
	virtual void CommonMesh::ReleaseObj();
 用途: デバイス喪失によるリソースの開放（仮想関数）
 戻り値: なし。
 ＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
void CommonMesh::ReleaseObj(){
    //後始末
    SafeDelete(m_pShadowVolume);
    SafeRelease(m_pMesh);
}


/**************************************************************************
 CommonMesh::CommonMesh();
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
CommonMesh::CommonMesh( wiz::OBJID id ):
	Object( id ),
	m_pShadowVolume(0),
	m_pMesh(0),
	m_bWrapMode(true),
	m_bWireFrame(false),
	m_bShadeModeFlat(false)
{
}
/**************************************************************************
 CommonMesh::~CommonMesh();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
CommonMesh::~CommonMesh(){
	ReleaseObj();
}
/**************************************************************************
void CommonMesh::CreateBox(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	D3DXVECTOR3& size,				//サイズ
	bool bTextureActive = false,		//テクスチャがアクティブかどうか
	int TexturePtn = PtnUV_1_1	//テクスチャが有効な場合のパターン
);
 用途:Boxオブジェクトの構築
 戻り値: なし（例外をthrow）
***************************************************************************/
void CommonMesh::CreateBox(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& size,
   bool bTextureActive,int TexturePtn){
	//もし作成済みのときのためにクリア
	ReleaseObj();
	try{
		//直方体の作成
		//m_Sizeはコンストラクタで設定済み
		if(FAILED(D3DXCreateBox(pD3DDevice, 
						size.x,
						size.y,
						size.z,
						&m_pMesh, 
						NULL))){
			// 初期化失敗
			throw BaseException(
				L"Boxの作成に失敗しました。",
				L"CommonMesh::CreateBox()"
				);
		}
		//テクスチャがある場合
		if(bTextureActive){
			switch(TexturePtn){
				case PtnUV_YWrap:
				case PtnUV_ZWrap:
					//ラッピングする
					m_bWrapMode = true;
				break;
				default:
					//PtnUV_1_1,PtnUV_6_1と同じ
					//ラッピングしない
					m_bWrapMode = false;
				break;
			}
			LPD3DXMESH m_pMesh2 = 0;
			//作成されたメッシュを元に、テクスチャつきのメッシュを作成
			if(FAILED(m_pMesh->CloneMeshFVF(NULL,CommonMeshFVF,pD3DDevice,&m_pMesh2))){
				// 初期化失敗
				throw BaseException(
					L"テクスチャ付のBoxの作成に失敗しました。",
					L"CommonMesh::CreateBox()"
					);
			}
			//もうもとのメッシュはいらないので削除
			SafeRelease(m_pMesh);
			m_pMesh = m_pMesh2;
			m_pMesh2 = 0;
			//テクスチャ上の座標をマッピング
			LPDIRECT3DVERTEXBUFFER9 pVB = 0;
			CommonMeshVertex* pVer = 0;
			m_pMesh->GetVertexBuffer(&pVB);
			pVB->Lock(0,0,(VOID**)&pVer,0);
			DWORD vsize = m_pMesh->GetNumVertices();
			for(DWORD n = 0;n < vsize;n++){ //頂点の数を取得する
				//法線と頂点からuv値を得る
				switch(TexturePtn){
					case PtnUV_1_1:
						BoxVecNomal2UV(pVer[n].vec,pVer[n].normal,pVer[n].tu,pVer[n].tv);
					break;
					case PtnUV_6_1:
						BoxVecNomal2UV_6_1(pVer[n].vec,pVer[n].normal,pVer[n].tu,pVer[n].tv);
					break;
					case PtnUV_YWrap:
						WrapVec2UV(pVer[n].vec.x,pVer[n].vec.y,pVer[n].vec.z,pVer[n].tu,pVer[n].tv,true);
					break;
					case PtnUV_ZWrap:
						WrapVec2UV(pVer[n].vec.x,pVer[n].vec.y,pVer[n].vec.z,pVer[n].tu,pVer[n].tv,false);
					break;
					default:
						//PtnUV_1_1と同じ
						BoxVecNomal2UV(pVer[n].vec,pVer[n].normal,pVer[n].tu,pVer[n].tv);
					break;
				}
			}
			pVB->Unlock();
		}
		//影ボリュームを作成
		m_pShadowVolume = new ShadowVolume(pD3DDevice,m_pMesh);
	}
	catch(...){
		//後始末
		ReleaseObj();
		//再スロー
		throw;
	}
}

/**************************************************************************
void CommonMesh::CreateSphere(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	FLOAT radius,					//半径
	bool bTextureActive = false,		//テクスチャがアクティブかどうか
	UINT Slices = 18,	//主軸の回転スライス数
	UINT Stacks = 18	//主軸に沿ったスライス数
);
 用途:球オブジェクトの構築
 戻り値: なし（例外をthrow）
***************************************************************************/
void CommonMesh::CreateSphere(LPDIRECT3DDEVICE9 pD3DDevice,FLOAT radius,
	bool bTextureActive,UINT Slices,UINT Stacks){
	//もし作成済みのときのためにクリア
	ReleaseObj();
	try{
		if(radius < 0.0f){
            // 初期化失敗
            throw BaseException(
                L"球の半径の指定が範囲外です。",
                L"CommonMesh::CreateSphere()"
                );
		}
        //球の作成
        if(FAILED(D3DXCreateSphere( pD3DDevice, 
                                            radius,
                                            Slices,
                                            Stacks,
                                            &m_pMesh, 
                                            NULL))){
            // 初期化失敗
            throw BaseException(
                L"球の作成に失敗しました。",
                L"CommonMesh::CreateSphere()"
                );
        }
		if(bTextureActive){
			//ラッピングする
			m_bWrapMode = true;
			//テクスチャメッシュ
			LPD3DXMESH pMesh2 = 0;
			//作成されたメッシュを元に、テクスチャつきのメッシュを作成
			if(FAILED(m_pMesh->CloneMeshFVF(NULL,CommonMeshFVF,pD3DDevice,&pMesh2))){
				// 初期化失敗
				throw BaseException(
					L"テクスチャ付の球の作成に失敗しました。",
					L"CommonMesh::CreateSphere()"
					);
			}
			//この段階でm_pMeshはいらないから削除
			SafeRelease(m_pMesh);
			//新しいメッシュを代入
			m_pMesh = pMesh2;
			//テクスチャ上の座標をマッピング
			LPDIRECT3DVERTEXBUFFER9 pVB = 0;
			CommonMeshVertex* pVer = 0;
			m_pMesh->GetVertexBuffer(&pVB);
			pVB->Lock(0,0,(VOID**)&pVer,0);
			for(DWORD n = 0;n < m_pMesh->GetNumVertices();n++){ //頂点の数を取得する
				float u,v;
				SphereVec2UV(pVer[n].vec.x,pVer[n].vec.y,pVer[n].vec.z,radius,u,v);
				pVer[n].tu = u;
				pVer[n].tv = v;
			}
			pVB->Unlock();
		}
		//影ボリュームを作成
		m_pShadowVolume = new ShadowVolume(pD3DDevice,m_pMesh);
	}
	catch(...){
		//後始末
		ReleaseObj();
		//再スロー
		throw;
	}
}

/**************************************************************************
void CommonMesh::CreateTorus(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
    FLOAT InnerRadius,              //内側の半径の大きさ
    FLOAT OuterRadius,              //外側の半径の大きさ
	bool bTextureActive = false,		//テクスチャがアクティブかどうか
	UINT Sides = 18,	//横断面の辺の数。値は 3 以上である必要がある。
	UINT Rings = 18		//トーラスを構成する環の数。値は 3 以上である必要がある。 
);
 用途:トーラスオブジェクトの構築
 戻り値: なし（例外をthrow）
***************************************************************************/
void CommonMesh::CreateTorus(LPDIRECT3DDEVICE9 pD3DDevice,
			FLOAT InnerRadius,FLOAT OuterRadius,bool bTextureActive,
			UINT Sides,UINT Rings){
	//もし作成済みのときのためにクリア
	ReleaseObj();
	try{
		if(InnerRadius < 0.0f ||
			OuterRadius < 0.0f ||
			Sides < 3 ||
			Rings < 3){
            // 初期化失敗
            throw BaseException(
                L"トーラスの外径、内径、サイド、リングの指定のいずれかが範囲外です。",
                L"CommonMesh::CreateTorus()"
                );
		}
        //トーラスの作成
        if(FAILED(D3DXCreateTorus(pD3DDevice, 
                                InnerRadius,
                                OuterRadius,
                                Sides,
                                Rings,
                                &m_pMesh, 
                                NULL))){
            // 初期化失敗
            throw BaseException(
                L"トーラスの作成に失敗しました。",
                L"CommonMesh::CreateTorus()"
                );
        }
		if(bTextureActive){
			//ラッピングする
			m_bWrapMode = true;
			//テクスチャメッシュ
			LPD3DXMESH pMesh2 = 0;
			//作成されたメッシュを元に、テクスチャつきのメッシュを作成
			if(FAILED(m_pMesh->CloneMeshFVF(NULL,CommonMeshFVF,pD3DDevice,&pMesh2))){
				// 初期化失敗
				throw BaseException(
					L"テクスチャ付のトーラスの作成に失敗しました。",
					L"CommonMesh::CreateTorus()"
					);
			}
			//この段階でm_pMeshはいらないから削除
			SafeRelease(m_pMesh);
			//新しいメッシュを代入
			m_pMesh = pMesh2;
			//テクスチャ上の座標をマッピング
			LPDIRECT3DVERTEXBUFFER9 pVB = 0;
			CommonMeshVertex* pVer = 0;
			m_pMesh->GetVertexBuffer(&pVB);
			pVB->Lock(0,0,(VOID**)&pVer,0);
			for(DWORD n = 0;n < m_pMesh->GetNumVertices();n++){ //頂点の数を取得する
				float u,v;
				TorusVec2UV(pVer[n].vec.x,pVer[n].vec.y,pVer[n].vec.z,InnerRadius,OuterRadius,u,v);
				pVer[n].tu = u;
				pVer[n].tv = v;
			}
			pVB->Unlock();
		}
		//影ボリュームを作成
		m_pShadowVolume = new ShadowVolume(pD3DDevice,m_pMesh);
	}
	catch(...){
		//後始末
		ReleaseObj();
		//再スロー
		throw;
	}
}

/**************************************************************************
void CommonMesh::CreateCylinder(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
    FLOAT Radius1,					//z 軸の負の側の面の半径。値は 0.0f 以上である必要がある。 
    FLOAT Radius2,					//z 軸の正の側の面の半径。値は 0.0f 以上である必要がある。
	FLOAT Length,					//z 軸方向の円柱の長さ。
	bool bTextureActive = false,	//テクスチャがアクティブかどうか
	UINT Slices = 18,				//主軸を回転軸としたスライスの数。
	UINT Stacks = 18				//主軸に沿ったスタック数。  
);
 用途:シリンダーオブジェクトの構築
 戻り値: なし（例外をthrow）
***************************************************************************/
void CommonMesh::CreateCylinder(LPDIRECT3DDEVICE9 pD3DDevice,
			FLOAT Radius1,FLOAT Radius2,FLOAT Length,bool bTextureActive,
			UINT Slices,UINT Stacks){
	//もし作成済みのときのためにクリア
	ReleaseObj();
	try{
		if(Radius1 < 0.0f ||
			 Radius2 < 0.0f){
            // 初期化失敗
            throw BaseException(
                L"シリンダーの半径指定のいずれかが範囲外です。",
                L"CommonMesh::CreateCylinder()"
                );
		}
        //シリンダーの作成
        if(FAILED(D3DXCreateCylinder(pD3DDevice, 
                                Radius1,
                                Radius2,
								Length,
                                Slices,
                                Stacks,
                                &m_pMesh, 
                                NULL))){
            // 初期化失敗
            throw BaseException(
                L"シリンダーの作成に失敗しました。",
                L"CommonMesh::CreateCylinder()"
                );
        }
		if(bTextureActive){
			//ラッピングする
			m_bWrapMode = true;
			//テクスチャメッシュ
			LPD3DXMESH pMesh2 = 0;
			//作成されたメッシュを元に、テクスチャつきのメッシュを作成
			if(FAILED(m_pMesh->CloneMeshFVF(NULL,CommonMeshFVF,pD3DDevice,&pMesh2))){
				// 初期化失敗
				throw BaseException(
					L"テクスチャ付のシリンダーの作成に失敗しました。",
					L"CommonMesh::CreateCylinder()"
					);
			}
			//この段階でm_pMeshはいらないから削除
			SafeRelease(m_pMesh);
			//新しいメッシュを代入
			m_pMesh = pMesh2;
			//テクスチャ上の座標をマッピング
			LPDIRECT3DVERTEXBUFFER9 pVB = 0;
			CommonMeshVertex* pVer = 0;
			m_pMesh->GetVertexBuffer(&pVB);
			pVB->Lock(0,0,(VOID**)&pVer,0);
			for(DWORD n = 0;n < m_pMesh->GetNumVertices();n++){ //頂点の数を取得する
				float u,v;
				WrapVec2UV(pVer[n].vec.x,pVer[n].vec.y,pVer[n].vec.z,u,v,false);
				pVer[n].tu = u;
				pVer[n].tv = v;
			}
			pVB->Unlock();
		}
		//影ボリュームを作成
		m_pShadowVolume = new ShadowVolume(pD3DDevice,m_pMesh);
	}
	catch(...){
		//後始末
		ReleaseObj();
		//再スロー
		throw;
	}
}

/**************************************************************************
void CommonMesh::CreatePolygon(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	FLOAT Length,					//各面の長さ。
	UINT Sides,						//ポリゴンの面数。値は 3 以上である必要がある。
	bool bTextureActive = false,	//テクスチャがアクティブかどうか
);
 用途:ポリゴンオブジェクトの構築
 戻り値: なし（例外をthrow）
***************************************************************************/
void CommonMesh::CreatePolygon(LPDIRECT3DDEVICE9 pD3DDevice,
	   FLOAT Length,UINT Sides,bool bTextureActive){
	//もし作成済みのときのためにクリア
	ReleaseObj();
	try{
		if(Sides < 0){
            // 初期化失敗
            throw BaseException(
                L"ポリゴンの面数が範囲外です。",
                L"CommonMesh::CreatePolygon()"
                );
		}
        //ポリゴンの作成
        if(FAILED(D3DXCreatePolygon(pD3DDevice, 
                                Length,
                                Sides,
                                &m_pMesh, 
                                NULL))){
            // 初期化失敗
            throw BaseException(
                L"ポリゴンの作成に失敗しました。",
                L"CommonMesh::CreatePolygon()"
                );
        }
		if(bTextureActive){
			//ラッピングしない
			m_bWrapMode = false;
			//テクスチャメッシュ
			LPD3DXMESH pMesh2 = 0;
			//作成されたメッシュを元に、テクスチャつきのメッシュを作成
			if(FAILED(m_pMesh->CloneMeshFVF(NULL,CommonMeshFVF,pD3DDevice,&pMesh2))){
				// 初期化失敗
				throw BaseException(
					L"テクスチャ付のポリゴンの作成に失敗しました。",
					L"CommonMesh::CreatePolygon()"
					);
			}
			//この段階でm_pMeshはいらないから削除
			SafeRelease(m_pMesh);
			//新しいメッシュを代入
			m_pMesh = pMesh2;
			//テクスチャ上の座標をマッピング
			LPDIRECT3DVERTEXBUFFER9 pVB = 0;
			CommonMeshVertex* pVer = 0;
			m_pMesh->GetVertexBuffer(&pVB);
			pVB->Lock(0,0,(VOID**)&pVer,0);
			//1回目のパスで、ポリゴンの半径を計算する
			FLOAT r = 0;
			for(DWORD n = 0;n < m_pMesh->GetNumVertices();n++){ //頂点の数を取得する
				D3DXVECTOR3 vec(pVer[n].vec.x,pVer[n].vec.y,0);
				FLOAT r2 = D3DXVec3Length(&vec);
				if(r < r2){
					r = r2;
				}
			}
			for(DWORD n = 0;n < m_pMesh->GetNumVertices();n++){ //頂点の数を取得する
				float u,v;
				PolygonVec2UV(pVer[n].vec.x,pVer[n].vec.y,pVer[n].vec.z,r,u,v);
				pVer[n].tu = u;
				pVer[n].tv = v;

			}
			pVB->Unlock();
		}
		//影ボリュームを作成
		m_pShadowVolume = new ShadowVolume(pD3DDevice,m_pMesh);
	}
	catch(...){
		//後始末
		ReleaseObj();
		//再スロー
		throw;
	}
}

/////////////////// ////////////////////
//// 関数名     ：void CommonMesh::Draw( DrawPacket& i_DrawPacket )
//// カテゴリ   ：仮想関数
//// 用途       ：メッシュを描画
//// 引数       ：  
//// 戻値       ：無し
//// 担当者     ： (山ノ井先生のひな形より)
//// 備考       ：なるべくこの関数は使わず DrawCommonMesh 関数を使うようにしてください
////            ：
////
void CommonMesh::Draw(DrawPacket& i_DrawPacket) {
    //無効チェック
    if((!m_pMesh) || (!i_DrawPacket.pD3DDevice)){
        throw BaseException(L"デバイスかメッシュが無効です。",
        L"CommonMesh::Draw()");
    }
    if(m_Material.Diffuse.a < 1.0f){
        //もし、透明度が1.0未満なら
        // アルファ合成の設定
        i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
        i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
        i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    }
    if(m_Material.Specular.r > 0.0f
        || m_Material.Specular.g > 0.0f
        || m_Material.Specular.b > 0.0f)
    {
        //もし、スペキュラーが設定していたら
        // スペキュラー有効の設定
        i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, 1);
    }
    // マテリアルをレンダリングパイプラインに設定
    i_DrawPacket.pD3DDevice->SetMaterial( &m_Material);
    //描画
    m_pMesh->DrawSubset(0);
    if(m_Material.Specular.r > 0.0f
        || m_Material.Specular.g > 0.0f
        || m_Material.Specular.b > 0.0f)
    {
        //もし、スペキュラーが設定していたら
        // スペキュラーを元に戻す
        i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, 0);
    }
    if(m_Material.Diffuse.a < 1.0f){
        //もし、透明度が1.0未満なら
        // アルファ合成を元に戻す
        i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
    }
}


/**************************************************************************
 void CommonMesh::DrawCommonMesh(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
	D3DXMATRIX& Matrix,				//変換行列
	D3DMATERIAL9& Material,			//マティリアル
	LPDIRECT3DTEXTURE9 pTexture = 0			//テクスチャ
 );
 用途: コモンオブジェクトを描画（派生クラスから呼ばれる）
 戻り値: なし。
***************************************************************************/
 void CommonMesh::DrawCommonMesh(LPDIRECT3DDEVICE9 pD3DDevice,D3DXMATRIX& Matrix,
	 D3DMATERIAL9& Material,LPDIRECT3DTEXTURE9 pTexture){
    //無効チェック
    if((!m_pMesh) || (!pD3DDevice)){
		return;
    }
	//テクスチャがある場合
	DWORD wkRap;
	DWORD wkdword;
	if(pTexture){
		//現在のテクスチャステータスを得る
		pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
		//ラッピングするかどうか
		if(m_bWrapMode){
			pD3DDevice->GetRenderState(D3DRS_WRAP0,&wkRap);
			//テクスチャ貼り付けで、0.0と1.0が共存している場合にラッピングを「0」の値にする
			//D3DWRAPCOORD_0 == u方向,D3DWRAPCOORD_1 == v方向
			pD3DDevice->SetRenderState(D3DRS_WRAP0, D3DWRAPCOORD_0 | D3DWRAPCOORD_1 );
		}
		//ステージの設定
		pD3DDevice->SetTexture(0,pTexture);
		//デフィーズ色とテクスチャを掛け合わせる設定
		pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
		pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		pD3DDevice->SetFVF(CommonMeshFVF);
	}
	// マトリックスをレンダリングパイプラインに設定
	pD3DDevice->SetTransform(D3DTS_WORLD, &Matrix);
	if(Material.Diffuse.a < 1.0f){
		//もし、透明度が1.0未満なら
		// アルファ合成の設定
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	}
	if(Material.Specular.r > 0.0f
		|| Material.Specular.g > 0.0f
		|| Material.Specular.b > 0.0f)
	{
		//もし、スペキュラーが設定していたら
		// スペキュラー有効の設定
		pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, 1);
	}
	//マテリアルをレンダリングパイプラインに設定
	pD3DDevice->SetMaterial(&Material);
	//ワイアフレームかどうか
	if(m_bWireFrame){
		pD3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
	}
	//それ以外
	else{
		pD3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID );
	}
	//シェードモード
	if(m_bShadeModeFlat){
		//フラット シェーディング モード
		pD3DDevice->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_FLAT );
	}
	else{
		//グーロー シェーディング モード
		pD3DDevice->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_GOURAUD );
	}

	//描画
	m_pMesh->DrawSubset(0);

	if(Material.Specular.r > 0.0f
		|| Material.Specular.g > 0.0f
		|| Material.Specular.b > 0.0f)
	{
		//もし、スペキュラーが設定していたら
		// スペキュラーを元に戻す
		pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, 0);
	}
	if(Material.Diffuse.a < 1.0f){
		//もし、透明度が1.0未満なら
		// アルファ合成を元に戻す
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
	}
	if(pTexture){
		//もしテクスチャ設定されていたら
		pD3DDevice->SetTexture(0,0);
		if(m_bWrapMode){
			//ラッピングを元に戻す
			pD3DDevice->SetRenderState(D3DRS_WRAP0,wkRap);
		}
		//ステージを元に戻す
		pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	}
}

/**************************************************************************
	void CommonMesh::DrawCommonShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
	D3DXMATRIX& AllMatrix,				//オブジェクトの変換行列
	LPD3DXEFFECT	pEffect,			//エフェクトのポインタ
	D3DXMATRIX& mCameraView,			//カメラのビュー行列
	D3DXMATRIX& mCameraProj			//カメラのプロジェクション行列
	);
 用途: 影ボリュームを描画（仮想関数）派生クラスから呼ばれる
 戻り値: なし。
***************************************************************************/
void CommonMesh::DrawCommonShadowVolume(
	LPDIRECT3DDEVICE9 pD3DDevice,D3DXMATRIX& AllMatrix,
	LPD3DXEFFECT pEffect,D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj){
	if(m_pShadowVolume){
		//オブジェクトのワールド行列をカメラ視線にして登録
		D3DXMATRIX WorldView;
		WorldView =  AllMatrix * mCameraView;
		pEffect->SetMatrix("g_mWorldView",&WorldView);
		//カメラのプロジェクトまで含んだ行列を登録
		WorldView = WorldView * mCameraProj;
		pEffect->SetMatrix("g_mWorldViewProjection",&WorldView);
		//影ボリュームの描画
		m_pShadowVolume->Draw(pD3DDevice,pEffect);
	}
}

/**************************************************************************
 class MultiCommonMesh : public CommonMesh;
 用途: 複数のコモンメッシュクラス
****************************************************************************/
/**************************************************************************
 virtual void MultiCommonMesh::Clear();
 用途:オブジェクトの破棄
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::Clear(){
	//アイテム配列のクリア
	SafeDeletePointerContainer(m_ItemVec);
}
/**************************************************************************
 MultiCommonMesh::MultiCommonMesh(
	bool IsTextureActive = false	//テクスチャを張るときは指定
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
 ＊コンストラクタでは、テクスチャを使用するかしないか指定する
***************************************************************************/
MultiCommonMesh::MultiCommonMesh( wiz::OBJID id , bool IsTextureActive )
:CommonMesh( id ),m_IsTextureActive(IsTextureActive)
{
	//何もしない
}
/**************************************************************************
 virtual MultiCommonMesh::~MultiCommonMesh();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
MultiCommonMesh::~MultiCommonMesh(){
	//後始末
	Clear();
}
/**************************************************************************
 virtual size_t MultiCommonMesh::AddItem(
    D3DXVECTOR3& Scale,               //スケール（拡大縮小の倍率）
    D3DXVECTOR3& Pos,                //最初の位置
	D3DXVECTOR3& Rot,				//回転(ラジアン単位)
    D3DCOLORVALUE& Diffuse,         //ディフューズ色
    D3DCOLORVALUE& Specular,            //スペキュラ色
    D3DCOLORVALUE& Ambient          //アンビエント色
	bool IsShadowActive = false,	//影を描画するかどうか
	LPDIRECT3DTEXTURE9 pTexture = 0			//テクスチャ
    );
 用途: アイテムを追加
 戻り値: 追加したインデックス（失敗時は例外をthrow）
***************************************************************************/
size_t MultiCommonMesh::AddItem(D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot,
		 D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		 bool IsShadowActive,LPDIRECT3DTEXTURE9 pTexture){
	CommonItem* pItem = 0;
	try{
		if(m_IsTextureActive){
			if(!pTexture){
				throw BaseException(L"MultiCommonMeshにテクスチャが必要ですが、指定されてません",
					L"MultiCommonMesh::AddItem()");
			}
		}
		else{
			if(pTexture){
				throw BaseException(L"MultiCommonMeshにテクスチャは不要ですが、指定されています",
					L"MultiCommonMesh::AddItem()");
			}
		}
		pItem = new CommonItem;
		//初期値は有効
		pItem->m_IsActive = true;
		// D3DMATERIAL9構造体を0でクリア
		::ZeroMemory(&pItem->m_Material,sizeof(D3DMATERIAL9));
		pItem->m_Material.Diffuse = Diffuse;
		pItem->m_Material.Specular = Specular;
		pItem->m_Material.Ambient = Ambient;
		pItem->m_BaseScale = Scale;
		pItem->m_BasePos = Pos;
		pItem->m_Pos = D3DXVECTOR3(0,0,0);
		//クオータニオンの初期化
		D3DXQuaternionIdentity(&pItem->m_BaseQt);
		D3DXQuaternionRotationYawPitchRoll(&pItem->m_BaseQt,
			Rot.y,Rot.x,Rot.z);
		D3DXQuaternionIdentity(&pItem->m_Qt);
		//行列の初期化
		D3DXMatrixIdentity(&pItem->m_WorldMatrix);
		//拡大縮小用
		D3DXMATRIX mtScale;
		D3DXMatrixIdentity(&mtScale);
		D3DXMatrixScaling(&mtScale,
			pItem->m_BaseScale.x,pItem->m_BaseScale.y,pItem->m_BaseScale.z);
		//ローカル回転用
		D3DXMATRIX mtRot;
		D3DXMatrixIdentity(&mtRot);
		//ローカル回転
		D3DXMatrixRotationQuaternion(&mtRot,&pItem->m_BaseQt);
		//ローカル移動用
		D3DXMATRIX mtPos;
		D3DXMatrixIdentity(&mtPos);
		D3DXMatrixTranslation(&mtPos,pItem->m_BasePos.x,pItem->m_BasePos.y,pItem->m_BasePos.z);

		//相対回転用
		D3DXMATRIX mtOffsetRot;
		D3DXMatrixIdentity(&mtOffsetRot);
		//相対回転
		D3DXMatrixRotationQuaternion(&mtOffsetRot,&pItem->m_Qt);

		//相対移動用
		D3DXMATRIX mtOffsetPos;
		D3DXMatrixIdentity(&mtOffsetPos);
		//相対移動
		D3DXMatrixTranslation(&mtOffsetPos,pItem->m_Pos.x,pItem->m_Pos.y,pItem->m_Pos.z);
		//すべてミックス行列をワールド行列に設定
		pItem->m_WorldMatrix = mtScale * mtRot  *  mtPos * mtOffsetRot * mtOffsetPos;
		//影を描画するかどうか
		pItem->m_IsShadowActive = IsShadowActive;
		//テクスチャ
		pItem->m_pTexture = pTexture;
		//アイテムの追加
		size_t ret = m_ItemVec.size();
		m_ItemVec.push_back(pItem);
		//追加したインデックスは直前の項目数になる
		return ret;
	}
	catch(...){
		SafeDelete(pItem);
		Clear();
		throw;
	}
}


/**************************************************************************
　size_t MultiCommonMesh::GetActiveItemCount();
 用途: 現在の有効なアイテム数を得る
 戻り値: アイテム数
***************************************************************************/
size_t MultiCommonMesh::GetActiveItemCount(){
	size_t ret = 0;
    vector<CommonItem*>::size_type sz = m_ItemVec.size();
    for(vector<CommonItem*>::size_type i = 0;i < sz;i++){
		if(m_ItemVec[i]->m_IsActive){
			ret++;
		}
	}
	return ret;
}

/**************************************************************************
bool MultiCommonMesh::IsActiveItem(
size_t Index	//取得したいインデックス
);
 用途: 指定したインデックスのアイテムが有効かどうかを調べる
 戻り値: 有効ならTRUE、無効ならFALSE、インデックスが範囲以外なら例外
***************************************************************************/
bool MultiCommonMesh::IsActiveItem(size_t Index){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		return m_ItemVec[Index]->m_IsActive;
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::IsActiveItem()");
	}
	return false;
}

/**************************************************************************
void MultiCommonMesh::SetActiveItem(
size_t Index,	//セットしたいインデックス
bool val		//したいしたい値（trueかfalse）
);
 用途: 指定したインデックスのアイテムが有効かどうかを設定する
 戻り値: なし、インデックスが範囲以外なら例外
***************************************************************************/
void MultiCommonMesh::SetActiveItem(size_t Index,bool val){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_IsActive = val;
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::SetActiveItem()");
	}
}
/**************************************************************************
 void MultiCommonMesh::CopyItem(
	 CommonItem* Dest,	//コピー先
	 size_t Index		//コピー元のアイテムのインデックス
 );
 用途:アイテムのコピー
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::CopyItem(CommonItem* Dest,size_t Index){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz && Dest){
		//コピー
		*Dest = *m_ItemVec[Index];
	}
	else{
		throw BaseException(L"インデックスが範囲外かコピー先が不定です。",
			L"MultiCommonMesh::CopyItem()");
	}
}

/**************************************************************************
 void MultiCommonMesh::GetItemMaterial(
	size_t Index,	//取得するインデックス
	D3DMATERIAL9& Material	//現在のマテリアル
  );
 用途: マテリアルを取得する
 戻り値: なし（MaterialにIndexのマテリアルを返す）
***************************************************************************/
void MultiCommonMesh::GetItemMaterial(size_t Index,D3DMATERIAL9& Material){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		Material = m_ItemVec[Index]->m_Material;
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::GetItemMaterial()");
	}
}

/**************************************************************************
 void MultiCommonMesh::SetItemMaterial(
	size_t Index,	//設定するインデックス
	D3DMATERIAL9& Material	//設定するマテリアル
  );
 用途: マテリアルを設定する
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::SetItemMaterial(size_t Index,D3DMATERIAL9& Material){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_Material = Material;
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::SetItemMaterial()");
	}
}


/**************************************************************************
bool MultiCommonMesh::IsTextureActive();
 用途: テクスチャが有効かどうかを調べる
 戻り値: 有効ならTRUE、無効ならFALSE
 ＊各インデックスのテクスチャを変更する場合は、先に有効かどうか調査すること
***************************************************************************/
bool MultiCommonMesh::IsTextureActive(){
	return m_IsTextureActive;
}
/**************************************************************************
 LPDIRECT3DTEXTURE9 MultiCommonMesh::GetItemTexture(
	size_t Index	//取得するインデックス
  );
 用途: テクスチャを取得する
 戻り値: 現在のテクスチャ（ない場合は0が返る）
***************************************************************************/
LPDIRECT3DTEXTURE9 MultiCommonMesh::GetItemTexture(size_t Index){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		return m_ItemVec[Index]->m_pTexture;
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::GetItemTexture()");
	}
}
/**************************************************************************
 void MultiCommonMesh::SetItemTexture(
	size_t Index,	//設定するインデックス
	LPDIRECT3DTEXTURE9 pTexture	//設定するテクスチャ
  );
 用途: テクスチャを設定する
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::SetItemTexture(size_t Index,LPDIRECT3DTEXTURE9 pTexture){
	if(m_IsTextureActive){
		//テクスチャが有効なら0は設定できない
		if(!pTexture){
			throw BaseException(L"このオブジェクトはテクスチャが必要です。",
				L"MultiCommonMesh::SetItemTexture()");
		}
	}
	else{
		//テクスチャが無効なら0以外は設定できない
		if(pTexture){
			throw BaseException(L"このオブジェクトはテクスチャを設定できません。",
				L"MultiCommonMesh::SetItemTexture()");
		}
	}

    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_pTexture = pTexture;
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::SetItemTexture()");
	}
}

/**************************************************************************
bool MultiCommonMesh::IsShadowActiveItem(
size_t Index	//取得したいインデックス
);
 用途: 指定したインデックスの影が有効かどうかを調べる
 戻り値: 有効ならTRUE、無効ならFALSE、インデックスが範囲以外なら例外
***************************************************************************/
bool MultiCommonMesh::IsShadowActiveItem(size_t Index){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		return m_ItemVec[Index]->m_IsShadowActive;
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::IsShadowActiveItem()");
	}
}

/**************************************************************************
void MultiCommonMesh::SetShadowActiveItem(
size_t Index,	//セットしたいインデックス
bool val		//したいしたい値（trueかfalse）
);
 用途: 指定したインデックスの影が有効かどうかを設定する
 戻り値: なし、インデックスが範囲以外なら例外
***************************************************************************/
void MultiCommonMesh::SetShadowActiveItem(size_t Index,bool val){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_IsShadowActive = val;
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::SetShadowActiveItem()");
	}
}


/**************************************************************************
 void MultiCommonMesh::GetItemWorldPos(
	size_t Index,	//取得するインデックス
	D3DXVECTOR3& Pos	//現在のワールド位置
  );
 用途: ワールド位置を取得する
 戻り値: なし（PosにIndexのワールド位置を返す）
***************************************************************************/
void MultiCommonMesh::GetItemWorldPos(size_t Index,D3DXVECTOR3& Pos){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		Pos = m_ItemVec[Index]->m_BasePos
			+ m_ItemVec[Index]->m_Pos;
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::GetItemWorldPos()");
	}
}

/**************************************************************************
 void MultiCommonMesh::GetItemWorldRot(
	size_t Index,	//取得するインデックス
	D3DXVECTOR3& Rot	//現在のワールド回転
  );
 用途: ワールド回転を取得する
 戻り値: なし（RotにIndexのワールド回転を返す）
***************************************************************************/
void MultiCommonMesh::GetItemWorldRot(size_t Index,D3DXVECTOR3& Rot){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		//回転
		D3DXQUATERNION Qt = m_ItemVec[Index]->m_Qt * m_ItemVec[Index]->m_BaseQt;
		//正規化
		D3DXQuaternionNormalize(&Qt,&Qt);
		//QtからRotに変換
		Math::QtToRot(Qt,Rot);

	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::GetItemWorldRot()");
	}
}

/**************************************************************************
 void MultiCommonMesh::GetItemWorldQt(
	size_t Index,	//取得するインデックス
	D3DXQUATERNION& Qt	//現在のワールド回転
  );
 用途: ワールド回転を取得する
 戻り値: なし（QtにIndexのワールド回転を返す）
***************************************************************************/
void MultiCommonMesh::GetItemWorldQt(size_t Index,D3DXQUATERNION& Qt){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		//回転
		Qt = m_ItemVec[Index]->m_Qt * m_ItemVec[Index]->m_BaseQt;
		//正規化
		D3DXQuaternionNormalize(&Qt,&Qt);

	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::GetItemWorldQt()");
	}
}

/**************************************************************************
 void MultiCommonMesh::GetItemWorldScale(
	size_t Index,	//取得するインデックス
	D3DXVECTOR3& Scale	//現在のワールドスケール
  );
 用途: ワールドスケールを取得する
 ＊この関数はGetItemBaseScale関数と同じ
 戻り値: なし（ScaleにIndexのワールド回転を返す）
***************************************************************************/
void MultiCommonMesh::GetItemWorldScale(size_t Index,D3DXVECTOR3& Scale){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		//スケーリングはBaseのみ存在するので、Baseの値を返す
		Scale = m_ItemVec[Index]->m_BaseScale;
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::GetItemWorldScale()");
	}
}

/**************************************************************************
 void MultiCommonMesh::GetItemWorld(
	size_t Index,	//取得するインデックス
	D3DXVECTOR3& Scale,	//現在のワールドスケール
	D3DXVECTOR3& Pos,	//現在のワールド位置
	D3DXVECTOR3& Rot,	//現在のワールド回転（オイラー各）
	D3DXQUATERNION& Qt	//現在のワールド回転（クオータニオン）
  );
 用途: すべてのワールド値を取得する
 戻り値: なし（参照にIndexのワールド値を返す）
***************************************************************************/
void MultiCommonMesh::GetItemWorld(size_t Index,
	D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot,D3DXQUATERNION& Qt){
	//指定の配置オブジェクトへの適用
	size_t sz = m_ItemVec.size();
	if(Index < sz){
		//スケーリングはBaseのみ存在するので、Baseの値を返す
		Scale = m_ItemVec[Index]->m_BaseScale;
		//位置
		Pos = m_ItemVec[Index]->m_BasePos
			+ m_ItemVec[Index]->m_Pos;
		//回転
		Qt = m_ItemVec[Index]->m_Qt * m_ItemVec[Index]->m_BaseQt;
		//正規化
		D3DXQuaternionNormalize(&Qt,&Qt);
		//QtからRotに変換
		Math::QtToRot(Qt,Rot);
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::GetItemWorld()");
	}
}

/**************************************************************************
 void MultiCommonMesh::GetItemWorldMatrix(
	size_t Index,_	//取得するインデックス
	D3DXMATRIX& mtWorld	//取得する行列
 );
 用途:ワールド変換を取得する
 戻り値: なし。mtWorldに変換行列をセットする
***************************************************************************/
void MultiCommonMesh::GetItemWorldMatrix(size_t Index,D3DXMATRIX& mtWorld){
	//指定の配置オブジェクトへの適用
	size_t sz = m_ItemVec.size();
	if(Index < sz){
		mtWorld = m_ItemVec[Index]->m_WorldMatrix;
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::GetItemWorldMatrix()");
	}
}
/**************************************************************************
 void MultiCommonMesh::CalcWorldMatrix();
 用途:すべてのアイテムのワールド変換を計算する
 戻り値: なし。現在の変換をもとにワールド行列を計算する
***************************************************************************/
void MultiCommonMesh::CalcWorldMatrix(){
    //配置オブジェクトの行列の設定
    vector<CommonItem*>::size_type sz = m_ItemVec.size();
    for(vector<CommonItem*>::size_type i = 0;i < sz;i++){
		//非アクティブなら計算しない
		if(!m_ItemVec[i]->m_IsActive){
			continue;
		}
		//拡大縮小用
		D3DXMATRIX mtScale;
		D3DXMatrixIdentity(&mtScale);
		D3DXMatrixScaling(&mtScale,
			m_ItemVec[i]->m_BaseScale.x,m_ItemVec[i]->m_BaseScale.y,m_ItemVec[i]->m_BaseScale.z);
		//ローカル回転用
		D3DXMATRIX mtRot;
		D3DXMatrixIdentity(&mtRot);
		//ローカル回転
		D3DXMatrixRotationQuaternion(&mtRot,&m_ItemVec[i]->m_BaseQt);
		//ローカル移動用
		D3DXMATRIX mtPos;
		D3DXMatrixIdentity(&mtPos);
		D3DXMatrixTranslation(&mtPos,m_ItemVec[i]->m_BasePos.x,m_ItemVec[i]->m_BasePos.y,m_ItemVec[i]->m_BasePos.z);

		//相対回転用
		D3DXMATRIX mtOffsetRot;
		D3DXMatrixIdentity(&mtOffsetRot);
		//相対回転
		D3DXMatrixRotationQuaternion(&mtOffsetRot,&m_ItemVec[i]->m_Qt);

		//相対移動用
		D3DXMATRIX mtOffsetPos;
		D3DXMatrixIdentity(&mtOffsetPos);
		//相対移動
		D3DXMatrixTranslation(&mtOffsetPos,m_ItemVec[i]->m_Pos.x,m_ItemVec[i]->m_Pos.y,m_ItemVec[i]->m_Pos.z);

		//すべてミックス行列をワールド行列に設定
		D3DXMatrixIdentity(&m_ItemVec[i]->m_WorldMatrix);
		m_ItemVec[i]->m_WorldMatrix = mtScale * mtRot  *  mtPos * mtOffsetRot * mtOffsetPos;
    }
}


/**************************************************************************
 void MultiCommonMesh::GetItemLocalPos(
	size_t Index,	//取得するインデックス
	D3DXVECTOR3& Pos	//現在の相対位置
  );
 用途: 相対位置を取得する
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::GetItemLocalPos(size_t Index,D3DXVECTOR3& Pos){
	//指定の配置オブジェクトへの適用
	size_t sz = m_ItemVec.size();
	if(Index < sz){
		//位置
		Pos = m_ItemVec[Index]->m_Pos;
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::GetItemLocalPos()");
	}
}

/**************************************************************************
 void MultiCommonMesh::GetItemLocalRot(
	size_t Index,	//取得するインデックス
	D3DXVECTOR3& Rot	//現在の回転
  );
 用途: 相対回転を取得する
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::GetItemLocalRot(size_t Index,D3DXVECTOR3& Rot){
	//指定の配置オブジェクトへの適用
	size_t sz = m_ItemVec.size();
	if(Index < sz){
		//回転
		D3DXQUATERNION Qt = m_ItemVec[Index]->m_Qt;
		//正規化
		D3DXQuaternionNormalize(&Qt,&Qt);
		//QtからRotに変換
		Math::QtToRot(Qt,Rot);
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::GetItemLocalRot()");
	}
}

/**************************************************************************
 void MultiCommonMesh::GetItemLocalQt(
	size_t Index,	//取得するインデックス
	D3DXQUATERNION& Qt	//現在の相対回転
  );
 用途: 相対回転を取得する（クオータニオン版）
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::GetItemLocalQt(size_t Index,D3DXQUATERNION& Qt){
	//指定の配置オブジェクトへの適用
	size_t sz = m_ItemVec.size();
	if(Index < sz){
		//回転
		Qt = m_ItemVec[Index]->m_Qt;
		//正規化
		D3DXQuaternionNormalize(&Qt,&Qt);
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::GetItemLocalQt()");
	}
}

/**************************************************************************
 void MultiCommonMesh::GetItemLocalPosQt(
	size_t Index,	//取得するインデックス
	D3DXVECTOR3& Pos,	//現在の相対位置
	D3DXQUATERNION& Qt	//現在の相対回転
  );
 用途: 相対値を取得する(クオータニオン版)
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::GetItemLocalPosQt(size_t Index,
		D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		Pos = m_ItemVec[Index]->m_Pos;
		Qt = m_ItemVec[Index]->m_Qt;
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::GetItemLocalPosQt()");
	}
}

/**************************************************************************
 void MultiCommonMesh::GetItemLocalPosRot(
	size_t Index,	//取得するインデックス
	D3DXVECTOR3& Pos,	//現在の相対位置
	D3DXVECTOR3& Rot	//現在の回転
  );
 用途: 相対値を取得する
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::GetItemLocalPosRot(size_t Index,
	 D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		Pos = m_ItemVec[Index]->m_Pos;
		//回転
		D3DXQUATERNION Qt = m_ItemVec[Index]->m_Qt;
		//正規化
		D3DXQuaternionNormalize(&Qt,&Qt);
		//QtからRotに変換
		Math::QtToRot(Qt,Rot);
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::GetItemLocalPosRot()");
	}
}

/**************************************************************************
 void MultiCommonMesh::SetItemLocalPosQt(
	size_t Index,	//インデックス
	D3DXVECTOR3& Pos,	//相対位置
	D3DXQUATERNION& Qt	//相対回転
  );
 用途: 相対値を設定する(クオータニオン版)
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::SetItemLocalPosQt(size_t Index,
	D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
	//指定の配置オブジェクトへの適用
	size_t sz = m_ItemVec.size();
	if(Index < sz){
		//位置
		m_ItemVec[Index]->m_Pos = Pos;
		//回転
		m_ItemVec[Index]->m_Qt = Qt;
		//正規化
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_Qt,&m_ItemVec[Index]->m_Qt);
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::SetItemLocalPosQ()");
	}
}
/**************************************************************************
 void MultiCommonMesh::SetItemLocalPosRot(
	size_t Index,	//インデックス
	D3DXVECTOR3& Pos,	//相対位置
	D3DXVECTOR3& Rot	//回転
  );
 用途: 相対値を設定する
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::SetItemLocalPosRot(size_t Index,
	D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
	//指定の配置オブジェクトへの適用
	size_t sz = m_ItemVec.size();
	if(Index < sz){
		//位置
		m_ItemVec[Index]->m_Pos = Pos;
		//回転
		D3DXQuaternionIdentity(&m_ItemVec[Index]->m_Qt);
		D3DXQuaternionRotationYawPitchRoll(&m_ItemVec[Index]->m_Qt,
			Rot.y,Rot.x,Rot.z);
		//正規化
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_Qt,&m_ItemVec[Index]->m_Qt);
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::SetItemLocalPosQ()");
	}
}

/**************************************************************************
 void MultiCommonMesh::MoveToPosRot(
	D3DXVECTOR3& Pos,	//動かす相対位置
	D3DXVECTOR3& Rot	//動かす回転
  );
 用途: 相対値を移動し回転する
 *すべてのオブジェクトに適用される
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::MoveToPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
	D3DXQUATERNION Qt;
	D3DXQuaternionIdentity(&Qt);
	D3DXQuaternionRotationYawPitchRoll(&Qt,
		Rot.y,Rot.x,Rot.z);
    //配置オブジェクトへの適用
    vector<CommonItem*>::size_type sz = m_ItemVec.size();
    for(vector<CommonItem*>::size_type i = 0;i < sz;i++){
		m_ItemVec[i]->m_Pos += Pos;
		m_ItemVec[i]->m_Qt *= Qt;
		//クオータニオンを正規化
		D3DXQuaternionNormalize(&m_ItemVec[i]->m_Qt,&m_ItemVec[i]->m_Qt);
	}
}


/**************************************************************************
 void MultiCommonMesh::MoveToPosQt(
	D3DXVECTOR3& Pos,	//動かす相対位置
	D3DXQUATERNION& Qt	//動かす回転
  );
 用途: 相対値を移動し回転する(クオータニオン版)
 *すべてのオブジェクトに適用される
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::MoveToPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
    //配置オブジェクトへの適用
    vector<CommonItem*>::size_type sz = m_ItemVec.size();
    for(vector<CommonItem*>::size_type i = 0;i < sz;i++){
		m_ItemVec[i]->m_Pos += Pos;
		m_ItemVec[i]->m_Qt *= Qt;
		//クオータニオンを正規化
		D3DXQuaternionNormalize(&m_ItemVec[i]->m_Qt,&m_ItemVec[i]->m_Qt);
	}
}



/**************************************************************************
 void MultiCommonMesh::MoveToItemPosRot(
	size_t Index,	//変化させるインデックス
	D3DXVECTOR3& Pos,	//新しい相対位置
	D3DXVECTOR3& Rot	//新しい回転
  );
 用途: 指定のメンバの相対値を移動し回転する
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::MoveToItemPosRot(size_t Index,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_Pos += Pos;
		D3DXQUATERNION Qt;
		D3DXQuaternionIdentity(&Qt);
		D3DXQuaternionRotationYawPitchRoll(&Qt,
			Rot.y,Rot.x,Rot.z);
		m_ItemVec[Index]->m_Qt *= Qt;
		//クオータニオンを正規化
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_Qt,&m_ItemVec[Index]->m_Qt);
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::MoveToItemPosRot()");
	}
}


/**************************************************************************
 void MultiCommonMesh::MoveToItemPosQt(
	size_t Index,	//変化させるインデックス
	D3DXVECTOR3& Pos,	//新しい相対位置
	D3DXQUATERNION& Qt	//動かす回転
  );
 用途: 指定のメンバの相対値を移動し回転する(クオータニオン版)
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::MoveToItemPosQt(size_t Index,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_Pos += Pos;
		m_ItemVec[Index]->m_Qt *= Qt;
		//クオータニオンを正規化
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_Qt,&m_ItemVec[Index]->m_Qt);
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::MoveToItemPosQt()");
	}
}


/**************************************************************************
 void MultiCommonMesh::MoveAtPosRot(
	D3DXVECTOR3& Pos,	//新しい相対位置
	D3DXVECTOR3& Rot	//新しい回転
  );
 用途: 相対置をセットする
 *すべてのオブジェクトに適用される
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::MoveAtPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
    //配置オブジェクトへの適用
    vector<CommonItem*>::size_type sz = m_ItemVec.size();
    for(vector<CommonItem*>::size_type i = 0;i < sz;i++){
		m_ItemVec[i]->m_Pos = Pos;
		D3DXQuaternionIdentity(&m_ItemVec[i]->m_Qt);
		D3DXQuaternionRotationYawPitchRoll(&m_ItemVec[i]->m_Qt,
			Rot.y,Rot.x,Rot.z);
		//クオータニオンを正規化
		D3DXQuaternionNormalize(&m_ItemVec[i]->m_Qt,&m_ItemVec[i]->m_Qt);
	}
}

/**************************************************************************
 void MultiCommonMesh::MoveAtPosQt(
	D3DXVECTOR3& Pos,	//新しい相対位置
	D3DXQUATERNION& Qt	//新しい回転
  );
 用途: 相対置をセットする(クオータニオン版)
 *すべてのオブジェクトに適用される
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::MoveAtPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
    //配置オブジェクトへの適用
    vector<CommonItem*>::size_type sz = m_ItemVec.size();
    for(vector<CommonItem*>::size_type i = 0;i < sz;i++){
		m_ItemVec[i]->m_Pos = Pos;
		m_ItemVec[i]->m_Qt = Qt;
		//クオータニオンを正規化
		D3DXQuaternionNormalize(&m_ItemVec[i]->m_Qt,&m_ItemVec[i]->m_Qt);
	}
}

/**************************************************************************
 void MultiCommonMesh::MoveAtItemPosRot(
	size_t Index,	//変化させるインデックス
	D3DXVECTOR3& Pos,	//新しい相対位置
	D3DXVECTOR3& Rot	//新しい回転
  );
 用途: 指定のメンバの相対置をセットする
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::MoveAtItemPosRot(size_t Index,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_Pos = Pos;
		D3DXQuaternionIdentity(&m_ItemVec[Index]->m_Qt);
		D3DXQuaternionRotationYawPitchRoll(&m_ItemVec[Index]->m_Qt,
			Rot.y,Rot.x,Rot.z);
		//クオータニオンを正規化
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_Qt,&m_ItemVec[Index]->m_Qt);
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::MoveAtItemPosRot()");
	}
}

/**************************************************************************
 void MultiCommonMesh::MoveAtItemPosQt(
	size_t Index,	//変化させるインデックス
	D3DXVECTOR3& Pos,	//新しい相対位置
	D3DXQUATERNION& Qt	//新しい回転
  );
 用途: 指定のメンバの相対置をセットする(クオータニオン版)
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::MoveAtItemPosQt(size_t Index,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_Pos = Pos;
		m_ItemVec[Index]->m_Qt = Qt;
		//クオータニオンを正規化
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_Qt,&m_ItemVec[Index]->m_Qt);
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::MoveAtItemPosQt()");
	}
}



/**************************************************************************
 void MultiCommonMesh::MoveAtIdentity();
 用途: 最初に作成された位置からの指定する相対位置をクリアする
 *すべてのオブジェクトに適用される
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::MoveAtIdentity(){
    //配置オブジェクトへの適用
    vector<CommonItem*>::size_type sz = m_ItemVec.size();
    for(vector<CommonItem*>::size_type i = 0;i < sz;i++){
		m_ItemVec[i]->m_Pos = D3DXVECTOR3(0,0,0);
		D3DXQuaternionIdentity(&m_ItemVec[i]->m_Qt);
	}
}
/**************************************************************************
 void MultiCommonMesh::MoveAtItemIdentity(
	size_t Index	//変化させるインデックス
 );
 用途: 指定のメンバの最初に作成された位置からの指定する相対位置をクリアする
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::MoveAtItemIdentity(size_t Index){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_Pos = D3DXVECTOR3(0,0,0);
		D3DXQuaternionIdentity(&m_ItemVec[Index]->m_Qt);
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::MoveAtItemIdentity()");
	}
}

/**************************************************************************
 void MultiCommonMesh::GetItemBaseScalePosRot(
	size_t Index,		//取得するインデックス
	D3DXVECTOR3& Scale,	//スケーリングの参照
	D3DXVECTOR3& Pos,	//ベース位置の参照
	D3DXVECTOR3& Rot	//ベース回転の参照
  );
 用途: 指定のインデックスのベースのスケーリングと位置と回転を同時に取り出す
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::GetItemBaseScalePosRot(size_t Index,
	 D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
    //指定の配置オブジェクトを検証
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		Scale = m_ItemVec[Index]->m_BaseScale;
		Pos = m_ItemVec[Index]->m_BasePos;
		D3DXQUATERNION Qt;
		//現在のベースクオータニオンを正規化
		D3DXQuaternionNormalize(&Qt,&m_ItemVec[Index]->m_BaseQt);
		//QtからRotに変換
		Math::QtToRot(Qt,Rot);

	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::GetBaseScalePosRot()");
	}
}


/**************************************************************************
 void MultiCommonMesh::GetItemBaseScalePosQt(
	size_t Index,		//取得するインデックス
	D3DXVECTOR3& Scale,	//スケーリングの参照
	D3DXVECTOR3& Pos,	//ベース位置の参照
	D3DXQUATERNION& Qt	//ベース回転クオータニオンの参照
  );
 用途: 指定のインデックスのベースのスケーリングと位置と回転を同時に取り出す（クオータニオン版）
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::GetItemBaseScalePosQt(size_t Index,
				D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
    //指定の配置オブジェクトを検証
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		Scale = m_ItemVec[Index]->m_BaseScale;
		Pos = m_ItemVec[Index]->m_BasePos;
		Qt = m_ItemVec[Index]->m_BaseQt;
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::GetBaseScalePosQt()");
	}
}


/**************************************************************************
 void MultiCommonMesh::SetItemBaseScale(
	size_t Index,		//設定するインデックス
	D3DXVECTOR3& Scale	//新しいベーススケーリング
  );
 用途: 指定のインデックスの最初に作成されたスケーリングを変更する
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::SetItemBaseScale(size_t Index,D3DXVECTOR3& Scale){
    //指定の配置オブジェクトを検証
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_BaseScale = Scale;
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::SetItemBaseScale()");
	}
}
/**************************************************************************
 void MultiCommonMesh::SetItemBasePos(
	size_t Index,		//設定するインデックス
	D3DXVECTOR3& Pos	//新しいベース位置
  );
 用途: 指定のインデックスの最初に作成された位置を変更する
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::SetItemBasePos(size_t Index,D3DXVECTOR3& Pos){
    //指定の配置オブジェクトを検証
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_BasePos = Pos;
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::SetItemBasePos()");
	}
}
/**************************************************************************
 void MultiCommonMesh::SetItemBaseRot(
	size_t Index,		//設定するインデックス
	D3DXVECTOR3& Rot	//新しいベース回転
  );
 用途: 指定のインデックスの最初に作成された回転を変更する
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::SetItemBaseRot(size_t Index,D3DXVECTOR3& Rot){
    //指定の配置オブジェクトを検証
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		D3DXQuaternionIdentity(&m_ItemVec[Index]->m_BaseQt);
		D3DXQuaternionRotationYawPitchRoll(&m_ItemVec[Index]->m_BaseQt,
			Rot.y,Rot.x,Rot.z);
		//クオータニオンを正規化
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_BaseQt,&m_ItemVec[Index]->m_BaseQt);
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::SetItemBaseRot()");
	}
}
/**************************************************************************
 void MultiCommonMesh::SetItemBaseQt(
	size_t Index,		//設定するインデックス
	D3DXQUATERNION& Qt	//新しいベース回転
  );
 用途: 指定のインデックスの最初に作成された回転を変更する(クオータニオン版)
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::SetItemBaseQt(size_t Index,D3DXQUATERNION& Qt){
    //指定の配置オブジェクトを検証
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_BaseQt = Qt;
		//クオータニオンを正規化
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_BaseQt,&m_ItemVec[Index]->m_BaseQt);
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::SetItemBaseQt()");
	}
}
/**************************************************************************
 void MultiCommonMesh::SetItemBaseScalePosRot(
	size_t Index,		//設定するインデックス
	D3DXVECTOR3& Scale,	//新しいベーススケーリング
	D3DXVECTOR3& Pos,	//新しいベース位置
	D3DXVECTOR3& Rot	//新しいベース回転
  );
 用途: 指定のインデックスの最初に作成されたスケーリングと位置と回転を同時に変更する
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::SetItemBaseScalePosRot(size_t Index,
	D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
    //指定の配置オブジェクトを検証
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_BaseScale = Scale;
		m_ItemVec[Index]->m_BasePos = Pos;
		D3DXQuaternionIdentity(&m_ItemVec[Index]->m_BaseQt);
		D3DXQuaternionRotationYawPitchRoll(&m_ItemVec[Index]->m_BaseQt,
			Rot.y,Rot.x,Rot.z);
		//クオータニオンを正規化
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_BaseQt,&m_ItemVec[Index]->m_BaseQt);
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::SetItemBaseScalePosRot()");
	}
}
/**************************************************************************
 void MultiCommonMesh::SetItemBaseScalePosQt(
	size_t Index,		//設定するインデックス
	D3DXVECTOR3& Scale,	//新しいベーススケーリング
	D3DXVECTOR3& Pos,	//新しいベース位置
	D3DXQUATERNION& Qt	//新しいベース回転
  );
 用途: 指定のインデックスの最初に作成されたスケーリングと位置と回転を同時に変更する(クオータニオン版)
 戻り値: なし
***************************************************************************/
void MultiCommonMesh::SetItemBaseScalePosQt(size_t Index,
	D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
    //指定の配置オブジェクトを検証
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_BaseScale = Scale;
		m_ItemVec[Index]->m_BasePos = Pos;
		m_ItemVec[Index]->m_BaseQt = Qt;
		//クオータニオンを正規化
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_BaseQt,&m_ItemVec[Index]->m_BaseQt);
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiCommonMesh::SetItemBaseScalePosRot()");
	}
}

/**************************************************************************
 virtual void MultiCommonMesh::Transform(
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Context& Data					//ユーザーデータ
 );
 用途: 描画前の変化。行列の計算などを行う（仮想関数）
 戻り値: なし。
***************************************************************************/
void MultiCommonMesh::Transform(vector<Object*>& Vec,
		const CONTROLER_STATE* pCntlState,Context& Data){
    //配置オブジェクトの行列の設定
    vector<CommonItem*>::size_type sz = m_ItemVec.size();
    for(vector<CommonItem*>::size_type i = 0;i < sz;i++){
		//非アクティブなら計算しない
		if(!m_ItemVec[i]->m_IsActive){
			continue;
		}
		//拡大縮小用
		D3DXMATRIX mtScale;
		D3DXMatrixIdentity(&mtScale);
		D3DXMatrixScaling(&mtScale,
			m_ItemVec[i]->m_BaseScale.x,m_ItemVec[i]->m_BaseScale.y,m_ItemVec[i]->m_BaseScale.z);
		//ローカル回転用
		D3DXMATRIX mtRot;
		D3DXMatrixIdentity(&mtRot);
		//ローカル回転
		D3DXMatrixRotationQuaternion(&mtRot,&m_ItemVec[i]->m_BaseQt);
		//ローカル移動用
		D3DXMATRIX mtPos;
		D3DXMatrixIdentity(&mtPos);
		D3DXMatrixTranslation(&mtPos,m_ItemVec[i]->m_BasePos.x,m_ItemVec[i]->m_BasePos.y,m_ItemVec[i]->m_BasePos.z);

		//相対回転用
		D3DXMATRIX mtOffsetRot;
		D3DXMatrixIdentity(&mtOffsetRot);
		//相対回転
		D3DXMatrixRotationQuaternion(&mtOffsetRot,&m_ItemVec[i]->m_Qt);

		//相対移動用
		D3DXMATRIX mtOffsetPos;
		D3DXMatrixIdentity(&mtOffsetPos);
		//相対移動
		D3DXMatrixTranslation(&mtOffsetPos,m_ItemVec[i]->m_Pos.x,m_ItemVec[i]->m_Pos.y,m_ItemVec[i]->m_Pos.z);

		//すべてミックス行列をワールド行列に設定
		D3DXMatrixIdentity(&m_ItemVec[i]->m_WorldMatrix);
		m_ItemVec[i]->m_WorldMatrix = mtScale * mtRot  *  mtPos * mtOffsetRot * mtOffsetPos;
    }
}


/**************************************************************************
 virtual void MultiCommonMesh::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Context& Data					//ユーザーデータ
 );
 用途: オブジェクトを描画（純粋仮想関数）
 戻り値: なし。
***************************************************************************/
void MultiCommonMesh::Draw(DrawPacket& i_DrawPacket){
    //配置オブジェクトの描画
    vector<CommonItem*>::size_type sz = m_ItemVec.size();
    for(vector<CommonItem*>::size_type i = 0;i < sz;i++){
		//非アクティブなら表示しない
		if(!m_ItemVec[i]->m_IsActive){
			continue;
		}
		//すでにワールド座標は変換済みと前提
		//コモンメッシュの描画を呼ぶ
		DrawCommonMesh(i_DrawPacket.pD3DDevice,m_ItemVec[i]->m_WorldMatrix,m_ItemVec[i]->m_Material,
			m_ItemVec[i]->m_pTexture);
    }
}
/**************************************************************************
	virtual void MultiCommonMesh::DrawShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
	LPD3DXEFFECT	pEffect,			//エフェクトのポインタ
	D3DXMATRIX& mCameraView,			//カメラのビュー行列
	D3DXMATRIX& mCameraProj			//カメラのプロジェクション行列
	);
 用途: 影ボリュームを描画（仮想関数）
 戻り値: なし。
***************************************************************************/
void MultiCommonMesh::DrawShadowVolume(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect,
	   D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj){
	//配置オブジェクトの影描画
	vector<CommonItem*>::size_type sz = m_ItemVec.size();
	for(vector<CommonItem*>::size_type i = 0;i < sz;i++){
		//非アクティブなら表示しない
		if(!m_ItemVec[i]->m_IsActive){
			continue;
		}
		//そのアイテムが影が有効なら
		if(m_ItemVec[i]->m_IsShadowActive){
			//影描画用のマトリクス
			D3DXMATRIX mtAllMatrix;
			//行列を取り出す
			mtAllMatrix = m_ItemVec[i]->m_WorldMatrix;
			mtAllMatrix._42 -=  0.02f;	//Y座標
			mtAllMatrix._11 *= 0.98f;	//Xスケール
			mtAllMatrix._22 *= 0.98f;	//Yスケール
			mtAllMatrix._33 *= 0.98f;	//Zスケール
			//コモンメッシュの影描画を呼ぶ
			DrawCommonShadowVolume(pD3DDevice,mtAllMatrix,pEffect,mCameraView,mCameraProj);
		}
	}
}


/**************************************************************************
 class MultiPolygon : public MultiCommonMesh;
 用途: 複数のポリゴンクラス
****************************************************************************/
/**************************************************************************
 void MultiPolygon::CreateInctance(
 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9インターフェイスへのポインタ
 );
 用途: インスタンスの構築
 戻り値: なし。（例外がthrowされる）
***************************************************************************/
void MultiPolygon::CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice){
    try{
		//ポリゴンの作成
		//失敗したら例外がthrowされる
		CreatePolygon(pD3DDevice,
		   m_Length,m_Sides,m_IsTextureActive);
    }
    catch(...){
        //コンストラクタ例外発生
		//後始末
		Clear();
        //再スロー
        throw;
    }
}
/**************************************************************************
 MultiPolygon(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9インターフェイスへのポインタ
	FLOAT Length,					//各面の長さ。
    UINT Sides,						//ポリゴンの面数。値は 3 以上である必要がある。
	bool IsTextureActive = false	//テクスチャを張るときは指定
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
 ＊コンストラクタでは、テクスチャを使用するかしないかを設定する
***************************************************************************/
MultiPolygon::MultiPolygon(LPDIRECT3DDEVICE9 pD3DDevice,
	 FLOAT Length,UINT Sides, wiz::OBJID id,bool IsTextureActive)
:MultiCommonMesh( id , IsTextureActive ),
m_Length(Length),
m_Sides(Sides)
{
	//インスタンスの構築
	//例外は呼び出した関数から投げられるので
	//ここには記述しなくて良い
	CreateInctance(pD3DDevice);
}
/**************************************************************************
 virtual MultiPolygon::~MultiPolygon();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
MultiPolygon::~MultiPolygon(){
	//後始末
	Clear();
}
/**************************************************************************
	virtual void MultiPolygon::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
 用途: デバイス喪失による再構築（仮想関数）
 戻り値: なし。
 ＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
void MultiPolygon::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//インスタンスの構築
	//例外は呼び出した関数から投げられるので
	//ここには記述しなくて良い
	CreateInctance(pD3DDevice);
}

/**************************************************************************
 class MultiBox : public MultiCommonMesh;
 用途: 複数の直方体クラス
****************************************************************************/
/**************************************************************************
 void MultiBox::CreateInctance(
 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9インターフェイスへのポインタ
 );
 用途: インスタンスの構築
 戻り値: なし。（例外がthrowされる）
***************************************************************************/
void MultiBox::CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice){
    try{
		//直方体の作成
		//失敗したら例外がthrowされる
		CreateBox(pD3DDevice,D3DXVECTOR3(m_Size.x,m_Size.y,m_Size.z),
			m_IsTextureActive,m_TexturePtn);
    }
    catch(...){
        //コンストラクタ例外発生
		//後始末
		Clear();
        //再スロー
        throw;
    }
}
/**************************************************************************
 MultiBox::MultiBox(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9インターフェイスへのポインタ
	D3DXVECTOR3& size,				//コモンメッシュを作成するときのサイズ
	bool IsTextureActive = false,	//テクスチャを張るときは指定
	int TexturePtn = PtnUV_1_1		//テクスチャのパターン
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
 ＊コンストラクタでは、テクスチャを使用するかしないかと、
 ＊テクスチャを使用する場合はテクスチャパターンを指定する
***************************************************************************/
MultiBox::MultiBox(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& size,
				   wiz::OBJID id,  bool IsTextureActive,int TexturePtn)
:MultiCommonMesh( id ,IsTextureActive),
m_Size(size),
m_TexturePtn(TexturePtn)
{
	//インスタンスの構築
	//例外は呼び出した関数から投げられるので
	//ここには記述しなくて良い
	CreateInctance(pD3DDevice);
}

/**************************************************************************
 virtual MultiBox::~MultiBox();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
MultiBox::~MultiBox(){
	//後始末
	Clear();
}



/**************************************************************************
	virtual void MultiBox::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
 用途: デバイス喪失による再構築（仮想関数）
 戻り値: なし。
 ＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
void MultiBox::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//インスタンスの構築
	//例外は呼び出した関数から投げられるので
	//ここには記述しなくて良い
	CreateInctance(pD3DDevice);
}

/**************************************************************************
	void MultiBox::GetOBB(
		size_t Index,
		OBB& obb	//取得するOBB
	);
 用途: 指定のインデックスの現在のOBBを得る
 戻り値: なし。インデックスが範囲外なら例外
 ＊現在のOBBを代入する
***************************************************************************/
void MultiBox::GetOBB(size_t Index,OBB& obb){
    //指定の配置オブジェクトを検証
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		obb.m_Center = m_ItemVec[Index]->m_BasePos + m_ItemVec[Index]->m_Pos;
		obb.m_Size = m_Size;
		obb.m_Size.x *= m_ItemVec[Index]->m_BaseScale.x;
		obb.m_Size.y *= m_ItemVec[Index]->m_BaseScale.y;
		obb.m_Size.z *= m_ItemVec[Index]->m_BaseScale.z;
		obb.m_Size *= 0.5f;
		//トータルの回転を得る
		D3DXQUATERNION Qt = m_ItemVec[Index]->m_BaseQt;
		Qt *= m_ItemVec[Index]->m_Qt;
		//クオータニオンを正規化
		D3DXQuaternionNormalize(&Qt,&Qt);
		//クオータニオンから回転行列を作成
		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationQuaternion(&mRot,&Qt);
		obb.m_Rot[0] = D3DXVECTOR3(mRot._11,mRot._12,mRot._13);
	    obb.m_Rot[1] = D3DXVECTOR3(mRot._21,mRot._22,mRot._23);
	    obb.m_Rot[2] = D3DXVECTOR3(mRot._31,mRot._32,mRot._33);
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"MultiBox::GetOBB()");
	}
}

/**************************************************************************
class ParallelMultiBox : public MultiBox;
 用途: 複数の軸に平行な直方体クラス
****************************************************************************/

/**************************************************************************
 ParallelMultiBox::ParallelMultiBox(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9インターフェイスへのポインタ
	D3DXVECTOR3& size,				//コモンメッシュを作成するときのサイズ
	bool IsTextureActive = false,	//テクスチャを張るときは指定
	int TexturePtn = PtnUV_1_1		//テクスチャのパターン
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
 ＊コンストラクタでは、テクスチャを使用するかしないかと、
 ＊テクスチャを使用する場合はテクスチャパターンを指定する
***************************************************************************/
ParallelMultiBox::ParallelMultiBox(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& size,
						wiz::OBJID id ,bool IsTextureActive,int TexturePtn)
:MultiBox(pD3DDevice,size,id,IsTextureActive,TexturePtn)
{
	//本体は何もしない
}

/**************************************************************************
 virtual ParallelMultiBox::~ParallelMultiBox();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
ParallelMultiBox::~ParallelMultiBox(){
	//何もしない
}


/**************************************************************************
 size_t ParallelMultiBox::AddItem(
    D3DXVECTOR3& Scale,               //スケール（拡大縮小の倍率）
    D3DXVECTOR3& Pos,                //最初の位置
    D3DCOLORVALUE& Diffuse,         //ディフューズ色
    D3DCOLORVALUE& Specular,            //スペキュラ色
    D3DCOLORVALUE& Ambient,          //アンビエント色
	bool IsShadowActive = false,	//影を描画するかどうか
	LPDIRECT3DTEXTURE9 pTexture = 0			//テクスチャ
    );
 用途: アイテムを追加
 ＊回転は受けつけない
 戻り値: 追加したインデックス（失敗時は例外をthrow）
***************************************************************************/
 size_t ParallelMultiBox::AddItem(
    D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,
    D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
	bool IsShadowActive,LPDIRECT3DTEXTURE9 pTexture){
	try{
		D3DXVECTOR3 Rot(0,0,0);				//回転は固定
		return MultiCommonMesh::AddItem(Scale,Pos,Rot,
				 Diffuse,Specular,Ambient,
				 IsShadowActive,pTexture);

	}
	catch(...){
		//再スロー
		throw;
	}
	return 0;
}
/**************************************************************************
	void ParallelMultiBox::GetAABB(
		size_t Index,			//インデックス
		AABB& Tgt	//矩形変数
	);
 用途: 指定のインデックスの現在矩形を得る
 戻り値: なし。インデックスが範囲外なら例外
***************************************************************************/
void ParallelMultiBox::GetAABB(size_t Index,AABB& Tgt){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		D3DXVECTOR3 Pos = m_ItemVec[Index]->m_BasePos + m_ItemVec[Index]->m_Pos;
		AABB aabb(Pos,
			m_Size.x * m_ItemVec[Index]->m_BaseScale.x,
			m_Size.y * m_ItemVec[Index]->m_BaseScale.y,
			m_Size.z * m_ItemVec[Index]->m_BaseScale.z
			);
		Tgt = aabb;
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"ParallelMultiBox::GetAABB()");
	}
}


/**************************************************************************
 class MultiSphere : public CommonMesh;
 用途: 複数の球クラス
****************************************************************************/
/**************************************************************************
 void MultiSphere::CreateInctance(
 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9インターフェイスへのポインタ
 );
 用途: インスタンスの構築
 戻り値: なし。（例外がthrowされる）
***************************************************************************/
void MultiSphere::CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice){
    try{
		//球の作成
		//失敗したら例外がthrowされる
		CreateSphere(pD3DDevice,m_Radius,m_IsTextureActive,m_Slices,m_Stacks);

    }
    catch(...){
        //コンストラクタ例外発生
		//後始末
		Clear();
        //再スロー
        throw;
    }
}

/**************************************************************************
 MultiSphere::MultiSphere(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9インターフェイスへのポインタ
	FLOAT radius,					//コモンメッシュを作成するときの半径
	bool IsTextureActive = false,	//テクスチャがあるかどうか
	UINT Slices = 18,				//主軸の回転スライス数
	UINT Stacks = 18				//主軸に沿ったスライス数
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
MultiSphere::MultiSphere(LPDIRECT3DDEVICE9 pD3DDevice,FLOAT radius,
		wiz::OBJID id,bool IsTextureActive,
		UINT Slices,UINT Stacks)
:MultiCommonMesh(id,IsTextureActive),
m_Radius(radius),
m_Slices(Slices),
m_Stacks(Stacks)
{
	//インスタンスの構築
	//例外は呼び出した関数から投げられるので
	//ここには記述しなくて良い
	CreateInctance(pD3DDevice);
}
/**************************************************************************
 virtual MultiSphere::~MultiSphere();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
MultiSphere::~MultiSphere(){
    //後始末
	Clear();
}

/**************************************************************************
	virtual void MultiSphere::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
 用途: デバイス喪失による再構築（仮想関数）
 戻り値: なし。
 ＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
void MultiSphere::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//インスタンスの構築
	//例外は呼び出した関数から投げられるので
	//ここには記述しなくて良い
	CreateInctance(pD3DDevice);
}

/**************************************************************************
 class MultiCylinder : public MultiCommonMesh;
 用途: 複数のシリンダークラス
****************************************************************************/
/**************************************************************************
 void MultiCylinder::CreateInctance(
 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9インターフェイスへのポインタ
 );
 用途: インスタンスの構築
 戻り値: なし。（例外がthrowされる）
***************************************************************************/
void MultiCylinder::CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice){
    try{
		//シリンダーの作成
		CreateCylinder(pD3DDevice,m_Radius1,m_Radius2,m_Length,m_IsTextureActive,m_Slices,m_Stacks);
    }
    catch(...){
        //コンストラクタ例外発生
		//後始末
		Clear();
        //再スロー
        throw;
    }
}

/**************************************************************************
 MultiCylinder::MultiCylinder(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9インターフェイスへのポインタ
    FLOAT Radius1,                   //z 軸の負の側の面の半径。値は 0.0f 以上である必要がある。 
    FLOAT Radius2,                   //z 軸の正の側の面の半径。値は 0.0f 以上である必要がある。
	FLOAT Length,					//z 軸方向の円柱の長さ。
	bool IsTextureActive = false,	//テクスチャがあるかどうか
	UINT Slices = 18,		//主軸を回転軸としたスライスの数。
	UINT Stacks = 18		//主軸に沿ったスタック数。
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
MultiCylinder::MultiCylinder(LPDIRECT3DDEVICE9 pD3DDevice,
		FLOAT Radius1,FLOAT Radius2,FLOAT Length, wiz::OBJID id,
		bool IsTextureActive,UINT Slices,UINT Stacks)
:MultiCommonMesh(id,IsTextureActive),
m_Radius1(Radius1),
m_Radius2(Radius2),
m_Length(Length),
m_Slices(Slices),
m_Stacks(Stacks)
{
	//インスタンスの構築
	//例外は呼び出した関数から投げられるので
	//ここには記述しなくて良い
	CreateInctance(pD3DDevice);
}
/**************************************************************************
 virtual MultiCylinder::~MultiCylinder();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
MultiCylinder::~MultiCylinder(){
    //後始末
	Clear();
}
/**************************************************************************
void MultiCylinder::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
 用途: デバイス喪失による再構築（仮想関数）
 戻り値: なし。
 ＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
void MultiCylinder::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//インスタンスの構築
	//例外は呼び出した関数から投げられるので
	//ここには記述しなくて良い
	CreateInctance(pD3DDevice);
}

/**************************************************************************
 class MultiTorus : public MultiCommonMesh;
 用途: 複数のトーラスクラス
****************************************************************************/
/**************************************************************************
 void MultiTorus::CreateInctance(
 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9インターフェイスへのポインタ
 );
 用途: インスタンスの構築
 戻り値: なし。（例外がthrowされる）
***************************************************************************/
void MultiTorus::CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice){
    try{
		//トーラスの作成
		//失敗したら例外がthrowされる
		CreateTorus(pD3DDevice,m_InnerRadius,m_OuterRadius,m_IsTextureActive,m_Sides,m_Rings);
    }
    catch(...){
        //コンストラクタ例外発生
		//後始末
		Clear();
        //再スロー
        throw;
    }
}

/**************************************************************************
 MultiTorus::MultiTorus(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9インターフェイスへのポインタ
    FLOAT InnerRadius,              //ドーナッツの半径
    FLOAT OuterRadius,              //原点からドーナッツ中心までの半径
	bool IsTextureActive = false,	//テクスチャがあるかどうか
	UINT Sides = 18,					//横断面の辺の数。値は 3 以上である必要がある。
	UINT Rings = 18				//トーラスを構成する環の数。値は 3 以上である必要がある
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
MultiTorus::MultiTorus(LPDIRECT3DDEVICE9 pD3DDevice,FLOAT InnerRadius,FLOAT OuterRadius,
					   wiz::OBJID id,bool IsTextureActive,UINT Sides,UINT Rings)
:MultiCommonMesh(id,IsTextureActive),
m_InnerRadius(InnerRadius),
m_OuterRadius(OuterRadius),
m_Sides(Sides),
m_Rings(Rings)
{
	//インスタンスの構築
	//例外は呼び出した関数から投げられるので
	//ここには記述しなくて良い
	CreateInctance(pD3DDevice);
}
/**************************************************************************
 virtual MultiTorus::~MultiTorus();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
MultiTorus::~MultiTorus(){
    //後始末
	Clear();
}
/**************************************************************************
	virtual void MultiTorus::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
 用途: デバイス喪失による再構築（仮想関数）
 戻り値: なし。
 ＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
void MultiTorus::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//インスタンスの構築
	//例外は呼び出した関数から投げられるので
	//ここには記述しなくて良い
	CreateInctance(pD3DDevice);
}

/**************************************************************************
 class SimpleCommonMesh : public CommonMesh;
 用途: 単純なコモンメッシュクラス
****************************************************************************/
/**************************************************************************
 SimpleCommonMesh::SimpleCommonMesh(
    D3DXVECTOR3& Pos,                //位置
	D3DXVECTOR3& Rot,				//回転(ラジアン単位)
    D3DCOLORVALUE& Diffuse,         //ディフューズ色
    D3DCOLORVALUE& Specular,            //スペキュラ色
    D3DCOLORVALUE& Ambient,          //アンビエント色
	bool IsShadowActive = false,	//影を描画するかどうか
	LPDIRECT3DTEXTURE9 pTexture = 0,	//テクスチャを張るときは指定
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
SimpleCommonMesh::SimpleCommonMesh(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		wiz::OBJID id,
		bool IsShadowActive,LPDIRECT3DTEXTURE9 pTexture)
:CommonMesh( id ),
m_IsActive(true),
m_BaseScale(1.0f,1.0f,1.0f),
m_BasePos(Pos),m_Pos(0,0,0),
m_BaseQt(0,0,0,1),m_Qt(0,0,0,1),
m_IsShadowActive(IsShadowActive),
m_pTexture(pTexture)
{
    try{
        //クオータニオンの初期化
		D3DXQuaternionIdentity(&m_BaseQt);
		D3DXQuaternionRotationYawPitchRoll(&m_BaseQt,
			Rot.y,Rot.x,Rot.z);
		D3DXQuaternionIdentity(&m_Qt);
		//行列の初期化
		D3DXMatrixIdentity(&m_WorldMatrix);
		//拡大縮小用
		D3DXMATRIX mtScale;
		D3DXMatrixIdentity(&mtScale);
		D3DXMatrixScaling(&mtScale,
			m_BaseScale.x,m_BaseScale.y,m_BaseScale.z);
		//基本回転用
		D3DXMATRIX mtRot;
		D3DXMatrixIdentity(&mtRot);
		//基本回転
		D3DXMatrixRotationQuaternion(&mtRot,&m_BaseQt);
		//基本移動用
		D3DXMATRIX mtPos;
		D3DXMatrixIdentity(&mtPos);
		D3DXMatrixTranslation(&mtPos,m_BasePos.x,m_BasePos.y,m_BasePos.z);

		//相対回転用
		D3DXMATRIX mtOffsetRot;
		D3DXMatrixIdentity(&mtOffsetRot);
		//相対回転
		D3DXMatrixRotationQuaternion(&mtOffsetRot,&m_Qt);

		//相対移動用
		D3DXMATRIX mtOffsetPos;
		D3DXMatrixIdentity(&mtOffsetPos);
		//相対移動
		D3DXMatrixTranslation(&mtOffsetPos,m_Pos.x,m_Pos.y,m_Pos.z);
		//すべてミックス行列
		m_WorldMatrix = mtScale * mtRot  *  mtPos * mtOffsetRot * mtOffsetPos;

        // D3DMATERIAL9構造体を0でクリア
        ::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
        // モデルの色を設定
        m_Material.Diffuse = Diffuse;
        m_Material.Specular = Specular;
        m_Material.Ambient = Ambient;
    }
    catch(...){
        //コンストラクタ例外発生
        //再スロー
        throw;
    }
}
/**************************************************************************
 virtual SimpleCommonMesh::~SimpleCommonMesh();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
 SimpleCommonMesh::~SimpleCommonMesh(){
	//マルチコモンメッシュ配列のクリア
	 SafeDeletePointerContainer(m_MultiVec);
	//自身のメッシュのクリアは親クラスで行なう
 }

/**************************************************************************
 size_t SimpleCommonMesh::AddMultiMesh(
	MultiCommonMesh* pMultiCommonMesh	//マルチメッシュのポインタ
  );
 用途: マルチメッシュを追加
 戻り値: 追加した配列のインデックス
***************************************************************************/
size_t SimpleCommonMesh::AddMultiMesh(MultiCommonMesh* pMultiCommonMesh){
	size_t ret = m_MultiVec.size();
	m_MultiVec.push_back(pMultiCommonMesh);
	return ret;
}

/**************************************************************************
 size_t SimpleCommonMesh::GetMultiMeshCount();
 用途: マルチメッシュの数を返す
 戻り値: マルチメッシュ配列の数
***************************************************************************/
size_t SimpleCommonMesh::GetMultiMeshCount(){
	return m_MultiVec.size();
}
/**************************************************************************
 MultiCommonMesh* SimpleCommonMesh::MultiCommonMesh(size_t Index);
 用途: 指定したインデックスのマルチメッシュを返す
 戻り値: マルチメッシュのポインタ（範囲外は例外）
***************************************************************************/
MultiCommonMesh* SimpleCommonMesh::GetMultiCommonMesh(size_t Index){
    //指定のマルチメッシュを調査
    size_t sz = m_MultiVec.size();
	if(Index < sz){
		return m_MultiVec[Index];
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"impleCommonMesh::GetMultiMesh()");
	}
	return false;
}


/**************************************************************************
bool SimpleCommonMesh::IsActive();
 用途: オブジェクトが有効かどうかを調べる
 戻り値: 有効ならTRUE、無効ならFALSE
***************************************************************************/
bool SimpleCommonMesh::IsActive(){
	return m_IsActive;
}
/**************************************************************************
void SimpleCommonMesh::SetActive(
	bool val		//したいしたい値（trueかfalse）
);
 用途:このオブジェクトが有効かどうかを設定する
 戻り値: なし、
***************************************************************************/
void SimpleCommonMesh::SetActive(bool val){
	m_IsActive = val;
}


/**************************************************************************
 void SimpleCommonMesh::GetMaterial(
	D3DMATERIAL9& Material	//現在のマテリアル
  );
 用途: マテリアルを取得する
 戻り値: なし（Materialにマテリアルを返す）
***************************************************************************/
void SimpleCommonMesh::GetMaterial(D3DMATERIAL9& Material){
	Material = m_Material;
}
/**************************************************************************
 void SimpleCommonMesh::SetMaterial(
	D3DMATERIAL9& Material	//設定するマテリアル
  );
 用途: マテリアルを設定する
 戻り値: なし
***************************************************************************/
void SimpleCommonMesh::SetMaterial(D3DMATERIAL9& Material){
	m_Material = Material;
}

/**************************************************************************
bool SimpleCommonMesh::IsTextureActive();
 用途: テクスチャが有効かどうかを調べる
 戻り値: 有効ならTRUE、無効ならFALSE
 ＊テクスチャを変更する場合は、先に有効かどうか調査すること
***************************************************************************/
bool SimpleCommonMesh::IsTextureActive(){
	if(m_pTexture){
		return true;
	}
	else{
		return false;
	}
}

/**************************************************************************
 LPDIRECT3DTEXTURE9 SimpleCommonMesh::GetTexture();
 用途: テクスチャを取得する
 戻り値: 現在のテクスチャ（ない場合は0が返る）
***************************************************************************/
LPDIRECT3DTEXTURE9 SimpleCommonMesh::GetTexture(){
	return m_pTexture;
}
/**************************************************************************
 void SimpleCommonMesh::SetTexture(
	LPDIRECT3DTEXTURE9 pTexture	//設定するテクスチャ
  );
 用途: テクスチャを設定する
 戻り値: なし
***************************************************************************/
void SimpleCommonMesh::SetTexture(LPDIRECT3DTEXTURE9 pTexture){
	//テクスチャがある場合
	if(m_pTexture){
		if(!pTexture){
			throw BaseException(L"このオブジェクトはテクスチャが必要です。",
				L"SimpleCommonMesh::SetTexture()");
		}
	}
	else{
	//テクスチャがない場合
		if(pTexture){
			throw BaseException(L"このオブジェクトはテクスチャが設定できません。",
				L"SimpleCommonMesh::SetTexture()");
		}

	}
	m_pTexture = pTexture;
}

/**************************************************************************
bool SimpleCommonMesh::IsShadowActive();
 用途: 影が有効かどうかを調べる
 戻り値: 有効ならTRUE、無効ならFALSE
***************************************************************************/
bool SimpleCommonMesh::IsShadowActive(){
	return m_IsShadowActive;
}

/**************************************************************************
void SimpleCommonMesh::SetShadowActive(
bool val		//したいしたい値（trueかfalse）
);
 用途: 影が有効かどうかを設定する
 戻り値: なし、
***************************************************************************/
void SimpleCommonMesh::SetShadowActive(bool val){
	m_IsShadowActive = val;
}


/**************************************************************************
 void SimpleCommonMesh::GetWorldPos(
	D3DXVECTOR3& Pos	//現在のワールド位置
  );
 用途: ワールド位置を取得する
 戻り値: なし（Posにワールド位置を返す）
***************************************************************************/
void SimpleCommonMesh::GetWorldPos(D3DXVECTOR3& Pos){
	Pos = m_BasePos + m_Pos;
}

/**************************************************************************
 void SimpleCommonMesh::GetWorldRot(
	D3DXVECTOR3& Rot	//現在のワールド回転
  );
 用途: ワールド回転を取得する
 戻り値: なし（Rotにワールド回転を返す）
***************************************************************************/
void SimpleCommonMesh::GetWorldRot(D3DXVECTOR3& Rot){
	D3DXQUATERNION Qt = m_BaseQt * m_Qt;
	//現在のベースクオータニオンを正規化
	D3DXQuaternionNormalize(&Qt,&Qt);
	//QtからRotに変換
	Math::QtToRot(Qt,Rot);

}
/**************************************************************************
 void SimpleCommonMesh::GetWorldQt(
	D3DXQUATERNION& Qt	//現在のワールド回転
  );
 用途: ワールド回転を取得する
 戻り値: なし（Qtにワールド回転を返す）
***************************************************************************/
void SimpleCommonMesh::GetWorldQt(D3DXQUATERNION& Qt){
	Qt = m_BaseQt * m_Qt;
}
/**************************************************************************
 void SimpleCommonMesh::GetWorldScale(
	D3DXVECTOR3& Scale	//現在のワールドスケール
  );
 用途: ワールドスケールを取得する
 ＊この関数はGetBaseScale関数と同じ
 戻り値: なし（Scaleにワールドスケーリングを返す）
***************************************************************************/
void SimpleCommonMesh::GetWorldScale(D3DXVECTOR3& Scale){
	Scale = m_BaseScale;
}
/**************************************************************************
 void SimpleCommonMesh::GetWorld(
	D3DXVECTOR3& Scale,	//現在のワールドスケール
	D3DXVECTOR3& Pos,	//現在のワールド位置
	D3DXVECTOR3& Rot,	//現在のワールド回転（オイラー各）
	D3DXQUATERNION& Qt	//現在のワールド回転（クオータニオン）
  );
 用途: すべてのワールド値を取得する
 戻り値: なし（参照にワールド値を返す）
***************************************************************************/
void SimpleCommonMesh::GetWorld(
		D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot,D3DXQUATERNION& Qt){
	Scale = m_BaseScale;
	Pos = m_BasePos + m_Pos;
	Qt = m_BaseQt * m_Qt;
	//現在のベースクオータニオンを正規化
	D3DXQuaternionNormalize(&Qt,&Qt);
	//QtからRotに変換
	Math::QtToRot(Qt,Rot);
}

/**************************************************************************
 void SimpleCommonMesh::GetWorldMatrix(
	D3DXMATRIX& mtWorld
 );
 用途:ワールド変換を取得する
 戻り値: なし。mtWorldに変換行列をセットする
***************************************************************************/
void SimpleCommonMesh::GetWorldMatrix(D3DXMATRIX& mtWorld){
	mtWorld = m_WorldMatrix;
}

/**************************************************************************
 void SimpleCommonMesh::CalcWorldMatrix();
 用途:ワールド変換を計算する
 戻り値: なし。現在の変換をもとにワールド行列を計算する
***************************************************************************/
void SimpleCommonMesh::CalcWorldMatrix(){
	if(!m_IsActive){
		//アクティブでなければ計算しない
		return;
	}
	//拡大縮小用
	D3DXMATRIX mtScale;
	D3DXMatrixIdentity(&mtScale);
	D3DXMatrixScaling(&mtScale,
		m_BaseScale.x,m_BaseScale.y,m_BaseScale.z);
	//基本回転用
	D3DXMATRIX mtRot;
	D3DXMatrixIdentity(&mtRot);
	//基本回転
	D3DXMatrixRotationQuaternion(&mtRot,&m_BaseQt);
	//基本移動用
	D3DXMATRIX mtPos;
	D3DXMatrixIdentity(&mtPos);
	D3DXMatrixTranslation(&mtPos,m_BasePos.x,m_BasePos.y,m_BasePos.z);

	//相対回転用
	D3DXMATRIX mtOffsetRot;
	D3DXMatrixIdentity(&mtOffsetRot);
	//相対回転
	D3DXMatrixRotationQuaternion(&mtOffsetRot,&m_Qt);

	//相対移動用
	D3DXMATRIX mtOffsetPos;
	D3DXMatrixIdentity(&mtOffsetPos);
	//相対移動
	D3DXMatrixTranslation(&mtOffsetPos,m_Pos.x,m_Pos.y,m_Pos.z);
	//すべてミックス行列
	m_WorldMatrix = mtScale * mtRot  *  mtPos * mtOffsetRot * mtOffsetPos;
	//マルチメッシュ配列内の描画前の変化
	vector<MultiCommonMesh*>::size_type sz = m_MultiVec.size();
	for(vector<MultiCommonMesh*>::size_type i = 0;i < sz;i++){
		m_MultiVec[i]->CalcWorldMatrix();
	}
}

/**************************************************************************
 void SimpleCommonMesh::GetLocalPosQt(
	D3DXVECTOR3& Pos,	//現在の相対位置
	D3DXQUATERNION& Qt	//現在の相対回転
  );
 用途: 相対値を取得する(クオータニオン版)
 戻り値: なし
***************************************************************************/
void SimpleCommonMesh::GetLocalPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
	Pos = m_Pos;
	Qt = m_Qt;
}
/**************************************************************************
 void GetLocalPosRot(
	D3DXVECTOR3& Pos,	//現在の相対位置
	D3DXVECTOR3& Rot	//現在の回転
  );
 用途: 相対値を取得する
 戻り値: なし
***************************************************************************/
void SimpleCommonMesh::GetLocalPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
	Pos = m_Pos;
	//回転
	D3DXQUATERNION Qt;
	//現在のローカルクオータニオンを正規化
	D3DXQuaternionNormalize(&Qt,&m_Qt);
	//正規化
	D3DXQuaternionNormalize(&Qt,&Qt);
	//QtからRotに変換
	Math::QtToRot(Qt,Rot);
}

/**************************************************************************
 void SimpleCommonMesh::SetLocalPosQt(
	D3DXVECTOR3& Pos,	//相対位置
	D3DXQUATERNION& Qt	//相対回転
  );
 用途: 相対値を設定する(クオータニオン版)
 戻り値: なし
***************************************************************************/
void SimpleCommonMesh::SetLocalPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
	m_Pos = Pos;
	m_Qt = Qt;
}
/*************************************************************************
 void SimpleCommonMesh::SetLocalPosRot(
	D3DXVECTOR3& Pos,	//相対位置
	D3DXVECTOR3& Rot	//回転
  );
 用途: 相対値を設定する
 戻り値: なし
***************************************************************************/
void SimpleCommonMesh::SetLocalPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
	m_Pos = Pos;
	D3DXQuaternionIdentity(&m_Qt);
	D3DXQuaternionRotationYawPitchRoll(&m_Qt,
		Rot.y,Rot.x,Rot.z);
}


/**************************************************************************
 void SimpleCommonMesh::MoveToPosRot(
	D3DXVECTOR3& Pos,	//動かす相対位置
	D3DXVECTOR3& Rot	//動かす回転
  );
 用途: 相対値を移動し回転する
 戻り値: なし
***************************************************************************/
void SimpleCommonMesh::MoveToPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
	m_Pos += Pos;
	D3DXQUATERNION Qt;
	D3DXQuaternionIdentity(&Qt);
	D3DXQuaternionRotationYawPitchRoll(&Qt,
		Rot.y,Rot.x,Rot.z);
	m_Qt *= Qt;
	//クオータニオンを正規化
	D3DXQuaternionNormalize(&m_Qt,&m_Qt);
	vector<MultiCommonMesh*>::size_type sz = m_MultiVec.size();
	for(vector<MultiCommonMesh*>::size_type i = 0;i < sz;i++){
		m_MultiVec[i]->MoveToPosRot(Pos,Rot);
	}
}

/**************************************************************************
 void SimpleCommonMesh::MoveToPosQt(
	D3DXVECTOR3& Pos,	//動かす相対位置
	D3DXQUATERNION& Qt	//動かす回転
  );
 用途: 相対値を移動し回転する(クオータニオン版)
 戻り値: なし
***************************************************************************/
void SimpleCommonMesh::MoveToPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
	m_Pos += Pos;
	m_Qt *= Qt;
	//クオータニオンを正規化
	D3DXQuaternionNormalize(&m_Qt,&m_Qt);
	vector<MultiCommonMesh*>::size_type sz = m_MultiVec.size();
	for(vector<MultiCommonMesh*>::size_type i = 0;i < sz;i++){
		m_MultiVec[i]->MoveToPosQt(Pos,Qt);
	}
}


/**************************************************************************
 void SimpleCommonMesh::MoveAtPosRot(
	D3DXVECTOR3& Pos,	//新しい相対位置
	D3DXVECTOR3& Rot	//新しい回転
  );
 用途: 相対値を設定しなおす
 戻り値: なし
***************************************************************************/
void SimpleCommonMesh::MoveAtPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
	m_Pos = Pos;
	D3DXQuaternionIdentity(&m_Qt);
	D3DXQuaternionRotationYawPitchRoll(&m_Qt,
		Rot.y,Rot.x,Rot.z);
	//クオータニオンを正規化
	D3DXQuaternionNormalize(&m_Qt,&m_Qt);
	vector<MultiCommonMesh*>::size_type sz = m_MultiVec.size();
	for(vector<MultiCommonMesh*>::size_type i = 0;i < sz;i++){
		m_MultiVec[i]->MoveAtPosRot(Pos,Rot);
	}
}

/**************************************************************************
 void SimpleCommonMesh::MoveAtPosQt(
	D3DXVECTOR3& Pos,	//新しい相対位置
	D3DXQUATERNION& Qt	//新しい回転
  );
 用途: 相対値を設定しなおす(クオータニオン版)
 戻り値: なし
***************************************************************************/
void SimpleCommonMesh::MoveAtPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
	m_Pos = Pos;
	m_Qt = Qt;
	//クオータニオンを正規化
	D3DXQuaternionNormalize(&m_Qt,&m_Qt);
	vector<MultiCommonMesh*>::size_type sz = m_MultiVec.size();
	for(vector<MultiCommonMesh*>::size_type i = 0;i < sz;i++){
		m_MultiVec[i]->MoveAtPosQt(Pos,Qt);
	}
}


/**************************************************************************
 void SimpleCommonMesh::MoveAtIdentity();
 用途: 最初に作成された位置からの指定する相対位置をクリアする
 戻り値: なし
***************************************************************************/
void SimpleCommonMesh::MoveAtIdentity(){
	m_Pos = D3DXVECTOR3(0,0,0);
	D3DXQuaternionIdentity(&m_Qt);
	vector<MultiCommonMesh*>::size_type sz = m_MultiVec.size();
	for(vector<MultiCommonMesh*>::size_type i = 0;i < sz;i++){
		m_MultiVec[i]->MoveAtIdentity();
	}
}
/**************************************************************************
 void SimpleCommonMesh::GetBaseScalePosRot(
	D3DXVECTOR3& Scale,	//スケーリングの参照
	D3DXVECTOR3& Pos,	//ベース位置の参照
	D3DXVECTOR3& Rot	//ベース回転の参照
  );
 用途: 最初に作成されたスケーリングと位置と回転を同時に取り出す
 戻り値: なし
***************************************************************************/
void SimpleCommonMesh::GetBaseScalePosRot(D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
	Scale = m_BaseScale;
	Pos = m_BasePos;
	D3DXQUATERNION Qt;
	//現在のベースクオータニオンを正規化
	D3DXQuaternionNormalize(&Qt,&m_BaseQt);
	//QtからRotに変換
	Math::QtToRot(Qt,Rot);
}

/**************************************************************************
 void SimpleCommonMesh::GetBaseScalePosQt(
	D3DXVECTOR3& Scale,	//スケーリングの参照
	D3DXVECTOR3& Pos,	//ベース位置の参照
	D3DXQUATERNION& Qt	//ベース回転クオータニオンの参照
  );
 用途: 最初に作成されたスケーリングと位置と回転を同時に取り出す（クオータニオン版）
 戻り値: なし
***************************************************************************/
void SimpleCommonMesh::GetBaseScalePosQt(D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
	Scale = m_BaseScale;
	Pos = m_BasePos;
	Qt = m_BaseQt;
}


/**************************************************************************
 void SimpleCommonMesh::SetBaseScale(
	D3DXVECTOR3& Scale	//新しいベーススケーリング
  );
 用途: 最初に作成されたスケーリングを変更する
 戻り値: なし
***************************************************************************/
void SimpleCommonMesh::SetBaseScale(D3DXVECTOR3& Scale){
	m_BaseScale = Scale;
	//含まれるマルチメッシュには適用しない
}
/**************************************************************************
 void SimpleCommonMesh::SetBasePos(
	D3DXVECTOR3& Pos	//新しいベース位置
  );
 用途: 最初に作成された位置を変更する
 戻り値: なし
***************************************************************************/
void SimpleCommonMesh::SetBasePos(D3DXVECTOR3& Pos){
	m_BasePos = Pos;
	//含まれるマルチメッシュには適用しない
}
/**************************************************************************
 void SimpleCommonMesh::SetBaseRot(
	D3DXVECTOR3& Rot	//新しいベース回転
  );
 用途: 最初に作成された回転を変更する
 戻り値: なし
***************************************************************************/
void SimpleCommonMesh::SetBaseRot(D3DXVECTOR3& Rot){
	D3DXQuaternionIdentity(&m_BaseQt);
	D3DXQuaternionRotationYawPitchRoll(&m_BaseQt,
		Rot.y,Rot.x,Rot.z);
	//ベースクオータニオンを正規化
	D3DXQuaternionNormalize(&m_BaseQt,&m_BaseQt);
	//含まれるマルチメッシュには適用しない
}

/**************************************************************************
 void SimpleCommonMesh::SetBaseQt(
	D3DXQUATERNION& Qt	//新しいベース回転
  );
 用途: 最初に作成された回転を変更する(クオータニオン版)
 戻り値: なし
***************************************************************************/
void SimpleCommonMesh::SetBaseQt(D3DXQUATERNION& Qt){
	m_BaseQt = Qt;
	//ベースクオータニオンを正規化
	D3DXQuaternionNormalize(&m_BaseQt,&m_BaseQt);
	//含まれるマルチメッシュには適用しない
}


/**************************************************************************
 void SimpleCommonMesh::SetBaseScalePosRot(
	D3DXVECTOR3& Scale,	//新しいベーススケーリング
	D3DXVECTOR3& Pos,	//新しいベース位置
	D3DXVECTOR3& Rot	//新しいベース回転
  );
 用途: 最初に作成されたスケーリングと位置と回転を同時に変更する
 戻り値: なし
***************************************************************************/
void SimpleCommonMesh::SetBaseScalePosRot(D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
	m_BaseScale = Scale;
	m_BasePos = Pos;
	D3DXQuaternionIdentity(&m_BaseQt);
	D3DXQuaternionRotationYawPitchRoll(&m_BaseQt,
		Rot.y,Rot.x,Rot.z);
	//ベースクオータニオンを正規化
	D3DXQuaternionNormalize(&m_BaseQt,&m_BaseQt);
	//含まれるマルチメッシュには適用しない
}

/**************************************************************************
 void SimpleCommonMesh::SetBaseScalePosQt(
	D3DXVECTOR3& Scale,	//新しいベーススケーリング
	D3DXVECTOR3& Pos,	//新しいベース位置
	D3DXQUATERNION& Qt	//新しいベース回転
  );
 用途: 最初に作成されたスケーリングと位置と回転を同時に変更する(クオータニオン版)
 戻り値: なし
***************************************************************************/
void SimpleCommonMesh::SetBaseScalePosQt(D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
	m_BaseScale = Scale;
	m_BasePos = Pos;
	m_BaseQt = Qt;
	//ベースクオータニオンを正規化
	D3DXQuaternionNormalize(&m_BaseQt,&m_BaseQt);
	//含まれるマルチメッシュには適用しない
}



 /**************************************************************************
virtual void SimpleCommonMesh::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
 用途: デバイス喪失による再構築（仮想関数）
 戻り値: なし。（失敗時は例外をthrow）
 ＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
void SimpleCommonMesh::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//マルチメッシュ配列内の再構築
	vector<MultiCommonMesh*>::size_type sz = m_MultiVec.size();
	for(vector<MultiCommonMesh*>::size_type i = 0;i < sz;i++){
		m_MultiVec[i]->ChangeDevice(pD3DDevice);
	}
	//自身のデバイスチェンジは派生クラスで行なう
}


/**************************************************************************
 virtual void SimpleCommonMesh::Transform(
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Context& Data					//ユーザーデータ
 );
 用途: 描画前の変化。行列の計算などを行う（仮想関数）
 戻り値: なし。
***************************************************************************/
void SimpleCommonMesh::Transform(vector<Object*>& Vec,
	   const CONTROLER_STATE* pCntlState,Context& Data){
	if(!m_IsActive){
		//アクティブでなければ計算しない
		return;
	}
	//拡大縮小用
	D3DXMATRIX mtScale;
	D3DXMatrixIdentity(&mtScale);
	D3DXMatrixScaling(&mtScale,
		m_BaseScale.x,m_BaseScale.y,m_BaseScale.z);
	//基本回転用
	D3DXMATRIX mtRot;
	D3DXMatrixIdentity(&mtRot);
	//基本回転
	D3DXMatrixRotationQuaternion(&mtRot,&m_BaseQt);
	//基本移動用
	D3DXMATRIX mtPos;
	D3DXMatrixIdentity(&mtPos);
	D3DXMatrixTranslation(&mtPos,m_BasePos.x,m_BasePos.y,m_BasePos.z);

	//相対回転用
	D3DXMATRIX mtOffsetRot;
	D3DXMatrixIdentity(&mtOffsetRot);
	//相対回転
	D3DXMatrixRotationQuaternion(&mtOffsetRot,&m_Qt);

	//相対移動用
	D3DXMATRIX mtOffsetPos;
	D3DXMatrixIdentity(&mtOffsetPos);
	//相対移動
	D3DXMatrixTranslation(&mtOffsetPos,m_Pos.x,m_Pos.y,m_Pos.z);
	//すべてミックス行列
	m_WorldMatrix = mtScale * mtRot  *  mtPos * mtOffsetRot * mtOffsetPos;
	//マルチメッシュ配列内の描画前の変化
	vector<MultiCommonMesh*>::size_type sz = m_MultiVec.size();
	for(vector<MultiCommonMesh*>::size_type i = 0;i < sz;i++){
		m_MultiVec[i]->Transform(Vec,pCntlState,Data);
	}
}



/**************************************************************************
 virtual void SimpleCommonMesh::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Context& Data					//ユーザーデータ
 );
 用途: オブジェクトを描画（純粋仮想関数）
 戻り値: なし。
***************************************************************************/
void SimpleCommonMesh::Draw(DrawPacket& i_DrawPacket){
	LPDIRECT3DDEVICE9 pD3DDevice = i_DrawPacket.pD3DDevice ;
	if(!m_IsActive){
		//アクティブでなければ表示しない
		return;
	}
	//コモンメッシュの描画を呼ぶ
	DrawCommonMesh(pD3DDevice,m_WorldMatrix,m_Material,m_pTexture);
	//マルチメッシュ配列内の描画
	vector<MultiCommonMesh*>::size_type sz = m_MultiVec.size();
	for(vector<MultiCommonMesh*>::size_type i = 0;i < sz;i++){
		m_MultiVec[i]->Draw(i_DrawPacket);
	}
}
/**************************************************************************
	virtual void SimpleCommonMesh::DrawShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
	LPD3DXEFFECT	pEffect,			//エフェクトのポインタ
	D3DXMATRIX& mCameraView,			//カメラのビュー行列
	D3DXMATRIX& mCameraProj			//カメラのプロジェクション行列
	);
 用途: 影ボリュームを描画（仮想関数）
 戻り値: なし。
***************************************************************************/
void SimpleCommonMesh::DrawShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect,
	D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj){
	if(!m_IsActive){
		//アクティブでなければ表示しない
		return;
	}
	if(m_IsShadowActive){
		//影用の行列
		D3DXMATRIX mtAllMatrix;
		//行列を取り出す
		mtAllMatrix = m_WorldMatrix;
		mtAllMatrix._42 -=  0.02f;	//Y座標
		mtAllMatrix._11 *= 0.98f;	//Xスケール
		mtAllMatrix._22 *= 0.98f;	//Yスケール
		mtAllMatrix._33 *= 0.98f;	//Zスケール
		//コモンメッシュの影描画を呼ぶ
		DrawCommonShadowVolume(pD3DDevice,mtAllMatrix,pEffect,mCameraView,mCameraProj);
	}
	//マルチメッシュ配列内の影描画
	vector<MultiCommonMesh*>::size_type sz = m_MultiVec.size();
	for(vector<MultiCommonMesh*>::size_type i = 0;i < sz;i++){
		m_MultiVec[i]->DrawShadowVolume(pD3DDevice,pEffect,mCameraView,mCameraProj);
	}
}


/**************************************************************************
 class Polygon : public SimpleCommonMesh;
 用途: ポリゴンクラス
****************************************************************************/
/**************************************************************************
 void Polygon::CreateInctance(
 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9インターフェイスへのポインタ
 );
 用途: インスタンスの構築
 戻り値: なし。（例外がthrowされる）
***************************************************************************/
void Polygon::CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice){
    try{
		//直方体の作成
		//失敗したら例外がthrowされる
		if(m_pTexture){
			CreatePolygon(pD3DDevice,m_Length,m_Sides,true);
		}
		else{
			CreatePolygon(pD3DDevice,m_Length,m_Sides);
		}
    }
    catch(...){
        //コンストラクタ例外発生
        //再スロー
        throw;
    }
}
/**************************************************************************
 Polygon::Polygon(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9インターフェイスへのポインタ
	FLOAT Length,					//各面の長さ
	UINT Sides,						//ポリゴン面数
    D3DXVECTOR3& pos,                //位置
	D3DXVECTOR3& rot,				//回転(ラジアン単位)
    D3DCOLORVALUE& Diffuse,         //ディフューズ色
    D3DCOLORVALUE& Specular,            //スペキュラ色
    D3DCOLORVALUE& Ambient,          //アンビエント色
	bool IsShadowActive = false,	//影を描画するかどうか
	LPDIRECT3DTEXTURE9 pTexture = 0	//テクスチャを張るときは指定
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
Polygon::Polygon(LPDIRECT3DDEVICE9 pD3DDevice,
	FLOAT Length,UINT Sides,D3DXVECTOR3& pos,D3DXVECTOR3& rot,
    D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
	wiz::OBJID id ,
	bool IsShadowActive,LPDIRECT3DTEXTURE9 pTexture)
:SimpleCommonMesh(pos,rot,Diffuse,Specular,Ambient,id,IsShadowActive,pTexture),
m_Length(Length),
m_Sides(Sides)
{
	//インスタンスの構築
	//例外は呼び出した関数から投げられるので
	//ここには記述しなくて良い
	CreateInctance(pD3DDevice);
}
/**************************************************************************
 virtual Polygon::~Polygon();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Polygon::~Polygon(){
	//何もしない
	//オブジェクトの開放は親クラスで行なう
}
/**************************************************************************
	virtual void Polygon::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
 用途: デバイス喪失による再構築（仮想関数）
 戻り値: なし。（失敗時は例外をthrow）
 ＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
void Polygon::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//インスタンスの構築
	//例外は呼び出した関数から投げられるので
	//ここには記述しなくて良い
	CreateInctance(pD3DDevice);
	//親クラスのChangeDeviceを呼ぶ（マルチメッシュ配列用）
	SimpleCommonMesh::ChangeDevice(pD3DDevice);
}

/**************************************************************************
 class Box : public SimpleCommonMesh;
 用途: ボックスクラス
****************************************************************************/
/**************************************************************************
 void Box::CreateInctance(
 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9インターフェイスへのポインタ
 );
 用途: インスタンスの構築
 戻り値: なし。（例外がthrowされる）
***************************************************************************/
void Box::CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice){
    try{
		//直方体の作成
		//失敗したら例外がthrowされる
		if(m_pTexture){
			CreateBox(pD3DDevice,m_Size,true,m_TexturePtn);
		}
		else{
			CreateBox(pD3DDevice,m_Size);
		}
    }
    catch(...){
        //コンストラクタ例外発生
        //再スロー
        throw;
    }
}

/**************************************************************************
 Box::Box(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9インターフェイスへのポインタ
    D3DXVECTOR3& size,               //大きさ
    D3DXVECTOR3& pos,                //位置
	D3DXVECTOR3& rot,				//回転(ラジアン単位)
    D3DCOLORVALUE& Diffuse,         //ディフューズ色
    D3DCOLORVALUE& Specular,            //スペキュラ色
    D3DCOLORVALUE& Ambient,          //アンビエント色
	bool IsShadowActive = false,	//影を描画するかどうか
	LPDIRECT3DTEXTURE9 pTexture = 0,	//テクスチャを張るときは指定
	int TexturePtn = PtnUV_1_1		//テクスチャのパターン
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
Box::Box(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& size,D3DXVECTOR3& pos,D3DXVECTOR3& rot,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		wiz::OBJID id,
		bool IsShadowActive,LPDIRECT3DTEXTURE9 pTexture,int TexturePtn)
:SimpleCommonMesh(pos,rot,Diffuse,Specular,Ambient,id,IsShadowActive,pTexture),
m_Size(size),
m_TexturePtn(TexturePtn)
{
	//インスタンスの構築
	//例外は呼び出した関数から投げられるので
	//ここには記述しなくて良い
	CreateInctance(pD3DDevice);
}
/**************************************************************************
 Box::~Box();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Box::~Box(){
	//何もしない
	//オブジェクトの開放は親クラスで行なう
}

/**************************************************************************
	virtual void Box::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
 用途: デバイス喪失による再構築（仮想関数）
 戻り値: なし。（失敗時は例外をthrow）
 ＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
void Box::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//インスタンスの構築
	//例外は呼び出した関数から投げられるので
	//ここには記述しなくて良い
	CreateInctance(pD3DDevice);
	//親クラスのChangeDeviceを呼ぶ（マルチメッシュ配列用）
	SimpleCommonMesh::ChangeDevice(pD3DDevice);
}

/**************************************************************************
 class ParallelBox : public Box;
 用途: 軸に平行な直方体クラス
****************************************************************************/
/**************************************************************************
 ParallelBox::ParallelBox(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9インターフェイスへのポインタ
    D3DXVECTOR3& size,               //大きさ
    D3DXVECTOR3& pos,                //位置
    D3DCOLORVALUE& Diffuse,         //ディフューズ色
    D3DCOLORVALUE& Specular,            //スペキュラ色
    D3DCOLORVALUE& Ambient,          //アンビエント色
	bool IsShadowActive = false,	//影を描画するかどうか
	LPDIRECT3DTEXTURE9 pTexture = 0,	//テクスチャを張るときは指定
	int TexturePtn = PtnUV_1_1		//テクスチャのパターン
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
ParallelBox::ParallelBox(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& size,D3DXVECTOR3& pos,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		wiz::OBJID id,
		bool IsShadowActive,LPDIRECT3DTEXTURE9 pTexture,int TexturePtn)
:Box(pD3DDevice,size,pos,
D3DXVECTOR3(0,0,0),	//回転のみ0にする
Diffuse,Specular,Ambient,id,
IsShadowActive,pTexture,TexturePtn)
{
	//何もしない
}
/**************************************************************************
 virtual ~ParallelBox();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
ParallelBox::~ParallelBox(){
	//何もしない
}

/**************************************************************************
	void ParallelBox::GetAABB(
		AABB& Tgt	//矩形変数
	);
 用途: 現在矩形を得る
 戻り値: なし。
 ＊現在の矩形を代入する
***************************************************************************/
void ParallelBox::GetAABB(AABB& Tgt){
	D3DXVECTOR3 Pos = m_BasePos + m_Pos;
	FLOAT xh = m_Size.x * m_BaseScale.x / 2.0f;
	FLOAT yh = m_Size.y * m_BaseScale.y / 2.0f;
	FLOAT zh = m_Size.z * m_BaseScale.z / 2.0f;
	//底辺
	Tgt.m_Min.x = Pos.x - xh;
	Tgt.m_Max.x = Pos.x + xh;

	Tgt.m_Min.y = Pos.y - yh;
	Tgt.m_Max.y = Pos.y + yh;

	Tgt.m_Min.z = Pos.z - zh;
	Tgt.m_Max.z = Pos.z + zh;
}



/**************************************************************************
 class Sphere : public SimpleCommonMesh;
 用途: 球クラス
****************************************************************************/
/**************************************************************************
 void Sphere::CreateInctance(
 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9インターフェイスへのポインタ
 );
 用途: インスタンスの構築
 戻り値: なし。（例外がthrowされる）
***************************************************************************/
void Sphere::CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice){
    try{
		//球の作成
		//失敗したら例外がthrowされる
		if(m_pTexture){
			CreateSphere(pD3DDevice,m_Radius,true,m_Slices,m_Stacks);
		}
		else{
			CreateSphere(pD3DDevice,m_Radius,false,m_Slices,m_Stacks);
		}
    }
    catch(...){
        //コンストラクタ例外発生
        //再スロー
        throw;
    }
}

/**************************************************************************
 Sphere::Sphere(
    LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9インターフェイスへのポインタ
    FLOAT radius,                   //半径の大きさ
    D3DXVECTOR3& pos,                //最初の位置
	D3DXVECTOR3& rot,				//回転(ラジアン単位)
    D3DCOLORVALUE& Diffuse,         //ディフューズ色
    D3DCOLORVALUE& Specular,            //スペキュラ色
    D3DCOLORVALUE& Ambient,          //アンビエント色
	bool IsShadowActive = false,	//影を描画するかどうか
	LPDIRECT3DTEXTURE9 pTexture = 0,	//テクスチャを張るときは指定
	UINT Slices = 18,	//主軸の回転スライス数
	UINT Stacks = 18	//主軸に沿ったスライス数
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
 Sphere::Sphere(LPDIRECT3DDEVICE9 pD3DDevice,
		FLOAT radius,D3DXVECTOR3& pos,D3DXVECTOR3& rot,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		wiz::OBJID id,
		bool IsShadowActive,LPDIRECT3DTEXTURE9 pTexture,
		UINT Slices,UINT Stacks)
:SimpleCommonMesh(pos,rot,Diffuse,Specular,Ambient,id,IsShadowActive,pTexture),
m_Radius(radius),
m_Slices(Slices),
m_Stacks(Stacks)
{
	//インスタンスの構築
	//例外は呼び出した関数から投げられるので
	//ここには記述しなくて良い
	CreateInctance(pD3DDevice);
}
/**************************************************************************
 virtual Sphere::~Sphere();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Sphere::~Sphere(){
	//何もしない
	//オブジェクトの開放は親クラスで行なう
}

/**************************************************************************
virtual void Sphere::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
 用途: デバイス喪失による再構築（仮想関数）
 戻り値: なし。
***************************************************************************/
void Sphere::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//インスタンスの構築
	//例外は呼び出した関数から投げられるので
	//ここには記述しなくて良い
	CreateInctance(pD3DDevice);
	//親クラスのChangeDeviceを呼ぶ（マルチメッシュ配列用）
	SimpleCommonMesh::ChangeDevice(pD3DDevice);
}


/**************************************************************************
 class Cylinder : public SimpleCommonMesh;
 用途: シリンダークラス
****************************************************************************/
/**************************************************************************
 void Cylinder::CreateInctance(
 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9インターフェイスへのポインタ
 );
 用途: インスタンスの構築
 戻り値: なし。（例外がthrowされる）
***************************************************************************/
void Cylinder::CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice){
    try{
		//シリンダーの作成
		//失敗したら例外がthrowされる
		if(m_pTexture){
			CreateCylinder(pD3DDevice,m_Radius1,m_Radius2,m_Length,true,m_Slices,m_Stacks);
		}
		else{
			CreateCylinder(pD3DDevice,m_Radius1,m_Radius2,m_Length,false,m_Slices,m_Stacks);
		}
    }
    catch(...){
        //コンストラクタ例外発生
        //再スロー
        throw;
    }
}

/**************************************************************************
 Cylinder::Cylinder(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9インターフェイスへのポインタ
    FLOAT Radius1,                   //z 軸の負の側の面の半径。値は 0.0f 以上である必要がある。 
    FLOAT Radius2,                   //z 軸の正の側の面の半径。値は 0.0f 以上である必要がある。
	FLOAT Length,					//z 軸方向の円柱の長さ。
    D3DXVECTOR3& pos,                //最初の位置
	D3DXVECTOR3& rot,				//回転(ラジアン単位)
    D3DCOLORVALUE& Diffuse,         //ディフューズ色
    D3DCOLORVALUE& Specular,            //スペキュラ色
    D3DCOLORVALUE& Ambient,          //アンビエント色
	bool IsShadowActive = false,	//影を描画するかどうか
	LPDIRECT3DTEXTURE9 pTexture = 0,	//テクスチャを張るときは指定
	UINT Slices = 18,		//主軸を回転軸としたスライスの数。
	UINT Stacks = 18		//主軸に沿ったスタック数。
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
 Cylinder::Cylinder(LPDIRECT3DDEVICE9 pD3DDevice,
	 FLOAT Radius1,FLOAT Radius2,FLOAT Length,
	 D3DXVECTOR3& pos,D3DXVECTOR3& rot,
	 D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
	 wiz::OBJID id,
	 bool IsShadowActive,LPDIRECT3DTEXTURE9 pTexture,
	 UINT Slices,UINT Stacks)
:SimpleCommonMesh(pos,rot,Diffuse,Specular,Ambient,id,IsShadowActive,pTexture),
m_Radius1(Radius1),
m_Radius2(Radius2),
m_Length(Length),
m_Slices(Slices),
m_Stacks(Stacks)
{
	//インスタンスの構築
	//例外は呼び出した関数から投げられるので
	//ここには記述しなくて良い
	CreateInctance(pD3DDevice);
}
/**************************************************************************
 virtual Cylinder::~Cylinder();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Cylinder::~Cylinder(){
	//何もしない
	//オブジェクトの開放は親クラスで行なう
}
/**************************************************************************
	virtual void Cylinder::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
 用途: デバイス喪失による再構築（仮想関数）
 戻り値: なし。
***************************************************************************/
void Cylinder::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//インスタンスの構築
	//例外は呼び出した関数から投げられるので
	//ここには記述しなくて良い
	CreateInctance(pD3DDevice);
	//親クラスのChangeDeviceを呼ぶ（マルチメッシュ配列用）
	SimpleCommonMesh::ChangeDevice(pD3DDevice);
}

/**************************************************************************
 class Torus : public SimpleCommonMesh;
 用途: トーラスクラス
****************************************************************************/
/**************************************************************************
 void Torus::CreateInctance(
 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9インターフェイスへのポインタ
 );
 用途: インスタンスの構築
 戻り値: なし。（例外がthrowされる）
***************************************************************************/
void Torus::CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice){
    try{
		//トーラスの作成
		//失敗したら例外がthrowされる
		if(m_pTexture){
			CreateTorus(pD3DDevice,m_InnerRadius,m_OuterRadius,true,m_Sides,m_Rings);
		}
		else{
			CreateTorus(pD3DDevice,m_InnerRadius,m_OuterRadius,false,m_Sides,m_Rings);
		}
    }
    catch(...){
        //コンストラクタ例外発生
        //再スロー
        throw;
    }
}

/**************************************************************************
 Torus::Torus(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9インターフェイスへのポインタ
    FLOAT InnerRadius,              //ドーナッツの半径
    FLOAT OuterRadius,              //原点からドーナッツ中心までの半径
    D3DXVECTOR3& pos,                //最初の位置
	D3DXVECTOR3& rot,				//回転(ラジアン単位)
    D3DCOLORVALUE& Diffuse,         //ディフューズ色
    D3DCOLORVALUE& Specular,            //スペキュラ色
    D3DCOLORVALUE& Ambient,          //アンビエント色
	bool IsShadowActive = false,	//影を描画するかどうか
	LPDIRECT3DTEXTURE9 pTexture = 0,	//テクスチャを張るときは指定
	UINT Sides = 18,	//横断面の辺の数。値は 3 以上である必要がある。
	UINT Rings = 18		//トーラスを構成する環の数。値は 3 以上である必要がある。     
	);
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
Torus::Torus(
		LPDIRECT3DDEVICE9 pD3DDevice,
		FLOAT InnerRadius,FLOAT OuterRadius,D3DXVECTOR3& pos,D3DXVECTOR3& rot,
		D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		wiz::OBJID id,
		bool IsShadowActive,LPDIRECT3DTEXTURE9 pTexture,
		UINT Sides,UINT Rings)
:SimpleCommonMesh(pos,rot,Diffuse,Specular,Ambient,id,IsShadowActive,pTexture),
m_InnerRadius(InnerRadius),
m_OuterRadius(OuterRadius),
m_Sides(Sides),
m_Rings(Rings)
{
	//インスタンスの構築
	//例外は呼び出した関数から投げられるので
	//ここには記述しなくて良い
	CreateInctance(pD3DDevice);
}
/**************************************************************************
 virtual Torus::~Torus();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Torus::~Torus(){
	//何もしない
	//オブジェクトの開放は親クラスで行なう
}

/**************************************************************************
virtual void Torus::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
 用途: デバイス喪失による再構築（仮想関数）
 戻り値: なし。
***************************************************************************/
void Torus::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//インスタンスの構築
	//例外は呼び出した関数から投げられるので
	//ここには記述しなくて良い
	CreateInctance(pD3DDevice);
	//親クラスのChangeDeviceを呼ぶ（マルチメッシュ配列用）
	SimpleCommonMesh::ChangeDevice(pD3DDevice);
}


/**************************************************************************
 class SimpleCommonMeshGroup : public Object;
 用途: グループ化されたコモンメッシュをさらにグループ化する
 ＊派生クラスとして作成するのではなく、
 SimpleCommonMeshを包含関係にて取り込む
****************************************************************************/
/**************************************************************************
 SimpleCommonMeshGroup::SimpleCommonMeshGroup(SimpleCommonMesh* pSimpleCommonMesh)
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrowする）
 ＊あらかじめ作成したシンプルコモンメッシュを渡す。

***************************************************************************/
SimpleCommonMeshGroup::SimpleCommonMeshGroup(SimpleCommonMesh* pSimpleCommonMesh,wiz::OBJID id )
:m_pSimpleCommonMesh(pSimpleCommonMesh)
,Object(OBJID_UNK)
{
}
/**************************************************************************
 virtual SimpleCommonMeshGroup::~SimpleCommonMeshGroup();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
SimpleCommonMeshGroup::~SimpleCommonMeshGroup(){
	//グループ配列のクリア
	SafeDeletePointerContainer(m_ItemVec);
	//SimpleCommonMeshのクリア
	SafeDelete(m_pSimpleCommonMesh);
}
/**************************************************************************
	virtual void SimpleCommonMeshGroup::ReleaseObj();
 用途: デバイス喪失によるリソースの開放（仮想関数）
 戻り値: なし。
 ＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
void SimpleCommonMeshGroup::ReleaseObj(){
	if(m_pSimpleCommonMesh){
		m_pSimpleCommonMesh->ReleaseObj();
	}
}
/**************************************************************************
	void SimpleCommonMeshGroup::SetSimpleCommonMesh(SimpleCommonMesh* pSimpleCommonMesh);
 用途: シンプルコモンメッシュの設定
 戻り値: なし。
***************************************************************************/
void SimpleCommonMeshGroup::SetSimpleCommonMesh(SimpleCommonMesh* pSimpleCommonMesh){
	m_pSimpleCommonMesh = pSimpleCommonMesh;
}

/**************************************************************************
 const SimpleCommonMesh* SimpleCommonMeshGroup::GetSimpleCommonMesh() const;
 用途: 基準となるコモンメッシュを返す
 戻り値: 基準となるコモンメッシュのポインタ
***************************************************************************/
const SimpleCommonMesh* SimpleCommonMeshGroup::GetSimpleCommonMesh() const{
	return m_pSimpleCommonMesh;
}


/**************************************************************************
	size_t SimpleCommonMeshGroup::AddItem(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
 用途: アイテムの登録
 戻り値: 追加したインデックス
***************************************************************************/
size_t SimpleCommonMeshGroup::AddItem(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
	GroupItem* pItem = 0;
	try{
		pItem = new GroupItem;
		//シンプルコモンメッシュがあれば、そこからマテリアルを取得
		if(m_pSimpleCommonMesh){
			m_pSimpleCommonMesh->GetMaterial(pItem->m_Material);
		}
		else{
			D3DCOLORVALUE def = {0.0f,0.0f,0.0f,0.0f};
			pItem->m_Material.Diffuse = def;
			pItem->m_Material.Specular = def;
			pItem->m_Material.Ambient = def;
		}
		pItem->m_Pos = Pos;
		//回転
		D3DXQuaternionIdentity(&pItem->m_Qt);
		D3DXQuaternionRotationYawPitchRoll(&pItem->m_Qt,
			Rot.y,Rot.x,Rot.z);
		//正規化
		D3DXQuaternionNormalize(&pItem->m_Qt,&pItem->m_Qt);
		//アイテムの追加
		size_t ret = m_ItemVec.size();
		m_ItemVec.push_back(pItem);
		//追加したインデックスは直前の項目数になる
		return ret;
	}
	catch(...){
		SafeDelete(pItem);
		throw;
	}
}
/**************************************************************************
 void SimpleCommonMeshGroup::GetItemMaterial(
	size_t Index,	//取得するインデックス
	D3DMATERIAL9& Material	//現在のマテリアル
  );
 用途: マテリアルを取得する
 戻り値: なし（MaterialにIndexのマテリアルを返す）
***************************************************************************/
void SimpleCommonMeshGroup::GetItemMaterial(size_t Index,D3DMATERIAL9& Material){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		 Material = m_ItemVec[Index]->m_Material;
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"SimpleCommonMeshGroup::GetItemMaterial()");
	}
}
/**************************************************************************
 void SimpleCommonMeshGroup::SetItemMaterial(
	size_t Index,	//設定するインデックス
	D3DMATERIAL9& Material	//設定するマテリアル
  );
 用途: マテリアルを設定する
 戻り値: なし
***************************************************************************/
void SimpleCommonMeshGroup::SetItemMaterial(size_t Index,D3DMATERIAL9& Material){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_Material = Material;
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"SimpleCommonMeshGroup::SetItemMaterial()");
	}
}

/**************************************************************************
 void SimpleCommonMeshGroup::GetItemLocalPosQt(
	size_t Index,	//取得するインデックス
	D3DXVECTOR3& Pos,	//現在の相対位置
	D3DXQUATERNION& Qt	//現在の相対回転
  );
 用途: 相対値を取得する(クオータニオン版)
 戻り値: なし
***************************************************************************/
void SimpleCommonMeshGroup::GetItemLocalPosQt(size_t Index,
	D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		 Pos = m_ItemVec[Index]->m_Pos;
		 Qt = m_ItemVec[Index]->m_Qt;
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"SimpleCommonMeshGroup::GetItemLocalPosQt()");
	}
}
/**************************************************************************
 void SimpleCommonMeshGroup::GetItemLocalPosRot(
	size_t Index,	//取得するインデックス
	D3DXVECTOR3& Pos,	//現在の相対位置
	D3DXVECTOR3& Rot	//現在の回転
  );
 用途: 相対値を取得する
 戻り値: なし
***************************************************************************/
void SimpleCommonMeshGroup::GetItemLocalPosRot(size_t Index,
	D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		 Pos = m_ItemVec[Index]->m_Pos;
		//正規化
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_Qt,&m_ItemVec[Index]->m_Qt);
		//行列に取り出す
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		D3DXMatrixRotationQuaternion(&mt,&m_ItemVec[Index]->m_Qt);
		//行列から回転部分を取り出す
		Rot.x = atan2(mt._32,mt._33);
		Rot.y = asin(-mt._13);
		Rot.z = atan2(mt._21,mt._11);
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"SimpleCommonMeshGroup::GetItemLocalPosRot()");
	}

}
/**************************************************************************
 void SimpleCommonMeshGroup::SetItemLocalPosQt(
	size_t Index,	//インデックス
	D3DXVECTOR3& Pos,	//相対位置
	D3DXQUATERNION& Qt	//相対回転
  );
 用途: 相対値を設定する(クオータニオン版)
 戻り値: なし
***************************************************************************/
void SimpleCommonMeshGroup::SetItemLocalPosQt(size_t Index,
	D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		//位置
		 m_ItemVec[Index]->m_Pos = Pos;
		//回転
		 m_ItemVec[Index]->m_Qt = Qt;
		//正規化
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_Qt,&m_ItemVec[Index]->m_Qt);
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"SimpleCommonMeshGroup::SetItemLocalPosQt()");
	}
}

/**************************************************************************
 void SimpleCommonMeshGroup::SetItemLocalPosRot(
	size_t Index,	//インデックス
	D3DXVECTOR3& Pos,	//相対位置
	D3DXVECTOR3& Rot	//相対回転
  );
 用途: 相対値を設定する(クオータニオン版)
 戻り値: なし
***************************************************************************/
 void SimpleCommonMeshGroup::SetItemLocalPosRot(size_t Index,
	 D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
    //指定の配置オブジェクトへの適用
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		//位置
		m_ItemVec[Index]->m_Pos = Pos;
		//回転
		D3DXQuaternionIdentity(&m_ItemVec[Index]->m_Qt);
		D3DXQuaternionRotationYawPitchRoll(&m_ItemVec[Index]->m_Qt,
			Rot.y,Rot.x,Rot.z);
		//正規化
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_Qt,&m_ItemVec[Index]->m_Qt);
	}
	else{
		throw BaseException(L"インデックスが範囲外です。",
			L"SimpleCommonMeshGroup::SetItemLocalPosRot()");
	}
}



/**************************************************************************
	virtual void SimpleCommonMeshGroup::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
 用途: デバイス喪失による再構築（仮想関数）
 戻り値: なし。
 ＊デバイスが喪失したときに最構築時に呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
void SimpleCommonMeshGroup::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	if(m_pSimpleCommonMesh){
		((Object*)m_pSimpleCommonMesh)->ChangeDevice(pD3DDevice);
	}
}
/**************************************************************************
 virtual void SimpleCommonMeshGroup::Transform(
 vector<Object*>& Vec,            //オブジェクトの配列
 const CONTROLER_STATE* pCntlState,	//コントローラの状態
 Context& Data					//ユーザーデータ
 );
 用途: オブジェクトを変化させる（仮想関数）
 戻り値: なし。
***************************************************************************/
void SimpleCommonMeshGroup::Transform(vector<Object*>& Vec,
		const CONTROLER_STATE* pCntlState,Context& Data){
}

/**************************************************************************
 virtual void SimpleCommonMeshGroup::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Context& Data					//ユーザーデータ
 );
 用途: オブジェクトを描画（純粋仮想関数）
 戻り値: なし。
***************************************************************************/
void SimpleCommonMeshGroup::Draw(DrawPacket& i_DrawPacket){
	 if(!m_pSimpleCommonMesh){
		 return;
	 }
	GroupItem TmpItem;
	//ローカル変換をテンポラリオブジェクトに取得
	m_pSimpleCommonMesh->GetMaterial(TmpItem.m_Material);
	m_pSimpleCommonMesh->GetLocalPosQt(TmpItem.m_Pos,TmpItem.m_Qt);
    //グループ配列の描画
    vector<GroupItem*>::size_type sz = m_ItemVec.size();
    for(vector<GroupItem*>::size_type i = 0;i < sz;i++){
		m_pSimpleCommonMesh->SetMaterial(m_ItemVec[i]->m_Material);
		m_pSimpleCommonMesh->MoveAtPosQt(m_ItemVec[i]->m_Pos,m_ItemVec[i]->m_Qt);
		m_pSimpleCommonMesh->CalcWorldMatrix();
		//描画
		m_pSimpleCommonMesh->Draw(i_DrawPacket);
	}
	//元に戻す
	m_pSimpleCommonMesh->SetMaterial(TmpItem.m_Material);
	m_pSimpleCommonMesh->MoveAtPosQt(TmpItem.m_Pos,TmpItem.m_Qt);
}
/**************************************************************************
	virtual void SimpleCommonMeshGroup::DrawShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
	LPD3DXEFFECT	pEffect,			//エフェクトのポインタ
	D3DXMATRIX& mCameraView,			//カメラのビュー行列
	D3DXMATRIX& mCameraProj			//カメラのプロジェクション行列
	);
 用途: 影ボリュームを描画（仮想関数）
 戻り値: なし。
***************************************************************************/
void SimpleCommonMeshGroup::DrawShadowVolume(
	LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect,
	D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj){
	 if(!m_pSimpleCommonMesh){
		 return;
	 }
	GroupItem TmpItem;
	//ローカル変換をテンポラリオブジェクトに取得
	m_pSimpleCommonMesh->GetMaterial(TmpItem.m_Material);
	m_pSimpleCommonMesh->GetLocalPosQt(TmpItem.m_Pos,TmpItem.m_Qt);
    //グループ配列の描画
    vector<GroupItem*>::size_type sz = m_ItemVec.size();
    for(vector<GroupItem*>::size_type i = 0;i < sz;i++){
		m_pSimpleCommonMesh->SetMaterial(m_ItemVec[i]->m_Material);
		m_pSimpleCommonMesh->MoveAtPosQt(m_ItemVec[i]->m_Pos,m_ItemVec[i]->m_Qt);
		m_pSimpleCommonMesh->CalcWorldMatrix();
		//描画
		m_pSimpleCommonMesh->DrawShadowVolume(pD3DDevice,pEffect,mCameraView,mCameraProj);
	}
	//元に戻す
	m_pSimpleCommonMesh->SetMaterial(TmpItem.m_Material);
	m_pSimpleCommonMesh->MoveAtPosQt(TmpItem.m_Pos,TmpItem.m_Qt);
}


}//end of namespace	baseobject.
}//end of namespace	wiz.