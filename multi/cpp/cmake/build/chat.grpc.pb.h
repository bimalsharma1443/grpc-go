// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: chat.proto
#ifndef GRPC_chat_2eproto__INCLUDED
#define GRPC_chat_2eproto__INCLUDED

#include "chat.pb.h"

#include <functional>
#include <grpc/impl/codegen/port_platform.h>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace chat {

// Defines the service
class Chat final {
 public:
  static constexpr char const* service_full_name() {
    return "chat.Chat";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    // Function invoked to send the request
    virtual ::grpc::Status sendRequest(::grpc::ClientContext* context, const ::chat::ChatRequest& request, ::chat::ChatReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::chat::ChatReply>> AsyncsendRequest(::grpc::ClientContext* context, const ::chat::ChatRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::chat::ChatReply>>(AsyncsendRequestRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::chat::ChatReply>> PrepareAsyncsendRequest(::grpc::ClientContext* context, const ::chat::ChatRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::chat::ChatReply>>(PrepareAsyncsendRequestRaw(context, request, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      // Function invoked to send the request
      virtual void sendRequest(::grpc::ClientContext* context, const ::chat::ChatRequest* request, ::chat::ChatReply* response, std::function<void(::grpc::Status)>) = 0;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void sendRequest(::grpc::ClientContext* context, const ::chat::ChatRequest* request, ::chat::ChatReply* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      #else
      virtual void sendRequest(::grpc::ClientContext* context, const ::chat::ChatRequest* request, ::chat::ChatReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
      #endif
    };
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    typedef class experimental_async_interface async_interface;
    #endif
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    async_interface* async() { return experimental_async(); }
    #endif
    virtual class experimental_async_interface* experimental_async() { return nullptr; }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::chat::ChatReply>* AsyncsendRequestRaw(::grpc::ClientContext* context, const ::chat::ChatRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::chat::ChatReply>* PrepareAsyncsendRequestRaw(::grpc::ClientContext* context, const ::chat::ChatRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status sendRequest(::grpc::ClientContext* context, const ::chat::ChatRequest& request, ::chat::ChatReply* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::chat::ChatReply>> AsyncsendRequest(::grpc::ClientContext* context, const ::chat::ChatRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::chat::ChatReply>>(AsyncsendRequestRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::chat::ChatReply>> PrepareAsyncsendRequest(::grpc::ClientContext* context, const ::chat::ChatRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::chat::ChatReply>>(PrepareAsyncsendRequestRaw(context, request, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      void sendRequest(::grpc::ClientContext* context, const ::chat::ChatRequest* request, ::chat::ChatReply* response, std::function<void(::grpc::Status)>) override;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void sendRequest(::grpc::ClientContext* context, const ::chat::ChatRequest* request, ::chat::ChatReply* response, ::grpc::ClientUnaryReactor* reactor) override;
      #else
      void sendRequest(::grpc::ClientContext* context, const ::chat::ChatRequest* request, ::chat::ChatReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
      #endif
     private:
      friend class Stub;
      explicit experimental_async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class experimental_async_interface* experimental_async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class experimental_async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::chat::ChatReply>* AsyncsendRequestRaw(::grpc::ClientContext* context, const ::chat::ChatRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::chat::ChatReply>* PrepareAsyncsendRequestRaw(::grpc::ClientContext* context, const ::chat::ChatRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_sendRequest_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    // Function invoked to send the request
    virtual ::grpc::Status sendRequest(::grpc::ServerContext* context, const ::chat::ChatRequest* request, ::chat::ChatReply* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_sendRequest : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_sendRequest() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_sendRequest() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status sendRequest(::grpc::ServerContext* /*context*/, const ::chat::ChatRequest* /*request*/, ::chat::ChatReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestsendRequest(::grpc::ServerContext* context, ::chat::ChatRequest* request, ::grpc::ServerAsyncResponseWriter< ::chat::ChatReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_sendRequest<Service > AsyncService;
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_sendRequest : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithCallbackMethod_sendRequest() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::chat::ChatRequest, ::chat::ChatReply>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::chat::ChatRequest* request, ::chat::ChatReply* response) { return this->sendRequest(context, request, response); }));}
    void SetMessageAllocatorFor_sendRequest(
        ::grpc::experimental::MessageAllocator< ::chat::ChatRequest, ::chat::ChatReply>* allocator) {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
    #else
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::experimental().GetHandler(0);
    #endif
      static_cast<::grpc::internal::CallbackUnaryHandler< ::chat::ChatRequest, ::chat::ChatReply>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~ExperimentalWithCallbackMethod_sendRequest() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status sendRequest(::grpc::ServerContext* /*context*/, const ::chat::ChatRequest* /*request*/, ::chat::ChatReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* sendRequest(
      ::grpc::CallbackServerContext* /*context*/, const ::chat::ChatRequest* /*request*/, ::chat::ChatReply* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* sendRequest(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::chat::ChatRequest* /*request*/, ::chat::ChatReply* /*response*/)
    #endif
      { return nullptr; }
  };
  #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
  typedef ExperimentalWithCallbackMethod_sendRequest<Service > CallbackService;
  #endif

  typedef ExperimentalWithCallbackMethod_sendRequest<Service > ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_sendRequest : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_sendRequest() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_sendRequest() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status sendRequest(::grpc::ServerContext* /*context*/, const ::chat::ChatRequest* /*request*/, ::chat::ChatReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_sendRequest : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_sendRequest() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_sendRequest() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status sendRequest(::grpc::ServerContext* /*context*/, const ::chat::ChatRequest* /*request*/, ::chat::ChatReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestsendRequest(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_sendRequest : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithRawCallbackMethod_sendRequest() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->sendRequest(context, request, response); }));
    }
    ~ExperimentalWithRawCallbackMethod_sendRequest() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status sendRequest(::grpc::ServerContext* /*context*/, const ::chat::ChatRequest* /*request*/, ::chat::ChatReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* sendRequest(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* sendRequest(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #endif
      { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_sendRequest : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_sendRequest() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::chat::ChatRequest, ::chat::ChatReply>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::chat::ChatRequest, ::chat::ChatReply>* streamer) {
                       return this->StreamedsendRequest(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_sendRequest() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status sendRequest(::grpc::ServerContext* /*context*/, const ::chat::ChatRequest* /*request*/, ::chat::ChatReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedsendRequest(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::chat::ChatRequest,::chat::ChatReply>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_sendRequest<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_sendRequest<Service > StreamedService;
};

}  // namespace chat


#endif  // GRPC_chat_2eproto__INCLUDED
