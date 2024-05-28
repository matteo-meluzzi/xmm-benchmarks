# Use the latest Ubuntu image
FROM ubuntu:latest

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update && \
    apt-get install -y \
    wget \
    gnupg \
    software-properties-common \
    git \
    build-essential \ 
    autoconf \
    automake \
    clang-15 \
    llvm-15 \
    llvm-15-dev \
    clang-12 \
    llvm-12 \
    llvm-12-dev \
    libffi-dev \
	zlib1g-dev \ 
    libedit-dev \
    python3.10 \
    python3-pip

WORKDIR /root

RUN git clone https://github.com/eupp/genmc-xmm genmc-dev
RUN git clone https://github.com/eupp/genmc-xmm genmc-xmm
RUN git clone https://github.com/eupp/genmc-xmm genmc-wkmo
RUN git clone https://github.com/matteo-meluzzi/xmm-benchmarks xmm-benchmarks

WORKDIR /root/genmc-dev
RUN git checkout -b dev
RUN autoreconf --install
RUN ./configure --with-llvm=/usr/lib/llvm-15
RUN make

WORKDIR /root/genmc-xmm
RUN git checkout -b matteo
RUN autoreconf --install
RUN ./configure --with-llvm=/usr/lib/llvm-15
RUN make

WORKDIR /root/genmc-wkmo
RUN git checkout -b wkmo
RUN autoreconf --install
RUN ./configure --with-llvm=/usr/lib/llvm-12
RUN make

WORKDIR /root/xmm-benchmarks    
RUN pip install notebook
RUN pip install -r requirements.txt