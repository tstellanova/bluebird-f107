
#target extended /dev/cu.usbmodemE2C2C4C1
target extended  /dev/cu.usbmodemBFDC9D01

monitor connect_srst enable
monitor swdp_scan

attach 1
set mem inaccessible-by-default off


