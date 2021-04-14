# docker build -t tbiernat/zmq-examples .
# docker run -it --name echo --rm -v /tmp:/tmp tbiernat/zmq-examples /echo ipc:///tmp/test.ipc
# docker run -it --name ping --rm -v /tmp:/tmp tbiernat/zmq-examples /ping ipc:///tmp/test.ipc 10 2048

FROM alpine as build-env
RUN apk add --no-cache czmq-dev build-base git
RUN git clone https://github.com/TimBiernat/zmq.git
WORKDIR /zmq
RUN gcc -Wall src/echo.c src/ping.c -lczmq

FROM alpine
RUN apk add --no-cache czmq-dev
COPY --from=build-env /zmq/echo/echo .
COPY --from=build-env /zmq/ping/ping .
