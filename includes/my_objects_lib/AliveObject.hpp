#pragma once

#include <stdexcept>

namespace my
{
  //! Class représentant un object dit "vivant" ou "mort".
  /*!
    Un object "vivant" possède un nombre de point de vie maximum et courant, lorsque ces points de vie tombent à 0, l'objet est considéré comme "mort"
  */
	class AliveObject
	{
	public:
		virtual ~AliveObject() {}

	  //! Détermine l'état de l'objet (vivatn ou mort).
	  /*!
	    <b>Valeur de retour</b><br/>
	    La fonction retourne <b>vrais</b> si l'objet est vivant, <b>faux</b> sinon.
	   */
		bool IsAlive() const noexcept;

	  //! Retourne le nonbre de points de vie courants.
	  /*!
	    <b>Valeur de retour</b><br/>
	    Retourne le nombre de points de vie courant dans un entier non-signé.
	   */
		unsigned GetCurHP() const noexcept;

	  //! Retourne le nombre de points de vie maximum.
	  /*!
	    <b>Valeur de retour</b><br/>
	    Retourne le nombre de points de vie maximum dans un entier non-signé.
	   */
		unsigned GetMaxHP() const noexcept;

	  //! Change le nombre de points de vie courants.
	  /*!
	    <b>Arguments</b><br/>
	    curHP: Le nouveau nombre de points de vie de l'objet.
	    <br/><br/>
	    <b>Exception</b><br/>
	    std::invalid_argument: Le nombre de points de vie est supérieur au maximum.
	   */
		void SetCurHP(unsigned curHP) throw (std::invalid_argument);

	  //! Change le nombre de points de vie maximum.
	  /*!
	    <b>Arguments</b><br/>
	    maxHP: Le nouveau nombre de points de vie maximum.
	   */
		void SetMaxHP(unsigned maxHP) noexcept;

	  //! Soustrait aux points de vie courant la valeur passé en argument.
	  /*!
	    <b>Arguments</b><br/>
	    damage: Le nombre de dommage à subir.
	   */
		virtual void TakeDamage(unsigned damage) noexcept;

	protected:
	  //! Index de l'animation de mort.
		static const std::string DEATH_ANIM_NAME;

		AliveObject();

	  //! Booléen déterminant si l'objet est "vivant" ou "mort".
		bool m_isAlive;
	  //! Nombre de points de vie courant.
		unsigned m_HP;
	  //! Nombre de points de vie maximum.
		unsigned m_maxHP;
	};
}
