#pragma once

#include "Types.h"
#include "BufferLayout.h"

namespace LivingEnd {
	namespace Graphics {
		namespace API {

			struct Buffer
			{
				uint id;
				uint target, usage;
				uint size;
				BufferLayout layout;

				Buffer(uint target, uint usage);
				~Buffer();

				void Resize(uint size);
				void SetData(uint size, const void* data);

				template<typename T>
				T* GetPointer(uint flags = 0x88B9/*GL_WRITE_ONLY*/)
				{
					return (T*)API::GetBufferPointer(target, flags);
				}

				void ReleasePointer();

				void Bind();
				void Unbind();
			};
		}
	}
}