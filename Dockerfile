FROM ubuntu:latest as base

RUN apt-get -y update && \
    apt-get -y upgrade && \
    apt-get --no-install-recommends install -y adduser ca-certificates cmake curl git ninja-build mingw-w64 unzip && \
    apt-get clean

RUN addgroup --system nonroot && \
    adduser --system --group nonroot

USER nonroot

ENV CXX=/usr/bin/x86_64-w64-mingw32-g++
ENV CC=/usr/bin/x86_64-w64-mingw32-gcc

WORKDIR /workdir

RUN git clone https://github.com/andvib/ferd && \
    cd ferd && \
    git submodule init && \
    git submodule update

RUN curl -L -o glfw.zip https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
RUN unzip glfw.zip -d ferd/ext/
RUN mv ferd/ext/glfw-3.4 ferd/ext/glfw

RUN curl -L -o glew.zip https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip
RUN unzip glew.zip -d ferd/ext/
RUN mv ferd/ext/glew-2.1.0 ferd/ext/glew
