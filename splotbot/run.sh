#!/bin/bash

set -x
socket="data/mendel.sock"
mendel_cmd="cat"

(cd node ; echo "" > $socket)
(cd node ; tail -f $socket | $mendel_cmd &)
(cd node ; ./run.js)

echo "ok"
