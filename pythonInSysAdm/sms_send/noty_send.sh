#!/bin/bash

num=+71234567890 #номер адресата
log=qwe@mail.ru  #Ваш почтовый ящик с которого будут высылаться смс
pas=*******      #Пароль от ящика
msg=$1

python ./send.py -l $log -p $pas -n $num -t "$msg"

exit 0
