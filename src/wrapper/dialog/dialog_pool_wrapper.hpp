#pragma once
#include "Server/Components/Dialogs/dialogs.hpp"
#include "v8.h"
#include "../utils.hpp"

void WrapDialogPool(IDialogsComponent *dialogPool, v8::Local<v8::Context> context);