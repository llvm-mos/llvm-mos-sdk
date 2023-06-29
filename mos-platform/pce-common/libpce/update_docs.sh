#!/bin/sh
mkdir -p build/doc
doxygen
cd build/doc/html
rsync -av -e 'ssh -p 20200' . asie@asie.pl:/var/www/domains/wonderful.asie.pl/doc/libpce  --delete
