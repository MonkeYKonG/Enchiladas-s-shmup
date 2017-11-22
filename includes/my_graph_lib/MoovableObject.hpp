#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

namespace               my
{
	//! Class permettant à un objet de se déplacer
	/*!
	Cette class fournis aux object qui en héritent des fonctions et attributs permettants de se déplacer dans la fenêtre.
	<br/><br/>
	La fonction UpdateDeplacement doit être appelé à chaque tours de boucle.<br/>
	Pour déplacer l'objet, m_onDeplacement doit être true.<br/>
	MoovableObject ne possède pas directement sa position, elle ne permet que de contenir des attributs de déplacements et de déterminer à l'aide de m_canMove si l'objet peux modifier sa position.<br/>
	Si le nombre de déplacements maximum est différents de -1, l'objet repassera ses compteurs à zéro et m_onDeplacement à false.
	*/
  class		            MoovableObject
  {
  public:
  	typedef std::shared_ptr<MoovableObject> MoovableObjectPtr;
  	
	MoovableObject() noexcept;
	virtual ~MoovableObject() noexcept {}

	//! Passe les attributs de répétition des déplacements à leurs valeurs par défauts.
	void				ResetDeplacement();
	//! Passe les attributs de déplacements à leurs valeurs par défauts et appel ResetDeplacement.
	void				ClearDeplacement();

	//! Détermine si l'objet se déplace.
	/*!
	<b>Valeur de retour</b><br/>
	Retourne true si l'objet se déplace, false sinon.
	*/
	bool		        IsOnDeplacement() const noexcept;
	//! Détermine si l'objet peux modifier sa position pendant cette frame.
	/*!
	<b>Valeur de retour</b><br/>
	Retourne true si l'objet peux modifier sa position pendant cette frame, false sinon.
	*/
	bool				CanMove() const noexcept;
	//! Retourne la vitesse de l'objet.
	float		        GetSpeed() const noexcept;
	//! Retourne un vecteur correspondant à la direction actuel de l'objet.
	const sf::Vector2f	&GetDirection() const noexcept;
	//! Retourne l'index de la frame actuel.
	int			        GetFrameRate() const noexcept;
	//! Retourne le nombre de frame séparrant deux modification de position.
	int					GetDeplacememtRate() const noexcept;
	//! Retourne le nombre de modification de position qui ont eut lieu.
	int			        GetDeplacementRepetition() const noexcept;
	//! Retourne le nombre de modification de position à effectués.
	int			        GetRepetitionMax() const noexcept;
	//! Retourne un pointeur sur la position de la cible de l'objet.
	/*!
	<b>Valeur de retour</b><br/>
	Si l'objet à une cible retourne un pointeur sur la position de la cible de l'objet, NULL sinon
	*/
	sf::Vector2f		*GetTarget() const noexcept;

	//! Changer la valeur de déplacement de l'objet.
	/*!
	<b>Arguments</b><br/>
	onDeplacement: valeur de déplacement de l'objet.
	*/
	void                SetOnDeplacement(bool onDeplacement) noexcept;
	//! Changer la vitesse du déplacement de l'objet.
	/*!
	<b>Arguments</b><br/>
	speed: Nouvelle vitesse de l'objet
	*/
	void		        SetSpeed(float speed) noexcept;
	//! Changer la direction du déplacement de l'objet.
	/*!
	<b>Arguments</b><br/>
	direction: Nouvelle direction de l'objet.
	*/
	void		        SetDirection(const sf::Vector2f & direction) noexcept;
	//! Change l'index de frame courante
	void		        SetFrameRate(int frameRate) noexcept;
	//! Change le nombre de frame séparant deux déplacement.
	void				SetDeplacementRate(int deplacementRate) noexcept;
	//! Change l'index de répétition de déplacement.
	void		        SetDeplacementRepetition(int deplacementRepetition) noexcept;
	//! Change le nombre de répétition du déplacement.
	void		        SetRepetitionMax(int repetitionMax) noexcept;
	//! Change la cible de l'objet.
	void				SetTarget(sf::Vector2f *target) noexcept;

  protected:
	  //! Met à jour le déplacement de l'objet.
	  /*!
	  Cette fonction met à jour les compteurs de frame. Et les remets à zéro lorsqu'ils attègnent leurs maximum.
	  Si le nombre de répétition maximum est atteint, appel la fonction ResetDeplacement.
	  */
	  virtual void	    UpdateMovement();

	  //! Autorisation de l'objet à se déplacer.
	bool		  m_onDeplacement;
	//! Autorisation de l'objet a modifier sa position.
	bool			m_canMove;
	//! Vitesse de l'objet.
	float		  m_speed;
	//! Direction du déplacement.
	sf::Vector2f  m_direction;
	//! Index de la frame courante séparant deux modification de position.
	int			  m_frameRate;
	//! Nombre de frame séparant deux modification de position.
	int			  m_deplacementRate;
	//! Index du nombre de répétition de modification de position.
	int			  m_deplacementRepetition;
	//! Nombre de répétition maximum de modification de position.
	int			  m_repetitionMax;
	//! Cible de l'objet.
	sf::Vector2f	*m_target;
  };

  //! Transforme un vecteur en sont equivalent normalisé.
	/*!
	<b>Arguments</b><br/>
	vector: Le vecteur à normalisé.
	<br/><br/>
	<b>Valeur de retour</b><br/>
	Retourne un nouveau vecteur normalisé du même type.
	*/
  template <typename T>
  sf::Vector2<T> NormalizeVector(const sf::Vector2<T>& vector);
}
