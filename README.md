# The Rail Ticket System

This is a simple system to simulate the process of buying a rail ticket

It uses [drogon framework](https://github.com/drogonframework/drogon) as the backend and cpp-httplib as the client

## How to run

requirements:

### mariadb
```bash
sudo apt install mariadb-server
```
in macOS
```bash
brew install mariadb
```
### Others
drogon framework

[cpp-httplib](https://github.com/yhirose/cpp-httplib)

fmt

jwt-cpp

It'll be recommend to install them using vcpkg

```bash
git clone https://github.com/Microsoft/vcpkg.git
./vcpkg/bootstrap-vcpkg.sh

vcpkg integrate install

vcpkg install [packages to install]
```

to install these dependencies using vcpkg
```bash
[path to vcpkg] install drogon drogon[mysql] cpp-httplib fmt jwt-cpp
```

### Build
```bash
mkdir build
./build.sh
```

### Run
```bash
# to run the server
./serve.sh
# to run the client
./client.sh
```