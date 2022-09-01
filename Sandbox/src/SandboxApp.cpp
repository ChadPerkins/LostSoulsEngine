#include <LostSouls.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public LostSouls::Layer
{
public:
	ExampleLayer() 
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), // Create a 16x9 aspect ratio
		 m_CameraPosition(0.0f)
	{
		// Vertex array
		m_VertexArray.reset(LostSouls::VertexArray::Create());

		// Vertex buffer
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.1f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.3f, 0.1f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		std::shared_ptr<LostSouls::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(LostSouls::VertexBuffer::Create(vertices, sizeof(vertices)));

		LostSouls::BufferLayout layout = {
			{ LostSouls::ShaderDataType::Vec3, "a_Position"},
			{ LostSouls::ShaderDataType::Vec4, "a_Color"},
		};
		vertexBuffer->SetLayout(layout);
		// Must add the vertex buffer to the vertex array after the layout has been set
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		// Index buffer
		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<LostSouls::IndexBuffer> indexBuffer;
		indexBuffer.reset(LostSouls::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		//// Creating a square ////
		m_SquareVA.reset(LostSouls::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,

		};

		std::shared_ptr<LostSouls::VertexBuffer> squareVB;
		squareVB.reset(LostSouls::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ LostSouls::ShaderDataType::Vec3, "a_Position"},
			});
		// Must add the vertex buffer to the vertex array after the layout has been set
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<LostSouls::IndexBuffer> squareIB;
		squareIB.reset(LostSouls::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		// Vertex and fragment shaders
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
			
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
			
		)";

		m_Shader.reset(LostSouls::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
			
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
			
		)";
		
		
		m_FlatColorShader.reset(LostSouls::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));
	}

	void OnUpdate(LostSouls::Timestep ts) override
	{
		// Conditions to control the camera movement
		if (LostSouls::Input::IsKeyPressed(LS_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMovementSpeed * ts;
		else if (LostSouls::Input::IsKeyPressed(LS_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMovementSpeed * ts;

		if (LostSouls::Input::IsKeyPressed(LS_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMovementSpeed * ts;
		else if (LostSouls::Input::IsKeyPressed(LS_KEY_UP))
			m_CameraPosition.y += m_CameraMovementSpeed * ts;

		if (LostSouls::Input::IsKeyPressed(LS_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (LostSouls::Input::IsKeyPressed(LS_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		
		LostSouls::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		LostSouls::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		LostSouls::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<LostSouls::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<LostSouls::OpenGLShader>(m_FlatColorShader)->UploadUniformVec3("u_Color", m_SquareColor);

		// Make a 20x20 grid of squares
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				LostSouls::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}
		LostSouls::Renderer::Submit(m_Shader, m_VertexArray);

		LostSouls::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(LostSouls::Event& event) override
	{

	}
	
private:
	std::shared_ptr<LostSouls::Shader> m_Shader;
	std::shared_ptr<LostSouls::VertexArray> m_VertexArray;

	std::shared_ptr<LostSouls::Shader> m_FlatColorShader;
	std::shared_ptr<LostSouls::VertexArray> m_SquareVA;

	LostSouls::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMovementSpeed = 5.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public LostSouls::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new LostSouls::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

LostSouls::Application* LostSouls::CreateApplication()
{
	return new Sandbox();
}