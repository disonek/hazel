#pragma once

#include "hazel/core/Layer.hpp"
#include "hazel/events/KeyEvent.hpp"
#include "hazel/events/MouseEvent.hpp"
#include "hazel/events/ApplicationEvent.hpp"

namespace hazel {

	class HAZEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();
	private:

		float m_Time = 0.0f;
	};

}
