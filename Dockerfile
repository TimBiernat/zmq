# docker build -t tbiernat/zmq-examples .
# docker run -it --name echo --rm -v /tmp:/tmp tbiernat/zmq-examples /echo ipc:///tmp/test.ipc
# docker run -it --name ping --rm -v /tmp:/tmp tbiernat/zmq-examples /ping ipc:///tmp/test.ipc 10 2048
# docker run -it --name pub --rm -v /tmp:/tmp tbiernat/zmq-examples /pub ipc:///tmp/test.ipc 100 64
# docker run -it --name sub --rm -v /tmp:/tmp tbiernat/zmq-examples /sub ipc:///tmp/test.ipc

FROM alpine as build-env
RUN apk add --no-cache czmq-dev build-base git
RUN git clone https://github.com/TimBiernat/zmq.git
WORKDIR /zmq/src
RUN gcc -Wall echo.c -o echo -lczmq
RUN gcc -Wall ping.c -o ping -lczmq
RUN gcc -Wall pub.c -o pub -lczmq
RUN gcc -Wall sub.c -o sub -lczmq

FROM alpine
RUN apk add --no-cache czmq-dev
COPY --from=build-env /zmq/src/echo .
COPY --from=build-env /zmq/src/ping .
COPY --from=build-env /zmq/src/pub .
COPY --from=build-env /zmq/src/sub .
