FROM ubuntu:24.04

RUN apt update && apt install -y git cmake meson libgmock-dev curl libcurl4-openssl-dev libpqxx* libpq-dev rapidjson-dev

COPY ../ MicroViewerBackend

RUN cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S MicroViewerBackend -B MicroViewerBackend/build
RUN cmake --build MicroViewerBackend/build --target MicroViewerBackend -j 10

ENTRYPOINT [ "/MicroViewerBackend/build/MicroViewerBackend"]