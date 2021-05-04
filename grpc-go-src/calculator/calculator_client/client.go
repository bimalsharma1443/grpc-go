package main

import (
	"context"
	"gRPC/grpc-go-src/calculator/calculatorpb"
	"io"
	"log"
	"sync"
	"time"

	"google.golang.org/grpc"
	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/credentials"
	"google.golang.org/grpc/status"
)

func main() {

	log.Printf("starting a client calculator")

	certFile := "ssl/ca.crt"

	creds, _ := credentials.NewClientTLSFromFile(certFile, "")

	opts := grpc.WithTransportCredentials(creds)

	clientConnection, err := grpc.Dial("localhost:50051", opts)

	if err != nil {
		log.Fatalf("unable to connect to server,  %v", err)
	}

	defer clientConnection.Close()

	client := calculatorpb.NewCalculatorServiceClient(clientConnection)

	// UNARY
	doUnary(client)

	// SERVER STREAMING
	// doServerStream(client)

	// Client Streaming
	// doClientStream(client)

	// BiDi Streaming
	// doBiDiStreaming(client)

	// error handling
	// doErrorHadling(client)

}

func doUnary(client calculatorpb.CalculatorServiceClient) {
	log.Printf("call unaru api to calculate sum. \n")

	req := &calculatorpb.CalculatorRequest{
		FirstNumber:  5,
		SecondNumber: 6,
	}

	res, err := client.Calculator(context.Background(), req)

	if err != nil {
		log.Fatalf("unable to get response, %v", err)
	}

	log.Printf("sum of two number is %d", res.GetSum())

}

func doServerStream(client calculatorpb.CalculatorServiceClient) {
	log.Printf("call server streamng api to calculate sum. \n")

	req := &calculatorpb.PrimeNumberDecompositionRequest{
		Number: 200,
	}

	stream, err := client.PrimeNumberDecomposition(context.Background(), req)

	if err != nil {
		log.Fatalf("unable to get response, %v", err)
	}

	for {
		resp, err := stream.Recv()

		if err == io.EOF {
			break
		}

		if err != nil {
			log.Printf("unable to read stream, %v", err)
		}

		log.Printf("stream data, %v\n", resp)
	}

}

func doClientStream(client calculatorpb.CalculatorServiceClient) {
	log.Printf("call client streamng api to calculate sum. \n")

	stream, err := client.ComputeAverage(context.Background())

	if err != nil {
		log.Fatalf("unable to get response, %v", err)
	}

	list := []int32{1, 4, 6, 30, 58, 78}

	for _, v := range list {
		err := stream.Send(&calculatorpb.ComputeAverageRequest{
			Number: v,
		})

		if err != nil {
			log.Printf("unable to send on stream, %v", err)
		}

		time.Sleep(time.Second)

		log.Println("sending number on stream from client is, ", v)

	}

	resp, err := stream.CloseAndRecv()

	if err != nil {
		log.Printf("unable to recieve on stream, %v", err)
	}

	log.Printf("stream data, %v\n", resp)

}

func doBiDiStreaming(client calculatorpb.CalculatorServiceClient) {
	log.Printf("call BiDi streamng api to calculate sum. \n")

	stream, err := client.FindMaximum(context.Background())

	if err != nil {
		log.Fatalf("unable to get response, %v", err)
	}

	list := []int32{1, 5, 3, 6, 2, 20}

	wg := sync.WaitGroup{}

	wg.Add(2)

	go func() {
		for _, v := range list {
			err := stream.Send(&calculatorpb.FindMaximumRequest{
				Number: v,
			})

			if err != nil {
				log.Printf("unable to send on stream, %v", err)
			}
			log.Println("sending number on stream from client is, ", v)
			time.Sleep(time.Second)

		}
		stream.CloseSend()
		wg.Done()
	}()

	go func() {
		for {
			resp, err := stream.Recv()
			if err == io.EOF {
				break
			}

			if err != nil {
				log.Printf("unable to send on stream, %v", err)
				break
			}
			log.Printf("maximum number is, %v", resp.GetMax())
		}
		wg.Done()
	}()
	wg.Wait()
}

func doErrorHadling(client calculatorpb.CalculatorServiceClient) {
	log.Printf("call error handling. \n")

	number := int32(10)
	handelError(client, number)
	number = int32(-2)
	handelError(client, number)

}

func handelError(client calculatorpb.CalculatorServiceClient, number int32) {
	resp, err := client.SqaurRoot(context.Background(), &calculatorpb.SqaurRootRequest{Number: number})

	if err != nil {
		errResp, ok := status.FromError(err)
		if ok {
			log.Println(errResp.Message())
			log.Println(errResp.Code())
			if errResp.Code() == codes.InvalidArgument {
				log.Printf("Big Error calling SquarRoot: %v", err)
			}
		} else {
			log.Fatalf("Big error squar root: %v", err)
		}
	}

	log.Println("squar root of ", number, resp.GetSquarRoot())
}
