#define _GNU_SOURCE
#include <netinet/ip.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/syscall.h>
#include <sys/mman.h>
#include <pthread.h>
#include <errno.h>

#define PACKET_SIZE 0x208

int sendfun(void *pvParm1)

{
  int bVar1;
  int __fd;
  int iVar2;
  ssize_t sVar3;
  int iVar4;
  int *piVar5;
  char *__format;
  int bVar6;
  char acStack1176 [1024];
  struct sockaddr local_98 [7];
  int local_28;
  
  local_28 = 1;
  __fd = socket(1,1,0);
  if (__fd < 0) {
    puts("lib: Unable to create socket:hwnff_operation");
    iVar2 = -1;
    goto LAB_00010b88;
  }
  __aeabi_memclr8(local_98,0x6e);
  local_98[0].sa_family = 1;
  __strlcpy_chk((uint)local_98 | 2,"#hwnff",0x6c,0x6c);
  local_98[0].sa_data[0] = 0;
  iVar2 = connect(__fd,local_98,8);
  if (iVar2 == -1) {
    __format = "Lib:%s: Connection daemon failed !!\n";
LAB_00010b58:
    printf(__format,"hwnff_operation");
    iVar2 = -1;
  }
  else {
    __aeabi_memclr4((int)pvParm1 + 8,0x200);
    sVar3 = send(__fd,pvParm1,PACKET_SIZE,0);
    if (sVar3 < 0) {
      __format = "Lib:%s: Send to server failed !!\n";
      goto LAB_00010b58;
    }
    bVar1 = 0;
    do {
      while( 1 ) {
        __aeabi_memclr8(acStack1176,0x400);
        iVar2 = recv(__fd,acStack1176,0x400,0x400);
        if (iVar2 < 0) break;
        if (bVar1) {
          iVar4 = strcmp(acStack1176,"HWNFFDATAEND");
          if (iVar4 == 0) goto LAB_00010b76;
          printf("%s",acStack1176);
        }
        else {
          iVar4 = strcmp(acStack1176,"HWNFFDATASTART");
          bVar1 = 1;
          if (iVar4 != 0) {
            puts("errro start data");
            goto LAB_00010b76;
          }
        }

        
      }
      piVar5 = (int *)__errno();
      iVar4 = *piVar5;
      bVar6 = iVar4 == 0xb;
      if (!bVar6) {
        iVar4 = *piVar5;
      }
    } while (bVar6 || iVar4 == 0xb);
    iVar4 = *piVar5;
    __format = strerror(*piVar5);
    printf("recv error %d(%s)\n",iVar4,__format);
LAB_00010b76:
    putchar(10);
    if (__fd < 0) goto LAB_00010b88;
  }
  close(__fd);
LAB_00010b88:
  return -1;
}

void main() {
    int i = 0;
    for (i = 0; i < 10; i++) {
        switch (i) {
            case 0:
                printf("/sys/class/power_supply/battery/temp: ");
                break;
            case 1:
                printf("/sys/class/power_supply/battery/voltage_now: ");
                break;
            case 2:
                printf("Mobile Signal Strength Info: ");
                break;
            case 6:
                printf("HWNFF Server Version: ");
                break;
            case 7:
                printf("ro.board.platform,ro.product.platform: ");
                break;
            case 8:
                printf("bootloader status: ");
                break;
        }
        char buf[PACKET_SIZE];
        memset(&buf, 0x0, sizeof(buf));
        buf[4] = i;
        sendfun(buf);
    }
}
