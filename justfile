set shell := ["bash", "-c"]

profile := "conan/profile/dev"

deps:
    conan install . -pr {{profile}} --build=missing --output-folder=build

configure:
    source build/conanbuild.sh && cmake -S . -B build/dev -G Ninja -DCMAKE_TOOLCHAIN_FILE=$PWD/build/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug

build:
    cmake --build build/dev

smoke: build
    ./build/dev/proto_smoke

agent: build
    ./build/dev/kopala_agent

client: build
    ./build/dev/kopala_client
