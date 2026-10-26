/*
Copyright (c) 2026 Daniel Zach. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
*/

#include "comet_std_include.hpp"

import comet;


class ExampleComponent
{
private:
	int counter = 0;
	
public:
	constexpr void onAttach(comet::Application&) noexcept
	{
		std::println("Attaching ExampleLayer...");
	}
	
	constexpr void onDetach(comet::Application&) noexcept
	{
		std::println("Detaching ExampleLayer...");
	}
	
	constexpr void onUpdate(comet::Application& app) noexcept
	{
		std::println("Updating ExampleLayer, counter is {}.", counter++);
		if(counter > 10)
		{
			std::println("Counter has reached 10, now stopping application!");
			app.stop();
		}
	}
};


auto main() -> int
{
	std::println("Hello Comet Engine!");
	
	comet::Application app;
	app.addComponent<ExampleComponent>();
	app.run();
}
