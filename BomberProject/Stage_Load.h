////////////////////////////// //////////////////////////////
//	vWFNg	FBomberProject
//	t@C¼		FStage_Load.h
//	J­Â«		FMSVC++ 2008
//	ÅK^u		F4
//	SÒ			F²¡Á
//	àïÃÞ°ÀÆõl	F[hXe[W
//					¥
//	namespace wiz;
//		class LoadStage : public Stage ;
//
#pragma once

#include "StdAfx.h"
#include "Stage.h"
#include "Scene.h"
#include "Factory_Load.h"
namespace wiz{
/**************************/
/**************************************************************************
 class LoadStage : public Stage;
 pr: [hXe[WNX
****************************************************************************/
class LoadStage : public Stage{
public:	
/**************************************************************************
 LoadStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//foCX
	const Script::MLPHeader& Header,	//	: vC·éyÈÌwb_[f[^
	const Script::SCORELEVEL Level		//	: vC·éxíÊ
 );
 pr: RXgN^
 ßèl: Èµi¸sÍáOðthrowj
***************************************************************************/
	LoadStage(LPDIRECT3DDEVICE9 pD3DDevice,Command* Com,Stage* pStage = NULL);
/**************************************************************************
ResultStage();
 pr: fXgN^
 ßèl: Èµ
***************************************************************************/
	virtual ~LoadStage();
};
/**************************/

}
//end of namespace wiz.
