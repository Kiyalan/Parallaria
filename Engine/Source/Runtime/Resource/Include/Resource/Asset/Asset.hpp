#ifndef ENGINE_ASSET_INCLUDED
#define ENGINE_ASSET_INCLUDED

// Unable to forward declare 'rapidjson::Value'
// namespace rapidjson {
// 	template <typename Encoding, typename Allocator>
// 	class GenericValue;
// 	template <typename CharType>
// 	struct UTF8;
// 	typedef GenericValue<UTF8<char> > Value;
// }
#include <rapidjson/document.h>

namespace Engine {
using FAssetFileContext = rapidjson::Value;
}

#endif // ENGINE_ASSET_INCLUDED