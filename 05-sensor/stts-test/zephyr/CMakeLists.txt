cmake_minimum_required(VERSION 3.13.1)

set(ENV{DTC_OVERLAY_FILE} lora_e5_dev_board.overlay)
include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(zephyr)

FILE(GLOB app_sources ../src/*.c*)
target_sources(app PRIVATE ${app_sources})
