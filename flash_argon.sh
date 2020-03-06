#!/bin/bash

set -e
set -x

echo "Usage: $0 <user-firmware>"

OPENOCD_ROOT="$HOME/.particle/toolchains/openocd/0.11.2-adhoc6ea4372.0"

$OPENOCD_ROOT/bin/openocd -f interface/cmsis-dap.cfg -f target/nrf52-particle.cfg \
    -c "adapter_khz 1000" \
    -c "transport select swd" \
    -c "init" \
    -c "program $1 0xD4000 verify reset" \
    -c "exit"
