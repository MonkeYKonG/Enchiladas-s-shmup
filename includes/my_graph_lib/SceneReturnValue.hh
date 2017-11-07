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

		SceneReturnValue(STATE_RETURN v = NOTHING, int si = -1, bool dr = false, bool di = false)
			: value(v), newSceneIndex(si), doReset(dr), doInitialize(di)
		{}
	};
}