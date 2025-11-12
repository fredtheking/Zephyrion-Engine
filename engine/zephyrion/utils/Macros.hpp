#pragma once

#define REF(...) __VA_ARGS__&
#define CREF(...) const REF(__VA_ARGS__)

#define UPTR(TYPE) std::unique_ptr<TYPE>
#define MAKE_UPTR(TYPE) std::make_unique<TYPE>
#define SPTR(TYPE) std::shared_ptr<TYPE>
#define MAKE_SPTR(TYPE) std::make_shared<TYPE>
#define WPTR(TYPE) std::weak_ptr<TYPE>

#define U(TYPE) unsigned TYPE
#define Z_UINT8 U(char)
#define Z_UINT16 U(short)
#define Z_UINT32 U(int)
#define Z_UINT64 U(long long)

#define C_STR const char*
#define STR std::string
#define VEC(TYPE) std::vector<TYPE>
#define ST_BOUNDS(TYPE) ZE::ST::Bounds<TYPE>
#define ST_REC(TYPE) ZE::ST::Rectangle<TYPE>
#define ST_VEC2(TYPE) ZE::ST::Vector2<TYPE>

#define NULLOPT std::nullopt
#define OPT(TYPE) std::optional<TYPE>
#define MAKE_OPT(TYPE) std::make_optional<TYPE>

#define VAR(...) std::variant<__VA_ARGS__>
#define CALL_VAR(VAR, METHOD_NAME, ...) std::visit([](auto& r){ r.METHOD_NAME(__VA_ARGS__); }, VAR);


#define FUNC(RETURN) std::function<RETURN>
#define VOID_FUNC FUNC(void())
#define VOID_FUNC_CONST CREF(VOID_FUNC)


#define SINGLETON_CONSTRUCTOR(NAME)    \
private:                                \
  NAME() = default;                      \
public:                                   \
  NAME(CREF(NAME)) = delete;               \
  REF(NAME) operator=(CREF(NAME)) = delete; \
  static REF(NAME) Get() {                   \
    static NAME singleton;                    \
    return singleton;                          \
  }
#define STATIC_ONLY_CONSTRUCTOR(NAME)   \
public:                                  \
  NAME() = delete;                        \
  NAME(CREF(NAME)) = delete;               \
  REF(NAME) operator=(CREF(NAME)) = delete; \


#define POS_N_NEG_ACTION_BASE(PREFIX_POS, PREFIX_NEG, NAME, TYPE, VAR) void PREFIX_POS##NAME(CREF(TYPE) VAR); \
                                                                       void PREFIX_NEG##NAME(CREF(TYPE) VAR);
#define ADD_N_REMOVE(NAME, TYPE, VAR) POS_N_NEG_ACTION_BASE(Add, Remove, NAME, TYPE, VAR)
#define REG_N_UNREG(NAME, TYPE, VAR) POS_N_NEG_ACTION_BASE(Register, Unregister, NAME, TYPE, VAR)
#define LINK_N_DETACH(NAME, TYPE, VAR) POS_N_NEG_ACTION_BASE(Link, Detach, NAME, TYPE, VAR)

#define PREFIX_GETTER_ARGS(PREFIX, NAME, TYPE, ...) TYPE PREFIX##Get##NAME(__VA_ARGS__) const
#define PREFIX_GETTER(PREFIX, NAME, TYPE) PREFIX_GETTER_ARGS(PREFIX, NAME, TYPE)
#define TRYGETTER(NAME, TYPE) template<typename T> \
                              bool TryGet##NAME(REF(TYPE) out)
#define T_GETTER(NAME, TYPE) template<typename T> \
                             TYPE Get##NAME()
#define GETTER(NAME, TYPE) PREFIX_GETTER( , NAME, TYPE)
#define SETTER(NAME, TYPE, VAR) void Set##NAME(CREF(TYPE) VAR);
#define GETTER_N_SETTER(NAME, TYPE, VAR) GETTER(NAME, TYPE) SETTER(NAME, TYPE, VAR)
#define GETTER_N_SETTER_DEFAULT(NAME, TYPE, VAR, ...) TYPE Get##NAME() { return this->VAR; } \
                                                 void Set##NAME(TYPE VAR) { this->VAR = VAR; __VA_ARGS__ }

#define INFINITE_FLOATING(TYPE) std::numeric_limits<TYPE>::infinity()
#define NONVALID_FLOAT -INFINITE_FLOATING(float)
#define NONVALID_INT INT_MIN
#define NONVALID_ST_VEC2 ST_VEC2(int){NONVALID_INT}

#define GET_APP_SINGLETON ZE::App::Get()
#define DEFINE_APP_VARIABLE REF(auto) app = GET_APP_SINGLETON;
#define GET_IMIO_SINGLETON ImGui::GetIO()
#define DEFINE_IMIO_VARIABLE REF(ImGuiIO) io = GET_IMIO_SINGLETON;
#define ENGINE_ASSETS "res/engine/"

#define BACKEND_CALL(BACKEND_ENUMVAR, FUNC_GL, FUNC_VK, FUNC_MTL) \
switch (BACKEND_ENUMVAR) {                                         \
  case ZE::Enums::ZE_BackendRenderer::OpenGL:                       \
    FUNC_GL; break;                                                  \
  case ZE::Enums::ZE_BackendRenderer::Vulkan:                         \
    FUNC_VK; break;                                                    \
  case ZE::Enums::ZE_BackendRenderer::Metal:                            \
    FUNC_MTL; break;                                                     \
}
#define RENDERER_HANDLER_TEMPLATE \
template <typename T>      \
requires std::derived_from<T, ZE::Low::RendererBase>

#ifdef Z_SHOW_INTERNALS
  #define INTERNAL_GUARD_BEGIN public:
  #define INTERNAL_GUARD_END private:
#else
  #define INTERNAL_GUARD_BEGIN private:
  #define INTERNAL_GUARD_END
#endif