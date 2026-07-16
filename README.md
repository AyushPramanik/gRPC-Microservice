# grpc-microservice

A C++ gRPC microservice implementing an `OrderService`. It demonstrates a clean
server setup with unary and server-streaming RPCs, a logging interceptor, and
graceful shutdown. Order data is kept in an in-memory mock store, so the service
runs without any external dependencies.

## Features

- **OrderService** with unary RPCs (`Get`, `List`, `Create`, `Update`) and a
  server-streaming RPC (`StreamOrderUpdated`) that emits order status changes.
- **Logging interceptor** that logs every RPC method invoked.
- **Graceful shutdown** on `SIGINT` / `SIGTERM`.
- **Environment-based configuration** for host and port.
- **Thread-safe** in-memory store guarded by a mutex.

## Project structure

```
protos/order_service/order.proto   Protobuf/gRPC service definition
genproto/                          Generated protobuf + gRPC C++ code
include/config/                    Config (env-based host/port)
include/server/                    Server + logging interceptor
include/service/                   OrderService declaration
src/main.cpp                       Entry point (signals, wiring, shutdown)
src/server/server.cpp              gRPC server bootstrap
src/service/order_service.cpp      OrderService implementation
scripts/proto-gen.sh               Regenerate code from .proto files
```

## Requirements

- CMake >= 3.28
- A C++17 compiler
- Protobuf and gRPC (C++), discoverable via CMake `find_package`
- `protoc` and `grpc_cpp_plugin` on your `PATH` (only needed to regenerate protos)

On macOS these can be installed with Homebrew:

```bash
brew install cmake protobuf grpc
```

## Build

```bash
cmake -S . -B build
cmake --build build
```

The resulting binary is `build/grpc-microservice`.

## Run

```bash
./build/grpc-microservice
```

By default the server listens on `0.0.0.0:50055`. Override via environment
variables:

| Variable    | Default   | Description        |
| ----------- | --------- | ------------------ |
| `GRPC_HOST` | `0.0.0.0` | Bind host          |
| `GRPC_PORT` | `50055`   | Bind port          |

```bash
GRPC_HOST=127.0.0.1 GRPC_PORT=50051 ./build/grpc-microservice
```

The server starts with three mock orders seeded for user `1`.

## Regenerating protobuf code

After editing `protos/order_service/order.proto`, regenerate the C++ sources:

```bash
./scripts/proto-gen.sh
```

## API

Service `order_service.v1.OrderService`:

| RPC                  | Type              | Description                                  |
| -------------------- | ----------------- | -------------------------------------------- |
| `Get`                | Unary             | Fetch a single order by ID                   |
| `List`               | Unary             | List a user's orders (paginated)             |
| `Create`             | Unary             | Create a new order for a user                |
| `Update`             | Unary             | Update an existing order                     |
| `StreamOrderUpdated` | Server streaming  | Stream status changes for a given order      |

## License

See [LICENSE](LICENSE).
