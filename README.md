# HWNFF Client

I noticed an undocumented service running as root on a Huawei phone called hwnffserver.
On the phone, there is also a client to interact with it (called hwnff).

I investigated a little bit on this service that is used to recover some information even from an unprivileged user.

In particular, you can obtain:
* `/sys/class/power_supply/battery/temp`
* `/sys/class/power_supply/battery/voltage_now`
* Mobile Signal Strength Info
* Touch screen type
* Camera type
* LCD Type
* EMMC flash type
* IMEI
* SerialNumber
* MAC address
* product model
* bootloader status
