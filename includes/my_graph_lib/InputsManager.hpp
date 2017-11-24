#pragma once

#include "SFML/Graphics.hpp"
#include <map>

namespace my
{
	class InputsManager
	{
	public:
		typedef std::map<sf::Keyboard::Key, bool> InputsKeyMap;
		typedef std::map<sf::Mouse::Button, bool> InputsButtonMap;

		static void ClearInputs() noexcept;
		static bool IsKeyPressedOne(sf::Keyboard::Key input) noexcept;
		static bool IsKeyPressed(sf::Keyboard::Key input) noexcept;
		static bool IsKeyReleasedOne(sf::Keyboard::Key input) noexcept;
		static bool IsButtonPressedOne(sf::Mouse::Button input) noexcept;
		static bool IsButtonPressed(sf::Mouse::Button input) noexcept;
		static bool IsButtonReleasedOne(sf::Mouse::Button input) noexcept;

	private:
		static InputsKeyMap KEY_MAP;
		static InputsKeyMap LAST_KEY_MAP;
		static InputsButtonMap BUTTON_MAP;
		static InputsButtonMap LAST_BUTTON_MAP;

		InputsManager();
		~InputsManager();

		static void AddInputs(sf::Keyboard::Key input);
		static void AddInputs(sf::Mouse::Button input);
	};
}