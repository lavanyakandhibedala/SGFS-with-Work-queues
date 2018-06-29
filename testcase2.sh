cd /usr/src/hw3-cse506g/hw3
make clean
make
sh install_modules.sh
echo "
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus sagittis libero mauris, a mollis mauris finibus eu. Donec velit quam, imperdiet quis mattis tempor, posuere sit amet urna. Praesent semper cursus arcu. Donec a metus at ante consectetur pretium. Phasellus viverra tempus fringilla. In hac habitasse platea dictumst. Interdum et malesuada fames ac ante ipsum primis in faucibus. Fusce porta convallis diam eu aliquam. Mauris nisl leo, venenatis non semper at, ultricies vitae enim.

Nulla facilisi. Nullam consequat ligula ac tempor vulputate. Quisque hendrerit libero placerat tortor rutrum tincidunt. Curabitur vitae rhoncus velit. Donec non laoreet lorem. Mauris in leo ac turpis porttitor semper. Nunc ac sem tincidunt nunc porttitor porttitor nec a arcu. Nunc condimentum id sem eget viverra. Curabitur odio felis, vulputate vel condimentum vel, feugiat a nibh. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris ultrices suscipit mattis. Vestibulum in odio orci aliquam." >temp1.txt
./xclone2 -m temp1.txt

echo "
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus sagittis libero mauris, a mollis mauris finibus eu. Donec velit quam, imperdiet quis mattis tempor, posuere sit amet urna. Praesent semper cursus arcu. Donec a metus at ante consectetur pretium. Phasellus viverra tempus fringilla. In hac habitasse platea dictumst. Interdum et malesuada fames ac ante ipsum primis in faucibus. Fusce porta convallis diam eu aliquam. Mauris nisl leo, venenatis non semper at, ultricies vitae enim.

Nulla facilisi. Nullam consequat ligula ac tempor vulputate. Quisque hendrerit libero placerat tortor rutrum tincidunt. Curabitur vitae rhoncus velit. Donec non laoreet lorem. Mauris in leo ac turpis porttitor semper. Nunc ac sem tincidunt nunc porttitor porttitor nec a arcu. Nunc condimentum id sem eget viverra. Curabitur odio felis, vulputate vel condimentum vel, feugiat a nibh. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris ultrices suscipit mattis. Vestibulum in odio orci aliquam." >temp1.txt
echo "abcdefghij" >/proc/enc_key_file
./xclone2 -me temp1.txt

echo "
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus sagittis libero mauris, a mollis mauris finibus eu. Donec velit quam, imperdiet quis mattis tempor, posuere sit amet urna. Praesent semper cursus arcu. Donec a metus at ante consectetur pretium. Phasellus viverra tempus fringilla. In hac habitasse platea dictumst. Interdum et malesuada fames ac ante ipsum primis in faucibus. Fusce porta convallis diam eu aliquam. Mauris nisl leo, venenatis non semper at, ultricies vitae enim.

Nulla facilisi. Nullam consequat ligula ac tempor vulputate. Quisque hendrerit libero placerat tortor rutrum tincidunt. Curabitur vitae rhoncus velit. Donec non laoreet lorem. Mauris in leo ac turpis porttitor semper. Nunc ac sem tincidunt nunc porttitor porttitor nec a arcu. Nunc condimentum id sem eget viverra. Curabitur odio felis, vulputate vel condimentum vel, feugiat a nibh. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris ultrices suscipit mattis. Vestibulum in odio orci aliquam." >temp1.txt
./xclone2 -mc temp1.txt
echo "
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus sagittis libero mauris, a mollis mauris finibus eu. Donec velit quam, imperdiet quis mattis tempor, posuere sit amet urna. Praesent semper cursus arcu. Donec a metus at ante consectetur pretium. Phasellus viverra tempus fringilla. In hac habitasse platea dictumst. Interdum et malesuada fames ac ante ipsum primis in faucibus. Fusce porta convallis diam eu aliquam. Mauris nisl leo, venenatis non semper at, ultricies vitae enim.

Nulla facilisi. Nullam consequat ligula ac tempor vulputate. Quisque hendrerit libero placerat tortor rutrum tincidunt. Curabitur vitae rhoncus velit. Donec non laoreet lorem. Mauris in leo ac turpis porttitor semper. Nunc ac sem tincidunt nunc porttitor porttitor nec a arcu. Nunc condimentum id sem eget viverra. Curabitur odio felis, vulputate vel condimentum vel, feugiat a nibh. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris ultrices suscipit mattis. Vestibulum in odio orci aliquam." >temp1.txt

echo "jihgfedcba" >/proc/enc_key_file
./xclone2 -mce temp1.txt


./xclone2 -p /usr/trashbin


