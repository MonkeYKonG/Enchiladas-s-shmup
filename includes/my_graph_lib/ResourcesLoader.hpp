#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <stdexcept>

namespace	my
{
	class	ResourcesLoader
	{
	public:
		static const sf::Texture 	&GetTexture(const std::string &id) throw (std::invalid_argument);
		static void					UnloadTexture(const std::string &id);
		static const sf::Font		&GetFont(const std::string &id) throw (std::invalid_argument);

	private:
		static const std::string	RESOURCES_PATH;
		static const std::string	TEXTURES_PATH;
		static const std::string	FONTS_PATH;

		static std::map<std::string, sf::Texture>	m_textures;
		static std::map<std::string, sf::Font>		m_fonts;

		ResourcesLoader() {}
		~ResourcesLoader() {}
	};
}