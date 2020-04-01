FROM node:alpine
MAINTAINER Ed Asriyan <ed-asriyan@protonmail.com>

RUN apk update && apk add --no-cache autoconf automake cmake g++ git libtool make
RUN git clone https://github.com/samkrew/libmbus && \
    cd libmbus && \
    autoheader && aclocal && libtoolize --ltdl --copy --force && automake --add-missing --copy && autoconf && \
    ./configure && make && make install && \
    cd .. && rm -fr libmbus

WORKDIR /application

ADD package.json .
ADD meter ./meter
RUN cd meter && cmake CMakeLists.txt && make && npm install

ADD config.json .
ADD database.js .
ADD index.js .

CMD npm start -- --interval $INTERVAL --device $DEVICE --db-uri $DB_URI
