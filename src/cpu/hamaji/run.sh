#!/bin/bash
cd "$(dirname "$0")"
exec ./lps.sh "$@" 2> hamaji.err

