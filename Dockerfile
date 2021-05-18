# Minimal Docker image for low_depth_regions using Alpine base
FROM alpine:latest
MAINTAINER Niema Moshiri <niemamoshiri@gmail.com>

# install low_depth_regions
RUN apk update && \
    apk add bash g++ && \
    wget "https://raw.githubusercontent.com/Niema-Docker/low_depth_regions/main/low_depth_regions.cpp" && \
    g++ -O3 -o /usr/local/bin/low_depth_regions low_depth_regions.cpp && \
    rm low_depth_regions.cpp
