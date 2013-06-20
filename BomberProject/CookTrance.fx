//	: �O���ϐ��̐錾�i�A�v���P�[�V�������̃f�[�^���󂯎�邽�߂̕ϐ��j
float4x4	g_mWorldViewProj ;
float4x4	g_mWorld ;
//float4x4	g_mWorldInverseTranspose ;
float4x4	g_mWIT ;

texture		g_Texture ;

float3		g_vEyePos ;

float3		g_vLightDir = { 0.0, -1.0, 0.0 } ;	//	���̕���

//	���̋���
float4		g_Ia	= { 0.3, 0.3, 0.3, 1.0 } ;	//	ambient�i�����j
float4		g_Id	= { 0.7, 0.7, 0.7, 1.0 } ;	//	diffuse�i���ˌ��j

//	���̂̐F�i���˗��j
float4		g_Ka	= { 1.0, 1.0, 1.0, 1.0 } ;	//	ambient
float4		g_Kd	= { 1.0, 1.0, 1.0, 1.0 } ;	//	diffuse

//	�e�N�X�`���T���v��
sampler	TexSamp	= sampler_state {
	Texture	= <g_Texture> ;
	MinFilter	= LINEAR ;
	MagFilter	= LINEAR ;
};

//	���_�V�F�[�_�̏o�̓f�[�^�i�s�N�Z���V�F�[�_�̓��̓f�[�^�j
struct	VS_OUTPUT
{
	float4	vPos	: POSITION ;
	float4	vColor	: COLOR0 ;
	float2	vUV		: TEXCOORD0 ;
	float3	vNormal	: TEXCOORD1 ;
	float3	vEye	: TEXCOORD2 ;
	//float3	vPosBefore	: TEXCOORD2 ;
};

//	: ���_�V�F�[�_�i���̂̒��_���\������p�����[�^��ϊ����邽�߂̃V�F�[�_�j
VS_OUTPUT	VS( float3 i_vPos : POSITION,
				float3 i_vNormal : NORMAL,
				float2 i_vUV : TEXCOORD0 )
{
	VS_OUTPUT	Out ;
	//	: �o�͍��W���Z�o
	Out.vPos	= mul( float4( i_vPos, 1.0 ), g_mWorldViewProj );
	
	//	: �o�̓J���[���Z�o
	float3	L			= -g_vLightDir ;
	float3	N			= normalize( mul( i_vNormal, (float3x3)g_mWIT ) );
	Out.vColor	= g_Kd * g_Id * max( 0, dot( N, L ) ) + g_Ka * g_Ia ;
	
	//	: �e�N�X�`�����W�i�t�u���W�j�����肷��
	Out.vUV		= i_vUV ;
	
	//	: �ϊ��ς݂̖@���x�N�g��
	Out.vNormal	= N ;
	
	//	: ���_����J�����̕������w���x�N�g�����Z�o
	Out.vEye	= normalize( g_vEyePos - i_vPos.xyz );
	
	return Out ;
}

//	: �s�N�Z���V�F�[�_�i���̂̐F�����肷�適�����ɂ���ĐF�����߂邱�Ƃŗl�X�ȉ��o���ł���j
float4	PS( VS_OUTPUT In ) : COLOR0
{
	float3	L	= -g_vLightDir ;
	float3	V	= In.vEye ;
	float3	H	= normalize( L + V );
	float3	N	= In.vNormal ;

	//	: �v�Z�p�Ɏg�����ꂼ��̓��ρi�e�̔䗦�j
	float	NV	= dot( N, V );
	float	NH	= dot( N, H );
	float	VH	= dot( V, H );
	float	NL	= dot( N, L );
	float	LH	= dot( L, H );
	
	//	: Beckman�̕��z�֐�
	const float m 	= 0.1f ;	//	: ���׉��ʂ̕��z�W��
	float NH2		= NH * NH ;
	float D 		= exp( -(1-NH2) / (NH2 * m * m ) ) / ( 4 * m * m * NH2 * NH2 );
	
	//	: �􉽌�����( �����˂������̖߂��Ă���m�� )
	float G = min( 1.0f, min( 2.0f * NH * NV / NH, 2.0f * NH * NL / NH ) );
	
	//	: �t���l������
	float n		= 20.0f;
	float g		= sqrt( n * n + LH * LH -1 );
	float gpc	= g + LH ;
	float gnc	= g - LH ;
	float cgpc	= LH * gpc -1 ;
	float cgnc	= LH * gpc +1 ;
	float F		= 0.5f * gnc * gnc * ( 1 + cgpc * cgpc / ( cgnc * cgnc ) ) / ( gpc * gpc )  ;

	//	: �����̐F( �� )
	float4 ks	= {
		2.0f * 0.486f , 2.0f * 0.433f , 2.0f * 0.433f , 1.0f 
	};
	
	return //tex2D( TexSamp, In.vUV ) *
	 In.vColor + ks * max( 0, F * D * G / NV ) ;
							//+ pow( max( 0, dot( N, H ) ), 10 ) ;
}

//	: �e�N�j�b�N�i���_�V�F�[�_�ƃs�N�Z���V�F�[�_�̃Z�b�g�����߂�j
technique	FirstTech
{
	pass	P0
	{
		vertexShader	= compile vs_2_0 VS();
		pixelShader		= compile ps_2_0 PS();
	}
}