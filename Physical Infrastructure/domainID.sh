virsh list | grep running | sed "s/ \([0-9]*\) .*/\1/" | awk '{print $1}' > domainID
