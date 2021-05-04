#!/bin/bash

protoc calculator/calculatorpb/calculator.proto --go_out=.
protoc calculator/calculatorpb/calculator.proto --go-grpc_out=.