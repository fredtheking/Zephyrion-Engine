#pragma once

#define REF(TYPE) TYPE&
#define CREF(TYPE) const REF(TYPE)
#define VOID_FUNC std::function<void()>
#define VOID_FUNC_CONST CREF(VOID_FUNC)

#define SINGLETON_CONSTRUCTOR(NAME) private:                                  \
                                      NAME() = default;                       \
                                    public:                                   \
                                      NAME(CREF(NAME)) = delete;             \
                                      REF(NAME) operator=(CREF(NAME)) = delete;  \
                                      static REF(NAME) Get() {               \
                                        static NAME singleton;                \
                                        return singleton;                     \
                                      }

#define EXTEND_I(NAME) public Interfaces::I##NAME
#define LOG_AND_RETURN(MSG, ...) { \
                                   std::cout << MSG << '\n'; \
                                   return __VA_ARGS__; \
                                 }

namespace Cobalt::Low {
  #define POS_N_NEG_ACTION_BASE(PREFIX_POS, PREFIX_NEG, NAME, TYPE, VAR) void PREFIX_POS##NAME(CREF(TYPE) VAR); \
                                                                         void PREFIX_NEG##NAME(CREF(TYPE) VAR);
}

#define ADD_N_REMOVE(NAME, TYPE, VAR) POS_N_NEG_ACTION_BASE(Add, Remove, NAME, TYPE, VAR)
#define REG_N_UNREG(NAME, TYPE, VAR) POS_N_NEG_ACTION_BASE(Register, Unregister, NAME, TYPE, VAR)
#define LINK_N_DETACH(NAME, TYPE, VAR) POS_N_NEG_ACTION_BASE(Link, Detach, NAME, TYPE, VAR)

#define PREFIX_GETTER_ARGS(PREFIX, NAME, TYPE, ...) TYPE PREFIX##Get##NAME(__VA_ARGS__);
#define PREFIX_GETTER(PREFIX, NAME, TYPE) PREFIX_GETTER_ARGS(PREFIX, NAME, TYPE)
#define TRYGETTER(NAME, TYPE) template<typename T> \
                              bool TryGet##NAME(REF(TYPE) out);
#define T_GETTER(NAME, TYPE) template<typename T> \
                             TYPE Get##NAME();
#define GETTER(NAME, TYPE) PREFIX_GETTER( , NAME, TYPE)
#define SETTER(NAME, TYPE, VAR) void Set##NAME(CREF(TYPE) VAR);
#define GETTER_N_SETTER(NAME, TYPE, VAR) GETTER(NAME, TYPE) SETTER(NAME, TYPE, VAR)
#define GETTER_N_SETTER_DEFAULT(NAME, TYPE, VAR) TYPE Get##NAME(){return this->VAR;} \
                                                 void Set##NAME(CREF(TYPE) VAR){this->VAR = VAR;}

#define INFINITE_FLOATING(TYPE) std::numeric_limits<TYPE>::infinity()
#define NONVALID_FLOAT -INFINITE_FLOATING(float)

#define GET_APP_SINGLETON Cobalt::App::Get()
#define DEFINE_APP_VARIABLE REF(auto) app = GET_APP_SINGLETON;