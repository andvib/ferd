FROM ubuntu:24.04

# Install build dependencies
RUN apt-get -y update && \
    apt-get -y upgrade && \
    apt-get --no-install-recommends install -y \
        ca-certificates \
        cmake \
        curl \
        git \
        mingw-w64 \
        ninja-build \
        unzip && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* && \
    addgroup --system nonroot && \
    adduser --system --group nonroot

# Set up MinGW environment for Windows cross-compilation
ENV CXX=/usr/bin/x86_64-w64-mingw32-g++
ENV CC=/usr/bin/x86_64-w64-mingw32-gcc

# Download and set up GLFW
WORKDIR /deps
RUN chown nonroot:nonroot /deps

USER nonroot
ADD https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip /deps/glfw.zip
RUN unzip glfw.zip && \
    rm glfw.zip

# Download and set up GLEW
RUN curl -L -o glew.zip https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip && \
    unzip glew.zip && \
    mv glew-2.1.0 glew && \
    rm glew.zip

# Set working directory for builds
WORKDIR /workspace
USER root
RUN chown nonroot:nonroot /workspace
USER nonroot
 