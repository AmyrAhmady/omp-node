#pragma once
#include "v8.h"

v8::Local<v8::Value> WrapConfigOptionType(v8::Local<v8::Context> context) {
    auto handle = EnumToObject<ConfigOptionType>({{"ConfigOptionType_None",    ConfigOptionType::ConfigOptionType_None},
                                                  {"ConfigOptionType_Int",     ConfigOptionType::ConfigOptionType_Int},
                                                  {"ConfigOptionType_String",  ConfigOptionType::ConfigOptionType_String},
                                                  {"ConfigOptionType_Float",   ConfigOptionType::ConfigOptionType_Float},
                                                  {"ConfigOptionType_Strings", ConfigOptionType::ConfigOptionType_Strings}},
                                                 context);

    return handle;
}