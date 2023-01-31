FROM ubuntu:latest

ENV DEBIAN_FRONTEND=nonintercative

RUN apt-get update && \
	apt-get install -y cmake build-essential libgl1-mesa-dev \
    qt6-base-dev texlive-latex-extra dvipng
	
COPY . /usr/src/apdf
WORKDIR /usr/src/apdf

RUN cmake -DCLANG_TIDY=OFF ./src && make

ENTRYPOINT [ "./APDFCreator" ]	

