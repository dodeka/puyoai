#!/bin/bash
cd "$(dirname "$0")"
exec ./mayah_cpu --num_threads=3 --opening=false "$@" 2> run.err
