cd /usr/src/hw3-cse506g/hw3
make clean
make
sh install_modules.sh
echo "sdkjfbshd" >../temp1.txt
./xclone2 -m ../temp1.txt

echo "sdkjfbshd" >../temp1.txt
echo "abcdefghij" >/proc/enc_key_file
./xclone2 -me ../temp1.txt

echo "sdkjfbshd" >../temp1.txt
./xclone2 -mc ../temp1.txt

echo "jihgfedc" >/proc/enc_key_file
./xclone2 -mce ../temp1.txt


./xclone2 -p /usr/trashbin


