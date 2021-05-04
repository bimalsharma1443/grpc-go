package main

import (
	"context"
	"fmt"
	"gRPC/grpc-go-src/calculator/calculatorpb"
	"io"
	"log"
	"math"
	"net"
	"time"

	"google.golang.org/grpc/credentials"
	"google.golang.org/grpc/reflection"

	"google.golang.org/grpc"
	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/status"
)

type server struct {
	calculatorpb.UnimplementedCalculatorServiceServer
}

func main() {
	log.Printf("calculator server is starting")

	certFile := "ssl/server.crt"
	keyFile := "ssl/server.key"

	creds, err := credentials.NewServerTLSFromFile(certFile, keyFile)

	if err != nil {
		log.Fatalf("failed to start server, %v", err)
	}

	lis, err := net.Listen("tcp", "0.0.0.0:50051")

	if err != nil {
		log.Fatalf("failed to start server, %v", err)
	}

	newServer := grpc.NewServer(grpc.Creds(creds))

	reflection.Register(newServer)

	calculatorpb.RegisterCalculatorServiceServer(newServer, &server{})

	if err = newServer.Serve(lis); err != nil {
		log.Fatalf("this is a server error, %v", err)
	}

}

func (server *server) Calculator(ctx context.Context, req *calculatorpb.CalculatorRequest) (*calculatorpb.CalculatorResponse, error) {
	log.Printf("unary api request is, %v", req)

	firstNumber := req.GetFirstNumber()
	secondNumber := req.GetSecondNumber()

	sum := firstNumber + secondNumber

	res := &calculatorpb.CalculatorResponse{
		Sum: sum,
	}

	return res, nil

}

func (server *server) PrimeNumberDecomposition(req *calculatorpb.PrimeNumberDecompositionRequest, strem calculatorpb.CalculatorService_PrimeNumberDecompositionServer) error {
	log.Printf("server side streaming request is, %v", req)

	number := req.GetNumber()
	devision := int64(2)
	for number > 1 {
		if number%devision == 0 {
			strem.Send(&calculatorpb.PrimeNumberDecompositionResponse{
				Devisior: devision,
			})
			number = number / 2
		} else {
			devision++
			fmt.Printf("incarease devision,%v , number is %v \n", devision, number)
		}
		time.Sleep(time.Second)
	}

	return nil

}

func (server *server) ComputeAverage(stream calculatorpb.CalculatorService_ComputeAverageServer) error {
	log.Printf("client side streaming request is")

	sum := int32(0)
	divider := int32(1)
	average := float32(0)

	for {
		req, err := stream.Recv()

		if err == io.EOF {
			return stream.SendAndClose(&calculatorpb.ComputeAverageResponse{
				Average: average,
			})
		}

		if err != nil {
			log.Fatalf("error in reciving an error, %v", err)
		}

		sum += req.GetNumber()

		average = float32(sum) / float32(divider)
		divider++

	}

	return nil

}

func (server *server) FindMaximum(stream calculatorpb.CalculatorService_FindMaximumServer) error {
	log.Printf("BiDi streaming request is")

	max := int32(0)

	for {
		req, err := stream.Recv()

		if err == io.EOF {
			log.Fatalf("end of file, %v", err)
			return nil
		}

		if err != nil {
			log.Fatalf("error in reciving an error, %v", err)
			return err
		}

		if max < req.GetNumber() {
			max = req.GetNumber()
		}

		stream.Send(&calculatorpb.FindMaximumResponse{
			Max: max,
		})

	}

	return nil

}

func (server *server) SqaurRoot(ctx context.Context, req *calculatorpb.SqaurRootRequest) (*calculatorpb.SqaurRootResponse, error) {
	log.Printf("finding squar root of number \n")
	number := req.GetNumber()

	if number < 0 {
		return nil, status.Errorf(
			codes.InvalidArgument,
			"negative number send",
		)
	}

	resp := calculatorpb.SqaurRootResponse{
		SquarRoot: math.Sqrt(float64(number)),
	}

	return &resp, nil

}
