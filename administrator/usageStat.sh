#!/bin/bash
cat usageStat|sed "s/.* load average: \([0-9.]*\) .*/\1/" | awk '{print $1*100}' > finalUsageStat

#appends usage-statistic of a physical node to the file finalUsageStatusage 