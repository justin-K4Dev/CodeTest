#!/bin/bash
 
while [ ! -e ./file ]; do
# Sleep until file does exists/is created
sleep 1
done

echo "File exists"