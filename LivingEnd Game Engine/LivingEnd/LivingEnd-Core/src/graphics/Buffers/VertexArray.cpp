#include "VertexArray.h"

namespace LivingEnd {
	namespace Graphics {

		uint VertexArray::s_CurrentBinding = 0;

		VertexArray::VertexArray()
		{
			m_ID = API::CreateVertexArray();
		}

		VertexArray::~VertexArray()
		{
			for (uint i = 0; i < m_Buffers.size(); i++)
				delete m_Buffers[i];

			API::FreeVertexArray(m_ID);
		}


		API::Buffer* VertexArray::GetBuffer(uint index)
		{
			return m_Buffers[index];
		}

		void VertexArray::PushBuffer(API::Buffer* buffer)
		{
#ifdef LivingEnd_DEBUG
			_ASSERT(s_CurrentBinding == m_ID);
#endif
			m_Buffers.push_back(buffer);

			const std::vector<BufferLayoutType>& layout = buffer->layout.GetLayout();
			for (uint i = 0; i < layout.size(); i++)
			{
				API::EnableVertexAttribute(i);
				API::SetVertexAttributePointer(i, layout[i].count, layout[i].type, layout[i].normalized, buffer->layout.GetStride(), layout[i].offset);
			}
		}

		void VertexArray::Bind() const
		{
#ifdef LivingEnd_DEBUG
			s_CurrentBinding = m_ID;
#endif
			API::BindVertexArray(m_ID);
		}

		void VertexArray::Unbind() const
		{
#ifdef LivingEnd_DEBUG
			s_CurrentBinding = 0;
#endif
			API::UnbindVertexArrays();
		}

		void VertexArray::Draw(uint count) const
		{
			API::DrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);
		}
	}
}

