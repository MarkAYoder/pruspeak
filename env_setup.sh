insmod ./bin/pru_speak.ko
SLOTS=/sys/devices/bone_capemgr.*/slots
# Turn off HDMI and P9_41 and P9_42
echo -6 > $SLOTS
echo -7 > $SLOTS
echo -8 > $SLOTS
# Turn on pruspeak
echo BB-PRUSPEAK > $SLOTS
python src/userspace_lib/bs_fifo.py > pruspeak.log &
