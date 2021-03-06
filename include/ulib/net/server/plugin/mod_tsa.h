// ============================================================================
//
// = LIBRARY
//    ULib - c++ library
//
// = FILENAME
//    mod_tsa.h
//
// = AUTHOR
//    Stefano Casazza
//
// ============================================================================

#ifndef U_MOD_TSA_H
#define U_MOD_TSA_H 1

#include <ulib/net/server/server_plugin.h>

class UCommand;

class U_EXPORT UTsaPlugIn : public UServerPlugIn {
public:

   // COSTRUTTORI

            UTsaPlugIn();
   virtual ~UTsaPlugIn();

   // define method VIRTUAL of class UServerPlugIn

   // Server-wide hooks

   virtual int handlerConfig(UFileConfig& cfg) U_DECL_OVERRIDE;
   virtual int handlerInit() U_DECL_OVERRIDE;

   // Connection-wide hooks

   virtual int handlerRequest() U_DECL_OVERRIDE;

   // DEBUG

#if defined(U_STDCPP_ENABLE) && defined(DEBUG)
   const char* dump(bool reset) const;
#endif

protected:
   static UCommand* command;

private:
#ifdef U_COMPILER_DELETE_MEMBERS
   UTsaPlugIn(const UTsaPlugIn&) = delete;
   UTsaPlugIn& operator=(const UTsaPlugIn&) = delete;
#else
   UTsaPlugIn(const UTsaPlugIn&) : UServerPlugIn() {}
   UTsaPlugIn& operator=(const UTsaPlugIn&)        { return *this; }
#endif
};

#endif
