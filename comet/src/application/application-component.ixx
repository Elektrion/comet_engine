/*
Copyright (c) 2026 Daniel Zach. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
*/

module;

#include "comet_std_include.hpp"


export module comet.application:component;


namespace comet::application
{
	
	template<auto = []{}>
	struct tag {};
	
	template<typename... Types>
	struct require_typelist {};
	
	export template<typename... Components>
	constexpr require_typelist<Components...> require{};
	
	constexpr tag tag_contains_components{};
	
	consteval bool hasMultipleComponents(std::meta::info component)
	{
		// TODO: standard should now be `annotations_of_with_type`
		return std::meta::annotations_of(component, ^^decltype(tag_contains_components)).size() > 0;
	}
	
	
	template<typename Application_t>
	class Component
	{
	public:
		constexpr virtual ~Component() = default;
		
		constexpr virtual void onAttach(Application_t&) {}
		
		constexpr virtual void onDetach(Application_t&) {}
		
		constexpr virtual void onUpdate(Application_t&) {}
	};

	consteval auto has_pointer_semantics(std::meta::info type) -> bool
	{
		auto ops = std::meta::members_of(type, std::meta::access_context::unchecked())
			| std::ranges::views::filter(std::meta::is_operator_function)
			| std::ranges::views::filter([](auto member) { return std::meta::operator_of(member) == std::meta::operators::op_arrow; });

		for (auto _ : ops)
		 	return true;
		return false;
	}
	
	template<typename Component_t, typename... Args>
	constexpr void onAttach(Component_t& component, Args&&... args)
	{
		if constexpr(std::meta::is_pointer_type(^^Component_t) || has_pointer_semantics(^^Component_t))
		{
		  component->onAttach(std::forward<Args>(args)...);
		}
		else if constexpr(hasMultipleComponents(^^Component_t))
		{
			// TODO: `component.main_component` is not part of contract yet
			// TODO: `component.components` is not part of contract yet
			// TODO: change to "true recursing" behaviour, if indicated by the type in the annotations
			
			auto& [...components] = component.components;
			
			onAttach(component.main_component, std::forward<Args>(args)..., components...);
			
			template for(auto& subcomponent : component.components)
				onAttach(subcomponent, std::forward<Args>(args)...);
		}
		else
		{
			component.onAttach(std::forward<Args>(args)...);
		}
	}
	
	template<typename Component_t, typename... Args>
	constexpr void onDetach(Component_t& component, Args&&... args)
	{
		if constexpr(std::meta::is_pointer_type(^^Component_t) || has_pointer_semantics(^^Component_t))
		{
			component->onDetach(std::forward<Args>(args)...);
		}
		else if constexpr(hasMultipleComponents(^^Component_t))
		{
			// TODO: `component.main_component` is not part of contract yet
			// TODO: `component.components` is not part of contract yet
			// TODO: change to "true recursing" behaviour, if indicated by the type in the annotations
			
			auto& [...components] = component.components;
			
			onDetach(component.main_component, std::forward<Args>(args)..., components...);
			
			template for(auto& subcomponent : component.components)
				onDetach(subcomponent, std::forward<Args>(args)...);
		}
		else
		{
			component.onDetach(std::forward<Args>(args)...);
		}
	}
	
	template<typename Component_t, typename... Args>
	constexpr void onUpdate(Component_t& component, Args&&... args)
	{
		if constexpr(std::meta::is_pointer_type(^^Component_t) || has_pointer_semantics(^^Component_t))
		{
			component->onUpdate(std::forward<Args>(args)...);
		}
		else if constexpr(hasMultipleComponents(^^Component_t))
		{
			// TODO: `component.main_component` is not part of contract yet
			// TODO: `component.components` is not part of contract yet
			// TODO: change to "true recursing" behaviour, if indicated by the type in the annotations
			
			auto& [...components] = component.components;
			
			onUpdate(component.main_component, std::forward<Args>(args)..., components...);
			
			template for(auto& subcomponent : component.components)
				onUpdate(subcomponent, std::forward<Args>(args)...);
		}
		else
		{
			component.onUpdate(std::forward<Args>(args)...);
		}
	}
	
	template<typename Application_t, typename Component_t>
	class ConcreteComponent : public Component<Application_t>
	{
	private:
		struct [[=tag_contains_components]] ComponentStorage;
		consteval
		{
			auto components = 
				std::meta::annotations_of(^^Component_t)
				| std::ranges::views::transform(std::meta::type_of)
				| std::ranges::views::filter(std::meta::has_template_arguments)
				| std::ranges::views::filter([](auto annotation) {
						return std::meta::template_of(annotation) == ^^require_typelist;
					})
				| std::ranges::views::transform(std::meta::template_arguments_of)
				| std::ranges::views::join;
			
			std::meta::define_aggregate(^^ComponentStorage, {
				std::meta::data_member_spec(^^Component_t, { .name = "main_component" }), 
				std::meta::data_member_spec(
					std::meta::substitute(^^std::tuple, components), 
					{ .name = "components" })
			});
		}
		ComponentStorage component;
		
	public:
		template<typename... Args>
		constexpr ConcreteComponent(Args&&... args)
			: component{ std::forward<Args>(args)... }
		{}
		
		constexpr void onAttach(Application_t& app) override
		{
			comet::application::onAttach(component, app);
		}
		
		constexpr void onDetach(Application_t& app) override
		{
			comet::application::onDetach(component, app);
		}
		
		constexpr void onUpdate(Application_t& app) override
		{
			comet::application::onUpdate(component, app);
		}
	};

	template<typename Application_t>
	using ComponentTypeFor = std::unique_ptr<Component<Application_t>>;

	template<typename Application_t, typename Component_t, typename... Args>
	constexpr auto makeComponentForOfType(Args&&... args) -> decltype(auto)
	{
		return std::make_unique<ConcreteComponent<Application_t, Component_t>>(std::forward<Args>(args)...);
	}
	
}
