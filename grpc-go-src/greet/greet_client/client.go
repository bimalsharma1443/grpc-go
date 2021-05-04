package main

import (
	"context"
	"gRPC/grpc-go-src/greet/greetpb"
	"io"
	"log"
	"sync"
	"time"

	"google.golang.org/grpc"
)

func main() {
	cc, err := grpc.Dial("localhost:50051", grpc.WithInsecure())
	if err != nil {
		log.Fatalf("unable to connect to server, %v", err)
	}

	defer cc.Close()

	c := greetpb.NewGreetServiceClient(cc)

	//unary
	// doUnary(c)

	// server striming
	// doServerStream(c)

	// client striming
	// doClientStream(c)

	// BiDi stream
	// doBiDiStream(c)

	// Unary timeout
	doUnaryTimeOut(c, 10*time.Second)
	doUnaryTimeOut(c, 1*time.Second)

}

func doUnary(c greetpb.GreetServiceClient) {
	req := &greetpb.GreetingRequest{
		Greeting: &greetpb.Greeting{
			FirstName:  "Bimal",
			SecondName: "Sharma",
		},
	}

	res, err := c.Greet(context.Background(), req)

	if err != nil {
		log.Fatalf("error in greed unary response, %v", err)
	}

	log.Printf("get response from res, %v", res)
}

func doServerStream(c greetpb.GreetServiceClient) {
	req := &greetpb.GreetingManyRequest{
		Greeting: &greetpb.Greeting{
			FirstName:  "Bimal",
			SecondName: "Sharma",
		},
	}

	stream, err := c.GreetManyTime(context.Background(), req)

	if err != nil {
		log.Fatalf("error in greed unary response, %v", err)
	}

	for {
		resp, err := stream.Recv()
		if err == io.EOF {
			break
		}
		if err != nil {
			log.Fatalf("error in  reading a file, %v", err)
		}

		log.Printf("response is, %v ", resp.GetResult())

	}
}

func doClientStream(c greetpb.GreetServiceClient) {
	log.Println("client streaming")
	requests := []*greetpb.LongGreetRequest{
		&greetpb.LongGreetRequest{
			Greeting: &greetpb.Greeting{
				FirstName:  "Bimal",
				SecondName: "Sharma",
			},
		},
		&greetpb.LongGreetRequest{
			Greeting: &greetpb.Greeting{
				FirstName:  "Shreya",
				SecondName: "Sharma",
			},
		},
		&greetpb.LongGreetRequest{
			Greeting: &greetpb.Greeting{
				FirstName:  "Jagruti",
				SecondName: "Sharma",
			},
		},
	}

	stream, err := c.LongGreet(context.Background())
	if err != nil {
		log.Fatalf("error in stream, %v", err)
	}

	for _, req := range requests {
		log.Println("client streaming sending ", req)
		err = stream.Send(req)
		if err != nil {
			log.Fatalf("error in send a request, %v", err)
		}

		time.Sleep(time.Second)

	}

	err = stream.CloseSend()

	if err != nil {
		log.Fatalf("error in recieve responsde, %v", err)
	}

	rsp, err := stream.Recv()

	if err != nil {
		log.Fatalf("error in recieve responsde, %v", err)
	}

	log.Println("value is , ", rsp)

}

func doBiDiStream(c greetpb.GreetServiceClient) {
	log.Println("BIDI streaming")

	requests := []*greetpb.GreetEveryoneRequest{
		&greetpb.GreetEveryoneRequest{
			Greeting: &greetpb.Greeting{
				FirstName:  "Bimal",
				SecondName: "Sharma",
			},
		},
		&greetpb.GreetEveryoneRequest{
			Greeting: &greetpb.Greeting{
				FirstName:  "Shreya",
				SecondName: "Sharma",
			},
		},
		&greetpb.GreetEveryoneRequest{
			Greeting: &greetpb.Greeting{
				FirstName:  "Jagruti",
				SecondName: "Sharma",
			},
		},
	}

	stream, err := c.GreetEveryone(context.Background())
	if err != nil {
		log.Fatalf("error in stream, %v", err)
	}

	wg := sync.WaitGroup{}

	wg.Add(2)

	go func() {
		for _, v := range requests {
			err = stream.Send(v)
			if err != nil {
				log.Fatalf("unable to send a data, %v", err)
				wg.Done()
			}
			log.Printf("request is, %v", v)
			time.Sleep(time.Second)

		}
		stream.CloseSend()
	}()

	go func() {
		for {
			resp, err := stream.Recv()

			if err == io.EOF {
				log.Fatalf("unable to send a data, %v", err)
				break
			}

			if err != nil {
				log.Fatalf("unable to send a data, %v", err)
				break
			}

			log.Printf("response is, %v", resp)
		}
		wg.Done()
	}()

	wg.Wait()

}

func doUnaryTimeOut(c greetpb.GreetServiceClient, deadline time.Duration) {
	req := &greetpb.GreetWithDeadLineRequest{
		Greeting: &greetpb.Greeting{
			FirstName:  "Bimal",
			SecondName: "Sharma",
		},
	}

	ctx, close := context.WithTimeout(context.Background(), deadline)
	defer close()

	res, err := c.GreetWithDeadLine(ctx, req)

	if err != nil {
		log.Fatalf("error in greed unary response, %v", err)
	}

	log.Printf("get response from res, %v", res)
}
