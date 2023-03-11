case $1 in
   -on) sudo echo -e "15 *	* * *	root	wget -O - http://127.0.0.1:8080/PHP/testScheduleDBReset.php >/dev/null 2>&1\n" > /etc/cron.d/root
   -off) sudo rm /etc/cron.d/root
   -now) ls /etd/cron.d | grep root;;
   *) echo "wrong input :(" ;;
esac





