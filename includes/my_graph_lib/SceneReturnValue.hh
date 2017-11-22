#pragma once

#include "StateReturn.hh"

namespace	my
{
	//! Valeur de retour de la fonction Update d'une sc�ne, contient toute les inforamtion utilis� par GameManager.
	struct 	SceneReturnValue
	{
		//! Etat de la valeur de retour.
		STATE_RETURN	value;
		//! Index de la nouvelle sc�ne � afficher.
		int				newSceneIndex;
		//! La sc�ne courante doit �tre remise � z�ro.
		bool			doReset;
		//! La sc�ne courante doit �tre initialis�.
		bool			doInitialize;

		SceneReturnValue(STATE_RETURN v = NOTHING, int si = -1, bool dr = false, bool di = false)
			: value(v), newSceneIndex(si), doReset(dr), doInitialize(di)
		{}
	};
}