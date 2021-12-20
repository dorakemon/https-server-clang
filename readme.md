# HTTPS Server by Clang

## Enviroment

create Docker and execute bash

``` shell
./setup.sh
./exec.sh
```

## How to compile and execute

### HTTP

```shell
gcc main.c HTTPServer.c RequestHandler.c ResponseHandler.c FileHandler.c DieWithError.c Time.c
./a.out <Any PORT num>
```

### HTTPS

create private key and certification

```shell
cd secret
genrsa 2048 > server.key
openssl req -new -key server.key > server.csr
openssl x509 -req -days 365 -signkey server.key < server.csr > server.crt
```

```shell
gcc main.c HTTPSServer.c RequestHandler.c ResponseHandler.c FileHandler.c DieWithError.c Time.c -lssl -lcrypto
./a.out
```

## Usage

Access http://0.0.0.0:8080/dist/index.html
