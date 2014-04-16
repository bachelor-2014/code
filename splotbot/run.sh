#!/bin/bash

set -x
socket="/tmp/mendel.sock"
mendel_cmd="/usr/bin/mendel.elf"

(cd node ; echo "" > $socket)
(cd node ; tail -f $socket | $mendel_cmd &)
(cd node ; ./run.js)

echo "ok"
