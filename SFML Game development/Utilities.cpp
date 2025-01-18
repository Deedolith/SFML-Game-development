#include <cassert>
#include <string>

#include <SFML/Graphics/Rect.hpp>

#include "Utilities.h"

//void centerOrigin(sf::Sprite& sprite)
//{
//	sf::FloatRect bounds{ sprite.getLocalBounds() };
//	sprite.setOrigin(bounds.size / 2.f);
//}
//
//void centerOrigin(sf::Text& text)
//{
//	sf::FloatRect bounds{ text.getLocalBounds() };
//	text.setOrigin(bounds.size / 2.f);
//}
//
//void centerOrigin(Fonts::Bitmaps::Text& text)
//{
//	sf::FloatRect bounds{ text.getLocalBounds() };
//	text.setOrigin(bounds.size / 2.f);
//}

std::vector<unsigned> splitString(const std::string& s, char delimiter)
{
	std::vector<unsigned> tokens;
	std::stringstream ss{ s };
	std::string token;
	while (std::getline(ss, token, delimiter))
	{
		tokens.push_back(std::stoul(token));
	}
	return tokens;
}

std::string keyToString(sf::Keyboard::Key key)
{
	std::string string{};
	#define KEYTOSTRING_CASE(x) case sf::Keyboard::Key:: ## x : string = #x; break;
	switch (key)
	{
		KEYTOSTRING_CASE(Unknown)
		KEYTOSTRING_CASE(A)
		KEYTOSTRING_CASE(B)
		KEYTOSTRING_CASE(C)
		KEYTOSTRING_CASE(D)
		KEYTOSTRING_CASE(E)
		KEYTOSTRING_CASE(F)
		KEYTOSTRING_CASE(G)
		KEYTOSTRING_CASE(H)
		KEYTOSTRING_CASE(I)
		KEYTOSTRING_CASE(J)
		KEYTOSTRING_CASE(K)
		KEYTOSTRING_CASE(L)
		KEYTOSTRING_CASE(M)
		KEYTOSTRING_CASE(N)
		KEYTOSTRING_CASE(O)
		KEYTOSTRING_CASE(P)
		KEYTOSTRING_CASE(Q)
		KEYTOSTRING_CASE(R)
		KEYTOSTRING_CASE(S)
		KEYTOSTRING_CASE(T)
		KEYTOSTRING_CASE(U)
		KEYTOSTRING_CASE(V)
		KEYTOSTRING_CASE(W)
		KEYTOSTRING_CASE(X)
		KEYTOSTRING_CASE(Y)
		KEYTOSTRING_CASE(Z)
		KEYTOSTRING_CASE(Num0)
		KEYTOSTRING_CASE(Num1)
		KEYTOSTRING_CASE(Num2)
		KEYTOSTRING_CASE(Num3)
		KEYTOSTRING_CASE(Num4)
		KEYTOSTRING_CASE(Num5)
		KEYTOSTRING_CASE(Num6)
		KEYTOSTRING_CASE(Num7)
		KEYTOSTRING_CASE(Num8)
		KEYTOSTRING_CASE(Num9)
		KEYTOSTRING_CASE(Escape)
		KEYTOSTRING_CASE(LControl)
		KEYTOSTRING_CASE(LShift)
		KEYTOSTRING_CASE(LAlt)
		KEYTOSTRING_CASE(LSystem)
		KEYTOSTRING_CASE(RControl)
		KEYTOSTRING_CASE(RShift)
		KEYTOSTRING_CASE(RAlt)
		KEYTOSTRING_CASE(RSystem)
		KEYTOSTRING_CASE(Menu)
		KEYTOSTRING_CASE(LBracket)
		KEYTOSTRING_CASE(RBracket)
		KEYTOSTRING_CASE(Semicolon)
		KEYTOSTRING_CASE(Comma)
		KEYTOSTRING_CASE(Period)
		KEYTOSTRING_CASE(Apostrophe)
		KEYTOSTRING_CASE(Slash)
		KEYTOSTRING_CASE(Backslash)
		KEYTOSTRING_CASE(Grave)
		KEYTOSTRING_CASE(Equal)
		KEYTOSTRING_CASE(Hyphen)
		KEYTOSTRING_CASE(Space)
		KEYTOSTRING_CASE(Enter)
		KEYTOSTRING_CASE(Backspace)
		KEYTOSTRING_CASE(Tab)
		KEYTOSTRING_CASE(PageUp)
		KEYTOSTRING_CASE(PageDown)
		KEYTOSTRING_CASE(End)
		KEYTOSTRING_CASE(Home)
		KEYTOSTRING_CASE(Insert)
		KEYTOSTRING_CASE(Delete)
		KEYTOSTRING_CASE(Add)
		KEYTOSTRING_CASE(Subtract)
		KEYTOSTRING_CASE(Multiply)
		KEYTOSTRING_CASE(Divide)
		KEYTOSTRING_CASE(Left)
		KEYTOSTRING_CASE(Right)
		KEYTOSTRING_CASE(Up)
		KEYTOSTRING_CASE(Down)
		KEYTOSTRING_CASE(Numpad0)
		KEYTOSTRING_CASE(Numpad1)
		KEYTOSTRING_CASE(Numpad2)
		KEYTOSTRING_CASE(Numpad3)
		KEYTOSTRING_CASE(Numpad4)
		KEYTOSTRING_CASE(Numpad5)
		KEYTOSTRING_CASE(Numpad6)
		KEYTOSTRING_CASE(Numpad7)
		KEYTOSTRING_CASE(Numpad8)
		KEYTOSTRING_CASE(Numpad9)
		KEYTOSTRING_CASE(F1)
		KEYTOSTRING_CASE(F2)
		KEYTOSTRING_CASE(F3)
		KEYTOSTRING_CASE(F4)
		KEYTOSTRING_CASE(F5)
		KEYTOSTRING_CASE(F6)
		KEYTOSTRING_CASE(F7)
		KEYTOSTRING_CASE(F8)
		KEYTOSTRING_CASE(F9)
		KEYTOSTRING_CASE(F10)
		KEYTOSTRING_CASE(F11)
		KEYTOSTRING_CASE(F12)
		KEYTOSTRING_CASE(F13)
		KEYTOSTRING_CASE(F14)
		KEYTOSTRING_CASE(F15)
		KEYTOSTRING_CASE(Pause)
	}
	return toUpperCase(string);
}

std::string toUpperCase(std::string string)
{
	for (char& c : string)
		c = std::toupper(c);
	return string;
}

