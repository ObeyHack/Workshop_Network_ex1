# Exercise #1: Benchmarking Throughput

## Goal 
The goal of this exercise is to learn how to measure point-to-point (unidirectional) throughput, by writing a C/C++ benchmark application on top of TCP sockets. 

## Makefile
create 2 objects: **server** and **client**.

## CMakelists.txt
```CMakelists.txt
cmake_minimum_required(VERSION 3.25)
project(Workshop_Network_ex1 C)

set(CMAKE_C_STANDARD 11)

add_executable(client client.c)
add_executable(server server.c)
```

## git clone
```bash
git clone https://github.com/ObeyHack/Workshop-Network-ex1.git
```

## git pull
```bash
git pull
```


## Server IPs
```bash
mlx-stud-01 - 132.65.164.101, 10.164.164.101
mlx-stud-02 - 
mlx-stud-03
mlx-stud-04
```

## Compile
```bash
make all
```

## Run
```bash
./server 132.65.164.101
./client
```

