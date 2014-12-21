virsh list | grep running | sed "s/.*\(VM[0-9]*\) .*/\1/" | awk '{print $1}' >> domainNames


