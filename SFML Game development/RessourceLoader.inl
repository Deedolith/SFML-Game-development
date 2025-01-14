template <class Ressource>
inline std::unique_ptr<Ressource> RessourceLoader<Ressource>::load(std::filesystem::path const& filename)
{
	std::unique_ptr<Ressource> ressource{ std::make_unique<Ressource>() };
	if (!ressource->loadFromFile(filename))
		throw std::runtime_error{ "RessourceHolder::load - Failed to load " + filename.string() };
	return ressource;
}

template <>
inline std::unique_ptr<sf::Font> RessourceLoader<sf::Font>::load(std::filesystem::path const& filename)
{
	std::unique_ptr<sf::Font> ressource{ std::make_unique<sf::Font>() };
	if (!ressource->openFromFile(filename))
		throw std::runtime_error{ "RessourceHolder::load - Failed to load " + filename.string() };
	return ressource;
}

template<>
inline std::unique_ptr<Maps::Map> RessourceLoader<Maps::Map>::load(std::filesystem::path const& filename)
{
	std::unique_ptr<Maps::Map> ressource{ std::make_unique<Maps::Map>(filename) };
	return ressource;
}

template <class Ressource>
template <class Parameter>
inline std::unique_ptr<Ressource> RessourceLoader<Ressource>::load(std::filesystem::path const& filename, Parameter const& secondParameter)
{
	std::unique_ptr<Ressource> ressource{ std::make_unique<Ressource>() };
	if (!ressource->loadFromFile(filename, secondParameter))
		throw std::runtime_error{ "RessourceHolder::load - Failed to load " + filename.string() };
	return ressource;
}