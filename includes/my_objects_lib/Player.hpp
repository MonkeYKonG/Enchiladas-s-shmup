#pragma once

#include "my_graph_lib/SpriteObject.hpp"
#include "Direction.hpp"

namespace my
{
	class Player : public SpriteObject
	{
	public:
		typedef std::shared_ptr<Player> PlayerPtr;
		typedef std::pair<sf::Keyboard::Key, Direction> InputPair;
		typedef std::vector<InputPair> InputsList;

		Player();
		virtual ~Player() {}

		virtual void Update() throw (std::out_of_range);

		const InputsList &GetInputsList() const noexcept;
		void AddInputs(const InputPair & newInput) noexcept;
		void SetInputs(const InputsList & inputs) noexcept;

	protected:
		static const unsigned CUR_DEPL_SIZE = 4;

		virtual void UpdateMovement() noexcept;
		virtual void CheckForInput() noexcept;

		InputsList	m_inputs;
		bool m_curentDeplacement[CUR_DEPL_SIZE];
	};
}