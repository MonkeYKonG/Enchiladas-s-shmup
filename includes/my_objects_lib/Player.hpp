#pragma once

#include "my_graph_lib/SpriteObject.hpp"
#include "Direction.hpp"
#include "Shooter.hpp"

namespace my
{
	class Player : public SpriteObject, public Shooter
	{
	public:
		typedef std::shared_ptr<Player> PlayerPtr;
		typedef std::pair<sf::Keyboard::Key, Direction> InputDeplacement;
		typedef std::pair<sf::Keyboard::Key, std::string> InputShoot;
		typedef std::vector<InputDeplacement> InputsDeplacementList;
		typedef std::vector<InputShoot> InputsShootList;

		Player();
		virtual ~Player() {}

		virtual void Update() throw (std::out_of_range);

		const InputsDeplacementList &GetInputsDeplacementList() const noexcept;
		const InputsShootList &GetInputsShootList() const noexcept;

		void AddInputDeplacement(const InputDeplacement & newInput) noexcept;
		void SetInputsDeplacement(const InputsDeplacementList & inputs) noexcept;
		void AddInputShoot(const InputShoot & newInput) noexcept;
		void SetInputsShoot(const InputsShootList & inputs) noexcept;

	protected:
		static const unsigned CUR_DEPL_SIZE = 4;

		virtual void UpdateMovement() noexcept;
		virtual void UpdateAnimation() throw (std::out_of_range);
		virtual void CheckForInput() noexcept;

		InputsDeplacementList	m_inputsDeplacement;
		bool m_curentDeplacement[CUR_DEPL_SIZE];
		InputsShootList m_inputsShoot;
	};
}