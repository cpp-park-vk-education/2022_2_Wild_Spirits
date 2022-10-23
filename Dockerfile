FROM gcc:latest

RUN apt update && \
    apt install -y cppcheck clang-tidy postgresql-server-dev-all && \
    apt install -y python3-pip && pip install cpplint && pip install cmake

RUN wget https://github.com/jtv/libpqxx/archive/refs/tags/7.7.4.tar.gz -O libpqxx.tar.gz && \
    tar -xzf libpqxx.tar.gz && cd libpqxx-7.7.4 && \
    cmake -DBUILD_TEST=OFF . && cmake --build . && cmake --install .

RUN wget https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz -O googletest.tar.gz && \
    tar -xzf googletest.tar.gz && cd googletest-release-1.12.1 && cmake . && make && make install
