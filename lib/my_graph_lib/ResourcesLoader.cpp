#include "ResourcesLoader.hpp"

namespace	my
{
	const std::string ResourcesLoader::RESOURCES_PATH = "resources/";
	const std::string ResourcesLoader::TEXTURES_PATH = "textures/";
	const std::string ResourcesLoader::FONTS_PATH = "fonts/";
	std::map<std::string, sf::Texture> ResourcesLoader::m_textures = std::map<std::string, sf::Texture>();
	std::map<std::string, sf::Font> ResourcesLoader::m_fonts = std::map<std::string, sf::Font>();

	const sf::Texture 	&ResourcesLoader::GetTexture(const std::string & id) throw (std::invalid_argument)
	{
		sf::Image img;

		if (m_textures.find(id) != m_textures.end())
			return (m_textures.at(id));
		if (!img.loadFromFile(RESOURCES_PATH + TEXTURES_PATH + id))
			throw (std::invalid_argument("loading texture file not found: " + RESOURCES_PATH + TEXTURES_PATH + id));
		m_textures[id] = sf::Texture();
		m_textures.at(id).loadFromImage(img);
		return (m_textures.at(id));
	}

	void				ResourcesLoader::UnloadTexture(const std::string & id)
	{

	}

	const sf::Font 		&ResourcesLoader::GetFont(const std::string & id) throw (std::invalid_argument)
	{
		if (m_fonts.find(id) != m_fonts.end())
			return (m_fonts.at(id));
		m_fonts[id] = sf::Font();
		if (!m_fonts.at(id).loadFromFile(RESOURCES_PATH + FONTS_PATH + id + ".ttf"))
			throw (std::invalid_argument("loading font file not found: " + RESOURCES_PATH + FONTS_PATH + id + ".ttf"));
		return (m_fonts.at(id));
	}
}