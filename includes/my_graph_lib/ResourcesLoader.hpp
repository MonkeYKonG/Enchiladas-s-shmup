#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <stdexcept>

namespace	my
{
  //! Class permettant de charger et stoker les ressources du jeu en utilisant un identifiant de type string
  /*! Les resources ne sont chargés que lorsqu'elle sont appelés pour la première fois.
   */
	class	ResourcesLoader
	{
	public:
	  //! Retourne une référence sur la texture demandé.
	  /*!
	    <b>Arguments</b><br/>
	    id: Chaine de caractère correspondant à l'identifiant de la texture.
	    <br/><br/>
	    <b>Valeur de retour</b><br/>
	    Retourne une référence constante sur une texture.
	    <br/><br/>
	    <b>Exception</b><br/>
	    std::invalid_argument: La texture demandé n'existe pas.
	  */
		static const sf::Texture 	&GetTexture(const std::string &id) throw (std::invalid_argument);

	  //! Décharge une texture.
	  /*!
	    <b>Arguments</b><br/>
	    id: Chaine de caractère corrsespondant à l'identifiant de la texture.
	  */
		static void					UnloadTexture(const std::string &id);

	  //! Retourne une référence sur la police demandé.
	  /*!
	    <b>Arguments</b><br/>
	    id: Chaine de caractère correspondant à l'identifiant de la police.
	    <br/><br/>
	    <b>Valeur de retour</b><br/>
	    Retourne une référence constante sur une police.
	    <br/><br/>
	    <b>Exception</b><br/>
	    std::invadlid_argument: La police demandé n'existe pas.
	   */
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
