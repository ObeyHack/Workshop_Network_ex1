# Exercise #1: Benchmarking Throughput

## Goal 
The goal of this exercise is to learn how to measure point-to-point (unidirectional) throughput, by writing a C/C++ benchmark application on top of TCP sockets.
/home/michael/CLionProjects/Workshop-Network-ex1/cmake-build-debug/client

## Output
```output
Running client...
Connected to server
Interval is 5000

Throughput for 1 bytes is 0.581395
Throughput for 2 bytes is 0.047668
Throughput for 4 bytes is 0.094480
Throughput for 8 bytes is 4.600345
Throughput for 16 bytes is 0.374059
Throughput for 32 bytes is 19.104478
Throughput for 64 bytes is 1.500410
Throughput for 128 bytes is 66.805846
Throughput for 256 bytes is 110.678772
Throughput for 512 bytes is 224.758560
Throughput for 1024 bytes is 230.526790
Throughput for 2048 bytes is 487.386959
Throughput for 4096 bytes is 638.403990
Throughput for 8192 bytes is 838.485159
Throughput for 16384 bytes is 1071.550033
Throughput for 32768 bytes is 1221.410467
Throughput for 65536 bytes is 1329.087996
Throughput for 131072 bytes is 1368.012358
Throughput for 262144 bytes is 1388.048163
Throughput for 524288 bytes is 1197.882466
Throughput for 1048576 bytes is 1199.325178
Average throughput is 569.933279


Client closed
```



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
