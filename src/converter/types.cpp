#include "types.hpp"
#include "primitive.hpp"

WorldTimePoint JSToWorldTimePoint(v8::Local<v8::Value> value,
                                  v8::Local<v8::Context> context,
                                  const WorldTimePoint &defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    auto msCount = static_cast<long long>(value.As<v8::Date>()->ValueOf());
    auto ms = Milliseconds(msCount);

    return WorldTimePoint(ms);
}

Milliseconds JSToMilliseconds(v8::Local<v8::Value> value,
                              v8::Local<v8::Context> context,
                              const Milliseconds &defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    auto msCount = JSToInt(value, context);
    return Milliseconds(msCount);
}

Seconds JSToSeconds(v8::Local<v8::Value> value, v8::Local<v8::Context> context, const Seconds &defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    auto sCount = JSToInt(value, context);
    return Seconds(sCount);
}

Minutes JSToMinutes(v8::Local<v8::Value> value, v8::Local<v8::Context> context, const Minutes &defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    auto mCount = JSToInt(value, context);
    return Minutes(mCount);
}

Hours JSToHours(v8::Local<v8::Value> value, v8::Local<v8::Context> context, const Hours &defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    auto hCount = JSToInt(value, context);
    return Hours(hCount);
}

Colour JSToColour(v8::Local<v8::Value> value, v8::Local<v8::Context> context, const Colour &defaultValue) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        return defaultValue;
    }

    return Colour::FromRGBA(JSToUInt<uint32_t>(value, context));
}

WorldTimePoint JSToWorldTimePoint(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return WorldTimePoint();
    }

    auto msCount = static_cast<long long>(value.As<v8::Date>()->ValueOf());
    auto ms = Milliseconds(msCount);

    return WorldTimePoint(ms);
}

Milliseconds JSToMilliseconds(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return Milliseconds();
    }

    auto msCount = JSToInt(value, context);
    return Milliseconds(msCount);
}

Seconds JSToSeconds(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return Seconds();
    }

    auto sCount = JSToInt(value, context);
    return Seconds(sCount);
}

Minutes JSToMinutes(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return Minutes();
    }

    auto mCount = JSToInt(value, context);
    return Minutes(mCount);
}

Hours JSToHours(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return Hours();
    }

    auto hCount = JSToInt(value, context);
    return Hours(hCount);
}

GTAQuat JSToGTAQuat(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (!value->IsArray()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An array is required").ToLocalChecked()));
        return GTAQuat();
    }

    auto wHandle = value.As<v8::Array>()->Get(context, 0);
    auto xHandle = value.As<v8::Array>()->Get(context, 1);
    auto yHandle = value.As<v8::Array>()->Get(context, 2);
    auto zHandle = value.As<v8::Array>()->Get(context, 3);

    if (wHandle.IsEmpty() || xHandle.IsEmpty() || yHandle.IsEmpty() || zHandle.IsEmpty()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "An array must contain 4 numbers").ToLocalChecked()));
        return GTAQuat();
    }

    auto w = JSToFloat(wHandle.ToLocalChecked(), context);
    auto x = JSToFloat(xHandle.ToLocalChecked(), context);
    auto y = JSToFloat(yHandle.ToLocalChecked(), context);
    auto z = JSToFloat(zHandle.ToLocalChecked(), context);

    return {
        w,
        x,
        y,
        z
    };
}

Colour JSToColour(v8::Local<v8::Value> value, v8::Local<v8::Context> context) {
    auto isolate = context->GetIsolate();

    if (value->IsUndefined()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate,
                                                                                 "A value is required").ToLocalChecked()));
        return Colour();
    }

    return Colour::FromRGBA(JSToUInt<uint32_t>(value, context));
}

v8::Local<v8::Date> WorldTimePointToJS(const WorldTimePoint &point, v8::Local<v8::Context> context) {
    auto sinceEpoch = point.time_since_epoch();

    auto ms = duration_cast<Milliseconds>(sinceEpoch);

    v8::Local<v8::Date> date = v8::Date::New(context, static_cast<double>(ms.count())).ToLocalChecked().As<v8::Date>();

    return date;
}

v8::Local<v8::Integer> TimePointToJS(const TimePoint &point, v8::Local<v8::Context> context) {
    auto sinceEpoch = point.time_since_epoch();

    auto ms = duration_cast<Milliseconds>(sinceEpoch);

    auto msCount = static_cast<long long>(ms.count());

    return IntToJS<long long>(msCount, context);
}

v8::Local<v8::Integer> MillisecondsToJS(const Milliseconds &ms, v8::Local<v8::Context> context) {
    return IntToJS(ms.count(), context);
}

v8::Local<v8::Integer> SecondsToJS(const Seconds &s, v8::Local<v8::Context> context) {
    return IntToJS(s.count(), context);
}

v8::Local<v8::Integer> MinutesToJS(const Minutes &m, v8::Local<v8::Context> context) {
    return IntToJS(m.count(), context);
}

v8::Local<v8::Integer> HoursToJS(const Hours &h, v8::Local<v8::Context> context) {
    return IntToJS(h.count(), context);
}

v8::Local<v8::Array> HoursMinutesToJS(const HoursMinutes &hoursMinutes, v8::Local<v8::Context> context) {
    v8::EscapableHandleScope handle_scope(context->GetIsolate());

    // Create a new empty array.
    v8::Local<v8::Array> array = v8::Array::New(context->GetIsolate(), 2);

    // Return an empty result if there was an error creating the array.
    if (array.IsEmpty())
        return v8::Local<v8::Array>();

    // Fill out the values
    array->Set(context, 0, IntToJS(hoursMinutes.first.count(), context)).Check();
    array->Set(context, 1, IntToJS(hoursMinutes.second.count(), context)).Check();

    return handle_scope.Escape(array);
}

v8::Local<v8::Array> PairBoolStringViewToJS(const PairBoolStringView &boolStringView, v8::Local<v8::Context> context) {
    v8::EscapableHandleScope handle_scope(context->GetIsolate());

    // Create a new empty array.
    v8::Local<v8::Array> array = v8::Array::New(context->GetIsolate(), 2);

    // Return an empty result if there was an error creating the array.
    if (array.IsEmpty())
        return v8::Local<v8::Array>();

    // Fill out the values
    array->Set(context, 0, BoolToJS(boolStringView.first, context)).Check();
    array->Set(context, 1, StringViewToJS(boolStringView.second, context)).Check();

    return handle_scope.Escape(array);
}

v8::Local<v8::Integer> ColourToJS(const Colour &colour, v8::Local<v8::Context> context) {
    return UIntToJS(colour.RGBA(), context);
}

OBJECT_CONVERTER_DEFINE_TO_JS(SemanticVersion,
                        (uint8_t, major, UIntToJS<uint8_t>, JSToUInt<uint8_t>),
                        (uint8_t, minor, UIntToJS<uint8_t>, JSToUInt<uint8_t>),
                        (uint8_t, patch, UIntToJS<uint8_t>, JSToUInt<uint8_t>),
                        (uint16_t, prerel, UIntToJS<uint16_t>, JSToUInt<uint16_t>))
