#pragma once

#include "my_menu_lib/SchmupScene.hpp"
#include "my_objects_lib/ProgressBar.hpp"

namespace my
{
	namespace schmup
	{
		class SchmupMainGame : public SchmupScene
		{
		public:
			SchmupMainGame();

			virtual void Initialize(XMLNode::XMLNodePtr sceneRoot) throw (std::out_of_range, std::invalid_argument);
			virtual void LoadSavingData(int slot = -1) throw (std::out_of_range, std::invalid_argument);
			virtual void Reset() throw (std::out_of_range, std::invalid_argument);
			virtual const SceneReturnValue Update(const sf::Vector2i & mousePos) throw (std::exception);
			
		private:
			enum GAME_STATES
			{
				MAIN = 0,
				PLAY = 1,
				CRAFTING,
				SELECT_STAGE,
				GAME_STATES_COUNT
			};

			enum MAIN_BUTTONS
			{
				PLAY_BTN = 0,
				UPDATE_BTN = 1,
				MAIN_MENU_BTN
			};

			enum CRAFTING_BUTTONS
			{
				MORE_ATK_BTN = 0,
				MORE_DEF_BTN = 1,
				CRAFTING_BACK_BTN
			};

			static const std::string MAIN_NODE_NAME;
			static const std::string PLAY_NODE_NAME;
			static const std::string CRAFTING_NODE_NAME;
			static const std::string SELECT_STAGE_NODE_NAME;
			static const std::string NODE_NAMES[GAME_STATES::GAME_STATES_COUNT];

			virtual void TriggerEnemyIsDamaged(Shooter::ShootList::iterator & bulletIt, EnemiesPool::EnemiesList::iterator &enemyIt) noexcept;
			virtual void PreparingPlayerBuller(Bullet::BulletPtr newBullet) noexcept;

			const SceneReturnValue UpdateMain(const sf::Vector2i & mousePos) throw (std::exception);
			const SceneReturnValue UpdatePlay(const sf::Vector2i & mousePos) throw (std::exception);
			const SceneReturnValue UpdateCrafting(const sf::Vector2i & mousePos) throw (std::exception);
			const SceneReturnValue UpdateSelectStage(const sf::Vector2i & mousePos) throw (std::exception);

			virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept;
			void drawMain(sf::RenderTarget & target, sf::RenderStates states) const noexcept;
			void drawPlay(sf::RenderTarget & target, sf::RenderStates states) const noexcept;
			void drawCrafting(sf::RenderTarget & target, sf::RenderStates states) const noexcept;
			void drawSelectStage(sf::RenderTarget & target, sf::RenderStates states) const noexcept;

			void ClearStageScreen() noexcept;

			void InitializeStage(unsigned levelIndex) throw (std::out_of_range, std::invalid_argument);
			void InitializePlayer() throw (std::out_of_range, std::invalid_argument);
			void InitializeGameValues() throw (std::out_of_range, std::invalid_argument);
			
			void ParseGameValuesNode() throw(std::out_of_range, std::invalid_argument);
			void SaveGame() throw (std::out_of_range, std::invalid_argument);

			XMLNode::XMLNodePtr GenerateStage(XMLNode::XMLNodePtr paternNode) throw (std::out_of_range, std::invalid_argument);
			bool AddExperience(unsigned exp) noexcept;
			void AddLevel() noexcept;

			void UpdateLimitPosition() noexcept;
			void CorrectPlayerPosition() noexcept;
			void UnloadUnlimitEnemies() noexcept;
			void UnloadUnlimitShoots() noexcept;
			
			bool IsOutOfLimit(Node::NodePtr node) const noexcept;
			bool IsOutOfLeftLimit(Node::NodePtr node) const noexcept;
			bool IsOutOfRightLimit(Node::NodePtr node) const noexcept;
			bool IsOutOfTopLimit(Node::NodePtr node) const noexcept;
			bool IsOutOfBottomLimit(Node::NodePtr node) const noexcept;

			int m_saveSlot;
			unsigned m_score;
			unsigned m_maxScore;
			unsigned m_playerLevel;
			unsigned m_playerCurExp;
			unsigned m_playerLevelUpExp;
			GAME_STATES m_gameState;
			XMLNode::XMLNodePtr	m_nodes[GAME_STATES::GAME_STATES_COUNT];
			XMLNode::XMLNodePtr m_gameRoot;
			XMLNode::XMLNodePtr m_playerNode;
			XMLNode::XMLNodePtr m_gameValuesNode;
		};
	}
}