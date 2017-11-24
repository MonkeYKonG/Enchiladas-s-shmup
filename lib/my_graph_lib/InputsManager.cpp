#include "InputsManager.hpp"

my::InputsManager::InputsKeyMap my::InputsManager::KEY_MAP = my::InputsManager::InputsKeyMap();
my::InputsManager::InputsKeyMap my::InputsManager::LAST_KEY_MAP = my::InputsManager::InputsKeyMap();
my::InputsManager::InputsButtonMap my::InputsManager::BUTTON_MAP = my::InputsManager::InputsButtonMap();
my::InputsManager::InputsButtonMap my::InputsManager::LAST_BUTTON_MAP = my::InputsManager::InputsButtonMap();

void my::InputsManager::AddInputs(sf::Keyboard::Key input)
{
	KEY_MAP[input] = sf::Keyboard::isKeyPressed(input);
	if (LAST_KEY_MAP.find(input) == LAST_KEY_MAP.end())
		LAST_KEY_MAP[input] = false;
}

void my::InputsManager::AddInputs(sf::Mouse::Button input)
{
	BUTTON_MAP[input] = sf::Mouse::isButtonPressed(input);
	if (LAST_BUTTON_MAP.find(input) == LAST_BUTTON_MAP.end())
		LAST_BUTTON_MAP[input] = false;
}

void my::InputsManager::ClearInputs() noexcept
{
	for (auto itKey = LAST_KEY_MAP.begin(); itKey != LAST_KEY_MAP.end(); ++itKey)
	{
		if (KEY_MAP.find(itKey->first) != KEY_MAP.end())
			itKey->second = KEY_MAP[itKey->first];
		else
			itKey->second = false;
	}
	KEY_MAP.clear();
	for (auto itButton = LAST_BUTTON_MAP.begin(); itButton != LAST_BUTTON_MAP.end(); ++itButton)
	{
		if (BUTTON_MAP.find(itButton->first) != BUTTON_MAP.end())
			itButton->second = BUTTON_MAP[itButton->first];
		else
			itButton->second = false;
	}
	BUTTON_MAP.clear();
}

bool my::InputsManager::IsKeyPressedOne(sf::Keyboard::Key input) noexcept
{
	if (KEY_MAP.find(input) == KEY_MAP.end())
		AddInputs(input);
	return (KEY_MAP.at(input) && !LAST_KEY_MAP.at(input));
}

bool my::InputsManager::IsKeyPressed(sf::Keyboard::Key input) noexcept
{
	if (KEY_MAP.find(input) == KEY_MAP.end())
		AddInputs(input);
	return (KEY_MAP.at(input));
}

bool my::InputsManager::IsKeyReleasedOne(sf::Keyboard::Key input) noexcept
{
	if (KEY_MAP.find(input) == KEY_MAP.end())
		AddInputs(input);
	return (!KEY_MAP[input] && LAST_KEY_MAP[input]);
}

bool my::InputsManager::IsButtonPressedOne(sf::Mouse::Button input) noexcept
{
	if (BUTTON_MAP.find(input) == BUTTON_MAP.end())
		AddInputs(input);
	return (BUTTON_MAP.at(input) && !LAST_BUTTON_MAP.at(input));
}

bool my::InputsManager::IsButtonPressed(sf::Mouse::Button input) noexcept
{
	if (BUTTON_MAP.find(input) == BUTTON_MAP.end())
		AddInputs(input);
	return (BUTTON_MAP.at(input));
}

bool my::InputsManager::IsButtonReleasedOne(sf::Mouse::Button input) noexcept
{
	if (BUTTON_MAP.find(input) == BUTTON_MAP.end())
		AddInputs(input);
	return (!BUTTON_MAP.at(input) && LAST_BUTTON_MAP.at(input));
}