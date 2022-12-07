FROM --platform=linux/amd64 ubuntu:22.04 as builder

RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential clang

COPY . /repo
WORKDIR /repo/tools/bin2s/src
RUN gcc -o bin2s bin2s.c
RUN clang++ /repo/mayhem/fuzz_pack.cpp -fsanitize=fuzzer,address -I /repo/tools/ -o /fuzz

FROM ubuntu:22.04 as package
COPY --from=builder /repo/tools/bin2s/src/bin2s /
COPY --from=builder /fuzz /fuzz_pack
