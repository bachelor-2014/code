#!/bin/bash

set -x
socket="/tmp/mendel.sock"
config="../basic_config"
mendel_cmd="/usr/bin/mendel.elf"

(cd node ; echo "" > $socket)
(cd node ; tail -f $socket | $mendel_cmd &)
(cd node ; ./run.js $config $socket)

echo "ok"
