#include "MnSFMLModule.h"

using namespace MNL;

MnSFMLModule::MnSFMLModule(uint32_t windowWidth, uint32_t windowHeight, std::string title) : 
m_windowWidth(windowWidth),
m_windowHeight(windowHeight),
m_title(title)
{
}

MnSFMLModule::~MnSFMLModule()
{
}

void MnSFMLModule::Update()
{
}

void MnSFMLModule::OnUnregistering()
{
}

void MnSFMLModule::OnRegistered()
{
	_CreateWindow(m_windowWidth, m_windowHeight, m_title);
}

std::shared_ptr<sf::RenderWindow> MnSFMLModule::GetRenderWindow()
{
	return m_spRenderWindow;
}

void MnSFMLModule::_CreateWindow(uint32_t width, uint32_t height, std::string title)
{
	m_spRenderWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title);
}
