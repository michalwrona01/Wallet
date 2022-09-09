FROM alpine:latest

RUN apk update && apk upgrade

RUN apk add g++

RUN apk add git
RUN apk add make
RUN apk add cmake

ADD . /service

WORKDIR /service/utility

RUN ./install-oatpp-modules.sh Release

WORKDIR /service/build

RUN cmake ..
RUN make

