# Build Environment
FROM ubuntu:22.04 as builder

# Set working directory inside the container
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
	sqlite3 \
    git && \
    rm -rf /var/lib/apt/lists/* # clean app cache
	
RUN pip install conan

# Copy the entire project directory into the container
COPY . .

# Create a build directory and navigate into it
RUN mkdir build
WORKDIR /app/build

# Configure CMake
# -DCMAKE_BUILD_TYPE=Release: Sets the build type to Release for optimization
RUN cmake .. -DCMAKE_BUILD_TYPE=Release

# Build the project
RUN cmake --build .

# (Optional) You can choose to run the application directly if it's a simple executable
CMD ["./ValueInvest"]