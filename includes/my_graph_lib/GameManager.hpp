#pragma once

#include <stdexcept>
#include <list>
#include "WindowBuffer.hh"
#include "XMLNode.hpp"

namespace	my
{
  //! Class principal du jeux
  /*! Contient tous les composants pour créer la fenêtre.<br/>
    L'initialisation est généré à partir de fichier XML
   */
	class 	GameManager
	{
	public:
		virtual ~GameManager() noexcept {}

	  //! Lance la boucle principal du jeu
	  /*! Cette fonction tourne en boucle tant que la fenêtre de rendue est ouverte, ou qu'une exception est lieu
	   */
		void			Loop() throw (std::out_of_range, std::invalid_argument);

	protected:
	  //! Initialise la fenêtre de rendu
	  /*!
	    <b>Arguments:</b><br/>
	    windowRoot: Noeud XML contenant les informations de la fenêtre.
	    <br/><br>
	    Il est possible de surcharger cette fonction pour y ajouter de nouvelles valeurs d'initialisation.
	   */
		virtual void	InitializeWindow(XMLNode::XMLNodePtr windowRoot) throw (std::out_of_range, std::invalid_argument);

	  //! Initialise les différentes Scenes.
	  /*!
	    <b>Arguments</b><br/>
	    scenesRoot: Noeud XML contentantes les inforamtions sur les scènes.
	    <br/><br/>
	  */
		virtual void	InitializeScenes(XMLNode::XMLNodePtr scenesRoot) throw (std::out_of_range, std::invalid_argument) = 0;

	  //! Charge le fichier XML puis appel les différentes fonction d'initilisation
		virtual void	Initialize() throw (std::out_of_range, std::invalid_argument);

	  //! Appel la fonction Update de la scene courant et interprette sa valeur de retour.
	  /*!
	    <b>Exception</b><br/>
	    Lance une exception si le conteneur de scenes est vide
	  */
		virtual void	Update() throw (std::exception);

	  //! Efface le contenue de la fenêtre, puis dessine et affiche la scene courante.
		virtual void	Draw() noexcept;

	  //! La fenêtre de rendu.
	  WindowBuffer	m_window;

	private:
		static const std::string	MAIN_XML_PATH;

		static const std::string	SCREEN_NODE;
		static const std::string	SCREEN_VIDEOMODE_NODE;
		static const std::string	SCREEN_VIDEOMODE_WIDTH_NODE;
		static const std::string	SCREEN_VIDEOMODE_HEIGHT_NODE;
		static const std::string	SCREEN_VIDEOMODE_BPP_NODE;
		static const std::string	SCREEN_TITLE_NODE;

		static const std::string	SCENES_NODE;
	};
}
