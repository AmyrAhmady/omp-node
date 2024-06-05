#pragma once
#include "node.h"
#include "v8.h"

namespace helpers
{
	template<typename T>
	using CopyablePersistent = v8::Persistent<T, v8::CopyablePersistentTraits<T>>;
}
