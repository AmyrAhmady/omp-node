#pragma once

#include "node.h"
#include "uv.h"

#include <sdk.hpp>

#include "helpers/v8.hpp"
#include "logger.hpp"

enum class ConfigVersion
{
	None,
	Version1,
	Unknown
};

struct ResourceInfo
{
	Impl::String name;
	Impl::String path;
	Impl::String entryFile;
	ConfigVersion configVersion;
};
