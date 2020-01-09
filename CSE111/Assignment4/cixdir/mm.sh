cd ..
rm cixdir/cix
rm cixddir/cixd
rm *.o
make
cp cix cixdir
cp cixd cixddir
cd cixdir
cix unix2.lt.ucsc.edu 65535
