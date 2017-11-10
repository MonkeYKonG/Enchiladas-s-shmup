#include "Border.hpp"
#include "my_graph_lib/ResourcesLoader.hpp"

namespace	my
{
	Border::Border()
	{}

	Border::~Border()
	{}

	bool Border::IsIntersect(const sf::Vector2f & point) const noexcept
	{
		for (auto it = m_childs.begin(); it != m_childs.end(); ++it)
			if ((*it)->IsIntersect(point))
				return (true);
		return (false);
	}

	bool	Border::IsIntersect(const sf::FloatRect & square) const noexcept
	{
		for (auto it = m_childs.begin(); it != m_childs.end(); ++it)
			if ((*it)->IsIntersect(square))
				return (true);
		return (false);
	}

	const std::string	&Border::GetTextureKey() const noexcept
	{
		return (m_textureKey);
	}

	const sf::Vector2u	&Border::GetSize() const noexcept
	{
		return (m_size);
	}	

	const sf::Vector2u 	&Border::GetTileSize() const noexcept
	{
		return (m_tileSize);
	}

	const sf::IntRect	&Border::GetCornerSubrect() const noexcept
	{
		return (m_cornerSubrect);
	}

	const sf::IntRect 	&Border::GetOutlineSubrect() const noexcept
	{
		return (m_outlineSubrect);
	}

	const Border::TileList	&Border::GetTiles() const noexcept
	{
		return (m_tiles);
	}

	void	Border::SetTextureKey(const std::string & textureKey) noexcept
	{
		m_textureKey = textureKey;
	}

	void	Border::SetSize(const sf::Vector2u & size) noexcept
	{
		m_size = size;
	}

	void	Border::SetTileSize(const sf::Vector2u & tileSize) noexcept
	{
		m_tileSize = tileSize;
	}

	void	Border::SetCornerSubrect(const sf::IntRect & cornerSubrect) noexcept
	{
		m_cornerSubrect = cornerSubrect;
	}

	void	Border::SetOutlineSubrect(const sf::IntRect & outlineSubrect) noexcept
	{
		m_outlineSubrect = outlineSubrect;
	}

	SpriteObject::SpriteObjectPtr	Border::AddCorner(const sf::Vector2f & position)throw (std::invalid_argument)
	{
		SpriteObject::SpriteObjectPtr newCorner;

		newCorner = SpriteObject::SpriteObjectPtr(new SpriteObject());
		try
		{
			newCorner->SetTexture(ResourcesLoader::GetTexture(m_textureKey));
			newCorner->SetSubrect(m_cornerSubrect);
			newCorner->setPosition(position);
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
		return (newCorner);
	}

	SpriteObject::SpriteObjectPtr 	Border::AddOutline(const sf::Vector2f & position) throw (std::invalid_argument)
	{
		SpriteObject::SpriteObjectPtr newOutline;

		newOutline = SpriteObject::SpriteObjectPtr(new SpriteObject());
		try
		{
			newOutline->SetTexture(ResourcesLoader::GetTexture(m_textureKey));
			newOutline->SetSubrect(m_outlineSubrect);
			newOutline->setPosition(position);
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
		return (newOutline);
	}

	void	Border::InitializeChilds() throw (std::invalid_argument)
	{
		if (m_size.x == 0 || m_size.y == 0)
			throw (std::invalid_argument("InitializeChilds: invalid size"));
		if (m_tileSize.x == 0 || m_tileSize.y == 0)
			throw (std::invalid_argument("InitializeChilds: invalide tileSize"));
		try
		{
			for (unsigned i = 1; i < m_size.x / m_tileSize.x; ++i)
			{
				m_tiles.push_back(AddOutline(sf::Vector2f(m_tileSize.x * i, 0)));
				m_tiles.push_back(AddOutline(sf::Vector2f(m_tileSize.x * i, m_size.y - m_tileSize.y)));
			}
			for (unsigned i = 1; i < m_size.y / m_tileSize.y; ++i)
			{
				m_tiles.push_back(AddOutline(sf::Vector2f(0, m_tileSize.y * i)));
				m_tiles.push_back(AddOutline(sf::Vector2f(m_size.x - m_tileSize.x, m_tileSize.y * i)));
			}
			m_tiles.push_back(AddCorner(sf::Vector2f(0, 0)));
			m_tiles.push_back(AddCorner(sf::Vector2f(m_size.x - m_tileSize.x, 0)));
			m_tiles.push_back(AddCorner(sf::Vector2f(0, m_size.y - m_tileSize.y)));
			m_tiles.push_back(AddCorner(sf::Vector2f(m_size.x - m_tileSize.x, m_size.y - m_tileSize.y)));
		}
		catch (const std::invalid_argument & e) 
		{
			throw (e);
		}
	}

	void	Border::UpdateTiles() noexcept
	{
		for (unsigned i = 0; i < m_tiles.size(); ++i)
		{
			m_tiles[i]->UpdateAnimation();
			m_tiles[i]->UpdateMovement();
		}
	}

	void	Border::draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept
	{
		if (!m_visible)
			return;
		Node::draw(target, states);
		states.transform *= getTransform();
		for (unsigned i = 0; i < m_tiles.size(); ++i)
			target.draw(*m_tiles[i], states);
	}
}