#pragma once

#include "StateReturn.hh"

namespace	my
{
	//! Valeur de retour de la fonction Update d'une scène, contient toute les inforamtion utilisé par GameManager.
	struct 	SceneReturnValue
	{
		//! Etat de la valeur de retour.
		STATE_RETURN	value;
		//! Index de la nouvelle scène à afficher.
		int				newSceneIndex;
		//! La scène courante doit être remise à zéro.
		bool			doReset;
		//! La scène courante doit être initialisé.
		bool			doInitialize;

		SceneReturnValue(STATE_RETURN v = NOTHING, int si = -1, bool dr = false, bool di = false)
			: value(v), newSceneIndex(si), doReset(dr), doInitialize(di)
		{}
	};
}