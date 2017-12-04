#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x5bc88bc8, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x3b270340, __VMLINUX_SYMBOL_STR(tcp_unregister_congestion_control) },
	{ 0xca2838b1, __VMLINUX_SYMBOL_STR(tcp_register_congestion_control) },
	{ 0x72d559fb, __VMLINUX_SYMBOL_STR(tcp_tso_autosize) },
	{ 0xfe719995, __VMLINUX_SYMBOL_STR(minmax_running_max) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0x7f24de73, __VMLINUX_SYMBOL_STR(jiffies_to_usecs) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xbae0e6d7, __VMLINUX_SYMBOL_STR(tcp_mss_to_mtu) },
	{ 0xa735db59, __VMLINUX_SYMBOL_STR(prandom_u32) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

