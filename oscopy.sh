make clean
make all
rm /Volumes/boot/kernel.img
rm /Volumes/boot/kernel7.img
cp kernel.img /Volumes/boot/kernel.img
cp kernel.img /Volumes/boot/kernel7.img
sudo umount /Volumes/boot