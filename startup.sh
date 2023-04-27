#/bin/bash

docker stop transliterator-backend
docker rm transliterator-backend
docker rmi markdurkot/transliterator-backend:latest
docker run -p 8080:8080 -p 1234:1234 --name=transliterator-backend -it markdurkot/transliterator-backend:latest
docker logs transliterator-backend > docker.log 2>&1
