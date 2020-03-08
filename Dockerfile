FROM ubuntu:19.04

RUN apt-get update && apt-get install -y vim build-essential cmake libgtest-dev libboost-all-dev libeigen3-dev
