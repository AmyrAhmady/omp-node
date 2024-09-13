#pragma once

#include "node.h"
#include "uv.h"

#include <sdk.hpp>

#include "helpers/v8.hpp"
#include "omp-node.hpp"

enum class ConfigVersion
{
	Unknown,
	Version1
};

struct ResourceInfo
{
	Impl::String name;
	Impl::String path;
	Impl::String entryFile;
	ConfigVersion configVersion;
};
