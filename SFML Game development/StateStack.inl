template<class T>
inline void States::StateStack::registerState(States::ID stateID)
{
	mFactories[stateID] = [this]()
		{
			return States::State::Ptr(std::make_unique<T>(*this, mContext));
		};
}