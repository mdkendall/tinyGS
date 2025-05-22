
#!/bin/sh

# Extraer el número de versión de Status.h
VERSION=$(grep 'const uint32_t version' tinyGS/src/Status.h | sed -E 's/.*= ([0-9]+);.*/\1/')

build_dir=".pio/build"

esp32_dir="heltec_wifi_lora_32"
esp32s3_dir="heltec_wifi_lora_32_V3"
esp32c3_dir="esp32c3"

echo ${esp32_dir}
echo ${esp32s3_dir}
echo ${esp32c3_dir}

platformio run -e ${esp32_dir} -e ${esp32s3_dir} -e ${esp32c3_dir}

esptool.py --chip esp32 merge_bin -o esp32_${VERSION}_merged.bin --flash_mode dio --flash_size 4MB \
  0x1000  ${build_dir}/${esp32_dir}/bootloader.bin \
  0x8000  ${build_dir}/${esp32_dir}/partitions.bin \
  0x10000 ${build_dir}/${esp32_dir}/firmware.bin

esptool.py --chip esp32-s3 merge_bin -o esp32_s3_${VERSION}_merged.bin --flash_mode dio --flash_size 4MB \
  0x1000  ${build_dir}/${esp32s3_dir}/bootloader.bin \
  0x8000  ${build_dir}/${esp32s3_dir}/partitions.bin \
  0x10000 ${build_dir}/${esp32s3_dir}/firmware.bin

esptool.py --chip esp32-c3 merge_bin -o esp32_c3_${VERSION}_merged.bin --flash_mode dio --flash_size 4MB \
  0x1000  ${build_dir}/${esp32c3_dir}/bootloader.bin \
  0x8000  ${build_dir}/${esp32c3_dir}/partitions.bin \
  0x10000 ${build_dir}/${esp32c3_dir}/firmware.bin