# Stage 1: Build the application
FROM ubuntu:23.04 AS build

# Update and install necessary packages
# Install necessary dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    qtbase5-dev \ 
    qt5-qmake \
    qt6-base-dev \
    qt6-httpserver-dev \
    qt6-websockets-dev

# Set up environment variables for Qt
ENV QTDIR /usr/lib/qt6
ENV PATH "$QTDIR/bin:$PATH"

# Create app directory
RUN mkdir /app

# Set working directory
WORKDIR /app

# Copy source code
COPY . .

# Build the application
RUN qmake && make

# Runtime stage
FROM ubuntu:23.04 AS runtime

# Update and install necessary packages
RUN apt-get update && apt-get install -y \
    qt6-base-dev \
    qt6-websockets-dev \
    qt6-httpserver-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Set up environment variables for Qt
ENV QTDIR /usr/lib/qt6
ENV PATH "$QTDIR/bin:$PATH"

# Create app directory
RUN mkdir /app

# Set working directory
WORKDIR /app

# Copy built application from the build stage
COPY --from=build /app/TransliteratorBackend .

# Expose ports
EXPOSE 1234
EXPOSE 8080

# Start the application
CMD ["./TransliteratorBackend", "-platform", "xcb"]