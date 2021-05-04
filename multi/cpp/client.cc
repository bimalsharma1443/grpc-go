#include <string>

#include <grpcpp/grpcpp.h>
#include "chat.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using chat::Chat;
using chat::ChatRequest;
using chat::ChatReply;

class ChatClient {
    public:
        ChatClient(std::shared_ptr<Channel> channel) : stub_(Chat::NewStub(channel)) {}

    std::string sendRequest(std::string message) {
        ChatRequest request;

        request.set_message(message);

        ChatReply reply;

        ClientContext context;

        Status status = stub_->sendRequest(&context, request, &reply);

        if(status.ok()){
            return reply.reply();
        } else {
            std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            return "";
        }
    }

    private:
        std::unique_ptr<Chat::Stub> stub_;
};

void Run() {
    std::string address("0.0.0.0:5000");
    ChatClient client(
        grpc::CreateChannel(
            address, 
            grpc::InsecureChannelCredentials()
        )
    );

    std::string response;

    std::string message = "Hello, I am  from c++";

    response = client.sendRequest(message);
   std::cout << "request: "  << message << std::endl;
   std::cout << "response: " << response << std::endl;
}

int main(int argc, char* argv[]){
    Run();

    return 0;
}
