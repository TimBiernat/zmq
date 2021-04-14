# sudo docker build -t tbiernat/echo .
# sudo docker run -it --name echo --rm -v /tmp:/tmp tbiernat/echo /echo ipc:///tmp/test.ipc

FROM alpine as build-env
RUN apk add --no-cache czmq-dev build-base git

RUN git clone https://github.com/TimBiernat/zmq.git

WORKDIR /zmq/echo
RUN gcc echo.c -o echo -lczmq

FROM alpine
RUN apk add --no-cache czmq-dev
COPY --from=build-env /zmq/echo/echo .

#CMD ["./echo","ipc:///tmp/test.ipc"] 
