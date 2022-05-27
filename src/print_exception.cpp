#include "print_exception.hpp"
#include "logger.hpp"
#include <cstdio>

template<typename ... Args>
std::string string_format(const std::string &format, Args ... args) {
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    if (size_s <= 0) {
        return std::string("Error during formatting.");
    }
    auto size = static_cast<size_t>( size_s );
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

static std::string GetErrorSource(v8::Isolate *isolate,
                                  v8::Local<v8::Context> context,
                                  v8::Local<v8::Message> message,
                                  bool *added_exception_line) {
    v8::MaybeLocal<v8::String> source_line_maybe = message->GetSourceLine(context);
    v8::String::Utf8Value encoded_source(isolate, source_line_maybe.ToLocalChecked());
    std::string sourceline(*encoded_source, encoded_source.length());
    *added_exception_line = false;

    // If source maps have been enabled, the exception line will instead be
    // added in the JavaScript context:
    node::Environment *env = node::GetCurrentEnvironment(context);
    const bool has_source_map_url = !message->GetScriptOrigin().SourceMapUrl().IsEmpty();
    if (has_source_map_url && env != nullptr && env->source_maps_enabled()) {
        return sourceline;
    }

    if (sourceline.find("node-do-not-add-exception-line") != std::string::npos) {
        return sourceline;
    }

    // Because of how node modules work, all scripts are wrapped with a
    // "function (module, exports, __filename, ...) {"
    // to provide script local variables.
    //
    // When reporting errors on the first line of a script, this wrapper
    // function is leaked to the user. There used to be a hack here to
    // truncate off the first 62 characters, but it caused numerous other
    // problems when vm.runIn*Context() methods were used for non-module
    // code.
    //
    // If we ever decide to re-instate such a hack, the following steps
    // must be taken:
    //
    // 1. Pass a flag around to say "this code was wrapped"
    // 2. Update the stack frame output so that it is also correct.
    //
    // It would probably be simpler to add a line rather than add some
    // number of characters to the first line, since V8 truncates the
    // sourceline to 78 characters, and we end up not providing very much
    // useful debugging info to the user if we remove 62 characters.

    // Print (filename):(line number): (message).
    v8::ScriptOrigin origin = message->GetScriptOrigin();
    v8::String::Utf8Value filename(isolate, message->GetScriptResourceName());
    const char *filename_string = *filename;
    int linenum = message->GetLineNumber(context).FromJust();

    int script_start = (linenum - origin.LineOffset()) == 1 ? origin.ColumnOffset() : 0;
    int start = message->GetStartColumn(context).FromMaybe(0);
    int end = message->GetEndColumn(context).FromMaybe(0);
    if (start >= script_start) {
        start -= script_start;
        end -= script_start;
    }

    std::string buf = string_format("%s:%i\n%s\n", filename_string, linenum, sourceline.c_str());
    *added_exception_line = true;

    if (start > end || start < 0 || static_cast<size_t>(end) > sourceline.size()) {
        return buf;
    }

    constexpr int kUnderlineBufsize = 1020;
    char underline_buf[kUnderlineBufsize + 4];
    int off = 0;
    // Print wavy underline (GetUnderline is deprecated).
    for (int i = 0; i < start; i++) {
        if (sourceline[i] == '\0' || off >= kUnderlineBufsize) {
            break;
        }
        underline_buf[off++] = (sourceline[i] == '\t') ? '\t' : ' ';
    }
    for (int i = start; i < end; i++) {
        if (sourceline[i] == '\0' || off >= kUnderlineBufsize) {
            break;
        }
        underline_buf[off++] = '^';
    }
    underline_buf[off++] = '\n';

    return buf + std::string(underline_buf, off);
}

void PrintStackTrace(v8::Isolate *isolate, v8::Local<v8::StackTrace> stack) {
    for (int i = 0; i < stack->GetFrameCount(); i++) {
        v8::Local<v8::StackFrame> stack_frame = stack->GetFrame(isolate, i);
        v8::String::Utf8Value fn_name_s(isolate, stack_frame->GetFunctionName());
        v8::String::Utf8Value script_name(isolate, stack_frame->GetScriptName());
        const int line_number = stack_frame->GetLineNumber();
        const int column = stack_frame->GetColumn();

        if (stack_frame->IsEval()) {
            if (stack_frame->GetScriptId() == v8::Message::kNoScriptIdInfo) {
                fprintf(stderr, "    at [eval]:%i:%i\n", line_number, column);
            } else {
                fprintf(stderr, "    at [eval] (%s:%i:%i)\n", *script_name, line_number, column);
            }
            break;
        }

        if (fn_name_s.length() == 0) {
            fprintf(stderr, "    at %s:%i:%i\n", *script_name, line_number, column);
        } else {
            fprintf(stderr, "    at %s (%s:%i:%i)\n", *fn_name_s, *script_name, line_number, column);
        }
    }
    fflush(stderr);
}

void PrintException(v8::Isolate *isolate,
                    v8::Local<v8::Context> context,
                    v8::Local<v8::Value> err,
                    v8::Local<v8::Message> message) {
    v8::String::Utf8Value reason(isolate, err->ToDetailString(context).FromMaybe(v8::Local<v8::String>()));
    bool added_exception_line = false;
    std::string source = GetErrorSource(isolate, context, message, &added_exception_line);
    fprintf(stderr, "%s\n", source.c_str());
    fprintf(stderr, "%s\n", *reason);

    v8::Local<v8::StackTrace> stack = message->GetStackTrace();
    if (!stack.IsEmpty())
        PrintStackTrace(isolate, stack);
}
