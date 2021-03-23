FROM debian:buster as dev
RUN apt-get update \
    && apt install -y build-essential wget curl libmicrohttpd-dev libjansson-dev libcurl4-gnutls-dev libgnutls28-dev libgcrypt20-dev libsystemd-dev libz-dev

RUN wget https://github.com/babelouest/ulfius/releases/download/v2.7.2/ulfius-dev-full_2.7.2_debian_buster_x86_64.tar.gz \
    && tar xf ulfius-dev-full_2.7.2_debian_buster_x86_64.tar.gz \
    && dpkg -i liborcania-dev_2.2.0_debian_buster_x86_64.deb \
    && dpkg -i libyder-dev_1.4.13_debian_buster_x86_64.deb \
    && dpkg -i libulfius-dev_2.7.2_debian_buster_x86_64.deb

WORKDIR /usr/src/app

COPY . .
RUN make build

FROM debian:buster
WORKDIR /app
COPY --from=dev /usr/src/app/hello-world /app/hello-world
EXPOSE 8080
CMD ["/app/hello-world"]