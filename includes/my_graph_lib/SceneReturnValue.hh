#pragma once

#include "StateReturn.hh"

namespace	my
{
	struct 	SceneReturnValue
	{
		STATE_RETURN	value;
		int				newSceneIndex;
		bool			doReset;
		bool			doInitialize;
	};
}