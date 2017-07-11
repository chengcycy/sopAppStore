

rm -rf /home/ccy/SyberOS-SDK/root/jail-xuanwu/opt/cross/armv7tnhl-meego-linux-gnueabi/sys-root/lib/sdkplugins/
rm -f /home/ccy/SyberOS-SDK/root/jail-xuanwu/opt/cross/armv7tnhl-meego-linux-gnueabi/sys-root/lib/libimsdkapi.so
rm -f /home/ccy/SyberOS-SDK/root/jail-xuanwu/opt/cross/armv7tnhl-meego-linux-gnueabi/sys-root/lib/libservice.so

cp -rf  sdkplugins /home/ccy/SyberOS-SDK/root/jail-xuanwu/opt/cross/armv7tnhl-meego-linux-gnueabi/sys-root/lib/sdkplugins/
cp -f  libimsdkapi.so /home/ccy/SyberOS-SDK/root/jail-xuanwu/opt/cross/armv7tnhl-meego-linux-gnueabi/sys-root/lib
cp -f  libservice.so /home/ccy/SyberOS-SDK/root/jail-xuanwu/opt/cross/armv7tnhl-meego-linux-gnueabi/sys-root/lib
