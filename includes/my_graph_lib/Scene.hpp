#pragma once

#include <stdexcept>
#include <memory>
#include <SFML/Graphics.hpp>
#include "SceneReturnValue.hh"
#include "XMLNode.hpp"

namespace	my
{
  //! Contient des entités dessinable, les mets à jour et peut les dessiner.
	class 	Scene : public sf::Drawable, public sf::Transformable
	{
	public:
		typedef std::shared_ptr<Scene> ScenePtr;

		virtual ~Scene() noexcept {}

		//! Vide la liste des évenements puis récupère les nouveaux évenements de la fenêtre
		/*!
		<b>Arguments</b><br/>
		window: La fenêtre de rendu actuellement utilisé
		*/
		void PollEvents(sf::RenderWindow & window) noexcept;

	  //! Met à jour les différentes entités
	  /*!
	    <b>Arguments</b><br/>
	    window: La fenêtre de rendu actuellement utilisé.
	  */
		virtual const SceneReturnValue Update(const sf::Vector2i & mousePos) throw (std::exception) = 0;

	  //! Initialise les entités.
	  /*!
	    <b>Arguments</b><br/>
	    sceneRoot: Noeud XML contenant les informations sur la scène
	  */
		virtual void Initialize(XMLNode::XMLNodePtr sceneRoot) throw (std::out_of_range, std::invalid_argument) = 0;

	  //! Replace les entités à leurs valeur de base
		virtual void Reset() throw(std::out_of_range, std::invalid_argument) = 0;

	protected:
	  //! Dessine les entités
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const = 0;

	  //! Tableau d'évenements.
		std::vector<sf::Event>	m_events;
	};
}
