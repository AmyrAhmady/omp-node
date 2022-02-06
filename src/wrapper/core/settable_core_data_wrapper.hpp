#pragma once
#include "v8.h"

v8::Local<v8::Value> WrapSettableCoreData(v8::Local<v8::Context> context) {
    auto handle = EnumToObject<SettableCoreDataType>({{"ServerName",    SettableCoreDataType::ServerName},
                                                      {"ModeText",      SettableCoreDataType::ModeText},
                                                      {"MapName",       SettableCoreDataType::MapName},
                                                      {"Language",      SettableCoreDataType::Language},
                                                      {"URL",           SettableCoreDataType::URL},
                                                      {"Password",      SettableCoreDataType::Password},
                                                      {"AdminPassword", SettableCoreDataType::AdminPassword},
                                                     }, context);

    return handle;
}