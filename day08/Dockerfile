FROM gcc:11.2.0 as BASE
COPY aoc.cpp input.txt ./
RUN  objcopy --input binary --output elf64-x86-64 input.txt input.o
RUN  g++ ./input.o ./aoc.cpp -std=c++20 -Ofast -march=native -flto -Wall -Werror -o /bin/aoc

FROM debian:unstable-slim
COPY --from=BASE /bin/aoc /bin/aoc
COPY input.txt ./
ENTRYPOINT /bin/aoc
