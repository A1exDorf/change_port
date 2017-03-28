#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/tcp.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dorofeev");
MODULE_DESCRIPTION("Change destination port";)

static struct nf_hook_ops h_ops;
struct udphdr *udp_header;
struct iphdr *ip_header;

unsigned int change_port(void *priv,
		struct sk_buff *skb,
		const struct nf_hook_state *state)
{
if (skb->protocol == htons(ETH_P_IP))
{
	ip_header = (struct iphdr *)skb_network_header(skb);

	if (ip_header->protocol == IPPROTO_UDP) {
		udp_header = (struct udphdr *)skb_transport_header(skb);
		if ((udp_header->dest) == htons(7777))
		{
			udp_header->dest = htons(7778);
		}
	}
}
	return NF_ACCEPT;
}

int init_module(void)
{
	h_ops.hook = change_port;
	h_ops.pf = PF_INET;
	h_ops.hooknum = 0;
	h_ops.priority = NF_IP_PRI_FIRST;

	nf_register_hook(&h_ops);

	return 0;
}

void cleanup_module(void)
{
	nf_unregister_hook(&h_ops);
}

