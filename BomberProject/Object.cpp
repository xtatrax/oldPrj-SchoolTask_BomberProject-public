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
Light::Light(){
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
    :Light()
	,Object(id)
{
    m_Light.Type       = D3DLIGHT_DIRECTIONAL;
    m_Light.Diffuse = Diffuse;
    m_Light.Specular = Specular;
    m_Light.Ambient = Ambient;
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


}
//end of namespace wiz.

