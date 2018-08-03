#pragma once

#include "MnGameSystemModule.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace MNL
{
	//얘는 진짜 오더가 최전단이어야 됨
	//Registered 되는 순간 즉시 윈도우가 생성됩니다잉
	class MnSFMLModule : public MnGameSystemModule
	{
	public:
		MnSFMLModule(uint32_t windowWidth, uint32_t windowHeight, std::string title);
		virtual ~MnSFMLModule();

		void Update() override;
		void OnRegistered() override;
		void OnUnregistering() override;

		std::shared_ptr<sf::RenderWindow> GetRenderWindow();

	private:
		void _CreateWindow(uint32_t width, uint32_t height, std::string title);
		
	private:
		std::shared_ptr<sf::RenderWindow> m_spRenderWindow;
		uint32_t m_windowWidth;
		uint32_t m_windowHeight;
		std::string m_title;
	};
}
