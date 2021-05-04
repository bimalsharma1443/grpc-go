#!/bin/bash

protoc greet/greetpb/greet.proto --go_out=.
protoc greet/greetpb/greet.proto --go-grpc_out=.