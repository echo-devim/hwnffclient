
void FUN_00102208(uint *puParm1)

{
  byte *pbVar1;
  longlong lVar2;
  byte bVar3;
  uint __fd;
  byte bVar4;
  byte bVar5;
  ssize_t sVar6;
  pthread_t __th;
  size_t sVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  long lVar11;
  ulonglong uVar12;
  undefined8 *__s;
  char *__nptr;
  ulonglong uVar13;
  longlong lVar14;
  undefined8 *puVar15;
  undefined4 local_a40;
  undefined8 local_a38;
  longlong lStack2608;
  char local_a28;
  undefined7 uStack2599;
  undefined uStack2592;
  undefined7 uStack2591;
  byte bStack2584;
  ulonglong local_a10;
  ulonglong local_a08;
  ulonglong local_a00;
  undefined8 uStack2552;
  undefined8 local_9f0;
  undefined8 uStack2536;
  undefined8 local_9e0;
  undefined8 uStack2520;
  undefined8 local_910;
  ulonglong local_908;
  undefined4 local_900;
  undefined4 local_810;
  uint local_80c;
  undefined8 local_608;
  undefined8 uStack1536;
  undefined8 local_5f8;
  undefined8 local_5f0;
  undefined8 local_8;
  
  local_8 = __stack_chk_guard;
  __fd = *puParm1;
  memset(&local_810,0,0x208);
  __android_log_print(4,"HWNFF","Daemon: hwnff_handler\n");
  sVar6 = recvfrom(__fd,&local_810,0x208,0,(sockaddr *)0x0,(socklen_t *)0x0);
  if (sVar6 < 1) {
    __android_log_print(6,"HWNFF","Daemon: Unable to recv data from client\n");
    goto LAB_00102334;
  }
  __android_log_print(4,"HWNFF","Daemon: recv\n");
  pthread_mutex_lock((pthread_mutex_t *)&__bss_start__);
  send(__fd,"HWNFFDATASTART",0xf,0);
  usleep(20000);
  printf("Daemon:  cmd Type %u\n",(ulonglong)local_80c);
  if (9 < local_80c) {
    local_810 = 0xffffffff;
    __android_log_print(6,"HWNFF","Daemon: Unknown cmd Type %u\n");
    goto LAB_00102364;
  }
  switch(local_80c) {
  case 0:
    local_a40 = 0;
    local_608 = 0;
    uStack1536 = 0;
    local_5f8 = 0;
    local_5f0 = ((ulonglong)local_5f0._4_4_ & 0xffff0000) << 0x20;
    __nptr = (char *)openFile("/sys/class/power_supply/battery/temp",&local_a40);
    if (__nptr != (char *)0x0) {
      iVar9 = atoi(__nptr);
      free(__nptr);
      if (iVar9 != 0) {
        snprintf((char *)&local_608,0x1e,"%.1f");
LAB_00102474:
        local_810 = 0;
        sVar7 = strlen((char *)&local_608);
        FUN_00101da4((ulonglong)__fd,&local_608,(ulonglong)(sVar7 + 1));
        break;
      }
    }
    goto LAB_00103098;
  case 1:
    local_a40 = 0;
    local_608 = 0;
    uStack1536 = 0;
    local_5f8 = 0;
    local_5f0 = ((ulonglong)local_5f0._4_4_ & 0xffff0000) << 0x20;
    __nptr = (char *)openFile("/sys/class/power_supply/battery/voltage_now",&local_a40);
    if (__nptr != (char *)0x0) {
      iVar9 = atoi(__nptr);
      free(__nptr);
      if (iVar9 != 0) {
        snprintf((char *)&local_608,0x1e,"%d",(ulonglong)(uint)(iVar9 / 1000));
        goto LAB_00102474;
      }
    }
LAB_00103098:
    local_810 = 0xffffffff;
    break;
  case 2:
    local_608 = 0;
    uStack1536 = 0;
    local_5f8 = 0;
    local_a10 = 0;
    local_a08 = 0;
    local_5f0 = ((ulonglong)local_5f0._4_4_ & 0xffff0000) << 0x20;
    local_910 = 0;
    local_908 = 0;
    local_a00 = local_a00 & 0xffffffff00000000;
    local_900 = 0;
    iVar9 = property_get("gsm.rssi.sim1",&local_a10,0x104158);
    if (iVar9 == 0) {
      __android_log_print(6,"HWNFF","Daemon: %s property_get gsm.rssi.sim1 fail\n","get_rssi");
    }
    iVar9 = property_get("gsm.rssi.sim2",&local_910,0x104158);
    if (iVar9 == 0) {
      __android_log_print(6,"HWNFF","Daemon: %s property_get gsm.rssi.sim2 fail\n","get_rssi");
    }
    if ((char)local_a10 == 0) {
      if ((char)local_910 == 0) goto LAB_00103098;
LAB_00102e24:
      sVar7 = strlen((char *)&local_608);
      strncat((char *)&local_608,"SIM2:",0x1d - sVar7);
      sVar7 = strlen((char *)&local_608);
      strncat((char *)&local_608,(char *)&local_910,0x1d - sVar7);
    }
    else {
      sVar7 = strlen((char *)&local_608);
      strncat((char *)&local_608,"SIM1:",0x1d - sVar7);
      sVar7 = strlen((char *)&local_608);
      strncat((char *)&local_608,(char *)&local_a10,0x1d - sVar7);
      if ((char)local_910 != 0) {
        sVar7 = strlen((char *)&local_608);
        strncat((char *)&local_608,",",0x1d - sVar7);
        goto LAB_00102e24;
      }
    }
    goto LAB_001028a0;
  case 3:
    memset(&local_a10,0,0x100);
    memset(&local_608,0,0x600);
    uVar8 = get_app_info("touch_panel",&local_a10);
    if (uVar8 >> 0x1f != 0) {
      __android_log_print(6,"HWNFF","get touch_panel info err,ret is %d\n");
    }
    sVar7 = strlen((char *)&local_608);
    strncat((char *)&local_608,"Touch screen type:",0x5ff - sVar7);
    sVar7 = strlen((char *)&local_608);
    strncat((char *)&local_608,(char *)&local_a10,0x5ff - sVar7);
    sVar7 = strlen((char *)&local_608);
    strncat((char *)&local_608,"\n",0x5ff - sVar7);
    memset(&local_a10,0,0x100);
    uVar8 = get_app_info("camera_main",&local_a10);
    if (uVar8 >> 0x1f != 0) {
      __android_log_print(6,"HWNFF","get camera_main info err,ret is %d\n");
    }
    sVar7 = strlen((char *)&local_608);
    strncat((char *)&local_608,"\rExternal camera type:",0x5ff - sVar7);
    sVar7 = strlen((char *)&local_608);
    strncat((char *)&local_608,(char *)&local_a10,0x5ff - sVar7);
    sVar7 = strlen((char *)&local_608);
    strncat((char *)&local_608,"\n",0x5ff - sVar7);
    memset(&local_a10,0,0x100);
    uVar8 = get_app_info("camera_slave",&local_a10);
    if (uVar8 >> 0x1f != 0) {
      __android_log_print(6,"HWNFF","get camera_slave info err,ret is %d\n");
    }
    sVar7 = strlen((char *)&local_608);
    strncat((char *)&local_608,"\rInternal camera type:",0x5ff - sVar7);
    sVar7 = strlen((char *)&local_608);
    strncat((char *)&local_608,(char *)&local_a10,0x5ff - sVar7);
    sVar7 = strlen((char *)&local_608);
    strncat((char *)&local_608,"\n",0x5ff - sVar7);
    uVar8 = get_app_info("lcd type",&local_a10);
    if (uVar8 >> 0x1f != 0) {
      __android_log_print(6,"HWNFF","get lcd_type info err,ret is %d\n");
    }
    sVar7 = strlen((char *)&local_608);
    strncat((char *)&local_608,"\rLcd type:",0x5ff - sVar7);
    sVar7 = strlen((char *)&local_608);
    strncat((char *)&local_608,(char *)&local_a10,0x5ff - sVar7);
    sVar7 = strlen((char *)&local_608);
    strncat((char *)&local_608,"\n",0x5ff - sVar7);
    local_a40 = 0;
    memset(&local_910,0,0x100);
    memset(&local_a10,0,0x100);
    __nptr = (char *)openFile("/sys/block/mmcblk0/device/manfid",&local_a40);
    if (__nptr != (char *)0x0) {
      lVar11 = strtol(__nptr,(char **)0x0,0x10);
      free(__nptr);
      lVar14 = 0;
      do {
        if (lVar11 == (&DAT_00115ae8)[lVar14 * 4]) {
          strncpy((char *)&local_a10,(&PTR_s_Micron_00115af0)[(longlong)(int)lVar14 * 2],0xff);
          goto LAB_00102bdc;
        }
        lVar14 = lVar14 + 1;
      } while (lVar14 != 6);
      sVar7 = strlen((char *)&local_a10);
      strncat((char *)&local_a10,"unknown",0xff - sVar7);
LAB_00102bdc:
      __nptr = (char *)openFile("/sys/block/mmcblk0/device/block/mmcblk0/size",&local_a40);
      if (__nptr != (char *)0x0) {
        uVar8 = atoi(__nptr);
        snprintf((char *)&local_910,0x100,"%lu",
                 -(ulonglong)(uVar8 >> 0x1f) & 0xfffffe0000000000 | (ulonglong)uVar8 << 9);
        free(__nptr);
        sVar7 = strlen((char *)&local_a10);
        strncat((char *)&local_a10,"-",0xff - sVar7);
        sVar7 = strlen((char *)&local_a10);
        strncat((char *)&local_a10,(char *)&local_910,0xff - sVar7);
      }
    }
    local_810 = 0;
    sVar7 = strlen((char *)&local_608);
    strncat((char *)&local_608,"\rEMMC flash type:",0x5ff - sVar7);
    sVar7 = strlen((char *)&local_608);
    strncat((char *)&local_608,(char *)&local_a10,0x5ff - sVar7);
    sVar7 = strlen((char *)&local_608);
    FUN_00101f50((ulonglong)__fd,&local_608,(ulonglong)(sVar7 + 1));
    break;
  case 4:
    memset(&local_910,0,0x80);
    uVar12 = 0;
    printf("in get_nv_with_rpc buf_len = %d \n",0x80);
    memset(&local_608,0,0x80);
    printf("\n60069___1");
    local_a10 = 0;
    local_a08 = 0;
    local_a00 = 0;
    uStack2552 = 0;
    local_9f0 = 0;
    uStack2536 = 0;
    local_9e0 = 0;
    uStack2520 = 0;
    printf("\n60069___2");
    memcpy(&local_a10,&local_910,0x40);
    printf("\n60069___3");
    do {
      pbVar1 = (byte *)((longlong)&local_a10 + uVar12);
      uVar13 = uVar12 & 0xffffffff;
      uVar12 = uVar12 + 1;
      printf("\nlocal_time_record.time_record[%d] = %d",uVar13,(ulonglong)*pbVar1);
    } while (uVar12 != 0x10);
    local_810 = 0;
    FUN_00101da4((ulonglong)__fd,"User\'s start-up time error",0x1b);
    break;
  case 5:
    local_a38 = 0;
    lStack2608 = 0;
    memset(&local_a10,0,0x80);
    memset(&local_910,0,0xa0);
    memset(&local_608,0,0x100);
    __s = (undefined8 *)malloc(0x80);
    if (__s == (undefined8 *)0x0) goto LAB_00103098;
    uVar8 = get_app_info("board_id",&local_608);
    if (uVar8 >> 0x1f != 0) {
      __android_log_print(6,"HWNFF","get boardid info err,ret is %d\n",(ulonglong)uVar8);
    }
    printf("get boardid info is,ret is %s\n",&local_608);
    __nptr = strstr((char *)&local_608,"Cherry-CL10");
    if ((((__nptr != (char *)0x0) ||
         (__nptr = strstr((char *)&local_608,"Cherry-20"), __nptr != (char *)0x0)) ||
        (__nptr = strstr((char *)&local_608,"C8817E"), __nptr != (char *)0x0)) ||
       (__nptr = strstr((char *)&local_608,"C8817D"), __nptr != (char *)0x0)) {
      __nptr = (char *)0x1;
    }
    local_a40 = 0x80;
    iVar9 = oem_qmi_read_nv_from_modem_common(0x226,__s,&local_a40,__nptr);
    if ((iVar9 == 0) || (printf("oem_qmi_read_nv_from_modem_common read imei fail!"), iVar9 == 0)) {
      uVar12 = 0;
      do {
        pbVar1 = (byte *)((longlong)__s + uVar12);
        uVar13 = uVar12 & 0xffffffff;
        uVar12 = uVar12 + 1;
        printf("data_ptr->ue_imei[%d] = %d",uVar13,(ulonglong)*pbVar1);
      } while (uVar12 != 9);
      bVar4 = *(byte *)__s;
      if (bVar4 == 0) {
        __android_log_print(6,"HWNFF","imei_bcd_len==0, IMEI not programmed\n");
      }
      else {
        if (bVar4 < 9) {
          iVar9 = 1;
          local_a28 = 0;
          uStack2599 = 0;
          uStack2592 = 0;
          uStack2591 = 0;
          __nptr = &local_a28;
          puVar15 = __s;
          while (puVar15 = (undefined8 *)((longlong)puVar15 + 1), iVar9 <= (int)(uint)bVar4) {
            bVar3 = *(byte *)puVar15 & 0xf;
            if ((9 < bVar3) && (1 < iVar9)) {
              *(bool *)(&local_a28 + (longlong)((iVar9 + -1) * 2)) = iVar9 < 2;
              break;
            }
            bVar5 = *(byte *)puVar15 >> 4;
            *__nptr = bVar3 + 0x30;
            if ((9 < bVar5) && (1 < iVar9)) {
              *(bool *)(&local_a28 + (longlong)(((int)__nptr - (int)&local_a28) + 1)) = iVar9 < 2;
              break;
            }
            __nptr[2] = 0;
            __nptr[1] = bVar5 + 0x30;
            iVar9 = iVar9 + 1;
            __nptr = __nptr + 2;
          }
          local_a38 = 0;
          lStack2608 = (ulonglong)bStack2584 << 0x38;
          sVar7 = strlen((char *)&local_910);
          strncat((char *)&local_910,"IMEI:",0x9f - sVar7);
          sVar7 = strlen((char *)&local_910);
          strncat((char *)&local_910,(char *)&local_a38,0x9f - sVar7);
        }
        else {
          __android_log_print(6,"HWNFF",&DAT_00104658,"Invalid IMEI value from NV\n");
        }
      }
    }
    memset(__s,0,0x80);
    iVar9 = FUN_00102020(0x797,__s);
    if (iVar9 == 0) {
      printf("data_ptr->meid.meid = %014lX",*__s);
      memset(&local_a10,0,0x80);
      snprintf((char *)&local_a10,0x80,"%014lX",*__s);
      sVar7 = strlen((char *)&local_910);
      strncat((char *)&local_910,"\r\nMEID:",0x9f - sVar7);
      sVar7 = strlen((char *)&local_910);
      strncat((char *)&local_910,(char *)&local_a10,0x9f - sVar7);
    }
    memset(__s,0,0x80);
    iVar9 = FUN_00102020(0x72,__s);
    if (iVar9 == 0) {
      lVar14 = 0;
      do {
        lVar2 = lVar14 + 1;
        printf("data_ptr->fact_info[%d] = %c",(ulonglong)((int)lVar14 + 0x19),
               (ulonglong)*(byte *)((longlong)__s + lVar14 + 0x19));
        lVar14 = lVar2;
      } while (lVar2 != 0x10);
      memset(&local_a10,0,0x80);
      local_a10 = *(ulonglong *)((longlong)__s + 0x19);
      local_a08 = *(ulonglong *)((longlong)__s + 0x21);
      sVar7 = strlen((char *)&local_910);
      strncat((char *)&local_910,"\r\nSN:",0x9f - sVar7);
      sVar7 = strlen((char *)&local_910);
      strncat((char *)&local_910,(char *)&local_a10,0x9f - sVar7);
    }
    memset(__s,0,0x80);
    iVar9 = FUN_00102020(0x1bf,__s);
    if (iVar9 == 0) {
      uVar12 = 0;
      memset(&local_a10,0,0x80);
      do {
        printf("data_ptr->bd_addr[%d] = %x",uVar12 & 0xffffffff,
               (ulonglong)*(byte *)((longlong)__s + uVar12));
        lVar14 = uVar12 * 2;
        iVar9 = (int)uVar12;
        lVar2 = 5 - uVar12;
        uVar12 = uVar12 + 1;
        snprintf((char *)((longlong)&local_a10 + lVar14),iVar9 * -2 + 0x80,"%02x",
                 (ulonglong)*(byte *)((longlong)__s + lVar2));
      } while (uVar12 != 6);
      sVar7 = strlen((char *)&local_910);
      strncat((char *)&local_910,"\r\nBT:",0x9f - sVar7);
      sVar7 = strlen((char *)&local_910);
      strncat((char *)&local_910,(char *)&local_a10,0x9f - sVar7);
    }
    memset(__s,0,0x80);
    iVar9 = FUN_00102020(0x1246,__s);
    if (iVar9 == 0) {
      uVar12 = 0;
      memset(&local_a10,0,0x80);
      do {
        printf("data_ptr->wlan_mac_address[%d] = %x",uVar12 & 0xffffffff,
               (ulonglong)*(byte *)((longlong)__s + uVar12));
        iVar9 = (int)uVar12;
        lVar2 = 5 - uVar12;
        lVar14 = uVar12 * 2;
        uVar12 = uVar12 + 1;
        snprintf((char *)((longlong)&local_a10 + lVar14),iVar9 * -2 + 0x80,"%02x",
                 (ulonglong)*(byte *)((longlong)__s + lVar2));
      } while (uVar12 != 6);
      sVar7 = strlen((char *)&local_910);
      strncat((char *)&local_910,"\r\nWiFi:",0x9f - sVar7);
      sVar7 = strlen((char *)&local_910);
      strncat((char *)&local_910,(char *)&local_a10,0x9f - sVar7);
    }
    local_810 = 0;
    sVar7 = strlen((char *)&local_910);
    FUN_00101f50((ulonglong)__fd,&local_910,(ulonglong)(sVar7 + 1));
    free(__s);
    break;
  case 6:
    local_810 = FUN_00101da4((ulonglong)__fd,"Ver2.3",7);
    break;
  case 7:
    local_608 = 0;
    uStack1536 = 0;
    local_5f8 = 0;
    local_5f0 = 0;
    local_a10 = 0;
    local_a08 = local_a08 & 0xff00000000000000;
    local_910 = 0;
    local_908 = local_908 & 0xff00000000000000;
    iVar9 = property_get("ro.board.platform",&local_a10,0x104158);
    if (iVar9 == 0) {
      __android_log_print(6,"HWNFF","Daemon: %s property_get ro.product.brand fail\n","get_platform"
                         );
    }
    iVar9 = property_get("ro.product.board",&local_910,0x104158);
    if (iVar9 == 0) {
      __android_log_print(6,"HWNFF","Daemon: %s property_get ro.product.brand fail\n","get_platform"
                         );
    }
    sVar7 = strlen((char *)&local_608);
    strncat((char *)&local_608,(char *)&local_a10,0x1f - sVar7);
    sVar7 = strlen((char *)&local_608);
    strncat((char *)&local_608,",",0x1f - sVar7);
    sVar7 = strlen((char *)&local_608);
    strncat((char *)&local_608,(char *)&local_910,0x1f - sVar7);
LAB_001028a0:
    local_810 = 1;
    sVar7 = strlen((char *)&local_608);
    FUN_00101da4((ulonglong)__fd,&local_608,(ulonglong)(sVar7 + 1));
    break;
  case 8:
    local_5f8 = 0;
    local_608 = 0;
    uStack1536 = 0;
    local_a40 = 0;
    local_5f0 = (ulonglong)(local_5f0._4_4_ & 0xffff0000) << 0x20;
    iVar9 = FUN_0010327c();
    iVar10 = hw_widevine_get_lock_state(&local_a40);
    if (iVar10 == 0) {
      __android_log_print(6,"HWNFF","Daemon: %s widevine_get_lock_state fail\n","get_root_status");
    }
    sVar7 = strlen((char *)&local_608);
    uVar12 = (ulonglong)sVar7;
    *(undefined8 *)((longlong)&local_608 + uVar12) = 0x616f6c746f6f6228;
    *(undefined4 *)(&uStack1536 + uVar12) = 0x29726564;
    *(undefined2 *)(&uStack1536 + uVar12 + 4) = 0x20;
    if ((iVar9 == 0) && (local_a40 == 0)) {
      *(undefined4 *)((longlong)&local_608 + uVar12 + 0xd) = 0x6b636f6c;
      *(undefined2 *)(&uStack1536 + uVar12 + 9) = 0x6465;
      (&uStack1536)[uVar12 + 0xb] = 0;
    }
    else {
      *(undefined8 *)((longlong)&local_608 + uVar12 + 0xd) = 0x64656b636f6c6e75;
      (&uStack1536)[uVar12 + 0xd] = 0;
    }
LAB_001023e8:
    sVar7 = strlen((char *)&local_608);
    local_810 = FUN_00101da4((ulonglong)__fd,&local_608,(ulonglong)(sVar7 + 1));
    break;
  case 9:
    local_5f8 = 0;
    local_608 = 0;
    uStack1536 = 0;
    local_5f0 = ((ulonglong)local_5f0._4_4_ & 0xffff0000) << 0x20;
    local_a40 = 0;
    uVar12 = rmt_oeminfo_read(0x47,4,&local_a40);
    if ((int)uVar12 == 0) {
      snprintf((char *)&local_608,0x1e,"\r\n%d\r\nOKAY\r\n",(ulonglong)local_a40._2_1_);
      goto LAB_001023e8;
    }
    local_810 = 0xffffffff;
    __android_log_print(6,"HWNFF","get_powerfail_num:remote_oeminfo_read fail %d\n",
                        uVar12 & 0xffffffff);
  }
LAB_00102364:
  usleep(20000);
  send(__fd,"HWNFFDATAEND",0xd,0);
  pthread_mutex_unlock((pthread_mutex_t *)&__bss_start__);
LAB_00102334:
  close(__fd);
  __th = pthread_self();
  pthread_detach(__th);
                    /* WARNING: Subroutine does not return */
  pthread_exit((void *)0x0);
}


