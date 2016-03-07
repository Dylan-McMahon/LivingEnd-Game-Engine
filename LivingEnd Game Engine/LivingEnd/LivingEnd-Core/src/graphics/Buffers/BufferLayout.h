#pragma once

#include <string>
#include <vector>
#include <cstddef>
#include ".\Types.h"
#include "glm\glm\ext.hpp"
#include "gl_core_4_4.h"

namespace LivingEnd {
	namespace Graphics {

		struct BufferLayoutType
		{
			std::string name;
			uint type;
			uint size;
			uint count;
			uint offset;
			bool normalized;
		};

		class BufferLayout 
		{
		public:
			BufferLayout();

			template<typename T>
			void Push(const std::string& name, uint count = 1, bool normalized = false)
			{
				_ASSERT_EXPR(false, "Unkown type!");
			}

			template<> void Push<float>(const std::string& name, uint count, bool normalized) { Push(name, GL_FLOAT, sizeof(float) * count, count, normalized); }
			template<> void Push<uint>(const std::string& name, uint count, bool normalized) { Push(name, GL_UNSIGNED_INT, sizeof(uint) * count, count, normalized); }
			template<> void Push<byte>(const std::string& name, uint count, bool normalized) { Push(name, GL_UNSIGNED_BYTE, sizeof(byte) * count, count, normalized); }
			template<> void Push<glm::vec2>(const std::string& name, uint count, bool normalized) { Push(name, GL_FLOAT, sizeof(glm::vec2) * count, 2 * count, normalized); }
			template<> void Push<glm::vec3>(const std::string& name, uint count, bool normalized) { Push(name, GL_FLOAT, sizeof(glm::vec3) * count, 3 * count, normalized); }
			template<> void Push<glm::vec4>(const std::string& name, uint count, bool normalized) { Push(name, GL_FLOAT, sizeof(glm::vec4) * count, 4 * count, normalized); }

			inline const std::vector<BufferLayoutType>& GetLayout() const { return m_Layout; }
			inline uint GetStride() const { return m_Size; }
		private:
			uint m_Size;
			std::vector<BufferLayoutType> m_Layout;
			void Push(const std::string& name, uint type, uint size, uint count, bool normalized);
		};
	}
}