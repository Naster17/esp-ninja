#!/bin/bash

python scripts/clangd_fix.py && sed -i 's/-std=gnu++2b/-std=gnu2y/g' compile_commands.json
