////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FDefineValue.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�O���[�o���ȃf�B�t�@�C���l�Q
//					��
//
#ifndef	__Define_Value__
#define	__Define_Value__
//////////
// �}�N���֐�

#define TL_SQUARE(n)							((n)*(n))

//
//////////


//////////
//	: �R���p�C�����O�t���O

#define CF_SINGLETHREAD			/* �V���O���X���b�h���[�h     */
//#define CF_LOADINGANIMATION		/* ���[�h��ʂŃA�j���[�V���� */
#if defined(DEBUG) || defined(_DEBUG)
	#define ON_DEBUGGINGPROCESS		/* �f�o�b�N���[�h             */
	#define DEBUG_STRINGS_ON			/* �f�o�b�O�p�������L���� */
	#define ___MLP_DEBUG_TIMEDRAW_ 
#else
	#define CF_FULLSCREEN				/* �t���X�N���[�����[�h       */
#endif
#define DEBUG_KEYBORD_ON			/* �f�o�b�O�p�L�[�{�[�h�����L���� */

//	: �f�t�@�C���萔
#define MAP_PARTS_HEIGHT		(    1.0f)	/*  */
#define MAP_PARTS_WIDTH			(    1.0f)	/*  */
#define BASE_CLIENT_HEIGHT		(  600.0f)	/* ��ɂȂ�`��̈�̍��� */
#define BASE_CLIENT_WIDTH		( 1024.0f)	/* ��ɂȂ�`��̈�̕�   */
#define STANDARD_WINDOW_HEIGHT  (  600.0f)	/* �E�C���h�E���[�h�̍���   */
#define STANDARD_WINDOW_WIDTH   ( 1024.0f)	/* �E�C���h�E���[�h�̕�     */

#define DEFAULT_WINDOW_TITLE		( L"�E�C���h�E�^�C�g��" )
#define DEFAULT_WINDOW_CLASS_NAME	( L"�E�C���h�E�N���X�l�[��" )

//	�L�[�{�[�h��`
#define MYVK_GAMEPAD_A				( 'X' )
#define MYVK_GAMEPAD_B				( 'C' )
#define MYVK_GAMEPAD_X				( 'S' )
#define MYVK_GAMEPAD_Y				( 'D' )

#define MYVK_GAMEPAD_BACK			( 'W' )
#define MYVK_GAMEPAD_START			( 'E' )
#define MYVK_GAMEPAD_LB				( 'A' )
#define MYVK_GAMEPAD_RB				( 'F' )

#define MYVK_GAMEPAD_POV_UP			( VK_UP    )
#define MYVK_GAMEPAD_POV_DOWN 		( VK_DOWN  )
#define MYVK_GAMEPAD_POV_RIGHT		( VK_RIGHT )
#define MYVK_GAMEPAD_POV_LEFT		( VK_LEFT  )

#define MYVK_GAMEPAD_STICK_UP		( 'I' )
#define MYVK_GAMEPAD_STICK_DOWN 	( 'K' )
#define MYVK_GAMEPAD_STICK_RIGHT	( 'L' )
#define MYVK_GAMEPAD_STICK_LEFT		( 'J' )


#define MYVK_DEBUG_STOP_UPDATE		( VK_F12 )
#define MYVK_DEBUG_SLOW_UPDATE		( VK_F11 )
#define MYVK_DEBUG_OUTPUT_DBGSTR	( VK_F9  )
#define MYVK_DEBUG_OUTPUT_MEMORY	( VK_F8  )

//
//////////

//////////
//	�Q�[���p�[�c
#define GP_CREATE_NONE		(   0 )
#define GP_CREATE_TESTTIP	(   1 )
#define GP_CREATE_GROUND	(   2 )
#define GP_CREATE_ENEMY		(   3 )
#define GP_CREATE_BIRD		(   4 )
#define GP_CREATE_ARROW		(   5 )
#define GP_CREATE_CLEAR		(   6 )
//#define  GP_CREATE_NONE (0)
//


//
namespace wiz{
	enum{
		GM_WITHOUT				,
		GM_OPENSTAGE_TITLE		,
		GM_OPENSTAGE_PLAY		,
		GM_OPENSTAGE_RESULT		,
		GM_OPENSTAGE_RANKING	,
		GM_OPENSTAGE_OPTION		,
		GM_OPENSTAGE_GAMECLEAR	,
		GM_OPENSTAGE_GAMEOVER	,
		GM_EXIT					,

		GM_OPENDEBUGSTAGE_DEBUGMENU      ,
		GM_OPENDEBUGSTAGE_TATEAWORKSPACE ,
		GM_OPENDEBUGSTAGE_TOJIWORKSPACE  ,
		GM_OPENDEBUGSTAGE_HSWORKSPACE    ,
		GM_OPENDEBUGSTAGE_STAGECREATE    ,

		//////////
		//	: 
		GM_PLAYOPENING_END	,

	};

	enum OBJID{
		OBJID_UNK					,

		OBJID_SYS_CAMERA			,
		OBJID_SYS_LIGHT				,
		OBJID_SYS_GUIDELINE			,
		OBJID_SYS_SOUND				,
		OBJID_SYS_ENEMYMANAGER		,
		OBJID_SYS_CLEARAREA			,

		OBJID_UI_SPRITE				,
		OBJID_UI_SPRITEBUTTON		,
		OBJID_UI_LIFE				,
		OBJID_UI_GAUGE				,
		OBJID_UI_SCORE				,
		OBJID_UI_TIME				,

		OBJID_2D_WALL				,

		OBJID_3D_POLYGON			,
		OBJID_3D_BOX				,
		OBJID_3D_BOX_PARALLEL		,
		OBJID_3D_SPHERE				,
		OBJID_3D_CYLINDER			,

		OBJID_3D_MULTI_POLYGON		,
		OBJID_3D_MULTI_BOX			,
		OBJID_3D_MULTI_BOX_PARALLEL	,
		OBJID_3D_MULTI_SPHERE		,
		OBJID_3D_MULTI_CYLINDER		,
		OBJID_3D_MULTI_TAURUS		,

		OBJID_3D_PLAYER				,
		OBJID_3D_EFFECT				,
	} ;

}
//
//////////

//////////
//	: �O���[�o���ȕϐ�

extern D3DXVECTOR3 g_vZero ;	//	: �[���x�N�g��
extern D3DXVECTOR3 g_vOne  ;	//	: ��x�N�g��
extern D3DXVECTOR3 g_vMax  ;	//	: �ō��x�N�g��
extern D3DXVECTOR3 g_vMin  ;	//	: �Œ�x�N�g��

extern wstring g_sDefaultTexturePath ;	//	: �e�N�X�`���̒u����

//	
//////////
 
#endif