# Build Environment
FROM ubuntu:22.04

# Set working directory inside container
WORKDIR /app

# Install build dependencies
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    cmake \
	doxygen \
    graphviz \
	libssl-dev \
	python3-pip \
	rapidjson-dev \
    git && \
    rm -rf /var/lib/apt/lists/* # clean app cache

# Copy the project directory into container
COPY . .

# Create a build directory and navigate into it
RUN mkdir build
WORKDIR /app/build

# Configure CMake
RUN cmake .. -DCMAKE_BUILD_TYPE=Release

# Build the project
RUN cmake --build .

CMD ["./ValueInvest"]