#ifndef ENGINE_SERIALIZABLE_INCLUDED
#define ENGINE_SERIALIZABLE_INCLUDED

#include <type_traits>
// #include <utility>
#include <fstream>
#include <filesystem>

#include <Development/Assert/Assert.hpp>
#include <Development/Log/Log.hpp>

namespace Engine {

/* Depracated
template<typename _Type>
struct FReflectionVariableFieldInfo {
    size_t offset;
    size_t size;
};


class Serializable {
private:
    // No exception (or assert, during compilation) check, to be added
    inline void _SingleSerializer(std::ostream& os, const char* obj, size_t size) const {
        os.write(obj, size);
    }
    inline void _SingleDeserializer(std::istream& is, char* obj, size_t size) const {
        is.read(obj, size);
    }
protected:
    virtual const std::vector<std::pair<std::string, FReflectionVariableFieldInfo>>& GetFieldsMap() const = 0;
public:
    void Serialize(std::ofstream& os) const {
        for (auto& kv : GetFieldsMap()) {
            const auto& fieldName = kv.first;
            _SingleSerializer(os, reinterpret_cast<const char*>(this) + kv.second.offset, kv.second.size);
        }
    }
    void Deserialize(std::ifstream& is)  {
        for (auto& kv : GetFieldsMap()) {
            const auto& fieldName = kv.first;
            _SingleDeserializer(is, reinterpret_cast<char*>(this) + kv.second.offset, kv.second.size);
        }
    }
};

// Temporary: public for testing
#define SERIALIZATION_START(iClassName) \
public: \
    inline static std::vector<std::pair<std::string, FReflectionVariableFieldInfo>> fieldsMap {}; \
protected: \
    inline std::vector<std::pair<std::string, FReflectionVariableFieldInfo>>& GetFieldsMap() const override {return fieldsMap;} \
public:                                                                               \
    static void ConfigureSerialization() {                                                             \
        fieldsMap.clear(); \
        using ClassName = iClassName;

#define SERIALIZATION_ADD_FUNDAMENTAL(member)                                                        \
        fieldsMap.push_back({                                                         \
            #member,                                                                  \
            FReflectionVariableFieldInfo{                                                                \
                offsetof(ClassName, member),                                          \
                sizeof(decltype(std::declval<ClassName>().member))                      \
            }                                                                         \
        });

#define SERIALIZATION_ADD_ARRAY(sizeMember, pointerMember) \
        static_assert(std::is_integral<decltype(std::declval<ClassName>().sizeMember)>::value, "Array size must be an integral"); \
        fieldsMap.push_back({ \
            #sizeMember, \
            FReflectionVariableFieldInfo{ \
                offsetof(ClassName, sizeMember), \
                sizeof(decltype(std::declval<ClassName>().sizeMember)) \
            } \
        }); \
        fieldsMap.push_back({                                                                \
            #pointerMember,                                                                        \
            FReflectionVariableFieldInfo{                                                                      \
                offsetof(ClassName, pointerMember),                                                 \
                size_t(sizeMember) * sizeof(std::remove_pointer_t<decltype(std::declval<ClassName>().pointerMember)>) \
            } \
        });

#define SERIALIZATION_END()                                                                   \
    }
*/


// Temporary: public for testing
#define SERIALIZATION_START() \
public: \
    template<bool bIsSerialize> \
    inline bool Serialize(std::filesystem::path path) { \
        if constexpr (!bIsSerialize) if (!std::filesystem::exists(path)) \
            return PRINT_ERROR("Serializable::Serialize: File does not exist", bIsSerialize), false; \
        typename std::conditional<bIsSerialize, std::ofstream, std::ifstream>::type fs; \
        fs.open(path.string().c_str(), std::ios::binary); \
        if (!fs.is_open()) \
            return PRINT_ERROR("Serializable::Serialize: File could not be opened", bIsSerialize), false;
#define SERIALIZATION_ADD_FUNDAMENTAL(member) \
        if constexpr (bIsSerialize) \
            fs.write(reinterpret_cast<const char*>(&member), sizeof(member)); \
        else \
            fs.read(reinterpret_cast<char*>(&member), sizeof(member));
#define SERIALIZATION_ADD_ARRAY(sizeMember, pointerMember) \
        STATIC_ASSERT(std::is_integral<decltype(sizeMember)>::value, "SERIALIZATION_ADD_ARRAY: Array size must be an integral"); \
        if constexpr (bIsSerialize) \
            fs.write(reinterpret_cast<const char*>(&sizeMember), sizeof(sizeMember)),\
            fs.write(reinterpret_cast<const char*>(pointerMember), sizeMember * sizeof(std::remove_pointer_t<decltype(pointerMember)>)); \
        else \
            fs.read(reinterpret_cast<char*>(&sizeMember), sizeof(sizeMember)), \
            DYNAMIC_ASSERT(pointerMember == nullptr, "SERIALIZATION_ADD_ARRAY: Array pointer must be null"), \
            pointerMember = new std::remove_pointer_t<decltype(pointerMember)>[sizeMember], \
            fs.read(reinterpret_cast<char*>(pointerMember), sizeMember * sizeof(std::remove_pointer_t<decltype(pointerMember)>));
// size in bytes
#define SERIALIZATION_ADD_PLACEHOLDER(size) \
        if constexpr (bIsSerialize) \
            fs.write(reinterpret_cast<const char*>(nullptr), size); \
        else \
            fs.read(reinterpret_cast<char*>(nullptr), size);
#define SERIALIZATION_END() \
        return true; \
    }
}
#endif // ENGINE_SERIALIZABLE_INCLUDED
