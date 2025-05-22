
#!/bin/sh

# Extraer el número de versión de Status.h
VERSION=$(grep 'const uint32_t version' tinyGS/src/Status.h | sed -E 's/.*= ([0-9]+);.*/\1/')

esp32_build_dir=".pio/build/heltec_wifi_lora_32big"
esp32s3_build_dir=".pio/build/heltec_wifi_lora_32_V3big"

esptool.py --chip esp32 merge_bin -o esp32_${VERSION}_merged.bin --flash_mode dio --flash_size 4MB \
  0x1000 ${esp32_build_dir}/bootloader.bin \
  0x8000 ${esp32_build_dir}/partitions.bin \
  0x10000 ${esp32_build_dir}/firmware.bin

esptool.py --chip esp32-s3 merge_bin -o esp32_s3_${VERSION}_merged.bin --flash_mode dio --flash_size 4MB \
  0x1000 ${esp32s3_build_dir}/bootloader.bin \
  0x8000 ${esp32s3_build_dir}/partitions.bin \
  0x10000 ${esp32s3_build_dir}/firmware.bin