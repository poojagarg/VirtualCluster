#!/bin/bash
top -bn1 | grep "Cpu(s)" |sed "s/.*, *\([0-9.]*\)%* id.*/\1/"|awk '{print 100 - $1}'>> /mnt/kvmshared/poojaCloud/usageStat

#keeps usageStatistic of 