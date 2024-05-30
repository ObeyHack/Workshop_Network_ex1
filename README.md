# Exercise #1: Benchmarking Throughput

## Goal 
The goal of this exercise is to learn how to measure point-to-point (unidirectional) throughput, by writing a C/C++ benchmark application on top of TCP sockets. 

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