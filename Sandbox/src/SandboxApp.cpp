#include <LostSouls.h>

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
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,

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

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_Shader.reset(new LostSouls::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
			
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
			
		)";

		m_BlueShader.reset(new LostSouls::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate() override
	{
		// Conditions to control the camera movement
		if (LostSouls::Input::IsKeyPressed(LS_KEY_LEFT))
			m_CameraPosition.x -= m_MovementSpeed;		
		else if (LostSouls::Input::IsKeyPressed(LS_KEY_RIGHT))
			m_CameraPosition.x += m_MovementSpeed;
		
		if (LostSouls::Input::IsKeyPressed(LS_KEY_DOWN))
			m_CameraPosition.y -= m_MovementSpeed;
		else if (LostSouls::Input::IsKeyPressed(LS_KEY_UP))
			m_CameraPosition.y += m_MovementSpeed;

		if (LostSouls::Input::IsKeyPressed(LS_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed;
		if (LostSouls::Input::IsKeyPressed(LS_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed;
		

		LostSouls::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		LostSouls::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		LostSouls::Renderer::BeginScene(m_Camera);

		LostSouls::Renderer::Submit(m_BlueShader, m_SquareVA);
		LostSouls::Renderer::Submit(m_Shader, m_VertexArray);

		LostSouls::Renderer::EndScene();
	}

	void OnEvent(LostSouls::Event& event) override
	{

	}

	

private:
	std::shared_ptr<LostSouls::Shader> m_Shader;
	std::shared_ptr<LostSouls::VertexArray> m_VertexArray;

	std::shared_ptr<LostSouls::Shader> m_BlueShader;
	std::shared_ptr<LostSouls::VertexArray> m_SquareVA;

	LostSouls::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 2.0f;
	float m_MovementSpeed = 0.1f;
};

class Sandbox : public LostSouls::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

LostSouls::Application* LostSouls::CreateApplication()
{
	return new Sandbox();
}