#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <memory>

namespace	my
{
	//! Class permetant à un objet de s'annimé.
	/*!
	Cette class fournis aux objects qui en hérite des fonctions et attributs pour s'annimé.
	<br/><br/>
	La fonction UpdateAnimation doit être appelé à chaque tours de boucle.<br/>
	L'objet ne s'annime que lorsque l'attribut m_onAnimation est true.<br/>
	Un animated object possède un tableau d'animation indexé par des chaines de caractères.
	*/
  class		AnimatedObject
  {
	public:
		//! Conteneur d'animation.
		struct Animation
		{
			typedef std::vector<sf::IntRect>	AnimationRects;

			Animation() : framerateMax(0), loop(false) {}

			//! Tableau de tuiles.
			AnimationRects rects;
			//! Nombre de frame séparant deux tuiles.
			unsigned framerateMax;
			//! Index de l'animation.
			std::string key;
			//! L'animation doit se répéter.
			bool loop;
		};

		typedef std::shared_ptr<AnimatedObject> AnimatedObjectPtr;
		typedef std::vector<Animation> Animations;

		AnimatedObject() noexcept;
		virtual ~AnimatedObject() noexcept {}

		//! Détermine si l'objet est en cours d'animation
		bool                            IsOnAnimation() const noexcept;
		//! Détermine si l'index d'animation passé en argument existe.
		/*!
		<b>Arguments</b><br/>
		id: L'index de l'animation recherché.
		<br/><br/>
		<b>Valeur de retour</b><br/>
		retourne true si l'animation existe, false sinon.
		*/
		bool							AnimationExist(const std::string & key) const noexcept;
		//! Retourne la tuile courante.
		const sf::IntRect&			    GetCurentRect() const throw (std::out_of_range);
		//! Retourne le conteneur d'aniation courant.
		/*!
		<b>Exception</b><br/>
		std::out_of_range: m_animIndex ou m_animTileIndex est invalide.
		*/
		const Animation&                GetCurentAnimation() const throw (std::out_of_range);
		//! Retourne le tableau d'animation de l'objet.
		const Animations&				GetAnimations() const noexcept;
		//! Retourne le nombre de frame écoulé depuis le dernier chagement de tuile.
		unsigned						GetCurFramerate() const noexcept;

		//! Demande à l'objet de s'annimé ou de s'arreter.
		void                            SetOnAnimation(bool onAnimation) noexcept;
		//! Change le tableau d'animation par celui passer ena argument.
		void			                SetAnimations(const Animations & animations) noexcept;
		//! Ajoute l'animation passé en argument au tableau d'animation.
		void							AddAnimation(const Animation & animation) noexcept;
		//! Change l'index de l'animation courante et celui de sa tuile.
		/*!
		<b>Arguments</b><br/>
		index: Nouvel index d'animation.<br/>
		tileIndex: Nouvel index de la tuile.
		<br/><br/>
		<b>Exception</b><br/>
		std::out_of_range: Un des indexs passé en argument est invalide.
		*/
		void			                SetAnimIndex(int index, int tileIndex = 0) throw (std::out_of_range);
		//! Change l'index de l'animation courante et celui de sa tuile.
		/*!
		<b>Arguments</b><br/>
		index: Nouvel index d'animation.<br/>
		tileIndex: Nouvel index de la tuile.
		<br/><br/>
		<b>Exception</b><br/>
		std::out_of_range: Un des indexs passé en argument est invalide.
		*/
		void							SetAnimIndex(const std::string & key, int tileIndex = 0) throw (std::out_of_range);
		//! Change l'index de la tuile courante
		/*!
		<b>Arguments</b><br/>
		tileIndex: Nouvel index de la tuile.
		<br/><br/>
		<b>Exception</b><br/>
		std::out_of_range: L'index passé en argument est invalide.
		*/
		void			                SetAnimTileIndex(int tileIndex) throw (std::out_of_range);
		//! Change le nombre de frame passé depuis le dernier changement de tuile par celui passé en argument.
		void							SetCurFrameRate(unsigned curFramerate) noexcept;

	protected:
		//! Index de l'animation par défaut.
		static const std::string	DEFAULT_ANIM_NAME;

		//! Met a jour les compteurs de frame et met a jour la tuile courante.
		/*!
		<b>Exception</b><br/>
		std::out_of_range: Un dex index de l'objet est invalide.
		*/
		virtual void		    UpdateAnimation() throw (std::out_of_range);

		//! Autoriser l'objet a s'animé.
		bool		m_onAnimation;
		//! Tableau d'animation.
		Animations	m_animations;
		//! Index de l'animation courante.
		int			m_animIndex;
		//! Index de la tuile courate.
		int			m_animTileIndex;
		//! Nombre de frame écoulé depuis le dernier changement de tuile.
		unsigned	m_curFramerate;

	private:
		bool AnimInvalidIndex(int animIndex) const noexcept;
		bool AnimInvalidIndex() const noexcept;
		bool InvalidIndexs(int tileIndex) const noexcept;
		bool InvalidIndexs() const noexcept;
	};
}
