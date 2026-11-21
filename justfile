set shell := ["bash", "-c"]

profile := "conan/profile/dev"

deps:
    conan install . -pr {{profile}} --build=missing --output-folder=build

configure:
    source build/conanbuild.sh && cmake -S . -B build/dev -G Ninja -DCMAKE_TOOLCHAIN_FILE=$PWD/build/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug

build:
    cmake --build build/dev

agent: build
    ./build/dev/bin/kopala_agent

client: build
    ./build/dev/bin/kopala_client
