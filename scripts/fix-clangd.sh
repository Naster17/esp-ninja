#!/bin/bash

sed -i 's/-mlongcalls/-I./g' compile_commands.json
sed -i 's/-fstrict-volatile-bitfields/-I./g' compile_commands.json
sed -i 's/-fno-tree-switch-conversion/-I./g' compile_commands.json
sed -i 's/-fno-shrink-wrap/-I./g' compile_commands.json
