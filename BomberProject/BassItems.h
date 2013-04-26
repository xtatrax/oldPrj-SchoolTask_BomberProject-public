////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：BassItems.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包ﾃﾞｰﾀと備考	：ゲームのベースになるアイテム群の宣言
//					▼
//	プリミティブ周辺を山ノ井先生のソースを参考に大改造する! 
//
//	namespace wiz;
//		union Color                :				# DWORD表記カラーを使いやすくしてみた(使いやすいと思うよ多分…)動作
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
#pragma once
#include "Object.h"
#include "AnimationModelClass/AnimationModelClass.h"
#include "TL-String.h"
namespace wiz {



//**************************************************************************
// class Motion;
//
// 担当者  : 鴫原 徹
// 用途    : モーション
//**************************************************************************
class Motion{
public:
	virtual void Update(D3DXVECTOR3& i_vScale, D3DXVECTOR3& i_vRot, D3DXVECTOR3& i_vPos) = 0;
};

namespace baseobject{

//**************************************************************************
// class Camera : public Object;
//
// 担当者  : (山ノ井先生のひな形より)
// 用途    : カメラクラス
//**************************************************************************
class Camera : public Object{
    D3DXMATRIX  m_View;     // カメラの配置
    D3DXVECTOR3 m_Eye;      //カメラの位置
    D3DXVECTOR3 m_At;       //直視点
    FLOAT m_Near;           //射影の手前側の距離
    FLOAT m_Far;            //射影の奥側の距離
    FLOAT m_FovY;           //射影角度
	//float CameraKyori;
	bool CameraFlg;
public:
/////////////////// ////////////////////
//// 関数名     ：Camera(D3DXVECTOR3& Eye,D3DXVECTOR3& At,FLOAT Near,FLOAT Far,FLOAT FovY)
//// カテゴリ   ：コンストラクタ
//// 用途       ：カメラの生成時処理
//// 引数       ：  D3DXVECTOR3& Eye,   //カメラの位置
////            ：  D3DXVECTOR3& At,    //直視点
////            ：  FLOAT Near,         //射影の手前側の距離
////            ：  FLOAT Far,          //射影の奥側の距離
////            ：  FLOAT FovY          //射影角度
//// 戻値       ：なし
//// 担当者     ：(山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
	Camera(D3DXVECTOR3& Eye,D3DXVECTOR3& At,FLOAT Near,FLOAT Far,FLOAT FovY,wiz::OBJID id = OBJID_SYS_CAMERA);
/////////////////// ////////////////////
//// 関数名     ：~Camera()
//// カテゴリ   ：デストラクタ
//// 用途       ：カメラの破棄時処理
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：(山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
    virtual ~Camera();
/////////////////// ////////////////////
//// 関数名     ：virtual void Update( LPDIRECT3DDEVICE9 pD3DDevice
////            ：  vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& i_DrawPacket.pCommand)
//// カテゴリ   ：仮想関数
//// 用途       ：カメラを更新
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,				//オブジェクトの配列
////            ：  const CONTROLER_STATE* pCntlState	//コントローラのステータス
//// 戻値       ：なし
//// 担当者     ：
//// 備考       ：Objectクラスの純粋仮想関数
////            ：
////
    virtual void Update(UpdatePacket& i_UpdatePacket);

/////////////////// ////////////////////
//// 関数名     ：void Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// カテゴリ   ：仮想関数
//// 用途       ：カメラを設置
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,				//オブジェクトの配列
//// 戻値       ：なし
//// 担当者     ：(山ノ井先生のひな形より)
//// 備考       ：Objectクラスの純粋仮想関数
////            ：
////
    virtual void Draw(DrawPacket& i_DrawPacket);

/////////////////// ////////////////////
//// 関数名     ：void setTarget(D3DXVECTOR3 vPos)
//// カテゴリ   ：セッター
//// 用途       ：視点を設定
//// 引数       ：  D3DXVECTOR3 vPos		//	視点
//// 戻値       ：なし
//// 担当者     ：(山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
	void setTarget(D3DXVECTOR3 vPos,D3DXVECTOR3& vCPos/*,D3DXVECTOR3& vCEPos*/);
/////////////////// ////////////////////
//// 関数名     ：D3DXVECTOR3 getEye()
//// カテゴリ   ：ゲッター
//// 用途       ：カメラ座標を獲得
//// 引数       ：  D3DXVECTOR3 vPos		//	視点
//// 戻値       ：カメラの座標
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	D3DXVECTOR3 getEye(){return m_Eye;};
};


//**************************************************************************
// class Guide : public Object;
//
// 担当者  ; (山ノ井先生のひな形より)
// 用途    : ガイドクラス（x、y、z方向に伸びるガイド線）
//**************************************************************************
class Guide : public Object{
    IDirect3DVertexBuffer9* m_pVB;
    //クラス内構造体
    //ここでしか使用しないので、内部に持つ
    struct CUSTOMVERTEX
    {
        D3DXVECTOR3 vec;
        DWORD color;
    };
public:
/////////////////// ////////////////////
//// 関数名     ：Guide(LPDIRECT3DDEVICE9 pD3DDevice)
//// カテゴリ   ：コンストラクタ
//// 用途       ：ガイドライン生成時処理
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9インターフェイスへのポインタ
//// 戻値       ：なし（失敗時は例外をthrow）
//// 担当者     ：(山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
	Guide(LPDIRECT3DDEVICE9 pD3DDevice,wiz::OBJID id = OBJID_SYS_GUIDELINE);
/////////////////// ////////////////////
//// 関数名     ：Guide::~Guide()
//// カテゴリ   ：デストラクタ
//// 用途       ：ガイドライン破棄時処理
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：(山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
    virtual ~Guide();
/////////////////// ////////////////////
//// 関数名     ：void Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// カテゴリ   ：仮想関数
//// 用途       ：ガイドラインを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,				//オブジェクトの配列
//// 戻値       ：なし
//// 担当者     ：(山ノ井先生のひな形より)
//// 備考       ：Objectクラスの純粋仮想関数
////            ：
////
    virtual void Draw(DrawPacket& i_DrawPacket) ;
};



/**************************************************************************
 class CommonMesh : public Object;
 用途: コモンメッシュクラス
 (山ノ井先生のひな形より)
****************************************************************************/
class CommonMesh {
public:
	//Boxのテクスチャパターン
	//パターンは呼び出し側で指定するので、これだけpublicにする
	enum {PtnUV_1_1 = 0, PtnUV_6_1,PtnUV_YWrap,PtnUV_ZWrap};
protected:
    //メッシュ
    LPD3DXMESH m_pMesh;
	//サブセット
	DWORD        m_dwDrawSubset;
	//マトリックス
	D3DXMATRIX	 m_mMatrix ;
	//マテリアル
	D3DMATERIAL9 m_Material ;
private:
	//直接構築できないように、
	//メンバを基本的にprivateにする
	//影ボリュームクラス
	//ShadowVolume* m_pShadowVolume;
	//ラッピングテクスチャかどうか
	bool m_bWrapMode;
	//ワイアーフレーム表示するかどうか
	bool m_bWireFrame;
/**************************************************************************
 struct  CommonMeshVertex;
 用途: CommonMeshのテクスチャがある場合の頂点フォーマットの定義
	D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1
	を構造体化している
****************************************************************************/
	struct  CommonMeshVertex{
		D3DXVECTOR3 vec;	//頂点
		D3DXVECTOR3 normal;	//法線
		FLOAT       tu,tv;	//UV値
	};
	//CommonMesh用のFVFをDirectXAPIに渡すときのパラメータ
	enum { CommonMeshFVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
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
	static void PolygonVec2UV(float x,float y,float z,float r,float& u,float& v);
/**************************************************************************
 static void BoxVecNomal2UV(
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
	static void BoxVecNomal2UV(D3DXVECTOR3 vec,D3DXVECTOR3 normal,float& u,float& v);
/**************************************************************************
 static void BoxVecNomal2UV_6_1(
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
	static void BoxVecNomal2UV_6_1(D3DXVECTOR3 vec,D3DXVECTOR3 normal,float& u,float& v);
/**************************************************************************
 static void SphereVec2UV(
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
	static void SphereVec2UV(float x,float y,float z,float r,float& u,float& v);
/**************************************************************************
 static void WrapVec2UV(
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
	static void WrapVec2UV(float x,float y,float z,float& u,float& v,bool IsYWrap = true);
/**************************************************************************
 static void TorusVec2UV(
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
	static void TorusVec2UV(float x,float y,float z,float inr,float outr,float& u,float& v);
protected:
	//以下は派生クラスから呼ばれる
/**************************************************************************
 CommonMesh();
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
	CommonMesh();
/**************************************************************************
 CommonMesh(D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient);
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
	CommonMesh(D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient);
/**************************************************************************
 virtual ~CommonMesh();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~CommonMesh();
/**************************************************************************
void CreateBox(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	D3DXVECTOR3& size,				//サイズ
	bool bTextureActive = false,		//テクスチャがアクティブかどうか
	int TexturePtn = PtnUV_1_1	//テクスチャが有効な場合のパターン
);
 用途:Boxオブジェクトの構築
 戻り値: なし（例外をthrow）
***************************************************************************/
	void CreateBox(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& size,
		bool bTextureActive = false,int TexturePtn = PtnUV_1_1);
/**************************************************************************
void CreateSphere(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	FLOAT radius,					//半径
	bool bTextureActive = false,		//テクスチャがアクティブかどうか
	UINT Slices = 18,	//主軸の回転スライス数
	UINT Stacks = 18	//主軸に沿ったスライス数
);
 用途:球オブジェクトの構築
 戻り値: なし（例外をthrow）
***************************************************************************/
	void CreateSphere(LPDIRECT3DDEVICE9 pD3DDevice,FLOAT radius,
		bool bTextureActive = false,UINT Slices = 18,UINT Stacks = 18);
/**************************************************************************
void CreateTorus(
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
	void CreateTorus(LPDIRECT3DDEVICE9 pD3DDevice,
			FLOAT InnerRadius,FLOAT OuterRadius,bool bTextureActive = false,
			UINT Sides = 18,UINT Rings = 18);
/**************************************************************************
void CreateCylinder(
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
	void CreateCylinder(LPDIRECT3DDEVICE9 pD3DDevice,
			FLOAT Radius1,FLOAT Radius2,FLOAT Length,bool bTextureActive = false,
			UINT Slices = 18,UINT Stacks = 18);
/**************************************************************************
void CreatePolygon(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	FLOAT Length,					//各面の長さ。
	UINT Sides,						//ポリゴンの面数。値は 3 以上である必要がある。
	bool bTextureActive = false,	//テクスチャがアクティブかどうか
);
 用途:ポリゴンオブジェクトの構築
 戻り値: なし（例外をthrow）
***************************************************************************/
void CreatePolygon(LPDIRECT3DDEVICE9 pD3DDevice,
	FLOAT Length,UINT Sides,bool bTextureActive = false);

/////////////////// ////////////////////
//// 関数名     ：void CommonMesh::Draw( DrawPacket& i_DrawPacket )
//// カテゴリ   ：仮想関数
//// 用途       ：メッシュを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,				//オブジェクトの配列
//// 戻値       ：無し
//// 担当者     ： (山ノ井先生のひな形より)
//// 備考       ：Objectクラスの純粋仮想関数
////            ：
////
void Draw(DrawPacket& i_DrawPacket);
/**************************************************************************
 void DrawCommonMesh(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
	D3DXMATRIX& Matrix,			//変換行列
	D3DMATERIAL9& Material,		//マティリアル
	Texture* pTexture = 0			//テクスチャ
 );
 用途: コモンオブジェクトを描画（派生クラスから呼ばれる）
 戻り値: なし。
***************************************************************************/
	 void DrawCommonMesh(LPDIRECT3DDEVICE9 pD3DDevice,D3DXMATRIX& Matrix,
		D3DMATERIAL9& Material,LPDIRECT3DTEXTURE9 pTexture = 0);
/**************************************************************************
	void DrawCommonShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
	D3DXMATRIX& AllMatrix,				//オブジェクトの変換行列
	LPD3DXEFFECT	pEffect,			//エフェクトのポインタ
	D3DXMATRIX& mCameraView,			//カメラのビュー行列
	D3DXMATRIX& mCameraProj			//カメラのプロジェクション行列
	);
 用途: 影ボリュームを描画（仮想関数）派生クラスから呼ばれる
 戻り値: なし。
***************************************************************************/
	void DrawCommonShadowVolume(
		LPDIRECT3DDEVICE9 pD3DDevice,D3DXMATRIX& AllMatrix,
		LPD3DXEFFECT pEffect,D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj);
public:
/**************************************************************************
	void SetWireFrame(
	bool Value	//ワイアフレームにするかどうか
	);
 用途: ワイアフレームの場合はtrue、それ以外はfalseを設定する
 戻り値: なし。
***************************************************************************/
	void SetWireFrame(bool Value){
		m_bWireFrame = Value;
	}
	//以下はデバイス喪失時に外部から呼ばれる
/**************************************************************************
	virtual void ReleaseObj();
 用途: デバイス喪失によるリソースの開放（仮想関数）
 戻り値: なし。
 ＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
	virtual void ReleaseObj();
};



//**************************************************************************
// class LoadMeshFromX : public MultiCommonMesh;
//
// 担当者  : 鴫原 徹
// 用途    : xファイルをもとにメッシュを作成
//             モデルデータを読み込んでメッシュを作りたい時に継承ると便利
//	           動かない
//**************************************************************************
class LoadMeshFromX : public CommonMesh{
protected:
	//**************************************************************************
	// struct LoadMeshFromX::MaterialItem;
	//
	// 担当者  : 鴫原 徹
	// 用途    : マテリアル構造体
	//**************************************************************************
	struct MaterialItem{
		LPDIRECT3DTEXTURE9 m_pTexture;	//	: テクスチャー
		D3DMATERIAL9       m_Material;	//	: マテリアル
		void init(LPDIRECT3DDEVICE9 pD3DDevice,D3DXMATERIAL d3dxMaterials,
				TextureManager& TexMgr,const wchar_t* pDirPath,const wchar_t* pFileName = NULL)
		{
			m_Material			= d3dxMaterials.MatD3D;
			m_Material.Ambient	= m_Material.Diffuse; // ?なにこれ
			m_pTexture			= NULL;

			if(	( pFileName != NULL && lstrlen(pFileName)  > 0 )  ||
				( d3dxMaterials.pTextureFilename != NULL &&
				 lstrlen((LPCWSTR)d3dxMaterials.pTextureFilename) > 0) )
			{
				wstring sFilePath, sFileName;
				if(pFileName)	sFileName = pFileName ;
				else			TLIB::widen(d3dxMaterials.pTextureFilename,sFileName);
				sFilePath		= pDirPath ;
				m_pTexture		= TexMgr.addTexture(pD3DDevice,(sFilePath + sFileName).c_str());
			}
		}
	};
	//**************************************************************************
	// static LoadMeshFromX::MaterialItems;
	//
	// 担当者  : 鴫原 徹
	// 用途    : 不特定多数のマテリアルを保持する
	//**************************************************************************
	struct MaterialItems{		
		DWORD			m_MaterialQty;		//	: マテリアル件数
		MaterialItem*	m_Material;			//	: マテリアル
		void init(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXBUFFER pD3DXMtrlBuffer,
				DWORD materialQty,TextureManager& TexMgr,const wchar_t* pDirPath,const wchar_t* pFileName = NULL)
		{
			m_MaterialQty	= materialQty;
			m_Material		= new MaterialItem[m_MaterialQty];
			D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
			for(DWORD i=0; i<m_MaterialQty; i++)
			{
				this->m_Material[i].init(pD3DDevice,d3dxMaterials[i],TexMgr,pDirPath,pFileName);
			}
		}
		~MaterialItems(){
			SafeDeleteArr( m_Material );
		}
	};
	//**************************************************************************
	// static LoadMeshFromX::MaterialItems;
	//
	// 担当者  : 鴫原 徹
	// 用途    : メッシュに必要なデータ
	//**************************************************************************
	struct MeshItem{
	    //メッシュ
		string				m_sTextureName	;	// テクスチャ名名
		LPDIRECT3DTEXTURE9	m_pTexture		;	// マテリアル
		LPD3DXMESH			m_pMesh			;	// めっしゅ
		AABB				m_AABB			;	// OBB
		bool				m_bHidden		;	// 隠す
		MeshItem():m_pTexture(NULL){};
		MeshItem(LPDIRECT3DDEVICE9 pD3DDevice, MeshItem& other)
			:m_pTexture(NULL){
			DWORD option = other.m_pMesh->GetOptions() ;
			DWORD fvf    = other.m_pMesh->GetFVF();
			m_bHidden    = true ;
			other.m_pMesh->CloneMeshFVF(option,fvf,pD3DDevice,&this->m_pMesh);
		};
	};
	MaterialItems     m_MaterialItems;	// マテリアル
	MeshItem          m_BassMesh;		// ベースになるメッシュ
	string            m_sFileName;		// ファイル名 データの合致確認に使います
	LPDIRECT3DDEVICE9 pD3DDevice;		// デバイス(ここにいる??)
	vector<MeshItem*> m_MeshItems;		// メッシュがいっぱいはいってる
	LoadMeshFromX(LPDIRECT3DDEVICE9 pD3DDevice,char *pFileName,TextureManager& TexMgr,char *pTexName = NULL);
	virtual ~LoadMeshFromX(){
		SafeDeletePointerContainer( m_MeshItems );
	};
/////////////////// ////////////////////
//// 関数名     ：void Draw( DrawPacket& i_DrawPacket)
//// カテゴリ   ：仮想メンバ関数
//// 用途       ：メッシュを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  Tempus2* i_DrawPacket.pTime                 // 時間を管理するクラスへのポインタ
////            ：  vector<Object*>& Vec            // オブジェクトの配列
////            ：  Command& i_DrawPacket.pCommand                    // コマンド
//// 戻値       ：なし
//// 担当者		：鴫原 徹
//// 備考       ：Objectクラスの純粋仮想関数
////            ：
////
    virtual void Draw(DrawPacket& i_DrawPacket) ;
/////////////////// ////////////////////
//// 関数名     ：void subsetDraw( DrawPacket& i_DrawPacket)
//// カテゴリ   ：仮想メンバ関数
//// 用途       ：メッシュを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  Tempus2* i_DrawPacket.pTime                 // 時間を管理するクラスへのポインタ
////            ：  vector<Object*>& Vec            // オブジェクトの配列
////            ：  Command& i_DrawPacket.pCommand                    // コマンド
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
    void subsetDraw(DrawPacket& i_DrawPacket) ;
public:
/////////////////// ////////////////////
//// 関数名     ：void Add(D3DXVECTOR3& vScale,D3DXVECTOR3& vRot,D3DXVECTOR3& vPos)
//// カテゴリ   ：公開メンバ関数
//// 用途       ：メッシュを描画
//// 引数       ：  D3DXVECTOR3& vScale
////            ；  D3DXVECTOR3& vRot
////            ：  D3DXVECTOR3& vPos
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	virtual void Add(D3DXVECTOR3& vScale,D3DXVECTOR3& vRot,D3DXVECTOR3& vPos,
		LPDIRECT3DDEVICE9 pD3DDevice = NULL, TextureManager* pTexMgr = NULL, wstring pTexName = L"");
/////////////////// ////////////////////
//// 関数名     ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	bool CheckSame(string i_sXFilePath);
};
//**************************************************************************
// class LoadAnimationModel;
//
// 担当者  : 鴫原 徹
// 用途    : xファイルをもとにメッシュを作成
//           モデルデータを読み込んでメッシュを作りたい時に継承ると便利
//**************************************************************************
class LoadAnimationModel {
protected:
	AnimationModel* m_pAnmModel;
	D3DXMATRIX		m_mMatrix;
	friend	class LAMEnemy;
public:
	LoadAnimationModel(LPDIRECT3DDEVICE9 pD3DDevice,char *pFileName,
		D3DXVECTOR3 size,D3DXVECTOR3 rot, D3DXVECTOR3 pos,
		float InitialTracSpeed = 1.0f,DWORD InitialTrac = 0);
	virtual ~LoadAnimationModel(){
		SAFE_RELEASE(m_pAnmModel);
	};
	
/////////////////// ////////////////////
//// 関数名     ：void Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// カテゴリ   ：仮想関数
//// 用途       ：メッシュを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,				//オブジェクトの配列
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：Objectクラスの純粋仮想関数
////            ：
////
    virtual void Draw(DrawPacket& i_DrawPacket) ;
};

//**************************************************************************
// class PrimitiveBox : public CommonMesh;
//
// 担当者  : (山ノ井先生のひな形より)
// 用途    : 立方体クラス
//           立方体の物体を作りたい時などに継承すると便利
//**************************************************************************
class PrimitiveBox : public CommonMesh {
/////////////////// ////////////////////
//// 関数名     ：void PrimitiveBox::CreateBox(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture)
//// カテゴリ   ：関数
//// 用途       ：ボックスメッシュを生成
//// 引数       ：  	LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9インターフェイスへのポインタ
////            ：  	LPDIRECT3DTEXTURE9 pTexture = 0	//	テクスチャ
//// 戻値       ：なし（失敗時は例外をthrow）
//// 担当者     ：(山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
	void CreateBox(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture);
protected:
/////////////////// ////////////////////
//// 関数名     ：void VecNomal2UV(D3DXVECTOR3 vec,D3DXVECTOR3 normal,float& u,float& v)
//// カテゴリ   ：仮想関数
//// 用途       ：Vectorと法線からUとVを作り出す
//// 引数       ：  D3DXVECTOR3 vec,	//頂点
////            ：  D3DXVECTOR3 normal,	//法線
////            ：  float& u,			//変換するu（テクスチャ上のU座標）
////            ：  float& v			//変換するv（テクスチャ上のV座標）
//// 戻値       ：なし
//// 担当者     ：(山ノ井先生のひな形より)
//// 備考       ：float& uとfloat& vに変換後の値を代入
////            ：
////
	void VecNomal2UV(D3DXVECTOR3 vec,D3DXVECTOR3 normal,float& u,float& v);
	LPDIRECT3DTEXTURE9 m_pTexture;
	//	テクスチャがある場合の頂点フォーマットの定義
	// D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1
	// を構造体化している
	struct  PlateVertex{
		D3DXVECTOR3 vec;
		D3DXVECTOR3 normal;
		FLOAT       tu,tv;
	};
	//PrimitiveBox用のFVFをDIrectXAPIに渡すときのパラメータ
	enum { PlateFVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
/////////////////// ////////////////////
//// 関数名     ：PrimitiveBox(LPDIRECT3DDEVICE9 pD3DDevice,
////            ：  	D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
////            ：  	LPDIRECT3DTEXTURE9 pTexture = 0);
//// カテゴリ   ：コンストラクタ
//// 用途       ：インスタンス生成時処理
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9インターフェイスへのポインタ
////            ：  D3DCOLORVALUE& Diffuse,			//ディフューズ色
////            ：  D3DCOLORVALUE& Specular,		//スペキュラ色
////            ：  D3DCOLORVALUE& Ambient,			//アンビエント色
////            ：  LPDIRECT3DTEXTURE9 pTexture = 0	//テクスチャを張るときは指定
//// 戻値       ：なし失敗時は例外をthrow）
//// 担当者     ：(山ノ井先生のひな形より)
//// 備考       ：独立オブジェクト向けコンストラクタ
////            ：
////
	PrimitiveBox(LPDIRECT3DDEVICE9 pD3DDevice,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		LPDIRECT3DTEXTURE9 pTexture = 0);
/////////////////// ////////////////////
//// 関数名     ：PrimitiveBox(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture = 0)
//// カテゴリ   ：コンストラクタ
//// 用途       ：インスタンス生成時処理
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9インターフェイスへのポインタ
////            ：  LPDIRECT3DTEXTURE9 pTexture = 0	//テクスチャを張るときは指定
//// 戻値       ：なし失敗時は例外をthrow）
//// 担当者     ：(山ノ井先生のひな形より)
//// 備考       ：独立オブジェクト向けコンストラクタ
////            ：
////
    PrimitiveBox(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture = 0);
/////////////////// ////////////////////
//// 関数名     ：virtual ~PrimitiveBox()
//// カテゴリ   ：デストラクタ
//// 用途       ：
//// 戻値       ：なし
//// 担当者     ：(山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
    virtual ~PrimitiveBox();
/////////////////// ////////////////////
//// 関数名     ：void Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// カテゴリ   ：仮想関数
//// 用途       ：立方体を描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec				//オブジェクトの配列
//// 戻値       ：なし
//// 担当者     ：(山ノ井先生のひな形より)
//// 備考       ：Objectクラスの純粋仮想関数
////            ：
////
    virtual void Draw(DrawPacket& i_DrawPacket) ;

};

//**************************************************************************
// class PrimitiveCylinder : public CommonMesh;
//
// 担当者  : 鴫原 徹
// 用途    : 円柱クラス
//**************************************************************************
class PrimitiveCylinder : public CommonMesh  {
	// D3DFVF_XYZ | D3DFVF_TEX1
	// を構造体化している
	struct  SphereVertex{
		D3DXVECTOR3 vec;
		D3DXVECTOR3 n;
		FLOAT       tu,tv;
	};
	//PrimitiveCylinder用のFVFをDIrectXAPIに渡すときのパラメータ
	enum { BallFVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
		LPDIRECT3DTEXTURE9 m_pTexture;
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
	void CreateCylinder(LPDIRECT3DDEVICE9 pD3DDevice);
protected:
/////////////////// ////////////////////
//// 関数名     ：PrimitiveCylinder( LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture = 0);
//// カテゴリ   ：コンストラクタ
//// 用途       ：球体を作成
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	//IDirect3DDevice9インターフェイスへのポインタ
////            ：  LPDIRECT3DTEXTURE9 pTexture = 0	//テクスチャを張るときは指定
//// 戻値       ：なし（失敗時は例外をthrow）
//// 担当者     ： (山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
    PrimitiveCylinder(LPDIRECT3DDEVICE9 pD3DDevice,
          D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		   LPDIRECT3DTEXTURE9 pTexture);
/////////////////// ////////////////////
//// 関数名     ：~PrimitiveCylinder();
//// カテゴリ   ：デストラクタ
//// 用途       ：球体を破棄
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ： (山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
    virtual ~PrimitiveCylinder();

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
//**************************************************************************
// class PrimitiveSphere : public CommonMesh;
//
// 担当者  : 鴫原 徹
// 用途    : 円柱クラス
//**************************************************************************
class PrimitiveSphere : public CommonMesh {
	// D3DFVF_XYZ | D3DFVF_TEX1
	// を構造体化している
	struct  SphereVertex{
		D3DXVECTOR3 vec;
		D3DXVECTOR3 n;
		FLOAT       tu,tv;
	};
	//PrimitiveSphere用のFVFをDIrectXAPIに渡すときのパラメータ
	enum { BallFVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
		LPDIRECT3DTEXTURE9 m_pTexture;
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
//// 関数名     ：PrimitiveSphere(LPDIRECT3DDEVICE9 pD3DDevice,D3DCOLORVALUE& Diffuse,
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
//// 備考       ：
////            ：
////
    PrimitiveSphere(LPDIRECT3DDEVICE9 pD3DDevice,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		LPDIRECT3DTEXTURE9 pTexture = 0);

/////////////////// ////////////////////
//// 関数名     ：PrimitiveSphere( LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture = 0);
//// カテゴリ   ：コンストラクタ
//// 用途       ：球体を作成
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	//IDirect3DDevice9インターフェイスへのポインタ
////            ：  LPDIRECT3DTEXTURE9 pTexture = 0	//テクスチャを張るときは指定
//// 戻値       ：なし（失敗時は例外をthrow）
//// 担当者     ： (山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
    //PrimitiveSphere(LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture = 0);
/////////////////// ////////////////////
//// 関数名     ：~PrimitiveSphere();
//// カテゴリ   ：デストラクタ
//// 用途       ：球体を破棄
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ： (山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
    virtual ~PrimitiveSphere();

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
//**************************************************************************
// class PrimitiveSprite ;
//
// 担当者  : 鴫原 徹
// 用途    : ２D環境のスプライトクラス
//**************************************************************************
class PrimitiveSprite {
protected:
	LPDIRECT3DTEXTURE9 m_pTexture;	//	: 描画するテクスチャ
	LPD3DXSPRITE	m_pSprite;		//	: 描画するためのスプライト
	D3DXMATRIX		m_mMatrix;		//	: マトリックス (派生クラスはここに座標データを入れる)
	D3DXVECTOR3		m_vOffsetPos;	//	: テクスチャーの描画オフセット(基本は０値点);
	D3DXVECTOR3		m_vCenter;		//	: テクスチャーの中心
	RECT*			m_pRect;		//	: テクスチャーの描画領域
	Color			m_Color;
public:
	void setMatrix( D3DXMATRIX i_mMatrix ){ m_mMatrix = i_mMatrix ; }

/////////////////// ////////////////////
//// 関数名     ：PrimitiveSprite(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,RECT* Rect,
////            ：    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,D3DCOLOR color = 0xFFFFFFFF);
//// カテゴリ   ：仮想関数
//// 用途       ：スプライトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	//	: デバイス
////            ：  LPDIRECT3DTEXTURE9 pTexture,	//	: テクスチャーへのポインタ
////            ：  RECT*			Rect,			//	: テクスチャの描画範囲
////            ：  D3DXVECTOR3&	vCenter,		//	: 中心位置
////            ：  D3DXVECTOR3&	vOffsetPos,		//	: ローカル座標
////            ：  D3DCOLOR		color			//	: 色
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	PrimitiveSprite(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,RECT* Rect,
			D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
/////////////////// ////////////////////
//// 関数名     ：virtual ~PrimitiveSprite()
//// カテゴリ   ：デストラクタ
//// 用途       ：
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	virtual ~PrimitiveSprite();
/////////////////// ////////////////////
//// 関数名     ：void Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// カテゴリ   ：仮想関数
//// 用途       ：スプライトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,				//オブジェクトの配列
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	virtual void Draw(DrawPacket& i_DrawPacket);


};

//**************************************************************************
// class SpriteObject : public Object ,public PrimitiveSprite ;
//
// 担当者  : 鴫原 徹
// 用途    : スプライトをとりあえず描画するためのクラス
//           何の動作もしないとりあえずスプライトを描画したい時におすすめ
//**************************************************************************
class SpriteObject : public Object ,public PrimitiveSprite{
public:
/////////////////// ////////////////////
//// 関数名     ：SpriteObject(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
////            ：    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect,
////            ：    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
//// カテゴリ   ：コンストラクタ
//// 用途       ：スプライトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  LPDIRECT3DTEXTURE9 pTexture     // 貼り付けたいテクスチャ
////            ：  D3DXVECTOR3 &vScale             // 大きさ
////            ：  D3DXVECTOR3 &vRot               // 三軸回転
////            ：  D3DXVECTOR3 &vPos               // 設置座標
////            ：  RECT* pRect                     // 描画したい範囲(NULLで全体を描画)
////            ：  D3DXVECTOR3& vCenter            // 中心
////            ：  D3DXVECTOR3& vOffsetPos         // オフセット座標
////            ：  Color color = 0xFFFFFFFF        // 色
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	SpriteObject(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
			D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect,
			D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF,
			wiz::OBJID id = OBJID_UI_SPRITE);
/////////////////// ////////////////////
//// 関数名     ：~SpriteObject();
//// カテゴリ   ：デストラクタ
//// 用途       ：
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	virtual ~SpriteObject();
/////////////////// ////////////////////
//// 関数名     ：void Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// カテゴリ   ：仮想関数
//// 用途       ：スプライトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,				//オブジェクトの配列
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	virtual void Draw(DrawPacket& i_DrawPacket);
};
/**************************************************************************
 class Sound: public Object;
 用途: サウンドクラス
****************************************************************************/
class Sound : public Object{
protected:
	IXACT3Engine* m_pEngine;
	IXACT3WaveBank* m_pWaveBank;
	IXACT3SoundBank* m_pSoundBank;
	VOID* m_pbWaveBank; // Handle to wave bank data.  Its memory mapped so call UnmapViewOfFile() upon cleanup to release file
	VOID* m_pbSoundBank; // Pointer to sound bank data.  Call delete on it when the sound bank is destroyed
/**************************************************************************
 void Clear();
 用途:オブジェクトの破棄
 戻り値: なし
***************************************************************************/
	void Clear();
public:
/**************************************************************************
 Sound(
 const wchar_t* pWavBankFileName,		//Wavバンクのファイル名
 const wchar_t* pSoundBankFileName	//Soundバンクのファイル名
 );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
	Sound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName);
/**************************************************************************
 virtual ~Sound();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	virtual ~Sound();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Command& i_DrawPacket.pCommand					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: 描画（サウンドなのでなにもしない）
 戻り値: なし。
***************************************************************************/
    virtual void Draw(DrawPacket& i_DrawPacket);
};
/**************************************************************************
 class ZapSound: public Sound;
 用途: Zapサウンドクラス
****************************************************************************/
class ZapSound : public Sound{
	XACTINDEX m_iZap;
	XACTINDEX m_iFire;
	XACTINDEX m_iBGM;
	XACTINDEX m_iBS;
	XACTINDEX m_iGET;
	XACTINDEX m_iHANAB1;
	XACTINDEX m_iHANAB2;
public:
/**************************************************************************
 ZapSound(
 const wchar_t* pWavBankFileName,		//Wavバンクのファイル名
 const wchar_t* pSoundBankFileName	//Soundバンクのファイル名
 const char* pZapKey				//爆発音のキー
 const char* pFireKey				//発射音のキー
 );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
	ZapSound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,
		const char* pZapKey,const char* pFireKey,const char* BGM,const char* BS,const char* GET,const char* HANAB1,const char* HANAB2);
/**************************************************************************
 virtual ~ZapSound();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	virtual ~ZapSound();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Command& i_DrawPacket.pCommand					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: 描画（サウンドなのでなにもしない）
 戻り値: なし。
***************************************************************************/
	void Draw(DrawPacket& i_DrawPacket){};
/**************************************************************************
 void PlayZap();
 用途: 爆発を鳴らす
 戻り値: なし。
***************************************************************************/
    void PlayZap();
/**************************************************************************
 void PlayFire();
 用途: 発射音を鳴らす
 戻り値: なし。
***************************************************************************/
    void PlayFire();
/**************************************************************************
 void BGM();
 用途: ゲーム中のBGM
 戻り値: なし。
***************************************************************************/
    void BGM();
/**************************************************************************
 void PlayFire();
 用途: 発射音を鳴らす
 戻り値: なし。
***************************************************************************/
    void BS();
/**************************************************************************
 void BGM();
 用途: ゲーム中のBGM
 戻り値: なし。
***************************************************************************/
    void GET();

/**************************************************************************
 void BGM();
 用途: ゲーム中のBGM
 戻り値: なし。
***************************************************************************/
    void HANAB1();
/**************************************************************************
 void BGM();
 用途: ゲーム中のBGM
 戻り値: なし。
***************************************************************************/
    void HANAB2();
};
}//end of namespace baseobject.
using namespace baseobject;
}//end of namespace wiz.
