# Exercise #1: Benchmarking Throughput

## Goal 
The goal of this exercise is to learn how to measure point-to-point (unidirectional) throughput, by writing a C/C++ benchmark application on top of TCP sockets.
/home/michael/CLionProjects/Workshop-Network-ex1/cmake-build-debug/client

## Output
```output
Running client...
Connected to server
Interval is 1000

Throughput for 1 bytes is 0.474383
Throughput for 2 bytes is 0.047073
Throughput for 4 bytes is 0.093751
Throughput for 8 bytes is 0.182490
Throughput for 16 bytes is 8.993817
Throughput for 32 bytes is 0.761977
Throughput for 64 bytes is 33.126294
Throughput for 128 bytes is 62.652961
Throughput for 256 bytes is 125.613346
Throughput for 512 bytes is 183.184258
Throughput for 1024 bytes is 272.630458
Throughput for 2048 bytes is 370.343580
Throughput for 4096 bytes is 442.762945
Throughput for 8192 bytes is 632.831209
Throughput for 16384 bytes is 818.095571
Throughput for 32768 bytes is 1058.192857
Throughput for 65536 bytes is 1124.849816
Throughput for 131072 bytes is 1174.648695
Throughput for 262144 bytes is 1206.718929
Throughput for 524288 bytes is 1194.291507
Throughput for 1048576 bytes is 1192.630227
Average throughput is 495.156307

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
