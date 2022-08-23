#pragma once
#include "LostSouls/Layer.h"

#include "LostSouls/Events/ApplicationEvent.h"
#include "LostSouls/Events/KeyEvent.h"
#include "LostSouls/Events/MouseEvent.h"

namespace LostSouls {

	class LOSTSOULS_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;

	};

}
