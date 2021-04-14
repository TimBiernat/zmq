# sudo docker build -t tbiernat/ping .
# sudo docker run -it --name ping --rm -v /tmp:/tmp tbiernat/ping /ping ipc:///tmp/test.ipc 10 256

FROM alpine as build-env
RUN apk add --no-cache czmq-dev build-base git

RUN git clone https://github.com/TimBiernat/zmq.git

WORKDIR /zmq/ping

RUN gcc ping.c -o ping -lczmq

FROM alpine
RUN apk add --no-cache czmq-dev
COPY --from=build-env /zmq/ping/ping .

#CMD ["/ping","ipc:///tmp/test.ipc","10","256"] 
