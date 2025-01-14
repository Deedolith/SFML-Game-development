#include <utility>
#include <stdexcept>
#include <cassert>

template<class Ressource, class Identifier>
inline void RessourceHolder<Ressource, Identifier>::insert(Identifier id, std::unique_ptr<Ressource> ressource)
{
	auto inserted{ mRessourceMap.insert(std::make_pair(id, std::move(ressource))) };
	assert(inserted.second && "The given id is already used.");
}

template<class Ressource, class Identifier>
inline Ressource& RessourceHolder<Ressource, Identifier>::get(Identifier id)
{
	auto found{ mRessourceMap.find(id) };
	if(found == mRessourceMap.end())
		assert(found != mRessourceMap.end() && "The given id do not exist.");
	return *found->second;
}

template<class Ressource, class Identifier>
inline Ressource const& RessourceHolder<Ressource, Identifier>::get(Identifier id) const
{
	auto found{ mRessourceMap.find(id) };
	assert(found != mRessourceMap.end() && "The given id do not exist.");
	return *found->second;
}
