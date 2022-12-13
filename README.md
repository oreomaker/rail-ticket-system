# The Rail Ticket System

this is a simple system to buy tickets for a train

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
[drogon framework](https://github.com/drogonframework/drogon/wiki/CHN-02-%E5%AE%89%E8%A3%85)

[cpp-httplib](https://github.com/yhirose/cpp-httplib)

fmt

jwt-cpp

It'll be recommend to install them by vcpkg

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