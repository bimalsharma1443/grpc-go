package main

import (
	"context"
	"gRPC/grpc-go-src/greet/greetpb"
	"io"
	"log"
	"net"
	"strconv"
	"time"

	"google.golang.org/grpc"
)

type server struct {
	greetpb.UnimplementedGreetServiceServer
}

func main() {
	lis, err := net.Listen("tcp", "0.0.0.0:50051")
	if err != nil {
		log.Fatalf("Failed to listen : %v", err)
	}

	s := grpc.NewServer()
	greetpb.RegisterGreetServiceServer(s, &server{})

	if err := s.Serve(lis); err != nil {
		log.Fatalf("Failed to serve : %v", err)
	}
}

func (server *server) Greet(ctx context.Context, req *greetpb.GreetingRequest) (*greetpb.GreetingResponse, error) {

	firstName := req.GetGreeting().GetFirstName()
	secondName := req.GetGreeting().GetSecondName()
	result := "Hello " + firstName + " " + secondName

	response := greetpb.GreetingResponse{
		Result: result,
	}

	return &response, nil
}

func (server *server) GreetManyTime(req *greetpb.GreetingManyRequest, stream greetpb.GreetService_GreetManyTimeServer) error {

	firstName := req.GetGreeting().GetFirstName()
	secondName := req.GetGreeting().GetSecondName()
	for i := 0; i < 10; i++ {
		result := "Hello " + firstName + " " + secondName + strconv.Itoa(i)

		req := &greetpb.GreetingManyResponse{
			Result: result,
		}

		stream.Send(req)
		time.Sleep(1 * time.Second)
	}

	return nil
}

func (server *server) LongGreet(stream greetpb.GreetService_LongGreetServer) error {

	result := "Hello "
	for {
		req, err := stream.Recv()

		log.Println(result)

		if err == io.EOF {
			// we have finished reading the client stream
			return stream.Send(&greetpb.LongGreetResponse{
				Result: result,
			})
		}

		log.Println(result)

		if err != nil {
			log.Fatalf("Error while reading client stream, %v", err)
		}

		firstName := req.GetGreeting().GetFirstName()
		secondName := req.GetGreeting().GetSecondName()

		result = result + " " + firstName + " " + secondName + "!"

	}

	return nil
}

func (server *server) GreetEveryone(stream greetpb.GreetService_GreetEveryoneServer) error {

	for {
		result := "Hello"
		req, err := stream.Recv()
		if err == io.EOF {
			log.Fatalf("log error message, %v", err)
			return nil
		}
		if err != nil {
			log.Fatalf("log error message, %v", err)
			return err
		}

		result += " " + req.GetGreeting().GetFirstName()
		result += " " + req.GetGreeting().GetSecondName()

		err = stream.Send(&greetpb.GreetEveryoneResponse{
			Result: result,
		})

		if err != nil {
			log.Fatalf("log error message, %v", err)
			return err
		}

	}
}

func (server *server) GreetWithDeadLine(ctx context.Context, req *greetpb.GreetWithDeadLineRequest) (*greetpb.GreetWithDeadLineResponse, error) {

	firstName := req.GetGreeting().FirstName
	secondName := req.GetGreeting().GetSecondName()
	result := "Hello " + firstName + " " + secondName

	response := greetpb.GreetWithDeadLineResponse{
		Result: result,
	}

	time.Sleep(3 * time.Second)

	return &response, nil
}
