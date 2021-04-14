# docker build -t tbiernat/zmq-examples .
# docker run -it --name echo --rm -v /tmp:/tmp tbiernat/zmq-examples /echo ipc:///tmp/test.ipc
# docker run -it --name ping --rm -v /tmp:/tmp tbiernat/zmq-examples /ping ipc:///tmp/test.ipc 10 2048

FROM alpine as build-env
RUN apk add --no-cache czmq-dev build-base git
RUN git clone https://github.com/TimBiernat/zmq.git
WORKDIR /zmq/src
RUN gcc -Wall echo.c -o echo -lczmq
RUN gcc -Wall ping.c -o ping -lczmq

FROM alpine
RUN apk add --no-cache czmq-dev
COPY --from=build-env /zmq/src/echo .
COPY --from=build-env /zmq/src/ping .
