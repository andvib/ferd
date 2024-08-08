FROM ubuntu:24.04 AS base

RUN apt-get -y update && \
    apt-get -y upgrade && \
    apt-get --no-install-recommends install -y adduser ca-certificates cmake curl git mingw-w64 ninja-build unzip && \
    apt-get clean && \
    addgroup --system nonroot && \
    adduser --system --group nonroot

WORKDIR /workdir

ADD https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip glfw/glfw.zip
RUN mkdir downloads && \
    unzip glfw/glfw.zip -d downloads/ && \
    chown -R nonroot:nonroot . && \
    chown -R nonroot:nonroot downloads

USER nonroot

ENV CXX=/usr/bin/x86_64-w64-mingw32-g++
ENV CC=/usr/bin/x86_64-w64-mingw32-gcc

RUN git clone https://github.com/andvib/ferd && \
    cd ferd && \
    git submodule init && \
    git submodule update && \
    cd .. && \
    curl -L -o glew.zip https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip &&\
    unzip glew.zip -d ferd/ext/ &&\
    mv ferd/ext/glew-2.1.0 ferd/ext/glew && \
    mv downloads/glfw-3.4 ferd/ext/glfw
 