/*
Copyright (c) 2026 Daniel Zach. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
*/

#include "comet_std_include.hpp"

import comet;


class [[=comet::require<comet::WindowComponent>]] ExampleComponent
{
public:
	constexpr void onAttach(comet::Application&, comet::WindowComponent&) noexcept
	{
		std::println("Attaching ExampleLayer...");
	}
	
	constexpr void onDetach(comet::Application&, comet::WindowComponent&) noexcept
	{
		std::println("Detaching ExampleLayer...");
	}
	
	constexpr void onUpdate(comet::Application&, comet::WindowComponent&) noexcept
	{
		// This might get annoying...
		// std::println("Updating ExampleLayer...");
	}
};


auto main() -> int
{
	std::println("Hello Comet Engine!");
	
	comet::Application app;
	app.addComponent<comet::WindowAPIManagerComponent>();
	app.addComponent<ExampleComponent>();
	app.run();
}
