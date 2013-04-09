////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FStick Figures
//	�t�@�C����		�FDebug_Stage.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�f�o�b�N�p�X�e�[�W
//					��
//	namespace wiz;
//		class DebugStage : public MenuStage;
//		class DebugMenu  : public MenuStage;
//
#pragma once
#include "BassItems.h"
namespace wiz{
extern class Player;

class Effect : public Object{
protected:
	Effect( wiz::OBJID id = OBJID_3D_EFFECT ) : Object(id){}
};


//	: ���_�f�[�^�̒�`
struct	Vertex
{
	D3DXVECTOR3	vPos ;		//	: ���_�́A�ʒu���W�f�[�^������
	DWORD		dwColor ;	//	: ���_�́A�F�f�[�^������
	D3DXVECTOR2	vTex ;		//	: ���_�́A�e�N�X�`�����W������

	//	: �f�t�H���g�R���X�g���N�^
	Vertex()
	{
	}
	//	: ���������ȗ������邽�߂̈����t���R���X�g���N�^
	Vertex( const D3DXVECTOR3& i_vPos, DWORD i_dwColor, const D3DXVECTOR2& i_vTex )
		: vPos( i_vPos ), dwColor( i_dwColor ), vTex( i_vTex )
	{
	}
	//	: �f�X�g���N�^
	virtual ~Vertex()
	{
	}

	//	: ���̒��_�f�[�^�̌`����Ԃ�
	static DWORD	getFVF()
	{
		return D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 ;
	}

	//	: ���̒��_�f�[�^�̃f�[�^�T�C�Y��Ԃ�
	static int		getSize()
	{
		return sizeof( Vertex );
	}
};

//////////
//	: Particle�p�̒��_�f�[�^
struct PointVertex{
	D3DXVECTOR3 vPos ;
	union{
		DWORD dwColor ;
		struct {
			BYTE b,g,r,a;
		}Color;
	};
	PointVertex()
		:vPos(0.0f,0.0f,0.0f),dwColor(0x00000000)
	{}
	PointVertex(const D3DXVECTOR3& i_vPos, DWORD i_dwColor)
		:vPos(i_vPos),dwColor(i_dwColor)
	{}
	~PointVertex()
	{}
	static DWORD getFVF(){
		return D3DFVF_XYZ | D3DFVF_DIFFUSE ;	//	: ���_���ƐF�̂�
	}
	static int getSize()
	{
		return sizeof( PointVertex );
	}

};
//
///////////
class Particle{
private:
	PointVertex		m_VertexList;
	D3DXVECTOR3		m_vDirection;
	float			m_fSpeed;
public:
	Particle()
		:m_vDirection(0.0f,0.0f,0.0f)
		,m_fSpeed(0.08f)
	{
//		m_VertexList.dwColor = 0x00FF00FF;
		BYTE ColorType = rand() % 4 ;
		switch(ColorType){
			case 0:
				m_VertexList.Color.r = 0xFF;
				break;
			case 1:
				m_VertexList.Color.g = 0xFF;
				break;
			case 2:
				m_VertexList.Color.b = 0xFF;
				break;
			case 3:
				m_VertexList.Color.r = 0xFF;
				m_VertexList.Color.g = 0xFF;
				break;
		}
		m_vDirection.x = (rand() % 1000) / 1000.0f - 0.5f;
		m_vDirection.y = (rand() % 1000) / 1000.0f - 0.5f;
		m_vDirection.z = (rand() % 1000) / 1000.0f - 0.5f;

		//m_VertexList.vPos = m_vDirection;
	};
	void Draw(IDirect3DDevice9* pd3dDevice){

		//////////
		//	: ���_�̈ړ�
		m_VertexList.vPos += m_vDirection * m_fSpeed;

		//////////
		//	: ���_�Ƀe�N�X�`����\��t����
		float fPointSize = 0.03f;
		pd3dDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE );
		pd3dDevice->SetRenderState(D3DRS_POINTSCALEENABLE , TRUE );
		pd3dDevice->SetRenderState(D3DRS_POINTSIZE, *(DWORD*)&fPointSize );
		//	
		//////////

		pd3dDevice->SetFVF(PointVertex::getFVF());
		pd3dDevice->DrawPrimitiveUP(D3DPT_POINTLIST , 1 , &m_VertexList , PointVertex::getSize() );

	};
};
class Particles{
private:
	list<Particle*> m_ParticleList;
	LPDIRECT3DTEXTURE9 m_pParticle;
public:
	Particles(IDirect3DDevice9* pd3dDevice)
		:m_pParticle(NULL)
	{
		D3DXCreateTextureFromFile(pd3dDevice, TEXT("media/Textures/kira1_96x96.png"), &m_pParticle);
		srand((long)time(NULL));
		BYTE pQt = rand();
		do{
			m_ParticleList.push_back(new Particle());
		}while(--pQt > 0);
	};
	virtual ~Particles(){
		SAFE_RELEASE(m_pParticle);
		list<Particle*>::iterator it = m_ParticleList.begin();
		for( ;it != m_ParticleList.end(); it++ ){
			SAFE_DELETE(*it);
		}
	};

	void Draw(IDirect3DDevice9* pd3dDevice){
		//////////
		//	: �����_�[�X�e�[�g�̕ێ�
		DWORD	dwLighting_Status,
				dwAlphaEnable_Status,
				dwSrcBlend_Status,
				dwDestBlend_Status,
				dwZwrteenable_Status;

		pd3dDevice->GetRenderState( D3DRS_LIGHTING,			&dwLighting_Status		);
		pd3dDevice->GetRenderState( D3DRS_ALPHABLENDENABLE,	&dwAlphaEnable_Status	);
		pd3dDevice->GetRenderState( D3DRS_SRCBLEND,			&dwSrcBlend_Status		);
		pd3dDevice->GetRenderState( D3DRS_DESTBLEND,		&dwDestBlend_Status		);
		pd3dDevice->GetRenderState( D3DRS_ZWRITEENABLE,		&dwZwrteenable_Status	);
		//
		//////////

		//////////
		//	: �f�o�C�X�̐ݒ�
		pd3dDevice->SetRenderState( D3DRS_LIGHTING,			FALSE			);
		pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,	TRUE			);
		pd3dDevice->SetRenderState( D3DRS_SRCBLEND,			D3DBLEND_ONE	);
		pd3dDevice->SetRenderState( D3DRS_DESTBLEND,		D3DBLEND_ONE	);
		pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,		FALSE			);
		
		//	: �e�N�X�`�����ڂ����ݒ�i�h�b�g��ڗ����Ȃ�����j
		pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
		pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
		//pd3dDevice->SetRenderState(D3DRS_LIGHTING , FALSE);

		pd3dDevice->SetTexture(0,m_pParticle);
		//
		//////////

		//////////
		//	: �e���_�̕`��
		list<Particle*>::iterator it = m_ParticleList.begin();
		for( ;it != m_ParticleList.end(); it++ ){
			(*it)->Draw(pd3dDevice);
		}
		//
		//////////

		//////////
		//	: �����_�[�X�e�[�g�̕���
		pd3dDevice->SetRenderState( D3DRS_LIGHTING,			dwLighting_Status		);
		pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,	dwAlphaEnable_Status	);
		pd3dDevice->SetRenderState( D3DRS_SRCBLEND,			dwSrcBlend_Status		);
		pd3dDevice->SetRenderState( D3DRS_DESTBLEND,		dwDestBlend_Status		);
		pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,		dwZwrteenable_Status	);
		//
		//////////
	};
};

struct fRect{
	float left , top , right , bottom;
	fRect(){}
	fRect(float l,float t,float r,float b)
	:left(l) , top(t) , right(r) , bottom(b){}
};

class SlidingEffect : public Effect , public PrimitiveBox{
private:
	Player*		m_pPlayer;
	const BYTE	m_byFrameQty;
	BYTE		m_byFrameNum;
	fRect*		m_pFrameRectArray;
	void ChangeUV();
public:
	SlidingEffect(LPDIRECT3DDEVICE9 pD3DDevice,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		Player* pPlayer,BYTE byFrameQty,fRect FirstRect,LPDIRECT3DTEXTURE9 pTexture = 0);
	~SlidingEffect();
	
};



}	//	: wiz