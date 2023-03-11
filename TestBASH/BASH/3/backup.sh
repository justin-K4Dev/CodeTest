#!/bin/bash

OF=ftp-user-bu_$(date +%Y%m%d).tar.gz
tar -czf $OF /home/ftp-user
