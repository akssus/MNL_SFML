#include "MnInputModuleSFML.h"
#include <SFML/Window/Event.hpp>

using namespace MNL;

MnKeyState MnInputModuleSFML::GetKeyState(const std::string & keyName)
{
	auto keyCode = m_inputMapper.Get(keyName).keyCode;
	return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(keyCode)) ? MN_KEYSTATE_PRESSED : MN_KEYSTATE_RELEASED;
}
