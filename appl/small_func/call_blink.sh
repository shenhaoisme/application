#!/bin/sh -e
PIN=3

gpio mode $PIN out

while true; do
  gpio write $PIN 1
  sleep 0.5
  gpio write $PIN 0
  sleep 0.5
done
