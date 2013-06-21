#include "StdAfx.h"
#include "Line.h"

namespace wiz{

Line::Line()
	: m_vStartPos( D3DXVECTOR3(0.0f, 0.0f, 0.0f) ), m_vDir( D3DXVECTOR3(1.0f, 0.0f, 0.0f) ), m_vEndPos( m_vDir ), m_fLength( 1.0f ), m_fAngle( 0.0f ), m_dwColor(0xFFFFFFFF)
{
}

Line::Line( const D3DXVECTOR3& i_vStartPos, const D3DXVECTOR3& i_vDirection, float i_fLength, DWORD i_dwColor )
	: m_vStartPos( i_vStartPos ), m_fLength( i_fLength ), m_dwColor( i_dwColor )
{
	D3DXVec3Normalize( &m_vDir, &i_vDirection );
	m_vEndPos	= m_vStartPos + m_vDir * m_fLength ;
	
	float	fAngle = atan2( m_vDir.y, m_vDir.x );
	m_fAngle	= ( fAngle >= 0.0f ) ? fAngle : D3DX_PI * 2.0f + fAngle ;
	
	m_Vertices[ 0 ]	= Vertex( m_vStartPos, m_dwColor );
	m_Vertices[ 1 ]	= Vertex( m_vEndPos, m_dwColor );
}

Line::Line( const D3DXVECTOR3& i_vStartPos, const D3DXVECTOR3& i_vEndPos, DWORD i_dwColor )
	: m_vStartPos( i_vStartPos ), m_vEndPos( i_vEndPos ), m_dwColor( i_dwColor )
{
	D3DXVECTOR3	v	= m_vEndPos - m_vStartPos ;
	m_fLength	= D3DXVec3Length( &v );
	D3DXVec3Normalize( &m_vDir, &v );

	float	fAngle = atan2( v.y, v.x );
	m_fAngle	= ( fAngle >= 0.0f ) ? fAngle : D3DX_PI * 2.0f + fAngle ;
	
	m_Vertices[ 0 ]	= Vertex( m_vStartPos, m_dwColor );
	m_Vertices[ 1 ]	= Vertex( m_vEndPos, m_dwColor );
}

//Line::Line( float i_fRadian, float i_fLength, DWORD i_dwColor )
//{
//	*this	= Line( D3DXVECTOR3(cos(i_fRadian), sin(i_fRadian), 0.0f), i_fLength, i_dwColor );
//}

void	Line::setMatrix( const D3DXMATRIX& i_Matrix )
{
	D3DXVECTOR4	vTransformed ;
	
	D3DXVec3Transform( &vTransformed, &m_vStartPos, &i_Matrix );
	m_Vertices[ 0 ].vPos.x	= vTransformed.x ;
	m_Vertices[ 0 ].vPos.y	= vTransformed.y ;
	m_Vertices[ 0 ].vPos.z	= vTransformed.z ;

	D3DXVec3Transform( &vTransformed, &m_vEndPos, &i_Matrix );
	m_Vertices[ 1 ].vPos.x	= vTransformed.x ;
	m_Vertices[ 1 ].vPos.y	= vTransformed.y ;
	m_Vertices[ 1 ].vPos.z	= vTransformed.z ;

	D3DXVECTOR3	v	= m_Vertices[ 1 ].vPos - m_Vertices[ 0 ].vPos ;
	m_fLength	= D3DXVec3Length( &v );
	D3DXVec3Normalize( &m_vDir, &v );
}

void	Line::setColor( DWORD i_dwColor )
{
	m_dwColor	= i_dwColor ;
	m_Vertices[ 0 ].dwColor	= m_dwColor ;
	m_Vertices[ 1 ].dwColor	= m_dwColor ;
}


void	Line::draw( const LPDIRECT3DDEVICE9 i_pd3dDevice ) const
{
	i_pd3dDevice->SetFVF( Vertex::getFVF() );
	i_pd3dDevice->SetTexture( 0, NULL );
	
	i_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	i_pd3dDevice->DrawPrimitiveUP( D3DPT_LINELIST, 1, m_Vertices, Vertex::getSize() );
	i_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
}


Line2::Line2()
	: m_vStartPos( D3DXVECTOR3(0.0f, 0.0f, 0.0f) ), m_vDir( D3DXVECTOR3(1.0f, 0.0f, 0.0f) ), m_vEndPos( m_vDir ), m_fLength( 1.0f ), m_fAngle( 0.0f ), m_dwColor(0xFFFFFFFF)
{
}

Line2::Line2( const D3DXVECTOR3& i_vStartPos, const D3DXVECTOR3& i_vDirection, float i_fLength, DWORD i_dwColor )
	: m_vStartPos( i_vStartPos ), m_fLength( i_fLength ), m_dwColor( i_dwColor )
{
	D3DXVec3Normalize( &m_vDir, &i_vDirection );
	m_vEndPos	= m_vStartPos + m_vDir * m_fLength ;
	
	float	fAngle = atan2( m_vDir.y, m_vDir.x );
	m_fAngle	= ( fAngle >= 0.0f ) ? fAngle : D3DX_PI * 2.0f + fAngle ;
	
	m_Vertices[ 0 ]	= Vertex( m_vStartPos, m_dwColor );
	m_Vertices[ 1 ]	= Vertex( m_vEndPos, m_dwColor );
}

Line2::Line2( const D3DXVECTOR3& i_vStartPos, const D3DXVECTOR3& i_vEndPos, DWORD i_dwColor )
	: m_vStartPos( i_vStartPos ), m_vEndPos( i_vEndPos ), m_dwColor( i_dwColor )
{
	D3DXVECTOR3	v	= m_vEndPos - m_vStartPos ;
	m_fLength	= D3DXVec3Length( &v );
	D3DXVec3Normalize( &m_vDir, &v );

	float	fAngle = atan2( v.y, v.x );
	m_fAngle	= ( fAngle >= 0.0f ) ? fAngle : D3DX_PI * 2.0f + fAngle ;
	
	m_Vertices[ 0 ]	= Vertex( m_vStartPos, m_dwColor );
	m_Vertices[ 1 ]	= Vertex( m_vEndPos, m_dwColor );
}

//Line2::Line2( float i_fRadian, float i_fLength, DWORD i_dwColor )
//{
//	*this	= Line2( D3DXVECTOR3(cos(i_fRadian), sin(i_fRadian), 0.0f), i_fLength, i_dwColor );
//}

void	Line2::setMatrix( const D3DXMATRIX& i_Matrix )
{
	D3DXVECTOR4	vTransformed ;
	
	D3DXVec3Transform( &vTransformed, &m_vStartPos, &i_Matrix );
	m_Vertices[ 0 ].vPos.x	= vTransformed.x ;
	m_Vertices[ 0 ].vPos.y	= vTransformed.y ;
	m_Vertices[ 0 ].vPos.z	= vTransformed.z ;

	D3DXVec3Transform( &vTransformed, &m_vEndPos, &i_Matrix );
	m_Vertices[ 1 ].vPos.x	= vTransformed.x ;
	m_Vertices[ 1 ].vPos.y	= vTransformed.y ;
	m_Vertices[ 1 ].vPos.z	= vTransformed.z ;

	D3DXVECTOR3	v	= m_Vertices[ 1 ].vPos - m_Vertices[ 0 ].vPos ;
	m_fLength	= D3DXVec3Length( &v );
	D3DXVec3Normalize( &m_vDir, &v );
}

void	Line2::setColor( DWORD i_dwColor )
{
	m_dwColor	= i_dwColor ;
	m_Vertices[ 0 ].dwColor	= m_dwColor ;
	m_Vertices[ 1 ].dwColor	= m_dwColor ;
}


void	Line2::draw( const LPDIRECT3DDEVICE9 i_pd3dDevice ) const
{
	i_pd3dDevice->SetFVF( Vertex::getFVF() );
	i_pd3dDevice->SetTexture( 0, NULL );
	
	i_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	i_pd3dDevice->DrawPrimitiveUP( D3DPT_LINELIST, 1, m_Vertices, Vertex::getSize() );
	i_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
}

}