#pragma once

#include <map>
#include <SFML/Graphics.hpp>

namespace	my
{
	class	ResourcesLoader
	{
	public:
		static const sf::Texture 	&GetTexture(const std::string &id);
		static void					UnloadTexture(const std::string &id);

	private:
		ResourcesLoader() {}
		~ResourcesLoader() {}

		static std::map<std::string, sf::Texture>	m_textures;
	};
}