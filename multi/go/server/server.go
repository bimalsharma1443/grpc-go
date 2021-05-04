package main

import (
	"chatpb"
	"context"
	"log"
	"net"

	"google.golang.org/grpc"
)

type server struct {
	chatpb.UnimplementedChatServer
}

func main() {
	lis, err := net.Listen("tcp", "0.0.0.0:50051")
	if err != nil {
		log.Fatalf("Failed to listen : %v", err)
	}

	log.Println("Golag server started")

	s := grpc.NewServer()
	chatpb.RegisterChatServer(s, &server{})

	if err := s.Serve(lis); err != nil {
		log.Fatalf("Failed to serve : %v", err)
	}
}

func (server *server) SendRequest(ctx context.Context, req *chatpb.ChatRequest) (*chatpb.ChatReply, error) {

	message := req.GetMessage()

	log.Println(message)

	result := "Hello, I am from Go Lang"

	response := chatpb.ChatReply{
		Reply: result,
	}

	return &response, nil
}
