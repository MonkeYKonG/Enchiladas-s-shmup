#pragma once

#include "my_graph_lib/SpriteObject.hpp"

namespace	my
{
	class Border : public Node
	{
	public:
		typedef std::shared_ptr<Border> BorderPtr;

		Border();
		~Border();

		bool IsIntersect(const sf::Vector2f & point) const noexcept;
		bool IsIntersect(const sf::FloatRect & square) const noexcept;

		const std::string 	&GetTextureKey() const noexcept;
		const sf::Vector2u	&GetSize() const noexcept;
		const sf::Vector2u 	&GetTileSize() const noexcept;
		const sf::IntRect 	&GetCornerSubrect() const noexcept;
		const sf::IntRect 	&GetOutlineSubrect() const noexcept;
		void	SetTextureKey(const std::string & textureKey) noexcept;
		void	SetSize(const sf::Vector2u & size) noexcept;
		void	SetTileSize(const sf::Vector2u & tileSize) noexcept;
		void	SetCornerSubrect(const sf::IntRect & cornerSubrect) noexcept;
		void	SetOutlineSubrect(const sf::IntRect & outlineSubrect) noexcept;

		void	InitializeChilds() throw (std::invalid_argument);
		
	private:
		SpriteObject::SpriteObjectPtr AddCorner(const sf::Vector2f & position) throw (std::invalid_argument);
		SpriteObject::SpriteObjectPtr AddOutline(const sf::Vector2f & position) throw (std::invalid_argument);

		std::string		m_textureKey;
		sf::Vector2u	m_size;
		sf::Vector2u 	m_tileSize;
		sf::IntRect		m_cornerSubrect;
		sf::IntRect 	m_outlineSubrect;
	};
}