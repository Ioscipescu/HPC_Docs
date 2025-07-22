# A base image to build off of, in this case Ubuntu
FROM ubuntu:latest

# Sets the working directory inside of the container
WORKDIR /usr/src/app

# Copies application files from host to container
COPY . .

# Installs dependencies in the container
RUN apt-get update && apt-get install -y \
    python3 \
    python3-pip

# Set the default command to execute when the container starts
CMD ["python3", "test.py"]