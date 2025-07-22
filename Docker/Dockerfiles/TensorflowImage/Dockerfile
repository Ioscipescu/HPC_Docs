# A base image to build off of, in this case a release from tensorflow.
FROM tensorflow/tensorflow:latest

# Sets the working directory inside of the container
WORKDIR /usr/src/app

# Copies application files from host to container
COPY . .

CMD ["python3", "tensorflow_test.py"]