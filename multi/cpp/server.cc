#include <string>

#include <grpcpp/grpcpp.h>
#include "chat.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using chat::Chat;
using chat::ChatRequest;
using chat::ChatReply;

class ChatServiceImplementation final : public Chat::Service {
    Status sendRequest(
        ServerContext* context, 
        const ChatRequest* request, 
        ChatReply* reply
    ) override {
        std::string message = request->message();

        reply->set_reply("Hello, I am From C++");

        return Status::OK;
    } 
};

void Run() {
    std::string address("0.0.0.0:5000");
    ChatServiceImplementation service;

    ServerBuilder builder;

    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on port: " << address << std::endl;

    server->Wait();
}

int main(int argc, char** argv) {
    Run();

    return 0;
}
