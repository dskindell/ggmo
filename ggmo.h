/** @file ggmo.h
 *  @brief Defines the Global GoogleMock Object API
 *
 *  @see https://bitbucket.org/dskindell/ggmo/overview
 *
 *  @author David Skindell (dskindell)
 */
#ifndef GGMO_H_
#define GGMO_H_

#define MOCK_GLOBAL_FUNC_T(func) Mock_##func
#define GMO(func) _mock_##func
#define GMO_EXPECT_CALL(name, params) EXPECT_CALL(GMO(name), name params)
#define GMO_ON_CALL(name, params) ON_CALL(GMO(name), name params)

#define DECL_GLOBAL_FUNC_MOCK(func)        Mock_##func             _mock_##func
#define DECL_NICE_GLOBAL_FUNC_MOCK(func)   NiceMock<Mock_##func>   _mock_##func
#define DECL_STRICT_GLOBAL_FUNC_MOCK(func) StrictMock<Mock_##func> _mock_##func

template <class T>
class GMOSingletonMock
{
public:
   static T * pInstance;
   static T * get();
   virtual ~GMOSingletonMock() {}
   virtual std::string Name() const = 0;
};

template <class T>
T * GMOSingletonMock<T>::pInstance = 0;

template <class T>
T *
GMOSingletonMock<T>::
get()
{
   if (!pInstance)
   {
      pInstance = new T();
      std::cerr << "Warning! Instantiated mock object <" << pInstance->Name() << "> outside of test fixture\n";
   }
   return pInstance;
}

#define _MOCK_GLOBAL_OBJ0(rtn_t, name) \
class MOCK_GLOBAL_FUNC_T(name) : public GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)> { \
   void initialize(); \
   public: \
      virtual std::string Name() const { return std::string(#name); } \
      MOCK_GLOBAL_FUNC_T(name)() { MOCK_GLOBAL_FUNC_T(name)::pInstance = this; initialize(); } \
      virtual ~MOCK_GLOBAL_FUNC_T(name)() {} \
      MOCK_METHOD0(name, rtn_t()); \
}; \
rtn_t name()

#define MOCK_GLOBAL_OBJ0(rtn_t, name) \
   _MOCK_GLOBAL_OBJ0(rtn_t, name) { return GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)>::get()->name(); } \
   void MOCK_GLOBAL_FUNC_T(name)::initialize()

#define MOCK_GLOBAL_VOID_OBJ0(name) \
   _MOCK_GLOBAL_OBJ0(void, name) { GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)>::get()->name(); } \
   void MOCK_GLOBAL_FUNC_T(name)::initialize()

#define _MOCK_GLOBAL_OBJ1(rtn_t, name, arg0_t) \
class MOCK_GLOBAL_FUNC_T(name) : public GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)> { \
   void initialize(); \
   public: \
      virtual std::string Name() const { return std::string(#name); } \
      MOCK_GLOBAL_FUNC_T(name)() { MOCK_GLOBAL_FUNC_T(name)::pInstance = this; initialize(); } \
      virtual ~MOCK_GLOBAL_FUNC_T(name)() {} \
      MOCK_METHOD1(name, rtn_t(arg0_t arg0)); \
}; \
rtn_t name(arg0_t arg0)

#define MOCK_GLOBAL_OBJ1(rtn_t, name, arg0_t) \
   _MOCK_GLOBAL_OBJ1(rtn_t, name, arg0_t) { return GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)>::get()->name(arg0); } \
   void MOCK_GLOBAL_FUNC_T(name)::initialize()

#define MOCK_GLOBAL_VOID_OBJ1(name, arg0_t) \
   _MOCK_GLOBAL_OBJ1(void, name, arg0_t) { GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)>::get()->name(arg0); } \
   void MOCK_GLOBAL_FUNC_T(name)::initialize()

#define _MOCK_GLOBAL_OBJ2(rtn_t, name, arg0_t, arg1_t) \
class MOCK_GLOBAL_FUNC_T(name) : public GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)> { \
   void initialize(); \
   public: \
      virtual std::string Name() const { return std::string(#name); } \
      MOCK_GLOBAL_FUNC_T(name)() { MOCK_GLOBAL_FUNC_T(name)::pInstance = this; initialize(); } \
      virtual ~MOCK_GLOBAL_FUNC_T(name)() {} \
      MOCK_METHOD2(name, rtn_t(arg0_t arg0, arg1_t arg1)); \
}; \
rtn_t name(arg0_t arg0, arg1_t arg1)

#define MOCK_GLOBAL_OBJ2(rtn_t, name, arg0_t, arg1_t) \
   _MOCK_GLOBAL_OBJ2(rtn_t, name, arg0_t, arg1_t) { return GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)>::get()->name(arg0, arg1); } \
   void MOCK_GLOBAL_FUNC_T(name)::initialize()

#define MOCK_GLOBAL_VOID_OBJ2(name, arg0_t, arg1_t) \
   _MOCK_GLOBAL_OBJ2(void, name, arg0_t, arg1_t) { GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)>::get()->name(arg0, arg1); } \
   void MOCK_GLOBAL_FUNC_T(name)::initialize()

#define _MOCK_GLOBAL_OBJ3(rtn_t, name, arg0_t, arg1_t, arg2_t) \
class MOCK_GLOBAL_FUNC_T(name) : public GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)> { \
   void initialize(); \
   public: \
      virtual std::string Name() const { return std::string(#name); } \
      MOCK_GLOBAL_FUNC_T(name)() { MOCK_GLOBAL_FUNC_T(name)::pInstance = this; initialize(); } \
      virtual ~MOCK_GLOBAL_FUNC_T(name)() {} \
      MOCK_METHOD3(name, rtn_t(arg0_t arg0, arg1_t arg1, arg2_t arg2)); \
}; \
rtn_t name(arg0_t arg0, arg1_t arg1, arg2_t arg2)

#define MOCK_GLOBAL_OBJ3(rtn_t, name, arg0_t, arg1_t, arg2_t) \
   _MOCK_GLOBAL_OBJ3(rtn_t, name, arg0_t, arg1_t, arg2_t) { return GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)>::get()->name(arg0, arg1, arg2); } \
   void MOCK_GLOBAL_FUNC_T(name)::initialize()

#define MOCK_GLOBAL_VOID_OBJ3(name, arg0_t, arg1_t, arg2_t) \
   _MOCK_GLOBAL_OBJ3(void, name, arg0_t, arg1_t, arg2_t) { GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)>::get()->name(arg0, arg1, arg2); } \
   void MOCK_GLOBAL_FUNC_T(name)::initialize()

#define _MOCK_GLOBAL_OBJ4(rtn_t, name, arg0_t, arg1_t, arg2_t, arg3_t) \
class MOCK_GLOBAL_FUNC_T(name) : public GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)> { \
   void initialize(); \
   public: \
      virtual std::string Name() const { return std::string(#name); } \
      MOCK_GLOBAL_FUNC_T(name)() { MOCK_GLOBAL_FUNC_T(name)::pInstance = this; initialize(); } \
      virtual ~MOCK_GLOBAL_FUNC_T(name)() {} \
      MOCK_METHOD4(name, rtn_t(arg0_t arg0, arg1_t arg1, arg2_t arg2, arg3_t arg3)); \
}; \
rtn_t name(arg0_t arg0, arg1_t arg1, arg2_t arg2, arg3_t arg3)

#define MOCK_GLOBAL_OBJ4(rtn_t, name, arg0_t, arg1_t, arg2_t, arg3_t) \
   _MOCK_GLOBAL_OBJ4(rtn_t, name, arg0_t, arg1_t, arg2_t, arg3_t) { return GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)>::get()->name(arg0, arg1, arg2, arg3); } \
   void MOCK_GLOBAL_FUNC_T(name)::initialize()

#define MOCK_GLOBAL_VOID_OBJ4(name, arg0_t, arg1_t, arg2_t, arg3_t) \
   _MOCK_GLOBAL_OBJ4(void, name, arg0_t, arg1_t, arg2_t, arg3_t) { GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)>::get()->name(arg0, arg1, arg2, arg3); } \
   void MOCK_GLOBAL_FUNC_T(name)::initialize()

#define _MOCK_GLOBAL_OBJ5(rtn_t, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t) \
class MOCK_GLOBAL_FUNC_T(name) : public GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)> { \
   void initialize(); \
   public: \
      virtual std::string Name() const { return std::string(#name); } \
      MOCK_GLOBAL_FUNC_T(name)() { MOCK_GLOBAL_FUNC_T(name)::pInstance = this; initialize(); } \
      virtual ~MOCK_GLOBAL_FUNC_T(name)() {} \
      MOCK_METHOD5(name, rtn_t(arg0_t arg0, arg1_t arg1, arg2_t arg2, arg3_t arg3, arg4_t arg4)); \
}; \
rtn_t name(arg0_t arg0, arg1_t arg1, arg2_t arg2, arg3_t arg3, arg4_t arg4)

#define MOCK_GLOBAL_OBJ5(rtn_t, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t) \
   _MOCK_GLOBAL_OBJ5(rtn_t, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t) { return GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)>::get()->name(arg0, arg1, arg2, arg3, arg4); } \
   void MOCK_GLOBAL_FUNC_T(name)::initialize()

#define MOCK_GLOBAL_VOID_OBJ5(rtn_t, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t) \
   _MOCK_GLOBAL_OBJ5(void, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t) { GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)>::get()->name(arg0, arg1, arg2, arg3, arg4); } \
   void MOCK_GLOBAL_FUNC_T(name)::initialize()

#define _MOCK_GLOBAL_OBJ6(rtn_t, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t) \
class MOCK_GLOBAL_FUNC_T(name) : public GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)> { \
   void initialize(); \
   public: \
      virtual std::string Name() const { return std::string(#name); } \
      MOCK_GLOBAL_FUNC_T(name)() { MOCK_GLOBAL_FUNC_T(name)::pInstance = this; initialize(); } \
      virtual ~MOCK_GLOBAL_FUNC_T(name)() {} \
      MOCK_METHOD6(name, rtn_t(arg0_t arg0, arg1_t arg1, arg2_t arg2, arg3_t arg3, arg4_t arg4, arg5_t arg5)); \
}; \
rtn_t name(arg0_t arg0, arg1_t arg1, arg2_t arg2, arg3_t arg3, arg4_t arg4, arg5_t arg5)

#define MOCK_GLOBAL_OBJ6(rtn_t, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t) \
   _MOCK_GLOBAL_OBJ6(rtn_t, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t) { return GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)>::get()->name(arg0, arg1, arg2, arg3, arg4, arg5); } \
   void MOCK_GLOBAL_FUNC_T(name)::initialize()

#define MOCK_GLOBAL_VOID_OBJ6(name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t) \
   _MOCK_GLOBAL_OBJ6(void, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t) { GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)>::get()->name(arg0, arg1, arg2, arg3, arg4, arg5); } \
   void MOCK_GLOBAL_FUNC_T(name)::initialize()

#define _MOCK_GLOBAL_OBJ7(rtn_t, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t) \
class MOCK_GLOBAL_FUNC_T(name) : public GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)> { \
   void initialize(); \
   public: \
      virtual std::string Name() const { return std::string(#name); } \
      MOCK_GLOBAL_FUNC_T(name)() { MOCK_GLOBAL_FUNC_T(name)::pInstance = this; initialize(); } \
      virtual ~MOCK_GLOBAL_FUNC_T(name)() {} \
      MOCK_METHOD7(name, rtn_t(arg0_t arg0, arg1_t arg1, arg2_t arg2, arg3_t arg3, arg4_t arg4, arg5_t arg5, arg6_t arg6)); \
}; \
rtn_t name(arg0_t arg0, arg1_t arg1, arg2_t arg2, arg3_t arg3, arg4_t arg4, arg5_t arg5, arg6_t arg6)

#define MOCK_GLOBAL_OBJ7(rtn_t, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t) \
   _MOCK_GLOBAL_OBJ7(rtn_t, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t) { return GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)>::get()->name(arg0, arg1, arg2, arg3, arg4, arg5, arg6); } \
   void MOCK_GLOBAL_FUNC_T(name)::initialize()

#define MOCK_GLOBAL_VOID_OBJ7(name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t) \
   _MOCK_GLOBAL_OBJ7(void, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t) { GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)>::get()->name(arg0, arg1, arg2, arg3, arg4, arg5, arg6); } \
   void MOCK_GLOBAL_FUNC_T(name)::initialize()

#define _MOCK_GLOBAL_OBJ8(rtn_t, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t) \
class MOCK_GLOBAL_FUNC_T(name) : public GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)> { \
   void initialize(); \
   public: \
      virtual std::string Name() const { return std::string(#name); } \
      MOCK_GLOBAL_FUNC_T(name)() { MOCK_GLOBAL_FUNC_T(name)::pInstance = this; initialize(); } \
      virtual ~MOCK_GLOBAL_FUNC_T(name)() {} \
      MOCK_METHOD8(name, rtn_t(arg0_t arg0, arg1_t arg1, arg2_t arg2, arg3_t arg3, arg4_t arg4, arg5_t arg5, arg6_t arg6, arg7_t arg7)); \
}; \
rtn_t name(arg0_t arg0, arg1_t arg1, arg2_t arg2, arg3_t arg3, arg4_t arg4, arg5_t arg5, arg6_t arg6, arg7_t arg7)

#define MOCK_GLOBAL_OBJ8(rtn_t, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t) \
   _MOCK_GLOBAL_OBJ8(rtn_t, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t) { return GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)>::get()->name(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7); } \
   void MOCK_GLOBAL_FUNC_T(name)::initialize()

#define MOCK_GLOBAL_VOID_OBJ8(name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t) \
   _MOCK_GLOBAL_OBJ8(void, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t) { GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)>::get()->name(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7); } \
   void MOCK_GLOBAL_FUNC_T(name)::initialize()

#define _MOCK_GLOBAL_OBJ9(rtn_t, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t) \
class MOCK_GLOBAL_FUNC_T(name) : public GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)> { \
   void initialize(); \
   public: \
      virtual std::string Name() const { return std::string(#name); } \
      MOCK_GLOBAL_FUNC_T(name)() { MOCK_GLOBAL_FUNC_T(name)::pInstance = this; initialize(); } \
      virtual ~MOCK_GLOBAL_FUNC_T(name)() {} \
      MOCK_METHOD9(name, rtn_t(arg0_t arg0, arg1_t arg1, arg2_t arg2, arg3_t arg3, arg4_t arg4, arg5_t arg5, arg6_t arg6, arg7_t arg7, arg8_t arg8)); \
}; \
rtn_t name(arg0_t arg0, arg1_t arg1, arg2_t arg2, arg3_t arg3, arg4_t arg4, arg5_t arg5, arg6_t arg6, arg7_t arg7, arg8_t arg8)

#define MOCK_GLOBAL_OBJ9(rtn_t, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t) \
   _MOCK_GLOBAL_OBJ9(rtn_t, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t) { return GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)>::get()->name(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); } \
   void MOCK_GLOBAL_FUNC_T(name)::initialize()

#define MOCK_GLOBAL_VOID_OBJ9(name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t) \
   _MOCK_GLOBAL_OBJ9(void, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t) { GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)>::get()->name(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); } \
   void MOCK_GLOBAL_FUNC_T(name)::initialize()

#define _MOCK_GLOBAL_OBJ10(rtn_t, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t, arg9_t) \
class MOCK_GLOBAL_FUNC_T(name) : public GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)> { \
   void initialize(); \
   public: \
      virtual std::string Name() const { return std::string(#name); } \
      MOCK_GLOBAL_FUNC_T(name)() { MOCK_GLOBAL_FUNC_T(name)::pInstance = this; initialize(); } \
      virtual ~MOCK_GLOBAL_FUNC_T(name)() {} \
      MOCK_METHOD10(name, rtn_t(arg0_t arg0, arg1_t arg1, arg2_t arg2, arg3_t arg3, arg4_t arg4, arg5_t arg5, arg6_t arg6, arg7_t arg7, arg8_t arg8, arg9_t arg9)); \
}; \
rtn_t name(arg0_t arg0, arg1_t arg1, arg2_t arg2, arg3_t arg3, arg4_t arg4, arg5_t arg5, arg6_t arg6, arg7_t arg7, arg8_t arg8, arg9_t arg9)

#define MOCK_GLOBAL_OBJ10(rtn_t, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t, arg9_t) \
   _MOCK_GLOBAL_OBJ10(rtn_t, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t, arg9_t) { return GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)>::get()->name(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9); } \
   void MOCK_GLOBAL_FUNC_T(name)::initialize()

#define MOCK_GLOBAL_VOID_OBJ10(name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t, arg9_t) \
   _MOCK_GLOBAL_OBJ10(void, name, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t, arg9_t) { GMOSingletonMock<MOCK_GLOBAL_FUNC_T(name)>::get()->name(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9); } \
   void MOCK_GLOBAL_FUNC_T(name)::initialize()

#endif
