////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Magnetic.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Magnetic ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_PlaneCircle.h"




namespace wiz{
namespace bomberobject{



class MagnetFieldCircle{
	struct Vertex
	{
		D3DXVECTOR3 vPos ;
		DWORD dwColor ;

		Vertex(): vPos( 0.0f, 0.0f, 0.0f ), dwColor( 0xFFFFFFFF ){ }
		Vertex( const D3DXVECTOR3& i_vPos, DWORD i_dwColor ): vPos( i_vPos ), dwColor( i_dwColor ){	}
		static size_t getSize()	{	return sizeof( Vertex );	}
		static DWORD getFVF(){return D3DFVF_XYZ | D3DFVF_DIFFUSE ;}
	};
	DWORD						m_dwVertexQty	;
	LPDIRECT3DVERTEXBUFFER9		m_pVertexBuffer	;	//�o�b�t�@
	D3DXMATRIX					m_mMatrix		;
public:
	MagnetFieldCircle(LPDIRECT3DDEVICE9 pD3DDevice,DWORD pVertexQty);
	void Draw(DrawPacket& i_DrawPacket);
	void setMatrix(D3DXMATRIX& i_mMatrix){
		m_mMatrix = i_mMatrix;
	}
	void setPole(POLE pl){
		Vertex* m_pVertex;
		m_pVertexBuffer->Lock( 0, 0, (void**)&m_pVertex ,0 );	//	: ���_�f�[�^�̃A�h���X���擾����ƂƂ��ɁA�f�[�^�ւ̃A�N�Z�X���J�n����	


		if( pl == POLE_S ){
			m_pVertex[ 0 ].dwColor = 0x3F0000FF;
			for ( DWORD i = 1 ; i <= m_dwVertexQty  ; i++ ){
				m_pVertex[ i ].dwColor = 0x3F0000FF;
			}
		}else{
			m_pVertex[ 0 ].dwColor = 0x3FFF0000;
			for ( DWORD i = 1 ; i <= m_dwVertexQty  ; i++ ){
				m_pVertex[ i ].dwColor = 0x3FFF0000;
			}
		
		}
		m_pVertexBuffer->Unlock();
	}

};

//3D�ϊ��p
//**************************************************************************//
// class MagneticumObject3D : public PrimitiveCylinder ;
//
// �S����  : �g�n ��m
// �ҏW    : ���� �O(�啝����)
//         : �{�� ���V
// �p�r    : ���E�I�u�W�F�N�g
//         : �R�C���I�u�W�F�N�g�⃆�[�U�[�ݒu���E�ɂ����p���Ă��܂��
//**************************************************************************//
extern class PlayerCoil ;
class MagneticumObject3D : public PrimitiveCylinder{
//////////
//	: ����J
private:
	//	: ���Ƀt���O
	//	: S�� = POLE_S
	//	: N�� = POLE_N
	POLE  m_bMagnetPole		;
	float m_fMagneticum		;
	float m_fEffectSizeRate	;
//////////
//	: �v���e�N�g
protected:
	Camera*				m_pCamera			;
	PlayerCoil*			m_pCoil				;
	MagnetFieldCircle	m_MagneticField		;
	D3DXVECTOR3			m_vPos ;

	struct Magnet3DItem{
		//	: ���W
		D3DXVECTOR3		m_vPos ;
		POLE			m_bMagnetPole ;
		float			m_fMapKey	;
		bool			m_bHidden	;
		virtual ~Magnet3DItem(){}
	};


	//map<�I�u�W�F�N�g�̃|�W�V����, Magnet3DItem>
	typedef multimap<float, Magnet3DItem*>	ALLCONTAINER		;
	typedef list<Magnet3DItem*>				TARGETCONTAINER		;
	ALLCONTAINER		m_ItemMap_All		;
	TARGETCONTAINER		m_ItemMap_Target	;

protected:
	void setPoleS(){ m_bMagnetPole = POLE_S  ; setColorS() ; }
	void setPoleN(){ m_bMagnetPole = POLE_N	 ; setColorN() ; }
	void setPole( POLE bPool ){
		     if( bPool == POLE_N ) setPoleN() ;
		else if( bPool == POLE_S ) setPoleS() ;
	}
	
	void setColorS(){
		m_Material.Ambient.a = 1.0f ; m_Material.Ambient.b = 1.0f ; m_Material.Ambient.g = 0.0f ; m_Material.Ambient.r = 0.0f ;
		m_Material.Diffuse.a = 1.0f ; m_Material.Diffuse.b = 1.0f ; m_Material.Diffuse.g = 1.0f ; m_Material.Diffuse.r = 1.0f ; 
	}
	void setColorN(){
		m_Material.Ambient.a = 1.0f ; m_Material.Ambient.b = 0.0f ; m_Material.Ambient.g = 0.0f ; m_Material.Ambient.r = 1.0f ;
		m_Material.Diffuse.a = 1.0f ; m_Material.Diffuse.b = 1.0f ; m_Material.Diffuse.g = 1.0f ; m_Material.Diffuse.r = 1.0f ;	
	}
	void setColorSuper(){
		m_Material.Ambient.a = 1.0f ; m_Material.Ambient.b = 0.0f ; m_Material.Ambient.g = 1.0f ; m_Material.Ambient.r = 1.0f ;
		m_Material.Diffuse.a = 1.0f ; m_Material.Diffuse.b = 1.0f ; m_Material.Diffuse.g = 1.0f ; m_Material.Diffuse.r = 1.0f ;			
	}

/////////////////// ////////////////////
//// �֐���     �Fvoid ChangePole()
//// �J�e�S��   �F����J�A�N�Z�b�T
//// �p�r       �F���ɂ𔽓]������
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F ���Ƀt���O�ƃJ���[��ύX����
////            �F
////

	bool ChangePole(){
		if( m_bMagnetPole == POLE_S )	{ setPoleN() ; }
		else							{ setPoleS() ; }
		return true ;
	}

//////////
//	: ���J
public:
	/////////////////// ////////////////////
	//// �p�r       �FMagneticumObject3D(
	///										LPDIRECT3DDEVICE9 pD3DDevice,
	///										LPDIRECT3DTEXTURE9 pTexture,
	///										wiz::OBJID id = OBJID_3D_MAGNET
	///										) ;
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	////			  :   LPDIRECT3DTEXTURE9 pTexture,  //�e�N�X�`��	
	////              :   wiz::OBJID id = OBJID_3D_MAGNET //ID
	//// �ߒl       �F����
	//// �S����     �F�g�n ��m
	//// ���l       �F
	////	
	MagneticumObject3D(
		LPDIRECT3DDEVICE9 pD3DDevice,
		wiz::OBJID id 
		) ;

	/////////////////// ////////////////////
	//// �p�r       �F	MagneticumObject3D(
	////									LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
	////									float Radius1,float Radius2,float Lenght,
	////									D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,D3DCOLORVALUE& Diffuse,
	////									D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
	////									wiz::OBJID id = OBJID_3D_MAGNET)
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �FPlayer�p�̃R���X�g���N�^
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	////			  :   LPDIRECT3DTEXTURE9 pTexture,  //�e�N�X�`��	
	////		      :   float Radius1						//�~�̒��a1
	////		      :   float Radius2						//�~�̒��a2
	////			  :   float Lenght						//����
	////		      :   D3DXVECTOR3 &vRot				//��]�p
	////		      :   D3DXVECTOR3 &vPos				//�ʒu
	////              :   D3DCOLORVALUE& Diffuse,		//�f�B�t���[�Y�F
	////              :   D3DCOLORVALUE& Specular,		//�X�y�L�����F
	////              :   D3DCOLORVALUE& Ambient,		//�A���r�G���g�F
	////              :   wiz::OBJID id = OBJID_3D_MAGNET //ID
	//// �ߒl       �F����
	//// �S����     �F�{�����V
	//// ���l       �F
	////	
	MagneticumObject3D(
		LPDIRECT3DDEVICE9 pD3DDevice,
		LPDIRECT3DTEXTURE9 pTexture,
		float Radius1,
		float Radius2,
		float Lenght,
		D3DXVECTOR3 &vRot,
		D3DXVECTOR3 &vPos,
		D3DCOLORVALUE& Diffuse,
		D3DCOLORVALUE& Specular,
		D3DCOLORVALUE& Ambient,
		wiz::OBJID id 
		) ;


	/////////////////// ////////////////////
	//// �p�r       �F  ~MagneticumObject3D()
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �FPlayer�p�̃R���X�g���N�^
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F
	////	
	~MagneticumObject3D();

	/////////////////// ////////////////////
	//// �p�r       �Fvoid Draw( DrawPacket& i_DrawPacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
	//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
	////			 �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////             �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
	////             �F  �� Tempus2*            i_DrawPacket.pTime	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////             �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F�g�n ��m
	//// ���l       �F
	////
	void Draw( DrawPacket& i_DrawPacket );

	/////////////////// ////////////////////
	//// �p�r       �Fvoid Update( UpdatePacket& i_UpdatePacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g���X�V
	//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
	////			  �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////              �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////              �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
	////              �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
	////              �F  ��       Command            pCommand        // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F�g�n ��m
	//// ���l       �F
	void Update( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// �p�r       �Fvoid AddMagnetic( DrawPacket& i_DrawPacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�}�O�l�b�g�̒ǉ�
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	////		    �F  D3DXVECTOR3 &vScale				//�g��k��
	////		    �F  D3DXVECTOR3 &vRot				//��]�p
	////		    �F  D3DXVECTOR3 &vPos				//�ʒu
	////            �F  D3DCOLORVALUE& Diffuse,			//�f�B�t���[�Y�F
	////            �F  D3DCOLORVALUE& Specular,		//�X�y�L�����F
	////            �F  D3DCOLORVALUE& Ambient,			//�A���r�G���g�F
	//// �ߒl       �F����
	//// �S����     �F�g�n ��m
	//// ���l       �F
	////
	void AddMagnetic(
		D3DXVECTOR3 &vScale,
		D3DXVECTOR3 &vRot,
		D3DXVECTOR3 &vPos,
		POLE		vPole,
		D3DCOLORVALUE& Diffuse,
		D3DCOLORVALUE& Speular,
		D3DCOLORVALUE& Ambient
		) ;
	
	/////////////////// ////////////////////
	//// �p�r       �Fbool CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos ) const
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�����𔻒�
	//// ����       �FD3DXVECTOR3& i_vMagneticFieldPos //���E�̈ʒu 
	////�@�@�@�@�@�@�FD3DXVECTOR3& i_vCoilPos          //�R�C���̈ʒu
	////�@�@�@�@�@�@�Ffloat        i_iBorder           //���肷��l
	//// �ߒl       �Ftrue , false
	//// �S����     �F�{�����V
	//// ���l       �F
	//bool CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos, float i_iBorder ) const;
	
	void setDrawTarget();

	/////////////////// ////////////////////
	//// �֐���     �FD3DXVECTOR3 getPos() const
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F���S���W���l��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F���� �O
	//// ���l       �F
	////            �F
	D3DXVECTOR3 getPos() const {
		return m_vPos			;	
	}	;

	/////////////////// ////////////////////
	//// �֐���     �Fvoid ChangePole()
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F���ɂ��l��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F�g�n��m
	//// ���l       �F S�� = POLE_S = false
	////			 �F N�� = POLE_N = true
	POLE  getMagnetPole() const { return m_bMagnetPole	;	}	;

	float getMagneticum() const { return m_fMagneticum*m_fMagneticum  ;	}	;

	void HitTest();

	/////////////////// ////////////////////
	//// �֐���     �Fmultimap<float, Magnet3DItem*> getMapTarget() const
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �Fm_ItemMap_Target���l��
	//// ����       �F�Ȃ�
	//// �ߒl       �Fm_ItemMap_Target
	//// �S��       �F�{�����V
	//// ���l       �F
	////            �F
	//multimap<float, Magnet3DItem*> getMapTarget() const{
	//	return m_ItemMap_Target;
	//}

};



/**************************************************************************
 class Factory_Magnetic;
 �p�r: ���C���H��N���X
****************************************************************************/
class Factory_Magnetic{
public:
/**************************************************************************
 Factory_Magnetic(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	//Factory_Magnetic(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,TextureManager& TexMgr);
	Factory_Magnetic( FactoryPacket* fpac ) ;
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
~Factory_Magnetic() ;
};
}
//end of namespace bomberobject.
}
//end of namespace wiz.
