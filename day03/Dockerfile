FROM gcc:11.2.0 as BASE
COPY aoc.cpp .
RUN  g++ ./aoc.cpp -std=c++20 -Ofast -march=native -flto -Wall -Werror -o /bin/aoc

FROM debian:unstable-slim
COPY --from=BASE /bin/aoc /bin/aoc
COPY input.txt .
ENTRYPOINT /bin/aoc