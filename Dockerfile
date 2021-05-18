# Minimal Docker image for low_depth_regions using Alpine base
FROM alpine:latest
MAINTAINER Niema Moshiri <niemamoshiri@gmail.com>

# install low_depth_regions
RUN apk update && \
    apk add bash python3 && \
    wget -O /usr/local/bin/low_depth_regions.py "https://raw.githubusercontent.com/niemasd/tools/master/low_depth_regions.py" && \
    chmod a+x /usr/local/bin/low_depth_regions.py
