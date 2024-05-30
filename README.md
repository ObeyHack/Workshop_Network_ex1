# Exercise #1: Benchmarking Throughput

## Goal 
The goal of this exercise is to learn how to measure point-to-point (unidirectional) throughput, by writing a C/C++ benchmark application on top of TCP sockets.
/home/michael/CLionProjects/Workshop-Network-ex1/cmake-build-debug/client
Running client...
Troughput for 1 bytes is 4.405286

Troughput for 2 bytes is 8.810573

Troughput for 4 bytes is 16.194332

Troughput for 8 bytes is 35.087719

Troughput for 16 bytes is 13.698630

Troughput for 32 bytes is 131.687243

Troughput for 64 bytes is 239.700375

Troughput for 128 bytes is 391.437309

Troughput for 256 bytes is 766.467066

Troughput for 512 bytes is 1765.517241

Process finished with exit code 0


## Makefile
create 2 objects: **server** and **client**.

## Server IPs
```bash
mlx-stud-01 - 132.65.164.101, 10.164.164.101
mlx-stud-02 - 132.65.164.102, 10.164.164.102
mlx-stud-03 - 132.65.164.103, 10.164.164.103
mlx-stud-04 - 132.65.164.104, 10.164.164.104
```

## git
```bash
git clone https://github.com/ObeyHack/Workshop-Network-ex1.git
```
```bash
git pull
```

## Compile
```bash
make all
```

## Run
```bash
./server 
```
```bash
./client <server_ip>
```

## Docker usage
Follow the instructions in the following link to build the docker image and run the container.
```link
https://github.com/shuhaoliu/docker-clion-dev
```
```bash
docker build -t liuempire/docker_clion_dev .
```
```bash
docker-compose up -d
```
