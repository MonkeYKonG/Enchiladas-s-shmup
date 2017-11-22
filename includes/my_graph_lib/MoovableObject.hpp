#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

namespace               my
{
	//! Class permettant � un objet de se d�placer
	/*!
	Cette class fournis aux object qui en h�ritent des fonctions et attributs permettants de se d�placer dans la fen�tre.
	<br/><br/>
	La fonction UpdateDeplacement doit �tre appel� � chaque tours de boucle.<br/>
	Pour d�placer l'objet, m_onDeplacement doit �tre true.<br/>
	MoovableObject ne poss�de pas directement sa position, elle ne permet que de contenir des attributs de d�placements et de d�terminer � l'aide de m_canMove si l'objet peux modifier sa position.<br/>
	Si le nombre de d�placements maximum est diff�rents de -1, l'objet repassera ses compteurs � z�ro et m_onDeplacement � false.
	*/
  class		            MoovableObject
  {
  public:
  	typedef std::shared_ptr<MoovableObject> MoovableObjectPtr;
  	
	MoovableObject() noexcept;
	virtual ~MoovableObject() noexcept {}

	//! Passe les attributs de r�p�tition des d�placements � leurs valeurs par d�fauts.
	void				ResetDeplacement();
	//! Passe les attributs de d�placements � leurs valeurs par d�fauts et appel ResetDeplacement.
	void				ClearDeplacement();

	//! D�termine si l'objet se d�place.
	/*!
	<b>Valeur de retour</b><br/>
	Retourne true si l'objet se d�place, false sinon.
	*/
	bool		        IsOnDeplacement() const noexcept;
	//! D�termine si l'objet peux modifier sa position pendant cette frame.
	/*!
	<b>Valeur de retour</b><br/>
	Retourne true si l'objet peux modifier sa position pendant cette frame, false sinon.
	*/
	bool				CanMove() const noexcept;
	//! Retourne la vitesse de l'objet.
	float		        GetSpeed() const noexcept;
	//! Retourne un vecteur correspondant � la direction actuel de l'objet.
	const sf::Vector2f	&GetDirection() const noexcept;
	//! Retourne l'index de la frame actuel.
	int			        GetFrameRate() const noexcept;
	//! Retourne le nombre de frame s�parrant deux modification de position.
	int					GetDeplacememtRate() const noexcept;
	//! Retourne le nombre de modification de position qui ont eut lieu.
	int			        GetDeplacementRepetition() const noexcept;
	//! Retourne le nombre de modification de position � effectu�s.
	int			        GetRepetitionMax() const noexcept;
	//! Retourne un pointeur sur la position de la cible de l'objet.
	/*!
	<b>Valeur de retour</b><br/>
	Si l'objet � une cible retourne un pointeur sur la position de la cible de l'objet, NULL sinon
	*/
	sf::Vector2f		*GetTarget() const noexcept;

	//! Changer la valeur de d�placement de l'objet.
	/*!
	<b>Arguments</b><br/>
	onDeplacement: valeur de d�placement de l'objet.
	*/
	void                SetOnDeplacement(bool onDeplacement) noexcept;
	//! Changer la vitesse du d�placement de l'objet.
	/*!
	<b>Arguments</b><br/>
	speed: Nouvelle vitesse de l'objet
	*/
	void		        SetSpeed(float speed) noexcept;
	//! Changer la direction du d�placement de l'objet.
	/*!
	<b>Arguments</b><br/>
	direction: Nouvelle direction de l'objet.
	*/
	void		        SetDirection(const sf::Vector2f & direction) noexcept;
	//! Change l'index de frame courante
	void		        SetFrameRate(int frameRate) noexcept;
	//! Change le nombre de frame s�parant deux d�placement.
	void				SetDeplacementRate(int deplacementRate) noexcept;
	//! Change l'index de r�p�tition de d�placement.
	void		        SetDeplacementRepetition(int deplacementRepetition) noexcept;
	//! Change le nombre de r�p�tition du d�placement.
	void		        SetRepetitionMax(int repetitionMax) noexcept;
	//! Change la cible de l'objet.
	void				SetTarget(sf::Vector2f *target) noexcept;

  protected:
	  //! Met � jour le d�placement de l'objet.
	  /*!
	  Cette fonction met � jour les compteurs de frame. Et les remets � z�ro lorsqu'ils att�gnent leurs maximum.
	  Si le nombre de r�p�tition maximum est atteint, appel la fonction ResetDeplacement.
	  */
	  virtual void	    UpdateMovement();

	  //! Autorisation de l'objet � se d�placer.
	bool		  m_onDeplacement;
	//! Autorisation de l'objet a modifier sa position.
	bool			m_canMove;
	//! Vitesse de l'objet.
	float		  m_speed;
	//! Direction du d�placement.
	sf::Vector2f  m_direction;
	//! Index de la frame courante s�parant deux modification de position.
	int			  m_frameRate;
	//! Nombre de frame s�parant deux modification de position.
	int			  m_deplacementRate;
	//! Index du nombre de r�p�tition de modification de position.
	int			  m_deplacementRepetition;
	//! Nombre de r�p�tition maximum de modification de position.
	int			  m_repetitionMax;
	//! Cible de l'objet.
	sf::Vector2f	*m_target;
  };

  //! Transforme un vecteur en sont equivalent normalis�.
	/*!
	<b>Arguments</b><br/>
	vector: Le vecteur � normalis�.
	<br/><br/>
	<b>Valeur de retour</b><br/>
	Retourne un nouveau vecteur normalis� du m�me type.
	*/
  template <typename T>
  sf::Vector2<T> NormalizeVector(const sf::Vector2<T>& vector);
}
