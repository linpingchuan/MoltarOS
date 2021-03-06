cd libc;
make;

# If we fail to make libc, cleanup and exit
if [ $? -ne 0 ]; then
	echo "Failed to make libc!";
	make clean;
	exit;
fi

cd ../kernel;
make;

# If we fail to make the kernel, cleanup and exit
if [ $? -ne 0 ]; then
	echo "Failed to make kernel!";
	make clean;
	exit;
fi

# Move the .kernel image into the GRUB directory to prepare for build
cp MoltarOS.kernel ../tmp/iso/boot;

cd ../tmp;

# Build the CD
genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o MoltarOS.iso iso;

# If we fail to build the CD...
if [ $? -ne 0 ]; then
	echo "Failed to build the cd!";
	exit;
fi

# Finally, run the virtual machine.
bochs -f bochsrc.bxrc;
