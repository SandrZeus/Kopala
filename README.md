# Kopala

A native desktop control center for a self-hosted server.

## Stack

C++20, Qt 6 with QML, gRPC over mTLS, SQLite, Kubernetes, Built with CMake and Conan.

## Development setup

Reference environment: Arch Linux, x86-64, gcc 16.

Prerequisites:

```
sudo pacman -S --needed base-devel git cmake ninja gdb clang just pre-commit python-pipx ccache mold
pipx install conan
```

Dependencies (gRPC, protobuf, GoogleTest) come from Conan.

First time Conan setup:

```
conan profile detect
conan profile show -pr conan/profiles/dev
```

## License

AGPL-3.0-or-later. See [LICENSE](LICENSE).
