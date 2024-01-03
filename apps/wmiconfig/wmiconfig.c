/*
 * Copyright (c) 2011 Qualcomm Atheros, Inc.
 * All Rights Reserved. 
 * Qualcomm Atheros Confidential and Proprietary. 
 * 
 * $ATH_LICENSE_HOSTSDK0_C$
 *
 *
 */
#include <sys/types.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/types.h>
#include <linux/if.h>
#include <linux/wireless.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "wmiconfig.h"

typedef struct ioctl_wcmd{        
    union {
        struct ifreq     rq;
        //struct iwreq    iw;
    } u;
    uint32_t         cmd;        
    uint32_t         ivalue;
}ioctl_wcmd_t;

const char *progname;
const char commands[] =
"commands:\n\
--usbsuspend \n\
    suspend usb traffic \n\
--htcapallzero \n\
    set all vap's ht cap to 0 \n\
--uapsdon \n\
    set uapsd on for testing purpose \n\
--uapsdoff \n\
    set uapsd off for testing purpose \n\
--ap_keepalive_off \n\
    set AP keep alive off for testing purpose \n\
--diagread\n\
--diagwrite\n\
";

static void
usage(void)
{
    fprintf(stderr, "usage:\n%s [-i device] commands\n", progname);
    fprintf(stderr, "%s\n", commands);
    fprintf(stderr, "The options can be given in any order\n");
    exit(-1);
}

int
main (int argc, char **argv)
{
    int c, s;
    char ifname[IFNAMSIZ];
    unsigned int cmd = 0;
    progname = argv[0];
    struct ifreq ifr;
    struct iwreq iwr;
    ioctl_wcmd_t wcmd;
    //char *buf = malloc(sizeof(PACKET_LOG));
	char *buf = malloc(4096);
    int clearstat = 0;
    unsigned int *diagaddr = (unsigned int *)(buf + 4);
    unsigned int *diagdata = (unsigned int *)(buf + 8);

    char *ethIf;

    if (argc == 1) {
        usage();
    }

    memset(buf, 0, sizeof(buf));
    memset(ifname, '\0', IFNAMSIZ);
    if ((ethIf = getenv("NETIF")) == NULL) {
        ethIf = "eth1";
    }
    strcpy(ifname, ethIf);
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        err(1, "socket");
    }

    while (1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"usbsuspend",0, NULL, WMI_SET_USB_SUSPEND}, 
            {"htcapallzero",0, NULL, WMI_SET_HTCAP_ALLZERO}, 
            {"uapsdon",0, NULL, WMI_SET_UAPSD_ON}, 
            {"uapsdoff",0, NULL, WMI_SET_UAPSD_OFF}, 	
            {"ap_keepalive_off",0, NULL, WMI_SET_AP_KEEPALIVE_OFF},
            {"diagaddr", 1, NULL, DIAG_ADDR},
            {"diagdata", 1, NULL, DIAG_DATA},
            {"diagread", 1, NULL, DIAG_READ},
            {"diagwrite", 2, NULL, DIAG_WRITE},
            {0, 0, 0, 0}
        };

        c = getopt_long(argc, argv, "rsvda:b:c:e:h:f:g:h:i:l:p:q:r:w:n:t:u:x:y:z:A:B:C:D:E:F:G:H:I:J:K:L:M:N:O:P:Q:R:S:T:U:V:W:X:Y:Z:", long_options, &option_index);
        if (c == -1)
        break;
        switch (c) {
        case 'i':
            memset(ifname, '\0', 8);
            strcpy(ifname, optarg);
            break;
        case WMI_SET_USB_SUSPEND:
            cmd = WMI_SET_USB_SUSPEND;
            break;
        case WMI_SET_HTCAP_ALLZERO:
            cmd = WMI_SET_HTCAP_ALLZERO;
            break;
        case WMI_SET_UAPSD_ON:
            cmd = WMI_SET_UAPSD_ON;
            break;
        case WMI_SET_UAPSD_OFF:
            cmd = WMI_SET_UAPSD_OFF;
            break;
	    case WMI_SET_AP_KEEPALIVE_OFF:
			cmd = WMI_SET_AP_KEEPALIVE_OFF;
			break;

        case DIAG_ADDR:
            *diagaddr = strtoul(optarg, (char **)NULL, 0);
            printf("addr: 0x%x\n", *diagaddr);
            break;
        case DIAG_DATA:
            *diagdata = strtoul(optarg, (char **)NULL, 0);
            printf("data: 0x%x\n", *diagdata);
            break;
        case DIAG_READ:
            *diagaddr = strtoul(optarg, (char **)NULL, 0);
            printf("addr: 0x%x\n", *diagaddr);
            cmd = DIAG_READ;
            break;
        case DIAG_WRITE:
            *diagaddr = strtoul(argv[argc-2], (char **)NULL, 0);
            printf("addr: 0x%x\n", *diagaddr);
            *diagdata = strtoul(argv[argc-1], (char **)NULL, 0);
            printf("data: 0x%x\n", *diagdata);
            cmd = DIAG_WRITE;
            break;
			
       default:
            usage();
            break;
        }
    }

	
    strncpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));
    memset(&iwr, 0, sizeof(iwr));
    strncpy(iwr.ifr_name, ifname, sizeof(iwr.ifr_name));

    switch (cmd) {
    case WMI_SET_USB_SUSPEND:
        ((int *)buf)[0] = AR6000_XIOCTL_WMI_SET_USB_SUSPEND;
        ifr.ifr_data = buf;
        if (ioctl(s, AR6000_IOCTL_EXTENDED, &ifr) < 0)
        {
            err(1, "%s", ifr.ifr_name);
        }
        break;

    case WMI_SET_HTCAP_ALLZERO:
        ((int *)buf)[0] = AR6000_XIOCTL_WMI_SET_HT_CAP_ALL_ZERO;
        ifr.ifr_data = buf;
        if (ioctl(s, AR6000_IOCTL_EXTENDED, &ifr) < 0)
        {
            err(1, "%s", ifr.ifr_name);
        }
        break;

    case WMI_SET_UAPSD_ON:
        ((int *)buf)[0] = AR6000_XIOCTL_WMI_SET_UAPSD_ON;
        ifr.ifr_data = buf;
        if (ioctl(s, AR6000_IOCTL_EXTENDED, &ifr) < 0)
        {
            err(1, "%s", ifr.ifr_name);
        }
        break;

    case WMI_SET_UAPSD_OFF:
        ((int *)buf)[0] = AR6000_XIOCTL_WMI_SET_UAPSD_OFF;
        ifr.ifr_data = buf;
        if (ioctl(s, AR6000_IOCTL_EXTENDED, &ifr) < 0)
        {
            err(1, "%s", ifr.ifr_name);
        }

        break;

    case WMI_SET_AP_KEEPALIVE_OFF:
        ((int *)buf)[0] = AR6000_XIOCTL_WMI_SET_AP_KEEPALIVE_OFF;
        ifr.ifr_data = buf;
        if (ioctl(s, AR6000_IOCTL_EXTENDED, &ifr) < 0)
        {
            err(1, "%s", ifr.ifr_name);
        }

        break;

    case DIAG_READ:
        ((int *)buf)[0] = AR6000_XIOCTL_DIAG_READ;
        ifr.ifr_data = buf;
        if (ioctl(s, AR6000_IOCTL_EXTENDED, &ifr) < 0)
        {
            err(1, "%s", ifr.ifr_name);
        }

        printf("diagdata: 0x%x\n", *diagdata);
        break;
    case DIAG_WRITE:
        ((int *)buf)[0] = AR6000_XIOCTL_DIAG_WRITE;
        ifr.ifr_data = buf;
        if (ioctl(s, AR6000_IOCTL_EXTENDED, &ifr) < 0)
        {
            err(1, "%s", ifr.ifr_name);
        }
        break;

    default:
        usage();
    }

    exit (0);
}


