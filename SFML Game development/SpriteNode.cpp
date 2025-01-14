#include "SpriteNode.h"

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

SpriteNode::SpriteNode(sf::Texture const& texture) :
	mSprite{ texture }
{
}

SpriteNode::SpriteNode(sf::Texture const& texture, sf::IntRect const& rect) :
	mSprite{ texture, rect }
{
}
