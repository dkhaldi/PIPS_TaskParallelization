#! /bin/bash
while [ $# -ne 0 ] ; do
  last=$1
  shift
done
cat $last
