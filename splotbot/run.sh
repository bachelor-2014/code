#!/bin/bash

set -x
socket="/tmp/mendel.sock"
config="../basic_config.json"
mendel_cmd="/usr/bin/mendel.elf"

(cd node ; echo "" > $socket)
(cd node ; tail -f $socket | $mendel_cmd > /dev/null 2>&1 &)
(cd node ; ./run.js $config $socket)

echo "ok"
