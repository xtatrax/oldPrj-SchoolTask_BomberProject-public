#pragma once
#include "StdAfx.h"
#include "Object.h"

namespace wiz{

class Line
{
	struct Vertex
	{
		D3DXVECTOR3 vPos ;
		float fRhw ;
		DWORD dwColor ;

		Vertex()
			: vPos( 0.0f, 0.0f, 0.0f ), fRhw( 1.0f ), dwColor( 0xFFFFFFFF )
		{
		}

		Vertex( const D3DXVECTOR3& i_vPos, DWORD i_dwColor )
			: vPos( i_vPos ), fRhw( 1.0f ), dwColor( i_dwColor )
		{
		}

		static size_t getSize()
		{
			return sizeof( Vertex );
		}

		static DWORD getFVF()
		{
			return D3DFVF_XYZRHW | D3DFVF_DIFFUSE ;
		}
	};

private:
	Vertex m_Vertices[ 2 ] ;

	D3DXVECTOR3 m_vStartPos ;
	D3DXVECTOR3 m_vEndPos ;
	D3DXVECTOR3 m_vDir ;
	float		m_fLength ;
	float		m_fAngle ;
	DWORD		m_dwColor ;

public:
	Line();
	Line( const D3DXVECTOR3& i_vStartPos, const D3DXVECTOR3& i_vDirection, float i_fLength, DWORD i_dwColor = 0xFFFFFFFF );
	Line( const D3DXVECTOR3& i_vStartPos, const D3DXVECTOR3& i_vEndPos, DWORD i_dwColor = 0xFFFFFFFF );
	Line( float i_fRadian, float i_fLength, DWORD i_dwColor = 0xFFFFFFFF );

	void	setMatrix( const D3DXMATRIX& i_Matrix );
	void	setColor( DWORD i_dwColor );
	float getLength() const
	{
		return m_fLength ;
	}

	float getAngle() const
	{
		return m_fAngle ;
	}

	const D3DXVECTOR3& getDirection() const
	{
		return m_vDir ;
	}

	void draw( const LPDIRECT3DDEVICE9 i_pd3dDevice ) const ;

	D3DXVECTOR3	getEndPos(){
		return	m_vEndPos;
	}
};

class Line2
{
	struct Vertex
	{
		D3DXVECTOR3 vPos ;
		float fRhw ;
		DWORD dwColor ;

		Vertex()
			: vPos( 0.0f, 0.0f, 0.0f ), fRhw( 1.0f ), dwColor( 0xFFFFFFFF )
		{
		}

		Vertex( const D3DXVECTOR3& i_vPos, DWORD i_dwColor )
			: vPos( i_vPos ), fRhw( 1.0f ), dwColor( i_dwColor )
		{
		}

		static size_t getSize()
		{
			return sizeof( Vertex );
		}

		static DWORD getFVF()
		{
			return D3DFVF_XYZ | D3DFVF_DIFFUSE ;
		}
	};

private:
	Vertex m_Vertices[ 2 ] ;

	D3DXVECTOR3 m_vStartPos ;
	D3DXVECTOR3 m_vEndPos ;
	D3DXVECTOR3 m_vDir ;
	float		m_fLength ;
	float		m_fAngle ;
	DWORD		m_dwColor ;

public:
	Line2();
	Line2( const D3DXVECTOR3& i_vStartPos, const D3DXVECTOR3& i_vDirection, float i_fLength, DWORD i_dwColor = 0xFFFFFFFF );
	Line2( const D3DXVECTOR3& i_vStartPos, const D3DXVECTOR3& i_vEndPos, DWORD i_dwColor = 0xFFFFFFFF );
	Line2( float i_fRadian, float i_fLength, DWORD i_dwColor = 0xFFFFFFFF );

	void	setMatrix( const D3DXMATRIX& i_Matrix );
	void	setColor( DWORD i_dwColor );
	float getLength() const
	{
		return m_fLength ;
	}

	float getAngle() const
	{
		return m_fAngle ;
	}

	const D3DXVECTOR3& getDirection() const
	{
		return m_vDir ;
	}

	void draw( const LPDIRECT3DDEVICE9 i_pd3dDevice ) const ;

	D3DXVECTOR3	getEndPos(){
		return	m_vEndPos;
	}
};

}