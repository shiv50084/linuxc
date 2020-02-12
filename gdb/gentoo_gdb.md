# using gdb debug qemu on gentoo

安装相关软件

	emerge dev-util/debugedit

编译需要调试的软件(也可以写在make.conf中)

	CFLAGS="-O1 -pipe -ggdb" CXXFLAGS="${CFLAGS}" USE=debug FEATURES="nostrip installsources" emerge app-emulation/qemu

启动调试

	$ gdb --tui -d /usr/src/debug/app-emulation/qemu-4.2.0-r1/qemu-4.2.0 --args qemu-system-x86_64 -enable-kvm -cpu host,kvm=off -machine pc-i440fx-2.7,accel=kvm,usb=off,dump-guest-core=off,mem-merge=off -smp 2 -m 2048 -realtime mlock=off -boot d -hda guest.qcow2 -name ubuntuvm

相关调试设置

	(gdb) handle SIGUSR1 nostop noprint
	(gdb) b pc_init1
	(gdb) b pci_bus_irqs
	(gdb) b i440fx_init
	(gdb) b pci_register_root_bus
