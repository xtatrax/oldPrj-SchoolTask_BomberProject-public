//	: 外部変数の宣言（アプリケーション側のデータを受け取るための変数）
float4x4	g_mWorldViewProj ;
float4x4	g_mWorld ;
//float4x4	g_mWorldInverseTranspose ;
float4x4	g_mWIT ;

texture		g_Texture ;

float3		g_vEyePos ;

float3		g_vLightDir = { 0.0, -1.0, 0.0 } ;	//	光の方向

//	光の強さ
float4		g_Ia	= { 0.3, 0.3, 0.3, 1.0 } ;	//	ambient（環境光）
float4		g_Id	= { 0.7, 0.7, 0.7, 1.0 } ;	//	diffuse（反射光）

//	物体の色（反射率）
float4		g_Ka	= { 1.0, 1.0, 1.0, 1.0 } ;	//	ambient
float4		g_Kd	= { 1.0, 1.0, 1.0, 1.0 } ;	//	diffuse

//	テクスチャサンプラ
sampler	TexSamp	= sampler_state {
	Texture	= <g_Texture> ;
	MinFilter	= LINEAR ;
	MagFilter	= LINEAR ;
};

//	頂点シェーダの出力データ（ピクセルシェーダの入力データ）
struct	VS_OUTPUT
{
	float4	vPos	: POSITION ;
	float4	vColor	: COLOR0 ;
	float2	vUV		: TEXCOORD0 ;
	float3	vNormal	: TEXCOORD1 ;
	float3	vEye	: TEXCOORD2 ;
	//float3	vPosBefore	: TEXCOORD2 ;
};

//	: 頂点シェーダ（物体の頂点を構成するパラメータを変換するためのシェーダ）
VS_OUTPUT	VS( float3 i_vPos : POSITION,
				float3 i_vNormal : NORMAL,
				float2 i_vUV : TEXCOORD0 )
{
	VS_OUTPUT	Out ;
	//	: 出力座標を算出
	Out.vPos	= mul( float4( i_vPos, 1.0 ), g_mWorldViewProj );
	
	//	: 出力カラーを算出
	float3	L			= -g_vLightDir ;
	float3	N			= normalize( mul( i_vNormal, (float3x3)g_mWIT ) );
	Out.vColor	= g_Kd * g_Id * max( 0, dot( N, L ) ) + g_Ka * g_Ia ;
	
	//	: テクスチャ座標（ＵＶ座標）を決定する
	Out.vUV		= i_vUV ;
	
	//	: 変換済みの法線ベクトル
	Out.vNormal	= N ;
	
	//	: 頂点からカメラの方向を指すベクトルを算出
	Out.vEye	= normalize( g_vEyePos - i_vPos.xyz );
	
	return Out ;
}

//	: ピクセルシェーダ（物体の色を決定する←条件によって色を決めることで様々な演出ができる）
float4	PS( VS_OUTPUT In ) : COLOR0
{
	float3	L	= -g_vLightDir ;
	float3	V	= In.vEye ;
	float3	H	= normalize( L + V );
	float3	N	= In.vNormal ;

	//	: 計算用に使うそれぞれの内積（各の比率）
	float	NV	= dot( N, V );
	float	NH	= dot( N, H );
	float	VH	= dot( V, H );
	float	NL	= dot( N, L );
	float	LH	= dot( L, H );
	
	//	: Beckmanの分布関数
	const float m 	= 0.1f ;	//	: 微細凹凸の分布係数
	float NH2		= NH * NH ;
	float D 		= exp( -(1-NH2) / (NH2 * m * m ) ) / ( 4 * m * m * NH2 * NH2 );
	
	//	: 幾何減衰率( 乱反射した光の戻ってくる確率 )
	float G = min( 1.0f, min( 2.0f * NH * NV / NH, 2.0f * NH * NL / NH ) );
	
	//	: フレネル反射
	float n		= 20.0f;
	float g		= sqrt( n * n + LH * LH -1 );
	float gpc	= g + LH ;
	float gnc	= g - LH ;
	float cgpc	= LH * gpc -1 ;
	float cgnc	= LH * gpc +1 ;
	float F		= 0.5f * gnc * gnc * ( 1 + cgpc * cgpc / ( cgnc * cgnc ) ) / ( gpc * gpc )  ;

	//	: 金属の色( 金 )
	float4 ks	= {
		2.0f * 0.486f , 2.0f * 0.433f , 2.0f * 0.433f , 1.0f 
	};
	
	return //tex2D( TexSamp, In.vUV ) *
	 In.vColor + ks * max( 0, F * D * G / NV ) ;
							//+ pow( max( 0, dot( N, H ) ), 10 ) ;
}

//	: テクニック（頂点シェーダとピクセルシェーダのセットを決める）
technique	FirstTech
{
	pass	P0
	{
		vertexShader	= compile vs_2_0 VS();
		pixelShader		= compile ps_2_0 PS();
	}
}