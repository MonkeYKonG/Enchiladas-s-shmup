#pragma once

#include "memory"

namespace	my
{
	class	IUpdatableObject
	{
	public:
		typedef std::shared_ptr<IUpdatableObject> IUpdatableObjectPtr;

		virtual void Update() = 0;
	};
}