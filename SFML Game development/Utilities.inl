template <class T>
void centerOrigin(T& item)
{
	sf::FloatRect bounds{ item.getLocalBounds() };
	item.setOrigin(bounds.size / 2.f);
}