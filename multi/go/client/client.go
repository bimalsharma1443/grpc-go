package main

import (
	"chatpb"
	"context"
	"fmt"
	"log"

	"google.golang.org/grpc"
)

func main() {
	cc, err := grpc.Dial("localhost:50051", grpc.WithInsecure())
	if err != nil {
		log.Fatalf("unable to connect to server, %v", err)
	}

	defer cc.Close()

	c := chatpb.NewChatClient(cc)

	// Send a message
	sendMessage(c)

}

func sendMessage(c chatpb.ChatClient) {
	message := "Hello, I am from Golang"

	req := &chatpb.ChatRequest{
		Message: message,
	}

	fmt.Println(req)

	res, err := c.SendRequest(context.Background(), req)

	if err != nil {
		log.Fatalf("error in chat response, %v", err)
	}

	log.Printf("get response from res, %v", res)
}
