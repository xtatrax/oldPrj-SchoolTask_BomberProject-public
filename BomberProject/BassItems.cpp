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

namespace baseobject{

/**************************************************************************
 Camera 定義部
****************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：Camera::Camera(D3DXVECTOR3& Eye,D3DXVECTOR3& At,FLOAT Near,FLOAT Far,FLOAT FovY)
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
Camera::Camera(D3DXVECTOR3& Eye,D3DXVECTOR3& At,FLOAT Near,FLOAT Far,FLOAT FovY,wiz::OBJID id)
:Object(id),m_Eye(Eye),m_At(At),m_Near(Near),m_Far(Far),m_FovY(FovY)/*,CameraKyori(0.0f)*/,CameraFlg(true)
{
    D3DXMatrixIdentity(&m_View);
    D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
            &D3DXVECTOR3( 0.0f, 1.0f, 0.0f));
}
/////////////////// ////////////////////
//// 関数名     ：Camera::~Camera()
//// カテゴリ   ：デストラクタ
//// 用途       ：カメラの破棄時処理
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：(山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
Camera::~Camera(){
}
/////////////////// ////////////////////
//// 関数名     ：virtual voidCamera:: Update( LPDIRECT3DDEVICE9 pD3DDevice
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
void Camera::Update(UpdatePacket& i_UpdatePacket
	){

#ifdef DEBUG_KEYMOVE_CAMERA_ON
	if(pCntlState[0].Gamepad.fThumbLX > 0){
		CameraFlg = true;
	}

	if(pCntlState[0].Gamepad.fThumbLX < 0){
		CameraFlg = false;
	}

    if(pCntlState[0].bConnected){
		//Dパッド上
		//注視点Yを上
        if(pCntlState[0].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP){
			m_Eye.y += 0.1f;
			//MAX5.0
            //if(m_Eye.y > 5.0f){
            //    m_Eye.y = 5.0f;
            //}
        }
		//Dパッド下
		//注視点Yを下
        if(pCntlState[0].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN){
			m_Eye.y -= 0.1f;
			//MIN0.0
            //if(m_Eye.y < 0.0f){
            //    m_Eye.y = 0.0f;
            //}
        }
		////カメラ位置と注視点の間のベクトルを算出
		//D3DXVECTOR3 span = m_Eye - m_At;
		////正規化
		//D3DXVec3Normalize(&span,&span);
		////分割
		//span = span * 0.1f;
		//Dパッド左
		//カメラを引く
        if(pCntlState[0].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT){
			//カメラ位置を引く
			m_Eye.z += 0.1f;
			//MAX5.0
            //if(m_Eye.z > 50.0f){
            //    m_Eye.z= 50.0f;
            //}
        }
		//Dパッド右
		//カメラを寄る
        if(pCntlState[0].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT){
			//カメラ位置を寄る
			m_Eye.z -= 0.1f;
			//MAX5.0
            //if(m_Eye.z < -50.0f){
            //    m_Eye.z= -50.0f;
            //}
        }
		//Dパッド左
		//カメラを引く
		if(pCntlState[0].Gamepad.bLeftTrigger){
			//カメラ位置を引く
			m_Eye.x += 0.1f;
			//MAX5.0
            //if(m_Eye.x > 50.0f){
            //    m_Eye.x= 50.0f;
            //}
        }
		//Dパッド右
		//カメラを寄る
		if(pCntlState[0].Gamepad.bRightTrigger ){
			//カメラ位置を寄る
			m_Eye.x -= 0.1f;
			//MAX5.0
            //if(m_Eye.x < -50.0f){
            //    m_Eye.x= -50.0f;
            //}
        }
    }
#endif
}

/////////////////// ////////////////////
//// 関数名     ：void Camera::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// カテゴリ   ：仮想関数
//// 用途       ：カメラを設置
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,				//オブジェクトの配列
//// 戻値       ：なし
//// 担当者     ：(山ノ井先生のひな形より)
//// 備考       ：Objectクラスの純粋仮想関数
////            ：
////
void Camera::Draw(DrawPacket& i_DrawPacket) {
    // ビューポートの取得
    D3DVIEWPORT9 vp;
    if(FAILED(i_DrawPacket.pD3DDevice->GetViewport(&vp))){
        return;
    }
    D3DXMatrixIdentity(&m_View);
    D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
            &D3DXVECTOR3( 0.0f, 1.0f, 0.0f));

    // アスペクト比の計算
    float AspectRate;
    AspectRate = (float)vp.Width / (float)vp.Height;
    // 射影行列の初期化
    D3DXMATRIX mProj;
    D3DXMatrixIdentity(&mProj);
    D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(m_FovY), AspectRate,m_Near,m_Far);
    // 射影行列の設定
    i_DrawPacket.pD3DDevice->SetTransform(D3DTS_PROJECTION,&mProj);
    // カメラの設定
    i_DrawPacket.pD3DDevice->SetTransform(D3DTS_VIEW,&m_View);
}
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
void Camera::setTarget(D3DXVECTOR3 vPos,D3DXVECTOR3& vCPos/*,D3DXVECTOR3& vCEPos*/){

	if(CameraFlg == true && m_Eye.x < vPos.x){
	m_Eye.x = m_At.x = vPos.x;
	}
	//CameraKyori = m_Eye.x - 7.0f;
	//if(vPos.x <= CameraKyori){
	//	vPos.x = CameraKyori;
	//}
	vCPos = this->m_Eye;
	//vCEPos = this->m_Eye;
}

/**************************************************************************
 class Guide 定義部
****************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：Guide::Guide(LPDIRECT3DDEVICE9 pD3DDevice)
//// カテゴリ   ：コンストラクタ
//// 用途       ：ガイドライン生成時処理
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9インターフェイスへのポインタ
//// 戻値       ：無し（失敗時は例外をthrow）
//// 担当者     ：(山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
Guide::Guide(LPDIRECT3DDEVICE9 pD3DDevice,wiz::OBJID id)
    :Object(id),m_pVB(0)
{
    try{
        CUSTOMVERTEX Vertices[] = 
        {
            {D3DXVECTOR3(-1000.0,0.0,0.0),D3DCOLOR_ARGB(0xff,0xff,0,0)},
            {D3DXVECTOR3(1000.0,0.0,0.0),D3DCOLOR_ARGB(0xff,0xff,0,0)},
            {D3DXVECTOR3(0.0,-1000.0,0.0),D3DCOLOR_ARGB(0xff,0,0xff,0)},
            {D3DXVECTOR3(0.0,1000.0,0.0),D3DCOLOR_ARGB(0xff,0,0xff,0)},
            {D3DXVECTOR3(0.0,0.0,-1000.0),D3DCOLOR_ARGB(0xff,0,0,0xff)},
            {D3DXVECTOR3(0.0,0.0,1000.0),D3DCOLOR_ARGB(0xff,0,0,0xff)}
        };
        if(FAILED(pD3DDevice->CreateVertexBuffer( 6 * sizeof( CUSTOMVERTEX ),
                                    0,D3DFVF_XYZ|D3DFVF_DIFFUSE,
                                    D3DPOOL_DEFAULT, &m_pVB, NULL)))
        {
            // 初期化失敗
            throw BaseException(
                L"頂点バッファの作成に失敗しました。",
                L"Guide::Guide()"
                );
        }
        //バッファをロック
        VOID* pVertices;
        if(FAILED( m_pVB->Lock( 0, sizeof(Vertices),( void** )&pVertices, 0 ))){
            // 初期化失敗
            throw BaseException(
                L"頂点バッファのロックに失敗しました。",
                L"Guide::Guide()"
                );
        }
        //頂点データから頂点バッファに転送
        memcpy( pVertices,Vertices, sizeof(Vertices) );
        //頂点バッファをアンロック
        m_pVB->Unlock();
    }
    catch(...){
        //コンストラクタ例外発生
        //後始末
        SafeRelease(m_pVB);
        //再スロー
        throw;
    }
}
/////////////////// ////////////////////
//// 関数名     ：Guide::~Guide()
//// カテゴリ   ：デストラクタ
//// 用途       ：ガイドライン破棄時処理
//// 引数       ：無し
//// 戻値       ：無し
//// 担当者     ：(山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
Guide::~Guide(){
    SafeRelease(m_pVB);
}
/////////////////// ////////////////////
//// 関数名     ：void Guide::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// カテゴリ   ：仮想関数
//// 用途       ：ガイドラインを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,				//オブジェクトの配列
//// 戻値       ：無し
//// 担当者     ：(山ノ井先生のひな形より)
//// 備考       ：Objectクラスの純粋仮想関数
////            ：
////
void Guide::Draw(DrawPacket& i_DrawPacket) {
    D3DXMATRIX  wm;
    //座標変換無し
    D3DXMatrixIdentity(&wm);
    // マトリックスをレンダリングパイプラインに設定
    i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &wm);
    i_DrawPacket.pD3DDevice->SetStreamSource( 0, m_pVB, 0, sizeof( CUSTOMVERTEX ) );
    i_DrawPacket.pD3DDevice->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE);
    i_DrawPacket.pD3DDevice->SetRenderState( D3DRS_LIGHTING,FALSE);
    i_DrawPacket.pD3DDevice->LightEnable( 0, FALSE );
    i_DrawPacket.pD3DDevice->DrawPrimitive(D3DPT_LINELIST, 0, 3);
    i_DrawPacket.pD3DDevice->SetRenderState( D3DRS_LIGHTING,TRUE);
    i_DrawPacket.pD3DDevice->LightEnable( 0, TRUE );
}

















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
 virtual void CommonMesh::Clear();
 用途:オブジェクトの破棄
 戻り値: なし
***************************************************************************/
/**************************************************************************
	virtual void CommonMesh::ReleaseObj();
 用途: デバイス喪失によるリソースの開放（仮想関数）
 戻り値: なし。
 ＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
void CommonMesh::ReleaseObj(){
    //後始末
    //SafeDelete(m_pShadowVolume);
    SafeRelease(m_pMesh);
}
/////////////////// ////////////////////
//// 関数名     ：CommonMesh::CommonMesh(D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
//// カテゴリ   ：コンストラクタ
//// 用途       ：インスタンス生成時処理
//// 引数       ：  D3DXVECTOR3 pos,				//位置
////            ：  D3DCOLORVALUE& Diffuse,			//ディフューズ色
////            ：  D3DCOLORVALUE& Specular,		//スペキュラ色
////            ：  D3DCOLORVALUE& Ambient			//アンビエント色
//// 戻値       ：無し（失敗時は例外をthrow）
//// 担当者     ： (山ノ井先生のひな形より)
//// 備考       ：独立したオブジェクト向けのコンストラクタ
////            ：
////
CommonMesh::CommonMesh(D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
:m_pMesh(0)     //ポインタは０初期化
,m_dwDrawSubset(0)
{
    try{
		D3DXMatrixIdentity( &m_mMatrix );
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
 CommonMesh::CommonMesh();
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
CommonMesh::CommonMesh():
	//m_pShadowVolume(0),
	m_pMesh(0),
	m_bWrapMode(true),
	m_bWireFrame(false)
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
		//m_pShadowVolume = new ShadowVolume(pD3DDevice,m_pMesh);
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
		//m_pShadowVolume = new ShadowVolume(pD3DDevice,m_pMesh);
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
		//m_pShadowVolume = new ShadowVolume(pD3DDevice,m_pMesh);
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
		//m_pShadowVolume = new ShadowVolume(pD3DDevice,m_pMesh);
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
		//m_pShadowVolume = new ShadowVolume(pD3DDevice,m_pMesh);
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
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,				//オブジェクトの配列
//// 戻値       ：無し
//// 担当者     ： (山ノ井先生のひな形より)
//// 備考       ：Objectクラスの純粋仮想関数
////            ：
////
void CommonMesh::Draw(DrawPacket& i_DrawPacket) {
	LPDIRECT3DDEVICE9 pD3DDevice = i_DrawPacket.pD3DDevice ;
    //無効チェック
    if((!m_pMesh) || (!pD3DDevice)){
        throw BaseException(L"デバイスかメッシュが無効です。",
        L"CommonMesh::Draw()");
    }
    if(m_Material.Diffuse.a < 1.0f){
        //もし、透明度が1.0未満なら
        // アルファ合成の設定
        pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
        pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
        pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    }
    if(m_Material.Specular.r > 0.0f
        || m_Material.Specular.g > 0.0f
        || m_Material.Specular.b > 0.0f)
    {
        //もし、スペキュラーが設定していたら
        // スペキュラー有効の設定
        pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, 1);
    }
    // マテリアルをレンダリングパイプラインに設定
    pD3DDevice->SetMaterial( &m_Material);
    //描画
    m_pMesh->DrawSubset(m_dwDrawSubset);
    if(m_Material.Specular.r > 0.0f
        || m_Material.Specular.g > 0.0f
        || m_Material.Specular.b > 0.0f)
    {
        //もし、スペキュラーが設定していたら
        // スペキュラーを元に戻す
        pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, 0);
    }
    if(m_Material.Diffuse.a < 1.0f){
        //もし、透明度が1.0未満なら
        // アルファ合成を元に戻す
        pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
    }
}

/**************************************************************************
 void CommonMesh::DrawCommonMesh(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
	D3DXMATRIX& Matrix,			//変換行列
	D3DMATERIAL9& Material,		//マティリアル
	Texture* pTexture = 0			//テクスチャ
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
		pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
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
	//if(m_pShadowVolume){
	//	//オブジェクトのワールド行列をカメラ視線にして登録
	//	D3DXMATRIX WorldView;
	//	WorldView =  AllMatrix * mCameraView;
	//	pEffect->SetMatrix("g_mWorldView",&WorldView);
	//	//カメラのプロジェクトまで含んだ行列を登録
	//	WorldView = WorldView * mCameraProj;
	//	pEffect->SetMatrix("g_mWorldViewProjection",&WorldView);
	//	//影ボリュームの描画
	//	m_pShadowVolume->Draw(pD3DDevice,pEffect);
	//}
}









///**************************************************************************
// CommonMesh 定義部
//***************************************************************************/
///////////////////// ////////////////////
////// 関数名     ：CommonMesh::CommonMesh(D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
////// カテゴリ   ：コンストラクタ
////// 用途       ：インスタンス生成時処理
////// 引数       ：  D3DXVECTOR3 pos,				//位置
//////            ：  D3DCOLORVALUE& Diffuse,			//ディフューズ色
//////            ：  D3DCOLORVALUE& Specular,		//スペキュラ色
//////            ：  D3DCOLORVALUE& Ambient			//アンビエント色
////// 戻値       ：無し（失敗時は例外をthrow）
////// 担当者     ： (山ノ井先生のひな形より)
////// 備考       ：独立したオブジェクト向けのコンストラクタ
//////            ：
//////
//CommonMesh::CommonMesh(D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
//:m_pMesh(0)     //ポインタは０初期化
//,m_dwDrawSubset(0)
//{
//    try{
//		D3DXMatrixIdentity( &m_mMatrix );
//        // D3DMATERIAL9構造体を0でクリア
//        ::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
//        // モデルの色を設定
//        m_Material.Diffuse = Diffuse;
//        m_Material.Specular = Specular;
//        m_Material.Ambient = Ambient;
//    }
//    catch(...){
//        //コンストラクタ例外発生
//        //再スロー
//        throw;
//    }
//}
///////////////////// ////////////////////
////// 関数名     ：CommonMesh::CommonMesh()
////// カテゴリ   ：コンストラクタ
////// 用途       ：インスタンス生成時処理
////// 引数       ：無し
////// 戻値       ：無し（失敗時は例外をthrow）
////// 戻値       ：なし（失敗時は例外をthrow）
////// 備考       ：マルチオブジェクト向けのコンストラクタ
//////            ：
//////
//CommonMesh::CommonMesh()
//:m_pMesh(0)     //ポインタは０初期化
//,m_dwDrawSubset(0)
//{
//    try{
//		D3DXMatrixIdentity( &m_mMatrix );
//        // D3DMATERIAL9構造体を0でクリア
//        ::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
//
//        D3DCOLORVALUE dDiffuse = {0.8f,0.8f,0.8f,1.0f};
//        D3DCOLORVALUE dSpecular = {0.0f,0.0f,0.0f,1.0f};
//        D3DCOLORVALUE dAmbient = {0.5f,0.5f,0.5f,1.0f};
//
//        // モデルの色を設定
//        m_Material.Diffuse  = dDiffuse;
//        m_Material.Specular = dSpecular;
//        m_Material.Ambient  = dAmbient;
//    }
//    catch(...){
//        //コンストラクタ例外発生
//        //再スロー
//        throw;
//    }
//}
///////////////////// ////////////////////
////// 関数名     ：CommonMesh::~CommonMesh()
////// カテゴリ   ：デストラクタ
////// 用途       ：インスタンス破棄時処理
////// 引数       ：無し
////// 戻値       ：無し
////// 担当者     ： (山ノ井先生のひな形より)
////// 備考       ：
//////            ：
//////
//CommonMesh::~CommonMesh(){
//    //後始末
//	//派生クラスでのRelease忘れ対策
//    SafeRelease(m_pMesh);
//}
///////////////////// ////////////////////
////// 関数名     ：void CommonMesh::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
////// カテゴリ   ：仮想関数
////// 用途       ：メッシュを描画
////// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
//////            ：  vector<Object*>& Vec,				//オブジェクトの配列
////// 戻値       ：無し
////// 担当者     ： (山ノ井先生のひな形より)
////// 備考       ：Objectクラスの純粋仮想関数
//////            ：
//////
//void CommonMesh::Draw(DrawPacket& i_DrawPacket) {
//    //無効チェック
//    if((!m_pMesh) || (!i_DrawPacket.pD3DDevice)){
//        throw BaseException(L"デバイスかメッシュが無効です。",
//        L"CommonMesh::Draw()");
//    }
//    if(m_Material.Diffuse.a < 1.0f){
//        //もし、透明度が1.0未満なら
//        // アルファ合成の設定
//        i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
//        i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//        i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//    }
//    if(m_Material.Specular.r > 0.0f
//        || m_Material.Specular.g > 0.0f
//        || m_Material.Specular.b > 0.0f)
//    {
//        //もし、スペキュラーが設定していたら
//        // スペキュラー有効の設定
//        i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, 1);
//    }
//    // マテリアルをレンダリングパイプラインに設定
//    i_DrawPacket.pD3DDevice->SetMaterial( &m_Material);
//    //描画
//    m_pMesh->DrawSubset(m_dwDrawSubset);
//    if(m_Material.Specular.r > 0.0f
//        || m_Material.Specular.g > 0.0f
//        || m_Material.Specular.b > 0.0f)
//    {
//        //もし、スペキュラーが設定していたら
//        // スペキュラーを元に戻す
//        i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, 0);
//    }
//    if(m_Material.Diffuse.a < 1.0f){
//        //もし、透明度が1.0未満なら
//        // アルファ合成を元に戻す
//        i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
//    }
//}




















void dummy(){};
/**************************************************************************
 LoadMeshFromX 定義部
****************************************************************************/
LoadMeshFromX::LoadMeshFromX(LPDIRECT3DDEVICE9 pD3DDevice,char *pFileName ,TextureManager& TexMgr,char *pTexName)
{
    try{
		D3DXMatrixIdentity(&m_mMatrix);
		//string sFileDir ;
		m_sFileName = pFileName;

		//size_t	pathLength ;
		//for(  pathLength = strlen(pFileName) ; pathLength >= 0 ; pathLength--  )
		//	if(  pFileName[ pathLength ] == '/' || pFileName[ pathLength ] == '\\'  )
		//		break ;
		//for(  size_t i = 0 ; i < pathLength ; i++  )
		//	sFileDir	+= pFileName[ i ] ;

        //球の作成
		// Xファイルからメッシュをロードする 
		LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
		DWORD dwMQty;
		if(FAILED(D3DXLoadMeshFromXA(pFileName,
								D3DXMESH_SYSTEMMEM,
								pD3DDevice,
								NULL,
								&pD3DXMtrlBuffer,
								NULL,
								&dwMQty,
								&m_BassMesh.m_pMesh))){
			string	 buf1 = pFileName ;
			wstring  buf2 ;
			TLIB::widen(buf1,buf2);
			wstring msg  = wstring(L"モデルデータ\"") + buf2 + wstring(L"\"を読み込めませんでした");
			// 初期化失敗
            throw BaseException(
				msg.c_str(),
                L"LoadMeshFromX::LoadMeshFromX()"
                );
        }
		//
		//////////
		//	: テクスチャ名をワイド化
		wstring wsTexName  ;
		wchar_t* wpTexName = NULL;
		if(pTexName){
			wpTexName = new wchar_t[ strlen(pTexName) +1 ];
			size_t ret;
			mbstowcs_s(&ret, wpTexName, strlen(pTexName) +1, pTexName, strlen(pTexName) +1);
		}
		//
		//////////

		//TLIB::widen(sFileDir,wsFileDir);


		//D3DXMATERIAL d3dxMaterials = *(D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
		this->pD3DDevice = pD3DDevice;
		m_MaterialItems.init(pD3DDevice,pD3DXMtrlBuffer,dwMQty,TexMgr,g_sDefaultTexturePath.c_str(),wpTexName);
		m_BassMesh.m_AABB = AABB(m_BassMesh.m_pMesh);
		delete [] wpTexName;
	}
    catch(...){
        //再スロー
        throw;
    }

}
/////////////////// ////////////////////
//// 関数名     ：void LoadMeshFromX::Draw( DrawPacket& i_DrawPacket)
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
void LoadMeshFromX::Draw(DrawPacket& i_DrawPacket){
	vector<MeshItem*>::size_type i = 0, sz = m_MeshItems.size();
	while(i < sz){
		m_pMesh = m_MeshItems[i]->m_pMesh;
		m_MaterialItems.m_Material[0].m_pTexture = m_MeshItems[i]->m_pTexture;
		subsetDraw(i_DrawPacket);
		i++;
	}
}
/////////////////// ////////////////////
//// 関数名     ：void LoadMeshFromX::subsetDraw( LPDIRECT3DDEVICE9 pD3DDevice,
////            ：    Tempus2* i_DrawPacket.pTime,vector<Object*>& Vec,Command& i_DrawPacket.pCommand)
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
void LoadMeshFromX::subsetDraw(DrawPacket& i_DrawPacket){
	DWORD i = 0, dwLoop = m_MaterialItems.m_MaterialQty;
	while(i < dwLoop){
		m_dwDrawSubset = i;
		m_Material     = m_MaterialItems.m_Material[i].m_Material;
		LPDIRECT3DTEXTURE9  pTexture = m_MaterialItems.m_Material[i].m_pTexture;
		//テクスチャがある場合
		if(pTexture){
			DWORD wkdword;
			//現在のテクスチャステータスを得る
			i_DrawPacket.pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
			//ステージの設定
			i_DrawPacket.pD3DDevice->SetTexture(0,pTexture);
			//デフィーズ色とテクスチャを掛け合わせる設定
			i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
			i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
			i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
			//i_DrawPacket.pD3DDevice->SetFVF(PlateFVF);
			// マトリックスをレンダリングパイプラインに設定
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);

			//コモンメッシュのDraw()を呼ぶ
			CommonMesh::Draw(i_DrawPacket);
			i_DrawPacket.pD3DDevice->SetTexture(0,0);
			//ステージを元に戻す
			i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
		}
		else{
			// マトリックスをレンダリングパイプラインに設定
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);
			//コモンメッシュのDraw()を呼ぶ
			CommonMesh::Draw(i_DrawPacket);
		}
		i++;
	}
}
/////////////////// ////////////////////
//// 関数名     ：voidLoadMeshFromX:: Add(D3DXVECTOR3& vScale,D3DXVECTOR3& vRot,D3DXVECTOR3& vPos)
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
void LoadMeshFromX::Add(D3DXVECTOR3& vScale,D3DXVECTOR3& vRot,D3DXVECTOR3& vPos
		, LPDIRECT3DDEVICE9 pD3DDevice , TextureManager* pTexMgr , wstring pTexName )
{
	D3DXMATRIX mScale , mRot , mPos , mAll ;
	D3DXMatrixIsIdentity(&mScale);
	D3DXMatrixIsIdentity(&mRot);
	D3DXMatrixIsIdentity(&mPos);
	D3DXMatrixScaling(&mScale,vScale.x,vScale.y,vScale.z);
	D3DXMatrixRotationYawPitchRoll(&mRot,vRot.y,vRot.x,vRot.z);
	D3DXMatrixTranslation(&mPos,vPos.x,vPos.y,vPos.z);
	MeshItem* item = new MeshItem(this->pD3DDevice,m_BassMesh);
	mAll = (mScale*mRot*mPos) ;
	MeshTransformer(item->m_pMesh,mAll);
	item->m_AABB = AABB(item->m_pMesh);
	item->m_pTexture = m_BassMesh.m_pTexture;
	(pD3DDevice && pTexMgr && pTexName != L"" && (item->m_pTexture = pTexMgr->addTexture( pD3DDevice,wstring( g_sDefaultTexturePath + pTexName ).c_str() ) ) );
	m_MeshItems.push_back(item);
}
/////////////////// ////////////////////
//// 関数名     ：bool LoadMeshFromX::CheckSame(string i_sXFilePath)
//// カテゴリ   ：チェッカーズ
//// 用途       ：同じモデルデータか調べる
//// 引数       ：  string i_sXFilePath       //  : ファイルパス
//// 戻値       ： true  : 一致
////            ： false : 不一致
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
bool LoadMeshFromX::CheckSame(string i_sXFilePath){
	return (m_sFileName == i_sXFilePath);
}

/**************************************************************************
 LoadAnimationModel 定義部
****************************************************************************/
LoadAnimationModel::LoadAnimationModel(LPDIRECT3DDEVICE9 pD3DDevice,char *pFileName,
		D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXVECTOR3 pos,
		float InitialTracSpeed ,DWORD InitialTrac )
{
	m_pAnmModel = new AnimationModel(pD3DDevice,pFileName);
	for( int i = 0 ; i < m_pAnmModel->getNumTracks() ; i++ )
		m_pAnmModel->setTrackSpeed( i, InitialTracSpeed );
	m_pAnmModel->setTrack(InitialTrac);

	D3DXMATRIX mScale,mRot,mPos;
	D3DXMatrixIdentity(&m_mMatrix);
	D3DXMatrixIdentity(&mScale);
	D3DXMatrixIdentity(&mRot);
	D3DXMatrixIdentity(&mPos);
	D3DXMatrixScaling(&mScale,size.x,size.y,size.z);
	D3DXMatrixRotationYawPitchRoll(&mRot,rot.y,rot.x,rot.z);
	D3DXMatrixTranslation(&mPos,pos.x,pos.y,pos.z);
	m_mMatrix = mScale * mRot * mPos;


}
/////////////////// ////////////////////
//// 関数名     ：void LoadAnimationModel::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// カテゴリ   ：仮想関数
//// 用途       ：メッシュを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,				//オブジェクトの配列
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：Objectクラスの純粋仮想関数
////            ：
////
void LoadAnimationModel::Draw(DrawPacket& i_DrawPacket){

	m_pAnmModel->SetTransform( &m_mMatrix );
	m_pAnmModel->draw( i_DrawPacket.pD3DDevice, (float)i_DrawPacket.pTime->getElapsedTime() );

}





/**************************************************************************
 PrimitiveBox 定義部
***************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：void PrimitiveBox::VecNomal2UV(D3DXVECTOR3 vec,D3DXVECTOR3 normal,float& u,float& v)
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
void PrimitiveBox::VecNomal2UV(D3DXVECTOR3 vec,D3DXVECTOR3 normal,float& u,float& v){
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
void PrimitiveBox::CreateBox(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture){
    try{
		SafeRelease(m_pMesh);
		//平板の作成
		if(
			FAILED(
				D3DXCreateBox(
					pD3DDevice, 
					g_vOne.x,
					g_vOne.y,
					g_vOne.z,
					&m_pMesh, 
					NULL
				)
			)
		){
			// 初期化失敗
			throw BaseException(
				L"平板の作成に失敗しました。",
				L"PrimitiveBox::PrimitiveBox()"
				);
		}
		//テクスチャがある場合
		if(m_pTexture){
			//テクスチャなしのメッシュ
			LPD3DXMESH m_pMesh2 = 0;
			//作成されたメッシュを元に、テクスチャつきのメッシュを作成
			if(FAILED(m_pMesh->CloneMeshFVF(NULL,PlateFVF,pD3DDevice,&m_pMesh2))){
				// 初期化失敗
				throw BaseException(
					L"テクスチャ付の平板の作成に失敗しました。",
					L"PrimitiveBox::PrimitiveBox()"
					);
			}
			//この段階でテクスチャがないm_pMeshはいらないから削除
			SafeRelease(m_pMesh);
			//テクスチャがあるメッシュを代入
			m_pMesh = m_pMesh2;
			//テクスチャ上の座標をマッピング
			LPDIRECT3DVERTEXBUFFER9 pVB = 0;
			PlateVertex* pVer = 0;
			m_pMesh->GetVertexBuffer(&pVB);
			pVB->Lock(0,0,(VOID**)&pVer,0);
			DWORD vsize = m_pMesh->GetNumVertices();
			for(DWORD n = 0;n < vsize;n++){ //頂点の数を取得する
				//法線と頂点からuv値を得る
				VecNomal2UV(pVer[n].vec,pVer[n].normal,pVer[n].tu,pVer[n].tv);
			}
			pVB->Unlock();
		}
    }
    catch(...){
        //コンストラクタ例外発生
        //後始末
        SafeRelease(m_pMesh);
        //再スロー
        throw;
    }

};
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
PrimitiveBox::PrimitiveBox(LPDIRECT3DDEVICE9 pD3DDevice,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		LPDIRECT3DTEXTURE9 pTexture)
    :CommonMesh(Diffuse,Specular,Ambient),m_pTexture(pTexture)
{
    try{
		CreateBox(pD3DDevice,pTexture);
	}
    catch(...){
        //再スロー
        throw;
    }
}
/////////////////// ////////////////////
//// 関数名     ：PrimitiveBox::PrimitiveBox(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture = 0)
//// カテゴリ   ：コンストラクタ
//// 用途       ：インスタンス生成時処理
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9インターフェイスへのポインタ
////            ：  LPDIRECT3DTEXTURE9 pTexture = 0	//テクスチャを張るときは指定
//// 戻値       ：なし失敗時は例外をthrow）
//// 担当者     ：(山ノ井先生のひな形より)
//// 備考       ：独立オブジェクト向けコンストラクタ
////            ：
////
PrimitiveBox::PrimitiveBox(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture)
    :CommonMesh(),m_pTexture(pTexture)
{
    try{
		CreateBox(pD3DDevice,pTexture);
	}
    catch(...){
        //再スロー
        throw;
    }
}
/////////////////// ////////////////////
//// 関数名     ：virtual PrimitiveBox::~PrimitiveBox()
//// カテゴリ   ：デストラクタ
//// 用途       ：
//// 戻値       ：なし
//// 担当者     ：(山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
PrimitiveBox::~PrimitiveBox(){
    //後始末（メッシュのReleaseは
	//CommonMeshで行なうので、本来はしなくても良い。
	//しても問題ない
    SafeRelease(m_pMesh);
}
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
void PrimitiveBox::Draw(DrawPacket& i_DrawPacket) {

	//テクスチャがある場合
	if(m_pTexture){
		DWORD wkdword;
		//現在のテクスチャステータスを得る
		i_DrawPacket.pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
		//ステージの設定
		i_DrawPacket.pD3DDevice->SetTexture(0,m_pTexture);
		//デフィーズ色とテクスチャを掛け合わせる設定
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		i_DrawPacket.pD3DDevice->SetFVF(PlateFVF);
		// マトリックスをレンダリングパイプラインに設定
		i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);

		//コモンメッシュのDraw()を呼ぶ
		CommonMesh::Draw(i_DrawPacket);
		i_DrawPacket.pD3DDevice->SetTexture(0,0);
		//ステージを元に戻す
		i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	}
	else{
		// マトリックスをレンダリングパイプラインに設定
		i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);
		//コモンメッシュのDraw()を呼ぶ
		CommonMesh::Draw(i_DrawPacket);
	}

}
/**************************************************************************
 PrimitiveSphere 定義部
***************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：void PrimitiveSphere::Vec2UV(float x,float y,float z,float r,float& u,float& v );
//// カテゴリ   ：メンバ関数
//// 用途       ：VectorをUとVにコンバート
//// 引数       ：  float x     //xの値
////            ：  float y     //yの値
////            ：  float z     //zの値
////            ：  float r     //球の半径
////            ：  float& u    //変換するu（テクスチャ上のU座標）
////            ：  float& v    //変換するv（テクスチャ上のV座標）
//// 戻値       ：なし
//// 担当者     ： (山ノ井先生のひな形より)
//// 備考       ：float& uとfloat& vに変換後の値を代入
////            ：
////
void PrimitiveSphere::Vec2UV(float x,float y,float z,float r,float& u,float& v){
	float q;
	float q2;
	q = atan2(z,x);
	u = q / (2.0f * D3DX_PI);
	q2 = asin(y / r);
	v = (1.0f - q2 / (D3DX_PI / 2.0f)) / 2.0f;
	if( u > 1.0f)
		u = 1.0f;
}
/////////////////// ////////////////////
//// 関数名     ：void PrimitiveSphere::CreateSphere(LPDIRECT3DDEVICE9 pD3DDevice)
//// カテゴリ   ：関数
//// 用途       ：球を生成
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
//// 戻値       ：なし
//// 担当者     ：鴫原 徹(山ノ井先生のひな形より)
//// 備考       ：float& uとfloat& vに変換後の値を代入
////            ：
////
void PrimitiveSphere::CreateSphere(LPDIRECT3DDEVICE9 pD3DDevice){
    try{
        //球の作成
        if(
			FAILED(
				D3DXCreateSphere(
					pD3DDevice, 
					1.0f,
					18,
					18,
					&m_pMesh, 
					NULL
				)
			)
		){
            // 初期化失敗
            throw BaseException(
                L"球の作成に失敗しました。",
                L"PrimitiveSphere::PrimitiveSphere"
                );
        }
		if(m_pTexture){
			//テクスチャメッシュ
			LPD3DXMESH pMesh2 = 0;
			//作成されたメッシュを元に、テクスチャつきのメッシュを作成
			if(FAILED(m_pMesh->CloneMeshFVF(NULL,BallFVF,pD3DDevice,&pMesh2))){
				// 初期化失敗
				throw BaseException(
					L"テクスチャ付の球の作成に失敗しました。",
					L"PrimitiveSphere::PrimitiveSphere"
					);
			}
			//この段階でm_pMeshはいらないから削除
			SafeRelease(m_pMesh);
			//新しいメッシュを代入
			m_pMesh = pMesh2;
			//テクスチャ上の座標をマッピング
			LPDIRECT3DVERTEXBUFFER9 pVB = 0;
			SphereVertex* pVer = 0;
			m_pMesh->GetVertexBuffer(&pVB);
			pVB->Lock(0,0,(VOID**)&pVer,0);
			for(DWORD n = 0;n < m_pMesh->GetNumVertices();n++){ //頂点の数を取得する
				float u,v;
				Vec2UV(pVer[n].vec.x,pVer[n].vec.y,pVer[n].vec.z,1.0f,u,v);
				pVer[n].tu=u;
				pVer[n].tv=v;
			}
			pVB->Unlock();
		}
        //クオータニオンの初期化
        //D3DXQuaternionRotationYawPitchRoll(&m_Qtn,0,0,0);
    }
    catch(...){
        //コンストラクタ例外発生
        //後始末
        SafeRelease(m_pMesh);
        //再スロー
        throw;
    }
};

/////////////////// ////////////////////
//// 関数名     ：PrimitiveSphere::PrimitiveSphere(LPDIRECT3DDEVICE9 pD3DDevice,D3DCOLORVALUE& Diffuse,
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
PrimitiveSphere::PrimitiveSphere(LPDIRECT3DDEVICE9 pD3DDevice,
           D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		   LPDIRECT3DTEXTURE9 pTexture)
    :CommonMesh(Diffuse,Specular,Ambient)
	,m_pTexture(pTexture)
{
    try{
		CreateSphere(pD3DDevice);
    }
    catch(...){
        //再スロー
        throw;
    }

}

/////////////////// ////////////////////
//// 関数名     ：PrimitiveSphere::PrimitiveSphere( LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture = 0);
//// カテゴリ   ：コンストラクタ
//// 用途       ：球体を作成
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	//IDirect3DDevice9インターフェイスへのポインタ
////            ：  LPDIRECT3DTEXTURE9 pTexture = 0	//テクスチャを張るときは指定
//// 戻値       ：なし（失敗時は例外をthrow）
//// 担当者     ： (山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
//PrimitiveSphere::PrimitiveSphere(LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture)
//    :CommonMesh()
//	,m_pTexture(pTexture)
//{
//    try{
//		CreateSphere(pD3DDevice);
//    }
//    catch(...){
//        //再スロー
//        throw;
//    }
//
//}

/////////////////// ////////////////////
//// 関数名     ：PrimitiveSphere::~PrimitiveSphere();
//// カテゴリ   ：デストラクタ
//// 用途       ：球体を破棄
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ： (山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
PrimitiveSphere::~PrimitiveSphere(){
    //後始末
    SafeRelease(m_pMesh);
}
/////////////////// ////////////////////
//// 関数名     ：voidPrimitiveSphere::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// カテゴリ   ：仮想関数
//// 用途       ：球体を描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,				//オブジェクトの配列
//// 戻値       ：なし
//// 担当者     ： (山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
void PrimitiveSphere::Draw(DrawPacket& i_DrawPacket){
	//テクスチャがあった場合
	if(m_pTexture){
		//テクスチャ描画命令
		DWORD wkdword;
		//現在のテクスチャステータスを得る
		i_DrawPacket.pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
		//ステージの設定
		i_DrawPacket.pD3DDevice->SetTexture(0,m_pTexture);
		//デフィーズ色とテクスチャを掛け合わせる設定
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		i_DrawPacket.pD3DDevice->SetFVF(BallFVF);
		// マトリックスをレンダリングパイプラインに設定
		i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);
		//コモンメッシュのDraw()を呼ぶ
		CommonMesh::Draw(i_DrawPacket);
		i_DrawPacket.pD3DDevice->SetTexture(0,0);
		//ステージを元に戻す
		i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	}
	else{
		//テクスチャがない場合
		// マトリックスをレンダリングパイプラインに設定
		i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);
		//コモンメッシュのDraw()を呼ぶ
		CommonMesh::Draw(i_DrawPacket);
	}
}
/**************************************************************************
 PrimitiveCylinder 定義部
***************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：void PrimitiveCylinder::Vec2UV(float x,float y,float z,float r,float& u,float& v );
//// カテゴリ   ：メンバ関数
//// 用途       ：VectorをUとVにコンバート
//// 引数       ：  float x     //xの値
////            ：  float y     //yの値
////            ：  float z     //zの値
////            ：  float r     //球の半径
////            ：  float& u    //変換するu（テクスチャ上のU座標）
////            ：  float& v    //変換するv（テクスチャ上のV座標）
//// 戻値       ：なし
//// 担当者     ： (山ノ井先生のひな形より)
//// 備考       ：float& uとfloat& vに変換後の値を代入
////            ：
////
void PrimitiveCylinder::Vec2UV(float x,float y,float z,float r,float& u,float& v){
	float q;
	float q2;
	q = atan2(z,x);
	u = q / (2.0f * D3DX_PI);
	q2 = asin(y / r);
	v = (1.0f - q2 / (D3DX_PI / 2.0f)) / 2.0f;
	if( u > 1.0f)
		u = 1.0f;
}
/////////////////// ////////////////////
//// 関数名     ：void PrimitiveCylinder::CreateSphere(LPDIRECT3DDEVICE9 pD3DDevice)
//// カテゴリ   ：関数
//// 用途       ：球を生成
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
//// 戻値       ：なし
//// 担当者     ：鴫原 徹(山ノ井先生のひな形より)
//// 備考       ：float& uとfloat& vに変換後の値を代入
////            ：
////
void PrimitiveCylinder::CreateCylinder(LPDIRECT3DDEVICE9 pD3DDevice)
{
    try{
        //球の作成
        if(
			FAILED(
				D3DXCreateCylinder(
					pD3DDevice,
					1.0f,
					1.0f,
					1.0f,
					18,
					2,
					&m_pMesh, 
					NULL
				)
			)
		){
            // 初期化失敗
            throw BaseException(
                L"円錐の作成に失敗しました。",
                L"PrimitiveCylinder::PrimitiveCylinder"
                );
        }
		if(m_pTexture){
			//テクスチャメッシュ
			LPD3DXMESH pMesh2 = 0;
			//作成されたメッシュを元に、テクスチャつきのメッシュを作成
			if(FAILED(m_pMesh->CloneMeshFVF(NULL,BallFVF,pD3DDevice,&pMesh2))){
				// 初期化失敗
				throw BaseException(
					L"テクスチャ付の円錐の作成に失敗しました。",
					L"PrimitiveCylinder::PrimitiveCylinder"
					);
			}
			//この段階でm_pMeshはいらないから削除
			SafeRelease(m_pMesh);
			//新しいメッシュを代入
			m_pMesh = pMesh2;
			//テクスチャ上の座標をマッピング
			LPDIRECT3DVERTEXBUFFER9 pVB = 0;
			SphereVertex* pVer = 0;
			m_pMesh->GetVertexBuffer(&pVB);
			pVB->Lock(0,0,(VOID**)&pVer,0);

			for(DWORD n = 0;n < m_pMesh->GetNumVertices();n++){ //頂点の数を取得する
				float u , v ;
				Vec2UV(pVer[n].vec.x,pVer[n].vec.y,pVer[n].vec.z,1.0f,u,v);
				pVer[n].tu = u ;
				pVer[n].tv = v ;
			}
			pVB->Unlock();
		}
        //クオータニオンの初期化
        //D3DXQuaternionRotationYawPitchRoll(&m_Qtn,0,0,0);
    }
    catch(...){
        //コンストラクタ例外発生
        //後始末
        SafeRelease(m_pMesh);
        //再スロー
        throw;
    }
};

/////////////////// ////////////////////
//// 関数名     ：PrimitiveCylinder::PrimitiveCylinder(LPDIRECT3DDEVICE9 pD3DDevice,D3DCOLORVALUE& Diffuse,
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
PrimitiveCylinder::PrimitiveCylinder(LPDIRECT3DDEVICE9 pD3DDevice,
           D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		   LPDIRECT3DTEXTURE9 pTexture)
    :CommonMesh()
	,m_pTexture(pTexture)
{
    try{
		CreateCylinder(pD3DDevice);
    }
    catch(...){
        //再スロー
        throw;
    }

}


/////////////////// ////////////////////
//// 関数名     ：PrimitiveCylinder::~PrimitiveCylinder();
//// カテゴリ   ：デストラクタ
//// 用途       ：球体を破棄
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ： (山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
PrimitiveCylinder::~PrimitiveCylinder(){
    //後始末
    SafeRelease(m_pMesh);
}
/////////////////// ////////////////////
//// 関数名     ：voidPrimitiveCylinder::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// カテゴリ   ：仮想関数
//// 用途       ：球体を描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,				//オブジェクトの配列
//// 戻値       ：なし
//// 担当者     ： (山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
void PrimitiveCylinder::Draw(DrawPacket& i_DrawPacket){
	//テクスチャがあった場合
	if(m_pTexture){
		//テクスチャ描画命令
		DWORD wkdword;
		//現在のテクスチャステータスを得る
		i_DrawPacket.pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
		//ステージの設定
		i_DrawPacket.pD3DDevice->SetTexture(0,m_pTexture);
		//デフィーズ色とテクスチャを掛け合わせる設定
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		i_DrawPacket.pD3DDevice->SetFVF(BallFVF);
		// マトリックスをレンダリングパイプラインに設定
		i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);
		//コモンメッシュのDraw()を呼ぶ
		CommonMesh::Draw(i_DrawPacket);
		i_DrawPacket.pD3DDevice->SetTexture(0,0);
		//ステージを元に戻す
		i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	}
	else{
		//テクスチャがない場合
		// マトリックスをレンダリングパイプラインに設定
		i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);
		//コモンメッシュのDraw()を呼ぶ
		CommonMesh::Draw(i_DrawPacket);
	}
}
/**************************************************************************
 PrimitiveSprite 定義部
***************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：PrimitiveSprite::PrimitiveSprite(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,RECT* Rect,
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
PrimitiveSprite::PrimitiveSprite(LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture, RECT* rect,
	D3DXVECTOR3& vCenter, D3DXVECTOR3& vOffsetPos, Color color)
	:m_pTexture(pTexture)
	,m_vOffsetPos(vOffsetPos)
	,m_vCenter(vCenter)
	,m_pRect(NULL)
	,m_Color(color)
{
	try{
		if(rect){
			m_pRect = new RECT(*rect);
		}
		if(
			FAILED(
				D3DXCreateSprite(
					pD3DDevice,
					&m_pSprite
				)
			)
		){
			// 初期化失敗
			throw BaseException(
				L"スプライトの作成に失敗しました。",
				L"PrimitiveSprite::PrimitiveSprite()"
			);
		}
	}
	catch(...){
		SafeRelease(m_pSprite);
		//再スロー
		throw;
	}
}

/////////////////// ////////////////////
//// 関数名     ：virtual PrimitiveSprite::~PrimitiveSprite()
//// カテゴリ   ：デストラクタ
//// 用途       ：
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
PrimitiveSprite::~PrimitiveSprite(){
	SAFE_DELETE(m_pRect);
	SafeRelease(m_pSprite);
}



/////////////////// ////////////////////
//// 関数名     ：void PrimitiveSprite::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// カテゴリ   ：仮想関数
//// 用途       ：スプライトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,				//オブジェクトの配列
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
void PrimitiveSprite::Draw(DrawPacket& i_DrawPacket)
{
	if(m_pSprite && m_pTexture){
		D3DXMATRIX mAspectRate,mAll;
		D3DXVECTOR2 AspectRate = DxDevice::getAspectRate();
		D3DXMatrixScaling(&mAspectRate,AspectRate.x,AspectRate.y,1.0f);
	    D3DXMatrixMultiply(&mAll,&m_mMatrix,&mAspectRate);
		m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );
		{
			m_pSprite->SetTransform( &mAll );
			m_pSprite->Draw(m_pTexture, m_pRect,
				&m_vCenter, &m_vOffsetPos, m_Color.dwColor );
		}
		m_pSprite->End();
	}
}
/**************************************************************************
 SpriteObject 定義部
***************************************************************************/
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
SpriteObject::SpriteObject(LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
			D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
			RECT *pRect, D3DXVECTOR3 &vCenter, D3DXVECTOR3 &vOffsetPos, Color color,
			wiz::OBJID id)
			:Object(id)
			,PrimitiveSprite(pD3DDevice,pTexture,pRect,vCenter,vOffsetPos,color)
{
	try{
		//	: 初期マトリックスを計算
		D3DXMATRIX mScale,mRot,mPos;
		D3DXMatrixScaling(&mScale,vScale.x,vScale.y,vScale.z);
		D3DXMatrixRotationYawPitchRoll(&mRot,vRot.y,vRot.x,vRot.z);
		D3DXMatrixTranslation(&mPos,vPos.x,vPos.y,vPos.z);
		m_mMatrix = mScale * mRot * mPos ;
	}
	catch(...){
		SafeRelease(m_pSprite);
		//再スロー
		throw;
	}

};
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
SpriteObject::~SpriteObject(){
};
/////////////////// ////////////////////
//// 関数名     ：void SpriteObject::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// カテゴリ   ：仮想関数
//// 用途       ：スプライトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,				//オブジェクトの配列
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
void SpriteObject::Draw(DrawPacket& i_DrawPacket)
{
	//	: 描画は親クラスに任せる
	PrimitiveSprite::Draw(i_DrawPacket);
};


/**************************************************************************
 Sound 定義部
****************************************************************************/
/**************************************************************************
 void Sound::Clear();
 用途:オブジェクトの破棄
 戻り値: なし
***************************************************************************/
void Sound::Clear(){
    if(m_pEngine){
        m_pEngine->ShutDown();
		SafeRelease(m_pEngine);
    }
	SafeDeleteArr(m_pbSoundBank);
	if(m_pbWaveBank){
        UnmapViewOfFile(m_pbWaveBank);
	}
    m_pbWaveBank = 0;
    CoUninitialize();
}
/**************************************************************************
 Sound::Sound(
 const wchar_t* pWavBankFileName,		//Wavバンクのファイル名
 const wchar_t* pSoundBankFileName	//Soundバンクのファイル名
 );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
Sound::Sound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName)
:m_pEngine(0),m_pWaveBank(0),m_pSoundBank(0),m_pbWaveBank(0),m_pbSoundBank(0)
,Object(OBJID_SYS_SOUND)
{
	try{
		HANDLE hFile;
		DWORD dwFileSize;
		DWORD dwBytesRead;
		HANDLE hMapFile;

		if(FAILED(CoInitializeEx( NULL, COINIT_MULTITHREADED))){
			// 初期化失敗
			throw BaseException(
				L"i_DrawPacket.pCommand初期化に失敗しました。",
				L"Sound::Sound()"
				);
		}


		//デバッグ時は以下をtrueにする
		bool bDebugMode = false;
		DWORD dwCreationFlags = 0;
		if( bDebugMode ) dwCreationFlags |= XACT_FLAG_API_DEBUG_MODE;
		if(FAILED(XACT3CreateEngine( dwCreationFlags, &m_pEngine ))){
			// 初期化失敗
			throw BaseException(
				L"サウンドエンジン構築に失敗しました。",
				L"Sound::Sound()"
				);
		}
		// Initialize & create the XACT runtime 
		XACT_RUNTIME_PARAMETERS xrParams = {0};
		xrParams.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
		if(FAILED(m_pEngine->Initialize( &xrParams ))){
			// 初期化失敗
			throw BaseException(
				L"サウンドエンジン初期化に失敗しました。",
				L"Sound::Sound()"
				);
		}

		hFile = CreateFile(pWavBankFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
		if( hFile != INVALID_HANDLE_VALUE ){
			dwFileSize = GetFileSize( hFile, NULL );
			if( dwFileSize != -1 ){
				hMapFile = CreateFileMapping( hFile, NULL, PAGE_READONLY, 0, dwFileSize, NULL );
				if( hMapFile ){
					m_pbWaveBank = MapViewOfFile( hMapFile, FILE_MAP_READ, 0, 0, 0 );
					if(m_pbWaveBank){
						if(FAILED(m_pEngine->CreateInMemoryWaveBank(m_pbWaveBank, dwFileSize, 0,
							0, &m_pWaveBank))){
							CloseHandle( hMapFile );
							CloseHandle( hFile );
							// 初期化失敗
							throw BaseException(
								L"Wavバンクハンドル初期化に失敗しました。",
								L"Sound::Sound()"
								);
						}
					}
					CloseHandle( hMapFile ); // pbWaveBank maintains a handle on the file so close this unneeded handle
				}
			}
			CloseHandle( hFile ); // pbWaveBank maintains a handle on the file so close this unneeded handle
		}
		hFile = CreateFile(pSoundBankFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
		if( hFile != INVALID_HANDLE_VALUE )
		{
			dwFileSize = GetFileSize( hFile, NULL );
			if( dwFileSize != -1 )
			{
				// Allocate the data here and free the data when recieving the sound bank destroyed notification
				m_pbSoundBank = new BYTE[dwFileSize];
				if(m_pbSoundBank)
				{
					if( 0 != ReadFile( hFile,m_pbSoundBank, dwFileSize, &dwBytesRead, NULL ) )
					{
						if(FAILED(m_pEngine->CreateSoundBank(m_pbSoundBank, dwFileSize, 0,
							0, &m_pSoundBank))){
							CloseHandle( hFile );
							// 初期化失敗
							throw BaseException(
								L"Soundバンクハンドル初期化に失敗しました。",
								L"Sound::Sound()"
								);

						}
					}
				}
			}
			CloseHandle( hFile );
		}

	}
	catch(...){
		Clear();
		//再throw
		throw;
	}
}
/**************************************************************************
 virtual Sound::~Sound();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Sound::~Sound(){
	Clear();
}
/**************************************************************************
 virtual void Sound::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Command& i_DrawPacket.pCommand					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: 影を描画
 戻り値: なし。
***************************************************************************/
void Sound::Draw(DrawPacket& i_DrawPacket){
}

/**************************************************************************
 ZapSound 定義部
****************************************************************************/
/**************************************************************************
 ZapSound::ZapSound(
 const wchar_t* pWavBankFileName,		//Wavバンクのファイル名
 const wchar_t* pSoundBankFileName	//Soundバンクのファイル名
 const char* pZapKey,				//Zapのキー
 const char* pFireKey				//発射音のキー
 );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
ZapSound::ZapSound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,
				   const char* pZapKey,const char* pFireKey,const char* pBGM,const char* pBS,const char* pGET,const char* pHANAB1,const char* pHANAB2)
:Sound(pWavBankFileName,pSoundBankFileName),m_iZap(0),m_iFire(0),m_iBGM(0),m_iBS(0),m_iGET(0),m_iHANAB1(0),m_iHANAB2(0)
{
	try{
		if(m_pSoundBank){
			m_iZap = m_pSoundBank->GetCueIndex(pZapKey);
			m_iFire = m_pSoundBank->GetCueIndex(pFireKey);
			m_iBGM = m_pSoundBank->GetCueIndex(pBGM);
			m_iBS = m_pSoundBank->GetCueIndex(pBS);
			m_iGET = m_pSoundBank->GetCueIndex(pGET);
			m_iHANAB1 = m_pSoundBank->GetCueIndex(pHANAB1);
			m_iHANAB2 = m_pSoundBank->GetCueIndex(pHANAB2);
		}
	}
	catch(...){
		Clear();
		//再throw
		throw;
	}
}
/**************************************************************************
 virtual ~ZapSound();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
ZapSound::~ZapSound(){
	//Clear()は親クラスが呼ぶ
}
/**************************************************************************
 virtual void ZapSound::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Command& i_DrawPacket.pCommand					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: 描画（サウンドなのでなにもしない）
 戻り値: なし。
***************************************************************************/
//void ZapSound::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
//		  vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& i_DrawPacket.pCommand){
//}
/**************************************************************************
 void PlayZap();
 用途: Zapを鳴らす
 戻り値: なし。
***************************************************************************/
void ZapSound::PlayZap(){
	if(m_pSoundBank){
		m_pSoundBank->Play(m_iZap, 5, 0, NULL );	
	}
}
/**************************************************************************
 void ZapSound::PlayFire();
 用途: 発射音を鳴らす
 戻り値: なし。
***************************************************************************/
void ZapSound::PlayFire(){
	if(m_pSoundBank){
		m_pSoundBank->Play(m_iFire, 0, 0, NULL );
	}
}
/**************************************************************************
 void ZapSound::BGM();
 用途: ゲーム中のBGM
 戻り値: なし。
***************************************************************************/
void ZapSound::BGM(){
	if(m_pSoundBank){
		m_pSoundBank->Play(m_iBGM, 0, 0, NULL );
	}
}
/**************************************************************************
 void ZapSound::PlayFire();
 用途: 発射音を鳴らす
 戻り値: なし。
***************************************************************************/
void ZapSound::BS(){
	if(m_pSoundBank){
		m_pSoundBank->Play(m_iBS, 0, 0, NULL );
	}
}
/**************************************************************************
 void ZapSound::BGM();
 用途: ゲーム中のBGM
 戻り値: なし。
***************************************************************************/
void ZapSound::GET(){
	if(m_pSoundBank){
		m_pSoundBank->Play(m_iGET, 0, 0, NULL );
	}
}
/**************************************************************************
 void ZapSound::BGM();
 用途: ゲーム中のBGM
 戻り値: なし。
***************************************************************************/
void ZapSound::HANAB1(){
	if(m_pSoundBank){
		m_pSoundBank->Play(m_iHANAB1, 0, 0, NULL );
	}
}
/**************************************************************************
 void ZapSound::BGM();
 用途: ゲーム中のBGM
 戻り値: なし。
***************************************************************************/
void ZapSound::HANAB2(){
	if(m_pSoundBank){
		m_pSoundBank->Play(m_iHANAB2, 0, 0, NULL );
	}
}
}//end of namespace	baseobject.
}//end of namespace	wiz.