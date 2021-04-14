# sudo docker build -t tbiernat/echo .
# sudo docker run -it --name echo --rm -v /tmp:/tmp tbiernat/echo /app/echo ipc:///tmp/test.ipc

FROM alpine as build-env
RUN apk add --no-cache czmq-dev build-base

WORKDIR /app
COPY . .
RUN gcc echo.c -o echo -lczmq

FROM alpine
RUN apk add --no-cache czmq-dev
COPY --from=build-env /app/echo /app/echo

#CMD ["/app/echo","ipc:///tmp/test.ipc"] 
