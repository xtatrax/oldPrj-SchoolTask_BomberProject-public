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
//
//
#pragma once
#include "Object.h"
//#include "AnimationModelClass/AnimationModelClass.h"
#include "Bass2DItems.h"
#include "TL-String.h"
namespace wiz {
namespace baseitems{

//////////
//	: 仮宣言
class CommonMesh;
class SimpleCommonMesh ;
//	: 仮宣言
//////////

enum SHADING{
	SHADING_COOKTRANCE,
};

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
class CustomShader{
protected:
	LPD3DXMESH			pickoutMesh(CommonMesh* pComMesh);
	D3DMATERIAL9		pickoutMaterial(CommonMesh* pComMesh);
	D3DXMATRIX			pickoutMatrix(SimpleCommonMesh* pComMesh);
	LPTATRATEXTURE		pickoutTexture(SimpleCommonMesh* pComMesh);
};
class CookTrance : public CustomShader{
	Camera*			m_pCamera			;
	Light*			m_pLight			;
	LPD3DXEFFECT	m_pEffect			;
	D3DXHANDLE		m_hTech				;
	D3DXHANDLE		m_hWorldViewProj	;
	D3DXHANDLE		m_hWorld			;
	D3DXHANDLE		m_hWIT				;
	D3DXHANDLE		m_hLightDir			;
	D3DXHANDLE		m_hEyePos			;
	D3DXHANDLE		m_hTexture			;
	D3DXHANDLE		m_hDif				;
	D3DXHANDLE		m_hAmb				;
public:
	CookTrance(LPDIRECT3DDEVICE9 pD3DDevice);
	~CookTrance();

	/////////////////// ////////////////////
	//// 関数名     ：void CommonMesh::Draw( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：仮想関数
	//// 用途       ：メッシュを描画
	//// 引数       ：  
	//// 戻値       ：なし
	//// 担当者     ： (山ノ井先生のひな形より)
	//// 備考       ：なるべくこの関数は使わず DrawCommonMesh 関数を使うようにしてください
	////            ：
	////
	void Draw(DrawPacket& i_DrawPacket,CommonMesh* i_pComMesh);

	/////////////////// ////////////////////
	//// 関数名     ：void CommonMesh::Draw( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：仮想関数
	//// 用途       ：メッシュを描画
	//// 引数       ：  
	//// 戻値       ：なし
	//// 担当者     ： (山ノ井先生のひな形より)
	//// 備考       ：なるべくこの関数は使わず DrawCommonMesh 関数を使うようにしてください
	////            ：
	////
	void Draw(DrawPacket& i_DrawPacket,SimpleCommonMesh* i_pComMesh);

	/////////////////// ////////////////////
	//// 関数名     ：void CommonMesh::Draw( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：仮想関数
	//// 用途       ：メッシュを描画
	//// 引数       ：  
	//// 戻値       ：なし
	//// 担当者     ： (山ノ井先生のひな形より)
	//// 備考       ：なるべくこの関数は使わず DrawCommonMesh 関数を使うようにしてください
	////            ：
	////
	void Draw(
		DrawPacket&				i_DrawPacket	,
		LPD3DXMESH				i_pMesh			,
		LPTATRATEXTURE		i_pTexture		,
		D3DXMATRIX				i_mMatrix		,
		D3DMATERIAL9			i_Material
	);
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/


/**************************************************************************
class CommonMesh : public Object;
用途: コモンメッシュクラス
****************************************************************************/
class CommonMesh : public Object{
public:
	friend class CustomShader;

	//Boxのテクスチャパターン
	//パターンは呼び出し側で指定するので、これだけpublicにする
	enum {PtnUV_1_1 = 0, PtnUV_6_1,PtnUV_YWrap,PtnUV_ZWrap, PtnUV_1_4};
protected:
	//以下は派生クラスから呼ばれる
	//メッシュ
	LPD3DXMESH m_pMesh;
	//影ボリュームクラス
	//ShadowVolume* m_pShadowVolume;
	//ラッピングテクスチャかどうか
	bool m_bWrapMode;
	//ワイアーフレーム表示するかどうか
	bool m_bWireFrame;
	//フラットモードにするかどうか
	//デフォルトはfalse（グーロー シェーディング モード）
	bool m_bShadeModeFlat;

	//CustomShader* m_pShader;
protected:
	//テスト用
	D3DMATERIAL9	m_Material ;
	DWORD			m_dwDrawSubset;
	
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
	static void BoxVecNomalUV(
	D3DXVECTOR3 vec,	//頂点
	D3DXVECTOR3 normal,	//法線
	float& u,	//変換するu（テクスチャ上のU座標）
	float& v	//変換するv（テクスチャ上のV座標）
	);
	用途: BoxのVectorと法線からUとVを作り出す
	前面のみにテクスチャを展開する場合
	戻り値: なし
	float& uとfloat& vに変換後の値を代入
	***************************************************************************/
	static void BoxVecNomalUV(D3DXVECTOR3 vec,D3DXVECTOR3 normal,float& u,float& v);

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
	static void BoxVecNomal2UV_1_4(
	D3DXVECTOR3 vec,	//頂点
	D3DXVECTOR3 normal,	//法線
	float& u,	//変換するu（テクスチャ上のU座標）
	float& v	//変換するv（テクスチャ上のV座標）
	);
 用途: BoxのVectorと法線からUとVを作り出す
 テクスチャが4×1の画像になってる場合
 戻り値: なし
 float& uとfloat& vに変換後の値を代入
***************************************************************************/
				static void BoxVecNomal2UV_1_4(D3DXVECTOR3 vec,D3DXVECTOR3 normal,int ptn,float& u,float& v);
/**************************************************************************
 static void BoxVecNomal2UV_1_2(
	D3DXVECTOR3 vec,	//頂点
	D3DXVECTOR3 normal,	//法線
	float& u,	//変換するu（テクスチャ上のU座標）
	float& v	//変換するv（テクスチャ上のV座標）
	);
 用途: BoxのVectorと法線からUとVを作り出す
 テクスチャが2×1の画像になってる場合
 戻り値: なし
 float& uとfloat& vに変換後の値を代入
***************************************************************************/
				static void BoxVecNomal2UV_1_2(D3DXVECTOR3 vec,D3DXVECTOR3 normal,int ptn,float& u,float& v);
/**************************************************************************
 static void SphereVec2UV(
>>>>>>> workspace
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

	/**************************************************************************
	CommonMesh();
	用途: コンストラクタ
	戻り値: なし
	***************************************************************************/
	CommonMesh( wiz::OBJID id , CustomShader* pShader = NULL );

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
	void CreateBox(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& size,bool bTextureActive = false,int TexturePtn = PtnUV_1_1);

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
	void CreateSphere(LPDIRECT3DDEVICE9 pD3DDevice,FLOAT radius,bool bTextureActive = false,UINT Slices = 18,UINT Stacks = 18);

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
	void CreateTorus(LPDIRECT3DDEVICE9 pD3DDevice,FLOAT InnerRadius,FLOAT OuterRadius,bool bTextureActive = false,UINT Sides = 18,UINT Rings = 18);

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
	void CreateCylinder(LPDIRECT3DDEVICE9 pD3DDevice,FLOAT Radius1,FLOAT Radius2,FLOAT Length,bool bTextureActive = false,UINT Slices = 18,UINT Stacks = 18);

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
	void CreatePolygon(LPDIRECT3DDEVICE9 pD3DDevice,FLOAT Length,UINT Sides,bool bTextureActive = false);

	/////////////////// ////////////////////
	//// 関数名     ：void CommonMesh::CreateMeshFormX(LPDIRECT3DDEVICE9 pD3DDevice,char *pFileName,TextureManager& TexMgr)
	//// カテゴリ   ：関数
	//// 用途       ：メッシュXファイルから読み込み
	//// 引数       ：  LPDIRECT3DDEVICE9	pD3DDevice
	////            ：  char*				pFileName
	////            ：  TextureManager&		TexMgr
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	void CreateMeshFormX(
		const LPDIRECT3DDEVICE9 pD3DDevice,
		const char *pFileName,
		const TextureManager* pTexMgr
	);
	
	/////////////////// ////////////////////
	//// 関数名     ：void CommonMesh::Draw( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：仮想関数
	//// 用途       ：メッシュを描画
	//// 引数       ：  
	//// 戻値       ：なし
	//// 担当者     ： (山ノ井先生のひな形より)
	//// 備考       ：なるべくこの関数は使わず DrawCommonMesh 関数を使うようにしてください
	////            ：
	////
	void Draw(DrawPacket& i_DrawPacket,RENDERSTATE_PARAM* pParam = NULL);
	/**************************************************************************
	void DrawCommonMesh(
	LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
	D3DXMATRIX& Matrix,			//変換行列
	D3DMATERIAL9& Material,		//マティリアル
	LPTATRATEXTURE pTexture = 0			//テクスチャ
	);
	用途: コモンオブジェクトを描画（派生クラスから呼ばれる）
	戻り値: なし。
	***************************************************************************/
	void DrawCommonMesh(LPDIRECT3DDEVICE9 pD3DDevice,D3DXMATRIX& Matrix,D3DMATERIAL9& Material,LPTATRATEXTURE pTexture = 0,RENDERSTATE_PARAM* pParam = NULL);
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
	void DrawCommonShadowVolume( LPDIRECT3DDEVICE9 pD3DDevice,D3DXMATRIX& AllMatrix, LPD3DXEFFECT pEffect,D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj);
public:
	void ShaderChange( CustomShader* pShader ){
	//	SafeDelete( m_pShader );
	//	m_pShader = pShader;
	}
	CustomShader* getShader(){
		return NULL;//m_pShader;
	}

	/**************************************************************************
	void SetWireFrame(
	bool Value	//ワイアフレームにするかどうか
	);
	用途: ワイアフレームの場合はtrue、それ以外はfalseを設定する
	戻り値: なし。
	***************************************************************************/
	void SetWireFrame(bool Value){ m_bWireFrame = Value; }
	/**************************************************************************
	void SetShadeModeFlat(
	bool Value	//シェーダーをフラットモードにするかどうか
	);
	用途: シェーダーをフラットモードの場合はtrue、
	それ以外（グーロー シェーディング モードはfalseを設定する
	戻り値: なし。
	***************************************************************************/
	void SetShadeModeFlat(bool Value){ m_bShadeModeFlat = Value;}

	//以下はデバイス喪失時に外部から呼ばれる
	/**************************************************************************
	virtual void ReleaseObj();
	用途: デバイス喪失によるリソースの開放（仮想関数）
	戻り値: なし。
	＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
	***************************************************************************/
	virtual void ReleaseObj();
};


/**************************************************************************
 class MultiCommonMesh : public CommonMesh;
 用途: 複数のコモンメッシュクラス
****************************************************************************/
class MultiCommonMesh : public CommonMesh{
protected:
	//テクスチャつきかどうか
	bool m_IsTextureActive;
	struct CommonItem{
		//このアイテムは有効かどうか
		bool m_IsActive;
		//マテリアル
		D3DMATERIAL9 m_Material;
		//初期のスケール
		D3DXVECTOR3 m_BaseScale;
		//初期位置のオブジェクトの中心
		D3DXVECTOR3 m_BasePos;
		//回転用のクオータニオン
		D3DXQUATERNION m_BaseQt;
		//現在の初期位置からの相対位置
		D3DXVECTOR3 m_Pos;
		//現在の初期位置からの回転用のクオータニオン
		D3DXQUATERNION m_Qt;
		//描画時に使用されるワールド変換行列
		D3DXMATRIX m_WorldMatrix;
		//影を描画するかどうか
		bool m_IsShadowActive;
		//テクスチャ
		LPTATRATEXTURE m_pTexture;
		//派生クラスを作ってもClear()関数で
		//削除できるように仮想デストラクタにしておく
		virtual ~CommonItem(){}
	};
	//CommonItemの配列
	vector<CommonItem*> m_ItemVec;
	/**************************************************************************
	virtual void Clear();
	用途:オブジェクトの破棄
	戻り値: なし
	***************************************************************************/
	virtual void Clear();
	/**************************************************************************
	MultiCommonMesh(
	bool IsTextureActive = false	//テクスチャを張るときは指定
	);
	用途: コンストラクタ
	戻り値: なし（失敗時は例外をthrow）
	＊コンストラクタでは、テクスチャを使用するかしないか指定する
	***************************************************************************/
	MultiCommonMesh( wiz::OBJID id , bool IsTextureActive = false );
public:
	/**************************************************************************
	virtual ~MultiCommonMesh();
	用途: デストラクタ
	戻り値: なし
	***************************************************************************/
	virtual ~MultiCommonMesh();
	/**************************************************************************
	virtual size_t AddItem(
	D3DXVECTOR3& Scale,               //スケール（拡大縮小の倍率）
	D3DXVECTOR3& Pos,                //最初の位置
	D3DXVECTOR3& Rot,				//回転(ラジアン単位)
	D3DCOLORVALUE& Diffuse,         //ディフューズ色
	D3DCOLORVALUE& Specular,            //スペキュラ色
	D3DCOLORVALUE& Ambient          //アンビエント色
	bool IsShadowActive = false,	//影を描画するかどうか
	LPTATRATEXTURE pTexture = 0			//テクスチャ
	);
	用途: アイテムを追加
	戻り値: 追加したインデックス（失敗時は例外をthrow）
	***************************************************************************/
	virtual size_t AddItem(D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot,D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,bool IsShadowActive = false,LPTATRATEXTURE pTexture = 0);
	/**************************************************************************
	size_t GetItemCount();
	用途: 現在のアイテム数を得る
	戻り値: アイテム数
	***************************************************************************/
	size_t GetItemCount(){return  m_ItemVec.size();}
	/**************************************************************************
	size_t GetActiveItemCount();
	用途: 現在の有効なアイテム数を得る
	戻り値: アイテム数
	***************************************************************************/
	size_t GetActiveItemCount();
	/**************************************************************************
	bool IsActiveItem(
	size_t Index	//取得したいインデックス
	);
	用途: 指定したインデックスのアイテムが有効かどうかを調べる
	戻り値: 有効ならTRUE、無効ならFALSE、インデックスが範囲以外なら例外
	***************************************************************************/
	bool IsActiveItem(size_t Index);

	/**************************************************************************
	void SetActiveItem(
	size_t Index,	//セットしたいインデックス
	bool val		//したいしたい値（trueかfalse）
	);
	用途: 指定したインデックスのアイテムが有効かどうかを設定する
	戻り値: なし、インデックスが範囲以外なら例外
	***************************************************************************/
	void SetActiveItem(size_t Index,bool val);
	/**************************************************************************
	void CopyItem(
	CommonItem* Dest,	//コピー先
	size_t Index		//コピー元のアイテムのインデックス
	);
	用途:アイテムのコピー
	戻り値: なし
	***************************************************************************/
	void CopyItem(CommonItem* Dest,size_t Index);
	/**************************************************************************
	void GetItemMaterial(
	size_t Index,	//取得するインデックス
	D3DMATERIAL9& Material	//現在のマテリアル
	);
	用途: マテリアルを取得する
	戻り値: なし（MaterialにIndexのマテリアルを返す）
	***************************************************************************/
	void GetItemMaterial(size_t Index,D3DMATERIAL9& Material);
	/**************************************************************************
	void SetItemMaterial(
	size_t Index,	//設定するインデックス
	D3DMATERIAL9& Material	//設定するマテリアル
	);
	用途: マテリアルを設定する
	戻り値: なし
	***************************************************************************/
	void SetItemMaterial(size_t Index,D3DMATERIAL9& Material);

	/**************************************************************************
	bool IsTextureActive();
	用途: テクスチャが有効かどうかを調べる
	戻り値: 有効ならTRUE、無効ならFALSE
	＊各インデックスのテクスチャを変更する場合は、先に有効かどうか調査すること
	***************************************************************************/
	bool IsTextureActive();

	/**************************************************************************
	LPTATRATEXTURE GetItemTexture(
	size_t Index	//取得するインデックス
	);
	用途: テクスチャを取得する
	戻り値: 現在のテクスチャ（ない場合は0が返る）
	***************************************************************************/
	LPTATRATEXTURE GetItemTexture(size_t Index);
	/**************************************************************************
	void SetItemTexture(
	size_t Index,	//設定するインデックス
	LPTATRATEXTURE pTexture	//設定するテクスチャ
	);
	用途: テクスチャを設定する
	戻り値: なし
	***************************************************************************/
	void SetItemTexture(size_t Index,LPTATRATEXTURE pTexture);

	/**************************************************************************
	bool IsShadowActiveItem(
	size_t Index	//取得したいインデックス
	);
	用途: 指定したインデックスの影が有効かどうかを調べる
	戻り値: 有効ならTRUE、無効ならFALSE、インデックスが範囲以外なら例外
	***************************************************************************/
	bool IsShadowActiveItem(size_t Index);

	/**************************************************************************
	void SetShadowActiveItem(
	size_t Index,	//セットしたいインデックス
	bool val		//したいしたい値（trueかfalse）
	);
	用途: 指定したインデックスの影が有効かどうかを設定する
	戻り値: なし、インデックスが範囲以外なら例外
	***************************************************************************/
	void SetShadowActiveItem(size_t Index,bool val);


	/**************************************************************************
	void GetItemWorldPos(
	size_t Index,	//取得するインデックス
	D3DXVECTOR3& Pos	//現在のワールド位置
	);
	用途: ワールド位置を取得する
	戻り値: なし（PosにIndexのワールド位置を返す）
	***************************************************************************/
	void GetItemWorldPos(size_t Index,D3DXVECTOR3& Pos);

	/**************************************************************************
	void GetItemWorldRot(
	size_t Index,	//取得するインデックス
	D3DXVECTOR3& Rot	//現在のワールド回転
	);
	用途: ワールド回転を取得する
	戻り値: なし（RotにIndexのワールド回転を返す）
	***************************************************************************/
	void GetItemWorldRot(size_t Index,D3DXVECTOR3& Rot);
	/**************************************************************************
	void GetItemWorldQt(
	size_t Index,	//取得するインデックス
	D3DXQUATERNION& Qt	//現在のワールド回転
	);
	用途: ワールド回転を取得する
	戻り値: なし（QtにIndexのワールド回転を返す）
	***************************************************************************/
	void GetItemWorldQt(size_t Index,D3DXQUATERNION& Qt);
	/**************************************************************************
	void GetItemWorldScale(
	size_t Index,	//取得するインデックス
	D3DXVECTOR3& Scale	//現在のワールドスケール
	);
	用途: ワールドスケールを取得する
	＊この関数はGetItemBaseScale関数と同じ
	戻り値: なし（ScaleにIndexのワールド回転を返す）
	***************************************************************************/
	void GetItemWorldScale(size_t Index,D3DXVECTOR3& Scale);
	/**************************************************************************
	void GetItemWorld(
	size_t Index,_	//取得するインデックス
	D3DXVECTOR3& Scale,	//現在のワールドスケール
	D3DXVECTOR3& Pos,	//現在のワールド位置
	D3DXVECTOR3& Rot,	//現在のワールド回転（オイラー各）
	D3DXQUATERNION& Qt	//現在のワールド回転（クオータニオン）
	);
	用途: すべてのワールド値を取得する
	戻り値: なし（参照にIndexのワールド値を返す）
	***************************************************************************/
	void GetItemWorld(size_t Index,D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot,D3DXQUATERNION& Qt);
	/**************************************************************************
	void GetItemWorldMatrix(
	size_t Index,_	//取得するインデックス
	D3DXMATRIX& mtWorld	//取得する行列
	);
	用途:ワールド変換を取得する
	戻り値: なし。mtWorldに変換行列をセットする
	***************************************************************************/
	void GetItemWorldMatrix(size_t Index,D3DXMATRIX& mtWorld);
	/**************************************************************************
	void CalcWorldMatrix();
	用途:すべてのアイテムのワールド変換を計算する
	戻り値: なし。現在の変換をもとにワールド行列を計算する
	***************************************************************************/
	void CalcWorldMatrix();
	/**************************************************************************
	void GetItemLocalPos(
	size_t Index,	//取得するインデックス
	D3DXVECTOR3& Pos	//現在の相対位置
	);
	用途: 相対位置を取得する
	戻り値: なし
	***************************************************************************/
	void GetItemLocalPos(size_t Index,D3DXVECTOR3& Pos);

	/**************************************************************************
	void GetItemLocalRot(
	size_t Index,	//取得するインデックス
	D3DXVECTOR3& Rot	//現在の回転
	);
	用途: 相対回転を取得する
	戻り値: なし
	***************************************************************************/
	void GetItemLocalRot(size_t Index,D3DXVECTOR3& Rot);

	/**************************************************************************
	void GetItemLocalQt(
	size_t Index,	//取得するインデックス
	D3DXQUATERNION& Qt	//現在の相対回転
	);
	用途: 相対回転を取得する（クオータニオン版）
	戻り値: なし
	***************************************************************************/
	void GetItemLocalQt(size_t Index,D3DXQUATERNION& Qt);

	/**************************************************************************
	void GetItemLocalPosQt(
	size_t Index,	//取得するインデックス
	D3DXVECTOR3& Pos,	//現在の相対位置
	D3DXQUATERNION& Qt	//現在の相対回転
	);
	用途: 相対値を取得する(クオータニオン版)
	戻り値: なし
	***************************************************************************/
	void GetItemLocalPosQt(size_t Index,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	void GetItemLocalPosRot(
	size_t Index,	//取得するインデックス
	D3DXVECTOR3& Pos,	//現在の相対位置
	D3DXVECTOR3& Rot	//現在の回転
	);
	用途: 相対値を取得する
	戻り値: なし
	***************************************************************************/
	void GetItemLocalPosRot(size_t Index,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);

	/**************************************************************************
	void SetItemLocalPosQt(
	size_t Index,	//インデックス
	D3DXVECTOR3& Pos,	//相対位置
	D3DXQUATERNION& Qt	//相対回転
	);
	用途: 相対値を設定する(クオータニオン版)
	戻り値: なし
	***************************************************************************/
	void SetItemLocalPosQt(size_t Index,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	void SetItemLocalPosRot(
	size_t Index,	//インデックス
	D3DXVECTOR3& Pos,	//相対位置
	D3DXVECTOR3& Rot	//回転
	);
	用途: 相対値を設定する
	戻り値: なし
	***************************************************************************/
	void SetItemLocalPosRot(size_t Index,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);

	/**************************************************************************
	void MoveToPosRot(
	D3DXVECTOR3& Pos,	//動かす相対位置
	D3DXVECTOR3& Rot	//動かす回転
	);
	用途: 相対値を移動し回転する
	*すべてのオブジェクトに適用される
	戻り値: なし
	***************************************************************************/
	void MoveToPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	/**************************************************************************
	void MoveToPosQt(
	D3DXVECTOR3& Pos,	//動かす相対位置
	D3DXQUATERNION& Qt	//動かす回転
	);
	用途: 相対値を移動し回転する(クオータニオン版)
	*すべてのオブジェクトに適用される
	戻り値: なし
	***************************************************************************/
		void MoveToPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);

	/**************************************************************************
	void MoveToItemPosRot(
	size_t Index,	//変化させるインデックス
	D3DXVECTOR3& Pos,	//新しい相対位置
	D3DXVECTOR3& Rot	//新しい回転
	);
	用途: 指定のメンバの相対値を移動し回転する
	戻り値: なし
	***************************************************************************/
	void MoveToItemPosRot(size_t Index,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	/**************************************************************************
	void MoveToItemPosQt(
	size_t Index,	//変化させるインデックス
	D3DXVECTOR3& Pos,	//新しい相対位置
	D3DXQUATERNION& Qt	//動かす回転
	);
	用途: 指定のメンバの相対値を移動し回転する(クオータニオン版)
	戻り値: なし
	***************************************************************************/
	void MoveToItemPosQt(size_t Index,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	void MoveAtPosRot(
	D3DXVECTOR3& Pos,	//新しい相対位置
	D3DXVECTOR3& Rot	//新しい回転
	);
	用途: 相対置をセットする
	*すべてのオブジェクトに適用される
	戻り値: なし
	***************************************************************************/
	void MoveAtPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	/**************************************************************************
	void MoveAtPosQt(
	D3DXVECTOR3& Pos,	//新しい相対位置
	D3DXQUATERNION& Qt	//新しい回転
	);
	用途: 相対置をセットする(クオータニオン版)
	*すべてのオブジェクトに適用される
	戻り値: なし
	***************************************************************************/
	void MoveAtPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	void MoveAtItemPosRot(
	size_t Index,	//変化させるインデックス
	D3DXVECTOR3& Pos,	//新しい相対位置
	D3DXVECTOR3& Rot	//新しい回転
	);
	用途: 指定のメンバの相対置をセットする
	戻り値: なし
	***************************************************************************/
	void MoveAtItemPosRot(size_t Index,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	/**************************************************************************
	void MoveAtItemPosQt(
	size_t Index,	//変化させるインデックス
	D3DXVECTOR3& Pos,	//新しい相対位置
	D3DXQUATERNION& Qt	//新しい回転
	);
	用途: 指定のメンバの相対置をセットする(クオータニオン版)
	戻り値: なし
	***************************************************************************/
	void MoveAtItemPosQt(size_t Index,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	void MoveAtIdentity();
	用途: 最初に作成された位置からの指定する相対位置をクリアする
	*すべてのオブジェクトに適用される
	戻り値: なし
	***************************************************************************/
	void MoveAtIdentity();
	/**************************************************************************
	void MoveAtItemIdentity(
	size_t Index	//変化させるインデックス
	);
	用途: 指定のメンバの最初に作成された位置からの指定する相対位置をクリアする
	戻り値: なし
	***************************************************************************/
	void MoveAtItemIdentity(size_t Index);
	/**************************************************************************
	void GetItemBaseScalePosRot(
	size_t Index,		//取得するインデックス
	D3DXVECTOR3& Scale,	//スケーリングの参照
	D3DXVECTOR3& Pos,	//ベース位置の参照
	D3DXVECTOR3& Rot	//ベース回転の参照
	);
	用途: 指定のインデックスのベースのスケーリングと位置と回転を同時に取り出す
	戻り値: なし
	***************************************************************************/
	void GetItemBaseScalePosRot(size_t Index,D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	/**************************************************************************
	void GetItemBaseScalePosQt(
	size_t Index,		//取得するインデックス
	D3DXVECTOR3& Scale,	//スケーリングの参照
	D3DXVECTOR3& Pos,	//ベース位置の参照
	D3DXQUATERNION& Qt	//ベース回転クオータニオンの参照
	);
	用途: 指定のインデックスのベースのスケーリングと位置と回転を同時に取り出す（クオータニオン版）
	戻り値: なし
	***************************************************************************/
	void GetItemBaseScalePosQt(size_t Index,D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);

	/**************************************************************************
	void SetItemBaseScale(
	size_t Index,		//設定するインデックス
	D3DXVECTOR3& Scale	//新しいベーススケーリング
	);
	用途: 指定のインデックスの最初に作成されたスケーリングを変更する
	戻り値: なし
	***************************************************************************/
	void SetItemBaseScale(size_t Index,D3DXVECTOR3& Scale);
	/**************************************************************************
	void SetItemBasePos(
	size_t Index,		//設定するインデックス
	D3DXVECTOR3& Pos	//新しいベース位置
	);
	用途: 指定のインデックスの最初に作成された位置を変更する
	戻り値: なし
	***************************************************************************/
	void SetItemBasePos(size_t Index,D3DXVECTOR3& Pos);
	/**************************************************************************
	void SetItemBaseRot(
	size_t Index,		//設定するインデックス
	D3DXVECTOR3& Rot	//新しいベース回転
	);
	用途: 指定のインデックスの最初に作成された回転を変更する
	戻り値: なし
	***************************************************************************/
	void SetItemBaseRot(size_t Index,D3DXVECTOR3& Rot);
	/**************************************************************************
	void SetItemBaseQt(
	size_t Index,		//設定するインデックス
	D3DXQUATERNION& Qt	//新しいベース回転
	);
	用途: 指定のインデックスの最初に作成された回転を変更する(クオータニオン版)
	戻り値: なし
	***************************************************************************/
	void SetItemBaseQt(size_t Index,D3DXQUATERNION& Qt);
	/**************************************************************************
	void SetItemBaseScalePosRot(
	size_t Index,		//設定するインデックス
	D3DXVECTOR3& Scale,	//新しいベーススケーリング
	D3DXVECTOR3& Pos,	//新しいベース位置
	D3DXVECTOR3& Rot	//新しいベース回転
	);
	用途: 指定のインデックスの最初に作成されたスケーリングと位置と回転を同時に変更する
	戻り値: なし
	***************************************************************************/
	void SetItemBaseScalePosRot(size_t Index,D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	/**************************************************************************
	void SetItemBaseScalePosQt(
	size_t Index,		//設定するインデックス
	D3DXVECTOR3& Scale,	//新しいベーススケーリング
	D3DXVECTOR3& Pos,	//新しいベース位置
	D3DXQUATERNION& Qt	//新しいベース回転
	);
	用途: 指定のインデックスの最初に作成されたスケーリングと位置と回転を同時に変更する(クオータニオン版)
	戻り値: なし
	***************************************************************************/
	void SetItemBaseScalePosQt(size_t Index,D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	virtual void Transform(
	vector<Object*>& Vec,            //オブジェクトの配列
	const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Context& Data					//ユーザーデータ
	);
	用途: オブジェクトを変化させる（仮想関数）
	戻り値: なし。
	***************************************************************************/
	virtual void Transform(vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Context& Data);
	/**************************************************************************
	virtual void Draw(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	vector<Object*>& Vec,            //オブジェクトの配列
	const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Context& Data					//ユーザーデータ
	);
	用途: オブジェクトを描画（純粋仮想関数）
	戻り値: なし。
	***************************************************************************/
	virtual void Draw(DrawPacket& i_DrawPacket);
	/**************************************************************************
	virtual void DrawShadowVolume(
	LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
	LPD3DXEFFECT	pEffect,			//エフェクトのポインタ
	D3DXMATRIX& mCameraView,			//カメラのビュー行列
	D3DXMATRIX& mCameraProj			//カメラのプロジェクション行列
	);
	用途: 影ボリュームを描画（仮想関数）
	戻り値: なし。
	***************************************************************************/
	virtual void DrawShadowVolume(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect,D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj);
};



/**************************************************************************
 class MultiPolygon : public MultiCommonMesh;
 用途: 複数のポリゴンクラス
****************************************************************************/
class MultiPolygon : public MultiCommonMesh{
	/**************************************************************************
	void CreateInctance(
	LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9インターフェイスへのポインタ
	);
	用途: インスタンスの構築
	戻り値: なし。（例外がthrowされる）
	***************************************************************************/
	void CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice);
protected:
	FLOAT m_Length;	//各面の長さ。
	UINT m_Sides;	//ポリゴンの面数。値は 3 以上である必要がある。
public:
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
	MultiPolygon(LPDIRECT3DDEVICE9 pD3DDevice,FLOAT Length,UINT Sides,wiz::OBJID id = OBJID_3D_MULTI_POLYGON,bool IsTextureActive = false);
	/**************************************************************************
	virtual ~MultiPolygon();
	用途: デストラクタ
	戻り値: なし
	***************************************************************************/
	virtual ~MultiPolygon();
	/**************************************************************************
	virtual void ChangeDevice(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
	用途: デバイス喪失による再構築（仮想関数）
	戻り値: なし。
	＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
};



/**************************************************************************
class MultiBox : public MultiCommonMesh;
用途: 複数の直方体クラス
****************************************************************************/
class MultiBox : public MultiCommonMesh{
	/**************************************************************************
	void CreateInctance(
	LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9インターフェイスへのポインタ
	);
	用途: インスタンスの構築
	戻り値: なし。（例外がthrowされる）
	***************************************************************************/
	void CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice);
protected:
	//テクスチャパターン
	int m_TexturePtn;
	//コモンメッシュのサイズ
	D3DXVECTOR3 m_Size;
public:
	/**************************************************************************
	MultiBox(
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
	MultiBox(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& size,wiz::OBJID id = OBJID_3D_MULTI_BOX,bool IsTextureActive = false,int TexturePtn = PtnUV_1_1);
	/**************************************************************************
	virtual ~MultiBox();
	用途: デストラクタ
	戻り値: なし
	***************************************************************************/
	virtual ~MultiBox();
	/**************************************************************************
	virtual void ChangeDevice(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
	用途: デバイス喪失による再構築（仮想関数）
	戻り値: なし。
	＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
	/**************************************************************************
	void GetOBB(
	size_t Index,
	OBB& obb	//取得するOBB
	);
	用途: 指定のインデックスの現在のOBBを得る
	戻り値: なし。インデックスが範囲外なら例外
	＊現在のOBBを代入する
	***************************************************************************/
	void GetOBB(size_t Index,OBB& obb);
};

/**************************************************************************
class ParallelMultiBox : public MultiBox;
用途: 複数の軸に平行な直方体クラス
****************************************************************************/
class ParallelMultiBox : public MultiBox{
public:
	/**************************************************************************
	ParallelMultiBox(
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
	ParallelMultiBox(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& size,wiz::OBJID id = OBJID_3D_MULTI_BOX_PARALLEL,bool IsTextureActive = false,int TexturePtn = PtnUV_1_1);
	/**************************************************************************
	virtual ~ParallelMultiBox();
	用途: デストラクタ
	戻り値: なし
	***************************************************************************/
	virtual ~ParallelMultiBox();
	/**************************************************************************
	size_t AddItem(
	D3DXVECTOR3& Scale,               //スケール（拡大縮小の倍率）
	D3DXVECTOR3& Pos,                //最初の位置
	D3DCOLORVALUE& Diffuse,         //ディフューズ色
	D3DCOLORVALUE& Specular,            //スペキュラ色
	D3DCOLORVALUE& Ambient,          //アンビエント色
	bool IsShadowActive = false,	//影を描画するかどうか
	LPTATRATEXTURE pTexture = 0			//テクスチャ
	);
	用途: アイテムを追加
	＊回転は受けつけない
	戻り値: 追加したインデックス（失敗時は例外をthrow）
	***************************************************************************/
	size_t AddItem(D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,bool IsShadowActive = false,LPTATRATEXTURE pTexture = 0);
	/**************************************************************************
	void GetAABB(
	size_t Index,			//インデックス
	AABB& Tgt	//矩形変数
	);
	//用途: 指定のインデックスの現在矩形を得る
	戻り値: なし。インデックスが範囲外なら例外
	***************************************************************************/
	void GetAABB(size_t Index,AABB& Tgt);
};

/**************************************************************************
 class MultiSphere : public MultiCommonMesh;
 用途: 複数の球クラス
****************************************************************************/
class MultiSphere : public MultiCommonMesh{
	/**************************************************************************
	void CreateInctance(
	LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9インターフェイスへのポインタ
	);
	用途: インスタンスの構築
	戻り値: なし。（例外がthrowされる）
	***************************************************************************/
	void CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice);
protected:
	FLOAT m_Radius;	//半径
	//主軸の回転スライス数
	UINT m_Slices;
	//主軸に沿ったスライス数
	UINT m_Stacks;
public:
	/**************************************************************************
	MultiSphere(
	LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9インターフェイスへのポインタ
	FLOAT radius,					//コモンメッシュを作成するときの半径
	bool IsTextureActive = false,	//テクスチャがあるかどうか
	UINT Slices = 18,				//主軸の回転スライス数
	UINT Stacks = 18				//主軸に沿ったスライス数
	);
	用途: コンストラクタ
	戻り値: なし（失敗時は例外をthrow）
	***************************************************************************/
	MultiSphere(LPDIRECT3DDEVICE9 pD3DDevice,FLOAT radius,wiz::OBJID id = OBJID_3D_MULTI_SPHERE,bool IsTextureActive = false,UINT Slices = 18,UINT Stacks = 18);
	/**************************************************************************
	virtual ~MultiSphere();
	用途: デストラクタ
	戻り値: なし
	***************************************************************************/
	virtual ~MultiSphere();
	/**************************************************************************
	virtual void ChangeDevice(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
	用途: デバイス喪失による再構築（仮想関数）
	戻り値: なし。
	＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
};

/**************************************************************************
 class MultiCylinder : public MultiCommonMesh;
 用途: 複数のシリンダークラス
****************************************************************************/
class MultiCylinder : public MultiCommonMesh{
	/**************************************************************************
	void CreateInctance(
	LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9インターフェイスへのポインタ
	);
	用途: インスタンスの構築
	戻り値: なし。（例外がthrowされる）
	***************************************************************************/
	void CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice);
	protected:
		FLOAT m_Radius1;	//z 軸の負の側の面の半径。
		FLOAT m_Radius2;	//z 軸の正の側の面の半径。
		FLOAT m_Length;		//z 軸方向の円柱の長さ。
		//主軸を回転軸としたスライスの数。
		UINT m_Slices;
		//主軸に沿ったスタック数。
		UINT m_Stacks;	
	public:
	/**************************************************************************
	MultiCylinder(
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
	MultiCylinder(LPDIRECT3DDEVICE9 pD3DDevice,FLOAT Radius1,FLOAT Radius2,FLOAT Length,wiz::OBJID id = OBJID_3D_MULTI_CYLINDER,bool IsTextureActive = false,UINT Slices = 18,UINT Stacks = 18);
	/**************************************************************************
	virtual ~MultiCylinder();
	用途: デストラクタ
	戻り値: なし
	***************************************************************************/
	virtual ~MultiCylinder();
	/**************************************************************************
	virtual void ChangeDevice(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
	用途: デバイス喪失による再構築（仮想関数）
	戻り値: なし。
	＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
};

/**************************************************************************
 class MultiTorus : public MultiCommonMesh;
 用途: 複数のトーラスクラス
****************************************************************************/
class MultiTorus : public MultiCommonMesh{
	/**************************************************************************
	void CreateInctance(
	LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9インターフェイスへのポインタ
	);
	用途: インスタンスの構築
	戻り値: なし。（例外がthrowされる）
	***************************************************************************/
	void CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice);
protected:
	//ドーナッツの半径
	FLOAT m_InnerRadius;
	//原点からドーナッツ中心までの半径
	FLOAT m_OuterRadius;
	//横断面の辺の数。値は 3 以上である必要がある。
	UINT m_Sides;
	//トーラスを構成する環の数。値は 3 以上である必要がある
	UINT m_Rings;		
public:
	/**************************************************************************
	MultiTorus(
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
	MultiTorus(LPDIRECT3DDEVICE9 pD3DDevice,FLOAT InnerRadius,FLOAT OuterRadius,wiz::OBJID id = OBJID_3D_MULTI_TAURUS ,bool IsTextureActive = false,UINT Sides = 18,UINT Rings = 18);
	/**************************************************************************
	virtual ~MultiTorus();
	用途: デストラクタ
	戻り値: なし
	***************************************************************************/
	virtual ~MultiTorus();
	/**************************************************************************
	virtual void ChangeDevice(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
	用途: デバイス喪失による再構築（仮想関数）
	戻り値: なし。
	＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
};



/**************************************************************************
 class SimpleCommonMesh : public CommonMesh;
 用途: 単純なコモンメッシュクラス
****************************************************************************/
class SimpleCommonMesh : public CommonMesh{
	friend class CustomShader;
protected:
	//このオブジェクトは有効かどうか
	bool m_IsActive;
	//表示のスケーリング
	//通常は変化させない
	D3DXVECTOR3 m_BaseScale;
	//初期位置のオブジェクトの中心
	D3DXVECTOR3 m_BasePos;
	//回転用のクオータニオン
	D3DXQUATERNION m_BaseQt;
	//現在の初期位置からの相対位置
	D3DXVECTOR3 m_Pos;
	//現在の初期位置からの回転用のクオータニオン
	D3DXQUATERNION m_Qt;
	//描画時に使用されるワールド変換行列
	D3DXMATRIX m_WorldMatrix;
	//マテリアル
	//D3DMATERIAL9 m_Material;
	//影を描画するかどうか
	bool m_IsShadowActive;
	//テクスチャ
	LPTATRATEXTURE m_pTexture;
	//グループ化する場合のマルチメッシュのポインタの配列
	vector<MultiCommonMesh*> m_MultiVec;
	/**************************************************************************
	SimpleCommonMesh(
	D3DXVECTOR3& Pos,                //位置
	D3DXVECTOR3& Rot,				//回転(ラジアン単位)
	D3DCOLORVALUE& Diffuse,         //ディフューズ色
	D3DCOLORVALUE& Specular,            //スペキュラ色
	D3DCOLORVALUE& Ambient,          //アンビエント色
	bool IsShadowActive = false,	//影を描画するかどうか
	LPTATRATEXTURE pTexture = 0,	//テクスチャを張るときは指定
	);
	用途: コンストラクタ
	戻り値: なし（失敗時は例外をthrow）
	***************************************************************************/
	SimpleCommonMesh(
		const D3DXVECTOR3&			Pos				,
		const D3DXVECTOR3&			Rot				,
		const D3DCOLORVALUE&		Diffuse			,
		const D3DCOLORVALUE&		Specular		,
		const D3DCOLORVALUE&		Ambient			,
		const wiz::OBJID			id				,
		const bool					IsShadowActive	= false	,
		const LPTATRATEXTURE		pTexture		= 0
	);
	/**************************************************************************
	virtual void ChangeDevice(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
	用途: デバイス喪失による再構築（仮想関数）
	戻り値: なし。（失敗時は例外をthrow）
	＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
public:
	/**************************************************************************
	virtual D3DXVECTOR3 GetPos();
	用途: 現在のポジションを返す
	戻り値: 現在のポジション
	***************************************************************************/
	virtual D3DXVECTOR3 GetPos(){ return m_BasePos + m_Pos;}
	/**************************************************************************
	virtual ~SimpleCommonMesh();
	用途: デストラクタ
	戻り値: なし
	***************************************************************************/
	virtual ~SimpleCommonMesh();
	/**************************************************************************
	size_t AddMultiMesh(
	MultiCommonMesh* pMultiCommonMesh	//マルチメッシュのポインタ
	);
	用途: マルチメッシュを追加
	戻り値: 追加した配列のインデックス
	***************************************************************************/
	size_t AddMultiMesh(MultiCommonMesh* pMultiCommonMesh);
	/**************************************************************************
	size_t GetMultiMeshCount();
	用途: マルチメッシュの数を返す
	戻り値: マルチメッシュ配列の数
	***************************************************************************/
	size_t GetMultiMeshCount();
	/**************************************************************************
	MultiCommonMesh* GetMultiCommonMesh(size_t Index);
	用途: 指定したインデックスのマルチメッシュを返す
	戻り値: マルチメッシュのポインタ（範囲外は例外）
	***************************************************************************/
	MultiCommonMesh* GetMultiCommonMesh(size_t Index);
	/**************************************************************************
	bool IsActive();
	用途: オブジェクトが有効かどうかを調べる
	戻り値: 有効ならTRUE、無効ならFALSE
	***************************************************************************/
	bool IsActive();
	/**************************************************************************
	void SetActive(
	bool val		//したいしたい値（trueかfalse）
	);
	用途:このオブジェクトが有効かどうかを設定する
	戻り値: なし、
	***************************************************************************/
	void SetActive(bool val);
	/**************************************************************************
	void GetMaterial(
	D3DMATERIAL9& Material	//現在のマテリアル
	);
	用途: マテリアルを取得する
	戻り値: なし（Materialにマテリアルを返す）
	***************************************************************************/
	void GetMaterial(D3DMATERIAL9& Material);
	/**************************************************************************
	void SetMaterial(
	D3DMATERIAL9& Material	//設定するマテリアル
	);
	用途: マテリアルを設定する
	戻り値: なし
	***************************************************************************/
	void SetMaterial(D3DMATERIAL9& Material);

	/**************************************************************************
	bool IsTextureActive();
	用途: テクスチャが有効かどうかを調べる
	戻り値: 有効ならTRUE、無効ならFALSE
	＊テクスチャを変更する場合は、先に有効かどうか調査すること
	***************************************************************************/
	bool IsTextureActive();

	/**************************************************************************
	LPTATRATEXTURE GetTexture();
	用途: テクスチャを取得する
	戻り値: 現在のテクスチャ（ない場合は0が返る）
	***************************************************************************/
	LPTATRATEXTURE GetTexture();
	/**************************************************************************
	void SetTexture(
	LPTATRATEXTURE pTexture	//設定するテクスチャ
	);
	用途: テクスチャを設定する
	戻り値: なし
	***************************************************************************/
	void SetTexture(LPTATRATEXTURE pTexture);

	/**************************************************************************
	bool IsShadowActive();
	用途: 影が有効かどうかを調べる
	戻り値: 有効ならTRUE、無効ならFALSE
	***************************************************************************/
	bool IsShadowActive();

	/**************************************************************************
	void SetShadowActive(
	bool val		//したいしたい値（trueかfalse）
	);
	用途: 影が有効かどうかを設定する
	戻り値: なし、
	***************************************************************************/
	void SetShadowActive(bool val);

	/**************************************************************************
	void GetWorldPos(
	D3DXVECTOR3& Pos	//現在のワールド位置
	);
	用途: ワールド位置を取得する
	戻り値: なし（Posにワールド位置を返す）
	***************************************************************************/
	void GetWorldPos(D3DXVECTOR3& Pos);

	/**************************************************************************
	void GetWorldRot(
	D3DXVECTOR3& Rot	//現在のワールド回転
	);
	用途: ワールド回転を取得する
	戻り値: なし（Rotにワールド回転を返す）
	***************************************************************************/
	void GetWorldRot(D3DXVECTOR3& Rot);
	/**************************************************************************
	void GetWorldQt(
	D3DXQUATERNION& Qt	//現在のワールド回転
	);
	用途: ワールド回転を取得する
	戻り値: なし（Qtにワールド回転を返す）
	***************************************************************************/
	void GetWorldQt(D3DXQUATERNION& Qt);
	/**************************************************************************
	void GetWorldScale(
	D3DXVECTOR3& Scale	//現在のワールドスケール
	);
	用途: ワールドスケールを取得する
	＊この関数はGetBaseScale関数と同じ
	戻り値: なし（Scaleにワールドスケーリングを返す）
	***************************************************************************/
	void GetWorldScale(D3DXVECTOR3& Scale);
	/**************************************************************************
	void GetWorld(
	D3DXVECTOR3& Scale,	//現在のワールドスケール
	D3DXVECTOR3& Pos,	//現在のワールド位置
	D3DXVECTOR3& Rot,	//現在のワールド回転（オイラー各）
	D3DXQUATERNION& Qt	//現在のワールド回転（クオータニオン）
	);
	用途: すべてのワールド値を取得する
	戻り値: なし（参照にワールド値を返す）
	***************************************************************************/
	void GetWorld(D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot,D3DXQUATERNION& Qt);
	/**************************************************************************
	void GetWorldMatrix(
	D3DXMATRIX& mtWorld
	);
	用途:ワールド変換を取得する
	戻り値: なし。mtWorldに変換行列をセットする
	***************************************************************************/
	void GetWorldMatrix(D3DXMATRIX& mtWorld);
	/**************************************************************************
	void CalcWorldMatrix();
	用途:ワールド変換を計算する
	戻り値: なし。現在の変換をもとにワールド行列を計算する
	***************************************************************************/
	void CalcWorldMatrix();
	/**************************************************************************
	void SimpleCommonMesh::CalcMatrix(D3DXMATRIX mPos , D3DXMATRIX mScale , D3DXMATRIX mRotZ);
	用途:ワールド変換を計算する
	戻り値: なし。現在の変換をもとにワールド行列を計算する
	***************************************************************************/
	void CalcMatrix(D3DXMATRIX mPos , D3DXMATRIX mScale , D3DXMATRIX mRot);
	/**************************************************************************
	void GetLocalPosQt(
	D3DXVECTOR3& Pos,	//現在の相対位置
	D3DXQUATERNION& Qt	//現在の相対回転
	);
	用途: 相対値を取得する(クオータニオン版)
	戻り値: なし
	***************************************************************************/
	void GetLocalPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	void GetLocalPosRot(
	D3DXVECTOR3& Pos,	//現在の相対位置
	D3DXVECTOR3& Rot	//現在の回転
	);
	用途: 相対値を取得する
	戻り値: なし
	***************************************************************************/
	void GetLocalPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);

	/**************************************************************************
	void SetLocalPosQt(
	D3DXVECTOR3& Pos,	//相対位置
	D3DXQUATERNION& Qt	//相対回転
	);
	用途: 相対値を設定する(クオータニオン版)
	戻り値: なし
	***************************************************************************/
	void SetLocalPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	void SetLocalPosRot(
	D3DXVECTOR3& Pos,	//相対位置
	D3DXVECTOR3& Rot	//回転
	);
	用途: 相対値を設定する
	戻り値: なし
	***************************************************************************/
	void SetLocalPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);


	/**************************************************************************
	void MoveToPosRot(
	D3DXVECTOR3& Pos,	//動かす相対位置
	D3DXVECTOR3& Rot	//動かす回転
	);
	用途: 相対値を移動し回転する
	戻り値: なし
	***************************************************************************/
	void MoveToPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	/**************************************************************************
	void MoveToPosQt(
	D3DXVECTOR3& Pos,	//動かす相対位置
	D3DXQUATERNION& Qt	//動かす回転
	);
	用途: 相対値を移動し回転する(クオータニオン版)
	戻り値: なし
	***************************************************************************/
	void MoveToPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);

	/**************************************************************************
	void MoveAtPosRot(
	D3DXVECTOR3& Pos,	//新しい相対位置
	D3DXVECTOR3& Rot	//新しい回転
	);
	用途: 相対値を設定しなおす
	戻り値: なし
	***************************************************************************/
	void MoveAtPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	/**************************************************************************
	void MoveAtPosQt(
	D3DXVECTOR3& Pos,	//新しい相対位置
	D3DXQUATERNION& Qt	//新しい回転
	);
	用途: 相対値を設定しなおす(クオータニオン版)
	戻り値: なし
	***************************************************************************/
	void MoveAtPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	void MoveAtIdentity();
	用途: 最初に作成された位置からの指定する相対位置をクリアする
	戻り値: なし
	***************************************************************************/
	void MoveAtIdentity();
	/**************************************************************************
	void GetBaseScalePosRot(
	D3DXVECTOR3& Scale,	//スケーリングの参照
	D3DXVECTOR3& Pos,	//ベース位置の参照
	D3DXVECTOR3& Rot	//ベース回転の参照
	);
	用途: 最初に作成されたスケーリングと位置と回転を同時に取り出す
	戻り値: なし
	***************************************************************************/
	void GetBaseScalePosRot(D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	/**************************************************************************
	void GetBaseScalePosQt(
	D3DXVECTOR3& Scale,	//スケーリングの参照
	D3DXVECTOR3& Pos,	//ベース位置の参照
	D3DXQUATERNION& Qt	//ベース回転クオータニオンの参照
	);
	用途: 最初に作成されたスケーリングと位置と回転を同時に取り出す（クオータニオン版）
	戻り値: なし
	***************************************************************************/
	void GetBaseScalePosQt(D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	void SetBaseScale(
	D3DXVECTOR3& Scale	//新しいベーススケーリング
	);
	用途: 最初に作成されたスケーリングを変更する
	戻り値: なし
	***************************************************************************/
	void SetBaseScale(D3DXVECTOR3& Scale);
	/**************************************************************************
	void SetBasePos(
	D3DXVECTOR3& Pos	//新しいベース位置
	);
	用途: 最初に作成された位置を変更する
	戻り値: なし
	***************************************************************************/
	void SetBasePos(D3DXVECTOR3& Pos);
	/**************************************************************************
	void SetPos(
	D3DXVECTOR3& Pos	//新しいベース位置
	);
	用途: 位置を変更する
	戻り値: なし
	***************************************************************************/
	void SetPos(D3DXVECTOR3& Pos);
	/**************************************************************************
	void SetBaseRot(
	D3DXVECTOR3& Rot	//新しいベース回転
	);
	用途: 最初に作成された回転を変更する
	戻り値: なし
	***************************************************************************/
	void SetBaseRot(D3DXVECTOR3& Rot);
	/**************************************************************************
	void SetBaseQt(
	D3DXQUATERNION& Qt	//新しいベース回転
	);
	用途: 最初に作成された回転を変更する(クオータニオン版)
	戻り値: なし
	***************************************************************************/
	void SetBaseQt(D3DXQUATERNION& Qt);
	/**************************************************************************
	void SetBaseScalePosRot(
	D3DXVECTOR3& Scale,	//新しいベーススケーリング
	D3DXVECTOR3& Pos,	//新しいベース位置
	D3DXVECTOR3& Rot	//新しいベース回転
	);
	用途: 最初に作成されたスケーリングと位置と回転を同時に変更する
	戻り値: なし
	***************************************************************************/
	void SetBaseScalePosRot(const D3DXVECTOR3& Scale,const D3DXVECTOR3& Pos,const D3DXVECTOR3& Rot);
	/**************************************************************************
	void SetBaseScalePosQt(
	D3DXVECTOR3& Scale,	//新しいベーススケーリング
	D3DXVECTOR3& Pos,	//新しいベース位置
	D3DXQUATERNION& Qt	//新しいベース回転
	);
	用途: 最初に作成されたスケーリングと位置と回転を同時に変更する(クオータニオン版)
	戻り値: なし
	***************************************************************************/
	void SetBaseScalePosQt(D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	virtual void Transform(
	vector<Object*>& Vec,            //オブジェクトの配列
	const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Context& Data					//ユーザーデータ
	);
	用途: オブジェクトを変化させる（仮想関数）
	戻り値: なし。
	***************************************************************************/
	virtual void Transform(vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Context& Data);
	/**************************************************************************
	virtual void Draw(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	vector<Object*>& Vec,            //オブジェクトの配列
	const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Context& Data					//ユーザーデータ
	);
	用途: オブジェクトを描画（純粋仮想関数）
	戻り値: なし。
	***************************************************************************/
	virtual void Draw(DrawPacket& i_DrawPacket);
	/**************************************************************************
	virtual void DrawShadowVolume(
	LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
	LPD3DXEFFECT	pEffect,			//エフェクトのポインタ
	D3DXMATRIX& mCameraView,			//カメラのビュー行列
	D3DXMATRIX& mCameraProj			//カメラのプロジェクション行列
	);
	用途: 影ボリュームを描画（仮想関数）
	戻り値: なし。
	***************************************************************************/
	virtual void DrawShadowVolume(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect,D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj);
};

/**************************************************************************
class Polygon : public SimpleCommonMesh;
用途: 単純なポリゴンクラス
****************************************************************************/
class Polygon : public SimpleCommonMesh{
	/**************************************************************************
	void CreateInctance(
	LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9インターフェイスへのポインタ
	);
	用途: インスタンスの構築
	戻り値: なし。（例外がthrowされる）
	***************************************************************************/
	void CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice);
protected:
	FLOAT m_Length;	//各面の長さ。
	UINT m_Sides;	//ポリゴンの面数。値は 3 以上である必要がある。
public:
	/**************************************************************************
	Polygon(
	LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9インターフェイスへのポインタ
	FLOAT Length,					//各面の長さ
	UINT Sides,						//ポリゴン面数
	D3DXVECTOR3& pos,                //位置
	D3DXVECTOR3& rot,				//回転(ラジアン単位)
	D3DCOLORVALUE& Diffuse,         //ディフューズ色
	D3DCOLORVALUE& Specular,            //スペキュラ色
	D3DCOLORVALUE& Ambient,          //アンビエント色
	bool IsShadowActive = false,	//影を描画するかどうか
	LPTATRATEXTURE pTexture = 0	//テクスチャを張るときは指定
	);
	用途: コンストラクタ
	戻り値: なし（失敗時は例外をthrow）
	***************************************************************************/
	Polygon(
		const LPDIRECT3DDEVICE9		pD3DDevice		,
		const FLOAT					Length			,
		const UINT					Sides			,
		const D3DXVECTOR3&			pos				,
		const D3DXVECTOR3&			rot				,
		const D3DCOLORVALUE&		Diffuse			,
		const D3DCOLORVALUE&		Specular		,
		const D3DCOLORVALUE&		Ambient			,
		const wiz::OBJID			id				= OBJID_3D_POLYGON	,
		const bool					IsShadowActive	= false				,
		const LPTATRATEXTURE		pTexture		= 0
	);
	/**************************************************************************
	virtual ~Polygon();
	用途: デストラクタ
	戻り値: なし
	***************************************************************************/
	virtual ~Polygon();
	/**************************************************************************
	virtual void ChangeDevice(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
	用途: デバイス喪失による再構築（仮想関数）
	戻り値: なし。（失敗時は例外をthrow）
	＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
};



/**************************************************************************
class Box : public SimpleCommonMesh;
用途: ボックスクラス
****************************************************************************/
class Box : public SimpleCommonMesh{
	/**************************************************************************
	void CreateInctance(
	LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9インターフェイスへのポインタ
	);
	用途: インスタンスの構築
	戻り値: なし。（例外がthrowされる）
	***************************************************************************/
	void CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice);
protected:
	D3DXVECTOR3 m_Size;  //大きさ
	int m_TexturePtn;	//テクスチャパターン
public:
	/**************************************************************************
	Box(
	LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9インターフェイスへのポインタ
	D3DXVECTOR3& size,               //大きさ
	D3DXVECTOR3& pos,                //位置
	D3DXVECTOR3& rot,				//回転(ラジアン単位)
	D3DCOLORVALUE& Diffuse,         //ディフューズ色
	D3DCOLORVALUE& Specular,            //スペキュラ色
	D3DCOLORVALUE& Ambient,          //アンビエント色
	bool IsShadowActive = false,	//影を描画するかどうか
	LPTATRATEXTURE pTexture = 0,	//テクスチャを張るときは指定
	int TexturePtn = PtnUV_1_1		//テクスチャのパターン
	);
	用途: コンストラクタ
	戻り値: なし（失敗時は例外をthrow）
	***************************************************************************/
	Box(
		const LPDIRECT3DDEVICE9		pD3DDevice		,
		const D3DXVECTOR3&			size			,
		const D3DXVECTOR3&			pos				,
		const D3DXVECTOR3&			rot				,
		const D3DCOLORVALUE&		Diffuse			,
		const D3DCOLORVALUE&		Specular		,
		const D3DCOLORVALUE&		Ambient			,
		const wiz::OBJID			id				= OBJID_3D_BOX	,
		const bool					IsShadowActive	= false			,
		const LPTATRATEXTURE		pTexture		= 0				,
		const int					TexturePtn		= PtnUV_1_1
	);
	/**************************************************************************
	virtual ~Box();
	用途: デストラクタ
	戻り値: なし
	***************************************************************************/
	virtual ~Box();
	/**************************************************************************
	virtual void ChangeDevice(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
	用途: デバイス喪失による再構築（仮想関数）
	戻り値: なし。（失敗時は例外をthrow）
	＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
};

/**************************************************************************
 class ParallelBox : public Box;
 用途: 軸に平行な直方体クラス
****************************************************************************/
class ParallelBox : public Box{
public:
	/**************************************************************************
	ParallelBox(
	LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9インターフェイスへのポインタ
	D3DXVECTOR3& size,               //大きさ
	D3DXVECTOR3& pos,                //位置
	D3DCOLORVALUE& Diffuse,         //ディフューズ色
	D3DCOLORVALUE& Specular,            //スペキュラ色
	D3DCOLORVALUE& Ambient,          //アンビエント色
	bool IsShadowActive = false,	//影を描画するかどうか
	LPTATRATEXTURE pTexture = 0,	//テクスチャを張るときは指定
	int TexturePtn = PtnUV_1_1		//テクスチャのパターン
	);
	用途: コンストラクタ
	戻り値: なし（失敗時は例外をthrow）
	***************************************************************************/
	ParallelBox(
		const LPDIRECT3DDEVICE9		pD3DDevice		,
		const D3DXVECTOR3&			size			,
		const D3DXVECTOR3&			pos				,
		const D3DCOLORVALUE&		Diffuse			,
		const D3DCOLORVALUE&		Specular		,
		const D3DCOLORVALUE&		Ambient			,
		const wiz::OBJID			id				= OBJID_3D_BOX_PARALLEL		,
		const bool					IsShadowActive	= false						,
		const LPTATRATEXTURE		pTexture		= 0							,
		const int					TexturePtn		= PtnUV_1_1
	);
	/**************************************************************************
	virtual ~ParallelBox();
	用途: デストラクタ
	戻り値: なし
	***************************************************************************/
	virtual ~ParallelBox();
	/**************************************************************************
	void GetAABB(
	AABB& Tgt	//矩形変数
	);
	用途: 現在矩形を得る
	戻り値: なし。
	＊現在の矩形を代入する
	***************************************************************************/
	void GetAABB(AABB& Tgt);
};



/**************************************************************************
class Sphere : public SimpleCommonMesh;
用途: 球クラス
****************************************************************************/
class Sphere : public SimpleCommonMesh{
	/**************************************************************************
	void CreateInctance(
	LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9インターフェイスへのポインタ
	);
	用途: インスタンスの構築
	戻り値: なし。（例外がthrowされる）
	***************************************************************************/
	void CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice);
protected:
	//半径
	FLOAT m_Radius;
	//主軸の回転スライス数
	UINT m_Slices;
	//主軸に沿ったスライス数
	UINT m_Stacks;
public:
	/**************************************************************************
	Sphere(
	LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9インターフェイスへのポインタ
	FLOAT radius,                   //半径の大きさ
	D3DXVECTOR3& pos,                //最初の位置
	D3DXVECTOR3& rot,				//回転(ラジアン単位)
	D3DCOLORVALUE& Diffuse,         //ディフューズ色
	D3DCOLORVALUE& Specular,            //スペキュラ色
	D3DCOLORVALUE& Ambient,          //アンビエント色
	bool IsShadowActive = false,	//影を描画するかどうか
	LPTATRATEXTURE pTexture = 0,	//テクスチャを張るときは指定
	UINT Slices = 18,	//主軸の回転スライス数
	UINT Stacks = 18	//主軸に沿ったスライス数
	);
	用途: コンストラクタ
	戻り値: なし（失敗時は例外をthrow）
	***************************************************************************/
	Sphere(
		const LPDIRECT3DDEVICE9		pD3DDevice		,
		const FLOAT					radius			,
		const D3DXVECTOR3&			pos				,
		const D3DXVECTOR3&			rot				,
		const D3DCOLORVALUE&		Diffuse			,
		const D3DCOLORVALUE&		Specular		,
		const D3DCOLORVALUE&		Ambient			,
		const wiz::OBJID			id				= OBJID_3D_SPHERE	,
		const bool					IsShadowActive	= false				,
		const LPTATRATEXTURE		pTexture		= 0					,
		const UINT					Slices			= 18				,
		const UINT					Stacks			= 18
	);
	/**************************************************************************
	virtual ~Sphere();
	用途: デストラクタ
	戻り値: なし
	***************************************************************************/
	virtual ~Sphere();
	/**************************************************************************
	virtual void ChangeDevice(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
	用途: デバイス喪失による再構築（仮想関数）
	戻り値: なし。
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
};


/**************************************************************************
 class Cylinder : public SimpleCommonMesh;
 用途: シリンダークラス
****************************************************************************/
class Cylinder : public SimpleCommonMesh{
	/**************************************************************************
	 void CreateInctance(
	 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9インターフェイスへのポインタ
	 );
	 用途: インスタンスの構築
	 戻り値: なし。（例外がthrowされる）
	***************************************************************************/
	void CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice);
protected:
	FLOAT m_Radius1;
	FLOAT m_Radius2;
	FLOAT m_Length;
	//主軸を回転軸としたスライスの数。
	UINT m_Slices;
	//主軸に沿ったスタック数。
	UINT m_Stacks;	
public:
	/**************************************************************************
	 Cylinder(
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
		LPTATRATEXTURE pTexture = 0,	//テクスチャを張るときは指定
		UINT Slices = 18,		//主軸を回転軸としたスライスの数。
		UINT Stacks = 18		//主軸に沿ったスタック数。
		);
	 用途: コンストラクタ
	 戻り値: なし（失敗時は例外をthrow）
	***************************************************************************/
	Cylinder(
		const LPDIRECT3DDEVICE9 pD3DDevice			,
		const FLOAT Radius1							,
		const FLOAT Radius2							,
		const FLOAT Length							,
		const D3DXVECTOR3& pos						,
		const D3DXVECTOR3& rot						,
		const D3DCOLORVALUE& Diffuse				,
		const D3DCOLORVALUE& Specular				,
		const D3DCOLORVALUE& Ambient				,
		const wiz::OBJID id = OBJID_3D_CYLINDER		,
		const bool IsShadowActive = false			,
		const LPTATRATEXTURE pTexture = 0		,
		const UINT Slices = 18						,
		const UINT Stacks = 18
	);
	/**************************************************************************
	virtual ~Cylinder();
	用途: デストラクタ
	戻り値: なし
	***************************************************************************/
	virtual ~Cylinder();
	/**************************************************************************
		virtual void ChangeDevice(
		LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
		);
	 用途: デバイス喪失による再構築（仮想関数）
	 戻り値: なし。
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);

	///////////////////// ////////////////////
	//// 関数名     ：D3DXVECTOR3 getPos() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：DEAD OR ALIVE
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当者     ：本多寛之
	//// 備考       ：
	////            ：
	////
	D3DXVECTOR3 getPos() const;

	///////////////////// ////////////////////
	//// 関数名     ：FLOAT getRaduis1() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：Radius1
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当者     ：曳地 大洋
	//// 備考       ：
	////            ：
	////
	FLOAT getRadius1() const ;
	///////////////////// ////////////////////
	//// 関数名     ：FLOAT getRaduis2() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：Radius2
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当者     ：曳地 大洋
	//// 備考       ：
	////            ：
	////
	FLOAT getRadius2() const ;
};

/**************************************************************************
 class Torus : public SimpleCommonMesh;
 用途: トーラスクラス
****************************************************************************/
class Torus : public SimpleCommonMesh{
	/**************************************************************************
	void CreateInctance(
	LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9インターフェイスへのポインタ
	);
	用途: インスタンスの構築
	戻り値: なし。（例外がthrowされる）
	***************************************************************************/
	void CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice);
protected:
	//ドーナッツの半径
	FLOAT m_InnerRadius;
	//原点からドーナッツ中心までの半径
	FLOAT m_OuterRadius;
	//横断面の辺の数。値は 3 以上である必要がある。
	UINT m_Sides;
	//トーラスを構成する環の数。値は 3 以上である必要がある
	UINT m_Rings;		
public:
	/**************************************************************************
	Torus(
	LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9インターフェイスへのポインタ
	FLOAT InnerRadius,              //ドーナッツの半径
	FLOAT OuterRadius,              //原点からドーナッツ中心までの半径
	D3DXVECTOR3& pos,                //最初の位置
	D3DXVECTOR3& rot,				//回転(ラジアン単位)
	D3DCOLORVALUE& Diffuse,         //ディフューズ色
	D3DCOLORVALUE& Specular,            //スペキュラ色
	D3DCOLORVALUE& Ambient,          //アンビエント色
	bool IsShadowActive = false,	//影を描画するかどうか
	LPTATRATEXTURE pTexture = 0,	//テクスチャを張るときは指定
	UINT Sides = 18,	//横断面の辺の数。値は 3 以上である必要がある。
	UINT Rings = 18		//トーラスを構成する環の数。値は 3 以上である必要がある。     
	);
	用途: コンストラクタ
	戻り値: なし（失敗時は例外をthrow）
	***************************************************************************/
	Torus(
		const LPDIRECT3DDEVICE9		pD3DDevice		,
		const FLOAT					InnerRadius		,
		const FLOAT					OuterRadius		,
		const D3DXVECTOR3&			pos				,
		const D3DXVECTOR3&			rot				,
		const D3DCOLORVALUE&		Diffuse			,
		const D3DCOLORVALUE&		Specular		,
		const D3DCOLORVALUE&		Ambient			,
		const wiz::OBJID			id				= OBJID_3D_SPHERE	,
		const bool					IsShadowActive	= false				,
		const LPTATRATEXTURE	pTexture		= 0					,
		const UINT					Sides			= 18				,
		const UINT					Rings			= 18
	);
	/**************************************************************************
	virtual ~Torus();
	用途: デストラクタ
	戻り値: なし
	***************************************************************************/
	virtual ~Torus();
	/**************************************************************************
	virtual void ChangeDevice(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
	用途: デバイス喪失による再構築（仮想関数）
	戻り値: なし。
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
};

/**************************************************************************
 class SimpleCommonMeshGroup : public Object;
 用途: グループ化されたコモンメッシュをさらにグループ化する
 ＊派生クラスとして作成するのではなく、
 SimpleCommonMeshを包含関係にて取り込む
****************************************************************************/
class SimpleCommonMeshGroup : public Object{
protected:
	//元となるシンプルコモンメッシュ
	SimpleCommonMesh* m_pSimpleCommonMesh;
	struct GroupItem{
		//マテリアル
		D3DMATERIAL9 m_Material;
		//現在の初期位置からの相対位置
		D3DXVECTOR3 m_Pos;
		//現在の初期位置からの回転用のクオータニオン
		D3DXQUATERNION m_Qt;
		//派生クラスを作っても
		//削除できるように仮想デストラクタにしておく
		virtual ~GroupItem(){}
	};
	//GroupItemの配列
	vector<GroupItem*> m_ItemVec;
public:
	/**************************************************************************
	SimpleCommonMeshGroup(SimpleCommonMesh* pSimpleCommonMesh = 0)
	用途: コンストラクタ
	戻り値: なし（失敗時は例外をthrowする）
	＊あらかじめ作成したシンプルコモンメッシュを渡す。
	***************************************************************************/
	SimpleCommonMeshGroup(SimpleCommonMesh* pSimpleCommonMesh = 0,wiz::OBJID id = OBJID_UNK);
	/**************************************************************************
	virtual ~SimpleCommonMeshGroup();
	用途: デストラクタ
	戻り値: なし
	***************************************************************************/
	virtual ~SimpleCommonMeshGroup();
	/**************************************************************************
	virtual void ReleaseObj();
	用途: デバイス喪失によるリソースの開放（仮想関数）
	戻り値: なし。
	＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
	***************************************************************************/
	virtual void ReleaseObj();
	/**************************************************************************
	void SetSimpleCommonMesh(SimpleCommonMesh* pSimpleCommonMesh);
	用途: シンプルコモンメッシュの設定
	戻り値: なし。
	***************************************************************************/
	void SetSimpleCommonMesh(SimpleCommonMesh* pSimpleCommonMesh);
	/**************************************************************************
	const SimpleCommonMesh* GetSimpleCommonMesh() const;
	用途: 基準となるコモンメッシュを返す
	戻り値: 基準となるコモンメッシュのポインタ
	***************************************************************************/
	const SimpleCommonMesh* GetSimpleCommonMesh() const;
	/**************************************************************************
	size_t AddItem(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	用途: アイテムの登録
	戻り値: 追加したインデックス
	***************************************************************************/
	size_t AddItem(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	/**************************************************************************
	size_t GetItemCount();
	用途: 現在のアイテム数を得る
	戻り値: アイテム数
	***************************************************************************/
	size_t GetItemCount(){return  m_ItemVec.size();}
	/**************************************************************************
	void GetItemMaterial(
	size_t Index,	//取得するインデックス
	D3DMATERIAL9& Material	//現在のマテリアル
	);
	用途: マテリアルを取得する
	戻り値: なし（MaterialにIndexのマテリアルを返す）
	***************************************************************************/
	void GetItemMaterial(size_t Index,D3DMATERIAL9& Material);
	/**************************************************************************
	void SetItemMaterial(
	size_t Index,	//設定するインデックス
	D3DMATERIAL9& Material	//設定するマテリアル
	);
	用途: マテリアルを設定する
	戻り値: なし
	***************************************************************************/
	void SetItemMaterial(size_t Index,D3DMATERIAL9& Material);

	/**************************************************************************
	void GetItemLocalPosQt(
	size_t Index,	//取得するインデックス
	D3DXVECTOR3& Pos,	//現在の相対位置
	D3DXQUATERNION& Qt	//現在の相対回転
	);
	用途: 相対値を取得する(クオータニオン版)
	戻り値: なし
	***************************************************************************/
	void GetItemLocalPosQt(size_t Index,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	void GetItemLocalPosRot(
	size_t Index,	//取得するインデックス
	D3DXVECTOR3& Pos,	//現在の相対位置
	D3DXVECTOR3& Rot	//現在の回転
	);
	用途: 相対値を取得する
	戻り値: なし
	***************************************************************************/
	void GetItemLocalPosRot(size_t Index,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	/**************************************************************************
	void SetItemLocalPosQt(
	size_t Index,	//インデックス
	D3DXVECTOR3& Pos,	//相対位置
	D3DXQUATERNION& Qt	//相対回転
	);
	用途: 相対値を設定する(クオータニオン版)
	戻り値: なし
	***************************************************************************/
	void SetItemLocalPosQt(size_t Index,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	void SetItemLocalPosRot(
	size_t Index,	//インデックス
	D3DXVECTOR3& Pos,	//相対位置
	D3DXVECTOR3& Rot	//相対回転
	);
	用途: 相対値を設定する(クオータニオン版)
	戻り値: なし
	***************************************************************************/
	void SetItemLocalPosRot(size_t Index,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);

	/**************************************************************************
	virtual void ChangeDevice(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
	用途: デバイス喪失による再構築（仮想関数）
	戻り値: なし。
	＊デバイスが喪失したときに最構築時に呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
	/**************************************************************************
	virtual void Transform(
	vector<Object*>& Vec,            //オブジェクトの配列
	const CONTROLER_STATE* pCntlState,	//コントローラの状態
	Context& Data					//ユーザーデータ
	);
	用途: オブジェクトを変化させる（仮想関数）
	戻り値: なし。
	***************************************************************************/
	virtual void Transform(vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Context& Data);
	/**************************************************************************
	virtual void Draw(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	vector<Object*>& Vec,            //オブジェクトの配列
	const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Context& Data					//ユーザーデータ
	);
	用途: オブジェクトを描画（純粋仮想関数）
	戻り値: なし。
	***************************************************************************/
	virtual void Draw(DrawPacket& i_DrawPacket);
	/**************************************************************************
	virtual void DrawShadowVolume(
	LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
	LPD3DXEFFECT	pEffect,			//エフェクトのポインタ
	D3DXMATRIX& mCameraView,			//カメラのビュー行列
	D3DXMATRIX& mCameraProj			//カメラのプロジェクション行列
	);
	用途: 影ボリュームを描画（仮想関数）
	戻り値: なし。
	***************************************************************************/
	virtual void DrawShadowVolume(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect,D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj);
};

class PrimitiveCylinder : public Cylinder{
	
public:
	PrimitiveCylinder(LPDIRECT3DDEVICE9 pD3DDevice,
          D3DCOLORVALUE& Diffuse,
		  D3DCOLORVALUE& Specular,
		  D3DCOLORVALUE& Ambient,
		  wiz::OBJID id = OBJID_3D_CYLINDER,
		  LPTATRATEXTURE pTexture = 0 )
	:Cylinder(pD3DDevice, 0.5, 0.5, 1, g_vZero, g_vZero, Diffuse, Specular, Ambient,id, false, pTexture)
	{
		
	}

	/////////////////// ////////////////////
	//// 用途       ：PrimitiveCylinder(
	////									LPDIRECT3DDEVICE9 pD3DDevice,LPTATRATEXTURE pTexture,
	////									float Radius1,float Radius2,float Lenght,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
	////									D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
	////									wiz::OBJID id = OBJID_3D_MAGNET)
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：Player用のコンストラクタ
	//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	////			  :   LPTATRATEXTURE pTexture,  //テクスチャ	
	////		      :   float Radius1						//円の直径1
	////		      :   float Radius2						//円の直径2
	////			  :   float Lenght						//高さ
	////		      :   D3DXVECTOR3 &vRot				//回転角
	////		      :   D3DXVECTOR3 &vPos				//位置
	////              :   D3DCOLORVALUE& Diffuse,		//ディフューズ色
	////              :   D3DCOLORVALUE& Specular,		//スペキュラ色
	////              :   D3DCOLORVALUE& Ambient,		//アンビエント色
	////              :   wiz::OBJID id = OBJID_3D_MAGNET //ID
	//// 戻値       ：なし
	//// 担当者     ：本多寛之
	//// 備考       ：
	////	
	PrimitiveCylinder(
			LPDIRECT3DDEVICE9 pD3DDevice,
			LPTATRATEXTURE pTexture,
			float Radius1,
			float Radius2,
			float Lenght,
			D3DXVECTOR3 &vRot,
			D3DXVECTOR3 &vPos,
			D3DCOLORVALUE& Diffuse,
			D3DCOLORVALUE& Specular,
			D3DCOLORVALUE& Ambient,
			wiz::OBJID id = OBJID_3D_CYLINDER)
    :Cylinder(pD3DDevice, Radius1, Radius2, Lenght,
			  vPos, vRot, Diffuse, Specular, Ambient,id, false, pTexture)
	{
		
	}
	
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/


/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
class PrimitiveBox : public Box {
public:
	PrimitiveBox(LPDIRECT3DDEVICE9 pD3DDevice,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		wiz::OBJID id = OBJID_3D_BOX,
		LPTATRATEXTURE pTexture = 0)
		:Box( pD3DDevice, g_vOne, g_vZero, g_vZero, Diffuse, Specular, Ambient, id, false, pTexture, PtnUV_1_4)
	{
	}


};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
class PrimitiveSphere : public Sphere {
	public:
		PrimitiveSphere(
			const LPDIRECT3DDEVICE9		pD3DDevice	,
			const D3DCOLORVALUE&		Diffuse		,
			const D3DCOLORVALUE&		Specular	,
			const D3DCOLORVALUE&		Ambient		,
			const LPTATRATEXTURE		pTexture	= 0,
			const wiz::OBJID			id			= OBJID_3D_SPHERE
		)
			:Sphere( pD3DDevice,0.5f, g_vZero, g_vZero,Diffuse, Specular, Ambient,id, false, pTexture ,18, 18){}
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
class PrimitivePlate {
protected:
	LPTATRATEXTURE		m_pTexture	;
	D3DXMATRIX				m_mMatrix	;
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	D3DXVECTOR3				m_vPos;
	float					m_vCameraY;

	//	: 頂点データの定義
	struct	Vertex
	{
		D3DXVECTOR3	vPos ;		//	: 頂点は、位置座標データを持つ
		DWORD		dwColor ;	//	: 頂点は、色データを持つ
		D3DXVECTOR2	vTex ;		//	: 頂点は、テクスチャ座標を持つ

		//	: デフォルトコンストラクタ
		Vertex()
		{}
		//	: 初期化を簡略化するための引数付きコンストラクタ
		Vertex( const D3DXVECTOR3& i_vPos, DWORD i_dwColor, const D3DXVECTOR2& i_vTex )
			: vPos( i_vPos ), dwColor( i_dwColor ), vTex( i_vTex )
		{}
		//	: デストラクタ
		~Vertex()
		{}

		//	: この頂点データの形式を返す
		static DWORD	getFVF()
		{
			return D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 ;
		}

		//	: この頂点データのデータサイズを返す
		static int		getSize()
		{
			return sizeof( Vertex );
		}
	};
	Vertex	*v ;	//	: 頂点バッファが内包する頂点データへのポインタを格納するためのポインタ

public:
	PrimitivePlate(LPDIRECT3DDEVICE9 pD3DDevice, LPTATRATEXTURE i_pTexture = NULL, Color i_Color = 0xFFFF0000);
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
	virtual void Update(int i_iPtn) ;
	void setMatrix(D3DXMATRIX& i_mMatrix){
		m_mMatrix = i_mMatrix ;
	}

	D3DXVECTOR3	getPos(){
		return	v->vPos;
	}
	void setMatrixPos( D3DXVECTOR3 i_vPos ){
		D3DXMATRIX	mPos;
		D3DXMatrixTranslation( &mPos, i_vPos.x, i_vPos.y, i_vPos.x );
		m_mMatrix = mPos ;
	}
};

//***********************************************
class PlateObject : public PrimitivePlate, Object{
public:
	PlateObject(LPDIRECT3DDEVICE9 pD3DDevice, LPTATRATEXTURE i_pTexture = NULL, Color i_Color = 0xFFFF0000)
		:PrimitivePlate( pD3DDevice, i_pTexture, i_Color)
		,Object( OBJID_UNK )
	{
	}
};

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
inline D3DXVECTOR3 T2DPointTo3DPoint(Camera* i_pCamera,Point po){
	if( !i_pCamera ) return g_vZero ;
	float fXMagnification		= 50.0f / STANDARD_WINDOW_WIDTH ;		//	: 伸縮比率
	float fXHalfCorrection		= po.x - (STANDARD_WINDOW_WIDTH /2) ;	//	: 

	float fYMagnification		= 28.3f / STANDARD_WINDOW_HEIGHT;		//	: 伸縮比率
	float fYReverseCoordinate	= (STANDARD_WINDOW_HEIGHT /2)  -po.y ;	//	: ハーフ座標化
	//	: マウス座標の３Ｄ変換
	return D3DXVECTOR3( 
		(    fXHalfCorrection * fXMagnification ) + i_pCamera->getEye().x ,
		( fYReverseCoordinate * fYMagnification ) + i_pCamera->getEye().y ,
		0.0f
	);
}
inline Point T3DPointTo2DPoint(Camera* i_pCamera,D3DXVECTOR3 po){
	if( !i_pCamera ) return Point(0,0) ;
	float fXMagnification		= 50.0f / STANDARD_WINDOW_WIDTH ;		//	: 伸縮比率
	float fXHalfCorrection		= po.x  / fXMagnification - i_pCamera->getEye().x / fXMagnification ;

	float fYMagnification		= 28.3f / STANDARD_WINDOW_HEIGHT;		//	: 伸縮比率
	float fYReverseCoordinate	= po.y  / fYMagnification - i_pCamera->getEye().y / fYMagnification ;

	float x =    fXHalfCorrection     +  (STANDARD_WINDOW_WIDTH /2) ;
	float y =    -fYReverseCoordinate + (STANDARD_WINDOW_HEIGHT /2) ;
	return Point( (int)x , (int)y );

}
class Cursor3D : public Cursor2D{
	static D3DXVECTOR3	m_vMousePos;
public:
	static D3DXVECTOR3 getPos(Camera* i_pCamera);
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//**************************************************************************
// class DrawSphere : public Object;
//
// 担当者  ; 鴫原 徹
// 用途    : Sphereの可視化
//**************************************************************************
class DrawSphere : public Sphere{
	IDirect3DVertexBuffer9* m_pVB;
	//クラス内構造体
	//ここでしか使用しないので、内部に持つ
	SPHERE m_TargetSphere ;
	static bool isEnableDraw ;
public:
	/////////////////// ////////////////////
	//// 関数名     ：DrawSphere(LPDIRECT3DDEVICE9 pD3DDevice)
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：Sphere
	//// 引数       ：  
	//// 戻値       ：なし（失敗時は例外をthrow）
	//// 担当者     ：
	//// 備考       ：
	////            ：
	////
	DrawSphere(LPDIRECT3DDEVICE9 pD3DDevice, SPHERE i_Sphere, Color i_Color = 0xFF0000FF, wiz::OBJID id = OBJID_3D_DRAWOBB);

	/////////////////// ////////////////////
	//// 関数名     ：DrawSphere::~DrawSphere()
	//// カテゴリ   ：デストラクタ
	//// 用途       ：ガイドライン破棄時処理
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当者     ：(山ノ井先生のひな形より)
	//// 備考       ：
	////            ：
	////
	virtual ~DrawSphere();

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

	/////////////////// ////////////////////
	//// 関数名     ：
	//// カテゴリ   ：
	//// 用途       ：
	//// 引数       ：
	////            ：
	//// 戻値       ：
	//// 担当者     ：
	//// 備考       ：
	////            ：
	////
	void UpdateSPHERE( SPHERE i_SPHERE){
		m_TargetSphere = i_SPHERE ;
		SetBaseScale( g_vOne * i_SPHERE.m_Radius );
		SetBasePos( m_TargetSphere.m_Center );
	}
};


//**************************************************************************
// class DrawOBB : public Object;
//
// 担当者  ; 鴫原 徹
// 用途    : OBBの可視化
//**************************************************************************
class DrawOBB : public Object{
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	float	m_fTimeAccumulator;

	//クラス内構造体
	//ここでしか使用しないので、内部に持つ
	struct CUSTOMVERTEX
	{
		D3DXVECTOR3 vec;
		DWORD color;
	};
	OBB m_TargetObb ;
	static bool isEnableDraw ;
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
	DrawOBB(LPDIRECT3DDEVICE9 pD3DDevice, OBB i_OBB, Color i_Color = 0xFFFF0000, wiz::OBJID id = OBJID_3D_DRAWOBB);
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
	virtual ~DrawOBB();
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
//**************************************************************************
// class DrawOBBLite : public Object;
//
// 担当者  ; 鴫原 徹
// 用途    : OBBの可視化
//**************************************************************************
class DrawOBBLite : public Object{
	IDirect3DVertexBuffer9* m_pVB;
	float m_fTimeAccumulator;
	//クラス内構造体
	//ここでしか使用しないので、内部に持つ
	struct CUSTOMVERTEX
	{
		D3DXVECTOR3 vec;
		DWORD color;
	};
	OBB m_TargetObb ;
	static bool isEnableDraw ;
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
	DrawOBBLite(LPDIRECT3DDEVICE9 pD3DDevice, OBB i_OBB, Color i_Color, wiz::OBJID id = OBJID_3D_DRAWOBB);
public:
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
	virtual ~DrawOBBLite();
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

	static void Add(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& Vec, OBB i_OBB, Color i_Color = 0xFFFF0000){
		#ifdef ON_DEBUGGINGPROCESS
			if( isEnableDraw ){
				Vec.push_back( new DrawOBBLite(pD3DDevice, i_OBB, i_Color) );
			}
		#endif
	}

};

	}//end of namespace baseitems.
	using namespace baseitems;
}//end of namespace wiz.
