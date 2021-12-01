FROM gcc:11.2.0 as BASE
COPY aoc.cpp .
RUN  g++ -std=c++20 ./aoc.cpp -o /bin/aoc

FROM debian:buster-slim
COPY --from=BASE /bin/aoc /bin/aoc
COPY input.txt .
ENTRYPOINT /bin/aoc