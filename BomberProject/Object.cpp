////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：Object.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：
//					▼
//	namespace wiz;
//		class Object ;
//		class Light  ;
//		class DirectionalLight : public Light , public Object ;
//
#include "StdAfx.h"
#include "Object.h"

namespace wiz{
namespace system{
/**************************************************************************
 Light 定義部
****************************************************************************/
/////////////////// ////////////////////
//// 用途       ：Light()
//// カテゴリ   ：こんすとらくた
//// 用途       ：プロテクトコンストラクタ
//// 引数       ：なし
//// 戻値       ：なし 
//// 担当者     ：
//// 備考       ：直接構築できないように、プロテクトにする
////            ：
////
Light::Light(wiz::OBJID id)
:Object(id)
{
    // D3DLIGHT9構造体を0でクリアする
    ::ZeroMemory(&m_Light, sizeof(D3DLIGHT9));
}
/////////////////// ////////////////////
//// 用途       ：Light()
//// カテゴリ   ：ですとらくた
//// 用途       ：プロテクトデストラクタ（仮想デストラクタ）
//// 引数       ：なし
//// 戻値       ：なし 
//// 担当者     ：
//// 備考       ：直接構築できないように、プロテクトにする
////            ：
Light::~Light(){}
/**************************************************************************
 DirectionalLight 定義部
****************************************************************************/
/////////////////// ////////////////////
//// 用途       ：DirectionalLight(LPDIRECT3DDEVICE9 pD3DDevice,
////            ：    D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,
////            ：    D3DCOLORVALUE Ambient,D3DXVECTOR3 Direction)
//// カテゴリ   ：コンストラクタ
//// 用途       ：
//// 引数       ：なし
//// 戻値       ：  LPDIRECT3DDEVICE9 pD3DDevice,   //デバイス
////            ：  D3DCOLORVALUE Diffuse,          //ディフューズ色
////            ：  D3DCOLORVALUE Specular,         //スペキュラ色
////            ：  D3DCOLORVALUE Ambient,          //アンビエント色
////            ：  D3DXVECTOR3 Direction           //ワールド空間で光が指す方向
//// 担当者     ：
//// 備考       ：ディレクショナルライトを構築する
////            ：
////
DirectionalLight::DirectionalLight(LPDIRECT3DDEVICE9 pD3DDevice,
    D3DCOLORVALUE Diffuse,
    D3DCOLORVALUE Specular,
    D3DCOLORVALUE Ambient,
    D3DXVECTOR3 Direction,
	wiz::OBJID id)
    :Light(id)
{
    m_Light.Type		= D3DLIGHT_DIRECTIONAL;
    m_Light.Diffuse		= Diffuse;
    m_Light.Specular	= Specular;
    m_Light.Ambient		= Ambient;
    D3DXVec3Normalize((D3DXVECTOR3*)&m_Light.Direction, &Direction);
    // ライトをレンダリングパイプラインに設定
    pD3DDevice->SetLight( 0, &m_Light );
    // ライトを有効にする
    pD3DDevice->LightEnable( 0, TRUE );
}
/////////////////// ////////////////////
//// 用途       ：virtual ~DirectionalLight()
//// カテゴリ   ：セストラクタ
//// 用途       ：
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：
//// 備考       ：
////            ：
////
DirectionalLight::~DirectionalLight(){}

/**************************************************************************
 Camera 定義部
****************************************************************************/
/**************************************************************************
 Camera::Camera(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
    D3DXVECTOR3& At,    //直視点
	FLOAT AbsPosZFromAt,//直視点から見た、カメラ位置のZの位置(絶対値指定)
	FLOAT PosYFromAt,	//直視点から見た、カメラ位置のYの位置
    FLOAT Near,         //射影の手前側の距離
    FLOAT Far,          //射影の奥側の距離
    FLOAT FovY          //Y軸射影角度
    );
 用途: コンストラクタ
 ＊カメラ位置の初期値は直接は指定できない。
 ＊直視点からみて、Zの手前に引く相対位置とYの相対位置を指定する。Xは0に固定
 ＊Zの手前に引く相対位置（AbsPosZFromAt）は絶対値化されるので、
	マイナスを指定しても意味がない。
 戻り値: なし
***************************************************************************/
Camera::Camera(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& At,FLOAT AbsPosZFromAt,FLOAT PosYFromAt,
    FLOAT Near,FLOAT Far,FLOAT FovY)
:Object(OBJID_SYS_CAMERA),m_Eye(),m_At(At),m_Near(Near),m_Far(Far),m_FovY(FovY)
{
	try{
		//カメラ位置の確定
		m_Eye.x = m_At.x;
		m_Eye.y = m_At.y + PosYFromAt;
		m_Eye.z = m_At.z - fabs(AbsPosZFromAt);
		//カメラビューの作成
		D3DXMatrixIdentity(&m_View);
		D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
				&D3DXVECTOR3( 0.0f, 1.0f, 0.0f));
		//カメラと直視点との間（Arm）ｗ０作成
		m_Arm = m_At - m_Eye;
		D3DXVECTOR3 m;
		//正規化
		D3DXVec3Normalize(&m,&m_Arm);
		m_TotalAngleXZ = 0;
		//正規化されたYの値から高さのラジアンを得る
		FLOAT a_c,a_s;
		a_c = acos(m.z);
		a_s = asin(m.y);
		if(a_s < 0.0f){
			m_TotalAngleY = a_c;
		}
		else{
			m_TotalAngleY = D3DX_PI + D3DX_PI - a_c;
		}
		// ビューポートの取得
		D3DVIEWPORT9 vp;
		if(FAILED(pD3DDevice->GetViewport(&vp))){
			//実行失敗
			//WinMainのCatchまで飛ぶ
			throw BaseException(
				L"ビューポートの取得に失敗しました。",
				L"Camera::Draw()"
				);
		}
		m_Eye = m_At - m_Arm;
		D3DXMatrixIdentity(&m_View);
		D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
				&D3DXVECTOR3( 0.0f, 1.0f, 0.0f));
		// アスペクト比の計算
		float aspect;
		aspect = (float)vp.Width / (float)vp.Height;
		// 射影行列の初期化
		D3DXMatrixIdentity(&m_Proj);
		//D3DXMatrixPerspectiveFovLH(&m_Proj, D3DXToRadian(m_FovY), aspect,m_Near,m_Far);
		D3DXMatrixOrthoLH(&m_Proj, D3DXToRadian(m_FovY), aspect,m_Near,m_Far);
		// 射影行列の設定
		pD3DDevice->SetTransform(D3DTS_PROJECTION,&m_Proj);
		// カメラの設定
		pD3DDevice->SetTransform(D3DTS_VIEW,&m_View);
	}
	catch(...){
		throw;
	}
}

/**************************************************************************
Camera::Camera(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
    D3DXVECTOR3& Eye,	//カメラの位置
    D3DXVECTOR3& At,    //直視点
    FLOAT Near,         //射影の手前側の距離
    FLOAT Far,          //射影の奥側の距離
    FLOAT FovY          //Y軸射影角度
    );
 用途: Fixカメラの時に使用するコンストラクタ
 戻り値: なし
***************************************************************************/
Camera::Camera(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& Eye,D3DXVECTOR3& At,
	 FLOAT Near,FLOAT Far,FLOAT FovY)
	 :Object(OBJID_SYS_CAMERA),m_View(),m_Proj(),m_Eye(Eye),m_At(At),m_Near(Near),m_Far(Far),m_FovY(FovY)
{
	try{
		m_Arm = m_At - m_Eye;
		//Fixカメラの時に使用するコンストラクタなので
		//カメラ変化はなくても良い
		m_TotalAngleXZ = 0;
		m_TotalAngleY = 0;
		// ビューポートの取得
		D3DVIEWPORT9 vp;
		if(FAILED(pD3DDevice->GetViewport(&vp))){
			//実行失敗
			//WinMainのCatchまで飛ぶ
			throw BaseException(
				L"ビューポートの取得に失敗しました。",
				L"Camera::Draw()"
				);
		}
		m_Eye = m_At - m_Arm;
		D3DXMatrixIdentity(&m_View);
		D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
				&D3DXVECTOR3( 0.0f, 1.0f, 0.0f));
		// アスペクト比の計算
		float aspect;
		aspect = (float)vp.Width / (float)vp.Height;
		// 射影行列の初期化
		D3DXMatrixIdentity(&m_Proj);
		//D3DXMatrixPerspectiveFovLH(&m_Proj, D3DXToRadian(m_FovY), aspect,m_Near,m_Far);
		D3DXMatrixOrthoLH(&m_Proj, D3DXToRadian(m_FovY), aspect,m_Near,m_Far);
		// 射影行列の設定
		pD3DDevice->SetTransform(D3DTS_PROJECTION,&m_Proj);
		// カメラの設定
		pD3DDevice->SetTransform(D3DTS_VIEW,&m_View);
	}
	catch(...){
		throw;
	}
}


/**************************************************************************
 Camera::~Camera();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Camera::~Camera(){
}
/**************************************************************************
 void Camera::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState   //コントローラーのステータス
 );
 用途: カメラを設置
 戻り値: なし。
***************************************************************************/
/**************************************************************************
 virtual void Camera::Draw(
	DrawPacket& i_DrawPacket
);
 用途: オブジェクトを描画（純粋仮想関数）
 戻り値: なし。
***************************************************************************/
void Camera::Draw(DrawPacket& i_DrawPacket){

    // ビューポートの取得
    D3DVIEWPORT9 vp;
    if(FAILED(i_DrawPacket.pD3DDevice->GetViewport(&vp))){
        //実行失敗
		//WinMainのCatchまで飛ぶ
        throw BaseException(
            L"ビューポートの取得に失敗しました。",
            L"Camera::Draw()"
            );
    }
	m_Eye = m_At - m_Arm;
    D3DXMatrixIdentity(&m_View);
    D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
            &D3DXVECTOR3( 0.0f, 1.0f, 0.0f));
    // アスペクト比の計算
    float aspect;
    aspect = (float)vp.Width / (float)vp.Height;
    // 射影行列の初期化
    D3DXMatrixIdentity(&m_Proj);
    D3DXMatrixPerspectiveFovLH(&m_Proj, D3DXToRadian(m_FovY), aspect,m_Near,m_Far);
    // 射影行列の設定
    i_DrawPacket.pD3DDevice->SetTransform(D3DTS_PROJECTION,&m_Proj);
    // カメラの設定
    i_DrawPacket.pD3DDevice->SetTransform(D3DTS_VIEW,&m_View);
}


/**************************************************************************
 class LookAtCamera : public Object;
 用途: オブジェクトを注目するカメラクラス
****************************************************************************/
/**************************************************************************
 LookAtCamera::LookAtCamera(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
    Object*	pObj,		//直視点を得るためのオブジェクト
	FLOAT LocalY,		//直視点から調整するY位置
	FLOAT AbsPosZFromAt,//直視点から見た、カメラ位置のZの位置(絶対値指定)
	FLOAT PosYFromAt,	//直視点から見た、カメラ位置のYの位置
    FLOAT Near,         //射影の手前側の距離
    FLOAT Far,          //射影の奥側の距離
    FLOAT FovY          //Y軸射影角度
    );
 用途: コンストラクタ
 ＊カメラ位置の初期値は直接は指定できない。
 ＊直視点からみて、Zの手前に引く相対位置とYの相対位置を指定する。Xは0に固定
 ＊Zの手前に引く相対位置（AbsPosZFromAt）は絶対値化されるので、
	マイナスを指定しても意味がない。
 戻り値: なし
***************************************************************************/
LookAtCamera::LookAtCamera(LPDIRECT3DDEVICE9 pD3DDevice,
		Object* pObj,FLOAT LocalY,FLOAT AbsPosZFromAt,FLOAT PosYFromAt,
	    FLOAT Near,FLOAT Far,FLOAT FovY)
:

Camera(
	pD3DDevice,			//デバイス
	D3DXVECTOR3(0,0,0),    //カメラの位置
	D3DXVECTOR3(0,0,0),    //直視点
	Near,         //射影の手前側の距離
	Far,          //射影の奥側の距離
	FovY          //Y軸射影角度
	),
m_pObject(pObj),
m_LocalY(LocalY)
{
	try{
		D3DXVECTOR3 ObjPos(0,0,0);
		if(m_pObject){
			ObjPos = m_pObject->getPos();
		}
		//直視点を取得
		m_At = ObjPos;
		m_At.y += m_LocalY;

		//カメラ位置の確定
		m_Eye.x = m_At.x;
		m_Eye.y = m_At.y + PosYFromAt;
		m_Eye.z = m_At.z - fabs(AbsPosZFromAt);
		//カメラビューの作成
		D3DXMatrixIdentity(&m_View);
		D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
				&D3DXVECTOR3( 0.0f, 1.0f, 0.0f));
		//カメラと直視点との間（Arm）ｗ０作成
		m_Arm = m_At - m_Eye;
		D3DXVECTOR3 m;
		//正規化
		D3DXVec3Normalize(&m,&m_Arm);
		m_TotalAngleXZ = 0;
		//正規化されたYの値から高さのラジアンを得る
		FLOAT a_c,a_s;
		a_c = acos(m.z);
		a_s = asin(m.y);
		if(a_s < 0.0f){
			m_TotalAngleY = a_c;
		}
		else{
			m_TotalAngleY = D3DX_PI + D3DX_PI - a_c;
		}
		// ビューポートの取得
		D3DVIEWPORT9 vp;
		if(FAILED(pD3DDevice->GetViewport(&vp))){
			//実行失敗
			//WinMainのCatchまで飛ぶ
			throw BaseException(
				L"ビューポートの取得に失敗しました。",
				L"Camera::Draw()"
				);
		}
		D3DXMatrixIdentity(&m_View);
		D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
				&D3DXVECTOR3( 0.0f, 1.0f, 0.0f));
		// アスペクト比の計算
		float aspect;
		aspect = (float)vp.Width / (float)vp.Height;
		// 射影行列の初期化
		D3DXMatrixIdentity(&m_Proj);
		D3DXMatrixPerspectiveFovLH(&m_Proj, D3DXToRadian(m_FovY), aspect,m_Near,m_Far);
		// 射影行列の設定
		pD3DDevice->SetTransform(D3DTS_PROJECTION,&m_Proj);
		// カメラの設定
		pD3DDevice->SetTransform(D3DTS_VIEW,&m_View);

	}
	catch(...){
		//再スロー
		throw;
	}

}


/**************************************************************************
 LookAtCamera::~LookAtCamera();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
LookAtCamera::~LookAtCamera(){
}

/**************************************************************************
 virtual void LookAtCamera::Transform(
 vector<Object*>& Vec,            //オブジェクトの配列
 const CONTROLER_STATE* pCntlState,	//コントローラの状態
 Context& Data					//ユーザーデータ
 );
 用途: オブジェクトを変化させる（純粋仮想関数）
 戻り値: なし。
***************************************************************************/
void LookAtCamera::Update( UpdatePacket& i_UpdatePacket ){


    if(i_UpdatePacket.pCntlState[0].bConnected){
		BoxCon wButtons = i_UpdatePacket.pCntlState[0].Gamepad.wButtons.XConState;
		Point  sThumbR  = Point( i_UpdatePacket.pCntlState[0].Gamepad.sThumbRX, i_UpdatePacket.pCntlState[0].Gamepad.sThumbRY);

		D3DXVECTOR3 ObjPos(0,0,0);
		if(m_pObject){
			ObjPos = m_pObject->getPos();
		}
		//現在の直視点を得る
		m_At.x = ObjPos.x;
		m_At.z = ObjPos.z;
		//m_Eye位置の変更１
		if(wButtons.RIGHT_SHOULDER){
			//完全注目
			m_At.y = ObjPos.y;
			m_At.y += m_LocalY;
		}

		//カメラ位置と注視点の間のベクトルを算出
		D3DXVECTOR3 span = m_Eye - m_At;
		//正規化
		D3DXVec3Normalize(&span,&span);
		//分割
		span = span * 0.2f;
		//Dパッド下
		//カメラを引く
        if(wButtons.DOWN){
			//カメラ位置を引く
			m_Eye = m_Eye + span;
		    m_Arm = m_At - m_Eye;
			if(D3DXVec3Length(&m_Arm) > (m_Far * 0.5f)){
				m_Eye = m_Eye - span;
			    m_Arm = m_At - m_Eye;
			}
        }
		//Dパッド上
		//カメラを寄る
        if(wButtons.UP){
			//カメラ位置を寄る
			m_Eye = m_Eye - span;
		    m_Arm = m_At - m_Eye;
			if(D3DXVec3Length(&m_Arm) < 2.0f){
				m_Eye = m_Eye + span;
			    m_Arm = m_At - m_Eye;
			}
        }
		//m_Eye位置の変更２
		FLOAT AngleX = 0;
		//右スティックX方向
        if(sThumbR.x != 0){
            AngleX = sThumbR.x / 1000000.0f;
        }
		//右スティックY方向
		FLOAT AngleY = 0;
        if(sThumbR.y != 0){
            AngleY = sThumbR.y / 1000000.0f;
        }
		m_TotalAngleXZ += AngleX;
		if(m_TotalAngleXZ > (D3DX_PI * 2)){
			m_TotalAngleXZ -= (D3DX_PI * 2);
		}
		if(m_TotalAngleXZ < -(D3DX_PI * 2)){
			m_TotalAngleXZ += (D3DX_PI * 2);
		}
		m_TotalAngleY += AngleY;
		if(m_TotalAngleY < -(D3DX_PI / 180)){
			m_TotalAngleY = -(D3DX_PI / 180);
		}
		if(m_TotalAngleY > (D3DX_PI / 4)){
			m_TotalAngleY = (D3DX_PI / 4);
		}
		FLOAT xArm = D3DXVec3Length(&m_Arm) * cos(m_TotalAngleY);
		FLOAT yArm = D3DXVec3Length(&m_Arm) * sin(m_TotalAngleY);
		m_Eye.x = xArm * sin(m_TotalAngleXZ) + m_At.x;
		m_Eye.y = yArm + m_At.y;
		m_Eye.z = xArm * -cos(m_TotalAngleXZ) + m_At.z;
	    m_Arm = m_At - m_Eye;
	}
}



/**************************************************************************
 virtual void LookAtCamera::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Context& Data					//ユーザーデータ
 );
 用途: オブジェクトを描画（純粋仮想関数）
 戻り値: なし。
***************************************************************************/
void LookAtCamera::Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& Vec,
	const CONTROLER_STATE* pCntlState,Context& Data){
    // ビューポートの取得
    D3DVIEWPORT9 vp;
    if(FAILED(pD3DDevice->GetViewport(&vp))){
        //実行失敗
		//WinMainのCatchまで飛ぶ
        throw BaseException(
            L"ビューポートの取得に失敗しました。",
            L"Camera::Draw()"
            );
    }
    D3DXMatrixIdentity(&m_View);
    D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
            &D3DXVECTOR3( 0.0f, 1.0f, 0.0f));
    // アスペクト比の計算
    float aspect;
    aspect = (float)vp.Width / (float)vp.Height;
    // 射影行列の初期化
    D3DXMatrixIdentity(&m_Proj);
    D3DXMatrixPerspectiveFovLH(&m_Proj, D3DXToRadian(m_FovY), aspect,m_Near,m_Far);
    // 射影行列の設定
    pD3DDevice->SetTransform(D3DTS_PROJECTION,&m_Proj);
    // カメラの設定
    pD3DDevice->SetTransform(D3DTS_VIEW,&m_View);
}


/**************************************************************************
 class Guide 定義部
****************************************************************************/
/**************************************************************************
 void Guide::CreateInctance(
 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9インターフェイスへのポインタ
 );
 用途: インスタンスの構築
 戻り値: なし。（例外がthrowされる）
***************************************************************************/
void Guide::CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice){
	ReleaseObj();
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
		ReleaseObj();
        //再スロー
        throw;
    }
}

/**************************************************************************
 Guide::Guide(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9インターフェイスへのポインタ
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
Guide::Guide(LPDIRECT3DDEVICE9 pD3DDevice)
:Object(OBJID_SYS_GUIDELINE),m_pVB(0)
{
	CreateInctance(pD3DDevice);
}
/**************************************************************************
 Guide::~Guide();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Guide::~Guide(){
	ReleaseObj();
}
/**************************************************************************
	virtual void Guide::ReleaseObj();
 用途: デバイス喪失によるリソースの開放（仮想関数）
 戻り値: なし。
 ＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
void Guide::ReleaseObj(){
    SafeRelease(m_pVB);
}

/**************************************************************************
	virtual void Guide::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
 用途: デバイス喪失による再構築（仮想関数）
 戻り値: なし。
 ＊デバイスが喪失したときに最構築時に呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
void Guide::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//基底クラスでは何もしない
	CreateInctance(pD3DDevice);
}


/**************************************************************************
 virtual void Guide::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Context& Data					//ユーザーデータ
 );
 用途: オブジェクトを描画（純粋仮想関数）
 戻り値: なし。
***************************************************************************/
void Guide::Draw(DrawPacket& i_DrawPacket){
	LPDIRECT3DDEVICE9 pD3DDevice = i_DrawPacket.pD3DDevice ;
	if(!m_pVB){
		//バッファが無効なら何もしない
		return;
	}
    D3DXMATRIX  wm;
    //座標変換無し
    D3DXMatrixIdentity(&wm);
    // マトリックスをレンダリングパイプラインに設定
    pD3DDevice->SetTransform(D3DTS_WORLD, &wm);
    pD3DDevice->SetStreamSource( 0, m_pVB, 0, sizeof( CUSTOMVERTEX ) );
    pD3DDevice->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE);
    pD3DDevice->SetRenderState( D3DRS_LIGHTING,FALSE);
    pD3DDevice->LightEnable( 0, FALSE );
    pD3DDevice->DrawPrimitive(D3DPT_LINELIST, 0, 3);
    pD3DDevice->SetRenderState( D3DRS_LIGHTING,TRUE);
    pD3DDevice->LightEnable( 0, TRUE );
}




}
//end of namespace system.

}
//end of namespace wiz.

