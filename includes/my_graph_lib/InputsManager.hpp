#pragma once

namespace my
{
	template<typename T>
	class InputsManager
	{
	public:
		static bool IsPressedOne(T input) noexcept;

	private:
		InputsManager();
		~InputsManager();
	};
}

template<typename T>
bool my::InputsManager<T>::IsPressedOne(T input) noexcept
{
	return false;
}