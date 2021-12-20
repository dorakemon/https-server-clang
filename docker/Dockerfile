FROM ubuntu:bionic

WORKDIR /osb

RUN apt-get update && \
    apt-get -y install build-essential && \
    apt-get -y install libssl-dev && \
    apt-get -y install curl && \
    rm -rf /var/lib/apt/lists/*