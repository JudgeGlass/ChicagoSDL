from debian
workdir /code
run uname -a
run apt-get update
run apt-get install -y make g++ gcc libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev
cmd ["make", "all"]