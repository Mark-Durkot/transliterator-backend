#/bin/bash

docker stop transliterator-backend
docker run -p 8080:8080 -p 1234:1234 --name=transliterator-backend markdurkot/transliterator-backend:latest
