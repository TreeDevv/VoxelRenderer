$ErrorActionPreference = "Stop"
if (!(Test-Path external/vcpkg/.vcpkg-root)) {
    git submodule update --init --recursive external/vcpkg
    & external/vcpkg/bootstrap-vcpkg.bat
}
cmake --preset msvc-debug
cmake --build --preset build-debug