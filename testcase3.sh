cd /usr/src/hw3-cse506g/hw3
make clean
make
sh install_modules.sh
echo "Lent semper cursus arcu. Donec a metus at ante consectetur pretium. Phasellus viverra tempus fringilla. In hac habitasse platea dictumst. Interdum et malesuada fames ac ante ipsum primis in faucibus. Fusce porta convallis diam eu aliquam. Mauris nisl leo, venenatis non semper at, ultricies vitae enim." >temp1.txt
./xclone2 temp1.txt
./xclone2 -m temp1.txt tmp.txt

./xclone2 -g temp1.txt

./xclone2 -m temp1.txt

./xclone2 -p /usr/trashbin


