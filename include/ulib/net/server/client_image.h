// ============================================================================
//
// = LIBRARY
//    ULib - c++ library
//
// = FILENAME
//    client_image.h - Handles accepted connections from UServer's client
//
// = AUTHOR
//    Stefano Casazza
//
// ============================================================================

#ifndef U_CLIENT_IMAGE_H
#define U_CLIENT_IMAGE_H 1

#include <ulib/timeval.h>
#include <ulib/event/event_fd.h>
#include <ulib/internal/chttp.h>
#include <ulib/utility/socket_ext.h>

#ifdef USE_LIBSSL
#  include <ulib/ssl/certificate.h>
#  include <ulib/ssl/net/sslsocket.h>
#endif

/**
 * @class UClientImage
 *
 * @brief Handles accepted connections from UServer's client (A representation of the Server responsible for handling Client instances)
 */

class UHTTP;
class UHTTP2;
class UIPAllow;
class USSIPlugIn;
class UHttpPlugIn;
class UNoCatPlugIn;
class UServer_Base;
class UStreamPlugIn;

template <class T> class UServer;

#define U_ClientImage_request_is_cached UClientImage_Base::cbuffer[0]

class U_EXPORT UClientImage_Base : public UEventFd {
public:

   // Check for memory error
   U_MEMORY_TEST

   // Allocator e Deallocator
   U_MEMORY_ALLOCATOR
   U_MEMORY_DEALLOCATOR

   // SERVICES

   bool genericRead();
   int  handlerResponse();

   bool isPendingSendfile()
      {
      U_TRACE(0, "UClientImage_Base::isPendingSendfile()")

      if (count > 0) U_RETURN(true);

      U_RETURN(false);
      }

   static void setNoHeaderForResponse()
      {
      U_TRACE(0, "UClientImage_Base::setNoHeaderForResponse()")

      iov_vec[1].iov_len = 0;
      }

   static void setHeaderForResponse(uint32_t len)
      {
      U_TRACE(0, "UClientImage_Base::setHeaderForResponse(%u)", len)

      iov_vec[1].iov_len = len;
      }

   static void init();
   static void clear();

   static const char* getRequestUri(uint32_t& len);

   static bool isAllowed(UVector<UIPAllow*>& vallow_IP) __pure; // Check whether the ip address client ought to be allowed

   // define method VIRTUAL of class UEventFd

   virtual int handlerRead() U_DECL_OVERRIDE;
   virtual int handlerWrite() U_DECL_OVERRIDE;
   virtual int handlerTimeout() U_DECL_OVERRIDE;

   virtual void handlerError() U_DECL_OVERRIDE;
   virtual void handlerDelete() U_DECL_OVERRIDE;

   // manage if other data already available... (pipelining)

   static void resetPipeline()
      {
      U_TRACE(0, "UClientImage_Base::resetPipeline()")

      U_INTERNAL_DUMP("U_ClientImage_pipeline = %b U_ClientImage_parallelization = %d",
                       U_ClientImage_pipeline,     U_ClientImage_parallelization)

      if (U_ClientImage_pipeline)
         {
         U_INTERNAL_ASSERT(request->same(*rbuffer) == false)

         U_ClientImage_pipeline = false;

#     ifndef U_CACHE_REQUEST_DISABLE
         U_INTERNAL_DUMP("U_ClientImage_request_is_cached = %b", U_ClientImage_request_is_cached)

         if (U_ClientImage_request_is_cached == false)
#     endif
         size_request = 0; // NB: we don't want to process further the read buffer...
         }
      }

   static void resetPipelineAndClose()
      {
      U_TRACE(0, "UClientImage_Base::resetPipelineAndClose()")

      // NB: because we close the connection we don't need to process other request in pipeline...

      resetPipeline();

      U_ClientImage_close = true;

      U_INTERNAL_DUMP("U_ClientImage_close = %b", U_ClientImage_close)
      }

   static void resetAndClose()
      {
      U_TRACE(0, "UClientImage_Base::resetAndClose()")

      U_INTERNAL_ASSERT_POINTER(psocket)

      resetPipeline();

      setRequestProcessed();

      psocket->close();
      }

   static void setCloseConnection()
      {
      U_TRACE(0, "UClientImage_Base::setCloseConnection()")

      U_INTERNAL_DUMP("U_ClientImage_pipeline = %b", U_ClientImage_pipeline)

      if (U_ClientImage_pipeline == false) U_ClientImage_close = true;

      U_INTERNAL_DUMP("U_ClientImage_close = %b", U_ClientImage_close)
      }

   // request state processing

   enum RequestStatusType {
   // NOT_FOUND         = 0x0000,
      FORBIDDEN         = 0x0001,
      NO_CACHE          = 0x0002,
      IN_FILE_CACHE     = 0x0004,
      ALREADY_PROCESSED = 0x0008
   };

   static bool isRequestNotFound()
      {
      U_TRACE(0, "UClientImage_Base::isRequestNotFound()")

      U_INTERNAL_DUMP("U_ClientImage_request = %d %B", U_ClientImage_request, U_ClientImage_request)

#  ifdef U_CACHE_REQUEST_DISABLE
      if (U_ClientImage_request == 0) U_RETURN(true);
#  else
      if ((U_ClientImage_request & ~NO_CACHE) == 0) U_RETURN(true);
#  endif

      U_RETURN(false);
      }

   static void setRequestProcessed()
      {
      U_TRACE(0, "UClientImage_Base::setRequestProcessed()")

      U_INTERNAL_DUMP("U_ClientImage_request = %d %B", U_ClientImage_request, U_ClientImage_request)

      if ((U_ClientImage_request & ALREADY_PROCESSED) == 0) U_ClientImage_request |= ALREADY_PROCESSED;
      }

   static void setRequestNeedProcessing()
      {
      U_TRACE(0, "UClientImage_Base::setRequestNeedProcessing()")

      U_INTERNAL_DUMP("U_ClientImage_request = %d %B", U_ClientImage_request, U_ClientImage_request)

      U_ClientImage_request &= ~ALREADY_PROCESSED;

      U_INTERNAL_DUMP("U_ClientImage_request = %d %B", U_ClientImage_request, U_ClientImage_request)
      }

   static bool isRequestNeedProcessing()
      {
      U_TRACE(0, "UClientImage_Base::isRequestNeedProcessing()")

      U_INTERNAL_DUMP("U_ClientImage_request = %d %B", U_ClientImage_request, U_ClientImage_request)

      if ((U_ClientImage_request & ALREADY_PROCESSED) == 0) U_RETURN(true);

      U_RETURN(false);
      }

   static bool isRequestAlreadyProcessed()
      {
      U_TRACE(0, "UClientImage_Base::isRequestAlreadyProcessed()")

      U_INTERNAL_DUMP("U_ClientImage_request = %d %B", U_ClientImage_request, U_ClientImage_request)

      if ((U_ClientImage_request & ALREADY_PROCESSED) != 0) U_RETURN(true);

      U_RETURN(false);
      }

   static bool isRequestRedirected()
      {
      U_TRACE(0, "UClientImage_Base::isRequestRedirected()")

      U_INTERNAL_DUMP("U_ClientImage_request = %d %B u_http_info.nResponseCode = %d", U_ClientImage_request,
                       U_ClientImage_request,        u_http_info.nResponseCode)

      if ((U_ClientImage_request & ALREADY_PROCESSED) != 0 &&
          (u_http_info.nResponseCode == HTTP_MOVED_TEMP    ||
           u_http_info.nResponseCode == HTTP_NETWORK_AUTHENTICATION_REQUIRED))
         {
         U_RETURN(true);
         }

      U_RETURN(false);
      }

   static void setRequestForbidden()
      {
      U_TRACE(0, "UClientImage_Base::setRequestForbidden()")

      U_INTERNAL_DUMP("U_ClientImage_request = %d %B", U_ClientImage_request, U_ClientImage_request)

      U_ClientImage_request |= FORBIDDEN | ALREADY_PROCESSED;
      }

   static bool isRequestForbidden()
      {
      U_TRACE(0, "UClientImage_Base::isRequestForbidden()")

      U_INTERNAL_DUMP("U_ClientImage_request = %d %B", U_ClientImage_request, U_ClientImage_request)

      if ((U_ClientImage_request & FORBIDDEN) != 0) U_RETURN(true);

      U_RETURN(false);
      }

   static void setRequestInFileCache()
      {
      U_TRACE(0, "UClientImage_Base::setRequestInFileCache()")

      U_INTERNAL_DUMP("U_ClientImage_request = %d %B", U_ClientImage_request, U_ClientImage_request)

      U_ClientImage_request |= IN_FILE_CACHE | ALREADY_PROCESSED;
      }

   static bool isRequestInFileCache()
      {
      U_TRACE(0, "UClientImage_Base::isRequestInFileCache()")

      U_INTERNAL_DUMP("U_ClientImage_request = %d %B", U_ClientImage_request, U_ClientImage_request)

      if ((U_ClientImage_request & IN_FILE_CACHE) != 0) U_RETURN(true);

      U_RETURN(false);
      }

   static void setRequestNoCache()
      {
      U_TRACE(0, "UClientImage_Base::setRequestNoCache()")

#  ifndef U_CACHE_REQUEST_DISABLE
      U_ClientImage_request |= NO_CACHE;

      U_INTERNAL_DUMP("U_ClientImage_request = %d %B", U_ClientImage_request, U_ClientImage_request)
#  endif
      }

   // DEBUG

#if defined(U_STDCPP_ENABLE) && defined(DEBUG)
   const char* dump(bool reset) const;
#endif

   // NB: these are public for plugin access...

public:
   UString* logbuf; // it is needed for U_SRV_LOG_WITH_ADDR...

   static bool bIPv6; 
   static UString* body;
   static UString* rbuffer;
   static UString* wbuffer;
   static UString* request;
   static USocket* psocket;

   static char cbuffer[128];
   static UString* request_uri;
   static UString* environment;
   static bPF callerHandlerCache;
   static struct iovec iov_sav[4];
   static struct iovec iov_vec[4];
   static UClientImage_Base* pthis;
   static bPFpc callerIsValidRequest;
   static vPF callerHandlerEndRequest;
   static bPFpcu callerIsValidRequestExt;
   static uint32_t rstart, size_request;
   static iPF callerHandlerRead, callerHandlerRequest, callerHandlerReset, callerHandlerDataPending;

   // NB: these are for ULib Servlet Page (USP) - USP_PRINTF...

   static UString* _value;
   static UString* _buffer;
   static UString* _encoded;

protected:
   USocket* socket;
#ifndef U_HTTP2_DISABLE
   void* connection;
#endif
   UString* data_pending;
   uint32_t start, count;
   int sfd, pending_close;
   time_t last_event;

   void   set();
   void reset()
      {
      U_TRACE(0, "UClientImage_Base::reset()")

      UEventFd::op_mask = EPOLLIN | EPOLLRDHUP;

      start =
      count = 0;
      sfd   = -1;
      }

   void prepareForSendfile();

   static uint32_t getCountToRead()
      {
      U_TRACE(0, "UClientImage_Base::getCountToRead()")

      if (size_request == 0) U_RETURN(U_SINGLE_READ);

      uint32_t sz = rbuffer->size();

      if (size_request > sz)
         {
         sz = size_request - sz;

         U_RETURN(sz);
         }

      U_RETURN(U_SINGLE_READ);
      }

   static void setSendfile(int _sfd, uint32_t _start, uint32_t _count)
      {
      U_TRACE(0, "UClientImage_Base::setSendfile(%d,%u,%u)", _sfd, _start, _count)

      U_INTERNAL_ASSERT_MAJOR(_count, 0)
      U_INTERNAL_ASSERT_DIFFERS(_sfd, -1)

      pthis->start = _start;
      pthis->count = _count;
      pthis->sfd   = _sfd;
      }

#ifndef U_LOG_DISABLE
   void logRequest();
#endif
   bool writeResponse();
   bool logCertificate(); // append on log the peer certicate of client ("issuer","serial")
   bool askForClientCertificate();

   static struct iovec* piov;
   static int csfd, idx, iovcnt;
   static UTimeVal* chronometer;
   static bool log_request_partial;
   static long time_between_request, time_run;
   static uint32_t ncount, nrequest, resto, uri_offset, uri_len;

   static void   endRequest();
   static bool startRequest();

   static void resetReadBuffer();
   static void resetWriteBuffer();
   static void saveRequestResponse();
   static void manageReadBufferResize(UString& buffer, uint32_t n);

#ifndef U_CACHE_REQUEST_DISABLE
   static bool isRequestCacheable() __pure;
#endif

   // COSTRUTTORI

            UClientImage_Base();
   virtual ~UClientImage_Base();

#ifdef DEBUG
   bool check_memory();
#endif

private:
   static int handlerDataPending() U_NO_EXPORT;

   static bool isValidRequest(   const char* ptr)              U_NO_EXPORT;
   static bool isValidRequestExt(const char* ptr, uint32_t sz) U_NO_EXPORT;

   UClientImage_Base(const UClientImage_Base&) : UEventFd() {}
   UClientImage_Base& operator=(const UClientImage_Base&)   { return *this; }

                      friend class UHTTP;
                      friend class UHTTP2;
                      friend class USSIPlugIn;
                      friend class UHttpPlugIn;
                      friend class UNoCatPlugIn;
                      friend class UServer_Base;
                      friend class UStreamPlugIn;
   template <class T> friend class UServer;
   template <class T> friend void u_delete_vector(      T* _vec, uint32_t offset, uint32_t n);
#ifdef DEBUG
   template <class T> friend bool u_check_memory_vector(T* _vec,                  uint32_t n);
#endif
};

template <class Socket> class U_EXPORT UClientImage : public UClientImage_Base {
public:

   // COSTRUTTORI

   UClientImage() : UClientImage_Base()
      {
      U_TRACE_REGISTER_OBJECT(0, UClientImage<Socket>, "", 0)

      socket = U_NEW(Socket(UClientImage_Base::bIPv6));

      set();
      }

   virtual ~UClientImage()
      {
      U_TRACE_UNREGISTER_OBJECT(0, UClientImage<Socket>)
      }

   // DEBUG

#if defined(U_STDCPP_ENABLE) && defined(DEBUG)
   const char* dump(bool _reset) const { return UClientImage_Base::dump(_reset); }
#endif

private:
   UClientImage(const UClientImage&) : UClientImage_Base() {}
   UClientImage& operator=(const UClientImage&)            { return *this; }
};

#ifdef USE_LIBSSL // specializzazione con USSLSocket
template <> class U_EXPORT UClientImage<USSLSocket> : public UClientImage_Base {
public:

   UClientImage() : UClientImage_Base()
      {
      U_TRACE_REGISTER_OBJECT(0, UClientImage<USSLSocket>, "", 0)

      socket = U_NEW(USSLSocket(UClientImage_Base::bIPv6, USSLSocket::sctx, true));

      set();
      }

   virtual ~UClientImage()
      {
      U_TRACE_UNREGISTER_OBJECT(0, UClientImage<USSLSocket>)
      }

   // DEBUG

#if defined(U_STDCPP_ENABLE) && defined(DEBUG)
   const char* dump(bool _reset) const { return UClientImage_Base::dump(_reset); }
#endif

private:
#ifdef U_COMPILER_DELETE_MEMBERS
   UClientImage<USSLSocket>(const UClientImage<USSLSocket>&) = delete;
   UClientImage<USSLSocket>& operator=(const UClientImage<USSLSocket>&) = delete;
#else
   UClientImage<USSLSocket>(const UClientImage<USSLSocket>&) : UClientImage_Base() {}
   UClientImage<USSLSocket>& operator=(const UClientImage<USSLSocket>&)            { return *this; }
#endif
};
#endif

#endif
