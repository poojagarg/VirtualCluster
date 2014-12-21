#!/bin/bash
cat usageStat|sed "s/.* load average: \([0-9.]*\) .*/\1/" | awk '{print $1*100}' > finalUsageStat

