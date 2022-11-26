
export hostip=$(cat /etc/resolv.conf |grep -oP '(?<=nameserver\ ).*')
export https_proxy="http://${hostip}:7890"
export http_proxy="http://${hostip}:7890"
export ALL_proxy="http://${hostip}:7890"
export all_proxy="http://${hostip}:7890"
echo "finish"