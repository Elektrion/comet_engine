/*
Copyright (c) 2026 Daniel Zach. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
*/

module;

#include "comet_std_include.hpp"


export module comet.application;

export import :component;


namespace comet::application
{
	
	export class Application
	{	
	private:
		using Component = ComponentTypeFor<Application>;
	
	private:
		std::vector<Component> components;
		bool running = false;
		
	public:
		constexpr void run()
		{
			running = true;
			
			std::ranges::for_each(components, [this](Component& component)
			{
				onAttach(component, *this);
			});
			
			while(running)
			{
				std::ranges::for_each(components, [this](Component& component)
				{
					onUpdate(component, *this);
				});
			}
			
			std::ranges::for_each(components | std::ranges::views::reverse, [this](Component& component)
			{
				onDetach(component, *this);
			});
			
			running = false;
		}
		
		constexpr void stop()
		{
			running = false;
		}
		
		template<typename Component_t, typename... Args>
		constexpr void addComponent(Args&&... args)
		{
			components.emplace_back(makeComponentForOfType<Application, Component_t>(std::forward<Args>(args)...));
		}
		
	};
	
}
