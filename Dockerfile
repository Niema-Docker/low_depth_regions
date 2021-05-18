# Minimal Docker image for low_depth_regions using Alpine base
FROM alpine:latest
MAINTAINER Niema Moshiri <niemamoshiri@gmail.com>

# install low_depth_regions
RUN apk update && \
    apk add bash && \
    wget -O /usr/local/bin/low_depth_regions "https://github.com/Niema-Docker/low_depth_regions/releases/download/1.0.0/low_depth_regions_binary-alpine" && \
    chmod a+x /usr/local/bin/low_depth_regions
