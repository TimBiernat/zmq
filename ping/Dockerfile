# sudo docker build -t tbiernat/ping .
# sudo docker run -it --name ping --rm -v /tmp:/tmp tbiernat/ping /app/ping ipc:///tmp/test.ipc 10 256

FROM alpine as build-env
RUN apk add --no-cache czmq-dev build-base

WORKDIR /app
COPY . .
RUN gcc ping.c -o ping -lczmq

FROM alpine
RUN apk add --no-cache czmq-dev
COPY --from=build-env /app/ping /app/ping

#CMD ["/app/ping","ipc:///tmp/test.ipc","10","256"] 
