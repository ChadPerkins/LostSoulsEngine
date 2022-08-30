#include "lspch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace LostSouls {
	
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		// Make sure the view projection matrix gets set so its not just an identity matrix
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	void OrthographicCamera::RecalculateViewMatrix()
	{
		// Transformation matrix (position * rotation):
		// Create an identity matrix to translate the m_Position vector to a matrix
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			// Then multiply it by a rotation matrix created from the m_Rotation 
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		// Set the view matrix to be the inverse matrix of the transformation matrix
		m_ViewMatrix = glm::inverse(transform);
		// Create the view projection matrix by multiplying the view and the projection matrix.
		// (note: OpenGL requires the matrix to be multiplied in projection * view order)
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}