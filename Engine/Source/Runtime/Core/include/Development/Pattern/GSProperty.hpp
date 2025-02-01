#pragma once
#ifndef ENGINE_GSPROPERTY_INCLUDED
#define ENGINE_GSPROPERTY_INCLUDED

#define READONLY_PROPERTY(Type, lowerCaseFirst, upperCaseFirst, rest, defaultValue) \
private: \
    Type _##lowerCaseFirst##rest {(defaultValue)}; \
public: \
    inline Type Get##upperCaseFirst##rest() const { return _##lowerCaseFirst##rest; };

#endif