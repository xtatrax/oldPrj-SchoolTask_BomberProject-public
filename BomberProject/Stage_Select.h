////////////////////////////// //////////////////////////////
//	vWFNg	FBomberProject
//	t@C¼		FStage_Select.h
//	J­Â«		FMSVC++ 2008
//	ÅK^u		F4
//	SÒ			F²¡Á
//	àïÃÞ°ÀÆõl	F^CgXe[W
//					¥
//	namespace wiz;
//		class StageSelect : public Stage ;
//
#pragma once

#include "StdAfx.h"
#include "Stage.h"
#include "Scene.h"
#include "Factory_Title.h"

namespace wiz{
/**************************/
/**************************************************************************
 class StageSelect : public Stage;
 pr: Q[Xe[WNX
****************************************************************************/
class StageSelect : public Stage{
public:	
/**************************************************************************
 StageSelect(
	LPDIRECT3DDEVICE9 pD3DDevice,		//foCX
	const Script::MLPHeader& Header,	//	: vC·éyÈÌwb_[f[^
	const Script::SCORELEVEL Level		//	: vC·éxíÊ
 );
 pr: RXgN^
 ßèl: Èµi¸sÍáOðthrowj
***************************************************************************/
	StageSelect(LPDIRECT3DDEVICE9 pD3DDevice,Stage* pStage = NULL);
/**************************************************************************
StageSelect();
 pr: fXgN^
 ßèl: Èµ
***************************************************************************/
	virtual ~StageSelect();
};
/**************************/

}
//end of namespace wiz.
