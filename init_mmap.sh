mkdir -p log/
dd if=/dev/zero of=log/ColorSensorLog.bin bs=8192 count=2
dd if=/dev/zero of=log/DebugLog.bin bs=8192 count=32
